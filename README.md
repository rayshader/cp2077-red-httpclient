# Red Http Client
![Cyberpunk 2077](https://img.shields.io/badge/Cyberpunk%202077-v2.12-blue)
![GitHub License](https://img.shields.io/github/license/rayshader/cp2077-red-httpclient)
[![Donate](https://img.shields.io/badge/donate-buy%20me%20a%20coffee-yellow)](https://www.buymeacoffee.com/lpfreelance)

This plugin allows to execute HTTP requests. It can be used with Redscript and 
CET.

# Getting started

## Compatibility
- Cyberpunk 2077 v2.12
- [Redscript] 0.5.17+
- [Cyber Engine Tweaks] 1.31.0+

## Installation
1. Install requirements:
  - [RED4ext] v1.23.0+
2. Extract the [latest archive] into the Cyberpunk 2077 directory.

## Usage

### HttpClient

#### Method
> Method(arg: Variant) -> ref&lt;Variant&gt;

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
cmake -G "Visual Studio 17 2022" -A x64 -S . -B build
```

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
[examples/]: https://github.com/rayshader/cp2077-red-httpclient/tree/master/examples