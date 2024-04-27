#ifndef REDHTTPCLIENT_HTTPRESPONSE_HPP
#define REDHTTPCLIENT_HTTPRESPONSE_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#ifdef HAS_REDDATA
#include <RedData.hpp>
#endif

#include "HttpStatus.hpp"

namespace RedHttpClient {

class HttpResponse {
 private:
  Red::Handle<Red::IScriptable> wrapper;

 public:
  HttpResponse() = default;

  explicit HttpResponse(Red::Handle<Red::IScriptable> wrapper) : wrapper(std::move(wrapper)) {}

  explicit operator bool() const noexcept { return wrapper; }

  inline HttpStatus GetStatus() const {
    HttpStatus status;

    Red::CallVirtual(wrapper, "GetStatus", status);
    return status;
  }

  inline int32_t GetStatusCode() const {
    int32_t statusCode = -1;

    Red::CallVirtual(wrapper, "GetStatusCode", statusCode);
    return statusCode;
  }

  inline HttpHeaders GetHeaders() const {
    HttpHeaders headers;

    Red::CallVirtual(wrapper, "GetHeaders", headers);
    return headers;
  }

  inline bool HasHeader(const Red::CString& name) const {
    bool isPresent = false;

    Red::CallVirtual(wrapper, "HasHeader", isPresent, name);
    return isPresent;
  }

  inline Red::CString GetHeader(const Red::CString& name) const {
    Red::CString value;

    Red::CallVirtual(wrapper, "GetHeader", value, name);
    return value;
  }

  inline Red::CString GetText() const {
    Red::CString body;

    Red::CallVirtual(wrapper, "GetText", body);
    return body;
  }

#ifdef HAS_REDDATA
  inline RedData::Json::JsonVariant GetJson() const {
    Red::Handle<Red::IScriptable> handle;

    Red::CallVirtual(wrapper, "GetJson", handle);
    return RedData::Json::JsonVariant(handle);
  }
#endif

};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPRESPONSE_HPP
