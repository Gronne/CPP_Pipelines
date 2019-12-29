#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PipeQueue.hpp"
#include "TaskFactory.hpp"
#include <map>


using namespace std;
using namespace PLS;

void readFile(string& path, PipeQueue<string>& out)
{
  cout << "readFile: path: "<< path << endl << flush;
  ifstream input(path);
  if(input.is_open())
  {
    while (!input.eof())
    {
      string line;
      getline(input, line);
      out.push(std::move(line));
    }
  }
  else
  {
    cout << "failed to open " << path << endl << flush;
  }
  cout << "Done reading files" << endl << flush;
  out.set_eof(); 
}

int main()
{
  //std::cout << "Hello world!" << std::endl;
  PipeQueue<string> lines, words;
  map<string, PipeQueue<string>> map;

  decltype(auto) lambda = [](PipeQueue<string>& in, PipeQueue<string>& out) {
    cout << "Started to read words" << endl << flush;
    while(!in.eof())
    {
      stringstream line(in.pop());
      string word;
      
      while (line >> word)
        out.push(std::move(word));
        
    }
  cout << "Done reading words" << endl << flush;
    out.set_eof();
  };

  function f = lambda;
  string filePath = "Example/Books/Dracula.txt";

  cout << "Starting to get lines" << endl;
  future<void> f1 = TaskFactory::start_async_task(readFile, filePath, lines); // Read lines from books
  cout << "Starting to get words" << endl;
  future<void> f2 = TaskFactory::start_async_task(lambda, lines, words); // Test with lambda
  cout << "Starting to map words" << endl;
  
  // TODO: DOES NOT WORK YET
  // auto f3 = TaskFactory::start_async_task([](PipeQueue<string> &in, std::map<string, PipeQueue<string>> &map){
  //   cout << "Started to map words " << endl << flush;
  //   while(!in.eof())
  //   {
  //     string word(in.pop());
      
  //     auto temp = map.find(word);
  //     if(map.end() != temp)
  //     {
  //       temp->second.push(word);
  //       map.insert_or_assign(temp->second.front(), temp->second);
  //     }
  //     else
  //     {
  //       PipeQueue<string> q;
  //       q.push(word);
  //       map.insert_or_assign(q.front(), q);
  //     }
  //   }
  //   cout << "Mapping done" << endl;
  // },
  // words,
  // map);

  cout << "Waiting for all end" << endl;

  TaskFactory::wait_all(f1, f2);

  cout << "wait_all done" << endl;
  //auto t = map.find("alone");
  //cout << "Word why count: " << t->second.size() << endl;

  //PipeQueue<string, std::vector<int>> test; // Test that another type in the vec
}