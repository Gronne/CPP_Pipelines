#ifndef TASKFACTORY_HPP
#define TASKFACTORY_HPP
#include <functional>
#include <future>
#include <type_traits>

namespace PLS {
  //SFINAE check for function has_wait
  template<typename T, typename = void>
  struct has_wait : std::false_type { };

  template<typename T>
  struct has_wait<T, std::void_t<decltype(std::declval<T>().wait())> > : std::true_type { };
  

  template<typename... Args>
  using is_awaitable = std::conjunction<has_wait<Args>...>;


  class TaskFactory
  {
  private:
    /* data */
  public:
    TaskFactory();
    ~TaskFactory();

    template<typename T, typename...Args>
    void wait_all(T&& first, Args&& ...args)
    {
      static_assert(is_awaitable<Args...>::value, "Argument in TaskFactory::wait_all(...) does not implement the wait function");
      first.wait();
      wait_all(args...);
    }

    template<typename T>
    void wait_all(T&& future)
    {
      future.wait();
    }

    

    template<class F, class... Args, typename R = std::result_of_t<std::decay_t<F>&&(Args...)>>
    std::future<R> startAsyncTask(F&& callable, Args&&... args)
    {
      std::future<R> task = std::async(std::launch::async, callable, std::ref(args)...); 
      return task;
    }
  };  
}

#endif