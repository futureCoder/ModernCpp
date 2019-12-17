#pragma once

typedef struct {
	float* data;
	size_t nrows;
	size_t ncols;
} matrix;


enum matrix_err_code {
	MATRIX_SUCCESS,
	MATRIX_ERR_MEMORY_INSUFFICIENT,
	MATRIX_ERR_MISMATCHED_MATRIX_SIZE,
};



class CMatrix {
public:
	CMatrix(size_t nrows, size_t ncols);
	~CMatrix();
	friend CMatrix operator*(const CMatrix& lhs, const CMatrix& rhs);

	float* data_;
	size_t nrows_;
	size_t ncols_;
};

CMatrix operator*(const CMatrix& lhs, const CMatrix& rhs);