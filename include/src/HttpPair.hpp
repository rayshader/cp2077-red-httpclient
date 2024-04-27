#ifndef REDHTTPCLIENT_HTTPPAIR_HPP
#define REDHTTPCLIENT_HTTPPAIR_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

struct HttpPair {
  Red::CString key;
  Red::CString value;
};

using HttpPairs = Red::DynArray<HttpPair>;

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPPAIR_HPP
