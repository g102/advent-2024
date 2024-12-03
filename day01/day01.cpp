#include <algorithm>
#include <fstream>
#include <print>
#include <vector>

size_t how_often(int x, const std::ranges::range auto& v) {
	return std::count(std::begin(v), std::end(v), x);
}

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "input.txt"};
	std::vector<int> list1, list2;
	
	for (int t1, t2; input >> t1 >> t2; ) {
		list1.push_back(t1);
		list2.push_back(t2);
	}
	input.close();

	std::ranges::sort(list1);
	std::ranges::sort(list2);

	int ctr_pt1 = 0, ctr_pt2 = 0;
	for (size_t ix = 0; ix < list1.size(); ix++) {
		ctr_pt1 += std::abs(list1[ix] - list2[ix]);
		ctr_pt2 += list1[ix] * how_often(list1[ix], list2);
	}
	std::print("{}, {}\n", ctr_pt1, ctr_pt2);
}
