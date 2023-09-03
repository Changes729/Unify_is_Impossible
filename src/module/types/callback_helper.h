/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CALLBACK_HELPER_H
#define CALLBACK_HELPER_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

/* Public namespace ----------------------------------------------------------*/
using std::index_sequence;

/* Public define -------------------------------------------------------------*/
#define CALLBACK_MAKE(type, func)                                              \
  __make_callback<type>::__match<decltype(func)>::cb<func>
#define CALLBACK_REVERSE_MAKE(type, func)                                      \
  __make_callback<type>::__reverse_match<decltype(func)>::cb<func>

/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/

// Declare primary template for index range builder
template<std::size_t MIN, std::size_t N, std::size_t... Is>
struct range_builder;

// Base step
template<std::size_t MIN, std::size_t... Is>
struct range_builder<MIN, MIN, Is...>
{
  typedef std::index_sequence<Is...> type;
};

template<std::size_t MIN, std::size_t MAX>
using index_range = typename range_builder<MIN, MAX>::type;

// Induction step
template<std::size_t MIN, std::size_t N, std::size_t... Is>
struct range_builder: public range_builder<MIN, N - 1, N - 1, Is...>
{};

template<typename __source_class__, typename _Callable, typename _Tuple, std::size_t... _Is>
__attribute__((always_inline)) inline auto invoke_reverse_args(
    _Callable&& f, _Tuple&& t, std::index_sequence<_Is...>)
{
  return std::invoke(f,
                     (__source_class__*)
                         std::get<std::tuple_size<_Tuple>::value - 1>(t),
                     std::get<_Is>(t)...);
}

template<typename __source_class__, typename _Callable, typename _Tuple, std::size_t... _Is>
__attribute__((always_inline)) inline auto invoke_args(
    _Callable&& f, _Tuple&& t, std::index_sequence<_Is...>)
{
  return std::invoke(f, (__source_class__*)std::get<0>(t), std::get<_Is>(t)...);
}

/* Public class --------------------------------------------------------------*/
template<typename __destiny_func_t>
struct __make_callback;

template<typename __ret_type, typename... __d_args_pkg>
struct __make_callback<__ret_type (*)(__d_args_pkg...)>
    : public __make_callback<__ret_type(__d_args_pkg...)>
{};

template<typename __ret_type, typename... __d_args_pkg>
struct __make_callback<__ret_type(__d_args_pkg...)>
{
  template<typename __source_func_t>
  struct __match;

  template<typename __source_class__, typename... __s_args_pkg>
  struct __match<__ret_type (__source_class__::*)(__s_args_pkg...)>
  {
    template<__ret_type (__source_class__::*_prt)(__s_args_pkg...)>
    static __ret_type cb(__d_args_pkg... args)
    {
      return invoke_args<
          __source_class__>(_prt,
                            std::forward_as_tuple(args...),
                            index_range<1, sizeof...(__s_args_pkg) + 1>{});
    };
  };

  template<typename __source_func_t>
  struct __reverse_match;

  template<typename __source_class__, typename... __s_args_pkg>
  struct __reverse_match<__ret_type (__source_class__::*)(__s_args_pkg...)>
  {
    template<__ret_type (__source_class__::*_prt)(__s_args_pkg...)>
    static __ret_type cb(__d_args_pkg... args)
    {
      return invoke_reverse_args<
          __source_class__>(_prt,
                            std::forward_as_tuple(args...),
                            std::make_index_sequence<sizeof...(__s_args_pkg)>{});
    };
  };
};

template<typename... __d_args_pkg>
struct __make_callback<void (*)(__d_args_pkg...)>
    : public __make_callback<void(__d_args_pkg...)>
{};

template<typename... __d_args_pkg>
struct __make_callback<void(__d_args_pkg...)>
{
  template<typename __source_func_t>
  struct __match;

  template<typename __source_class__, typename... __s_args_pkg>
  struct __match<void (__source_class__::*)(__s_args_pkg...)>
  {
    template<void (__source_class__::*_prt)(__s_args_pkg...)>
    static void cb(__d_args_pkg... args)
    {
      invoke_args<__source_class__>(_prt,
                                    std::forward_as_tuple(args...),
                                    index_range<1, sizeof...(__s_args_pkg) + 1>{});
    };
  };

  template<typename __source_func_t>
  struct __reverse_match;

  template<typename __source_class__, typename... __s_args_pkg>
  struct __reverse_match<void (__source_class__::*)(__s_args_pkg...)>
  {
    template<void (__source_class__::*_prt)(__s_args_pkg...)>
    static void cb(__d_args_pkg... args)
    {
      invoke_reverse_args<__source_class__>(_prt,
                                            std::forward_as_tuple(args...),
                                            std::make_index_sequence<sizeof...(
                                                __s_args_pkg)>{});
    };
  };
};

#endif /* CALLBACK_HELPER_H */
