#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PipeQueue.hpp"
#include "TaskFactory.hpp"


using namespace std;
using namespace PLS;

void readFile(string path, PipeQueue<string>& out)
{
  ifstream input(path);
  if(input.is_open())
  {
    while (!input.eof())
    {
      string line;
      getline(input, line);
      out.push_back(std::move(line));
    }
  }
}

int main()
{
  //std::cout << "Hello world!" << std::endl;
  PipeQueue<string> lines, words;

  decltype(auto) lambda = [](PipeQueue<string>& in, PipeQueue<string>& out) {
    while(true)
    {
      stringstream line(in.front());
      string word;
      in.pop_front();
      
      while (line >> word)
        out.push_back(std::move(word));
    }
  };

  function f = lambda;
  string filePath = "Books/Dracula.txt";

  TaskFactory factory;
  cout << "Starting to get lines" << endl;
  auto t1 = factory.startAsyncTask(readFile, filePath, lines); // Read lines from books
  cout << "Starting to get words" << endl;
  future<void> t2 = factory.startAsyncTaskThreaded(lambda, lines, words); // Test with lambda

  cout << "Starting t1" << endl;
  t1(filePath, lines);
  cout << "Waiting for t1 to end" << endl;
  t1.get_future().wait();
  cout << "Waiting for t2 to end" << endl;
  t2.wait();


  

}