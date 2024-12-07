#include "Matrix.h"

Matrix::Matrix(std::string _s) : data(_s), shape(2, 0), stride(2, 0) {
	if (data.back() != '\n') {
		data.append(1, '\n');
	}

	shape[0] = std::ranges::count(data, '\n');
	shape[1] = data.length() / shape[0] - 1;

	stride[0] = shape[1];
	stride[1] = 1;

	std::erase(data, '\n');
}

void Matrix::transpose() {
	std::swap(stride[0], stride[1]);
	std::swap(shape[0], shape[1]);
}

void Matrix::print() {
	for (size_t ix = 0; ix < shape[0]; ix++) {
		std::print("{}\n", std::ranges::to<std::string>((*this).row(ix)));
	}
}
