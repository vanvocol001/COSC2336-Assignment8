/** @file ListIterator.hpp
 * @brief Abstract class for defining C++ iterators over List<T> objects.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Definition of ListIterator<T> abstraction.  A common use case
 * of linked lists is to simply iterate over the items of the list.
 * We want to conform to C++ standard abstractions and provide
 * iterator objects for iterating lists.
 */
#ifndef _LIST_ITERATOR_HPP_
#define _LIST_ITERATOR_HPP_
#include <iostream>
using namespace std;

/** @class ListIterator
 * @brief The ListIterator interface
 *
 * The defined ADT interface for a ListIterator objects.
 * These allow us to iterate over List<T> objects in the
 * standard and expected way for C++ template classes.
 */
template<class T>
class ListIterator
{
public:
  // constructors and descturcotr
  ListIterator();

  // overloaded operators
  virtual T operator*();
  virtual ListIterator<T>& operator++();
  virtual bool operator==(const ListIterator<T>& rhs) const;
  virtual bool operator!=(const ListIterator<T>& rhs) const;
};

#endif // define _LIST_ITERATOR_HPP_
