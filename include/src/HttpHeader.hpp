#ifndef REDHTTPCLIENT_HTTPHEADER_HPP
#define REDHTTPCLIENT_HTTPHEADER_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

struct HttpHeader {
  Red::CString name;
  Red::CString value;
};

using HttpHeaders = Red::DynArray<HttpHeader>;

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPHEADER_HPP
