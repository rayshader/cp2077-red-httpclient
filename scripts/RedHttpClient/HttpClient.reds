public native class HttpClient {

  public static native func Get(url: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  public static native func Post(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
  public static native func PostForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;

  @if(ModuleExists("RedData"))
  public static func PostJson(url: String, body: ref<JsonVariant>) -> ref<HttpResponse> {
    let headers: array<HttpHeader> = [];

    ArrayPush(headers, HttpHeader.Create("Content-Type", "application/json; charset=utf-8"));
    return HttpClient.Post(url, body.ToString(), headers);
  }

}