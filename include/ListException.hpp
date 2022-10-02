/** @file ListException.hpp
 * @brief Declare Exceptions that can be thrown by List instances.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Declare all exceptions that can be generated and thrown by List
 * instances.
 */
#ifndef _LIST_EXCEPTION_HPP_
#define _LIST_EXCEPTION_HPP_
#include <string>
using namespace std;

/** @class ListEmptyException
 * @brief List Empty Exception for the List class.
 *
 * Exception to be thrown by our List class if attempt
 * to access item from front, back or anywhere of an
 * empty list is attempted.
 *
 */
class ListEmptyException : public exception
{
public:
  explicit ListEmptyException(const string& message);
  ~ListEmptyException();
  virtual const char* what() const throw();

private:
  /// Stores the particular message describing what caused the exception.
  string message;
};

/** @class ListMemoryBoundsException
 * @brief Memory Bounds Exception for the List class.
 *
 * Exception to be thrown by our List class if an illegal
 * memory bounds access is attempted.
 *
 */
class ListMemoryBoundsException : public exception
{
public:
  explicit ListMemoryBoundsException(const string& message);
  ~ListMemoryBoundsException();
  virtual const char* what() const throw();

private:
  /// Stores the particular message describing what caused the exception.
  string message;
};

/** @class ListValueNotFoundException
 * @brief Search for a value expected in list failed.
 *
 * Exception to be thrown by our List class if a search
 * for an expected value fails.
 *
 */
class ListValueNotFoundException : public exception
{
public:
  explicit ListValueNotFoundException(const string& message);
  ~ListValueNotFoundException();
  virtual const char* what() const throw();

private:
  /// Stores the particular message describing what caused the exception.
  string message;
};

#endif // _LIST_EXCEPTION_HPP_