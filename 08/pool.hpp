#pragma once
#include <thread>
#include <future>
#include <condition_variable>
#include <functional>
#include <queue>
#include <iostream>


class ThreadPool
{
    size_t size;
    bool active;

    std::queue<std::function<void()>> queue_;
    std::vector<std::thread> pool_;

    std::mutex mut;
    std::condition_variable cv;

public:
    ThreadPool(size_t poolSize): size(poolSize), active(true)
    {
        for (size_t i = 0; i < size; i++)
        {
            pool_.emplace_back([this, i]()
                { 
                    while (true)
                    {
                        std::unique_lock<std::mutex> lock(mut);
                        if (!queue_.empty())
                        {
                            auto func = std::move(queue_.front());
                            queue_.pop();
                            lock.unlock();
							std::cout << "thread " << i << std::endl;
                            func();
                        }
                        else// случай, когда потоки ожидают задачи
                        {
                            if (active)
                                cv.wait(lock);
                            else
                                break;
                        }
                    }
                });
        }
    }

	~ThreadPool()
	{
		active = false;
		cv.notify_all();
		for (auto & t: pool_)
		{
			t.join();
		}
	}
	
	
	template <class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
	{
		auto p = std::make_shared<std::packaged_task<decltype(func(args...))()> >(
			std::bind(std::forward<Func>(func), std::forward<Args>(args)...)); //делаем для функции тот интерфейс, который требуется
		{
			std::lock_guard<std::mutex> lock(mut);
			if (!active)
			{
				throw std::runtime_error("The pool has stopped");
			}
			queue_.emplace([p]()
				{
					(*p)();
				}); //добавляем в очередь.
		}
		cv.notify_one(); //будим любой поток, пусть выполняет нашу задачу
		return p->get_future(); 
	}
};
