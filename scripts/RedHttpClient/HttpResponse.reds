public native class HttpResponse {

  public native func GetStatusCode() -> Int32;
  public native func GetHeaders() -> array<HttpHeader>;
  public native func GetText() -> String;
  //public native func GetJson() -> ref<JsonVariant>;
  //public native func GetXml() -> ref<XmlVariant>;

}