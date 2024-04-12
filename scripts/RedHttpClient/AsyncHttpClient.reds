public native class AsyncHttpClient {

  public static native func Get(callback: HttpCallback, url: String, opt headers: array<HttpHeader>) -> Void;

  public static native func Post(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PostForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData"))
  public static func PostJson(callback: HttpCallback, url: String, body: ref<JsonVariant>) -> Void {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    AsyncHttpClient.Post(callback, url, body.ToString(), headers);
  }

  public static native func Put(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PutForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData"))
  public static func PutJson(callback: HttpCallback, url: String, body: ref<JsonVariant>) -> Void {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    AsyncHttpClient.Put(callback, url, body.ToString(), headers);
  }

  public static native func Patch(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
  public static native func PatchForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;

  @if(ModuleExists("RedData"))
  public static func PatchJson(callback: HttpCallback, url: String, body: ref<JsonVariant>) -> Void {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    AsyncHttpClient.Patch(callback, url, body.ToString(), headers);
  }

  public static native func Delete(callback: HttpCallback, url: String, opt headers: array<HttpHeader>) -> Void;

}