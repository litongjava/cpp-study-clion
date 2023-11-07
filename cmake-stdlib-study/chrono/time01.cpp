#include <iostream>
#include <chrono>
#include <thread>

int main() {
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(std::chrono::seconds(2)); // pause for 2 seconds
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  auto duration = end - start;
  long long int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  std::cout << "Time elapsed: " << elapsed << " ms" << std::endl;

  return 0;
}