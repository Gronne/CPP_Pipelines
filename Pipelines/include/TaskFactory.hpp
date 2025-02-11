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
  public:
    template<typename T, typename...Args>
    static void wait_all(T&& awaitable, Args&& ...args)
    {
      static_assert(is_awaitable<Args...>::value, "Argument in TaskFactory::wait_all(...) does not implement the wait function");
      awaitable.wait();
      wait_all(args...);
    }


    template<typename T>
    static void wait_all(T&& awaitable)
    {
      awaitable.wait();
    }

    template<typename F, typename... Args, typename R = std::result_of_t<std::decay_t<F>&&(Args...)>>
    static std::future<R> start_async_task(F&& callable, Args&&... args)
    {
      std::future<R> task = std::async(std::launch::async, callable, std::ref(args)...); 
      return task;
    }
  };  
}

#endif