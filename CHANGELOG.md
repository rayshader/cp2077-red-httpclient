# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

------------------------

## [0.5.0] - 2024-12-11
### Changed
- support patch 2.2
- bump libcpr to 1.11.1 (was 1.10.5)

------------------------

## [0.4.0] - 2024-09-13
### Changed
- support patch 2.13

------------------------

## [0.3.4] - 2024-07-14
### Fixed
- `RedData.Json` is now optional when installing `RedHttpClient`.

### Added
- support in `HttpClient` and `AsyncHttpClient` to send a body with `DELETE`
  methods.

------------------------

## [0.3.3] - 2024-05-29
### Fixed
- crash when initializing plugin while using MO2.

------------------------

## [0.3.2] - 2024-05-09
### Fixed
- gracefully release plugin when game is shutting down.

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
[Unreleased]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.5.0...HEAD
[0.5.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.4.0...v0.5.0
[0.4.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.4...v0.4.0
[0.3.4]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.3...v0.3.4
[0.3.3]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.2...v0.3.3
[0.3.2]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.1...v0.3.2
[0.3.1]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/rayshader/cp2077-red-httpclient/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/rayshader/cp2077-red-httpclient/releases/tag/v0.1.0
