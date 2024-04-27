#ifndef REDHTTPCLIENT_HTTPMULTIPART_H
#define REDHTTPCLIENT_HTTPMULTIPART_H

#include <cpr/multipart.h>
#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

#include "HttpPair.h"

namespace RedHttpClient {

class HttpMultipart : public Red::IScriptable {
 private:
  cpr::Multipart multipart;

 public:
  HttpMultipart() : multipart({}) {}

  [[nodiscard]] cpr::Multipart get() const { return multipart; }

  void add_part(const Red::CString& p_name, const Red::CString& p_value) {
    multipart.parts.emplace_back(p_name.c_str(), p_value.c_str());
  }

  void set_part(const Red::CString& p_name, const Red::CString& p_value) {
    for (auto& part : multipart.parts) {
      if (part.name == p_name.c_str()) {
        part.value = p_value.c_str();
        return;
      }
    }
    multipart.parts.emplace_back(p_name.c_str(), p_value.c_str());
  }

  [[nodiscard]] Red::CString get_part(const Red::CString& p_name) const {
    for (const auto& part : multipart.parts) {
      if (part.name == p_name.c_str()) {
        return part.value;
      }
    }
    return {};
  }

  RTTI_IMPL_TYPEINFO(RedHttpClient::HttpMultipart);
  RTTI_IMPL_ALLOCATOR();
};

}  // namespace RedHttpClient

RTTI_DEFINE_CLASS(RedHttpClient::HttpMultipart, {
  RTTI_ALIAS("RedHttpClient.HttpMultipart");

  RTTI_METHOD(add_part, "AddPart");
  RTTI_METHOD(set_part, "SetPart");
  RTTI_METHOD(get_part, "GetPart");
});

#endif  //REDHTTPCLIENT_HTTPMULTIPART_H
