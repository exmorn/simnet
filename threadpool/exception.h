#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__
#include<string>
#include<exception>
using namespace std;
namespace simnet
{
	class Exception : exception
	{
	public:
		explicit Exception(const char* msg);
		explicit Exception(const string& msg);
		virtual ~Exception() throw();
		virtual const char* what() const throw();
	private:
		std::string m_msg;
	};
}
#endif