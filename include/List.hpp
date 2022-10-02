/** @file List.hpp
 * @brief Abstract base class definition of List abstract data type.
 *   This header defines the abstraction/interface for concrete
 *   List implementations.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Defination of List abstraction.  Concrete implementations of
 * this List interface must inherit from this abstract base class
 * and implement all defined virtual functions.
 */
#ifndef _LIST_HPP_
#define _LIST_HPP_
#include "ListIterator.hpp"
#include <iostream>
using namespace std;

/** @class List
 * @brief The List data type abstraction
 *
 * The defined ADT interface for a List data type.  This abstraction
 * provides the ability to perform the most common tasks we want to
 * perform with lists, such as add items on the beginning or end,
 * search the list, iterate over the items of the list, etc.
 */
template<class T>
class List
{
public:
  // accessor and information methods
  int getSize() const;
  bool isEmpty() const;
  virtual T getFront() const = 0;
  virtual T getBack() const = 0;
  virtual string str() const = 0;
  virtual bool operator==(const List<T>& rhs) const = 0;
  virtual T& operator[](int index) const = 0;

  // adding, accessing and removing values from the list
  virtual void clear() = 0;
  virtual List<T>& insertBack(const T& value) = 0;
  virtual List<T>& operator>>(const T& value) = 0;
  virtual void deleteBack() = 0;
  virtual List<T>& insertFront(const T& value) = 0;
  virtual List<T>& operator<<(const T& value) = 0;
  virtual void deleteFront() = 0;
  virtual void deleteValue(const T& value) = 0;
  virtual void deleteIndex(int index) = 0;

  // iterating over list the C++ way, using iterator objects
  virtual ListIterator<T> begin() = 0;
  virtual ListIterator<T> end() = 0;
  virtual ListIterator<T> cbegin() const = 0;
  virtual ListIterator<T> cend() const = 0;

  // friend functions and friend operators
  template<typename U>
  friend ostream& operator<<(ostream& out, const List<U>& rhs);

protected: // private to the class hierarchy, only child classes can access
  /// @brief the current size of the list of integer values, this is
  ///   protected so derived classes can access it
  int size;
};

#endif // define _LIST_HPP_
