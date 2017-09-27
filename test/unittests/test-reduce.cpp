
#include "gtest/gtest.h"

#include <vector>

#include "range.h"
#include "reduce.h"


using namespace gen;


TEST(ReduceTest, Constexpr1)
{
	//static_assert(reduce(range(5)) == reduce(range(5)), "");

	static_assert(std::plus<int>()(1, 1) == std::plus<int>()(1, 1), "");

	//assert(std::plus(1, 1) == std::plus(1, 1), "");

	EXPECT_EQ(std::plus<int>()(1, 1), std::plus<int>()(1, 1));

	EXPECT_EQ(5, 5);
}

//////////////////////////////////
//
//		
//			Reduce
//		Tests for Reduce class
//
//
/////////////////////////////////

TEST(ReduceTest, ValueFirst)
{
	int v = 0;
	for (auto i : reduce(range(5)))
	{
		v = i;
		break;
	}
	EXPECT_EQ(v, 0);
}

TEST(ReduceTest, ValueLast)
{
	auto r = reduce(range(5));
	++r;
	++r;
	++r;
	++r;
	++r;
	int i = r;
	EXPECT_EQ(i, 10);
}

TEST(ReduceTest, ValueLastToLong)
{
	auto r = reduce(range(5));
	++r;
	++r;
	++r;
	++r;
	++r;	// last
	++r;	// extra
	++r;	// extra
	int i = r;
	EXPECT_EQ(i, 10);
}

TEST(ReduceTest, ValueLastRangeFor)
{
	int v = 0;
	for (auto i : reduce(range(5)))
	{
		v = i;
	}
	EXPECT_EQ(v, 10);
}


TEST(ReduceTest, VectorTest)
{
	std::vector<int> v1 = { 0, 1,2,3,4 };
	int v = 0;
	for (auto i : reduce(v1.begin(), v1.end()))
	{
		v = i;
	}
	EXPECT_EQ(v, 10);
}




//////////////////////////////////
//
//		
//			ReduceAdv
//		Tests for ReduceAdv class
//
//
/////////////////////////////////


/*TEST(ReduceAdvTest, ValueFirst)
{
	int v = 0;
	std::vector<int> v1 = { 0,1 };
	auto r = reduce_advance<gen::reduce_policy::one>(range(1, 5), v1);
	for (auto i : r)
	{
		v = i;
		break;
	}
	EXPECT_EQ(v, 1);
}*/