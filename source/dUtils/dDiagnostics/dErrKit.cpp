#include "dbpch.h"

namespace dDiagnostics {
    // function to report errors
    void reportError(errorLevel errorLevel, errorCode code, const std::string& message, const char* sourceFile, int line) {
        // convert source file to a string
        std::string sourceFileStr(sourceFile);

        // construct error message with details
        std::string errorMessage = "Error: " + message + " [Code: " + std::to_string(static_cast<int>(code)) + "]";
        errorMessage += " [Source: " + sourceFileStr + " Line: " + std::to_string(line) + "]";

        // log error message using logging system
        switch (errorLevel) {
        case dDiagnostics::errorLevel::D_INFO:
            DB_INFO_QUIET(errorMessage);
            break;
        case dDiagnostics::errorLevel::D_WARNING:
            DB_WARN(errorMessage);
            break;
        case dDiagnostics::errorLevel::D_ERROR:
            DB_ERROR(errorMessage);
            break;
        case dDiagnostics::errorLevel::D_FATAL:
            DB_FATAL(errorMessage);
            // shut down the application for fatal errors
            exit(EXIT_FAILURE);
            break;
        default:
            DB_INFO_QUIET(errorMessage);
            break;
        }
    }

    // constructor implementation
    dError::dError(errorLevel errorLevel, errorCode code, const std::string& message, const char* sourceFile, int line)
        : m_errorLevel(errorLevel), m_code(code), m_message(message), m_sourceFile(sourceFile), m_line(line) {
    }

    // destructor implementation
    dError::~dError() {}

    // getter implementation for error code
    errorLevel dError::getErrorLevel() const {
        return m_errorLevel;
    }

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