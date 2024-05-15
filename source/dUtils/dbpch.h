#pragma once

// std lib headers
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// utility and helper functions
#include "dUtils/dDiagnostics/dAssert.h"
#include "dUtils/dDiagnostics/dErrKit.h"
#include "dUtils/dDiagnostics/dLogger.h"

#ifdef DB_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // DB_PLATFORM_WINDOWS
