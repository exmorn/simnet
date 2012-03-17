#ifndef __OBJCOUNTER_H__
#define __OBJCOUNTER_H__
#include"noncopyable.h"
namespace simnet
{
	template<class T>
	class ObjCounter:noncopyable
	{
	public:
		inline	ObjCounter(int step = 1)
		{
			m_step = step;
			static_m_obj_cnt += m_step;
		}
		inline	~ObjCounter()
		{
			static_m_obj_cnt -= m_step;
		}
		inline	static int getObjCnt()
		{
			return static_m_obj_cnt;
		}
	private:
		static int static_m_obj_cnt;
		int m_step;
	};
	template<class T>
	int ObjCounter<T>::static_m_obj_cnt = 0;
}
#endif