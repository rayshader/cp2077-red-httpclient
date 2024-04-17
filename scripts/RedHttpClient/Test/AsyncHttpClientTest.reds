import RedData.Json.*
import RedHttpClient.*

public class AsyncHttpClientTest extends BaseTest {

  public func Init() {
    this.m_modName = "RedHttpClient";
    this.m_name = "AsyncHttpClient";
    this.m_isAsync = true;
  }

  /// GET ///

  private cb func Test_Get(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Get", [done]);

    AsyncHttpClient.Get(callback, "https://postman-echo.com/get");
  }

  private cb func Async_Get(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectInt32("GET -> 200 OK", response.GetStatusCode(), 200);
    this.ExpectString("GET -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  private cb func Test_Get_NotFound(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Get_NotFound", [done]);

    AsyncHttpClient.Get(callback, "https://postman-echo.com/get_404");
  }

  private cb func Async_Get_NotFound(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectInt32("GET -> 404 Not Found", response.GetStatusCode(), 404);
    this.ExpectString("GET -> HttpStatus.NotFound", s"\(response.GetStatus())", s"\(HttpStatus.NotFound)");
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  private cb func Test_Get_WithoutSSL(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Get_WithoutSSL", [done]);

    AsyncHttpClient.Get(callback, "http://postman-echo.com/get");
  }

  private cb func Async_Get_WithoutSSL(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectBool("GET without SSL -> no response", IsDefined(response), false);
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  /// POST ///

  private cb func Test_Post(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Post", [done]);

    AsyncHttpClient.Post(callback, "https://postman-echo.com/post", "Hello world!");
  }

  private cb func Async_Post(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("POST -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("POST -> 'Hello world!'", data, "Hello world!");
    done.Call();
  }

  private cb func Test_PostForm(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PostForm", [done]);
    let form = [
      HttpPair.Create("client", "AsyncHttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];

    AsyncHttpClient.PostForm(callback, "https://postman-echo.com/post", form);
  }

  private cb func Async_PostForm(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("POST FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("POST FORM -> $.client == 'AsyncHttpClient'", jsonForm.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectString("POST FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
      done.Call();
  }

  private cb func Test_PostJson(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PostJson", [done]);
    let json = ParseJson("{\"client\": \"AsyncHttpClient\", \"version\": 42, \"items\": []}");

    AsyncHttpClient.PostJson(callback, "https://postman-echo.com/post", json);
  }

  private cb func Async_PostJson(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("POST JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("POST JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("POST JSON -> $.client == 'AsyncHttpClient'", json.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectInt64("POST JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("POST JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("POST JSON -> $.items.length == 0", items.GetSize(), 0u);
    done.Call();
  }

  private cb func Test_Post_WithoutSSL(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Post_WithoutSSL", [done]);

    AsyncHttpClient.Post(callback, "http://postman-echo.com/post", "NotSafe");
  }

  private cb func Async_Post_WithoutSSL(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectBool("POST without SSL -> no response", IsDefined(response), false);
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  /// PUT ///

  private cb func Test_Put(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Put", [done]);

    AsyncHttpClient.Put(callback, "https://postman-echo.com/put", "Hello world!");
  }

  private cb func Async_Put(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PUT -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("PUT -> 'Hello world!'", data, "Hello world!");
    done.Call();
  }

  private cb func Test_PutForm(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PutForm", [done]);
    let form = [
      HttpPair.Create("client", "AsyncHttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];

    AsyncHttpClient.PutForm(callback, "https://postman-echo.com/put", form);
  }

  private cb func Async_PutForm(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PUT FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("PUT FORM -> $.client == 'AsyncHttpClient'", jsonForm.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectString("PUT FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
      done.Call();
  }

  private cb func Test_PutJson(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PutJson", [done]);
    let json = ParseJson("{\"client\": \"AsyncHttpClient\", \"version\": 42, \"items\": []}");

    AsyncHttpClient.PutJson(callback, "https://postman-echo.com/put", json);
  }

  private cb func Async_PutJson(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PUT JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PUT JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("PUT JSON -> $.client == 'AsyncHttpClient'", json.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectInt64("PUT JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("PUT JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("PUT JSON -> $.items.length == 0", items.GetSize(), 0u);
    done.Call();
  }

  private cb func Test_Put_WithoutSSL(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Put_WithoutSSL", [done]);

    AsyncHttpClient.Put(callback, "http://postman-echo.com/put", "NotSafe");
  }

  private cb func Async_Put_WithoutSSL(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectBool("PUT without SSL -> no response", IsDefined(response), false);
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  /// PATCH ///

  private cb func Test_Patch(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Patch", [done]);

    AsyncHttpClient.Patch(callback, "https://postman-echo.com/patch", "Hello world!");
  }

  private cb func Async_Patch(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PATCH -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectString("PATCH -> 'Hello world!'", data, "Hello world!");
    done.Call();
  }

  private cb func Test_PatchForm(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PatchForm", [done]);
    let form = [
      HttpPair.Create("client", "AsyncHttpClient"),
      HttpPair.Create("version", "0.1.0")
    ];

    AsyncHttpClient.PatchForm(callback, "https://postman-echo.com/patch", form);
  }

  private cb func Async_PatchForm(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PATCH FORM -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH FORM -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let jsonForm = json.GetKey("form") as JsonObject;

    this.ExpectString("PATCH FORM -> $.client == 'AsyncHttpClient'", jsonForm.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectString("PATCH FORM -> $.version == '0.1.0'", jsonForm.GetKeyString("version"), "0.1.0");
      done.Call();
  }

  private cb func Test_PatchJson(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_PatchJson", [done]);
    let json = ParseJson("{\"client\": \"AsyncHttpClient\", \"version\": 42, \"items\": []}");

    AsyncHttpClient.PatchJson(callback, "https://postman-echo.com/patch", json);
  }

  private cb func Async_PatchJson(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("PATCH JSON -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("PATCH JSON -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    json = json.GetKey("json") as JsonObject;
    this.ExpectString("PATCH JSON -> $.client == 'AsyncHttpClient'", json.GetKeyString("client"), "AsyncHttpClient");
    this.ExpectInt64("PATCH JSON -> $.version == 42", json.GetKeyInt64("version"), 42l);
    let items = json.GetKey("items") as JsonArray;

    this.ExpectBool("PATCH JSON -> $.items === [...]", items.IsArray(), true);
    this.ExpectUint32("PATCH JSON -> $.items.length == 0", items.GetSize(), 0u);
    done.Call();
  }

  private cb func Test_Patch_WithoutSSL(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Patch_WithoutSSL", [done]);

    AsyncHttpClient.Patch(callback, "http://postman-echo.com/patch", "NotSafe");
  }

  private cb func Async_Patch_WithoutSSL(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectBool("PATCH without SSL -> no response", IsDefined(response), false);
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

  /// DELETE ///

  private cb func Test_Delete(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Delete", [done]);

    AsyncHttpClient.Delete(callback, "https://postman-echo.com/delete");
  }

  private cb func Async_Delete(response: ref<HttpResponse>, data: array<Variant>) {
    let done: ref<CallbackTest> = FromVariant(data[0]);

    this.ExpectString("DELETE -> HttpStatus.OK", s"\(response.GetStatus())", s"\(HttpStatus.OK)");
    let json = response.GetJson() as JsonObject;

    if !this.ExpectBool("DELETE -> application/json", IsDefined(json), true) {
      LogChannel(n"Error", "Response Json format invalid");
      done.Call();
      return;
    }
    let data = json.GetKeyString("data");

    this.ExpectInt32("DELETE -> <empty>", StrLen(data), 0);
    done.Call();
  }

  private cb func Test_Delete_WithoutSSL(done: ref<CallbackTest>) {
    let callback = HttpCallback.Create(this, n"Async_Delete_WithoutSSL", [done]);

    AsyncHttpClient.Delete(callback, "http://postman-echo.com/delete");
  }

  private cb func Async_Delete_WithoutSSL(response: ref<HttpResponse>, data: array<Variant>) {
    this.ExpectBool("DELETE without SSL -> no response", IsDefined(response), false);
    let done: ref<CallbackTest> = FromVariant(data[0]);

    done.Call();
  }

}
