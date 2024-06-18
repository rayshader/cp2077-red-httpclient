#ifndef REDHTTPCLIENT_ASYNCHTTPCLIENT_H
#define REDHTTPCLIENT_ASYNCHTTPCLIENT_H

#include <cpr/cpr.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpCallback.h"
#include "HttpHeader.h"
#include "HttpMultipart.h"
#include "HttpPair.h"
#include "HttpPlugin.h"

namespace RedHttpClient {

class AsyncHttpClient : public Red::IScriptable {
 private:
  static HttpPlugin* plugin;

  inline static void queue_request(
    const std::shared_future<cpr::Response>& p_future,
    const HttpCallback& p_callback);

  template <HttpMethod Method, class T>
  inline static void send(const HttpCallback& p_callback,
                          const Red::CString& p_url, const T& p_body,
                          const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static void send_body(const HttpCallback& p_callback,
                               const Red::CString& p_url,
                               const Red::CString& p_body,
                               const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static void send_form(const HttpCallback& p_callback,
                               const Red::CString& p_url,
                               const HttpPairs& p_form,
                               const Red::Optional<HttpHeaders>& p_headers);

  template <HttpMethod Method>
  inline static void send_multipart(
    const HttpCallback& p_callback, const Red::CString& p_url,
    const Red::Handle<HttpMultipart>& p_form,
    const Red::Optional<HttpHeaders>& p_headers);

 public:
  static void get(const HttpCallback& p_callback, const Red::CString& p_url,
                  const Red::Optional<HttpHeaders>& p_headers);
  static void post(const HttpCallback& p_callback, const Red::CString& p_url,
                   const Red::CString& p_body,
                   const Red::Optional<HttpHeaders>& p_headers);
  static void post_form(const HttpCallback& p_callback,
                        const Red::CString& p_url, const HttpPairs& p_form,
                        const Red::Optional<HttpHeaders>& p_headers);
  static void post_multipart(const HttpCallback& p_callback,
                             const Red::CString& p_url,
                             const Red::Handle<HttpMultipart>& p_form,
                             const Red::Optional<HttpHeaders>& p_headers);
  static void put(const HttpCallback& p_callback, const Red::CString& p_url,
                  const Red::CString& p_body,
                  const Red::Optional<HttpHeaders>& p_headers);
  static void put_form(const HttpCallback& p_callback,
                       const Red::CString& p_url, const HttpPairs& p_form,
                       const Red::Optional<HttpHeaders>& p_headers);
  static void put_multipart(const HttpCallback& p_callback,
                            const Red::CString& p_url,
                            const Red::Handle<HttpMultipart>& p_form,
                            const Red::Optional<HttpHeaders>& p_headers);
  static void patch(const HttpCallback& p_callback, const Red::CString& p_url,
                    const Red::CString& p_body,
                    const Red::Optional<HttpHeaders>& p_headers);
  static void patch_form(const HttpCallback& p_callback,
                         const Red::CString& p_url, const HttpPairs& p_form,
                         const Red::Optional<HttpHeaders>& p_headers);
  static void patch_multipart(const HttpCallback& p_callback,
                              const Red::CString& p_url,
                              const Red::Handle<HttpMultipart>& p_form,
                              const Red::Optional<HttpHeaders>& p_headers);
  static void delete_(const HttpCallback& p_callback, const Red::CString& p_url,
                      const Red::Optional<Red::CString>& p_body,
                      const Red::Optional<HttpHeaders>& p_headers);
  static void delete_form(const HttpCallback& p_callback,
                          const Red::CString& p_url, const HttpPairs& p_form,
                          const Red::Optional<HttpHeaders>& p_headers);
  static void delete_multipart(const HttpCallback& p_callback,
                               const Red::CString& p_url,
                               const Red::Handle<HttpMultipart>& p_form,
                               const Red::Optional<HttpHeaders>& p_headers);

  RTTI_IMPL_TYPEINFO(RedHttpClient::AsyncHttpClient);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::AsyncHttpClient, {
  RTTI_ALIAS("RedHttpClient.AsyncHttpClient");

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

#endif  //REDHTTPCLIENT_ASYNCHTTPCLIENT_H
