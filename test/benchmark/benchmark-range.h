#pragma once
#include "stdafx.h"
#include <chrono>
#include "range.h"

using namespace gen;

inline void benchamerk_range1()
{
	std::cout << std::fixed << "=================benchamerk_range1=====================" << std::endl;
	int nr = 100000;
	{
		int count = 0;
		auto t1 = std::chrono::high_resolution_clock::now();

		for (auto i = 0; i < nr; ++i)					// 0.28 | 0.29 || 0.24
			++count;

		auto te = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms1 = te - t1;
		std::cout << std::fixed << "Regular for loop count result " << std::endl << count
			<< " took " << ms1.count() << std::endl;
	}
	std::cout << std::endl;
	{
		int count = 0;
		auto tr1 = std::chrono::high_resolution_clock::now();

		for (auto i : range(nr))					//	34 | 13.8 || 9.7
			++count;

		auto tre = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> msr = tre - tr1;
		std::cout << std::fixed << "Range with range based for loop count result " << std::endl << count
			<< " took " << msr.count() << std::endl;
		// 125-140
	}
	std::cout << std::endl;
	{
		int count = 0;
		auto tr1 = std::chrono::high_resolution_clock::now();

		auto v = range(nr);
		for (auto i = std::begin(v); i != std::end(v); ++i)		// 94 | 33.6 | 29.8
			++count;

		auto tre = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> msr = tre - tr1;
		std::cout << std::fixed << "Range with regular for loop count result " << std::endl << count
			<< " took " << msr.count() << std::endl;
	}
	std::cout << std::endl;
	{
		int count = 0;
		auto tr1 = std::chrono::high_resolution_clock::now();

		auto v = range(nr);
		auto vb = std::begin(v);
		auto ve = std::end(v);
		for (auto i = vb; i != ve; ++i)						//	32 || 8 || 9.1
			++count;

		auto tre = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> msr = tre - tr1;
		std::cout << std::fixed << "Range with regular foor loop and begin/end found first count result " << std::endl << count
			<< " took " << msr.count() << std::endl;
	}
	std::cout << std::fixed << "__________________________________________________________" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}





inline void benchamerk_range()
{
	std::cout << std::fixed << "=================RANGE=====================" << std::endl;
	std::cout << std::fixed << "===========================================" << std::endl;

	benchamerk_range1();

	std::cout << std::fixed << "===========================================" << std::endl;
	std::cout << std::fixed << "===========================================" << std::endl;

}