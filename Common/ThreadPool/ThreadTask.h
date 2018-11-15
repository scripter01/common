#ifndef THREAD_TASK_H
#define THREAD_TASK_H

class ThreadTask
{
public:
	virtual ~ThreadTask() = default;
	virtual bool ready() { return true; }
	virtual void run() { execute(); }

	virtual void execute() { LOG("TASK execute in thread: " << std::this_thread::get_id()); };
};

class ThreadFuncTask: public ThreadTask
{
public:
	ThreadFuncTask(std::function<void()> func = nullptr);
	virtual void run();

private:
	void executeFunc();

private:
	std::function<void()> m_func;
};

#endif //THREAD_TASK_H