#pragma once

/*
	responses.h : Responses component class for OpenAI.
		This class contains all the methods for the Responses component
		of the OpenAI API. This class provides access to 'Responses' 
		endpoints on the OpenAI API and should be accessed via the
		liboai.h header file through an instantiated liboai::OpenAI
		object after setting necessary authentication information
		through the liboai::Authorization::Authorizer() singleton
		object.
		
	The Responses API is OpenAI's new API primitive that provides:
	- Server-side conversation state management
	- Better caching (40-80% improvement)
	- Simplified interface
	- Future-proof design for upcoming models
*/

#include "../core/authorization.h"
#include "../core/response.h"

namespace liboai {
	/*
		@brief Class for managing Responses API conversations with server-side state.
			Unlike Chat Completions which require manual conversation management,
			Responses API can maintain state server-side via response IDs.
	*/
	class ResponsesConversation final {
		public:
			ResponsesConversation() = default;
			ResponsesConversation(const ResponsesConversation& other) = default;
			ResponsesConversation(ResponsesConversation&& old) noexcept = default;
			~ResponsesConversation() = default;

			ResponsesConversation& operator=(const ResponsesConversation& other) = default;
			ResponsesConversation& operator=(ResponsesConversation&& old) noexcept = default;

			/*
				@brief Set the previous response ID for conversation chaining.
				
				@param response_id  The ID from a previous response to continue from.
			*/
			void SetPreviousResponseId(std::string_view response_id) {
				this->previous_response_id_ = response_id;
			}

			/*
				@brief Get the current previous response ID.
				
				@returns The previous response ID, or empty string if not set.
			*/
			std::string GetPreviousResponseId() const {
				return this->previous_response_id_;
			}

			/*
				@brief Clear the previous response ID (start a new conversation).
			*/
			void ClearPreviousResponseId() {
				this->previous_response_id_.clear();
			}

			/*
				@brief Check if a previous response ID is set.
				
				@returns True if a previous response ID exists.
			*/
			bool HasPreviousResponseId() const {
				return !this->previous_response_id_.empty();
			}

		private:
			std::string previous_response_id_;
	};

	/*
		@brief Class for interacting with the OpenAI Responses API.
			The Responses API provides server-side conversation state management,
			better caching, and built-in agentic capabilities.
			
		NO STREAMING SUPPORT - We only implement synchronous, blocking calls.
		Streaming is theater. Fast is good. Instant is better.
	*/
	class Responses final : private Network {
		public:
			Responses(const std::string &root): Network(root) {}
			NON_COPYABLE(Responses)
			NON_MOVABLE(Responses)
			~Responses() = default;

			/*
				@brief Creates a response from the model.
				
				@param *model             ID of the model to use (e.g., "gpt-4o", "gpt-5").
				@param *input             The input to send to the model.
				@param conversation       Optional ResponsesConversation object for chaining responses.
				@param instructions       Optional system-level instructions for the model.
				@param store              Whether to store the response server-side (default: true).
				@param temperature        Sampling temperature between 0 and 2.
				@param top_p              Nucleus sampling parameter.
				@param max_tokens         Maximum number of tokens to generate.
				@param presence_penalty   Penalty for token presence (-2.0 to 2.0).
				@param frequency_penalty  Penalty for token frequency (-2.0 to 2.0).
				@param user               Unique identifier for the end-user.
				
				@returns A Response object containing the API response.
			*/
			LIBOAI_EXPORT liboai::Response create(
				const std::string& model,
				const std::string& input,
				std::optional<ResponsesConversation*> conversation = std::nullopt,
				std::optional<std::string> instructions = std::nullopt,
				std::optional<bool> store = std::nullopt,
				std::optional<float> temperature = std::nullopt,
				std::optional<float> top_p = std::nullopt,
				std::optional<uint32_t> max_tokens = std::nullopt,
				std::optional<float> presence_penalty = std::nullopt,
				std::optional<float> frequency_penalty = std::nullopt,
				std::optional<std::string> user = std::nullopt
			) const & noexcept(false);

			/*
				@brief Asynchronously creates a response from the model.
				
				@param *model             ID of the model to use (e.g., "gpt-4o", "gpt-5").
				@param *input             The input to send to the model.
				@param conversation       Optional ResponsesConversation object for chaining responses.
				@param instructions       Optional system-level instructions for the model.
				@param store              Whether to store the response server-side (default: true).
				@param temperature        Sampling temperature between 0 and 2.
				@param top_p              Nucleus sampling parameter.
				@param max_tokens         Maximum number of tokens to generate.
				@param presence_penalty   Penalty for token presence (-2.0 to 2.0).
				@param frequency_penalty  Penalty for token frequency (-2.0 to 2.0).
				@param user               Unique identifier for the end-user.
				
				@returns A FutureResponse object for async access to the API response.
			*/
			LIBOAI_EXPORT liboai::FutureResponse create_async(
				const std::string& model,
				const std::string& input,
				std::optional<ResponsesConversation*> conversation = std::nullopt,
				std::optional<std::string> instructions = std::nullopt,
				std::optional<bool> store = std::nullopt,
				std::optional<float> temperature = std::nullopt,
				std::optional<float> top_p = std::nullopt,
				std::optional<uint32_t> max_tokens = std::nullopt,
				std::optional<float> presence_penalty = std::nullopt,
				std::optional<float> frequency_penalty = std::nullopt,
				std::optional<std::string> user = std::nullopt
			) const & noexcept(false);

			/*
				@brief Helper function to extract output_text from a Responses API response.
				
				@param response  The Response object from create() or create_async().
				
				@returns The text content from the response, or empty string if not found.
			*/
			LIBOAI_EXPORT static std::string GetOutputText(const liboai::Response& response) noexcept;

			/*
				@brief Helper function to extract the response ID from a Responses API response.
				
				@param response  The Response object from create() or create_async().
				
				@returns The response ID, or empty string if not found.
			*/
			LIBOAI_EXPORT static std::string GetResponseId(const liboai::Response& response) noexcept;

			/*
				@brief Helper function to update a conversation with the response ID.
				
				@param response      The Response object from create() or create_async().
				@param conversation  The ResponsesConversation object to update.
				
				@returns True if the response ID was successfully extracted and set.
			*/
			LIBOAI_EXPORT static bool UpdateConversation(
				const liboai::Response& response,
				ResponsesConversation& conversation
			) noexcept;

		private:
			Authorization& auth_ = Authorization::Authorizer();
	};
}
