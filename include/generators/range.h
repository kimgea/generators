#pragma once
#include <type_traits>

#include "base.h"
#include "exceptions.h"

#include <algorithm>
#include <math.h>
#include <cmath>

/*
	TODO: Make a second Range class that takes a generator as step. Create it with the same range functions
*/

namespace gen
{

	template<
		typename VAL = int,
		typename = typename std::enable_if<std::is_arithmetic<VAL>::value, VAL>::type
	>
	class Range final : public IGenForward<Range<VAL>, VAL>
	{
	public:
		//typedef Range generator_type;

	private:
		VAL start_;
		VAL end_;
		VAL step_;

		long long steps_;
		long long current_step_;


	public:

		Range() :	// end()
			start_(0), end_(0), step_(0), steps_(0), current_step_(0)
		{
			finished_ = true;
		}
		Range(VAL start, VAL end, VAL step, long long steps) :	// begin()
			start_(start), end_(end), step_(step), current_step_(0), steps_(steps)
		{
			value_ = start_;
		}

		Range(VAL start, VAL end, VAL step) : start_(start), end_(end), step_(step), current_step_(0)
		{
			value_ = start_;
			steps_ = static_cast<long long>(((std::max(start_, end_) - std::min(start_, end_)) / std::abs(step_)) - 0.00000001);	// TODO: last part is bad	
		}

		Range& operator++()
		{
			if (current_step_ < steps_)
			{
				value_ += step_;
				++current_step_;
			}
			else
				finished_ = true;

			return *this;
		}

		Range& operator++(int)
		{
			return this->operator++();
		}

		Range begin()
		{
			return Range(start_, end_, step_, steps_);
		}

		Range end()
		{
			return Range();
		}

	};



	

	template<typename VAL>
	inline Range<VAL> range(VAL start, VAL end, VAL step)
	{
		return Range<VAL>(start, end, step);
	}

	template<typename VAL>
	inline Range<VAL> range(VAL start, VAL end)
	{
		if (start <= end)
			return Range<VAL>(start, end, static_cast<VAL>(1));
		else
			return Range<VAL>(start, end, static_cast<VAL>(-1));
	}

	template<typename VAL>
	inline Range<VAL> range(VAL end)
	{
		if (end >= 0)
			return Range<VAL>(static_cast<VAL>(0), end, static_cast<VAL>(1));
		else
			return Range<VAL>(static_cast<VAL>(0), end, static_cast<VAL>(-1));
	}

}