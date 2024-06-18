#ifndef REDHTTPCLIENT_HTTPPLUGIN_H
#define REDHTTPCLIENT_HTTPPLUGIN_H

#include <cpr/response.h>
#include <cpr/ssl_options.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpMethod.h"
#include "HttpMultipart.h"
#include "HttpPair.h"
#include "Settings.h"

namespace RedHttpClient {

class HttpPlugin {
 private:
  static HttpPlugin singleton;

  Red::PluginHandle handle;
  Red::Logger* logger;

  const cpr::SslOptions ssl_options;

  Settings settings;

  static std::string log_http_method(HttpMethod p_method);

 public:
  HttpPlugin();

  static HttpPlugin* get();

  void load(const RED4ext::Sdk* p_sdk, Red::PluginHandle p_handle);
  void unload();

  void start();
  void stop();

  [[nodiscard]] cpr::SslOptions get_ssl_options() const;

  void log_response(const cpr::Response& p_response);

  template <class T>
  void log_request(HttpMethod p_method, const Red::CString& p_url,
                   const T& p_body, const cpr::Header& p_headers) {
    if (logger == nullptr || handle == nullptr || !settings.can_log()) {
      return;
    }
    const std::string method = log_http_method(p_method);

    logger->Info(handle, "HTTP request:");
    logger->Info(handle, std::format("{} {}", method, p_url.c_str()).c_str());
    for (const auto& header : p_headers) {
      logger->Info(handle,
                   std::format("{}: {}", header.first, header.second).c_str());
    }
    std::string body;

    if constexpr (std::is_same<T, Red::CString>()) {
      body = p_body.c_str();
    } else if constexpr (std::is_same<T, HttpPairs>()) {
      for (int i = 0; i < p_body.size; i++) {
        const auto& pair = p_body[i];

        body += pair.key.c_str();
        body += "=";
        body += pair.value.c_str();
        if (i + 1 < p_body.size) {
          body += "&";
        }
      }
    } else if constexpr (std::is_same<T, Red::Handle<HttpMultipart>>()) {
      cpr::Multipart multipart = p_body->get();
      const std::string boundary = "-----------------------------52414e444f4d";

      for (const auto& part : multipart.parts) {
        body += boundary + "\n";
        body += "Content-Disposition: form-data; name=\"" + part.name + "\"\n";
        body += "\n";
        body += part.value + "\n";
      }
      body += "\n";
      body += boundary;
    }
    logger->Info(handle, "");
    logger->Info(handle, body.c_str());
  }
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPPLUGIN_H
