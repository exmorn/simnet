#ifndef __TYPES_H__
#define __TYPES_H__
namespace simnet
{
	template<typename T>
	struct identity { typedef T type; };
	template <typename T>
	inline T implicit_cast (typename identity<T>::type x)
	{
		return x;
	}
	typedef unsigned int pid_t;
	typedef signed int int32_t;
}
#endif