/** @file AList.cpp
 * @brief Concrete array based implementation of List ADT.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implement the List abstraction using a fixed sized array.  This
 * array based implementation will dynamically allocate a new block of
 * memory once the current allocation becomes full.  The new block is
 * double in size of the old.  Thus insertion at the end of the list
 * can be O(1) in most cases, but will take O(n) copies as well as a
 * memory allocation if it needs to grow.  Insertion in the middle or
 * front still requires shifting of items, so it is O(n).
 */
#include "AList.hpp"
#include "AListIterator.hpp"
#include "ListException.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/** @brief Default constructor
 *
 * Construct an empty list.  The empty list will have no allocated memory
 * nor any values.
 */
template<class T>
AList<T>::AList()
{
  // Empty list has no values nor any allocated memory
  // associated with it
  this->size = 0;
  this->allocationSize = 0;
  values = nullptr;
}

/** @brief Standard constructor
 *
 * Construct a list of integer values from a (statically) defined and
 * provided array of values.  We simply allocate a block of memory
 * dynamically large enough to hold the values, then copy the values
 * from the input parameter into our own private array of values.
 *
 * @param size The size of the input values were are given as well as the
 *   size of the new list we are to construct.
 * @param values The (static) array of string values to use to construct
 *   this List values with.
 */
template<class T>
AList<T>::AList(int size, T values[])
{
  // dynamically allocate a block of memory on the heap large enough to copy
  // the given input values into
  this->size = size;
  this->allocationSize = size;
  this->values = new T[allocationSize];

  // copy the values from the input paramter into our new shiny block of memory
  for (int index = 0; index < size; index++)
  {
    this->values[index] = values[index];
  }
}

/** @brief Copy constructor
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
AList<T>::AList(const AList<T>& list)
{
  // copy the size of the existing list and allocate memory to hold
  // values we will copy
  this->size = list.getSize();
  allocationSize = 2 * this->size;
  values = new T[allocationSize];

  // copy the values from the input List into this list
  for (int index = 0; index < this->size; index++)
  {
    // relies on overloaded index operator[] for List types
    values[index] = list[index];
  }
}

/** @brief Class destructor
 *
 * Destructor for the List class.  A concrete List implementation must
 * provide a clear() method to clear all items and safely deallocate any
 * memory that the concrete instance is using.  Invoke the clear
 * of the concrete subclass to perform the destruction.
 */
template<class T>
AList<T>::~AList()
{
  // call clear to do actual work to deallocate any allocation
  // before we destruct
  this->clear();
}

/** @brief Allocation size accessor
 *
 * Accessor method to get the current amount of memory allocated
 * by and being managed by this list.
 *
 * @returns int Returns the current allocation size of the
 *   list of integers.
 */
template<class T>
int AList<T>::getAllocationSize() const
{
  return allocationSize;
}

/** @brief Access front of list
 *
 * Accessor method to get a copy of the item currently
 * at the front of this list.
 *
 * @returns T Returns a copy of the front item of the
 *   list.
 *
 * @throws ListEmptyException If an attempt is made to
 *   access front item of an empty list, this exception
 *   is generated and thrown instead.
 */
template<class T>
T AList<T>::getFront() const
{
  // make sure list is not empty before we try and access
  // the front item
  if (this->isEmpty())
  {
    ostringstream out;
    out << "Error: <Alist>::getFront() attempt to get item"
        << " from empty list, size:  " << this->size;

    throw ListEmptyException(out.str());
  }

  // otherwise safe to return the front item
  return values[0];
}

/** @brief Access back of list
 *
 * Accessor method to get a copy of the item currently
 * at the back of this list.
 *
 * @returns T Returns a copy of the back item of the
 *   list.
 *
 * @throws ListEmptyException If an attempt is made to
 *   access back item of an empty list, this exception
 *   is generated and thrown instead.
 */
template<class T>
T AList<T>::getBack() const
{
  // make sure list is not empty before we try and access
  // the back item
  if (this->isEmpty())
  {
    ostringstream out;
    out << "Error: <Alist>::getBack() attempt to get item"
        << " from empty list, size:  " << this->size;

    throw ListEmptyException(out.str());
  }

  // otherwise safe to return the back item
  return values[this->size - 1];
}

/** @brief List to string
 *
 * Accessor method to construct and return a string representation
 * of the current values and status of this List instance.
 *
 * @returns string Returns the string constructed with the information
 *   about this List.
 */
template<class T>
string AList<T>::str() const
{
  ostringstream out;

  // stream list information into the output stream
  out << "<list> size: " << this->size << " [ ";

  // stream the current value sof the list to the output stream
  for (int index = 0; index < this->size; index++)
  {
    out << values[index];

    // separate the values of the list, last one does not need , separator
    if (index == this->size - 1)
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

/** @brief Boolean equals operator
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
bool AList<T>::operator==(const List<T>& rhs) const
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
    if (values[index] != rhs[index])
    {
      return false;
    }
  }

  // if we get to this point, all values were the same in both
  // lists, so the answer is true, the lists are equal
  return true;
}

/** @brief Indexing operator
 *
 * Provide a way to index individual values in our private
 * internal array of integers.  This allows code to, for the
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
T& AList<T>::operator[](int index) const
{
  // first check that the requsted index is legally
  // within the bounds of the current size of our list
  if ((index < 0) or (index >= this->size))
  {
    ostringstream out;
    out << "Error: <AList::operator[]> illegal bounds access, list size: " << this->size << " tried to access index address: " << index;

    throw ListMemoryBoundsException(out.str());
  }

  // otherwise it is safe to return the reference to this value
  return values[index];
}

/** @brief Clear out list
 *
 * Clear or empty out the list.  Return the list back
 * to an empty list.
 */
template<class T>
void AList<T>::clear()
{
  // if values is not null, it points to a dynamic block of memory, so
  // delete that block.
  if (values != nullptr)
  {
    delete[] values;
    values = nullptr;
  }

  // make sure size and allocation are both reading as 0 now
  this->size = 0;
  allocationSize = 0;
}

/** @brief Insert value on back
 *
 * Append the indicated value to the end of this List
 * of values.  This method will grow the list allocation if
 * needed to accomodate appending the new value.  This method
 * returns a reference to this instance, so that the result can
 * be used in chained expressions of List types.
 *
 * @param value The value to append to the end of the current list.
 *
 * @returns List& Returns a reference to this List instance, so that
 *   the result can be used in further List operator expressions.
 */
template<class T>
List<T>& AList<T>::insertBack(const T& value)
{
  // first check and grow the memory allocation if needed
  growListIfNeeded();

  // list allocation is guaranteed to have some room now, so
  // simply append the value to the end of the current values
  values[this->size] = value;
  this->size++;

  // return a reference to this instance so that append operation
  // can be used in chained expressions of List objects
  return *this;
}

/** @brief Overload operator>> to append
 *
 * Overload the operator>> to perform append operation.  Implementation
 * is actually done by the insertBack() member function.
 *
 * @param value The value to append to the end of the current list.
 *
 * @returns List& Returns a reference to this List instance, so that
 *   the result can be used in further List operator expressions.
 */
template<class T>
List<T>& AList<T>::operator>>(const T& value)
{
  return insertBack(value);
}

/** @brief Delete back item
 *
 * Delete the item from the back of the list.  This is a
 * trivial O(1) operation for an array based implementation.
 */
template<class T>
void AList<T>::deleteBack()
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

  // removing back item of an array means simply reducing size by 1
  this->size -= 1;
}

/** @brief Insert value on front
 *
 * Prepend the indicated value to the beginning of this List
 * of values.  This method will grow the list allocation if
 * needed to accomodate prepending the new value.  This method
 * returns a reference to this instance, so that the result can
 * be used in chained expressions of List types.
 *
 * @param value The value to prepend to the beginning of the current list.
 *
 * @returns List& Returns a reference to this List instance, so that
 *   the result can be used in further List operator expressions.
 */
template<class T>
List<T>& AList<T>::insertFront(const T& value)
{
  // first check and grow the memory allocation if needed
  growListIfNeeded();

  // list allocation is guaranteed to have some room now,
  // but before we can prepend we have to shift all items up
  // by 1 index to make room at index 0
  for (int index = this->size; index >= 1; index--)
  {
    // shift value up 1 location
    values[index] = values[index - 1];
  }

  // now simply preppend the value to the beginning of the current values
  values[0] = value;
  this->size++;

  // return a reference to this instance so that append operation
  // can be used in chained expressions of List objects
  return *this;
}

/** @brief Overload operator<< to prepend
 *
 * Overload the operator<< to perform prepend operation.  Implementation
 * is actually done by the insertFront() member function.
 *
 * @param value The value to prepend to the beginning of the current list.
 *
 * @returns List& Returns a reference to this List instance, so that
 *   the result can be used in further List operator expressions.
 */
template<class T>
List<T>& AList<T>::operator<<(const T& value)
{
  return insertFront(value);
}

/** @brief Delete front item
 *
 * Delete the item from the front of the list.  This operation
 * is expensive for an array as we have to shift all items
 * back down, giving O(n) performance to remove the front item.
 */
template<class T>
void AList<T>::deleteFront()
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

  // iterate through values, shifting them all down by 1
  for (int index = 0; index < this->size - 1; index++)
  {
    values[index] = values[index + 1];
  }

  // size of list was reduced by 1 by removal
  this->size -= 1;
}

/** @brief Delete value(s)
 *
 * Delete the value from the list.  This method will delete all
 * instances of the value from this list that it finds.  If the list
 * does not conatin the value, then an exception is thrown.
 *
 * @param value The value to deleted from this list.
 *
 * @throws ListValueNotFoundException If we are asked to delete a value
 *   that does not exist, we thrown an exception instead of silently
 *   ignoring this condition.
 */
template<class T>
void AList<T>::deleteValue(const T& value)
{
  // flag so we can tell if we succeeded at least one time
  // or not in finding a value to remove
  bool foundValue = false;

  // iterate backwards through the list so we can safely use the
  // deleteIndex() List method to remove any values that we
  // find
  for (int index = this->size - 1; index >= 0; index--)
  {
    // if we find a value, remove it from the list
    if (values[index] == value)
    {
      deleteIndex(index);
      foundValue = true;
    }
  }

  // if we didn't find a value to delete, let the caller know there
  // may have been a problem
  if (not foundValue)
  {
    ostringstream out;
    out << "Error: <AList::deleteValue> asked to delete value: " << value << " but this value was not currently in the list";

    throw ListValueNotFoundException(out.str());
  }
}

/** @brief Delete value at index
 *
 * Delete the value from the indicated index in this
 * list.
 *
 * @param index The index of the value in the list to be removed.
 *
 * @throws ListMemoryBoundsException If an index is given below the
 *   beginning of the array or past the end we will throw a bounds
 *   exception for the illegal memory access attempt.
 */
template<class T>
void AList<T>::deleteIndex(int index)
{
  // first check that the requsted index is legally
  // within the bounds of the current size of our list
  if ((index < 0) or (index >= this->size))
  {
    ostringstream out;
    out << "Error: <AList::deleteIndex> illegal bounds access, list size: " << this->size << " tried to access index address: " << index;

    throw ListMemoryBoundsException(out.str());
  }

  // otherwise need to delete the item by shifting all items down from
  // this position to the end of the array by 1 index
  for (; index < this->size - 1; index++)
  {
    values[index] = values[index + 1];
  }

  // update size of the array after removing 1 item
  this->size--;
}

/** @brief Begin iterator
 *
 * Create and return a ListIterator pointing to the beginning of
 * this list of items, ready to be iterated over.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that keeps track of iterating over the list items.
 */
template<class T>
ListIterator<T> AList<T>::begin()
{
  // AListIterator<T>* beginItr = new AListIterator<T>(0, values);
  // return *beginItr;
  AListIterator<T> beginItr(0, values);
  return beginItr;
}

/** @brief End iterator
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
ListIterator<T> AList<T>::end()
{
  // AListIterator<T>* endItr = new AListIterator<T>(size, values);
  // return *endItr;
  AListIterator<T> endItr(this->size, values);
  return endItr;
}

/** @brief Constant begin iterator
 *
 * Create and return a ListIterator pointing to the beginning of
 * this list of items, ready to be iterated over.
 *
 * @returns ListIterator<T> returns a new instance of type
 *   ListIterator<T> that keeps track of iterating over the list items.
 */
template<class T>
ListIterator<T> AList<T>::cbegin() const
{
  AListIterator<T> beginItr(0, values);
  return beginItr;
}

/**@brief Constant end iterator
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
ListIterator<T> AList<T>::cend() const
{
  AListIterator<T> endItr(this->size, values);
  return endItr;
}

/** @brief Grow list allocation
 *
 * Private member method that will increase the memory allocation if
 * the list is currently at capacity.  To do this, we double the
 * current allocation, copy all of the values from the original block
 * of memory to the new block of memory, then delete the old block
 * that is no longer needed.  This method is called by methods that
 * need to grow the list, to ensure we have enough allocated capacity
 * to accommodate the growth.
 */
template<class T>
void AList<T>::growListIfNeeded()
{
  // if size is still less than what we have allocated, we still have room
  // to grow at least one or more items in sizes
  if (this->size < allocationSize)
  {
    return;
  }

  // otherwise size is equal to our allocation, double the size of our allocation
  // to accommodate future growth, or make size 10 initially by default if
  // an empty list is being grown
  if (allocationSize == 0)
  {
    allocationSize = INITIAL_ALLOCATION_SIZE;
  }
  else
  {
    allocationSize = 2 * allocationSize;
  }

  // dynamically allocate a new block of values of the new size
  T* newValues = new T[allocationSize];

  // copy the values from the original memory to this new block of memory
  for (int index = 0; index < this->size; index++)
  {
    newValues[index] = values[index];
  }

  // we don't need the old block of memory anymore, be good managers of
  // memory and return it to the heap
  delete[] values;

  // now make sure we are using the new block of memory going forward for this
  // list
  values = newValues;
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
template class AList<int>;
template class AList<string>;
