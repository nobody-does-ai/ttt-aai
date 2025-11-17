#include "../inc/config.hh"
#include "../inc/aai-client.hh"
#include "mcp_server.h"
#include "mcp_tool.h"
#include <iostream>
#include <memory>
#include <cstdlib>

using json = nlohmann::json;

/**
 * @brief MCP Server for AI APIs
 * 
 * Exposes AI capabilities as MCP tools, enabling AI-to-AI communication.
 * 
 * Usage:
 *   Set environment variables for your AI provider:
 *     OPENAI_API_KEY=sk-...
 *     OPENAI_API_URL=https://api.openai.com/v1
 *     OPENAI_API_MOD=gpt-4o
 *     OPENAI_API_MID=gpt
 *   
 *   Then run:
 *     AI_PROVIDER=OPENAI ./mcp-server
 */

int main(int argc, char** argv) {
    try {
        // Get provider from environment
        const char* provider_env = std::getenv("AI_PROVIDER");
        if (!provider_env) {
            std::cerr << "Error: AI_PROVIDER environment variable not set\n";
            std::cerr << "Example: AI_PROVIDER=OPENAI ./mcp-server\n";
            return 1;
        }
        std::string provider(provider_env);
        
        // Load configuration
        std::cout << "Loading configuration for provider: " << provider << "\n";
        ttt::config cfg = ttt::config::from_environment(provider);
        std::cout << "  Model: " << cfg.model << "\n";
        std::cout << "  Nickname: " << cfg.nickname << "\n";
        std::cout << "  API URL: " << cfg.api_url << "\n";
        
        // Create AI client
        std::cout << "Initializing AI client...\n";
        auto ai_client = std::make_shared<ttt::aai_client>(cfg);
        
        // Configure MCP server
        mcp::server::configuration server_config;
        server_config.name = cfg.nickname + "-mcp-server";
        server_config.version = "1.0.0";
        server_config.host = "localhost";
        server_config.port = 8080;
        
        // Create MCP server
        std::cout << "Starting MCP server...\n";
        mcp::server server(server_config);
        
        // Register the ask_ai tool
        auto ask_ai_tool = mcp::tool_builder("ask_ai")
            .with_description("Ask the AI a question and get a response")
            .with_string_param("prompt", "The question or prompt to send to the AI", true)
            .with_string_param("instructions", "Optional system instructions for the AI", false)
            .build();
        
        auto ask_ai_handler = [ai_client](const json& params, const std::string& session_id) -> json {
            try {
                // Extract parameters
                std::string prompt = params["prompt"];
                std::string instructions = params.value("instructions", "");
                
                // Call AI
                std::string response = ai_client->ask(prompt, instructions);
                
                // Return response
                return json{
                    {"type", "text"},
                    {"text", response}
                };
            }
            catch (const std::exception& e) {
                return json{
                    {"type", "error"},
                    {"error", e.what()}
                };
            }
        };
        
        server.register_tool(ask_ai_tool, ask_ai_handler);
        
        std::cout << "MCP server ready. Nickname: " << cfg.nickname << "\n";
        std::cout << "Listening on " << server_config.host << ":" << server_config.port << "\n";
        
        // Start server (blocking)
        server.start(true);
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
