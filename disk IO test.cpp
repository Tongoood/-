#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstring>

using namespace std;
using namespace std::chrono;

// 函数来生成测试数据
vector<char> generate_test_data(size_t size) {
    return vector<char>(size, 0);
}

// 函数来写入测试数据到文件
void write_test_file(const string& file_path, size_t size) {
    auto data = generate_test_data(size);
    ofstream file(file_path, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Failed to open file for writing: " << file_path << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    file.write(data.data(), data.size());
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;
    cout << "Write completed in " << elapsed.count() << " seconds" << endl;
    cout << "Write speed: " << size / elapsed.count() / (1024 * 1024) << " MB/s" << endl;

    file.close();
}

// 函数来读取文件并测量性能
void read_test_file(const string& file_path, size_t size) {
    vector<char> data(size);
    ifstream file(file_path, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Failed to open file for reading: " << file_path << endl;
        return;
    }

    auto start = high_resolution_clock::now();
    file.read(data.data(), data.size());
    auto end = high_resolution_clock::now();

    duration<double> elapsed = end - start;
    cout << "Read completed in " << elapsed.count() << " seconds" << endl;
    cout << "Read speed: " << size / elapsed.count() / (1024 * 1024) << " MB/s" << endl;

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    string file_path = argv[1];
    size_t file_size = 10 * 1024 * 1024 * 1024; // 10 GB

    cout << "Testing write performance..." << endl;
    write_test_file(file_path, file_size);

    cout << "Testing read performance..." << endl;
    read_test_file(file_path, file_size);

    return 0;
}
