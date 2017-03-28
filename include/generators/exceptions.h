#pragma once
#include <exception>



class BaseException : public std::exception {};

	class Exception : public BaseException {};
		class StopIteration : public Exception {};
	class StandardError : public BaseException {};
		class ValueError : public BaseException {};