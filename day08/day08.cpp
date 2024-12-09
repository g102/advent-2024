#include <set>

#include "common.h"

typedef std::pair<long, long> point;
point operator+(const point& lhs, const point& rhs) {
	return {lhs.first + rhs.first, lhs.second + rhs.second};
}
point operator*(const int lhs, const point& rhs) {
	return {lhs * rhs.first, lhs * rhs.second};
}
point operator-(const point& lhs, const point& rhs) {
	return lhs + (-1 * rhs);
}
point operator%(const point& lhs, int rhs) {
	return {lhs.first % rhs, lhs.second % rhs};
}
point operator/(const point& lhs, int rhs) {
	return {lhs.first / rhs, lhs.second / rhs};
}
bool operator==(const point& lhs, int rhs) {
	return lhs.first == rhs && lhs.second == rhs;
}

point to_point(long ix, size_t r, size_t c) { return {ix / c, ix % c}; }
size_t to_index(point p, size_t r, size_t c) { return p.first * c + p.second; }

void get_anodes(long ix0, long ix1, long r, long c, std::set<long>& cont) {
	auto in_bounds = [&](point p) {
		auto [x, y] = p;
		return 0 <= x && x < r && 0 <= y && y < c;
	};

	point p0 = to_point(ix0, r, c);
	point p1 = to_point(ix1, r, c);
	point temp, diff = p1 - p0;

	temp = 2 * p0 - p1;
	if (in_bounds(temp)) cont.insert(to_index(temp, r, c));

	temp = 2 * p1 - p0;
	if (in_bounds(temp)) cont.insert(to_index(temp, r, c));

	if (diff % 3 == 0) {
		diff = diff / 3;
		temp = p0 + diff;
		if (in_bounds(temp)) cont.insert(to_index(temp, r, c));

		temp = p0 - diff;
		if (in_bounds(temp)) cont.insert(to_index(temp, r, c));
	}
}

void get_resonant(long ix0, long ix1, long r, long c, std::set<long>& cont) {
	auto in_bounds = [&](point p) {
		auto [x, y] = p;
		return 0 <= x && x < r && 0 <= y && y < c;
	};

	point p0 = to_point(ix0, r, c);
	point p1 = to_point(ix1, r, c);
	point temp, diff = p1 - p0;

	// away from x0
	temp = p0;
	while (true) {
		temp = temp + diff;
		if (!in_bounds(temp)) break;
		cont.insert(to_index(temp, r, c));
	}

	// away from x1
	temp = p1;
	while (true) {
		temp = temp - diff;
		if (!in_bounds(temp)) break;
		cont.insert(to_index(temp, r, c));
	}
}

int main(int argc, char** argv) {
	std::string fname_in = argc > 1 ? argv[1] : "input.txt";
	auto [text, rows, cols] = read_clean(fname_in);

	// find all antennas
	std::vector<std::pair<long, char>> ants;
	for (size_t ix = 0; true; ix++) {
		ix = text.find_first_not_of('.', ix);
		if (ix == text.npos) break;
		ants.push_back({ix, text[ix]});
	}

	// find all anti-nodes
	std::set<long> anodes;
	for (auto it0 = ants.begin(); it0 != ants.end(); it0++) {
		for (auto it1 = it0 + 1; it1 != ants.end(); it1++) {
			if (it0->second != it1->second) continue;
			get_anodes(it0->first, it1->first, rows, cols, anodes);
		}
	}
	std::print("{}, ", anodes.size());

	// add all resonant nodes
	for (auto it0 = ants.begin(); it0 != ants.end(); it0++) {
		for (auto it1 = it0 + 1; it1 != ants.end(); it1++) {
			if (it0->second != it1->second) continue;
			get_resonant(it0->first, it1->first, rows, cols, anodes);
		}
	}
	std::print("{}\n", anodes.size());
}
