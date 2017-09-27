#pragma once
#include <functional>
#include <type_traits>
#include <vector>
#include "base.h"


namespace gen
{

	struct reduce_policy
	{
		struct one;
		struct two;
	};



	template<typename T>
	class Reduce : public IGen<Reduce<T>, typename T::value_type>
	{
	public:
		//typedef RED generator_type;

	protected:

		const T gen_begin_;
		const T gen_end_;
		T gen_itr_;
		//std::vector<value_type> init_;		// Not currently used. ment for advance reduce. Remove it... place it in advance reduce???
		const std::function<value_type(value_type, value_type)> binary_op_;


		constexpr Reduce(const T & gen_begin, const T & gen_end,
			std::function<value_type(value_type, value_type)> binary_op, 
			T gen_itr, typename T::value_type value, bool finished)
			:
			IGen<Reduce<T>, typename T::value_type>(value, finished),
			binary_op_(binary_op), gen_begin_(gen_begin), gen_end_(gen_end), gen_itr_(gen_itr)
		{
		}		

	public:

		constexpr Reduce(const T & gen, std::function<value_type(value_type, value_type)> binary_op) :
			IGen<Reduce<T>, typename T::value_type>(*std::begin(gen), false),
			binary_op_(binary_op), gen_begin_(gen), gen_end_(std::end(gen)), gen_itr_(gen)
		{
		}
		constexpr Reduce(T gen_begin, T gen_end, std::function<value_type(value_type, value_type)> binary_op) :
			IGen<Reduce<T>, typename T::value_type>(*gen_begin, false),
			gen_begin_(gen_begin), gen_end_(gen_end), binary_op_(binary_op), gen_itr_(gen_begin)
		{
		}

		inline Reduce& operator++()
		{
			if (gen_itr_ != gen_end_)
			{
				value_ = binary_op_(value_, *gen_itr_);
				++gen_itr_;
			}
			else
				finished_ = true;

			return *this;
		}
		inline Reduce& operator++(int)
		{
			return this->operator++();
		}

		constexpr Reduce begin() const
		{
			return Reduce(gen_begin_, gen_end_, binary_op_);
		}

		constexpr Reduce end() const
		{
			return Reduce(gen_begin_, gen_end_, binary_op_, gen_itr_, value_, true);
		}
	};


	template<typename T>
	constexpr Reduce<T> reduce(T gen)
	{
		return Reduce<T>(gen, std::plus<T::value_type>());
	}
	template<typename T>
	constexpr Reduce<T> reduce(T begin, T end)
	{
		return Reduce<T>(begin, end, std::plus<T::value_type>());
	}

	template<typename T>
	constexpr Reduce<T> reduce(T gen, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return Reduce<T>(gen, binary_op);
	}
	template<typename T>
	constexpr Reduce<T> reduce(T begin, T end, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return Reduce<T>(begin, end, binary_op);
	}



	/*template<typename RED, typename T>
	class ReduceBase : public IGen<ReduceBase<RED, T>, typename T::value_type>
	{
	public:
		//typedef RED generator_type;

	protected:

		const T gen_begin_;
		const T gen_end_;
		std::vector<value_type> init_;		// Not currently used. ment for advance reduce. Remove it... place it in advance reduce???
		std::function<value_type(value_type, value_type)> binary_op_;



	public:

		constexpr ReduceBase(T gen, std::vector<value_type> init, std::function<value_type(value_type, value_type)> binary_op) :
			IGen<Range<VAL>, VAL>(start, false),
			init_(init), binary_op_(binary_op), gen_begin_(std::begin(gen)), gen_end_(std::end(gen)), 
		{
			// = std::begin(gen);
			//gen_end_ = std::end(gen);
			//value_ = *gen_begin_;
		}
		constexpr ReduceBase(T gen_begin, T gen_end, std::vector<value_type> init, std::function<value_type(value_type, value_type)> binary_op) :
			IGen<Range<VAL>, VAL>(start, false),
			gen_begin_(gen_begin), gen_end_(gen_end), init_(init), binary_op_(binary_op), 
		{
			//value_ = *gen_begin;
		}


		RED& operator++(int)
		{
			return this->operator++();
		}

		constexpr RED begin()
		{
			return RED(gen_begin_, gen_end_, init_, binary_op_);
		}

		constexpr RED end()
		{
			auto ret = RED(gen_begin_, gen_end_, init_, binary_op_);
			ret.finished_ = true;
			return ret;
		}
	};


	////////////////////////////////////////////////////////////////////////////////


	template<typename T>
	class Reduce : public ReduceBase<Reduce<T>, T>
	{
	public:
		using ReduceBase<Reduce<T>, T>::ReduceBase;

		Reduce& operator++()
		{
			if (gen_begin_ != gen_end_)
			{
				value_ = binary_op_(value_, *gen_begin_);
				++gen_begin_;
			}
			else
				finished_ = true;

			return *this;
		}
	};
	*/



	/*template<typename T>
	Reduce<T> reduce(T gen)
	{
		return Reduce<T>(gen, std::vector<decltype(T::value_type())> {}, std::plus<T::value_type>());
	}
	template<typename T>
	Reduce<T> reduce(T begin, T end)
	{
		return Reduce<T>(begin, end, std::vector<decltype(T::value_type())> {}, std::plus<T::value_type>());
	}

	template<typename T>
	Reduce<T> reduce(T gen, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return Reduce<T>(gen, std::vector<decltype(T::value_type())> {}, binary_op);
	}
	template<typename T>
	Reduce<T> reduce(T begin, T end, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return Reduce<T>(begin, end, std::vector<decltype(T::value_type())> {}, binary_op);
	}*/



	////////////////////////////////////////////////////////////////////////////////
	//
	//		Advance Reduce is skipped for now. only wanted to try out enable_if
	//

	/*template<typename T, typename P>
	class ReduceAdvBase : public ReduceBase<ReduceAdvBase<T, P>, T>
	{
	public:
		using ReduceBase<ReduceAdvBase<T, P>, T>::ReduceBase;


		template<typename U = P>
		typename std::enable_if<std::is_same<U, reduce_policy::one>::value>::type 
			next()
		{
			if (gen_begin_ != gen_end_)
			{
				value_ = binary_op_(value_, *gen_begin_);
				++gen_begin_;
			}
			else
				finished_ = true;

			//return *this;
		}

		template<typename U = P>
		typename std::enable_if<std::is_same<U, reduce_policy::two>::value>::type
			next()
		{
			if (gen_begin_ != gen_end_)
			{
				value_ = binary_op_(value_, *gen_begin_);
				++gen_begin_;
			}
			else
				finished_ = true;

			//return *this;
		}

		ReduceAdvBase& operator++() 
		{
			next();
			return *this;
		}
	};*/


	/*template<typename T>
	class ReduceAdvBase<T, reduce_policy> : public ReduceBase<ReduceAdvBase<T, reduce_policy>, T>
	{
	public:
		using ReduceBase<ReduceAdvBase<T, reduce_policy>, T>::ReduceBase;

		ReduceAdvBase& operator++() //override
		{
			//
			if (gen_begin_ != gen_end_)
			{
			value_ = binary_op_(value_, *gen_begin_);
			++gen_begin_;
			}
			else
				finished_ = true;

			return *this;
		}
	};*/


	/*template<typename P, typename T>
	ReduceAdvBase<T, P> reduce_advance(T gen, std::vector<int> init) //-> decltype(ReduceAdvBase<T, policy>)
	{
		return ReduceAdvBase<T, P>(gen, init, std::plus<T::value_type>());
	}*/

	/*template<typename T, typename P>
	ReduceAdvBase<T, P> reduce_advance(reduce_policy policy, T begin, T end, std::vector<decltype(T::value_type())> init)
	{
		return ReduceAdvBase<T, policy>(begin, end, init, std::plus<T::value_type>());
	}

	template<typename T, typename P>
	ReduceAdvBase<T, P> reduce_advance(reduce_policy policy, T gen, std::vector<decltype(T::value_type())> init, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return ReduceAdvBase<T, policy>(gen, init, binary_op);
	}
	template<typename T, typename P>
	ReduceAdvBase<T, P> reduce_advance(reduce_policy policy, T begin, T end, std::vector<decltype(T::value_type())> init, std::function<decltype(T::value_type())(decltype(T::value_type()), decltype(T::value_type()))> binary_op)
	{
		return ReduceAdvBase<T, policy>(begin, init, end, binary_op);
	}*/

}