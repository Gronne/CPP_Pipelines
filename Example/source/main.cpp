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
  map<string, PipeQueue<string>> map;

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

  cout << "Starting to get lines" << endl;
  future<void> f1 = TaskFactory::startAsyncTask(readFile, filePath, lines); // Read lines from books
  cout << "Starting to get words" << endl;
  future<void> f2 = TaskFactory::startAsyncTask(lambda, lines, words); // Test with lambda
  cout << "Starting to map words" << endl;
  
  // TODO: DOES NOT WORK YET
  auto f3 = TaskFactory::startAsyncTask([](PipeQueue<string> &in, std::map<string, PipeQueue<string>> &map){
    while(!in.eof())
    {
      string word(in.front());
      in.pop_front();
      
      auto temp = map.find(word);
      if(map.end() != temp)
      {
        temp->second.push_back(word);
        map.insert_or_assign(temp->second.front(), temp->second);
      }
      else
      {
        PipeQueue<string> q;
        q.push_back(word);
        map.insert_or_assign(q.front(), q);
      }
    }
    cout << "Mapping done" << endl;
  },
  words,
  map);

  cout << "Waiting for all end" << endl;
  TaskFactory::wait_all(f1, f2, f3);

  auto t = map.find("why");
  cout << "Word why count: " << t->second.size() << endl;

  //PipeQueue<string, std::vector<int>> test; // Test that another type in the vec
}