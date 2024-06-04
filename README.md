# Red Http Client
![Cyberpunk 2077](https://img.shields.io/badge/Cyberpunk%202077-v2.12a-blue)
![GitHub License](https://img.shields.io/github/license/rayshader/cp2077-red-httpclient)
[![Donate](https://img.shields.io/badge/donate-buy%20me%20a%20coffee-yellow)](https://www.buymeacoffee.com/lpfreelance)

This plugin allows to send HTTP requests. It can be used with Redscript and 
CET.

# Getting started

## Compatibility
- Cyberpunk 2077 v2.12a
- [Redscript] 0.5.19+
- [Cyber Engine Tweaks] 1.32.2+

## Installation
1. Install requirements:
  - [RED4ext] v1.24.3+
  - [RedData] v0.4.0+
  - [RedFileSystem] v0.8.0+ is recommended
2. Extract the [latest archive] into the Cyberpunk 2077 directory.

## Usage

It logs all requests and responses by default, in 
`red4ext/logs/redhttpclient-YYYY-MM-DD-HH-mm-ss.log`. Logging can be disabled  
in file `red4ext/plugins/RedFileSystem/storages/RedHttpClient/config.json`.
User need to change value of `logging` to `false`. File is created after 
running the game when it isn't found.

All features are defined in module `RedHttpClient`. You need to import it with:
```swift
import RedHttpClient.*
import RedData.Json.* // When using Json from RedData.
```

You can find examples for both Redscript and Lua (CET) in [examples/].

### HttpResponse
```swift
GetStatus() -> HttpStatus;
GetStatusCode() -> Int32;

GetHeaders() -> array<HttpHeader>;
HasHeader(header: String) -> Bool;
GetHeader(header: String) -> String;

GetText() -> String;
GetJson() -> ref<JsonVariant>; // only with RedData.Json
```

After sending an HTTP request, you should receive a `HttpResponse` whether 
you're using `HttpClient` or `AsyncHttpClient` (see after).

```swift
// Suppose HTTP response from server is something like:
// GET / 200 OK
// Content-Type: text/plain
// 
// Hello world!
let response: ref<HttpResponse>;

LogChannel(n"Info", s"Status: \(response.GetStatus())");
LogChannel(n"Info", s"Status code: \(response.GetStatusCode())");
LogChannel(n"Info", s"Headers: \(ArraySize(response.GetHeaders()))");
LogChannel(n"Info", s"  Content-Type: \(response.HasHeader("Content-Type"))");
LogChannel(n"Info", s"  Content-Type: '\(response.GetHeader("Content-Type"))'");
LogChannel(n"Info", s"Text: '\(response.GetText())'");
LogChannel(n"Info", s"Is Json: \(IsDefined(response.GetJson()))");

// It should log the following:
// Status: OK
// Status code: 200
// Headers: 1
//   Content-Type: true
//   Content-Type: 'text/plain'
// Text: 'Hello world!'
// Is Json: false
```

### HttpStatus

A list of HTTP status codes is defined in enum `HttpStatus`. You can look at 
all values in [definition](https://github.com/rayshader/cp2077-red-httpclient/blob/master/scripts/RedHttpClient/HttpStatus.reds).

### HttpClient

Send HTTP requests using HTTP methods: `GET`, `POST`, `PUT`, `PATCH` and 
`DELETE`. All requests must be safe and executed through SSL. Therefore `url` 
must always start with `https://`. If you send an unsafe request with url 
`http://`, response will be `null`. This plugin requires at least TLS v1.2 
when communicating with servers.

`HttpClient` run requests in blocking mode. It blocks the current thread until 
a response is received. You should be careful when using it. If you're not 
sure, always use `AsyncHttpClient` instead.

> [!TIP]  
> Don't jump to *AsyncHttpClient* right now. Features are similar between both 
> clients. You'll find useful information below to use with *AsyncHttpClient*.

#### GET
```swift
Get(url: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
```

You can define headers like this:
```swift
let headers: array<HttpHeader> = [
  HttpHeader.Create("Authorization", "Bearer <token>")
];
```

#### POST
```swift
Post(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PostForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PostMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PostJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
```
Use `Post` to send body data as `text/plain` (default).

Use `PostForm` to send a list of key/value with:
- Content-Type: `application/x-www-form-urlencoded`
- Body: `key1=value1&key2=value2[...]`

You can define keys/values of a form like this:
```swift
let form = [
  HttpPair.Create("key1", "value1"),
  HttpPair.Create("key2", "value2")
];
```

Use `PostMultipart` to send a multipart form with:
- Content-Type: `multipart/form-data`
- Body: &lt;multipart data&gt;

You can add / set / get parts of a form like this:
```swift
let form: ref<HttpMultipart> = new HttpMultipart();

form.AddPart("name1", "value1");    // Add new part
form.SetPart("name1", "newvalue1"); // Replace value of name1
form.SetPart("name2", "value2");    // Add new part too
let value = form.GetPart("name2");  // value == "value2"
```

Use `PostJson` to send Json data with:
- Content-Type: `application/json; charset=utf-8`
- Body: &lt;Json data&gt;

Methods below use the same signature for `[Method]Form`, `[Method]Multipart` 
and `[Method]Json`.

#### PUT
```swift
Put(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PutForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PutMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PutJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
```

#### PATCH
```swift
Patch(url: String, body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PatchForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PatchMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
PatchJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
```

#### DELETE
```swift
Delete(url: String, opt body: String, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
DeleteForm(url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
DeleteMultipart(url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
DeleteJson(url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> ref<HttpResponse>;
```

### AsyncHttpClient

Send asynchronous HTTP requests using HTTP methods: `GET`, `POST`, `PUT`, 
`PATCH` and `DELETE`. 

`AsyncHttpClient` run requests in background using a `JobQueue`. This will not 
block the current thread. This is the best way to send requests and should be 
used instead of `HttpClient`. This uses the same rules described for 
*HttpClient*.

Unlike `HttpClient`, you need to provide a `HttpCallback`. It will be used to 
execute your function when a `HttpResponse` is ready.

### HttpCallback

You can target which object and function to execute when a response is ready. 
You can also provide additional data to transfer when consuming the response. 
Last argument `data` is optional, with type `array<Variant>` (see [Redscript Wiki]).
```swift
public class YourClass {
  // ...

  public func YourFunction() {
    let callback: HttpCallback = HttpCallback.Create(this, n"YourResponse", ["Hello", 42]);

    AsyncHttpClient.Get(callback, "https://httpbin.org/get");
  }

  private cb func YourResponse(response: ref<HttpResponse>, data: array<Variant>) {
    let arg0: String = FromVariant(data[0]); // == "Hello"
    let arg1: Int32 = FromVariant(data[1]); // == 42

    // Use response and additional data...
  }

  // ...
}
```

All functions are identical to `HttpClient`, except they all starts with a 
`callback` argument and return nothing:

#### GET
```swift
Get(callback: HttpCallback, url: String, opt headers: array<HttpHeader>) -> Void;
```

#### POST
```swift
Post(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
PostForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
PostMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;
PostJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void;
```

#### PUT
```swift
Put(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
PutForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
PutMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;
PutJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void;
```

#### PATCH
```swift
Patch(callback: HttpCallback, url: String, body: String, opt headers: array<HttpHeader>) -> Void;
PatchForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
PatchMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;
PatchJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void;
```

#### DELETE
```swift
Delete(callback: HttpCallback, url: String, opt body: String, opt headers: array<HttpHeader>) -> Void;
DeleteForm(callback: HttpCallback, url: String, form: array<HttpPair>, opt headers: array<HttpHeader>) -> Void;
DeleteMultipart(callback: HttpCallback, url: String, form: ref<HttpMultipart>, opt headers: array<HttpHeader>) -> Void;
DeleteJson(callback: HttpCallback, url: String, body: ref<JsonVariant>, opt headers: array<HttpHeader>) -> Void;
```

# Development
Contributions are welcome, feel free to fill an issue or a PR.

## Usage
1. Install requirements:
  - CMake v3.27+
  - Visual Studio Community 2022+
  - Node JS v20.11+
    - run `npm install --save-dev archiver`
2. Configure project with:
```shell
cmake -G "Visual Studio 17 2022" -A x64 -DBUILD_SHARED_LIBS:BOOL=OFF -S . -B build
```

`BUILD_SHARED_LIBS` is required to avoid conflicts with another version of 
`libcurl` from the game.

3. Build in debug mode:
```shell
cmake --build build --target RedHttpClient --config Debug
```

## Tests
1. Install in your game directory:

```shell
node install.mjs
```
 
2. Run game.
3. Open CET, show Game Log popup.
4. Output should show tests result.

## Release
1. Build in release mode:

```shell
cmake --build build --target RedHttpClient --config Release
```

2. Bundle release:

```shell
node bundle.mjs
```

<!-- Table of links -->
[RED4ext]: https://github.com/WopsS/RED4ext
[Redscript]: https://github.com/jac3km4/redscript
[Cyber Engine Tweaks]: https://github.com/maximegmd/CyberEngineTweaks
[latest archive]: https://github.com/rayshader/cp2077-red-httpclient/releases/latest
[Codeware]: https://github.com/psiberx/cp2077-codeware/wiki#lifecycle
[RedData]: https://github.com/rayshader/cp2077-red-data
[RedFileSystem]: https://github.com/rayshader/cp2077-red-filesystem
[examples/]: https://github.com/rayshader/cp2077-red-httpclient/tree/master/examples
[Redscript Wiki]: https://wiki.redmodding.org/redscript/language/patterns#heterogeneous-array-literals