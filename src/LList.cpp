/** @file LList.cpp
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
#include "LList.hpp"
#include "LListIterator.hpp"
#include "ListException.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/**
 * @brief Default constructor
 *
 * Construct an empty list.  The empty list will have no allocated memory
 * nor any values.
 */
template<class T>
LList<T>::LList()
{
  // Empty list has size 0 and both front and back are null
  this->size = 0;
  front = nullptr;
  back = nullptr;
}

/**
 * @brief Standard constructor
 *
 * Construct a list of integer values from a (statically) defined and
 * provided array of integers.  We need to dynamically construct
 * a node for each value in the array and create a linked list of these
 * nodes.
 *
 * @param size The size of the input values were are given as well as the
 *   size of the new list we are to construct.
 * @param values The (static) array of string values to use to construct
 *   this List values with.
 */
template<class T>
LList<T>::LList(int size, T values[])
{
  // Make sure list is empty before copying values from array.
  // Empty list has size 0 and both front and back are null
  this->size = 0;
  front = nullptr;
  back = nullptr;

  // iterate through the array reusing member functions to
  // simply insert new values one-by-one on the back
  for (int index = 0; index < size; index++)
  {
    // uncomment this after implementing insertBack() to enable its
    // reuse to correctly implement the array based constructor
    insertBack(values[index]);
  }
}

/**
 * @brief Copy constructor
 *
 * Provide a copy constructor for the List class.  A copy constructor
 * will be invoked whenver you assign one instance of a List to another.
 * For example
 *   List newList = existingList;
 * Where of course existingList was a previously created List.  This copy
 * constructor, as the name suggests, should make a copy of the values from
 * the given input list into a new List instance.
 *
 * @param list The other List type we are to make a copy of in this
 *   constructor.
 */
template<class T>
LList<T>::LList(const LList<T>& list)
{
  // Make sure list is empty before copying values from other list.
  // Empty list has size 0 and both front and back are null
  this->size = 0;
  front = nullptr;
  back = nullptr;

  // if the other list is not empty, then we need to iterate through
  // its values and insert them into the back of this list
  if (not list.isEmpty())
  {
    Node<T>* current = list.front;
    while (current != nullptr)
    {
      // uncomment this after implementing insertBack() to enable its
      // reuse to correctly implement the copy constructor
      insertBack(current->value);
      current = current->next;
    }
  }
}

/**
 * @brief Class destructor
 *
 * Destructor for the List class.  A concrete List implementation must
 * provide a clear() method to clear all items and safely deallocate any
 * memory that the concrete instance is using.  Invoke the clear
 * of the concrete subclass to perform the destruction.
 */
template<class T>
LList<T>::~LList()
{
  // call clear to do actual work to deallocate any allocation
  // before we destruct
  this->clear();
}

/**
 * @brief List to string
 *
 * Accessor method to construct and return a string representation
 * of the current values and status of this List instance.
 *
 * @returns string Returns the string constructed with the information
 *   about this List.
 */
template<class T>
string LList<T>::str() const
{
  ostringstream out;

  // stream list information into the output stream
  out << "<list> size: " << this->size << " [ ";

  // stream the current values of the list to the output stream
  Node<T>* current = front;
  while (current != nullptr)
  {
    // put value out to the stream
    out << current->value;

    // advance to the next value
    current = current->next;

    // separate for next value, or just space if no more values
    if (current == nullptr)
    {
      out << " ";
    }
    else
    {
      out << ", ";
    }
  }

  out << "]";

  // convert the string stream into a concrete string to return
  return out.str();
}

/**
 * @brief Boolean equals operator
 *
 * Check if this List is equal to the right hand side (rhs)
 * list.  The lists are equal if their sizes are equal, and if
 * all elements in both lists are equal.
 *
 * @param rhs The other list on the right hand side of the
 *   boolean comparison that we are comparing this List to.
 *
 * @returns bool true if the lists are equal, false if the are not.
 */
template<class T>
bool LList<T>::operator==(const List<T>& rhs) const
{
  // first the lists have to be of the same size, or else they
  // cannot be equal
  if (this->size != rhs.getSize())
  {
    return false;
  }

  // otherwise, lists are equal if all elements are equal.
  // compare each element, and if we find a pair that is not
  // equal then the answer is false
  for (int index = 0; index < this->size; index++)
  {
    if (this->operator[](index) != rhs[index])
    {
      return false;
    }
  }

  // if we get to this point, all values were the same in both
  // lists, so the answer is true, the lists are equal
  return true;
}

/**
 * @brief Indexing operator
 *
 * Provide a way to index individual values in our private
 * linked list of values.  This allows code to, for the
 * most part, treated an instance of our List as if it were
 * an array, though we also provide bounds checking to ensure
 * no illegal access beyond the list bounds is attempted.
 *
 * @param index The index of the value it is desired to access from
 *   this List.
 *
 * @returns int& Returns a reference to the requested List item at
 *   the requested index.
 *
 * @throws ListMemoryBoundsException if a request for an index beyond
 *   the end of the array (or less than 0) is made.
 */
template<class T>
T& LList<T>::operator[](int index) const
{
  // first check that the requsted index is legally
  // within the bounds of the current size of our list
  if ((index < 0) or (index >= this->size))
  {
    ostringstream out;
    out << "Error: <LList::operator[]> illegal bounds access, list size: " << this->size << " tried to access index address: " << index;

    throw ListMemoryBoundsException(out.str());
  }

  // otherwise it is safe to return the reference to the value, but
  // we have to do some work to find it first
  Node<T>* current = front;
  for (int currentIdx = 0; currentIdx < index; currentIdx++)
  {
    // advance to next node until we reach the index'th node of
    // this list
    current = current->next;
  }

  // return the reference to the value in the index'th node of the
  // list
  return current->value;
}

/**
 * @brief Clear out list
 *
 * Clear or empty out the list.  Return the list back to an empty
 * list.
 */
template<class T>
void LList<T>::clear()
{
  // if the list is not empty, we need to deallocate and return the nodes
  // back to the heap
  if (not this->isEmpty())
  {
    Node<T>* current = front;

    // iterate through the nodes of the list to delete them
    while (current != nullptr)
    {
      // remember this node to delete while advancing
      // to next node for next iteration
      Node<T>* nodeToDelete = current;
      current = current->next;

      // now safe to free up the memory of this node
      delete nodeToDelete;
    }
  }

  // make sure size is now 0 and front and back both point to null
  this->size = 0;
  front = nullptr;
  back = nullptr;
}

/**
 * @brief Delete back item
 *
 * Delete the item from the back of the list.  This is an expensive
 * O(n) operation for a singly linked list.
 */
template<class T>
void LList<T>::deleteBack()
{
  // make sure list is not empty before we try and access
  // the front item
  if (this->isEmpty())
  {
    ostringstream out;
    out << "Error: <Alist>::deleteBack() attempt to delete back item"
        << " from empty list, size:  " << this->size;

    throw ListEmptyException(out.str());
  }

  // if current list only has 1 item, then the list will now become
  // empty
  if (this->size == 1)
  {
    delete front;
    front = nullptr;
    back = nullptr;
    this->size = 0;
  }
  // otherwise there are at least 2 items in the list and we can
  // remove the current back item.  problem is, this is not a double
  // linked list, so we have to search till the item before the back
  else
  {
    // need to search through list and position prev to the node before
    // the back node
    Node<T>* prev = front;
    while (prev->next != back)
    {
      prev = prev->next;
    }

    // now remove the back node, and make prev the new back.
    delete back;
    prev->next = nullptr;
    back = prev;
    this->size -= 1;
  }
}

/**
 * @brief Delete front item
 *
 * Delete the item from the front of the list.  For a singly
 * linked list this operation is much cheaper than deleting
 * from the back, it is constant time O(1) to remove a front item.
 */
template<class T>
void LList<T>::deleteFront()
{
  // make sure list is not empty before we try and access
  // the front item
  if (this->isEmpty())
  {
    ostringstream out;
    out << "Error: <Alist>::deleteBack() attempt to delete back item"
        << " from empty list, size:  " << this->size;

    throw ListEmptyException(out.str());
  }

  // remember current front
  Node<T>* nodeToDelete = front;

  // move to new front
  front = front->next;

  // delete the node we removed
  delete nodeToDelete;

  // update list size since we just removed a node
  this->size -= 1;

  // list might now be empty, so make sure to repoint back as well
  // to nullptr if that is the case
  if (this->isEmpty())
  {
    back = nullptr;
  }
}

/**
 * @brief Begin iterator
 *
 * Create and return a ListIterator pointing to the beginning of
 * this list of items, ready to be iterated over.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that keeps track of iterating over the list items.
 */
template<class T>
ListIterator<T> LList<T>::begin()
{
  LListIterator<T> beginItr(front);
  return beginItr;
}

/**
 * @begin End iterator
 *
 * Return a ListIterator pointing to an index which is
 * at the end of this list, which is used to detect we are
 * at the end of the list when iteration.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that points to the end index indicator
 *   of the list.
 */
template<class T>
ListIterator<T> LList<T>::end()
{
  LListIterator<T> endItr(back);
  return endItr;
}

/**
 * @brief Constant begin iterator
 *
 * Create and return a ListIterator pointing to the beginning of
 * this list of items, ready to be iterated over.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that keeps track of iterating over the list items.
 */
template<class T>
ListIterator<T> LList<T>::cbegin() const
{
  LListIterator<T> beginItr(front);
  return beginItr;
}

/**
 * @brief Constant end iterator
 *
 * Return a ListIterator pointing to an index which is
 * at the end of this list, which is used to detect we are
 * at the end of the list when iteration.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that points to the end index indicator
 *   of the list.
 */
template<class T>
ListIterator<T> LList<T>::cend() const
{
  LListIterator<T> endItr(back);
  return endItr;
}

/**
 * @brief Back Insertion method
 * 
 * Method used to insert a value at the end of a 
 * given linked list
 * 
 * @param The new value to be added to the end of a linked list
 * 
 * @returns List<T>& returns a reference to the linked list
 * being operated on
 * 
 */
template<class T>
List<T>& LList<T>::insertBack(const T& newValue)
{
  Node<T> *node;
  node = new Node<T>;
  node->value = newValue;
  node->next = nullptr; 
  if (this->isEmpty())
  {
    front = node;
    back = node;
  }
  else
  {
    back->next = node;
    back = node; 
  }
  this->size++;
  return *this;
}

/**
 * @brief Back Insertion Operator 
 * 
 * Provide a way to directly add a value to the end of 
 * a given linked list. 
 * 
 * @param newValue
 * 
 * The new value to be added to the linked list
 * 
 * @returns List<T>& returns a reference to the linked list
 * being operated on
 * 
 */
template<class T>
List<T>& LList<T>::operator>>(const T& newValue)
{
  return insertBack(newValue);
}

/** @brief Access front of linked list
 *
 * Accessor method to get a copy of the item currently
 * at the front of this given linked list.
 *
 * @returns T Returns a copy of the front value of the
 *   linked list.
 *
 * @throws ListEmptyException If an attempt is made to
 *   access front value of an empty linked list, this exception
 *   is created and thrown instead.
 */
template<class T>
T LList<T>::getFront() const
{
  if (this->isEmpty())
  {
    throw ListEmptyException("Poop Fart");
  }

  return front->value;
}

/** @brief Access back of linked list
 *
 * Accessor method to get a copy of the value currently
 * at the back of this linked list.
 *
 * @returns T Returns a copy of the back item of the
 *   linked list.
 *
 * @throws ListEmptyException If an attempt is made to
 *   access back value of an empty linked list, this exception
 *   is created and thrown instead.
 */
template<class T>
T LList<T>::getBack() const
{
  if (this->isEmpty())
  {
    //back = nullptr;
    ostringstream out;

    throw ListEmptyException("Poop Fart");
  }

  return back->value;
}

/** @brief Insert value on front
 *
 * Prepend the indicated value to the beginning of this Linked List
 * of values.  This method will grow the linked list allocation if
 * needed to accomodate prepending the new value.  This method
 * returns a reference to this instance, so that the result can
 * be used in chained expressions of Linked List types.
 *
 * @param value The value to prepend to the beginning of the current list.
 *
 * @returns List<T>& Returns a reference to this Linked List instance, so that
 *   the result can be used in further Linekd List operator expressions.
 */
template<class T>
List<T>& LList<T>::insertFront(const T& newValue)
{
  Node<T> *node;
  node = new Node<T>;
  node->value = newValue;
  node->next = nullptr; 
  if (this -> isEmpty())
  {
    front = node;
    back = node;
  }
  else
  {
    node->next = front;
    front = node; 
  }
  this -> size++;
  return *this;
}

/** @brief Overload operator<< to prepend
 *
 * Overload the operator<< to perform prepend operation.  Implementation
 * is actually done by the insertFront() member function.
 *
 * @param value The value to prepend to the beginning of the current linked list.
 *
 * @returns List<T>& Returns a reference to this Linked List instance, so that
 *   the result can be used in further Linked List operator expressions.
 */
template<class T>
List<T>& LList<T>::operator<<(const T& newValue)
{
  return insertFront(newValue);
}

/** @brief Delete value at index
 *
 * Delete the value from the indicated index in this linked
 * list.
 *
 * @param index The index of the value in the linked list to be removed.
 *
 * @throws ListMemoryBoundsException If an index is given below the
 *   beginning of the array or past the end we will throw a bounds
 *   exception for the illegal memory access attempt.
 */
template<class T>
void LList<T>::deleteIndex(int position)
{
  if (position < 0 || position >= this->size)
  {
    ostringstream out;
    out << "Error: <LList::operator[]> illegal bounds access, list size: " << this->size << " tried to access index address: " << position;

    throw ListMemoryBoundsException(out.str());
  }
  if (position == 0)
  {
    deleteFront();
  }
  else if (position == this -> getSize() - 1)
  {
    deleteBack();
  }
  else
  {
    Node<T> *temp = front;
    for (int index = 0; temp != NULL && index < position - 1; index++)
    {
      temp = temp->next; 
    }
    if (temp == NULL || temp->next == NULL)
    {
      return;
    }
    Node<T> *newAddress = temp->next->next;
    Node<T> *deleteTemp = temp->next;
    temp->next = newAddress;
    delete(deleteTemp);
    this->size--;
  }
}

/** @brief Delete value(s)
 *
 * Delete the value from the linked list.  This method will delete all
 * instances of the value from this linked list that it finds.  If the linked list
 * does not conatin the value, then an exception is thrown.
 *
 * @param value The value to deleted from this linked list.
 *
 * @throws ListValueNotFoundException If we are asked to delete a value
 *   that does not exist, we thrown an exception instead of completely
 *   ignoring this condition.
 */
template<class T>
void LList<T>::deleteValue(const T& value)
{
  if (this -> isEmpty())
  {
    throw ListValueNotFoundException("Error: requested value not found within linked list");
  }
  bool noValue = true;
  if (front -> value == value)
  {
    noValue = false;
    deleteFront();
  }
  if (back -> value == value)
  {
    noValue = false;
    deleteBack();
  }
  if (this->size >= 3)
  {
    Node<T> *temp = front;
    while (temp->next != back)
    {
      if (temp->next->value == value)
      {
        Node<T> *newAddress = temp->next->next;
        Node<T> *deleteTemp = temp->next;
        temp->next = newAddress;
        delete(deleteTemp);
        noValue = false;
        this->size--;
      }
      else
      {
        temp = temp->next;
      }
    }
  }
  if (noValue)
  {
    throw ListValueNotFoundException("Error: requested value not found within linked list");
  }
  
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
template class LList<int>;
template class LList<string>;
