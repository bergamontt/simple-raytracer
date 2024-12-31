#include "matrix.h"
#include "func.h"

Matrix::~Matrix()
{
	destroy();
	_rows = 0;
	_cols = 0;
}

Matrix& Matrix::operator=(const Matrix& src)
{
	if (this != &src)
		deepCopy(src);
	return *this;
}

float Matrix::get(int row, int col) const
{
	return _matrix[row][col];
}

void Matrix::set(int row, int col, float value)
{
	_matrix[row][col] = value;
}

int Matrix::rows() const
{
	return _rows;
}

int Matrix::columns() const
{
	return _cols;
}

const Matrix Matrix::indentityMatrix(int n)
{
	Matrix indMatrix(n, n);
	for (int i = 0; i < n; ++i)
		indMatrix.set(i, i, 1.0);
	return indMatrix;
}

void Matrix::destroy()
{
	if (_matrix == nullptr)
		return;
	for (int i = 0; i < _rows; ++i)
		delete[] _matrix[i];
	delete[] _matrix;
}

void Matrix::initMatrix()
{
	for (int i = 0; i < _rows; ++i)
		_matrix[i] = new float[_cols]();
}

void Matrix::deepCopy(const Matrix& src)
{
	_rows = src._rows;
	_cols = src._cols;

	_matrix = new float* [_rows];
	initMatrix();

	for (int row = 0; row < _rows; ++row)
		for (int col = 0; col < _cols; ++col)
			_matrix[row][col] = src._matrix[row][col];
}

const Matrix Matrix::transpose() const
{
	Matrix result(_rows, _cols);
	for (int i = 0; i < _rows; ++i)
		for (int j = 0; j < _cols; ++j)
			result.set(i, j, _matrix[j][i]);
	return result;
}

bool Matrix::invertible() const
{
	return !equalDouble(determinant(), 0.0);
}

const Matrix Matrix::inverse() const
{
	Matrix inversed(_rows, _cols);
	for (int row = 0; row < _rows; ++row)
		for (int col = 0; col < _cols; ++col)
		{
			float cf = cofactor(row, col);
			inversed.set(col, row, cf / determinant());
		}
	return inversed;
}

float Matrix::determinant() const
{
	if (_rows == 2)
		return _matrix[0][0] * _matrix[1][1] - _matrix[1][0] * _matrix[0][1];
	float determinant = 0;
	for (int col = 0; col < _rows; ++col)
		determinant += _matrix[0][col] * cofactor(0, col);
	return determinant;
}

const Matrix Matrix::submatrix(int removedRow, int removedCol) const
{
	Matrix submatrix(_rows - 1, _cols - 1);
	for (int subRow = 0, row = 0; row < _rows && subRow < _rows - 1; ++subRow, ++row)
	{
		if (row == removedRow)
			++row;
		for (int subCol = 0, col = 0; row < _cols && subCol < _cols - 1; ++subCol, ++col)
		{
			if (col == removedCol)
				++col;
			submatrix.set(subRow, subCol, _matrix[row][col]);
		}
	}
	return submatrix;
}

float Matrix::minor(int row, int col) const
{
	Matrix sub = submatrix(row, col);
	return sub.determinant();
}

float Matrix::cofactor(int row, int col) const
{
	if ((row + col) % 2 == 1)
		return -minor(row, col);
	return minor(row, col);
}

bool operator==(const Matrix& a, const Matrix& b)
{
	if (a.rows() != b.rows() || a.columns() != b.columns())
		return false;

	for (int i = 0; i < a.rows(); ++i)
		for (int j = 0; j < a.columns(); ++j)
			if (!equalDouble(a.get(i, j), b.get(i, j)))
				return false;

	return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
	return !(a == b);
}

const Matrix operator*(const Matrix& a, const Matrix& b)
{
	Matrix result(a.rows(), b.columns());
	for(int i = 0; i < a.rows(); ++i)
	{
		for (int j = 0; j < b.columns(); ++j)
		{
			float sum = 0.0;
			for (int k = 0; k < a.columns(); ++k)
				sum += a.get(i, k) * b.get(k, j);
			result.set(i, j, sum);
		}
	}
	return result;
}

const Tuple operator*(const Matrix& a, const Tuple& b)
{
	return { a.get(0, 0) * b._x + a.get(0, 1) * b._y + a.get(0, 2) * b._z + a.get(0, 3) * b._w,
			 a.get(1, 0) * b._x + a.get(1, 1) * b._y + a.get(1, 2) * b._z + a.get(1, 3) * b._w,
			 a.get(2, 0) * b._x + a.get(2, 1) * b._y + a.get(2, 2) * b._z + a.get(2, 3) * b._w,
			 a.get(3, 0) * b._x + a.get(3, 1) * b._y + a.get(3, 2) * b._z + a.get(3, 3) * b._w };
}
