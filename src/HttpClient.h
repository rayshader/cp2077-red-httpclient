#ifndef REDHTTPCLIENT_HTTPCLIENT_H
#define REDHTTPCLIENT_HTTPCLIENT_H

#include <cpr/cpr.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpHeader.h"
#include "HttpMethod.h"
#include "HttpMultipart.h"
#include "HttpPair.h"
#include "HttpPlugin.h"
#include "HttpResponse.h"

namespace RedHttpClient {

class HttpClient : public Red::IScriptable {
 private:
  static HttpPlugin* plugin;

  template <HttpMethod Method, class T>
  inline static Red::Handle<HttpResponse> send(
    const Red::CString& p_url, const T& p_body,
    const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static Red::Handle<HttpResponse> send_body(
    const Red::CString& p_url, const Red::CString& p_body,
    const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static Red::Handle<HttpResponse> send_form(
    const Red::CString& p_url, const HttpPairs& p_form,
    const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static Red::Handle<HttpResponse> send_multipart(
    const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);

 public:
  static bool is_secure(const Red::CString& p_url);
  static cpr::Header build_headers(const HttpHeaders& p_headers);
  static HttpHeaders get_headers(const cpr::Response& p_response);

 public:
  static Red::Handle<HttpResponse> get(
    const Red::CString& p_url, const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> post(
    const Red::CString& p_url, const Red::CString& p_body,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> post_form(
    const Red::CString& p_url, const HttpPairs& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> post_multipart(
    const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> put(
    const Red::CString& p_url, const Red::CString& p_body,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> put_form(
    const Red::CString& p_url, const HttpPairs& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> put_multipart(
    const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> patch(
    const Red::CString& p_url, const Red::CString& p_body,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> patch_form(
    const Red::CString& p_url, const HttpPairs& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> patch_multipart(
    const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> delete_(
    const Red::CString& p_url, const Red::Optional<Red::CString>& p_body,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> delete_form(
    const Red::CString& p_url, const HttpPairs& p_form,
    const Red::Optional<HttpHeaders>& p_headers);
  static Red::Handle<HttpResponse> delete_multipart(
    const Red::CString& p_url, const Red::Handle<HttpMultipart>& p_form,
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
  RTTI_METHOD(post_multipart, "PostMultipart");
  RTTI_METHOD(put, "Put");
  RTTI_METHOD(put_form, "PutForm");
  RTTI_METHOD(put_multipart, "PutMultipart");
  RTTI_METHOD(patch, "Patch");
  RTTI_METHOD(patch_form, "PatchForm");
  RTTI_METHOD(patch_multipart, "PatchMultipart");
  RTTI_METHOD(delete_, "Delete");
  RTTI_METHOD(delete_form, "DeleteForm");
  RTTI_METHOD(delete_multipart, "DeleteMultipart");
});

#endif  //REDHTTPCLIENT_HTTPCLIENT_H
