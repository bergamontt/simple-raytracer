#pragma once
#include "tuple.h"

class Matrix
{
public:

	Matrix(int row, int col)
		: _rows{ row }
		, _cols{ col }
		, _matrix{ new float* [row] }
	{
		initMatrix();
	}

	Matrix(const float matrix[], int n)
		: _rows{ n }
		, _cols{ n }
		, _matrix{ new float* [n] }
	{
		for (int i = 0; i < _rows; ++i)
		{
			_matrix[i] = new float[_cols]();
			for (int j = 0; j < _cols; ++j)
				_matrix[i][j] = matrix[(i * _cols) + j];
		}
	}

	Matrix()
		: Matrix(Matrix::indentityMatrix(TRANSFORM_N))
	{}

	Matrix(const Matrix& src)
	{
		deepCopy(src);
	}

	~Matrix();

	Matrix& operator=(const Matrix& src);

	float get(int row, int col) const;
	void set(int row, int col, float value);

	int rows() const;
	int columns() const;

	const Matrix transpose() const;

	bool invertible() const;
	const Matrix inverse() const;

	float determinant() const;
	const Matrix submatrix(int row, int col) const;
	float minor(int row, int col) const;
	float cofactor(int row, int col) const;

	static const Matrix indentityMatrix(int n);

private:

	int _rows;
	int _cols;
	float** _matrix;

	void destroy();
	void initMatrix();
	void deepCopy(const Matrix& src);

};

bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);

const Matrix operator*(const Matrix& a, const Matrix& b);
const Tuple  operator*(const Matrix& a, const Tuple& b);