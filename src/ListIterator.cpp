/** @file ListIterator.cpp
 * @brief Iterator for List<T> list types.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implement the ListIterator abstraction to provide for
 * standard iteration over concrete AList<T> instances.
 */
#include "ListIterator.hpp"
using namespace std;

/**
 * @brief Default constructor
 *
 * Default constructor, iterator will not be iterating over
 * anything if constructed using the default constructor.
 */
template<class T>
ListIterator<T>::ListIterator()
{
}

/**
 * @brief Overload dereference operator
 *
 * Overload the dereference operator* for the ListIterator.
 * This method makes it easy/convenient to access the info
 * that the iterator is currently pointing two.  This is the
 * standard way that C++ accesses values during iteration of
 * the container.
 *
 * @returns T Returns the value currently being pointed to by
 *   this iterator.
 */
template<class T>
T ListIterator<T>::operator*()
{
  return T();
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
ListIterator<T>& ListIterator<T>::operator++()
{
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
bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const
{
  return false;
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
bool ListIterator<T>::operator!=(const ListIterator<T>& rhs) const
{
  return false;
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
template class ListIterator<int>;
template class ListIterator<string>;
