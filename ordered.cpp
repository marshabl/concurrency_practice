#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

int num_threads = 10;
std::atomic<int> atomicValue;
std::atomic<int> counter;

void updateCounter(int threadID, std::atomic<int> * c, std::atomic<int> * av) {
  while((*av).load()!=threadID);
  (*c)++;
  std::cout << "Thread ID: " << threadID << " shared variable: " << *c << '\n';
  (*av)++;
}

int main() {
  atomicValue = true;
  counter = 0;
  std::vector<std::thread> threads;

  for (int i=1; i<=num_threads; ++i) {
    threads.push_back(std::thread(updateCounter, i, &counter, &atomicValue));
  }

  for (std::thread & th : threads)
  {
      if (th.joinable())
          th.join();
  }

  return 0;

}
