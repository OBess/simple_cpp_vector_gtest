// All unit-test.
//----------------------------------------------------------

// Google test.
#include <gtest/gtest.h>

// The class under test.
#include "include/c_vector.hpp"

//----------------------------Tests

TEST(CustomVector, DefaultConstructor)
{
   c_vector<int> c;

   ASSERT_EQ(10, c.capacity());
}

TEST(CustomVector, AllocationConstructor)
{
   c_vector<int> c(25);

   ASSERT_EQ(30, c.capacity());
   ASSERT_EQ(0, c.back());
}

TEST(CustomVector, CopyConstructorAndFrontBack)
{
   c_vector c{25, 4, 6, 21, 65, -34, 65};
   c_vector c1(c);

   ASSERT_EQ(25, c.front());
   ASSERT_EQ(65, c.back());

   ASSERT_EQ(c.front(), c1.front());
   ASSERT_EQ(c.back(), c1.back());
}

TEST(CustomVector, MoveSemantic)
{
   c_vector c({25, 4, 6, 21, 65, -34, 65});

   ASSERT_EQ(25, c.front());
   ASSERT_EQ(65, c.back());
}

TEST(CustomVector, IndexOperator)
{
   c_vector<int> c{25, 4, 6, 21, 65, -34, 65};

   ASSERT_EQ(25, c[0]);
   ASSERT_EQ(65, c[c.size() - 1]);
   ASSERT_NO_THROW(c[c.size()]);
}

TEST(CustomVector, PushPopBack)
{
   c_vector c = {25, 4, 6, 21, 65, -34, 65};
   c.pop_back();
   c.push_back(45);
   c.pop_back();
   c.pop_back();

   ASSERT_EQ(65, c.back());
}

TEST(CustomVector, Resize)
{
   c_vector c{25, 4, 6, 21, 65, -34, 65};
   
   c.resize(4);
   ASSERT_EQ(21, c.back());

   c.resize(10, 100);
   ASSERT_EQ(100, c.back());

   c.resize(12);
   ASSERT_EQ(0, c.back());
}

//----------------------------~Tests

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}