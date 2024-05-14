#pragma once

#include <string>

namespace dDiagnostics {

	// enum for error codes
	enum class errorCode {
		INITIALIZATION_ERROR,
		RUNTIME_ERROR,
		INPUT_VALIDATION_ERROR,
		FILE_IO_ERROR
	};

	void reportError(errorCode code, const std::string& message, const char* sourceFile, int line);

	class dError {
	public:
		// constructor
		dError(errorCode code, const std::string& message, const char* sourceFile, int line);

		// destuctor 
		~dError();

		// getters for error details
		errorCode getCode() const;
		std::string getMessage() const;
		const char* getSourceFile() const;
		int getLine() const;

	private:
		errorCode m_code;
		std::string m_message;
		const char* m_sourceFile;
		int m_line;
	}; // end of error class
}

