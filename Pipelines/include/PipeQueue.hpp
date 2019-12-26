#include <deque>
#include <mutex>
#include <utility>

/*
* TODO LIST:
* - Add EOF signal
* - Rule of x
* - Move none template functions to cpp
* QUESTIONS: 
* - Do we need all the compare operators? I assume we don't intend to perform 
    algorithms on this container
* NOTE: 
* - Class naming uses Pascal casing
* - Snake case is used on container in attempt to keep the common interface
* - Otherwise camel casing is used
*/


namespace PLS
{
  template<class T, class Container = std::deque<T>>
  class PipeQueue
  {
  private:
    Container container;
    std::mutex access_lock;
    bool is_eof;
  public:
    PipeQueue() : container()
    {}
    ~PipeQueue()
    {
      // May be omitted
    }
    
    void push_back(T&& item)
    {
      std::lock_guard<std::mutex> lock(access_lock); // RIIA style lock for current scope
      container.push_back(std::move(item));
    }

    T &&front()
    {
      std::lock_guard<std::mutex> lock(access_lock);
      return std::move(container.front());
    }

    // Can be moved to cpp file
    void pop_front()
    {
      std::lock_guard<std::mutex> lock(access_lock);
      container.pop_front();
    }

    // Can
    bool eof()
    {
      return is_eof && container.empty();
    }

    void set_eof()
    {
      is_eof = true;
    }
  };
}