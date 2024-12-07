#ifndef AOC_MATRIX
#define AOC_MATRIX

#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <vector>

struct Matrix {
	std::string data;
	std::vector<size_t> shape, stride;

	Matrix(std::string);
	void transpose();
	void print();

	auto row(size_t ix) {
		return data | std::views::drop(ix * stride[0]) |
		       std::views::stride(stride[1]) | std::views::take(shape[1]);
	}

	auto col(size_t ix) {
		return data | std::views::drop(ix * stride[1]) |
		       std::views::stride(stride[0]) | std::views::take(shape[0]);
	}

	auto rows() { return shape[0]; }
	auto cols() { return shape[1]; }

	std::vector<size_t> ix2sub(size_t ix) {
		return {ix / shape[1], ix % shape[1]};
	}
	size_t sub2ix(std::vector<size_t> sub) {
		return sub[0] * shape[1] + sub[1];
	}

	auto& operator[](size_t ix) { return data[ix]; }
	auto& operator()(std::vector<size_t> sub) { return data[sub2ix(sub)]; }
	auto& operator()(size_t i0, size_t i1) { return data[sub2ix({i0, i1})]; }
};

#endif
