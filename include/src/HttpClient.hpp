#ifndef REDHTTPCLIENT_HTTPCLIENT_HPP
#define REDHTTPCLIENT_HTTPCLIENT_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#ifdef HAS_REDDATA
#include <RedData.hpp>
#endif

#include "HttpHeader.hpp"
#include "HttpMultipart.hpp"
#include "HttpPair.hpp"
#include "HttpResponse.hpp"

namespace RedHttpClient {

class HttpClient {
 public:
  inline static HttpResponse Get(const Red::CString& url,
                                 const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "Get", handle, url, headers);
    return HttpResponse(handle);
  }

  inline static HttpResponse Post(const Red::CString& url,
                                  const Red::CString& body,
                                  const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "Post", handle, url, body, headers);
    return HttpResponse(handle);
  }

  inline static HttpResponse Post(const Red::CString& url,
                                  const HttpPairs& form,
                                  const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "PostForm", handle, url, form, headers);
    return HttpResponse(handle);
  }

  inline static HttpResponse Post(const Red::CString& url,
                                  const HttpMultipart& form,
                                  const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "PostMultipart", handle, url, form, headers);
    return HttpResponse(handle);
  }

#ifdef HAS_REDDATA
  inline static HttpResponse Post(const Red::CString& url,
                                  const RedData::Json::JsonVariant& body,
                                  const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "PostJson", handle, url, body, headers);
    return HttpResponse(handle);
  }
#endif
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPCLIENT_HPP
