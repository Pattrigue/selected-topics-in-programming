#include <thread>
#include <condition_variable>
#include <future>
#include <functional>
#include <queue>

class thread_pool {
    std::queue<std::function<void()>> tasks;
    std::vector<std::jthread> threads;
    std::mutex mutex;
    std::condition_variable cv;
    
    bool stop = false;
    
public:
    explicit thread_pool(size_t num_threads) {
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock lock(mutex);
                        cv.wait(lock, [this] {
                            return stop || !tasks.empty(); 
                        });
                        
                        if (stop && tasks.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    
                    task();
                }
            });
        }
    }
    
    ~thread_pool() { 
        mutex.lock();
        stop = true;
        mutex.unlock();
        
        cv.notify_all();
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "Thread pool destroyed." << std::endl;
    }
    
    void add_task(std::function<void()> task) {
        {
            std::scoped_lock lock(mutex);
            tasks.push(std::move(task));
        }
        
        cv.notify_one();
    }

    template<typename Fn, typename... Args>
    auto async(Fn&& fn, Args&&... args) {
        using return_type = std::invoke_result_t<Fn, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...
        ));
        
        auto future = task->get_future();
        
        add_task([task]() {
            (*task)();
        });
        
        return future;
    }
};