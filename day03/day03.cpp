#include <fstream>
#include <print>
#include <regex>
#include <sstream>
#include <string>

#include "../lib/common.h"

typedef std::regex_iterator<std::string_view::iterator> sv_iter;

int parse_mul(std::string_view sv) {
	// parses all occurrences of mul(x,y) and returns the sums of all x * y
	// discarding if x and y have more than three digits
	// ignores do() and don't() instructions.

	std::regex r{"mul\\((\\d{0,3}),(\\d{0,3})\\)"};
	sv_iter matcher{sv.begin(), sv.end(), r};

	int counter = 0;
	for (sv_iter it = matcher; it != sv_iter{}; it++) {
		int n1 = std::stoi((*it)[1].str());
		int n2 = std::stoi((*it)[2].str());
		counter += n1 * n2;
	}
	return counter;
}

std::string do_remover(std::string_view sv) {
	// removes all text between a do() and a don't() instruction

	std::regex r{"don't\\(\\)(.|\\n)*?do\\(\\)"};
	sv_iter matcher{sv.begin(), sv.end(), r};

	if (matcher == sv_iter{}) {
		// there are no matches, return the original string
		return std::string{sv};
	} else {
		// iteratively, remove the bit between do() and don't() and repeat
		std::string out{""};
		out.append(matcher->prefix().str());
		out.append(matcher->suffix().str());
		return do_remover(out);
	}
}

int main(int argc, char** argv) {
	std::ifstream input{argc > 1 ? argv[1] : "input.txt"};
	std::string text{readall(input)};
	input.close();

	std::print("{}\n", parse_mul(text));

	std::print("{}\n", parse_mul(do_remover(text)));
}
