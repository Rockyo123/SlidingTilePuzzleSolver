#ifndef FRONTIER_QUEUE_HPP
#define FRONTIER_QUEUE_HPP

#include "state.hpp"
#include <vector>

template <typename T>
class frontier_queue {
public:

  bool empty();

  void push(const T &p, std::size_t cost, std::size_t heur);

  State<T> pop();

  bool contains(const T &p);

  void replaceif(const T &p, std::size_t cost);

private:

  std::vector<State<T>> queue;
  
};

#include "frontier_queue.tpp"

#endif
