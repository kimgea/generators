#pragma once
//#include "base.h"


namespace gen
{

	// TODO: Look for a better name, if anny.... make_container, ...

	// TODO: make template specialistations struct list_helper to optimize against specific containers

	template<typename T, typename GEN>
	T& list(T& li, GEN& gen)
	{	

		for (auto i : gen)
		{
			li.insert(li.end(), typename T::value_type(i));
		}
		return li;
	}

	template<
		template <class, class> class T = std::vector,
		typename GEN
	>
		auto list(GEN& gen)
	{
		T<
			GEN::value_type,
			std::allocator<GEN::value_type>
		> li;

		for (auto i : gen)
			li.insert(li.end(), typename GEN::value_type(i));
		return li;
	}

	template<
		template <class, class, class> class T,
		typename GEN
	>
		auto list(GEN& gen)
	{
		T<
			GEN::value_type,
			std::less<GEN::value_type>,
			std::allocator<GEN::value_type>
		> li;

		for (auto i : gen)
			li.insert(li.end(), typename GEN::value_type(i));
		return li;
	}

	template<
		template <class, class, class, class> class T,
		typename GEN
	>
		auto list(GEN& gen)
	{
		T<
			GEN::value_type,
			std::hash<GEN::value_type>,
			std::equal_to<GEN::value_type>,
			std::allocator<GEN::value_type>
		> li;

		for (auto i : gen)
			li.insert(li.end(), typename GEN::value_type(i));
		return li;
	}



}