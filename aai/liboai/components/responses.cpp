#include "../include/components/responses.h"

liboai::Response liboai::Responses::create(
	const std::string& model,
	const std::string& input,
	std::optional<ResponsesConversation*> conversation,
	std::optional<std::string> instructions,
	std::optional<bool> store,
	std::optional<float> temperature,
	std::optional<float> top_p,
	std::optional<uint32_t> max_tokens,
	std::optional<float> presence_penalty,
	std::optional<float> frequency_penalty,
	std::optional<std::string> user
) const & noexcept(false) {
	liboai::JsonConstructor jcon;
	jcon.push_back("model", model);
	jcon.push_back("input", input);

	// Add previous_response_id if conversation is provided and has one
	if (conversation && conversation.value()->HasPreviousResponseId()) {
		jcon.push_back("previous_response_id", conversation.value()->GetPreviousResponseId());
	}

	// Add optional parameters
	if (instructions) {
		jcon.push_back("instructions", instructions.value());
	}
	if (store.has_value()) {
		jcon.push_back("store", store.value());
	}
	if (temperature) {
		jcon.push_back("temperature", temperature.value());
	}
	if (top_p) {
		jcon.push_back("top_p", top_p.value());
	}
	if (max_tokens) {
		jcon.push_back("max_tokens", max_tokens.value());
	}
	if (presence_penalty) {
		jcon.push_back("presence_penalty", presence_penalty.value());
	}
	if (frequency_penalty) {
		jcon.push_back("frequency_penalty", frequency_penalty.value());
	}
	if (user) {
		jcon.push_back("user", user.value());
	}

	// Make the API request to /responses endpoint
	Response res;
	res = this->Request(
		Method::HTTP_POST, this->openai_root_, "/responses", "application/json",
		this->auth_.GetAuthorizationHeaders(),
		netimpl::components::Body {
			jcon.dump()
		},
		netimpl::components::WriteCallback{},  // No streaming support
		this->auth_.GetProxies(),
		this->auth_.GetProxyAuth(),
		this->auth_.GetMaxTimeout()
	);

	// Auto-update conversation with response ID if conversation was provided
	if (conversation && res) {
		UpdateConversation(res, *conversation.value());
	}

	return res;
}

liboai::FutureResponse liboai::Responses::create_async(
	const std::string& model,
	const std::string& input,
	std::optional<ResponsesConversation*> conversation,
	std::optional<std::string> instructions,
	std::optional<bool> store,
	std::optional<float> temperature,
	std::optional<float> top_p,
	std::optional<uint32_t> max_tokens,
	std::optional<float> presence_penalty,
	std::optional<float> frequency_penalty,
	std::optional<std::string> user
) const & noexcept(false) {
	return std::async(
		std::launch::async,
		&liboai::Responses::create,
		this,
		model,
		input,
		conversation,
		instructions,
		store,
		temperature,
		top_p,
		max_tokens,
		presence_penalty,
		frequency_penalty,
		user
	);
}

std::string liboai::Responses::GetOutputText(const liboai::Response& response) noexcept {
	try {
		if (response && response.raw_json.contains("output")) {
			const auto& output = response.raw_json["output"];
			
			// Iterate through output array to find message item
			for (const auto& item : output) {
				if (item.contains("type") && item["type"] == "message") {
					if (item.contains("content") && item["content"].is_array()) {
						// Find output_text in content array
						for (const auto& content_item : item["content"]) {
							if (content_item.contains("type") && content_item["type"] == "output_text") {
								if (content_item.contains("text")) {
									return content_item["text"].get<std::string>();
								}
							}
						}
					}
				}
			}
		}
	}
	catch (...) {
		// Return empty string on any error
	}
	
	return "";
}

std::string liboai::Responses::GetResponseId(const liboai::Response& response) noexcept {
	try {
		if (response && response.raw_json.contains("id")) {
			return response.raw_json["id"].get<std::string>();
		}
	}
	catch (...) {
		// Return empty string on any error
	}
	
	return "";
}

bool liboai::Responses::UpdateConversation(
	const liboai::Response& response,
	ResponsesConversation& conversation
) noexcept {
	try {
		std::string response_id = GetResponseId(response);
		if (!response_id.empty()) {
			conversation.SetPreviousResponseId(response_id);
			return true;
		}
	}
	catch (...) {
		// Return false on any error
	}
	
	return false;
}
