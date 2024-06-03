public native class AsyncHttpClient {

  public static native func Get(callback: HttpCallback, url: String, opt headers: array<HttpHeader>) -> Void;

  public static native func Post(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PostForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
  public static native func PostMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData.Json"))
  public static func PostJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    AsyncHttpClient.Post(callback, url, body.ToString(), requestHeaders);
  }

  public static native func Put(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PutForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
  public static native func PutMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData.Json"))
  public static func PutJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    AsyncHttpClient.Put(callback, url, body.ToString(), requestHeaders);
  }

  public static native func Patch(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PatchForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
  public static native func PatchMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData.Json"))
  public static func PatchJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void {
    let requestHeaders: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    for header in headers {
      if StrCmp(header.name, "Content-Type", -1, true) != 0 {
        ArrayPush(requestHeaders, header);
      }
    }
    AsyncHttpClient.Patch(callback, url, body.ToString(), requestHeaders);
  }

  public static native func Delete(callback: HttpCallback, url: String, opt headers: array<HttpHeader>) -> Void;

}