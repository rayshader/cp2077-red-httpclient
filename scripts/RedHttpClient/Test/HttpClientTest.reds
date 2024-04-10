public class HttpClientTest extends BaseTest {

  public func Init() {
    this.m_modName = "RedHttpClient";
    this.m_name = "HttpClient";
  }

  /// HttpResponse ///

  private cb func Test_HasHeader() {
    let response = HttpClient.Get("https://postman-echo.com/get");

    this.ExpectBool("GET -> Header 'Content-Type' is present", response.HasHeader("Content-Type"), true);
    this.ExpectBool("GET -> Header 'X-Unknown' is not present", response.HasHeader("X-Unknown"), false);
  }

  private cb func Test_GetHeader() {
    let response = HttpClient.Get("https://postman-echo.com/get");
    let contentType = "application/json; charset=utf-8";

    this.ExpectString(s"GET -> Header 'Content-Type' == '\(contentType)'", response.GetHeader("Content-Type"), contentType);
    this.ExpectString("GET -> Header 'X-Unknown' == ''", response.GetHeader("X-Unknown"), "");
  }

  /// GET ///

  private cb func Test_Get() {
    let response = HttpClient.Get("https://postman-echo.com/get");

    this.ExpectInt32("GET -> 200 OK", response.GetStatusCode(), 200);
    this.ExpectString("GET -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
  }

  private cb func Test_Get_NotFound() {
    let response = HttpClient.Get("https://postman-echo.com/get_404");

    this.ExpectInt32("GET -> 404 Not Found", response.GetStatusCode(), 404);
    this.ExpectString("GET -> HttpStatus.NotFound", s"\(response.GetStatus())", s"\(HttpStatus.NotFound)");
  }

  /// POST ///

  private cb func Test_Post() {
    let response = HttpClient.Post("https://postman-echo.com/post", "Hello world!");

    this.ExpectString("POST -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("POST -> 'Hello world!'", data, "Hello world!");
  }

  private cb func Test_PostForm() {
    let form = [
      HttpPair.Create("client", "HttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];
    let response = HttpClient.PostForm("https://postman-echo.com/post", form);

    this.ExpectString("POST FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("POST FORM -> $.client == 'HttpClient'", jsonForm.GetKeyString("client"), "HttpClient");
    this.ExpectString("POST FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
  }

  private cb func Test_PostJson() {
    let json = ParseJson("{\"client\": \"HttpClient\", \"version\": 42, \"items\": []}");
    let response = HttpClient.PostJson("https://postman-echo.com/post", json);

    this.ExpectString("POST JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("POST JSON -> $.client == 'HttpClient'", json.GetKeyString("client"), "HttpClient");
    this.ExpectInt64("POST JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("POST JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("POST JSON -> $.items.length == 0", items.GetSize(), 0u);
  }

}
