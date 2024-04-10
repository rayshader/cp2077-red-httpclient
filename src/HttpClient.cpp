#include "HttpClient.h"

#include <cpr/cpr.h>

#include "HttpHeader.h"

namespace RedHttpClient {

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

Red::Handle<HttpResponse> HttpClient::get(
  const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers) {
  cpr::Header request_headers = build_headers(p_headers.value);
  cpr::Response response = cpr::Get(cpr::Url{p_url.c_str()}, request_headers);
  HttpHeaders headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post(
  const Red::CString& p_url, const Red::CString& p_body,
  const Red::Optional<HttpHeaders>& p_headers) {
  cpr::Header request_headers = build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  cpr::Response response = cpr::Post(
    cpr::Url{p_url.c_str()}, cpr::Body{p_body.c_str()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post_form(
  const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = build_headers(p_headers.value);
  cpr::Response response =
    cpr::Post(cpr::Url{p_url.c_str()},
              cpr::Payload{values.begin(), values.end()}, request_headers);
  Red::DynArray<HttpHeader> headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

}  // namespace RedHttpClient