#pragma once

#include <string>
#include <cstdlib>
#include <stdexcept>

namespace ttt {

/**
 * @brief Configuration manager for reading AI provider settings from environment
 * 
 * Reads environment variables in the format:
 *   {PROVIDER}_API_KEY
 *   {PROVIDER}_API_URL
 *   {PROVIDER}_API_MOD (model)
 *   {PROVIDER}_API_MID (nickname)
 * 
 * Example:
 *   OPENAI_API_KEY=sk-...
 *   OPENAI_API_URL=https://api.openai.com/v1
 *   OPENAI_API_MOD=gpt-4o
 *   OPENAI_API_MID=gpt
 */
class config {
public:
    std::string api_key;
    std::string api_url;
    std::string model;
    std::string nickname;
    std::string provider;

    /**
     * @brief Load configuration from environment for a specific provider
     * 
     * @param provider_name The provider name (e.g., "OPENAI", "ANTHROPIC")
     * @return config object with all settings
     * @throws std::runtime_error if required variables are missing
     */
    static config from_environment(const std::string& provider_name);

    /**
     * @brief Check if all required configuration is present
     */
    bool is_valid() const {
        return !api_key.empty() && !api_url.empty() && !model.empty();
    }

private:
    static std::string get_env(const std::string& name, bool required = true);
};

} // namespace ttt
