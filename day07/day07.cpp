#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "../lib/common.h"

typedef std::vector<long> vec;

vec parse(std::string& line) {
	std::erase(line, ':');
	return string_to_vector(line);
}

bool is_concatenable(long N, long n) {
	return std::to_string(N).ends_with(std::to_string(n)) && N != n;
}
bool is_divisible(long N, long n) { return N % n == 0; }
bool is_addable(long N, long n) { return N - n > 0; }

long inverse_concat(long N, long n) {
	if (!is_concatenable(N, n)) return N;
	std::string temp = std::to_string(N);
	temp = temp.substr(0, temp.length() - std::to_string(n).length());
	return std::stol(temp);
}

bool valid(vec v, bool do_conc = false) {
	if (v.size() == 2) {
		return v[0] == v[1];
	}

	bool retval = false;
	if (is_concatenable(v.front(), v.back()) && do_conc) {
		vec newvec(v);
		newvec.front() = inverse_concat(newvec.front(), newvec.back());
		newvec.pop_back();
		retval = retval || valid(newvec, do_conc);
	}
	if (is_divisible(v.front(), v.back())) {
		vec newvec(v);
		newvec.front() /= newvec.back();
		newvec.pop_back();
		retval = retval || valid(newvec, do_conc);
	}
	if (is_addable(v.front(), v.back())) {
		vec newvec(v);
		newvec.front() -= newvec.back();
		newvec.pop_back();
		retval = retval || valid(newvec, do_conc);
	}
	return retval;
}

int main(int argc, char** argv) {
	std::ifstream input(argc > 1 ? argv[1] : "input.txt");
	long ctr = 0;
	for (std::string temp; getline(input, temp);) {
		vec data = parse(temp);
		if (valid(data, true)) ctr += data.front();
	}
	std::print("{}\n", ctr);
}
