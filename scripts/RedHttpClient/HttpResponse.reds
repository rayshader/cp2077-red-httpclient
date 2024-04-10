public native class HttpResponse {

  public native func GetStatus() -> HttpStatus;
  public native func GetStatusCode() -> Int32;

  public native func GetHeaders() -> array<HttpHeader>;
  public native func HasHeader(header: String) -> Bool;
  public native func GetHeader(header: String) -> String;

  public native func GetText() -> String;

  @if(ModuleExists("RedData"))
  public func GetJson() -> ref<JsonVariant> {
    return ParseJson(this.GetText());
  }

}