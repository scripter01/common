#ifndef THREAD_TASK_H
#define THREAD_TASK_H

class ThreadTask
{
public:
	virtual ~ThreadTask() = default;
	virtual void run() {};// = 0;
};

class ThreadFuncTask: public ThreadTask
{
public:
	ThreadFuncTask(std::function<void()> func): m_func(func) {}
	virtual void run() { m_func(); }

private:
	std::function<void()> m_func;
};

#endif //THREAD_TASK_H