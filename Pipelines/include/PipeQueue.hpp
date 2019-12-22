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
    {

    }
    ~PipeQueue()
    {

    }
    void push_back(T&& item)
    {
      std::lock_guard<std::mutex> lock(access_lock); // RIIA style lock for current scope
      container.push_back(item);
    }
    T &&pop_front()
    {
      std::lock_guard<std::mutex> lock(access_lock);
      return std::move(container.pop_front());
    }
  };
}