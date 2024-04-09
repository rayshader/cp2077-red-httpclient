#include "HttpClient.h"

#include <cpr/cpr.h>

#include "HttpHeader.h"

namespace RedHttpClient {

Red::DynArray<HttpHeader> HttpClient::get_headers(
  const cpr::Response& p_response) {
  Red::DynArray<HttpHeader> headers;

  for (const auto& header : p_response.header) {
    HttpHeader http_header;

    http_header.name = header.first;
    http_header.value = header.second;
    headers.PushBack(http_header);
  }
  return headers;
}

Red::Handle<HttpResponse> HttpClient::get(const Red::CString& p_url) {
  cpr::Response response = cpr::Get(cpr::Url{p_url.c_str()});
  Red::DynArray<HttpHeader> headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post(const Red::CString& p_url,
                                           const Red::CString& p_body) {
  cpr::Response response =
    cpr::Post(cpr::Url{p_url.c_str()}, cpr::Body{p_body.c_str()},
              cpr::Header{{"Content-Type", "text/plain"}});
  Red::DynArray<HttpHeader> headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

Red::Handle<HttpResponse> HttpClient::post_form(
  const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form) {
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Response response = cpr::Post(
    cpr::Url{p_url.c_str()}, cpr::Payload{values.begin(), values.end()});
  Red::DynArray<HttpHeader> headers = get_headers(response);

  return Red::MakeHandle<HttpResponse>(response.status_code, headers,
                                       response.text);
}

}  // namespace RedHttpClient