#include <set>

#include "common.h"

typedef std::tuple<long, long> point;

point to_point(long idx, size_t row, size_t col) {
	return {idx / col, idx % col};
}
size_t to_index(point sub, size_t r, size_t c) {
	return std::get<0>(sub) * c + std::get<1>(sub);
}

void get_anodes(long ix0, long ix1, long r, long c, std::set<long>& cont) {
	auto checker = [&](long x, long y) {
		return 0 <= x && x < r && 0 <= y && y < c;
	};

	long xt, yt;  // temps;
	auto [x0, y0] = to_point(ix0, r, c);
	auto [x1, y1] = to_point(ix1, r, c);

	xt = 2 * x0 - x1, yt = 2 * y0 - y1;
	if (checker(xt, yt)) cont.insert(to_index({xt, yt}, r, c));

	xt = 2 * x1 - x0, yt = 2 * y1 - y0;
	if (checker(xt, yt)) cont.insert(to_index({xt, yt}, r, c));

	if ((x1 - x0) % 3 == 0 && (y1 - y0) % 3 == 0) {
		long dx = (x1 - x0) / 3, dy = (y1 - y0) / 3;

		xt = x0 + dx, yt = y0 + dy;
		if (checker(xt, yt)) cont.insert(to_index({xt, yt}, r, c));

		xt = x1 - dx, yt = y1 - dy;
		if (checker(xt, yt)) cont.insert(to_index({xt, yt}, r, c));
	}
}

void get_resonant(long ix0, long ix1, long r, long c, std::set<long>& cont) {
	auto checker = [&](long x, long y) {
		return 0 <= x && x < r && 0 <= y && y < c;
	};

	auto [x0, y0] = to_point(ix0, r, c);
	auto [x1, y1] = to_point(ix1, r, c);

	long dx = x1 - x0, dy = y1 - y0, xt, yt;

	// away from x0
	xt = x0, yt = y0;
	while (true) {
		xt += dx, yt += dy;
		if (!checker(xt, yt)) break;
		cont.insert(to_index({xt, yt}, r, c));
	}

	// away from x1
	xt = x1, yt = y1;
	while (true) {
		xt -= dx, yt -= dy;
		if (!checker(xt, yt)) break;
		cont.insert(to_index({xt, yt}, r, c));
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
