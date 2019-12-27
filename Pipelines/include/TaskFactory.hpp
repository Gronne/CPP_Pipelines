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

    template<class...Args>
    void wait_all(Args&& ...args)
    {
      static_assert(is_awaitable<Args...>::value, "Argument in TaskFactory::wait_all(...) does not implement the wait function");
    }
    

    template<class F, class... Args, typename R = std::result_of_t<std::decay_t<F>&&(Args...)>>
    std::future<R> startAsyncTask(F&& callable, Args&&... args)
    {
      std::future<R> task = std::async(std::launch::async, callable, std::ref(args)...); 
      return task;
    } 

    // template<class FuncT>
    // std::packaged_task<FuncT> startAsyncTask(std::function<FuncT>&& callable)
    // {
    //   std::packaged_task<FuncT> task(callable);
    //   return task;
    // }

    // https://stackoverflow.com/questions/33135304/c-create-an-stdpackaged-task-of-a-generic-stdbind
    // template<class F, class...Args, typename R = std::result_of_t<std::decay_t<F>&&(Args...)>>
    // std::packaged_task<R(Args...)> startAsyncTask(F&& callable, Args&&...args)
    // {
    //   std::packaged_task<R(Args...)> task(
    //     [callable = std::forward<F>(callable)] (auto&&...args) {
    //       callable(args...);
    //   });
    //   return task;
    // }

    // We create and execute the task imidiatly, thus only returning a future
    // template<class F, class...Args, typename R = std::result_of_t<std::decay_t<F>&&(Args...)>>
    // std::future<R> startAsyncTaskThreaded(F&& callable, Args&&...args)
    // {
    //   std::packaged_task<R(Args...)> task(callable);
    //   std::thread task_td(std::move(task), args...);
    //   task_td.detach();
    //   return task.get_future();
    // }
  };  
}

#endif