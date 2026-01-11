#include <catch2/catch_test_macros.hpp>
#include <json/json.h>
#include <string>

namespace waybar::modules {
  class Pulseaudio {
    public:
      Pulseaudio(const std::string& id, const Json::Value& config) : id_(id), config_(config) {}

      virtual ~Pulseaudio() = default;

      virtual void update() {
        // pretend communication
      }
  }
}

