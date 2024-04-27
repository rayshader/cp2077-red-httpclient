#ifndef REDHTTPCLIENT_HTTPCALLBACK_HPP
#define REDHTTPCLIENT_HTTPCALLBACK_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

struct HttpCallback {
  Red::WeakHandle<Red::IScriptable> target;
  Red::CName function;
  Red::DynArray<Red::Variant> data;
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPCALLBACK_HPP
