
#include "gtest/gtest.h"

#include "range.h"
#include "operations.h"


using namespace gen;

TEST(BaseicOperations, Finished)
{	
	auto r = range(2);
	
	EXPECT_EQ(finished(r), false);
	++r;
	EXPECT_EQ(finished(r), false);
	++r;
	EXPECT_EQ(finished(r), true);
	++r;
	EXPECT_EQ(finished(r), true);
}


TEST(BaseicOperations, Run1)
{
	auto r = range(5);
	run(r);
	EXPECT_EQ(*r, 4);
}
TEST(BaseicOperations, Run2)
{
	auto r = run(range(5));
	EXPECT_EQ(r, 4);
}
