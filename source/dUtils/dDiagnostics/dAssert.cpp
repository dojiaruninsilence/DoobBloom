#include "dAssert.h"
#include "dUtils/dDiagnostics/dLogger.h"

#include <cstdlib>

void dAssert::handleAssertionFailure(const char* expression, const char* file, int line, const char* message) {
	std::string formattedMessage = formatAssertionMessage(expression, file, line, message);

	// log the assertion failure message using logging system
	DB_FATAL(formattedMessage);

	// abort the program execution
	std::abort();
}

std::string dAssert::formatAssertionMessage(const char* expression, const char* file, int line, const char* message) {
    std::string formattedMessage = "Assertion failed: ";
    formattedMessage += expression;
    formattedMessage += ", file ";
    formattedMessage += file;
    formattedMessage += ", line ";
    formattedMessage += std::to_string(line);

    if (message != nullptr) {
        formattedMessage += ": ";
        formattedMessage += message;
    }

    return formattedMessage;
}