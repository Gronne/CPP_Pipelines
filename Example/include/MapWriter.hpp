#ifndef MAPWRITER_HPP
#define MAPWRITER_HPP
#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

class MapWriter
{
private:
  std::string path_;

public:
  MapWriter(std::string &&path);
  ~MapWriter();
  template <typename K, typename V> 
	void writeMap(std::map<K, V> &map);
};

MapWriter::MapWriter(std::string &&path) : path_(std::move(path)) {}

MapWriter::~MapWriter() {}

template <typename K, typename V> // TODO SFINAE
void MapWriter::writeMap(std::map<K, V> &map) {
  // https://thispointer.com/how-to-sort-a-map-by-value-in-c/
	typedef std::function<bool(std::pair<K,V> const &, std::pair<K,V> const&)> Comparator;

  Comparator leastFirst = [](std::pair<K, V> const & a, std::pair<K, V> const & b) {
    return a.second < b.second;
  };

  Comparator largestFirst = [](std::pair<K, V> const & a, std::pair<K, V> const & b) {
    return a.second > b.second;
  };

	std::vector<std::pair<K, V>> sorted(map.begin(), map.end());
	std::sort(sorted.begin(), sorted.end(), largestFirst);

  std::ofstream file(path_, std::ios::trunc);
  file.exceptions(std::ifstream::failbit |
                  std::ifstream::badbit); // rethrow exception
  try
  {
		file << "Word: count" << std::endl;
    std::for_each(sorted.begin(), sorted.end(), [&file](std::pair<K, V> const & pair) {
			file << pair.first << ": " << pair.second << std::endl;
    });
  }
  catch (std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }
}

#endif