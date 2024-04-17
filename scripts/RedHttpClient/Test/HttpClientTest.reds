import RedData.Json.*
import RedHttpClient.*

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

  /// SSL ///

  private cb func Test_WithoutSSL() {
    let response = HttpClient.Get("http://postman-echo.com/get");

    this.ExpectBool("GET without SSL -> no response", IsDefined(response), false);
    response = HttpClient.Post("http://postman-echo.com/post", "Not safe");

    this.ExpectBool("POST without SSL -> no response", IsDefined(response), false);
    let form = [
      HttpPair.Create("ssl", "false"),
      HttpPair.Create("response", "null")
    ];
    response = HttpClient.PostForm("http://postman-echo.com/post", form);

    this.ExpectBool("POST FORM without SSL -> no response", IsDefined(response), false);
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

  /// PUT ///

  private cb func Test_Put() {
    let response = HttpClient.Put("https://postman-echo.com/put", "Hello world!");

    this.ExpectString("PUT -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("PUT -> 'Hello world!'", data, "Hello world!");
  }

  private cb func Test_PutForm() {
    let form = [
      HttpPair.Create("client", "HttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];
    let response = HttpClient.PutForm("https://postman-echo.com/put", form);

    this.ExpectString("PUT FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("PUT FORM -> $.client == 'HttpClient'", jsonForm.GetKeyString("client"), "HttpClient");
    this.ExpectString("PUT FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
  }

  private cb func Test_PutJson() {
    let json = ParseJson("{\"client\": \"HttpClient\", \"version\": 42, \"items\": []}");
    let response = HttpClient.PutJson("https://postman-echo.com/put", json);

    this.ExpectString("PUT JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("PUT JSON -> $.client == 'HttpClient'", json.GetKeyString("client"), "HttpClient");
    this.ExpectInt64("PUT JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("PUT JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("PUT JSON -> $.items.length == 0", items.GetSize(), 0u);
  }

  /// PATCH ///

  private cb func Test_Patch() {
    let response = HttpClient.Patch("https://postman-echo.com/patch", "Hello world!");

    this.ExpectString("PATCH -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("PATCH -> 'Hello world!'", data, "Hello world!");
  }

  private cb func Test_PatchForm() {
    let form = [
      HttpPair.Create("client", "HttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];
    let response = HttpClient.PatchForm("https://postman-echo.com/patch", form);

    this.ExpectString("PATCH FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("PATCH FORM -> $.client == 'HttpClient'", jsonForm.GetKeyString("client"), "HttpClient");
    this.ExpectString("PATCH FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
  }

  private cb func Test_PatchJson() {
    let json = ParseJson("{\"client\": \"HttpClient\", \"version\": 42, \"items\": []}");
    let response = HttpClient.PatchJson("https://postman-echo.com/patch", json);

    this.ExpectString("PATCH JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("PATCH JSON -> $.client == 'HttpClient'", json.GetKeyString("client"), "HttpClient");
    this.ExpectInt64("PATCH JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("PATCH JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("PATCH JSON -> $.items.length == 0", items.GetSize(), 0u);
  }

  /// DELETE ///

  private cb func Test_Delete() {
    let response = HttpClient.Delete("https://postman-echo.com/delete");

    this.ExpectString("DELETE -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("DELETE -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectInt32("DELETE -> <empty>", StrLen(data), 0);
  }

}
