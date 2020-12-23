#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <atomic>
#include <functional>
#include <vector>


static constexpr int N = 12;
static constexpr int M = 12;


/*!
* Algoritm sieve
*/

std::atomic<int> x0(0), x1(0), x2(0), x3(0), x4(0), x5(0),
                x6(0), x7(0), x8(0), x9(0), x10(0), x11(0);


struct read_num {
    int x0, x1, x2, x3, x4, x5,
    x6, x7, x8, x9, x10, x11;
};

read_num val0[N];
read_num val1[N];
read_num val2[N];
read_num val3[N];
read_num val4[N];
read_num val5[N];
read_num val6[N];
read_num val7[N];
read_num val8[N];
read_num val9[N];
read_num val10[N];
read_num val11[N];


bool Algorithm(std::atomic_int* var_to_int) {
    std::this_thread::yield();
    int j = M - 1;

    while (j >= 0 && var_to_int[j] == N - 1) j--;
    if (j < 0) return false;
    if (var_to_int[j] >= N - 1) j--;
    var_to_int->store(j + 1, std::memory_order_relaxed);
    if (j == M - 1) return true;
    for (int k = j + 1; k < M; k++) {
        var_to_int->store(1, std::memory_order_relaxed);
    }
    std::this_thread::yield();
    return true;
}

void init_set(std::atomic_int* var_to_int, read_num* values)
{
    std::this_thread::yield();
        static unsigned long long num = 1;
        int tmp1{};
        int tmp2{};


        for (int i = 0; i < N; i++) {
            values[i].x0 = x0.load(std::memory_order_relaxed);
            values[i].x1 = x1.load(std::memory_order_relaxed);
            values[i].x2 = x2.load(std::memory_order_relaxed);
            values[i].x3 = x3.load(std::memory_order_relaxed);
            values[i].x4 = x4.load(std::memory_order_relaxed);
            values[i].x5 = x5.load(std::memory_order_relaxed);
            values[i].x6 = x6.load(std::memory_order_relaxed);
            values[i].x7 = x7.load(std::memory_order_relaxed);
            values[i].x8 = x8.load(std::memory_order_relaxed);
            values[i].x9 = x9.load(std::memory_order_relaxed);
            values[i].x10 = x10.load(std::memory_order_relaxed);
            values[i].x11 = x11.load(std::memory_order_relaxed);
            var_to_int->store(i, std::memory_order_relaxed);
            tmp1 = values[i].x0+values[i].x1+values[i].x2+values[i].x3+values[i].x4+values[i].x5;
            tmp2 = values[i].x6+values[i].x7+values[i].x8+values[i].x9+values[i].x10+values[i].x11;
        }
        std::this_thread::yield();
        if(tmp1 == tmp2) {
            std::cout << "num: " << num++ << ": ";
            std::cout << std::endl;
        }

}

int main()
{

      std::vector<std::thread> vec_thread;

      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x0)) init_set(&x0, val0); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x1)) init_set(&x1, val1); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x2)) init_set(&x2, val2); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x3)) init_set(&x3, val3); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x4)) init_set(&x4, val4); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x5)) init_set(&x5, val5); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x6)) init_set(&x6, val6); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x7)) init_set(&x7, val7); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x8)) init_set(&x8, val8); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x9)) init_set(&x9, val9); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x10)) init_set(&x10, val10); }));
      vec_thread.push_back(std::thread([&]() {
          while (Algorithm(&x11)) init_set(&x11, val11); }));

      for (auto& x : vec_thread) {
         x.join();
      }

      return 0;
}
