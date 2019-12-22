#include <iostream>
#include <string>
#include "PipeQueue.hpp"

using namespace std;

int main()
{
  //std::cout << "Hello world!" << std::endl;
  PLS::PipeQueue<std::string> testQueue;
  testQueue.push_back("Hello");
  testQueue.push_back(", world!");
  cout << testQueue.front() << endl;
  testQueue.pop_front();
  cout << testQueue.front() << endl;
  testQueue.pop_front();
}