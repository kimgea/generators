#include "gtest/gtest.h"

#include <vector>
#include <set>
#include <list>
#include <deque>
#include <unordered_set>

#include "range.h"
#include "list.h"



TEST(List, Vector1)
{
	auto a = gen::list(gen::range(2));

	EXPECT_EQ(a.size(), 2);
}


TEST(List, Set1)
{
	auto a = gen::list<std::set>(gen::range(3));

	EXPECT_EQ(a.size(), 3);
}

TEST(List, List1)
{
	auto a = gen::list<std::list>(gen::range(4));

	EXPECT_EQ(a.size(), 4);
}

TEST(List, Deque1)
{
	auto a = gen::list<std::deque>(gen::range(4));

	EXPECT_EQ(a.size(), 4);
}

TEST(List, UnorderedSet)
{
	auto a = gen::list<std::unordered_set>(gen::range(4));

	EXPECT_EQ(a.size(), 4);
}