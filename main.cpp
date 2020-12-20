#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <atomic>
#include <functional>
#include <vector>

#include <omp.h>

static constexpr int N = 13;
static constexpr int M = 13;

static constexpr int H = N > M ? N : M;

/*!
* Algoritm sieve
*/

std::mutex mutex;


bool Algorithm(int* arr) {
    int j = M - 1;
    while (j >= 0 && arr[j] == N - 1) j--;
    if (j < 0) return false;
    if (arr[j] >= N - 1) j--;
    arr[j]++;
    if (j == M - 1) return true;
    for (int k = j + 1; k < M; k++) {
        arr[k] = 1;
    }
    return true;
}

void init_set(int *arr, int count)
{
#pragma omp parallel
    {
        static unsigned long long num = 1;
        int tmp1{};
        int tmp2{};
#pragma omp for
        for (int i = 0; i < N; i++) {
            if(i < 6) tmp1 += arr[i];
            else if(i > 6) tmp2 += arr[i];
        }
        if(tmp1 == tmp2) {
            std::cout << num++ << ": ";
#pragma omp for
            for (int i = 0; i < N; i++) {
                if(arr[i] == 10) std::cout << 'A' << "";
                else if(arr[i] == 11) std::cout << 'B' << "";
                else if(arr[i] == 12) std::cout << 'C' << "";
                else std::cout << arr[i] << "";
            }
            std::cout << "; " << std::endl;
        }
    }
}

int main()
{

     int count{};
      auto arr = new int[H];

      auto num_thred = (std::thread::hardware_concurrency() > 0) ? std::thread::hardware_concurrency() : 8;

      for (int i = 0; i < H; i++) arr[i] = 0;
      auto Loowp([&](auto& count) {
          while (Algorithm(arr)) init_set(arr, count);
      });
      auto second_task = std::async(std::launch::async, std::bind(Loowp, std::ref(count)));

      second_task.get();
//      unsigned long long i;
//      #pragma omp parallel shared(arr, count, N) private(i)
//      {
//          #pragma omp parallel for

//              for (i = 0; i < N*N*N*N*N*N*N*N*N*N*N*N*N; ++i) {
//                  if(Algorithm(arr)) init_set(arr, count);
//              }

//      }

      return 0;
}
