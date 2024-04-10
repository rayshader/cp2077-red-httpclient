public native class HttpClient {

  public static native func Get(url: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  public static native func Post(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PostForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData"))
  public static func PostJson(url: String, body: ref<JsonVariant>) -> ref<HttpResponse> {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    return HttpClient.Post(url, body.ToString(), headers);
  }

  public static native func Put(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PutForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData"))
  public static func PutJson(url: String, body: ref<JsonVariant>) -> ref<HttpResponse> {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    return HttpClient.Put(url, body.ToString(), headers);
  }

  public static native func Patch(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PatchForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData"))
  public static func PatchJson(url: String, body: ref<JsonVariant>) -> ref<HttpResponse> {
    let headers: array<HttpHeader> = [
      HttpHeader.Create("Content-Type", "application/json; charset=utf-8")
    ];

    return HttpClient.Patch(url, body.ToString(), headers);
  }

  public static native func Delete(url: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

}