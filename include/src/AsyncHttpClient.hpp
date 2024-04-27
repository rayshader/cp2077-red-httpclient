#ifndef REDHTTPCLIENT_ASYNCHTTPCLIENT_HPP
#define REDHTTPCLIENT_ASYNCHTTPCLIENT_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#ifdef HAS_REDDATA
#include <RedData.hpp>
#endif

#include "HttpHeader.hpp"
#include "HttpMultipart.hpp"
#include "HttpCallback.hpp"
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

class AsyncHttpClient {
 public:
  inline static void Get(const HttpCallback& callback, const Red::CString& url,
                         const HttpHeaders& headers = {}) {
    Red::CallStatic("AsyncHttpClient", "Get", callback, url, headers);
  }

  template <class T>
    requires is_body_allowed<T>
  inline static void Post(const HttpCallback& callback, const Red::CString& url,
                          const T& body, const HttpHeaders& headers = {}) {
    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("AsyncHttpClient", "Post", callback, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("AsyncHttpClient", "PostForm", callback, url, body,
                      headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("AsyncHttpClient", "PostMultipart", callback, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("AsyncHttpClient", "PostJson", callback, url,
                      body.GetHandle(), headers);
    }
#endif
  }

  template <class T>
    requires is_body_allowed<T>
  inline static void Put(const HttpCallback& callback, const Red::CString& url,
                         const T& body, const HttpHeaders& headers = {}) {
    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("AsyncHttpClient", "Put", callback, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("AsyncHttpClient", "PutForm", callback, url, body,
                      headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("AsyncHttpClient", "PutMultipart", callback, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("AsyncHttpClient", "PutJson", callback, url,
                      body.GetHandle(), headers);
    }
#endif
  }

  template <class T>
    requires is_body_allowed<T>
  inline static void Patch(const HttpCallback& callback,
                           const Red::CString& url, const T& body,
                           const HttpHeaders& headers = {}) {
    if constexpr (std::is_same_v<T, Red::CString>) {
      Red::CallStatic("AsyncHttpClient", "Patch", callback, url, body, headers);
    } else if constexpr (std::is_same_v<T, HttpPairs>) {
      Red::CallStatic("AsyncHttpClient", "PatchForm", callback, url, body,
                      headers);
    } else if constexpr (std::is_same_v<T, HttpMultipart>) {
      Red::CallStatic("AsyncHttpClient", "PatchMultipart", callback, url,
                      body.GetHandle(), headers);
    }
#ifdef HAS_REDDATA
    else if constexpr (std::is_same_v<T, RedData::Json::JsonVariant>) {
      Red::CallStatic("AsyncHttpClient", "PatchJson", callback, url,
                      body.GetHandle(), headers);
    }
#endif
  }

  inline static void Delete(const HttpCallback& callback,
                            const Red::CString& url,
                            const HttpHeaders& headers = {}) {
    Red::CallStatic("AsyncHttpClient", "Delete", callback, url, headers);
  }
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_ASYNCHTTPCLIENT_HPP
