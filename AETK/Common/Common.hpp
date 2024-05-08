/**
 *
 */
#pragma once

#ifndef COMMON_HPP
#define COMMON_HPP
#define _CRT_SECURE_NO_WARNINGS
// AETK Custom Wrapper Headers
#include "AETK/Common/SuiteManager.h"

// STD Headers
#include <algorithm>
#include <any>
#include <exception> // Include the <exception> header to define the std::exception class.
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <map>
#include <memory> // Include the <memory> header to use the standard allocator traits.
#include <mutex>
#include <optional>
#include <queue>
#include <set>
#include <sstream> // For std::ostringstream
#include <stdexcept>
#include <string> // Include the <string> header to use the std::string class.
#include <tuple>
#include <unicode/unistr.h>
#include <unordered_map> // Include the <unordered_map> header to use the unordered_map container.
#include <unordered_set>
#include <variant>
#include <vector>

#include <condition_variable>


using OneD = double;
using TwoD = std::tuple<double, double>;
using ThreeD = std::tuple<double, double, double>;
using Color = std::tuple<double, double, double, double>;

#endif // COMMON_HPP
