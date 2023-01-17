#include "frontier_queue.hpp"


template <typename T>
State<T> frontier_queue<T>::pop() 
{  

  //remove first node
  //list is empty
    if(queue.empty())
    {
        throw std::logic_error("can't remove from empty heap");
    }
    //one node
    if(queue.size() == 1)
    {
      State <T> temp = queue[0];
      queue.pop_back();
      return temp;
    }
    //only one child
    if(queue.size() == 2)
    {
      State <T> temp = queue[0];
      queue[0] = queue[queue.size()-1];
      queue.pop_back();
      return temp;
    }
    //two children
    State<T> temp = queue[0];
    queue[0] = queue[queue.size()-1];
    queue.pop_back();
    size_t pos = 0;

    
    bool good = false;
    
    //replace 
    while(((pos*2+2) < queue.size()) && !(good))
    {
        good = false;
        if(queue[pos*2+1].getFCost() < queue[pos*2+2].getFCost())
        {
            if(queue[pos*2+1].getFCost() < queue[pos].getFCost())
            {
              State<T> temp2 = queue[pos];
              queue[pos] = queue[pos*2+1];
              queue[pos*2+1]  = temp2;
              pos = pos*2+1;
            }
            else
            {
              good = true;
            }
            
        }
        else
        {
            if(queue[pos*2+2].getFCost() < queue[pos].getFCost())
            {
              State<T> temp2 = queue[pos];
              queue[pos] = queue[pos*2+2];
              queue[pos*2+2] = temp2;
              pos = pos*2+2;
            }
            else
            {
              good = true;
            }
            
        }
    }
    //if one child left
    if(pos*2+1 < queue.size())
    {
        if(queue[pos*2+1].getFCost() < queue[pos].getFCost())
        {
            State<T> temp2 = queue[pos];
            queue[pos] = queue[pos*2+1];
            queue[pos*2+1] = temp2;
        }  
    }

 return temp;

}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) 
{
  State<T> item(p, cost, heur);
  //implement this the same way we implemented push in the heap lecture.
    if(queue.empty())
    {
      queue.push_back(item);
      return;
    }
    else
    {
      queue.push_back(item);

      size_t pos = queue.size()-1;
      while(pos != 0 && (queue[pos].getFCost() < queue[(pos-1)/2].getFCost()))
      {
        queue[pos] = queue[(pos-1)/2];
        queue[(pos-1)/2] = item;
        pos = (pos-1)/2;
      }

    }

}

template <typename T>
bool frontier_queue<T>::empty() 
{

  if(queue.empty())
  {
    return true;
  }
  return false;

}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) 
{
  for(int i = 0; i < queue.size(); i++)
  {
    if(queue[i].getValue() == p)
    {
      return true;
    }
  }
  return false;
}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost)
{
  int pos = -1;
  for(int i = 0; i < queue.size(); i++)
  {
    if(queue[i].getValue() == p)
    {
      if(queue[i].getPathCost() > cost)
      {
        queue[i].updatePathCost(cost);
        pos = i;
        break;
      }
    }
  }
  if(pos != -1)
  {
    while(pos != 0)
    {
      if(queue[pos].getFCost() < queue[(pos-1)/2].getFCost())
      {
        State<T> temp = queue[pos];
        queue[pos] = queue[(pos-1)/2];
        queue[(pos-1)/2] = temp;
        pos = (pos-1)/2;
      }
    }
  }
}


