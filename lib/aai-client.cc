#include "../inc/aai-client.hh"
#include <stdexcept>

namespace ttt {

aai_client::aai_client(const config& cfg) : config_(cfg) {
    // Set up liboai authorization
    liboai::Authorization::Authorizer().SetKeyEnv(cfg.api_key);
    
    // Create OpenAI client with custom base URL
    client_ = std::make_unique<liboai::OpenAI>(cfg.api_url);
}

std::string aai_client::ask(
    const std::string& prompt,
    const std::string& instructions
) {
    try {
        // Prepare optional instructions
        std::optional<std::string> instr = instructions.empty() 
            ? std::nullopt 
            : std::make_optional(instructions);
        
        // Call Responses API
        auto response = client_->Responses->create(
            config_.model,
            prompt,
            &conversation_,  // Pass conversation for chaining
            instr,           // Optional instructions
            std::nullopt,    // store (default: true)
            std::nullopt,    // temperature
            std::nullopt,    // top_p
            std::nullopt,    // max_tokens
            std::nullopt,    // presence_penalty
            std::nullopt,    // frequency_penalty
            std::nullopt     // user
        );
        
        // Extract output text from response
        std::string output = liboai::Responses::GetOutputText(response);
        
        if (output.empty()) {
            throw std::runtime_error("Empty response from AI API");
        }
        
        return output;
    }
    catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("AI API error: ") + e.what()
        );
    }
}

void aai_client::new_conversation() {
    conversation_.ClearPreviousResponseId();
}

} // namespace ttt
