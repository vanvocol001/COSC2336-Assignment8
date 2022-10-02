/** @file LListIterator.hpp
 * @brief Concrete Iterator for AList<T> list types.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Definition of concrete LListIterator to iterate over
 * AList<T> instances.
 */
#ifndef _LLIST_ITERATOR_HPP_
#define _LLIST_ITERATOR_HPP_
#include "LList.hpp"
#include "ListIterator.hpp"
#include "Node.hpp"
using namespace std;

/** @class LListIterator
 * @brief The ListIterator interface
 *
 * The defined ADT interface for a ListIterator objects.
 * These allow us to iterate over List<T> objects in the
 * standard and expected way for C++ template classes.
 */
template<class T>
class LListIterator : public ListIterator<T>
{
public:
  // constructors
  LListIterator();
  LListIterator(Node<T>* ptr);

  // overloaded operators
  T operator*();
  ListIterator<T>& operator++();
  bool operator==(const LListIterator<T>& rhs) const;
  bool operator!=(const LListIterator<T>& rhs) const;

private:
  /// @brief pointer to the current node of the current
  ///   iteration of the list
  Node<T>* current;
};

#endif // define _LLIST_ITERATOR_HPP_
