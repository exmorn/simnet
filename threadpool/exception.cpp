#include "exception.h"
namespace simnet
{
	Exception::Exception(const char* msg)
		: m_msg(msg)
	{
	}

	Exception::Exception(const string& msg)
		: m_msg(msg)
	{
	}

	Exception::~Exception() throw()
	{
	}
	const char* Exception::what() const throw()
	{
		return m_msg.c_str();
	}
}