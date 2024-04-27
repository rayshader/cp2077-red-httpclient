#ifndef REDHTTPCLIENT_HTTPMULTIPART_HPP
#define REDHTTPCLIENT_HTTPMULTIPART_HPP

#include <RED4ext/RED4ext.hpp>
#include <RedLib.hpp>

namespace RedHttpClient {

class HttpMultipart {
 private:
  Red::Handle<Red::IScriptable> wrapper;

 public:
  HttpMultipart() {
    wrapper = Red::MakeScriptedHandle("RedHttpClient.HttpMultipart");
  }

  explicit HttpMultipart(Red::Handle<Red::IScriptable> wrapper)
      : wrapper(std::move(wrapper)) {}

  explicit operator bool() const noexcept { return wrapper; }

  inline void AddPart(const Red::CString& name,
                      const Red::CString& value) const {
    Red::CallVirtual(wrapper, "AddPart", name, value);
  }

  inline void SetPart(const Red::CString& name,
                      const Red::CString& value) const {
    Red::CallVirtual(wrapper, "SetPart", name, value);
  }

  inline Red::CString GetPart(const Red::CString& name) const {
    Red::CString value;

    Red::CallVirtual(wrapper, "GetPart", value, name);
    return value;
  }
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_HTTPMULTIPART_HPP
