#include <deque>
#include <mutex>
#include <utility>
#include <queue>



namespace PLS
{
  //TODO could use SFINAE to evaluate if Container has the necessary functions?
  template<typename T, typename Container = std::deque<T>>
  class PipeQueue
  {
  private:
    Container container_;
    std::mutex access_lock_;
    bool is_eof_;

    
  public:
    PipeQueue() : container_(), is_eof_(false) {
      static_assert(std::is_same<T, 
                    typename Container::value_type>::value, 
                    "T and value type of container is not the same");
    }
    ~PipeQueue() { }

    //Initialization Constructor
    PipeQueue(std::initializer_list<T> t_list) : PipeQueue() {
      for(auto &t : t_list)
        push(t);
    }

    //Copy Constructer
    PipeQueue(const PipeQueue &other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = other.container_;
    }

    //Move Constructor
    PipeQueue(PipeQueue&& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = std::move(other.container_);
    }


    ssize_t size()  {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_.size();
    }

    bool empty()  {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_.empty();
    }

    void clear()  {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.clear();
    }


    void push(T&& value) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.push_back(std::move(value));
    }

    void push(const T & value) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.push_back(value);
    }


    bool try_pop(T & t) {
      std::lock_guard<std::mutex> lock(access_lock_);

      if(container_.empty())
        return false;

      t = std::move(container_.front());
      container_.pop_front();

      return true;
    }
    

    void swap(PipeQueue& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_.swap(other.container_);
    }


    // Can
    bool eof() {
      std::lock_guard<std::mutex> lock(access_lock_);
      return is_eof_ && container_.empty();
    }

    void set_eof() {
      std::lock_guard<std::mutex> lock(access_lock_);
      is_eof_ = true;
    }


    //Copy Assignment
    PipeQueue& operator=(const PipeQueue& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = other.container_;
      return *this;
    }

    //Move Assignment
    PipeQueue& operator=(PipeQueue&& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      container_ = std::move(other.container_);
      return *this;
    }

    bool operator<(PipeQueue& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_.size() < other.size();
    }

    bool operator==(PipeQueue& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      return container_ == other.container_;
    }

    bool operator!=(PipeQueue& other) {
      std::lock_guard<std::mutex> lock(access_lock_);
      return (container_ == other.container_) == false;
    }    
  };
  
}