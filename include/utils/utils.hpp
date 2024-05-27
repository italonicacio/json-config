#pragma once

#include <vector>
#include <algorithm>

namespace Utils {
	template <typename T>
	inline bool contains(const std::vector<T>& vec, T value) {
		return std::find(vec.begin(), vec.end(), value) != vec.end();
	}
}
