# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

------------------------

## [0.3.1] - 2024-04-27
### Fixed
- name of HttpStatus in scripts.

------------------------

## [0.3.0] - 2024-04-27
### Fixed
- enable / disable logging when loading option from `config.json`.

### Added
- support to send `multipart/form-data` with `HttpClient` and `AsyncHttpClient`.
- class `HttpMultipart` to add / set / get parts, without support for files / buffers.

------------------------

## [0.2.0] - 2024-04-18
### Fixed
- add missing headers in request when using `HttpClient.Delete()` / `AsyncHttpClient.Delete()`.

### Added
- log requests and responses in `red4ext/logs/redhttpclient-YYYY-MM-DD-HH-mm-ss.log` (enabled by default).
- enable / disable logging in `red4ext/plugins/RedFileSystem/storages/RedHttpClient/config.json`.

------------------------

## [0.1.0] - 2024-04-13
### Added
- HttpClient to send HTTP requests (blocking mode).
- AsyncHttpClient to asynchronously send HTTP requests (callback mode).

<!-- Table of releases -->
[Unreleased]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.1...HEAD
[0.3.1]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/rayshader/cp2077-red-httpclient/releases/tag/v0.1.0
