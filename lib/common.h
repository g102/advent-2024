#ifndef AOC24_COMMON_H
#define AOC24_COMMON_H

#include <algorithm>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

std::string readall(std::ifstream&);
std::tuple<std::string, std::size_t, std::size_t> read_clean(std::string&);
std::vector<long> string_to_vector(std::string&);

#endif
