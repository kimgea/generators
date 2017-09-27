#pragma once
#include "base.h"


namespace gen
{

	template<typename TT>
	constexpr bool finished(const TT & gen)
	{
		return gen.finished_;
	}

	template<typename T>
	typename T::value_type run(T& gen)
	{
		while (!finished(++gen)) {}
		return *gen;
	}

}