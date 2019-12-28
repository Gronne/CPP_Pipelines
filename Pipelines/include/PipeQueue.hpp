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
    Container container_;
    std::mutex access_lock_;

  public:
    PipeQueue() : container_()
    {}
    ~PipeQueue()
    {
      // May be omitted
    }

    //Copy Constructer
    PipeQueue(const PipeQueue &other)
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = other.container_;
    }

    //Move Constructor
    PipeQueue(PipeQueue&& other)
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = std::move(other.container_);
    }

    //Copy Assignment
    PipeQueue& operator=(const PipeQueue& other)
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = other.container_;
      return *this;
    }

    //Move Assignment
    PipeQueue& operator=(PipeQueue&& other)
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = std::move(other.container_);
      return *this;
    }
    
    
    void push_back(T&& item)
    {
      std::lock_guard<std::mutex> lock(access_lock_); // RIIA style lock for current scope
      container_.push_back(std::move(item));
    }

    T &&front()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      return std::move(container_.front());
    }

    // Can be moved to cpp file
    void pop_front()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.pop_front();
    }
  };
}