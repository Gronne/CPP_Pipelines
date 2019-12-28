#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PipeQueue.hpp"
#include "TaskFactory.hpp"


using namespace std;
using namespace PLS;

void readFile(string& path, PipeQueue<string>& out)
{
  cout << "readFile: path: "<< path << endl;
  ifstream input(path);
  int i = 0;
  if(input.is_open())
  {
    while (!input.eof())
    {
      string line;
      getline(input, line);
      out.push_back(std::move(line));
      if(++i%1000 == 0)
        cout << "readFile count: " << i << endl;
    }
  }
  else
  {
    cout << "failed to open " << path << endl;
  }
  out.set_eof(); 
}

int main()
{
  //std::cout << "Hello world!" << std::endl;
  PipeQueue<string> lines, words;

  decltype(auto) lambda = [](PipeQueue<string>& in, PipeQueue<string>& out) {
    int i = 0;
    while(!in.eof())
    {
      stringstream line(in.front());
      string word;
      in.pop_front();
      
      while (line >> word)
        out.push_back(std::move(word));
      if(++i%10000 == 0)
        cout << "Lines read in lambda: " << i << endl;
    }
    out.set_eof();
  };

  function f = lambda;
  string filePath = "Example/Books/Dracula.txt";

  TaskFactory factory;
  cout << "Starting to get lines" << endl;
  future<void> f1 = factory.startAsyncTask(readFile, filePath, lines); // Read lines from books
  cout << "Starting to get words" << endl;
  future<void> f2 = factory.startAsyncTask(lambda, lines, words); // Test with lambda

  cout << "Waiting for all end" << endl;
  factory.wait_all(f1, f2);
}