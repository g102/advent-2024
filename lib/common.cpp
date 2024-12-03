#include "./common.h"

std::vector<int> string_to_vector(std::string& s) {
	size_t n = std::ranges::count(s, ' ') + 1;
	std::stringstream ss{s};
	std::vector<int> out(n);

	for (size_t ix = 0; ix < n; ix++) {
		ss >> out[ix];
	}
	return out;
}

std::string readall(std::ifstream& input) {
	std::string contents;
	input.seekg(0, std::ios::end);
	contents.resize(input.tellg());
	input.seekg(0, std::ios::beg);
	input.read(&contents[0], contents.size());
	return contents;
}
