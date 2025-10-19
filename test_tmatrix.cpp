#include "gtest.h"
#include "tdynamicmatrix.h"

TEST(TDynamicMatrix, can_create_matrix_with_positive_size)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_size)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-3));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(4);
  ASSERT_NO_THROW(TDynamicMatrix<int> copy(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source)
{
  TDynamicMatrix<int> m1(3);
  m1[0][0] = 1;
  m1[1][1] = 2;
  m1[2][2] = 3;

  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_own_memory)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 10;
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 99;

  EXPECT_NE(m1[0][0], m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(6);
  EXPECT_EQ(6, m.GetSize());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 42;
  EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_index_out_of_range)
{
  TDynamicMatrix<int> m(3);
  ASSERT_ANY_THROW(m[-1][0]);
  ASSERT_ANY_THROW(m[0][5]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(3);

  m1[0][0] = 5;
  m2[0][0] = 10;

  ASSERT_NO_THROW(m1 = m2);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_changes_matrix_size_if_needed)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(5);

  ASSERT_NO_THROW(m1 = m2);
  EXPECT_EQ(5, m1.GetSize());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(3);

  m1[1][1] = 7;
  m2[1][1] = 7;

  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(4);
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(4);
  EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);

  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;

  b[0][0] = 4; b[0][1] = 3;
  b[1][0] = 2; b[1][1] = 1;

  TDynamicMatrix<int> c = a + b;

  EXPECT_EQ(5, c[0][0]);
  EXPECT_EQ(5, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_different_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(3);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);

  a[0][0] = 5; a[1][1] = 7;
  b[0][0] = 1; b[1][1] = 3;

  TDynamicMatrix<int> c = a - b;

  EXPECT_EQ(4, c[0][0]);
  EXPECT_EQ(4, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_different_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(4);
  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  TDynamicMatrix<int> res = m * 2;

  EXPECT_EQ(2, res[0][0]);
  EXPECT_EQ(8, res[1][1]);
}

TEST(TDynamicMatrix, can_add_scalar_to_matrix)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[1][1] = 2;

  TDynamicMatrix<int> res = m + 3;

  EXPECT_EQ(4, res[0][0]);
  EXPECT_EQ(5, res[1][1]);
}

TEST(TDynamicMatrix, can_subtract_scalar_from_matrix)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 5; m[1][1] = 4;

  TDynamicMatrix<int> res = m - 2;

  EXPECT_EQ(3, res[0][0]);
  EXPECT_EQ(2, res[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);

  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;

  b[0][0] = 2; b[0][1] = 0;
  b[1][0] = 1; b[1][1] = 2;

  TDynamicMatrix<int> c = a * b;

  EXPECT_EQ(4, c[0][0]);
  EXPECT_EQ(4, c[0][1]);
  EXPECT_EQ(10, c[1][0]);
  EXPECT_EQ(8, c[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_different_size)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(3);
  ASSERT_ANY_THROW(a * b);
}
