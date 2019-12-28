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

// namespace PipeQueue
// {
// namespace Traits
// {
//   //SFINAE check for function has_wait
//   template<typename T, typename = void>
//   struct has_wait : std::false_type { };

//   template<typename T>
//   struct has_wait<T, std::void_t<decltype(std::declval<T>().wait())> > : std::true_type { };
  

//   template<typename >
//   using is_same = std::conjunction<has_wait<Args>...>;
// }
// }




  template<typename T, typename Container = std::deque<T>>
  class PipeQueue
  {
  private:
    Container container_;
    std::mutex access_lock_;
    bool is_eof_;
  public:
    PipeQueue() : container_()
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
      return container_.size();
    }
    
    
    void push_back(T&& value) {
      std::lock_guard<std::mutex> lock(access_lock_); // RIIA style lock for current scope
      container_.push_back(std::move(value));
    }

    void push_back(const T & value) {
      container_.push_back(value);
    }

    T &&front() {
      std::lock_guard<std::mutex> lock(access_lock_);
      return std::move(container_.front());
    }

    // Can be moved to cpp file
    void pop_front()
    {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.pop_front();
    }

    // Can
    bool eof()
    {
      return is_eof_ && container_.empty();
    }

    void set_eof()
    {
      is_eof_ = true;
    }
  };
}