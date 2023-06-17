#include <thread>
#include <condition_variable>
#include <future>
#include <functional>
#include <queue>

namespace StochSimLib {

    /** A class for managing a pool of threads executing tasks. */
    class ThreadPool {
        std::queue<std::function<void()>> m_tasks;  // Queue of tasks to be executed by the threads.
        std::vector<std::jthread> m_threads;        // Vector of worker threads.
        std::mutex m_mutex;                         // Mutex for synchronizing access to tasks.
        std::condition_variable m_cv;               // Condition variable to wake up threads when tasks are available.

        bool m_stop = false;                        // Boolean flag indicating whether to stop the thread pool.

    public:
        /**
         * @brief Constructs a ThreadPool with a specified number of worker threads.
         * @param num_threads Number of worker threads to create.
         */
        explicit ThreadPool(size_t num_threads) {
            // Create and start worker threads.
            for (int i = 0; i < num_threads; ++i) {
                m_threads.emplace_back([this] {
                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock lock(m_mutex);

                            // Wait until a task is available or stop is signaled.
                            m_cv.wait(lock, [this] {
                                return m_stop || !m_tasks.empty();
                            });

                            // If stop is signaled and no tasks are available, exit the thread.
                            if (m_stop && m_tasks.empty()) {
                                return;
                            }

                            // Get the next task from the queue.
                            task = std::move(m_tasks.front());
                            m_tasks.pop();
                        }

                        // Execute the task.
                        task();
                    }
                });
            }
        }

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;
        
        /** Destructor. Stops all worker threads and waits for them to finish. */
        ~ThreadPool() {
            {
                std::scoped_lock lock(m_mutex);
                m_stop = true;  // Signal all threads to stop.
            }

            m_cv.notify_all();  // Wake up all threads.

            // Wait for all threads to finish.
            for (auto &thread: m_threads) {
                thread.join();
            }
        }

        /** Adds a new task to be executed by the worker threads.
         * @param task Task to be added. This should be a callable object. */
        void addTask(std::function<void()> task) {
            {
                std::scoped_lock lock(m_mutex);
                m_tasks.push(std::move(task));  // Add the task to the queue.
            }

            m_cv.notify_one();  // Wake up one thread to handle the new task.
        }
    };
    
}