#include "AsyncHttpClient.h"
#include "HttpClient.h"

namespace RedHttpClient {

void AsyncHttpClient::queue_request(
  const std::shared_future<cpr::Response>& p_future,
  const HttpCallback& p_callback) {
  Red::JobQueue job_queue;

  job_queue.Dispatch([p_future, p_callback]() -> void {
    cpr::Response response = p_future.get();

    HttpClient::log_response(response);
    HttpHeaders headers = HttpClient::get_headers(response);
    auto http_response = Red::MakeHandle<HttpResponse>(response.status_code,
                                                       headers, response.text);

    p_callback(http_response);
  });
}

void AsyncHttpClient::get(const HttpCallback& p_callback,
                          const Red::CString& p_url,
                          const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  HttpClient::log_request(HttpMethod::GET, p_url, "", request_headers);
  cpr::AsyncResponse response = cpr::GetAsync(
    HttpClient::ssl_options, cpr::Url{p_url.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::post(const HttpCallback& p_callback,
                           const Red::CString& p_url,
                           const Red::CString& p_body,
                           const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  HttpClient::log_request(HttpMethod::POST, p_url, p_body, request_headers);
  cpr::AsyncResponse response =
    cpr::PostAsync(HttpClient::ssl_options, cpr::Url{p_url.c_str()},
                   cpr::Body{p_body.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::post_form(const HttpCallback& p_callback,
                                const Red::CString& p_url,
                                const Red::DynArray<HttpPair>& p_form,
                                const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  HttpClient::log_request_form(HttpMethod::POST, p_url, p_form,
                               request_headers);
  cpr::AsyncResponse response =
    cpr::PostAsync(HttpClient::ssl_options, cpr::Url{p_url.c_str()},
                   cpr::Payload{values.begin(), values.end()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::put(const HttpCallback& p_callback,
                          const Red::CString& p_url, const Red::CString& p_body,
                          const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  HttpClient::log_request(HttpMethod::PUT, p_url, p_body, request_headers);
  cpr::AsyncResponse response =
    cpr::PutAsync(HttpClient::ssl_options, cpr::Url{p_url.c_str()},
                  cpr::Body{p_body.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::put_form(const HttpCallback& p_callback,
                               const Red::CString& p_url,
                               const Red::DynArray<HttpPair>& p_form,
                               const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  HttpClient::log_request_form(HttpMethod::PUT, p_url, p_form, request_headers);
  cpr::AsyncResponse response =
    cpr::PutAsync(HttpClient::ssl_options, cpr::Url{p_url.c_str()},
                  cpr::Payload{values.begin(), values.end()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::patch(const HttpCallback& p_callback,
                            const Red::CString& p_url,
                            const Red::CString& p_body,
                            const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  if (!request_headers.contains("Content-Type")) {
    request_headers["Content-Type"] = "text/plain";
  }
  HttpClient::log_request(HttpMethod::PATCH, p_url, p_body, request_headers);
  cpr::AsyncResponse response =
    cpr::PatchAsync(HttpClient::ssl_options, cpr::Url{p_url.c_str()},
                    cpr::Body{p_body.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::patch_form(const HttpCallback& p_callback,
                                 const Red::CString& p_url,
                                 const Red::DynArray<HttpPair>& p_form,
                                 const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  std::vector<cpr::Pair> values;

  for (const auto& pair : p_form) {
    values.emplace_back(pair.key.c_str(), pair.value.c_str());
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  HttpClient::log_request_form(HttpMethod::PATCH, p_url, p_form,
                               request_headers);
  cpr::AsyncResponse response = cpr::PatchAsync(
    HttpClient::ssl_options, cpr::Url{p_url.c_str()},
    cpr::Payload{values.begin(), values.end()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::delete_(const HttpCallback& p_callback,
                              const Red::CString& p_url,
                              const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  HttpClient::log_request(HttpMethod::DELETE_, p_url, "", request_headers);
  cpr::AsyncResponse response = cpr::DeleteAsync(
    HttpClient::ssl_options, cpr::Url{p_url.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

}  // namespace RedHttpClient