#ifndef REDHTTPCLIENT_HTTPCALLBACK_H
#define REDHTTPCLIENT_HTTPCALLBACK_H

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpResponse.h"

namespace RedHttpClient {

struct HttpCallback {
  Red::WeakHandle<Red::IScriptable> target;
  Red::CName function;
  Red::DynArray<Red::Variant> data;

  void operator()(const Red::Handle<HttpResponse>& p_response) const {
    if (target.Expired()) {
      return;
    }
    if (data.size == 0) {
      Red::CallVirtual(target.Lock(), function, p_response);
    } else {
      Red::CallVirtual(target.Lock(), function, p_response, data);
    }
  }
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpCallback, {
  RTTI_ALIAS("RedHttpClient.HttpCallback");

  RTTI_PROPERTY(target);
  RTTI_PROPERTY(function);
  RTTI_PROPERTY(data);
});

#endif  //REDHTTPCLIENT_HTTPCALLBACK_H
