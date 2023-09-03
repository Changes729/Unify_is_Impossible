/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MANAGER_INTERFACE_H
#define MANAGER_INTERFACE_H
#pragma once
/* Public include ------------------------------------------------------------*/
#include <vector>
#include <algorithm>
#include <assert.h>

/* Public namespace ----------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public typedef ------------------------------------------------------------*/
/* Public template -----------------------------------------------------------*/
/* Public function prototypes ------------------------------------------------*/
/* Public class --------------------------------------------------------------*/
template<typename Child>
class IManager: public std::vector<Child>
{
public:
  virtual bool is_child_valid(const Child child_, size_t* index = nullptr)
  {
    auto begin_itr = std::vector<Child>::begin();
    auto end_itr   = std::vector<Child>::end();
    auto itr       = std::find(begin_itr, end_itr, child_);
    bool is_valid  = (itr != std::vector<Child>::end());

    if(is_valid && nullptr != index) {
      *index = std::distance(std::vector<Child>::begin(), itr);
    }

    return is_valid;
  }

  virtual void register_child(Child child_)
  {
    assert(!is_child_valid(child_));
    std::vector<Child>::push_back(child_);
  }

  virtual void unregister_child(Child child_)
  {
    size_t index = 0;
    if(is_child_valid(child_, &index)) {
      std::vector<Child>::erase(std::vector<Child>::begin() + index);
    }
  }
};

#endif /* MANAGER_INTERFACE_H */
