#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "../lib/common.h"

void reflect(std::ranges::range auto& v) {
	// so that v is always increasing
	for (auto it = v.rbegin(); it != v.rend(); it++) {
		*it = *v.begin() - *it;
	}
}

bool check_safe(std::ranges::range auto& v, const bool error_allowed) {
	if (v.back() < v.front()) {
		reflect(v);
	}

	int delta = 0;
	for (size_t ix = 1; ix < v.size(); ix++) {
		delta = v[ix] - v[ix - 1];
		if (delta > 3 or delta < 1) {
			if (error_allowed) {
				auto v1 = v, v2 = v;
				v1.erase(v1.begin() + ix);
				v2.erase(v2.begin() + ix - 1);
				return (check_safe(v1, 0) || check_safe(v2, 0));
			} else
				return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "input.txt"};

	std::vector<int> counters(2, 0);
	for (std::string temp; std::getline(input, temp);) {
		auto v = string_to_vector(temp);
		counters[0] += check_safe(v, 0);
		counters[1] += check_safe(v, 1);
	}
	std::print("{}, {}\n", counters[0], counters[1]);
}
