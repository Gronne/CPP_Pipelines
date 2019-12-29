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
#include <cctype>
#include <algorithm>


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

//Functor example
struct ReduceFunctor
{
  void operator()(map<string, vector<string>> &in, map<string, int> &out) {
    for_each(in.begin(), in.end(), [&out](tuple<string, vector<string>> pair){
      // accumelate vector in pair
      // insert new pair with pair key as key and accumelate result as value into out
    });
  }
};

int main() {
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
        this_thread::sleep_for(chrono::milliseconds(2));
        continue;
      }
      
      // Find words in line. Ignore non-word characters
      // https://en.cppreference.com/w/cpp/regex
      std::regex re("(\\w+)", std::regex_constants::ECMAScript);
      auto words_begin = sregex_iterator(line.begin(), line.end(), re);
      auto words_end = sregex_iterator();

      for (sregex_iterator i = words_begin; i != words_end; ++i) {
          string match = (*i).str();
          // algorithm 
          // https://en.cppreference.com/w/cpp/string/byte/tolower
          transform(match.begin(), 
                    match.end(), 
                    match.begin(), 
                    [](unsigned char c){ return tolower(c); }
                   );
          out.push(std::move(match));
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
  

  auto f3 = TaskFactory::start_async_task([](PipeQueue<string> &in, std::map<string, PipeQueue<string>> &map){
    cout << "Started to map words " << endl << flush;
    while(!in.eof())
    {
      string word;
      if(!in.try_pop(word))
      {
        this_thread::sleep_for(chrono::milliseconds(2));
        continue;
      }
      
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
  //todo create future for ReduceFunctor

  cout << "Waiting for all end" << endl;

  TaskFactory::wait_all(f1, f2, f3);

  cout << "wait_all done" << endl;
  auto t = map.find("alone");
  cout << "Word 'Alone' count: " << t->second.size() << endl;

  //PipeQueue<string, std::vector<int>> test; // Test that another type in the vec
}