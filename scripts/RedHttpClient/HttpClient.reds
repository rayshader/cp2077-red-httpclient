module RedHttpClient

@if(ModuleExists("RedData.Json"))
import RedData.Json.*

public native class HttpClient {

  public static native func Get(url: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  public static native func Post(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PostForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PostMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData.Json"))
  public static func PostJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse> {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    return HttpClient.Post(url, body.ToString(), requestHeaders);
  }

  public static native func Put(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PutForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PutMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData.Json"))
  public static func PutJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse> {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    return HttpClient.Put(url, body.ToString(), requestHeaders);
  }

  public static native func Patch(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PatchForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PatchMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData.Json"))
  public static func PatchJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse> {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    return HttpClient.Patch(url, body.ToString(), requestHeaders);
  }

  public static native func Delete(url: String, opt body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func DeleteForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func DeleteMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData.Json"))
  public static func DeleteJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse> {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    return HttpClient.Delete(url, body.ToString(), requestHeaders);
  }

}