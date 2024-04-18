#ifndef REDHTTPCLIENT_SETTINGS_H
#define REDHTTPCLIENT_SETTINGS_H

#include <RED4ext/RED4ext.hpp>
#include <RedData.hpp>
#include <RedFileSystem.hpp>
#include <RedLib.hpp>
#include <iostream>

namespace RedHttpClient {

class Settings {
 private:
  RedFileSystem::FileSystemStorage storage;
  RedFileSystem::File config;

  bool logging;

 private:
  void load_config() {
    if (!RedFileSystem::IsDetected() || !RedData::IsDetected()) {
      return;
    }
    storage = RedFileSystem::FileSystem::GetStorage("RedHttpClient");
    if (!storage) {
      return;
    }
    RedFileSystem::FileSystemStatus status = storage.Exists("config.json");

    config = storage.GetFile("config.json");
    if (status != RedFileSystem::FileSystemStatus::True) {
      create_config();
    } else {
      read_config();
    }
  }

  void create_config() {
    std::stringstream stream;

    stream << "{"
              "\"version\": \"0.2.0\","
              "\"logging\": " << std::boolalpha << logging
           << "}";
    auto json = RedData::Json::ParseJson(stream.str());

    config.WriteJson(json);
  }

  void read_config() {
    auto json = config.ReadAsJson();

    if (!json.IsObject()) {
      return;
    }
    RedData::Json::JsonObject conf = json.GetHandle();

    logging = conf.GetKeyBool("logging");
  }

 public:
  Settings() : logging(true) {}

  [[nodiscard]] bool can_log() const { return logging; }

  void load() { load_config(); }

  void unload() {
    storage = {};
    config = {};
  }
};

}  // namespace RedHttpClient

#endif  //REDHTTPCLIENT_SETTINGS_H
