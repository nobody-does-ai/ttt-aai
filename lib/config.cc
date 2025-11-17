#include "../inc/config.hh"
#include <stdexcept>
#include <sstream>

namespace ttt {

std::string config::get_env(const std::string& name, bool required) {
    const char* value = std::getenv(name.c_str());
    
    if (!value || value[0] == '\0') {
        if (required) {
            throw std::runtime_error("Required environment variable not set: " + name);
        }
        return "";
    }
    
    return std::string(value);
}

config config::from_environment(const std::string& provider_name) {
    config cfg;
    cfg.provider = provider_name;
    
    // Build environment variable names
    std::string prefix = provider_name + "_API_";
    
    // Required variables
    cfg.api_key = get_env(prefix + "KEY", true);
    cfg.api_url = get_env(prefix + "URL", true);
    cfg.model = get_env(prefix + "MOD", true);
    
    // Optional variables
    cfg.nickname = get_env(prefix + "MID", false);
    if (cfg.nickname.empty()) {
        // Default nickname is lowercase provider name
        cfg.nickname = provider_name;
        for (auto& c : cfg.nickname) {
            c = std::tolower(c);
        }
    }
    
    return cfg;
}

} // namespace ttt
