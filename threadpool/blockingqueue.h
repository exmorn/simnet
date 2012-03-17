#ifndef __BOLCKINGQUEUE_H__
#define __BOLCKINGQUEUE_H__
#include "noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "assert.h"
#include<deque>
namespace simple
{
	template<class T>
	class BlockingQueue : noncopyable
	{
	private:
		MutexLock m_mutex;
		Condition m_cond_notEmpty;
		std::deque<T> m_queue;
	public:
		BlockingQueue()
			: m_mutex()
			, m_cond_notEmpty(m_mutex)
			, m_queue()
		{
		}
		void put(const T& x)
		{
			MutexLockGuard lock(m_mutex);
			m_queue.push_back(x);
			m_cond_notEmpty.notify();
		}
		T take()
		{
			MutexLockGuard lock(m_mutex);
			while(m_queue.empty())
			{
				m_cond_notEmpty.wait();
			}
			assert(!m_queue.empty());
			T front(m_queue.front());
			m_queue.pop_front();
			return front;
		}
		size_t size()
		{
			MutexLockGuard lock(m_mutex);
			return m_queue.size();
		}
	};
}
#endif