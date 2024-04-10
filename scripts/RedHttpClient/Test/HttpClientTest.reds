public class HttpClientTest extends BaseTest {

  public func Init() {
    this.m_modName = "RedHttpClient";
    this.m_name = "HttpClient";
  }

  /// GET ///

  private cb func Test_Get() {
    let response = HttpClient.Get("https://postman-echo.com/get");

    this.ExpectInt32("GET -> 200 OK", response.GetStatusCode(), 200);
  }

  /// POST ///

  private cb func Test_Post() {
    let response = HttpClient.Post("https://postman-echo.com/post", "Hello world!");

    this.ExpectInt32("POST -> 200 OK", response.GetStatusCode(), 200);
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

    this.ExpectInt32("POST FORM -> 200 OK", response.GetStatusCode(), 200);
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

    this.ExpectInt32("POST JSON -> 200 OK", response.GetStatusCode(), 200);
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
