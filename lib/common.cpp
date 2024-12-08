#include "common.h"

std::vector<long> string_to_vector(std::string& s) {
	std::stringstream ss{s};
	std::vector<long> out;

	for (long temp; ss >> temp;) {
		out.push_back(temp);
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

std::tuple<std::string, std::size_t, std::size_t> read_clean(
	std::string& filename) {
	std::ifstream input(filename);
	std::string text = readall(input);
	input.close();

	if (text.back() != '\n') text += "\n";
	size_t rows = std::ranges::count(text, '\n');
	size_t cols = text.length() / rows - 1;
	std::erase(text, '\n');
	return {text, rows, cols};
}
