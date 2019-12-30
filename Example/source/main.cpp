#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <regex>
#include <iterator>
#include <thread>
#include <chrono>
#include <cctype>
#include <algorithm>

#include "PipeQueue.hpp"
#include "TaskFactory.hpp"



void readFile(const std::vector<std::string> &file_address_list, PLS::PipeQueue<std::string>& out)
{
  for(auto &path : file_address_list)
  {
    std::cout << "readFile: path: "<< path << std::endl << std::flush;
    std::ifstream input(path);
    if(input.is_open())
    {
      std::string line;
      while (std::getline(input, line))
        out << std::move(line);
    }
    else
      std::cout << "failed to open " << path << std::endl << std::flush;
    }
    
  std::cout << "Done reading files" << std::endl << std::flush;
  out.set_eof(); 
}


//Functor example
struct ReduceFunctor
{
  void operator()(std::map<std::string, std::vector<std::string>> &in, std::map<std::string, int> &out) {
    for_each(in.begin(), in.end(), [&out](std::tuple<std::string, std::vector<std::string>> pair){
      // accumelate vector in pair
      // insert new pair with pair key as key and accumelate result as value into out
    });
  }
};




int main(int argc, char *argv[]) {
  if(argc < 2)
    exit(0);

  std::vector<std::string> main_argument_list;

  std::for_each(&argv[1], &argv[argc], [&main_argument_list](const std::string &argument) {
    if(std::ifstream(argument).good())
      main_argument_list.push_back(argument);
    else 
      std::cout << "File does not exist: " << argument << std::endl;
  });



  //std::std::cout << "Hello world!" << std::std::endl;
  PLS::PipeQueue<std::string> lines, words;
  std::map<std::string, PLS::PipeQueue<std::string>> map;

  decltype(auto) lambda = [](PLS::PipeQueue<std::string>& in, PLS::PipeQueue<std::string>& out) {
    std::cout << "Started to read words" << std::endl << std::flush;
    
    while(in.eof() == false)
    {
      std::string line;

      if(in.try_pop(line) == false)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        continue;
      }
      
      // Find words in line. Ignore non-word characters
      // https://en.cppreference.com/w/cpp/regex
      std::regex re("(\\w+)", std::regex_constants::ECMAScript);
      auto words_begin = std::sregex_iterator(line.begin(), line.end(), re);
      auto words_end = std::sregex_iterator();

      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
          std::string match = (*i).str();
          // algorithm 
          // https://en.cppreference.com/w/cpp/std::string/byte/tolower
          transform(match.begin(), 
                    match.end(), 
                    match.begin(), 
                    [](unsigned char c){ return tolower(c); }
                   );

          out << std::move(match);
      }
    }

    std::cout << "Done reading words" << std::endl << std::flush;
    out.set_eof();
  };



  std::cout << "Starting to get lines" << std::endl;
  std::future<void> f1 = PLS::TaskFactory::start_async_task(::readFile, main_argument_list, lines); // Read lines from books

  std::cout << "Starting to get words" << std::endl;
  std::future<void> f2 = PLS::TaskFactory::start_async_task(lambda, lines, words); // Test with lambda

  std::cout << "Starting to map words" << std::endl;
  auto f3 = PLS::TaskFactory::start_async_task([](PLS::PipeQueue<std::string> &in, std::map<std::string, PLS::PipeQueue<std::string>> &map){
    std::cout << "Started to map words " << std::endl << std::flush;
    while(!in.eof())
    {
      std::string word;
      if(!in.try_pop(word))
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
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
        PLS::PipeQueue<std::string> q;
        q.push(word);
        map.insert_or_assign(word, q);
      }
    }
    std::cout << "Mapping done" << std::endl;
  },
  words,
  map);
  //todo create std::future for ReduceFunctor

  std::cout << "Waiting for all end" << std::endl;

  PLS::TaskFactory::wait_all(f1, f2, f3);

  std::cout << "wait_all done" << std::endl;
  auto t = map.find("alone");
  std::cout << "Word 'Alone' count: " << t->second.size() << std::endl;

  //PLS::PipeQueue<std::string, std::vector<int>> test; // Test that another type in the vec
}