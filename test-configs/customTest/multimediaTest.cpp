#include <catch2/catch_test_macros.hpp>
#include <json/json.h>
#include <string>

namespace waybar::modules {
  // === === === Semi-mocekd pulseaudio module === === ===
  class Pulseaudio {
    public:
      Pulseaudio(const std::string& id, const Json::Value& config) : id_(id), config_(config) {}

      virtual ~Pulseaudio() = default;

      virtual void update() {
        // pretend communication
      }

    protected:
      virtual std::string format() const {
        if (muted_) return "[muted]";
        return std::to_string(volume_) + "%";
      }

      std::string id_;
      Json::Value config_;
      uint32_t volume_{0};
      bool muted_{false};
  };
}

class PulseAudioTest : public waybar::modules::Pulseaudio {
  public:
  private:
};

