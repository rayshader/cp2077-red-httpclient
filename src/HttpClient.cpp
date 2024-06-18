#include "HttpClient.h"

#include <cpr/cpr.h>
#include <string>

#include "HttpHeader.h"
#include "HttpMethod.h"
#include "HttpPlugin.h"

namespace RedHttpClient {

HttpPlugin* HttpClient::plugin = HttpPlugin::get();

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
  HttpHeaders headers;

  for (const auto& header : p_response.header) {
    headers.EmplaceBack(header.first, header.second);
  }
  return headers;
}

template <HttpMethod Method, class T>
Red::Handle<HttpResponse> HttpClient::send(
  const Red::CString& p_url, const T& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  if constexpr (std::is_same<T, Red::CString>()) {
    return send_body<Method>(p_url, p_body, p_headers);
  } else if constexpr (std::is_same<T, HttpPairs>()) {
    return send_form<Method>(p_url, p_body, p_headers);
  } else if constexpr (std::is_same<T, Red::Handle<HttpMultipart>>()) {
    return send_multipart<Method>(p_url, p_body, p_headers);
  }
  return {};
}

template <HttpMethod Method>
Red::Handle<HttpResponse> HttpClient::send_body(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  plugin->log_request(Method, p_url, p_body, request_headers);
  cpr::Response response;

  if constexpr (Method == HttpMethod::POST) {
    response = cpr::Post(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                         cpr::Body{p_body.c_str()}, request_headers);
  } else if constexpr (Method == HttpMethod::PUT) {
    response = cpr::Put(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                        cpr::Body{p_body.c_str()}, request_headers);
  } else if constexpr (Method == HttpMethod::PATCH) {
    response = cpr::Patch(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                          cpr::Body{p_body.c_str()}, request_headers);
  } else if constexpr (Method == HttpMethod::DELETE_) {
    response = cpr::Delete(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                           cpr::Body{p_body.c_str()}, request_headers);
  }
  Red::DynArray<HttpHeader> headers = get_headers(response);

  plugin->log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

template <HttpMethod Method>
Red::Handle<HttpResponse> HttpClient::send_form(
  const Red::CString& p_url, const HttpPairs& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  plugin->log_request(Method, p_url, p_form, request_headers);
  cpr::Response response;

  if constexpr (Method == HttpMethod::POST) {
    response =
      cpr::Post(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                cpr::Payload{values.begin(), values.end()}, request_headers);
  } else if constexpr (Method == HttpMethod::PUT) {
    response =
      cpr::Put(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
               cpr::Payload{values.begin(), values.end()}, request_headers);
  } else if constexpr (Method == HttpMethod::PATCH) {
    response =
      cpr::Patch(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                 cpr::Payload{values.begin(), values.end()}, request_headers);
  } else if constexpr (Method == HttpMethod::DELETE_) {
    response =
      cpr::Delete(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                  cpr::Payload{values.begin(), values.end()}, request_headers);
  }
  Red::DynArray<HttpHeader> headers = get_headers(response);

  plugin->log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

template <HttpMethod Method>
Red::Handle<HttpResponse> HttpClient::send_multipart(
  const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  plugin->log_request(Method, p_url, p_form, request_headers);
  cpr::Response response;

  if constexpr (Method == HttpMethod::POST) {
    response = cpr::Post(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                         p_form->get(), request_headers);
  } else if constexpr (Method == HttpMethod::PUT) {
    response = cpr::Put(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                        p_form->get(), request_headers);
  } else if constexpr (Method == HttpMethod::PATCH) {
    response = cpr::Patch(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                          p_form->get(), request_headers);
  } else if constexpr (Method == HttpMethod::DELETE_) {
    response = cpr::Delete(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                           p_form->get(), request_headers);
  }
  Red::DynArray<HttpHeader> headers = get_headers(response);

  plugin->log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::get(
  const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers) {
  if (!is_secure(p_url)) {
    return {};
  }
  cpr::Header request_headers = build_headers(p_headers.value);

  plugin->log_request(HttpMethod::GET, p_url, "", request_headers);
  cpr::Response response = cpr::Get(plugin->get_ssl_options(),
                                    cpr::Url{p_url.c_str()}, request_headers);
  HttpHeaders headers = get_headers(response);

  plugin->log_response(response);
  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::POST>(p_url, p_body, p_headers);
}

Red::Handle<HttpResponse> HttpClient::post_form(
  const Red::CString& p_url, const HttpPairs& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::POST>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::post_multipart(
  const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::POST>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::put(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PUT>(p_url, p_body, p_headers);
}

Red::Handle<HttpResponse> HttpClient::put_form(
  const Red::CString& p_url, const HttpPairs& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PUT>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::put_multipart(
  const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PUT>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::patch(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PATCH>(p_url, p_body, p_headers);
}

Red::Handle<HttpResponse> HttpClient::patch_form(
  const Red::CString& p_url, const HttpPairs& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PATCH>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::patch_multipart(
  const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::PATCH>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::delete_(
  const Red::CString& p_url, const Red::Optional<Red::CString>& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::DELETE_>(p_url, p_body.value, p_headers);
}

Red::Handle<HttpResponse> HttpClient::delete_form(
  const Red::CString& p_url, const HttpPairs& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::DELETE_>(p_url, p_form, p_headers);
}

Red::Handle<HttpResponse> HttpClient::delete_multipart(
  const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  return send<HttpMethod::DELETE_>(p_url, p_form, p_headers);
}

}  // namespace RedHttpClient