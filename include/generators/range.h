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
		class Range final : public IGen<Range<VAL>, VAL>
	{
	public:
		//typedef Range generator_type;

	private:
		const VAL start_;
		const VAL end_;
		const VAL step_;

		const unsigned long long steps_;
		unsigned long long current_step_;

	protected:

		constexpr Range() :	// end()
			IGen<Range<VAL>, VAL>(),
			start_(0), end_(0), step_(0), steps_(0), current_step_(0)
		{
		}
		constexpr Range(VAL start, const VAL & end, VAL step, long long steps) :	// begin()
			IGen<Range<VAL>, VAL>(start, false),
			start_(start), end_(end), step_(step), current_step_(0), steps_(steps)			
		{
		}	

		constexpr Range(VAL start, const VAL & end, VAL step, long long steps, long long current_step, VAL value, bool finished) :	// const ++
			IGen<Range<VAL>, VAL>(start, finished),
			start_(start), end_(end), step_(step), steps_(steps), current_step_(current_step)			
		{
		}

	public:		

		constexpr Range(VAL start, const VAL & end, VAL step) : 
			IGen<Range<VAL>, VAL>(start, false),
			start_(start), end_(end), step_(step), current_step_(0),		
			steps_(static_cast<long long>(((std::max(start_, end_) - std::min(start_, end_)) / abs_custom(step_)) - 0.00000001))
		{			
		}

		inline Range& operator++()
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

		inline Range& operator++(int)
		{
			return this->operator++();
		}

		/*constexpr const Range & next_more() const
		{
			//const_cast<Range>(*this).current_step_ += 1;
			//const_cast<VAL>(value_) = value_ + step_;
			//const_cast<long long>(current_step_) = current_step_ + 1;
			//const_cast<VAL>(value_) = value_ + step_;
			const_cast<unsigned long long>(current_step_) = current_step_ + 1;
			//value_ = value_ + step_;
			return *this;
		}
		constexpr const Range & next_end() const
		{
			//const_cast<bool>(finished_) = true;
			finished_ = true;
			return *this;
		}

		constexpr const Range & operator++() const
		{	// Not as it should be. Need to look for a way to do this
			//return current_step_ < steps_ ?
			//	Range(start_, end_, step_, steps_, current_step_+1, value_+ step_, false)  :
			//	Range(start_, end_, step_, steps_, current_step_, value_, true);
			return current_step_ < steps_ ?
				next_more() :
				next_end();
			
		}
		constexpr const Range& operator++(int) const
		{
			return this->operator++();
		}*/			

		constexpr Range begin() const
		{
			return Range(start_, end_, step_, steps_);
		}

		constexpr Range end() const
		{
			return Range();
		}

		/*constexpr const Range cbegin() const
		{
			return Range(start_, end_, step_, steps_);
		}

		constexpr const Range cend() const
		{
			return Range();
		}*/

	};

	template<typename VAL>
	constexpr Range<VAL> range(VAL start, VAL end, VAL step)
	{	
		return Range<VAL>(start, end, step);
	}

	template<typename VAL>
	constexpr Range<VAL> range(VAL start, VAL end)
	{
		return start <= end ?
			Range<VAL>(start, end, static_cast<VAL>(1)) :
			Range<VAL>(start, end, static_cast<VAL>(-1));	
	}

	template<typename VAL>
	constexpr Range<VAL> range(VAL end)
	{
		return end >= 0 ? 
			Range<VAL>(static_cast<VAL>(0), end, static_cast<VAL>(1)) : 
			Range<VAL>(static_cast<VAL>(0), end, static_cast<VAL>(-1));
	}
	
}