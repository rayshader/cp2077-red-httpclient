#ifndef REDHTTPCLIENT_HTTPPAIR_H
#define REDHTTPCLIENT_HTTPPAIR_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

struct HttpPair {
  Red::CString key;
  Red::CString value;
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpPair, {
  RTTI_ALIAS("RedHttpClient.HttpPair");

  RTTI_PROPERTY(key);
  RTTI_PROPERTY(value);
});

#endif  //REDHTTPCLIENT_HTTPPAIR_H
