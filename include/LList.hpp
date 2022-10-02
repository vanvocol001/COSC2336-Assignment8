/** @file LList.hpp
 * @brief Concrete linked list based implementation of List ADT.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implement the List abstraction using a linked list of dynamically
 * allocated node items.  The linked list based implementation
 * createns new nodes dynamicall when items are inserted into the
 * list, and deletes these nodes when they are removed from the list.
 * The Node structure defined in this header is private to the LLink
 * class.
 */
#ifndef _LLIST_HPP_
#define _LLIST_HPP_
#include "LListIterator.hpp"
#include "List.hpp"
#include "Node.hpp"
#include <string>
using namespace std;

/** @class LList
 * @brief The LList concrete array based implemention of the
 *   List interface.
 *
 * Concrete implementation of List abstraction using an
 * array based implementation.
 */
template<class T>
class LList : public List<T>
{
public:
  // constructors and destructors
  LList();                          // default constructor
  LList(int size, T values[]);      // array based constructor
  LList(const LList<T>& otherList); // copy constructor
  ~LList();                         // destructor

  // accessor and information methods
  string str() const;
  bool operator==(const List<T>& rhs) const;
  T& operator[](int index) const;
  List<T>& operator>>(const T& value);
  List<T>& operator<<(const T& value);

  // adding, accessing and removing values from the list
  void clear();
  void deleteBack();
  void deleteFront();
  List<T>& insertBack(const T& value);
  T getFront() const;
  T getBack() const;
  List<T>& insertFront(const T& value);
  void deleteIndex(int index);
  void deleteValue(const T& value);

  // iterating over list the C++ way, using iterator objects
  // and supporting range based iteration
  ListIterator<T> begin();
  ListIterator<T> end();
  ListIterator<T> cbegin() const;
  ListIterator<T> cend() const;

private:
  /// @brief pointer to the front or first node of the linked list.
  Node<T>* front;

  /// @brief pointer to the back or last node of the linked list.
  Node<T>* back;
};

#endif // define _LLIST_HPP_
