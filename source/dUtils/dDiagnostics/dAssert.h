#pragma once

#include <string>

class dAssert {
public:
	static void handleAssertionFailure(const char* expression, const char* file, int line, const char* message = nullptr);

private:
	static std::string formatAssertionMessage(const char* expression, const char* file, int line, const char* message);
};

// Define assertion macros
#ifdef DB_DEBUG
    #define D_ASSERT(expression, message) \
            if (!(expression)) \
                dAssert::handleAssertionFailure(#expression, __FILE__, __LINE__, message)

    #define D_ASSERT_MSG(expression, message) D_ASSERT(expression, message)

    #define D_ASSERT_FAIL(message) \
            dAssert::handleAssertionFailure(nullptr, __FILE__, __LINE__, message)
#else
    #define D_ASSERT(expression, message)
    #define D_ASSERT_MSG(expression, message) D_ASSERT(expression, message)
    #define D_ASSERT_FAIL(message)
#endif 