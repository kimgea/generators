#pragma once



namespace gen
{
	template<class t>
	constexpr t abs_custom(t x)
	{	// std::abs dis not work in constexpr
		return x < 0 ? -x : x;
	}

	////////////////////////////////
	
	template<typename T, typename V>
	class IGen
	{
	public:
		typedef V value_type;
		typedef T generator_type;

	protected:
		bool finished_{ false };
		V value_;

		constexpr IGen() : value_(0), finished_(true) {}	// end()

	public:

		constexpr IGen(V value, bool finished) : value_(value), finished_(finished) {}

		constexpr V const & operator*() const
		{
			return value_;
		}

		constexpr operator V() const
		{
			return value_;
		}

		/*constexpr T begin() const
		{
			return static_cast<T*>(this)->begin();
		}

		constexpr T end() const
		{
			return static_cast<T*>(this)->end();
		}*/


		// Only compares if it is finished or not
		constexpr bool operator==(const T& right) const
		{
			return (finished_ == right.finished_);
		}
		constexpr bool operator!=(const T& right) const
		{
			return (finished_ != right.finished_);
		}

		template<typename TT>
		friend constexpr bool finished(const TT& gen);
	};


	// TODO: Might remove this. Forward is probably the only one... so it could be moved into IGen
	/*template<typename T, typename V>
	class IGenForward : public IGen<IGenForward<T, V>, V>
	{
	protected:
		constexpr IGenForward() : IGen<IGenForward<T, V>, V>() {}
	public:
		constexpr IGenForward(V value, bool finsihed) : IGen<IGenForward<T, V>, V>(value, finsihed) {}

		// TODO: Why did i make this ???
		inline T& operator++()
		{
			return static_cast<T*>(this)->operator++();
		}

		inline T& operator++(int)
		{
			return this->operator++();
		}
	};*/


}