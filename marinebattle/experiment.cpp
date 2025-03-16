#include <iostream>
#include <random>

int main() {
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<> u_d1{0, 9};

  int i = u_d1(mt);

  std::cout << i;
}