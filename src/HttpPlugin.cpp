#include "HttpPlugin.h"

namespace RedHttpClient {
HttpPlugin HttpPlugin::singleton;

HttpPlugin::HttpPlugin()
    : logger(nullptr),
      handle(nullptr),
      ssl_options(cpr::Ssl(cpr::ssl::TLSv1_2{})) {}

HttpPlugin* HttpPlugin::get() {
  return &singleton;
}

void HttpPlugin::load(const RED4ext::Sdk* p_sdk,
                      RED4ext::PluginHandle p_handle) {
  logger = p_sdk->logger;
  handle = p_handle;
  Red::GameState init;

  init.OnEnter = [](Red::CGameApplication* p_app) -> bool {
    HttpPlugin::get()->start();
    return true;
  };
  init.OnUpdate = nullptr;
  init.OnExit = nullptr;
  Red::GameState shutdown;

  shutdown.OnEnter = [](Red::CGameApplication* p_app) -> bool {
    HttpPlugin::get()->stop();
    return true;
  };
  shutdown.OnUpdate = nullptr;
  shutdown.OnExit = nullptr;
  p_sdk->gameStates->Add(p_handle, Red::EGameStateType::Initialization, &init);
  p_sdk->gameStates->Add(p_handle, Red::EGameStateType::Shutdown, &shutdown);
}

void HttpPlugin::unload() {
  logger = nullptr;
  handle = nullptr;
}

void HttpPlugin::start() {
  settings.load();
}

void HttpPlugin::stop() {
  settings.unload();
}

cpr::SslOptions HttpPlugin::get_ssl_options() const {
  return ssl_options;
}

std::string HttpPlugin::log_http_method(HttpMethod p_method) {
  switch (p_method) {
    case HttpMethod::GET:
      return "GET";
    case HttpMethod::POST:
      return "POST";
    case HttpMethod::PUT:
      return "PUT";
    case HttpMethod::PATCH:
      return "PATCH";
    case HttpMethod::DELETE_:
      return "DELETE";
    default:
      return "";
  }
}

void HttpPlugin::log_response(const cpr::Response& p_response) {
  if (logger == nullptr || handle == nullptr || !settings.can_log()) {
    return;
  }
  logger->Info(handle, "HTTP response:");
  logger->Info(handle, std::format("HTTP/1.1 {} {}", p_response.status_code,
                                   p_response.reason)
                         .c_str());
  for (const auto& header : p_response.header) {
    logger->Info(handle,
                 std::format("{}: {}", header.first, header.second).c_str());
  }
  if (!p_response.text.empty()) {
    logger->Info(handle, "");
    logger->Info(handle, p_response.text.c_str());
  }
}

}  // namespace RedHttpClient