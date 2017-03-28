#pragma once



namespace gen
{
	template<typename T, typename V>
	class IGen
	{
	public:
		typedef V value_type;
		typedef T generator_type;

	protected:
		bool finished_{ false };
		V value_;

	public:

		V const & operator*() const
		{
			return value_;
		}

		operator V()
		{
			return value_;
		}

		T begin()
		{
			return static_cast<T*>(this)->begin();
		}

		T end()
		{
			return static_cast<T*>(this)->end();
		}


		// Only compares if it is finished or not
		friend bool operator==(const T& left, const T& right)
		{
			return (left.finished_ == right.finished_);
		}
		friend bool operator!=(const T& left, const T& right)
		{
			return (left.finished_ != right.finished_);
		}

		template<typename TT>
		friend bool finished(const TT& gen);
	};


	// TODO: Might remove this. Forward is probably the only one... so it could be moved into IGen
	template<typename T, typename V>
	class IGenForward : public IGen<IGenForward<T, V>, V>
	{
		T& operator++()
		{
			return static_cast<T*>(this)->operator++();
		}

		T& operator++(int)
		{
			return this->operator++();;
		}
	};


}