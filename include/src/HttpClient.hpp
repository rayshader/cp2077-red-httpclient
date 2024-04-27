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

#ifdef HAS_REDDATA
template <class T>
concept is_body_allowed =
  std::is_same_v<T, Red::CString> || std::is_same_v<T, HttpPairs> ||
  std::is_same_v<T, HttpMultipart> || RedData::Json::JsonVariant;
#else
template <class T>
concept is_body_allowed =
  std::is_same_v<T, Red::CString> || std::is_same_v<T, HttpPairs> ||
  std::is_same_v<T, HttpMultipart>;
#endif

class HttpClient {
 public:
  inline static HttpResponse Get(const Red::CString& url,
                                 const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "Get", handle, url, headers);
    return HttpResponse(handle);
  }

  template <class T>
    requires is_body_allowed<T>
  inline static HttpResponse Post(const Red::CString& url, const T& body,
                                  const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("HttpClient", "Post", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("HttpClient", "PostForm", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("HttpClient", "PostMultipart", handle, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("HttpClient", "PostJson", handle, url, body.GetHandle(),
                      headers);
    }
#endif
    return HttpResponse(handle);
  }

  template <class T>
    requires is_body_allowed<T>
  inline static HttpResponse Put(const Red::CString& url, const T& body,
                                 const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("HttpClient", "Put", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("HttpClient", "PutForm", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("HttpClient", "PutMultipart", handle, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("HttpClient", "PutJson", handle, url, body.GetHandle(),
                      headers);
    }
#endif
    return HttpResponse(handle);
  }

  template <class T>
    requires is_body_allowed<T>
  inline static HttpResponse Patch(const Red::CString& url, const T& body,
                                   const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("HttpClient", "Patch", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("HttpClient", "PatchForm", handle, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("HttpClient", "PatchMultipart", handle, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("HttpClient", "PatchJson", handle, url, body.GetHandle(),
                      headers);
    }
#endif
    return HttpResponse(handle);
  }

  inline static HttpResponse Delete(const Red::CString& url,
                                    const HttpHeaders& headers = {}) {
    Red::Handle<Red::IScriptable> handle;

    Red::CallStatic("HttpClient", "Delete", handle, url, headers);
    return HttpResponse(handle);
  }
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPCLIENT_HPP
