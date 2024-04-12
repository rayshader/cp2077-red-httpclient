#ifndef REDHTTPCLIENT_ASYNCHTTPCLIENT_H
#define REDHTTPCLIENT_ASYNCHTTPCLIENT_H

#include <cpr/cpr.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpCallback.h"
#include "HttpHeader.h"
#include "HttpPair.h"

namespace RedHttpClient {

class AsyncHttpClient : public Red::IScriptable {
 private:
  static void queue_request(const std::shared_future<cpr::Response>& p_future,
                            const HttpCallback& p_callback);

 public:
  static void get(const HttpCallback& p_callback, const Red::CString& p_url,
                  const Red::Optional<HttpHeaders>& p_headers);
  static void post(const HttpCallback& p_callback, const Red::CString& p_url,
                   const Red::CString& p_body,
                   const Red::Optional<HttpHeaders>& p_headers);
  static void post_form(const HttpCallback& p_callback,
                        const Red::CString& p_url,
                        const Red::DynArray<HttpPair>& p_form,
                        const Red::Optional<HttpHeaders>& p_headers);
  static void put(const HttpCallback& p_callback, const Red::CString& p_url,
                  const Red::CString& p_body,
                  const Red::Optional<HttpHeaders>& p_headers);
  static void put_form(const HttpCallback& p_callback,
                       const Red::CString& p_url,
                       const Red::DynArray<HttpPair>& p_form,
                       const Red::Optional<HttpHeaders>& p_headers);
  static void patch(const HttpCallback& p_callback, const Red::CString& p_url,
                    const Red::CString& p_body,
                    const Red::Optional<HttpHeaders>& p_headers);
  static void patch_form(const HttpCallback& p_callback,
                         const Red::CString& p_url,
                         const Red::DynArray<HttpPair>& p_form,
                         const Red::Optional<HttpHeaders>& p_headers);
  static void delete_(const HttpCallback& p_callback, const Red::CString& p_url,
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
  RTTI_METHOD(put, "Put");
  RTTI_METHOD(put_form, "PutForm");
  RTTI_METHOD(patch, "Patch");
  RTTI_METHOD(patch_form, "PatchForm");
  RTTI_METHOD(delete_, "Delete");
});

#endif  //REDHTTPCLIENT_ASYNCHTTPCLIENT_H
