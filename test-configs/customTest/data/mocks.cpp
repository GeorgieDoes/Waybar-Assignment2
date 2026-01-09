#include <mutex>
#include <string>

std::mutex reap_mtx;
std::string reap;

namespace waybar {
    extern std::mutex reap_mtx;
    extern std::string reap;
    
    namespace util {
        void prepare_for_sleep() {}
    }
}

namespace waybar {
    std::mutex &reap_mtx_ref = ::reap_mtx;
}
