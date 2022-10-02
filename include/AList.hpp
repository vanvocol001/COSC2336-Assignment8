/** @file AList.hpp
 * @brief Concrete array based implementation of List ADT.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implement the List abstraction using a fixed sized array.
 * This array based implementation will dynamically allocate
 * a new block of memory once the current allocation becomes
 * full.  The new block is double in size of the old.  Thus
 * insertion at the end of the list can be O(1) in most cases,
 * but will take O(n) copies as well as a memory allocation
 * if it needs to grow.  Insertion in the middle or front
 * still requires shifting of items, so it is O(n).
 */
#ifndef _ALIST_HPP_
#define _ALIST_HPP_
#include "AListIterator.hpp"
#include "List.hpp"
#include <string>
using namespace std;

/** @class AList
 * @brief The AList concrete array based implemention of the
 *   List interface.
 *
 * Concrete implementation of List abstraction using an
 * array based implementation.
 */
template<class T>
class AList : public List<T>
{
public:
  // constructors and destructors
  AList();                          // default constructor
  AList(int size, T values[]);      // array based constructor
  AList(const AList<T>& otherList); // copy constructor
  ~AList();                         // destructor

  // accessor and information methods
  int getAllocationSize() const;
  T getFront() const;
  T getBack() const;
  string str() const;
  bool operator==(const List<T>& rhs) const;
  T& operator[](int index) const;

  // adding, accessing and removing values from the list
  void clear();
  List<T>& insertBack(const T& value);
  List<T>& operator>>(const T& value);
  void deleteBack();
  List<T>& insertFront(const T& value);
  List<T>& operator<<(const T& value);
  void deleteFront();
  void deleteValue(const T& value);
  void deleteIndex(int index);

  // iterating over list the C++ way, using iterator objects
  // and supporting range based iteration
  ListIterator<T> begin();
  ListIterator<T> end();
  ListIterator<T> cbegin() const;
  ListIterator<T> cend() const;

private:
  /// @brief private constant, initial allocation size for empty lists
  ///   to grow to
  const int INITIAL_ALLOCATION_SIZE = 10;

  /// @brief the current amount of allocated memory being
  ///   managed by/for this list of values
  int allocationSize;

  /// @brief For the array based implementation, the values is a fixed
  ///   array of type T values.  The values contained in the list
  ///   will be manged from the array, and a new array allocated and
  ///   values copied if we fill up the current allocation.
  T* values;

  // private member methods for managing the List internally
  void growListIfNeeded();
};

#endif // define _ALIST_HPP_
