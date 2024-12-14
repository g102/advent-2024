#include <format>

#include "common.h"

auto mod(const auto n, const auto M) { return ((n % M) + M) % M; }

int slice(const std::string_view line, size_t i0, size_t i1) {
	return std::stoi(std::string{line.substr(i0 + 1, i1 - i0 - 1)});
}

struct Robot {
	int x, y, u, v;
	std::array<int, 2> bounds;

	Robot(const std::string_view l, const auto _b) : bounds(_b) {
		std::array<char, 5> delim{'=', ',', ' ', '=', ','};
		std::array<size_t, 4> it;

		it[0] = l.find(delim[0], 0);
		for (size_t ix = 1; ix < delim.size(); ix++)
			it[ix] = l.find(delim[ix], it[ix - 1]);

		x = slice(l, it[0], it[1]);
		y = slice(l, it[1], it[2]);
		u = slice(l, it[3], it[4]);
		v = slice(l, it[4], -1);
	}

	void advance(int t = 1) {
		x = mod(x + u * t, bounds[0]);
		y = mod(y + v * t, bounds[1]);
	}

	std::array<int, 2> get_pos() { return {x, y}; }

	int get_quad() {
		if (x == bounds[0] / 2 || y == bounds[1] / 2) return -1;
		std::array<bool, 2> bcheck{x > bounds[0] / 2, y > bounds[1] / 2};
		return bcheck[0] * 2 + bcheck[1];
	}
};

std::array<int, 2> parse_bounds(const std::string_view line) {
	// line: 11 7
	std::stringstream ss{line.data()};
	std::array<int, 2> out;
	ss >> out[0] >> out[1];
	return out;
}

void save_image(const std::vector<Robot>& robots, size_t ix, auto& bounds) {
	std::vector<std::string> out;
	for (int i = 0; i < bounds[1]; i++) {
		std::string temp(bounds[0]+1, '.');
		temp.back() = '\n';
		out.push_back(temp);
	}

	for (auto& r: robots) {
		out[r.y][r.x] = 'X';
	}

	std::string path_out = std::format("./out-maps/{:04}.txt", ix);
	std::ofstream file_out{path_out};
	for (auto& l: out) file_out << l;
	file_out.close();
}

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "input.txt"};

	std::string temp;
	getline(input, temp);
	auto bounds = parse_bounds(temp);

	std::vector<Robot> robots;
	while (getline(input, temp)) {
		robots.push_back(Robot{temp, bounds});
	}
	input.close();

	std::array<int, 4> counter{0, 0, 0, 0};
	for (size_t i = 1; i < 10000; i++) {
		for (auto& r : robots) {
			r.advance();
			if (i == 100 && r.get_quad() != -1) counter[r.get_quad()]++;
		}
		save_image(robots, i, bounds);
	}

	std::print("{}\n",
	           std::ranges::fold_left(counter, 1, std::multiplies<int>()));
}
