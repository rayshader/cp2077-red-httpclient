#ifndef REDHTTPCLIENT_REDHTTPCLIENT_HPP
#define REDHTTPCLIENT_REDHTTPCLIENT_HPP

#include <RedLib.hpp>

#include "src/AsyncHttpClient.hpp"
#include "src/HttpCallback.hpp"
#include "src/HttpClient.hpp"
#include "src/HttpHeader.hpp"
#include "src/HttpMultipart.hpp"
#include "src/HttpPair.hpp"
#include "src/HttpResponse.hpp"
#include "src/HttpStatus.hpp"

namespace RedHttpClient {

inline bool IsDetected() {
  return Red::GetClass("HttpClient") != nullptr;
}

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_REDHTTPCLIENT_HPP
