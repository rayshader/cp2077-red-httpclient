#include "AsyncHttpClient.h"
#include "HttpClient.h"
#include "HttpPlugin.h"

namespace RedHttpClient {

HttpPlugin* AsyncHttpClient::plugin = HttpPlugin::get();

void AsyncHttpClient::queue_request(
  const std::shared_future<cpr::Response>& p_future,
  const HttpCallback& p_callback) {
  Red::JobQueue job_queue;

  job_queue.Dispatch([p_future, p_callback]() -> void {
    cpr::Response response = p_future.get();

    plugin->log_response(response);
    HttpHeaders headers = HttpClient::get_headers(response);
    auto http_response = Red::MakeHandle<HttpResponse>(response.status_code,
                                                       headers, response.text);

    p_callback(http_response);
  });
}

template <HttpMethod Method, class T>
void AsyncHttpClient::send(const HttpCallback& p_callback,
                           const Red::CString& p_url, const T& p_body,
                           const Red::Optional<HttpHeaders>& p_headers) {
  if constexpr (std::is_same<T, Red::CString>()) {
    send_body<Method>(p_callback, p_url, p_body, p_headers);
  } else if constexpr (std::is_same<T, HttpPairs>()) {
    send_form<Method>(p_callback, p_url, p_body, p_headers);
  } else if constexpr (std::is_same<T, Red::Handle<HttpMultipart>>()) {
    send_multipart<Method>(p_callback, p_url, p_body, p_headers);
  }
}

template <HttpMethod Method>
void AsyncHttpClient::send_body(const HttpCallback& p_callback,
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
  plugin->log_request(Method, p_url, p_body, request_headers);
  std::shared_future<cpr::Response> future;

  if constexpr (Method == HttpMethod::POST) {
    future = cpr::PostAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                            cpr::Body{p_body.c_str()}, request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::PUT) {
    future = cpr::PutAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                           cpr::Body{p_body.c_str()}, request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::PATCH) {
    future = cpr::PatchAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                             cpr::Body{p_body.c_str()}, request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::DELETE_) {
    future =
      cpr::DeleteAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                       cpr::Body{p_body.c_str()}, request_headers)
        .share();
  }
  queue_request(future, p_callback);
}

template <HttpMethod Method>
void AsyncHttpClient::send_form(const HttpCallback& p_callback,
                                const Red::CString& p_url,
                                const HttpPairs& p_form,
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

  plugin->log_request(Method, p_url, p_form, request_headers);
  std::shared_future<cpr::Response> future;

  if constexpr (Method == HttpMethod::POST) {
    future = cpr::PostAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                            cpr::Payload{values.begin(), values.end()},
                            request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::PUT) {
    future =
      cpr::PutAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                    cpr::Payload{values.begin(), values.end()}, request_headers)
        .share();
  } else if constexpr (Method == HttpMethod::PATCH) {
    future = cpr::PatchAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                             cpr::Payload{values.begin(), values.end()},
                             request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::DELETE_) {
    future = cpr::DeleteAsync(
               plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
               cpr::Payload{values.begin(), values.end()}, request_headers)
               .share();
  }
  queue_request(future, p_callback);
}

template <HttpMethod Method>
void AsyncHttpClient::send_multipart(
  const HttpCallback& p_callback, const Red::CString& p_url,
  const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  plugin->log_request(Method, p_url, p_form, request_headers);
  std::shared_future<cpr::Response> future;

  if constexpr (Method == HttpMethod::POST) {
    future = cpr::PostAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                            p_form->get(), request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::PUT) {
    future = cpr::PutAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                           p_form->get(), request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::PATCH) {
    future = cpr::PatchAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                             p_form->get(), request_headers)
               .share();
  } else if constexpr (Method == HttpMethod::DELETE_) {
    future =
      cpr::DeleteAsync(plugin->get_ssl_options(), cpr::Url{p_url.c_str()},
                       p_form->get(), request_headers)
        .share();
  }
  queue_request(future, p_callback);
}

void AsyncHttpClient::get(const HttpCallback& p_callback,
                          const Red::CString& p_url,
                          const Red::Optional<HttpHeaders>& p_headers) {
  if (!HttpClient::is_secure(p_url)) {
    p_callback({});
    return;
  }
  cpr::Header request_headers = HttpClient::build_headers(p_headers.value);

  plugin->log_request(HttpMethod::GET, p_url, "", request_headers);
  cpr::AsyncResponse response = cpr::GetAsync(
    plugin->get_ssl_options(), cpr::Url{p_url.c_str()}, request_headers);

  queue_request(response.share(), p_callback);
}

void AsyncHttpClient::post(const HttpCallback& p_callback,
                           const Red::CString& p_url,
                           const Red::CString& p_body,
                           const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::POST>(p_callback, p_url, p_body, p_headers);
}

void AsyncHttpClient::post_form(const HttpCallback& p_callback,
                                const Red::CString& p_url,
                                const HttpPairs& p_form,
                                const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::POST>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::post_multipart(
  const HttpCallback& p_callback, const Red::CString& p_url,
  const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::POST>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::put(const HttpCallback& p_callback,
                          const Red::CString& p_url, const Red::CString& p_body,
                          const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PUT>(p_callback, p_url, p_body, p_headers);
}

void AsyncHttpClient::put_form(const HttpCallback& p_callback,
                               const Red::CString& p_url,
                               const HttpPairs& p_form,
                               const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PUT>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::put_multipart(
  const HttpCallback& p_callback, const Red::CString& p_url,
  const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PUT>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::patch(const HttpCallback& p_callback,
                            const Red::CString& p_url,
                            const Red::CString& p_body,
                            const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PATCH>(p_callback, p_url, p_body, p_headers);
}

void AsyncHttpClient::patch_form(const HttpCallback& p_callback,
                                 const Red::CString& p_url,
                                 const HttpPairs& p_form,
                                 const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PATCH>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::patch_multipart(
  const HttpCallback& p_callback, const Red::CString& p_url,
  const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::PATCH>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::delete_(const HttpCallback& p_callback,
                              const Red::CString& p_url,
                              const Red::Optional<Red::CString>& p_body,
                              const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::DELETE_>(p_callback, p_url, p_body.value, p_headers);
}

void AsyncHttpClient::delete_form(const HttpCallback& p_callback,
                                  const Red::CString& p_url,
                                  const HttpPairs& p_form,
                                  const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::DELETE_>(p_callback, p_url, p_form, p_headers);
}

void AsyncHttpClient::delete_multipart(
  const HttpCallback& p_callback, const Red::CString& p_url,
  const Red::Handle<HttpMultipart>& p_form,
  const Red::Optional<HttpHeaders>& p_headers) {
  send<HttpMethod::DELETE_>(p_callback, p_url, p_form, p_headers);
}

}  // namespace RedHttpClient