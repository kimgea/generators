#include "gtest/gtest.h"

#include "range.h"


using namespace gen;



TEST(RangeTest, Constexpr1)
{
	static_assert(range(0, 5, 1) == range(0, 5, 1), "");
	static_assert(range(0, 5) == range(0, 5), "");
	static_assert(range(0, -5) == range(0, -5), "");
	static_assert(range(5) == range(5), "");
	static_assert(range(-5) == range(-5), "");

	constexpr Range<int> test_range1 = range(2);
	constexpr Range<int> test_range2(test_range1);
	static_assert(test_range2 == test_range1, "");


	static_assert(range(5).begin() == range(-5).begin(), "");	
	static_assert(range(5).end() == range(-5).end(), "");

	constexpr Range<int> test_range = range(2);
	//++test_range;
	//++test_range;
	//++test_range;
	static_assert(test_range == range(2), "");
	//static_assert(++test_range == range(2), "");
	//static_assert(test_range+1 == range(2), "");

	//static_assert(range(5).begin() == range(-5).end(), "");	// OK. It fails
	//static_assert(range(5, -5, -1) == range(0, 5, 1), "");	// Succes. Not good. Currently strange. not logical !!!!!!


	//Range<int> test_range2 = range(2);
	//test_range2 = test_range2 + 1;

	EXPECT_EQ(5, 5);
}


TEST(RangeTest, RangeOtherInc)
{

	auto r = range(5);
	//r += 2;		// TODO: make it work
	//r++;
	//++r;
	EXPECT_EQ(2, 2);
}


//////////////////////////////////
//
//		For types
//



TEST(RangeTest, RangeFor)
{
	long nr = 5;
	long count = 0;
	for (auto i : range(nr))
		++count;
	EXPECT_EQ(count, nr);
}

TEST(RangeTest, For)
{
	auto r = range(5);
	int count = 0;
	for (auto i = std::begin(r); i != std::end(r); ++i)
		++count;
	EXPECT_EQ(count, 5);
}

TEST(RangeTest, For2)
{
	auto r = range(5);
	int count = 0;
	auto vb = std::begin(r);
	auto ve = std::end(r);
	for (auto i = vb; i != ve; ++i)						//	32
		++count;
	EXPECT_EQ(count, 5);
}

TEST(RangeTest, For3)
{
	int count = 0;
	int nr = 100000;
	auto v = range(nr);
	auto vb = std::begin(v);
	auto ve = std::end(v);
	for (auto i = vb; i != ve; ++i)						//	32
		++count;
	EXPECT_EQ(count, nr);
}

//////////////////////////////////
//
//		INTEGER For
//

////// POS

TEST(RangeTest, SingleArgPos)
{
	int count = 0;
	for (auto i : range(5))
		++count;
	EXPECT_EQ(count, 5);
}


TEST(RangeTest, TwoArgPos)
{
	int count = 0;
	for (auto i : range(1,5))
		++count;
	EXPECT_EQ(count, 4);
}



TEST(RangeTest, ThreeArgPos)
{	
	int count = 0;
	for (auto i : range(1, 5, 1))
		++count;
	EXPECT_EQ(count, 4);
}


////// NEG

TEST(RangeTest, SingleArgNeg)
{
	int count = 0;
	for (auto i : range(-5))
		++count;
	EXPECT_EQ(count, 5);
}


TEST(RangeTest, TwoArgNeg)
{
	int count = 0;
	for (auto i : range(-1, -5))
		++count;
	EXPECT_EQ(count, 4);
}



TEST(RangeTest, ThreeArgNeg)
{
	int count = 0;
	for (auto i : range(-1, -5, -1))
		++count;
	EXPECT_EQ(count, 4);
}


////// POS NEG COMBINED

TEST(RangeTest, PosNegCombined1)
{
	int count = 0;
	for (auto i : range(-1, 5, 1))
		++count;
	EXPECT_EQ(count, 6);
}

TEST(RangeTest, PosNegCombined2)
{
	int count = 0;
	for (auto i : range(1, -5, -1))
		++count;
	EXPECT_EQ(count, 6);
}


//////////////////////////////////
//
//		DOUBLE For
//

////// POS

TEST(RangeTest, DoubleSingleArgPos)
{
	int count = 0;
	for (auto i : range(5.0))
		++count;
	EXPECT_EQ(count, 5);
}


TEST(RangeTest, DoubleTwoArgPos)
{
	int count = 0;
	for (auto i : range(1.5, 5.))
		++count;
	EXPECT_EQ(count, 4);
}



TEST(RangeTest, DoubleThreeArgPos)
{
	int count = 0;
	for (auto i : range(1., 5., 1.5))
		++count;
	EXPECT_EQ(count, 3);
}


////// NEG

TEST(RangeTest, DoubleSingleArgNeg)
{
	int count = 0;
	for (auto i : range(-5.0))
		++count;
	EXPECT_EQ(count, 5);
}


TEST(RangeTest, DoubleTwoArgNeg)
{
	int count = 0;
	for (auto i : range(-1.5, -5.0))
		++count;
	EXPECT_EQ(count, 4);
}


TEST(RangeTest, DoubleThreeArgNeg)
{
	int count = 0;
	for (auto i : range(-1., -5.5, -1.3))
		++count;
	EXPECT_EQ(count, 4);
}


////// POS NEG COMBINED

TEST(RangeTest, DoublePosNegCombined1)
{
	int count = 0;
	for (auto i : range(-1.5, 5.5, 1.1))
		++count;
	EXPECT_EQ(count, 7);
}

TEST(RangeTest, DoublePosNegCombined2)
{
	int count = 0;
	for (auto i : range(1., -5., -1.1))
		++count;
	EXPECT_EQ(count, 6);
}



//////////////////////////////////
//
//		Value Checks
//

TEST(RangeTest, ValueFirstInFor)
{
	for (auto i : range(5))
	{
		int v = i;
		EXPECT_EQ(v, 0);
		break;
	}	
}

TEST(RangeTest, ValueLastInFor)
{
	int v = 0;
	for (auto i : range(5))
	{
		v = i;		
	}
	EXPECT_EQ(v, 4);
}



//////////////////////////////////
//
//		function Checks
//