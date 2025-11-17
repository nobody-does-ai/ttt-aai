#pragma once

#include "config.hh"
#include "../aai/liboai/include/liboai.h"
#include <string>
#include <memory>

namespace ttt {

/**
 * @brief Simple client for interacting with AI APIs via Responses API
 * 
 * Wraps the liboai Responses API with a clean interface for our MCP server.
 * Manages conversation state and provides blocking (non-streaming) calls.
 */
class aai_client {
public:
    /**
     * @brief Construct an AI client from configuration
     * 
     * @param cfg Configuration with API key, URL, model, etc.
     */
    explicit aai_client(const config& cfg);
    
    ~aai_client() = default;

    /**
     * @brief Send a prompt to the AI and get a response
     * 
     * @param prompt The input prompt/message
     * @param instructions Optional system instructions
     * @return The AI's response text
     * @throws std::runtime_error on API errors
     */
    std::string ask(
        const std::string& prompt,
        const std::string& instructions = ""
    );

    /**
     * @brief Start a new conversation (clear state)
     */
    void new_conversation();

    /**
     * @brief Get the nickname for this AI
     */
    std::string get_nickname() const { return config_.nickname; }

    /**
     * @brief Get the model being used
     */
    std::string get_model() const { return config_.model; }

private:
    config config_;
    std::unique_ptr<liboai::OpenAI> client_;
    liboai::ResponsesConversation conversation_;
};

} // namespace ttt
