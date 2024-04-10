#ifndef REDHTTPCLIENT_HTTPCLIENT_H
#define REDHTTPCLIENT_HTTPCLIENT_H

#include <cpr/cpr.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpHeader.h"
#include "HttpPair.h"
#include "HttpResponse.h"

namespace RedHttpClient {

class HttpClient : public Red::IScriptable {
 private:
  static const cpr::SslOptions ssl_options;

  static inline bool is_secure(const Red::CString& p_url);
  static cpr::Header build_headers(const HttpHeaders& p_headers);
  static HttpHeaders get_headers(const cpr::Response& p_response);

 public:
  static Red::Handle<HttpResponse> get(
    const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> post(
    const Red::CString& p_url, const Red::CString& p_body,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> post_form(
    const Red::CString& p_url, const Red::DynArray<HttpPair>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);

  RTTI_IMPL_TYPEINFO(RedHttpClient::HttpClient);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpClient, {
  RTTI_ALIAS("RedHttpClient.HttpClient");

  RTTI_METHOD(get, "Get");
  RTTI_METHOD(post, "Post");
  RTTI_METHOD(post_form, "PostForm");
});

#endif  //REDHTTPCLIENT_HTTPCLIENT_H
