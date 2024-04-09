public native class HttpClient {

  public static native func Get(url: String) -> ref<HttpResponse>;

  public static native func Post(url: String, body: String) -> ref<HttpResponse>;
  public static native func PostForm(url: String, form: array<HttpPair>) -> ref<HttpResponse>;

}