#ifndef REDHTTPCLIENT_HTTPRESPONSE_HPP
#define REDHTTPCLIENT_HTTPRESPONSE_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpStatus.hpp"

namespace RedHttpClient {

class HttpResponse {
 private:
  Red::Handle<Red::IScriptable> wrapper;

 public:
  HttpResponse() = default;

  explicit HttpResponse(Red::Handle<Red::IScriptable> wrapper) : wrapper(std::move(wrapper)) {}

  explicit operator bool() const noexcept { return wrapper; }

  inline [[nodiscard]] HttpStatus GetStatus() const {
    HttpStatus status;

    Red::CallVirtual(wrapper, "GetStatus", status);
    return status;
  }

};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPRESPONSE_HPP
