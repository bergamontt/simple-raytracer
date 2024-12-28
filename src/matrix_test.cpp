#include "gtest/gtest.h"
#include "matrix.h"
#include "func.h"

TEST(MatrixTest, MatrixCreation)
{
	Matrix m(4, 4);
	m.set(0, 0, 1.0f);
	m.set(0, 3, 4.0f);
	m.set(1, 0, 5.5f);
	m.set(1, 2, 7.5f);
	m.set(2, 2, 11.0f);
	m.set(3, 0, 13.5f);
	ASSERT_EQ(m.get(0, 0), 1.0f);
	ASSERT_EQ(m.get(0, 3), 4.0f);
	ASSERT_EQ(m.get(1, 2), 7.5f);
}

TEST(MatrixTest, SameMatrixComparison)
{
	Matrix a(2, 2);
	Matrix b(2, 2);
	a.set(0, 0, 1.0f);
	a.set(0, 1, 2.0f);
	a.set(1, 0, 3.0f);
	a.set(1, 1, 4.0f);
	b.set(0, 0, 1.0f);
	b.set(0, 1, 2.0f);
	b.set(1, 0, 3.0f);
	b.set(1, 1, 4.0f);
	ASSERT_TRUE(a == b);
	ASSERT_FALSE(a != b);
}

TEST(MatrixTest, DiffMatrixComparison)
{
	Matrix a(2, 2);
	Matrix b(2, 2);
	a.set(1, 1, 1.0f);
	b.set(0, 1, 2.2f);
	ASSERT_FALSE(a == b);
	ASSERT_TRUE(a != b);
}

TEST(MatrixTest, IndentityMatrixMultiply)
{
	Matrix a(2, 2);
	a.set(1, 1, 3.3f);
	a.set(0, 1, 2.3f);
	Matrix res = a * Matrix::indentityMatrix(2);
	ASSERT_TRUE(res == a);
}

TEST(MatrixTest, TransposingMatrix)
{
	Matrix a(2, 2);
	a.set(0, 1, 2.0f);
	a.set(1, 0, 3.0f);
	Matrix tra = a.transpose();
	ASSERT_TRUE(tra.get(0, 1) == 3.0f);
	ASSERT_TRUE(tra.get(1, 0) == 2.0f);
}

TEST(MatrixTest, TransposingIndentityMatrix)
{
	Matrix ind = Matrix::indentityMatrix(4);
	Matrix trind = ind.transpose();
	ASSERT_TRUE(ind == trind);
}

TEST(MatrixTest, Submatrix3x3)
{
	float arr[] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
	Matrix m(arr, 3);
	Matrix subm = m.submatrix(0, 2);
	float arr1[] = { -3, 2, 0, 6 };
	Matrix res(arr1, 2);
	ASSERT_EQ(subm, res);
}

TEST(MatrixTest, Submatrix4x4)
{
	float arr[]{ -2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9 };
	Matrix a(arr, 4);
	Matrix suba = a.submatrix(0, 0);
	float arr1[] = { 1, 7, 3, 2, -9, 6, 7, 7, -9 };
	Matrix suppRes(arr1, 3);
	ASSERT_EQ(suppRes, suba);
}

TEST(MatrixTest, CalculatingMinor)
{
	float arr[]{ 3, 5, 0, 2, -1, -7, 6, -1, 5 };
	Matrix a(arr, 3);
	Matrix suba = a.submatrix(1, 0);
	ASSERT_TRUE(suba.determinant() == 25);
}

TEST(MatrixTest, CalculatingCofactor)
{
	float arr[]{ 3, 5, 0, 2, -1, -7, 6, -1, 5 };
	Matrix a(arr, 3);
	ASSERT_FLOAT_EQ(a.minor(0, 0), -12);
	ASSERT_FLOAT_EQ(a.cofactor(0, 0), -12);
	ASSERT_FLOAT_EQ(a.minor(1, 0), 25);
	ASSERT_FLOAT_EQ(a.cofactor(1, 0), -25);
}

TEST(MatrixTest, Determinant3x3)
{
	float arr[]{ 1, 2, 6, -5, 8, -4, 2, 6, 4 };
	Matrix a(arr, 3);
	ASSERT_FLOAT_EQ(a.cofactor(0, 0), 56);
	ASSERT_FLOAT_EQ(a.cofactor(0, 1), 12);
	ASSERT_FLOAT_EQ(a.cofactor(0, 2), -46);
	ASSERT_FLOAT_EQ(a.determinant(), -196);
}

TEST(MatrixTest, Determinant4x4)
{
	float arr[]{ -2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9 };
	Matrix a(arr, 4);
	ASSERT_FLOAT_EQ(a.cofactor(0, 0), 690);
	ASSERT_FLOAT_EQ(a.cofactor(0, 1), 447);
	ASSERT_FLOAT_EQ(a.cofactor(0, 2), 210);
	ASSERT_FLOAT_EQ(a.cofactor(0, 3), 51);
	ASSERT_FLOAT_EQ(a.determinant(), -4071);
}

TEST(MatrixTest, InvertibleMatrix)
{
	float arr[]{ 6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6 };
	Matrix a(arr, 4);
	ASSERT_FLOAT_EQ(a.determinant(), -2120);
	ASSERT_TRUE(a.invertible());
}

TEST(MatrixTest, NonIvertibleMatrix)
{
	float arr[]{ -4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0 };
	Matrix a(arr, 4);
	ASSERT_FLOAT_EQ(a.determinant(), 0);
	ASSERT_FALSE(a.invertible());
}

TEST(MatrixTest, InverseMatrix1)
{
	float arr[]{ 8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4 };
	Matrix a(arr, 4);
	float arr1[]{ -0.15385, -0.15385, -0.28205, -0.53846,
				  -0.07692, 0.12308, 0.02564, 0.03077,
				   0.35897,  0.35897, 0.43590, 0.92308,
				  -0.69231, -0.69231, -0.76923, -1.92308 };
	Matrix res(arr1, 4);
	Matrix inva = a.inverse();
	ASSERT_EQ(res, inva);
}

TEST(MatrixTest, InverseMatrix2)
{
	float arr[]{9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
	Matrix a(arr, 4);
	float arr1[]{ -0.04074, -0.07778, 0.14444, -0.22222,
				  -0.07778, 0.03333, 0.36667, -0.33333,
				  -0.02901, -0.14630, -0.10926, 0.12963,
				   0.17778, 0.06667, -0.26667, 0.33333 };
	Matrix res(arr1, 4);
	Matrix inva = a.inverse();
	ASSERT_EQ(res, inva);
}

TEST(MatrixTest, MultiplyingProductByInverse)
{
	float arr[]{ 3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1 };
	Matrix a(arr, 4);
	float arr1[]{ 8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5 };
	Matrix b(arr1, 4);
	Matrix product = a * b;
	ASSERT_EQ(product * b.inverse(), a);
}