#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;
static bool debug = false;
static std::vector<std::vector<uint64_t>> last_stat;
static std::vector<std::vector<double>> result;
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        if (token.empty() || token[0] == delimiter) {
            continue;
        }
        tokens.push_back(token);
    }
    return tokens;
}

void cal_one(ifstream& file) {
    file.clear();
    file.seekg(0);
    string line;
    vector<string> cpu_data;
    while (getline(file, line)) {
        if (line.substr(0, 3) == "cpu") {
            // if (debug) std::cout << "push_back line:" << line << std::endl;
            cpu_data.push_back(line);
        }
    }
    cout << "\033[2J\033[0;0H";
    cout << right << setw(10) << "CPU";
    cout << right << setw(10) << "usr";
    cout << right << setw(10) << "nice";
    cout << right << setw(10) << "sys";
    cout << right << setw(10) << "idle";
    cout << right << setw(10) << "iowait";
    cout << right << setw(10) << "irq";
    cout << right << setw(10) << "softirq";
    cout << right << setw(10) << "steal";
    cout << right << setw(10) << "guest";
    cout << right << setw(10) << "gnice" << endl;
    auto fill_stat_metric = [&cpu_data](std::vector<std::vector<uint64_t>>& last_stat) {
        for (int i = 0; i < cpu_data.size(); i++) {
            const auto & cpu_fields = split(cpu_data[i], ' ');
            if (cpu_fields.size() != 11) {
                std::cout << "cpu line not 11" << std::endl;
            }
            if (last_stat[i].size() == 0) {
                last_stat[i].resize(10);
            }
            string cpu_name = cpu_fields[0];
            last_stat[i][0] = stol(cpu_fields[1]); // usr
            last_stat[i][1] = stol(cpu_fields[2]); // nice
            last_stat[i][2] = stol(cpu_fields[3]); // sys
            last_stat[i][3] = stol(cpu_fields[4]); // idle
            last_stat[i][4] = stol(cpu_fields[5]); // iowait
            last_stat[i][5] = stol(cpu_fields[6]); // irq
            last_stat[i][6] = stol(cpu_fields[7]); // softirq
            last_stat[i][7] = stol(cpu_fields[8]); // steal
            last_stat[i][8] = stol(cpu_fields[9]); // guest
            last_stat[i][9] = stol(cpu_fields[10]); // guest_nice
        }
    };
    if (last_stat.size() != cpu_data.size()) {
        // run the first time
        last_stat.resize(cpu_data.size());
        result.resize(cpu_data.size());
        fill_stat_metric(last_stat);
        return;
    }
    for (int i = 0; i < cpu_data.size(); i++) {
        const auto & cpu_fields = split(cpu_data[i], ' ');
        if (result[i].size() == 0) {
            result[i].resize(10, 0);
        }
        string cpu_name = cpu_fields[0];

        uint64_t user = stol(cpu_fields[1]);
        uint64_t nice = stol(cpu_fields[2]);
        uint64_t system = stol(cpu_fields[3]);
        uint64_t idle = stol(cpu_fields[4]);
        uint64_t iowait = stol(cpu_fields[5]);
        uint64_t irq = stol(cpu_fields[6]);
        uint64_t softirq = stol(cpu_fields[7]);
        uint64_t steal = stol(cpu_fields[8]);
        uint64_t guest = stol(cpu_fields[9]);
        uint64_t guest_nice = stol(cpu_fields[10]);

        uint64_t delta_user = (user - last_stat[i][0]);
        uint64_t delta_nice = (nice - last_stat[i][1]);
        uint64_t delta_system = (system - last_stat[i][2]);
        uint64_t delta_idle = (idle - last_stat[i][3]);
        uint64_t delta_iowait = (iowait - last_stat[i][4]);
        uint64_t delta_irq = (irq - last_stat[i][5]);
        uint64_t delta_softirq = (softirq - last_stat[i][6]);
        uint64_t delta_steal = (steal - last_stat[i][7]);
        uint64_t delta_guest = (guest - last_stat[i][8]);
        uint64_t delta_guest_nice = (guest_nice - last_stat[i][9]);

        auto total_idle = delta_idle + delta_iowait;
        auto total_non_idle = delta_user + delta_nice + delta_system + delta_irq + delta_softirq + delta_steal;
        double total = total_idle + total_non_idle;

        // fill result
        result[i][0] = delta_user  / total * 100;
        result[i][1] = delta_nice / total * 100;
        result[i][2] = delta_system / total * 100;
        result[i][3] = delta_idle / total * 100;
        result[i][4] = delta_iowait / total * 100;
        result[i][5] = delta_irq / total * 100;
        result[i][6] = delta_softirq / total * 100;
        result[i][7] = delta_steal / total * 100;
        result[i][8] = delta_guest / total * 100;
        result[i][9] = delta_guest_nice / total * 100;

        // update last_stat
        last_stat[i][0] = user;

        last_stat[i][1] = nice;
        last_stat[i][2] = system;
        last_stat[i][3] = idle;
        last_stat[i][4] = iowait;
        last_stat[i][5] = irq;
        last_stat[i][6] = softirq;
        last_stat[i][7] = steal;
        last_stat[i][8] = guest;
        last_stat[i][9] = guest_nice;
        cout << right << setw(10) << cpu_name;
        cout << right << setw(10) << result[i][0];
        cout << right << setw(10) << result[i][1];
        cout << right << setw(10) << result[i][2];
        cout << right << setw(10) << result[i][3];
        cout << right << setw(10) << result[i][4];
        cout << right << setw(10) << result[i][5];
        cout << right << setw(10) << result[i][6];
        cout << right << setw(10) << result[i][7];
        cout << right << setw(10) << result[i][8];
        cout << right << setw(10) << result[i][9] << endl;
    }
}


int main() {
    ifstream file("/proc/stat");
    while (true) {
        cal_one(file);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    file.close();
    return 0;
}
