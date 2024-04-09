#ifndef REDHTTPCLIENT_HTTPHEADER_H
#define REDHTTPCLIENT_HTTPHEADER_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

struct HttpHeader {
  Red::CString name;
  Red::CString value;
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpHeader, {
  RTTI_ALIAS("RedHttpClient.HttpHeader");

  RTTI_PROPERTY(name);
  RTTI_PROPERTY(value);
});

#endif  //REDHTTPCLIENT_HTTPHEADER_H
