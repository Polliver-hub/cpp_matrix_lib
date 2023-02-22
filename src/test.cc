#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor_tests, default_constructor_1) {
  S21Matrix basic;
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(Constructor_tests, default_constructor_2) {
  S21Matrix basic;
  EXPECT_ANY_THROW(basic.SetRows(2));
  EXPECT_ANY_THROW(basic.SetColumns(3));
  basic.Set(2, 3);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(Constructor_tests, copy_constructor) {
  S21Matrix basic(2, 3);
  S21Matrix result(basic);
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic == result, true);
}

TEST(Constructor_tests, move_constructor) {
  S21Matrix basic(2, 3);
  S21Matrix result(std::move(basic));
  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetColumns(), 3);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
}

TEST(Constructor_tests, parameterized_constructor) {
  S21Matrix basic(2, 3);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(Constructor_tests, parameterized_constructor_Exception) {
  EXPECT_ANY_THROW(S21Matrix exception(0, -2));
}

TEST(Getter_And_Setter, set_max) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
  basic.SetRows(4);
  basic.SetColumns(3);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(Getter_And_Setter, set_max1) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 2);
  EXPECT_EQ(basic.GetColumns(), 3);
  basic.SetRows(400);
  basic.SetColumns(300);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 400);
  EXPECT_EQ(basic.GetColumns(), 300);
}

TEST(Getter_And_Setter, set_expect) {
  S21Matrix basic;
  EXPECT_ANY_THROW(basic.SetColumns(-100));
}

TEST(Getter_And_Setter, set_expect2) {
  S21Matrix basic(1, 1);
  EXPECT_ANY_THROW(basic.SetRows(-100));
}

TEST(Getter_And_Setter, set_min) {
  S21Matrix basic(6, 7);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.GetRows(), 6);
  EXPECT_EQ(basic.GetColumns(), 7);
  basic.SetRows(4);
  basic.SetColumns(3);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.GetRows(), 4);
  EXPECT_EQ(basic.GetColumns(), 3);
}

TEST(assignmentOperator, brackets) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(assignmentOperator, brackets2) {
  S21Matrix basic;
  basic.Set(120, 1);
  EXPECT_EQ(basic(110, 0), 0);
}

TEST(assignmentOperator, brackets_Exception) {
  S21Matrix exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(functionalFuncTest, brackets_Exception2) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 0) = 5);
}

TEST(functionalFuncTest, brackets_notEq) {
  S21Matrix exception(2, 2);
  S21Matrix exception2(1, 1);
  EXPECT_EQ(exception != exception2, true);
}

TEST(functionalFuncTest, brackets_const) {
  const S21Matrix exception2(1, 1);
  EXPECT_ANY_THROW(exception2(2, 2));
}

TEST(assignmentOperator, moveConst) {
  S21Matrix basic(2, 3);
  S21Matrix basic2 = std::move(basic);
  EXPECT_EQ(basic.GetRows(), 0);
  EXPECT_EQ(basic.GetColumns(), 0);
  EXPECT_EQ(basic2.GetRows(), 2);
  EXPECT_EQ(basic2.GetColumns(), 3);
}

TEST(functionalTest, copy) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalFuncTest, determinant) {
  S21Matrix basic(4, 4);
  basic(0, 0) = 9;
  basic(0, 1) = 2;
  basic(0, 2) = 2;
  basic(0, 3) = 4;

  basic(1, 0) = 3;
  basic(1, 1) = 4;
  basic(1, 2) = 4;
  basic(1, 3) = 4;

  basic(2, 0) = 4;
  basic(2, 1) = 4;
  basic(2, 2) = 9;
  basic(2, 3) = 9;

  basic(3, 0) = 1;
  basic(3, 1) = 1;
  basic(3, 2) = 5;
  basic(3, 3) = 1;
  EXPECT_DOUBLE_EQ(basic.Determinant(), -578);
}

TEST(functionalFuncTest, determinant2) {
  S21Matrix basic(1, 1);
  basic(0, 0) = 10;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 10);
}

TEST(functionalFuncTest, determinant3) {
  S21Matrix basic(2, 2);
  basic(0, 0) = 1.1;
  basic(0, 1) = 3.5;

  basic(1, 0) = -2;
  basic(1, 1) = 4;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 11.4);
}

TEST(functionalFuncTest, determinantmatrix_0_0) {
  S21Matrix basic;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 1);
}

TEST(functionalFuncTest, determinantException) {
  S21Matrix exception(4, 3);
  EXPECT_ANY_THROW(exception.Determinant());
}

TEST(functionalFuncTest, inversematrix_) {
  S21Matrix basic(3, 3);

  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;

  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;

  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;

  basic = basic.InverseMatrix();

  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);

  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);

  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(functionalFuncTest, inversematrix_2) {
  S21Matrix basic(3, 3);

  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;

  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;

  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;

  basic = basic.InverseMatrix();

  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);

  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);

  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(functionalFuncTest, inversematrix_Exception) {
  S21Matrix exception(3, 3);

  //  determ = 0
  exception(0, 0) = 1;
  exception(0, 1) = 1;
  exception(0, 2) = 3;
  exception(1, 0) = 4;
  exception(1, 1) = 4;
  exception(1, 2) = 6;
  exception(2, 0) = 4;
  exception(2, 1) = 4;
  exception(2, 2) = 9;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inversematrix_Exception2) {
  S21Matrix exception(3, 3);

  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inversematrix_Exception3) {
  S21Matrix exception(3, 2);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, transpose) {
  S21Matrix result(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(functionalFuncTest, calc_complements) {
  S21Matrix result(2, 2);
  S21Matrix another(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(functionalFuncTest, calc_complementsException) {
  S21Matrix exception(4, 3);
  EXPECT_ANY_THROW(exception.CalcComplements());
}

TEST(functionalFuncTest, calc_complementsException2) {
  S21Matrix exception(1, 1);
  exception(0, 0) = 123.21312;
  S21Matrix exception2 = exception.CalcComplements();
  EXPECT_EQ(exception2(0, 0), 0);
}

TEST(functionalTest, operators_over) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 2;
  int num = 2;
  S21Matrix res = num * m1;
  S21Matrix res2 = m1 * num;
  S21Matrix res3 = res * res2;
  EXPECT_EQ(res(0, 0), 4);
  EXPECT_EQ(res2(0, 0), 4);
  EXPECT_EQ(res3(0, 0), 16);
}

TEST(functionalTest, plus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(functionalTest, plus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus_Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a + b);
}

TEST(functionalTest, plus_Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(functionalTest, plus_Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(functionalTest, minus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(functionalTest, minus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus_Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a + b);
}

TEST(functionalTest, minus_Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, minus_Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(functionalTest, minus_Exception4) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a - b);
}

TEST(functionalTest, multmatrix_) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  S21Matrix result = a * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_2) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_3) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_Total) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 4);
  S21Matrix res(3, 4);

  for (int i = 0, value = 0; i < a.GetRows(); i++)
    for (int j = 0; j < a.GetColumns(); j++) a(i, j) = value++;

  for (int i = 0, value = 0; i < b.GetRows(); i++)
    for (int j = 0; j < b.GetColumns(); j++) b(i, j) = value++;

  res(0, 0) = 4, res(0, 1) = 5, res(0, 2) = 6, res(0, 3) = 7;
  res(1, 0) = 12, res(1, 1) = 17, res(1, 2) = 22, res(1, 3) = 27;
  res(2, 0) = 20, res(2, 1) = 29, res(2, 2) = 38, res(2, 3) = 47;

  S21Matrix answer = a * b;
  EXPECT_TRUE(res == answer);
}

TEST(functionalTest, multmatrix__Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a * b);
}

TEST(functionalTest, multmatrix__Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(functionalTest, multmatrix__Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(functionalTest, multmatrix_Num) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  S21Matrix result = a * 2;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_Num2) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_Num3) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, multmatrix_Num4) {
  S21Matrix a(3, 2);
  a.MulNumber(NAN);
  EXPECT_EQ(std::isnan(a(1, 1)), 1);
  EXPECT_EQ(std::isnan(a(2, 1)), 1);
  EXPECT_EQ(std::isnan(a(1, 0)), 1);
}

TEST(functionalTest, equal) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.SetRows(2);
  b.SetColumns(3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(functionalTest, equal2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
