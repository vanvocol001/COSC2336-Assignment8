/** @file AListIterator.hpp
 * @brief Concrete Iterator for AList<T> list types.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Definition of concrete AListIterator to iterate over
 * AList<T> instances.
 */
#ifndef _ALIST_ITERATOR_HPP_
#define _ALIST_ITERATOR_HPP_
#include "ListIterator.hpp"
using namespace std;

/** @class AListIterator
 * @brief The ListIterator interface
 *
 * The defined ADT interface for a ListIterator objects.
 * These allow us to iterate over List<T> objects in the
 * standard and expected way for C++ template classes.
 */
template<class T>
class AListIterator : public ListIterator<T>
{
public:
  // constructors
  AListIterator();
  AListIterator(int index, T* values);

  // overloaded operators
  T operator*();
  ListIterator<T>& operator++();
  bool operator==(const AListIterator<T>& rhs) const;
  bool operator!=(const AListIterator<T>& rhs) const;

private:
  /// The AList<T> class copies the current pointer
  ///   to the list values when this iterator is
  ///   created
  T* values;
  /// Current index to the point we currently are at
  ///   in iterating through this AList
  int current;
};

#endif // define _ALIST_ITERATOR_HPP_
