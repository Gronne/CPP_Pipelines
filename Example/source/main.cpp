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
#include "MapWriter.hpp"



void readFile(const std::vector<std::string> &file_address_list, PLS::PipeQueue<std::string>& out)
{
  for(auto &address : file_address_list)
  {
    std::cout << "readFile: path: "<< address << std::endl << std::flush;
    std::ifstream input(address);
    if(input.is_open())
    {
      std::string line;
      while (std::getline(input, line))
        out.push(std::move(line));
    }
    else
      std::cout << "failed to open " << address << std::endl << std::flush;
  }
    
  std::cout << "Done reading files" << std::endl << std::flush;
  out.set_eof(); 
}


//Functor example
struct MapReduceFunctor
{
  void operator()(PLS::PipeQueue<std::string> &in, std::map<std::string, int> &map) {
    std::cout << "Started to map words " << std::endl << std::flush;
    while(!in.eof())
    {
      std::string word;
      if(!in.try_pop(word))
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        continue;
      }

      if(map.find(word) == map.end())
        map.insert_or_assign(word, 1);

      map[word]++;
    }
    std::cout << "Mapping done" << std::endl;
  }
};


int main(int argc, char *argv[]) {
  if(argc < 2)
    exit(0);

  std::vector<std::string> valid_address_list;

  std::for_each(&argv[1], &argv[argc], [&valid_address_list](const std::string &argument) {
    if(std::ifstream(argument).good())
      valid_address_list.push_back(argument);
    else 
      std::cout << "File does not exist: " << argument << std::endl;
  });


  decltype(auto) splitLineToWords = [](PLS::PipeQueue<std::string>& in, PLS::PipeQueue<std::string>& out) {
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

          out.push(std::move(match));
      }
    }

    std::cout << "Done reading words" << std::endl << std::flush;
    out.set_eof();
  };


  PLS::PipeQueue<std::string> lines, words;
  std::map<std::string, int> map;

  std::cout << "Starting to get lines" << std::endl;
  std::future<void> f1 = PLS::TaskFactory::start_async_task(::readFile, valid_address_list, lines); // Read lines from books

  std::cout << "Starting to get words" << std::endl;
  std::future<void> f2 = PLS::TaskFactory::start_async_task(splitLineToWords, lines, words); // Test with lambda

  std::cout << "Starting to map and reduce words" << std::endl;
  auto f3 = PLS::TaskFactory::start_async_task(MapReduceFunctor(), words, map);

  std::cout << "Waiting for all end" << std::endl;
  PLS::TaskFactory::wait_all(f1, f2, f3);

  MapWriter map_writer("MapReducedBooks.txt");
  map_writer.writeMap(map);

  // std::cout << "wait_all done" << std::endl;
  // auto t = map.find("alone");
  // std::cout << "Word 'Alone' count: " << t->second << std::endl;

  //PLS::PipeQueue<std::string, std::vector<int>> test; // Test that another type in the vec
}