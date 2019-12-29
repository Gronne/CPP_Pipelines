#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PipeQueue.hpp"
#include "TaskFactory.hpp"
#include <map>
#include <regex>
#include <iterator>
#include <thread>
#include <chrono>


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
      string line;

      if(!in.try_pop(line))
      {
        std::cout << "No item in 'in'" << endl << flush;
        this_thread::sleep_for(chrono::seconds(1));
        continue;
      }
      cout << line << endl << flush;
      
      // Find words in line. Ignore non-word characters
      // https://en.cppreference.com/w/cpp/regex
      std::regex re("(\\w+))", std::regex_constants::ECMAScript);
      this_thread::sleep_for(chrono::seconds(1));
      auto words_begin = 
        sregex_iterator(line.begin(), line.end(), re);
      auto words_end = sregex_iterator();

      for (sregex_iterator i = words_begin; i != words_end; ++i) {
          smatch match = *i;
          cout << match.str() << flush;
          out.push(match.str());
      }
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
  auto f3 = TaskFactory::start_async_task([](PipeQueue<string> &in, std::map<string, PipeQueue<string>> &map){
    cout << "Started to map words " << endl << flush;
    while(!in.eof())
    {
      string word;
      if(!in.try_pop(word))
        continue;
      
      auto temp = map.find(word);
      if(map.end() != temp)
      {
        temp->second.push(word);
        map.insert_or_assign(word, temp->second);
      }
      else
      {
        PipeQueue<string> q;
        q.push(word);
        map.insert_or_assign(word, q);
      }
    }
    cout << "Mapping done" << endl;
  },
  words,
  map);

  cout << "Waiting for all end" << endl;

  TaskFactory::wait_all(f1, f2, f3);

  cout << "wait_all done" << endl;
  auto t = map.find("alone.");
  cout << "Word 'alone' count: " << t->second.size() << endl;

  //PipeQueue<string, std::vector<int>> test; // Test that another type in the vec
}