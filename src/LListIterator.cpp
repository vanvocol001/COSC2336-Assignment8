/** @file LListIterator.cpp
 * @brief Concrete Iterator for LList<T> list types.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implement the ListIterator abstraction to provide for
 * standard iteration over concrete LList<T> instances.
 */
#include "LListIterator.hpp"
#include "LList.hpp"
using namespace std;

/**
 * @brief Default constructor
 *
 * Default constructor, iterator will not be iterating over
 * anything if constructed using the default constructor.
 */
template<class T>
LListIterator<T>::LListIterator()
{
  current = nullptr;
}

/**
 * @brief Standard constructor
 *
 * Standard constructor, we are given a pointer to the node
 * we are to begin iteration with.
 *
 * @param ptr A pointer to the Node<T> item at start of
 *   this iteration of the linked list LList<T> instance.
 */
template<class T>
LListIterator<T>::LListIterator(Node<T>* ptr)
{
  this->current = ptr;
}

/**
 * @brief Overload dereference operator
 *
 * Overload the dereference operator* for the LListIterator.
 * This method makes it easy/convenient to access the info
 * that the iterator is currently pointing two.  This is the
 * standard way that C++ accesses values during iteration of
 * the container.
 *
 * @returns T Returns the value currently being pointed to by
 *   this iterator.
 */
template<class T>
T LListIterator<T>::operator*()
{
  // TODO: should we be checking case where current is not a valid
  // index
  // TODO: should we be checking for empty list cases
  return current->value;
}

/**
 * @brief Overload increment operator
 *
 * Overload the post increment operator++.  This is defined to cause the
 * iterator to move to the next item in the list we are iterating over.
 *
 * @returns ListIterator<T> We need to return ourself after incrementing
 *   the iterator to the next value of the list we are iterating over.
 *
 */
template<class T>
ListIterator<T>& LListIterator<T>::operator++()
{
  current = current->next;

  return *this;
}

/**
 * @brief Overload boolean equality operator
 *
 * Overload the boolean operator== to check for equivalence.  This is
 * needed to create loops and test if we are done yet or not iterating
 * over the list by testing if the iterator is == the end() iterator item.
 *
 * @param rhs The other ListIterator we are comparing ourself against.
 *
 * @returns bool True if the iterators are both pointing to the same
 *   value of the iteration, false otherwise.
 */
template<class T>
bool LListIterator<T>::operator==(const LListIterator<T>& rhs) const
{
  return current == rhs.current;
}

/**
 * @brief Overload boolean not equal operator
 *
 * Overload the boolean operator!= to check for nonequivalance.  This is
 * needed to create loops and test if we are done yet or not iterating
 * over the list by testing if the iterator is != the end() iterator item.
 *
 * @param rhs The other ListIterator we are comparing ourself against.
 *
 * @returns bool True if the iterators are not pointing to the same
 *   value of the iteration, false otherwise.
 */
template<class T>
bool LListIterator<T>::operator!=(const LListIterator<T>& rhs) const
{
  return current == rhs.current;
}

/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class List<needed_type>
 * here of any types we are going to be instantianting with the
 * template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template class LListIterator<int>;
template class LListIterator<string>;
