#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/atomic.hpp>
#include <chrono>
class TestBean {
public:
    int64_t number;
    boost::mutex mutex;

    void add() {
        for (int i = 0; i < 100000; i++) {
            boost::lock_guard<boost::mutex> lock{mutex};
            number++;
        }
    }
};

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    boost::thread_group threads;
    boost::shared_ptr<TestBean> bean = boost::make_shared<TestBean>();
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.create_thread(boost::bind(&TestBean::add, bean));
    threads.join_all();
    std::cout << "[lock] number = " << bean->number << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns" << std::endl;
}
