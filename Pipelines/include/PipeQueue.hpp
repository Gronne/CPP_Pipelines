#include <deque>
#include <mutex>
#include <utility>
#include <queue>

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
  template<typename T, typename Container = std::deque<T>>
  class PipeQueue
  {
  private:
    Container container_;
    std::mutex access_lock_;
    bool is_eof_;
  public:
    PipeQueue() : container_(), is_eof_(false)
    {
      static_assert(std::is_same<T, typename Container::value_type>::value, "T and value type of container is not the same");
      // static_assert(container_implements<)
    }
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

    const ssize_t size() {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_.size();
    }

    bool operator<(PipeQueue& other)
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      if (container_.size() < other.size())
        return true;
      else
        return false;
    }

    template<typename H>
    friend PipeQueue<H>& operator<<(PipeQueue<H>& pipe, H&& input);


    template<typename H>
    friend H& operator>>(PipeQueue<H>& pipe, H& output);
    
    
    void push(T&& value) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.push_back(std::move(value));
    }

    void push(const T & value) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.push_back(value);
    }

    const T& unsafe_front()
    {
      return container_.front();
    }

    bool try_pop(T & t) {
      std::lock_guard<std::mutex> lock(access_lock_);
      if(container_.empty())
        return false;
      t = std::move(container_.front());
      container_.pop_front();
      return true;
    }

    bool empty() 
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_.empty();
    }

    void clear()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.clear();
    }


    // Can
    bool eof()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      return is_eof_ && container_.empty();
    }

    void set_eof()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      is_eof_ = true;
    }
  };

  template<typename H>
  PipeQueue<H>& operator<<(PipeQueue<H>&  pipe, H&& input)
  {
    pipe.push_back(std::move(input));
    return pipe;
  }


  template<typename H>
  H& operator>>(PipeQueue<H>& pipe, H& output)
  {
    output = pipe.front();
    pipe.pop_front();
    return output;
  }
  
}