#include "HttpClient.h"

#include <cpr/cpr.h>
#include <string>

#include "HttpHeader.h"
#include "HttpMethod.h"

namespace RedHttpClient {

const cpr::SslOptions HttpClient::ssl_options = cpr::Ssl(cpr::ssl::TLSv1_2{});
Settings HttpClient::settings;
Red::Logger* HttpClient::logger = nullptr;
Red::PluginHandle HttpClient::handle = nullptr;

bool HttpClient::is_secure(const Red::CString& p_url) {
  std::string url(p_url.c_str());

  return url.starts_with("https://");
}

cpr::Header HttpClient::build_headers(
  const RedHttpClient::HttpHeaders& p_headers) {
  cpr::Header headers;

  for (const auto& header : p_headers) {
    headers.emplace(header.name.c_str(), header.value.c_str());
  }
  return headers;
}

HttpHeaders HttpClient::get_headers(const cpr::Response& p_response) {
  Red::DynArray<HttpHeader> headers;

  for (const auto& header : p_response.header) {
    HttpHeader http_header;

    http_header.name = header.first;
    http_header.value = header.second;
    headers.PushBack(http_header);
  }
  return headers;
}

const char* log_http_method(const HttpMethod p_method) {
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
      return nullptr;
  }
}

void HttpClient::log_request(const HttpMethod p_method,
                             const Red::CString& p_url,
                             const Red::CString& p_body,
                             const cpr::Header& p_headers) {
  if (logger == nullptr || handle == nullptr || !settings.can_log()) {
    return;
  }
  const char* method = log_http_method(p_method);

  logger->Info(handle, "HTTP request:");
  logger->Info(handle, std::format("{} {}", method, p_url.c_str()).c_str());
  for (const auto& header : p_headers) {
    logger->Info(handle,
                 std::format("{}: {}", header.first, header.second).c_str());
  }
  if (p_body.length > 0) {
    logger->Info(handle, "");
    logger->Info(handle, p_body.c_str());
  }
}

void HttpClient::log_request_form(const HttpMethod p_method,
                                  const Red::CString& p_url,
                                  const Red::DynArray<HttpPair>& p_form,
                                  const cpr::Header& p_headers) {
  if (logger == nullptr || handle == nullptr || !settings.can_log()) {
    return;
  }
  std::string body;

  for (int i = 0; i < p_form.size; i++) {
    const auto& pair = p_form[i];

    body += pair.key.c_str();
    body += "=";
    body += pair.value.c_str();
    if (i + 1 < p_form.size) {
      body += "&";
    }
  }
  log_request(p_method, p_url, body.c_str(), p_headers);
}

void HttpClient::log_response(const cpr::Response& p_response) {
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

void HttpClient::load(const RED4ext::Sdk* p_sdk,
                      const Red::PluginHandle& p_handle) {
  logger = p_sdk->logger;
  handle = p_handle;
  Red::GameState init;

  init.OnEnter = [](Red::CGameApplication* p_app) -> bool {
    HttpClient::start();
    return true;
  };
  init.OnUpdate = nullptr;
  init.OnExit = nullptr;
  Red::GameState shutdown;

  shutdown.OnEnter = [](Red::CGameApplication* p_app) -> bool {
    HttpClient::stop();
    return true;
  };
  init.OnUpdate = nullptr;
  init.OnExit = nullptr;
  p_sdk->gameStates->Add(p_handle, Red::EGameStateType::Initialization, &init);
  p_sdk->gameStates->Add(p_handle, Red::EGameStateType::Shutdown, &shutdown);
}

void HttpClient::start() {
  settings.load();
}

void HttpClient::stop() {
  settings.unload();
}

void HttpClient::unload() {
  logger = nullptr;
  handle = nullptr;
}

Red::Handle<HttpResponse> HttpClient::get(
  const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  log_request(HttpMethod::GET, p_url, "", request_headers);
  cpr::Response response =
    cpr::Get(ssl_options, cpr::Url{p_url.c_str()}, request_headers);
  HttpHeaders headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  log_request(HttpMethod::POST, p_url, p_body, request_headers);
  cpr::Response response =
    cpr::Post(ssl_options, cpr::Url{p_url.c_str()}, cpr::Body{p_body.c_str()},
              request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post_form(
  const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  log_request_form(HttpMethod::POST, p_url, p_form, request_headers);
  cpr::Response response =
    cpr::Post(ssl_options, cpr::Url{p_url.c_str()},
              cpr::Payload{values.begin(), values.end()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::put(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  log_request(HttpMethod::PUT, p_url, p_body, request_headers);
  cpr::Response response = cpr::Put(ssl_options, cpr::Url{p_url.c_str()},
                                    cpr::Body{p_body.c_str()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::put_form(
  const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  log_request_form(HttpMethod::PUT, p_url, p_form, request_headers);
  cpr::Response response =
    cpr::Put(ssl_options, cpr::Url{p_url.c_str()},
             cpr::Payload{values.begin(), values.end()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::patch(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  log_request(HttpMethod::PATCH, p_url, p_body, request_headers);

  cpr::Response response =
    cpr::Patch(ssl_options, cpr::Url{p_url.c_str()}, cpr::Body{p_body.c_str()},
               request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::patch_form(
  const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  log_request_form(HttpMethod::PATCH, p_url, p_form, request_headers);
  cpr::Response response =
    cpr::Patch(ssl_options, cpr::Url{p_url.c_str()},
               cpr::Payload{values.begin(), values.end()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::delete_(
  const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  log_request(HttpMethod::DELETE_, p_url, "", request_headers);
  cpr::Response response =
    cpr::Delete(ssl_options, cpr::Url{p_url.c_str()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

}  // namespace RedHttpClient