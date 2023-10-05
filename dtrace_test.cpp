#include <sys/sdt.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <thread>
#include <vector>
#include <atomic>

inline void trace_tag_timestamp(uint64_t unique_id, const std::string& point_name,
                                uint64_t ts, const std::string& tag,
                                const std::string& str_arg) {
    DTRACE_PROBE5(test_grp, test_idx, unique_id, point_name.c_str(), ts, tag.c_str(), str_arg.c_str());
}
volatile bool stop = false;
volatile uint64_t start = 0;
volatile uint64_t end = 0;
uint64_t get_cur_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
void print_func(int sig) {
    end = get_cur_time_us();
    stop = true;
}
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "dtrace_test $qps [$thread_size 4]" << std::endl;
        return 0;
    }
    int thread_size = 4;
    if (argc == 3) {
        thread_size = std::stoi(argv[2]);
    }
    if (signal(SIGINT, print_func) == SIG_ERR) {
        std::cout << "Failed to caught signal" << std::endl;
    }
    int qps = std::stoi(argv[1]);

    start =get_cur_time_us();
    std::vector<std::shared_ptr<uint64_t>> count_vec;
    auto test_func = [](int qps, uint64_t *count) {
        int sleep_d = 1000000 / qps;
        while(!stop) {
            trace_tag_timestamp((*count)++, "point_name", 1, "tag", "str_arg");
            usleep(sleep_d);
        }
    };
    std::vector<std::shared_ptr<std::thread>> thread_vec;
    int single_qps = qps / thread_size;
    std::cout << "thread_size: " << thread_size << " single_qps: " << single_qps << " actual_qps: " << thread_size * single_qps << std::endl;
    for (int i = 0; i < thread_size; ++i) {
        count_vec.push_back(std::make_shared<uint64_t>());
        thread_vec.push_back(std::make_shared<std::thread>(test_func, single_qps, count_vec.at(i).get()));
    }
    for (auto& t : thread_vec) {
        t->join();
    }
    uint64_t total_count = 0;
    for (auto ptr : count_vec) {
        total_count += *ptr;
    }
    std::cout << "total_count: " << total_count << std::endl;
    std::cout << "duration: " << float((end - start)) / 1000000 << " s, qps: " << total_count / (float((end - start)) / 1000000) << std::endl;
}
