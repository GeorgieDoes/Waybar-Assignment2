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

// === === === Test subclass === === ===
class PulseAudioTest : public waybar::modules::Pulseaudio {
  public:
    PulseAudioTest() : Pulseaudio("pulseaudio", Json::Value()) { }

    void setMockState(uint32_t volume, bool muted) {
        volume_ = volume;
        muted_ = muted;
    }

    std::string formatted() const { return format(); }
    void update() override { update_count++; }
    int getUpdateCount() const { return update_count; }

  private:
    int update_count{0};
};

TEST_CASE_METHOD(PulseAudioTest, "Audio formatting logic") {
  SECTION("Muted takes priority") {
    setMockState(50, true);
    update();
    REQUIRE(getUpdateCount() == 1);
    REQUIRE(formatted().find("muted") != std::string::npos);
    REQUIRE(formatted().find("50") == std::string::npos);
  }
}

