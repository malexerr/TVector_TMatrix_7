#include "gtest.h"
#include "tdynamicvector.h"

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(5);
  ASSERT_NO_THROW(TDynamicVector<int> copy(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source)
{
  TDynamicVector<int> v1(4);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v1[3] = 4;

  TDynamicVector<int> v2(v1);
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_own_memory)
{
  TDynamicVector<int> v1(3);
  v1[0] = 10;
  v1[1] = 20;
  v1[2] = 30;

  TDynamicVector<int> v2(v1);
  v2[1] = 99;

  EXPECT_NE(v1[1], v2[1]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(7);
  EXPECT_EQ(7, v.GetSize());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[2] = 55;
  EXPECT_EQ(55, v[2]);
}

TEST(TDynamicVector, throws_when_index_is_out_of_range)
{
  TDynamicVector<int> v(3);
  ASSERT_ANY_THROW(v[-1]);
  ASSERT_ANY_THROW(v[5]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(5);
  ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_same_size)
{
  TDynamicVector<int> v1(3);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  TDynamicVector<int> v2(3);
  v2[0] = 4;
  v2[1] = 5;
  v2[2] = 6;

  ASSERT_NO_THROW(v1 = v2);
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_changes_vector_size_if_needed)
{
  TDynamicVector<int> v1(2);
  TDynamicVector<int> v2(4);

  ASSERT_NO_THROW(v1 = v2);
  EXPECT_EQ(v1.GetSize(), 4);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(3);
  v1[0] = 1; v1[1] = 2; v1[2] = 3;

  TDynamicVector<int> v2(3);
  v2[0] = 1; v2[1] = 2; v2[2] = 3;

  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(4);
  EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> res = v + 10;

  EXPECT_EQ(11, res[0]);
  EXPECT_EQ(12, res[1]);
  EXPECT_EQ(13, res[2]);
}

TEST(TDynamicVector, can_subtract_scalar)
{
  TDynamicVector<int> v(3);
  v[0] = 5; v[1] = 6; v[2] = 7;

  TDynamicVector<int> res = v - 1;

  EXPECT_EQ(4, res[0]);
  EXPECT_EQ(5, res[1]);
  EXPECT_EQ(6, res[2]);
}

TEST(TDynamicVector, can_multiply_by_scalar)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> res = v * 2;

  EXPECT_EQ(2, res[0]);
  EXPECT_EQ(4, res[1]);
  EXPECT_EQ(6, res[2]);
}

TEST(TDynamicVector, can_add_vectors_of_same_size)
{
  TDynamicVector<int> a(3);
  TDynamicVector<int> b(3);

  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 3; b[1] = 2; b[2] = 1;

  TDynamicVector<int> c = a + b;

  EXPECT_EQ(4, c[0]);
  EXPECT_EQ(4, c[1]);
  EXPECT_EQ(4, c[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_different_size)
{
  TDynamicVector<int> a(3);
  TDynamicVector<int> b(4);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_of_same_size)
{
  TDynamicVector<int> a(3);
  TDynamicVector<int> b(3);

  a[0] = 5; a[1] = 4; a[2] = 3;
  b[0] = 1; b[1] = 1; b[2] = 1;

  TDynamicVector<int> c = a - b;

  EXPECT_EQ(4, c[0]);
  EXPECT_EQ(3, c[1]);
  EXPECT_EQ(2, c[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_different_size)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(3);
  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_calculate_scalar_product)
{
  TDynamicVector<int> a(3);
  TDynamicVector<int> b(3);

  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;

  EXPECT_EQ(32, a * b);
}

TEST(TDynamicVector, cant_calculate_scalar_product_for_different_size)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(3);
  ASSERT_ANY_THROW(a * b);
}
