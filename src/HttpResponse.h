#ifndef REDHTTPCLIENT_HTTPRESPONSE_H
#define REDHTTPCLIENT_HTTPRESPONSE_H

#include <utility>

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpHeader.h"

namespace RedHttpClient {

class HttpResponse : public Red::IScriptable {
 private:
  int32_t status_code = -1;
  Red::DynArray<HttpHeader> headers;
  Red::CString body;

 public:
  HttpResponse() = default;
  explicit HttpResponse(int32_t p_status_code,
                        Red::DynArray<HttpHeader> p_headers,
                        Red::CString p_body)
      : status_code(p_status_code),
        headers(std::move(p_headers)),
        body(std::move(p_body)) {}

  [[nodiscard]] int32_t get_status_code() const {
    return status_code;
  }

  [[nodiscard]] Red::DynArray<HttpHeader> get_headers() const {
    return headers;
  }

  [[nodiscard]] Red::CString get_text() const {
    return body;
  }

  RTTI_IMPL_TYPEINFO(RedHttpClient::HttpResponse);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpResponse, {
  RTTI_ALIAS("RedHttpClient.HttpResponse");

  RTTI_METHOD(get_status_code, "GetStatusCode");
  RTTI_METHOD(get_headers, "GetHeaders");
  RTTI_METHOD(get_text, "GetText");
});

#endif  //REDHTTPCLIENT_HTTPRESPONSE_H
