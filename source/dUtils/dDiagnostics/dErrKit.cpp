#include "dErrKit.h"

#include "dUtils/dDiagnostics/dLogger.h"

namespace dDiagnostics {
    // function to report errors
    void reportError(errorCode code, const std::string& message, const char* sourceFile, int line) {
        // convert source file to a string
        std::string sourceFileStr(sourceFile);

        // construct error message with details
        std::string errorMessage = "Error: " + message + " [Code: " + std::to_string(static_cast<int>(code)) + "]";
        errorMessage += " [Source: " + sourceFileStr + " Line: " + std::to_string(line) + "]";

        // log error message using your existing logging system (assuming dLogger is your logging system)
        DB_ERROR(errorMessage);

        // add more - like add a switch for severity levels, and maybe stop the application if above a severity level?
    }

    // constructor implementation
    dError::dError(errorCode code, const std::string& message, const char* sourceFile, int line)
        : m_code(code), m_message(message), m_sourceFile(sourceFile), m_line(line) {
    }

    // destructor implementation
    dError::~dError() {}

    // getter implementation for error code
    errorCode dError::getCode() const {
        return m_code;
    }

    // getter implementation for error message
    std::string dError::getMessage() const {
        return m_message;
    }

    // getter implementation for source file
    const char* dError::getSourceFile() const {
        return m_sourceFile;
    }

    // getter implementation for line number
    int dError::getLine() const {
        return m_line;
    }
}