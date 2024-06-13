#pragma once

#include "dUtils/dDiagnostics/dLogger.h"

#include <string>

namespace doob {

	// enum for error severity
	enum class errorLevel {
		D_INFO,
		D_WARNING,
		D_ERROR,
		D_FATAL
	};

	// enum for error codes
	enum class errorCode {
		INITIALIZATION_ERROR,
		RUNTIME_ERROR,
		INPUT_VALIDATION_ERROR,
		FILE_IO_ERROR,
		OUT_OF_BOUNDS
	};

	void reportError(errorLevel errorLevel, errorCode code, const std::string& message, const char* sourceFile, int line);

	class dError {
	public:
		// constructor
		dError(errorLevel errorLevel, errorCode code, const std::string& message, const char* sourceFile, int line);

		// destuctor 
		~dError();

		// getters for error details
		errorLevel getErrorLevel() const;
		errorCode getCode() const;
		std::string getMessage() const;
		const char* getSourceFile() const;
		int getLine() const;

	private:
		errorLevel m_errorLevel;
		errorCode m_code;
		std::string m_message;
		const char* m_sourceFile;
		int m_line;
	}; // end of error class
}

