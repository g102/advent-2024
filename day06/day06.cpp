#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

#include "../lib/Matrix.h"
#include "../lib/common.h"

std::map<ssize_t, std::vector<ssize_t>> rules{
	{0, {-1, 0}}, {1, {0, 1}}, {2, {1, 0}}, {3, {0, -1}}};

inline bool in(const std::ranges::range auto& container, const auto& item) {
	return std::ranges::find(container, item) != container.end();
}

struct Player {
	Matrix& world;
	ssize_t row, col, dir;
	std::vector<std::vector<ssize_t>> history;

	Player(Matrix& _w) : world(_w) {
		auto it = world.data.find('^');
		row = world.ix2sub(it)[0];
		col = world.ix2sub(it)[1];
		dir = 0;
	}

	int advance() {
		history.push_back({row, col, dir});

		while (true) {
			auto newrow = row + rules[dir][0];
			auto newcol = col + rules[dir][1];

			if (newrow < 0 || newcol < 0) {
				return 1;  // exited from top or left
			}

			if (newrow >= static_cast<ssize_t>(world.rows()) ||
			    newcol >= static_cast<ssize_t>(world.cols())) {
				return 1;  // exited from bottom or right
			}

			if (world(newrow, newcol) == '#') {
				dir = (dir + 1) % 4;  // ran into a wall, turning
			} else {
				break;
			}
		}

		row = row + rules[dir][0];
		col = col + rules[dir][1];

		if (in(history, std::vector{row, col, dir})) {
			return 2;  // we were already on this tile facing this dir, looping!
		}

		return 0;  // 0: still going
	}

	bool loops() {
		while (true) {
			auto state = advance();
			if (state == 1) return false;
			if (state == 2) return true;
		}
	}

	long how_many_unique() {
		std::set<std::vector<ssize_t>> uniq;
		for (auto v : history) {
			uniq.insert(std::vector{v[0], v[1]});
		}
		return uniq.size();
	}
};

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "test.txt"};
	Matrix world(readall(input));
	input.close();

	// part 1, smooth
	Player p(world);
	p.loops();
	std::print("{}, ", p.how_many_unique());

	// part 2, bruteforce
	long ctr{0};
	for (size_t ix = 0; ix < world.data.size(); ix++) {
		char prev = world[ix];
		if (prev != '.') continue;
		world[ix] = '#';

		Player ghost(world);
		if (ghost.loops()) {
			ctr++;
		}

		world[ix] = prev;
	}
	std::print("{}\n", ctr);
}
