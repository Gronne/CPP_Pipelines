#include <deque>
#include <mutex>
#include <utility>



namespace PLS
{
  template<class T, class Container = std::deque<T>>
  class PipeQueue
  {
  private:
    Container container;
    std::mutex access_lock;
  public:
    PipeQueue() : container()
    {}
    ~PipeQueue()
    {
      // May be omitted
    }
    //TODO rule of X
    // copy constructor
    // assignment operator
    // move constructor
    // move assignment operator
    
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
  };
}