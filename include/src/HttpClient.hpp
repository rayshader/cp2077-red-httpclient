#ifndef REDHTTPCLIENT_HTTPCLIENT_HPP
#define REDHTTPCLIENT_HTTPCLIENT_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpHeader.hpp"
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
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPCLIENT_HPP
