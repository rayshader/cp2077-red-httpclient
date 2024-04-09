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
    this.ExpectString("POST -> 'Hello world!'", response.GetText(), "Hello world!");
  }

  private cb func Test_PostForm() {
    let form = [
      HttpPair.Create("client", "HttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];
    let response = HttpClient.PostForm("https://postman-echo.com/post", form);

    this.ExpectInt32("POST FORM -> 200 OK", response.GetStatusCode(), 200);
    this.ExpectString("POST FORM -> {client: HttpClient, version: 0.1.0}", response.GetText(), "{client: HttpClient, version: 0.1.0}");
  }

}
