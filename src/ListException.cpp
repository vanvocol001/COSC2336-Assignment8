/** @file ListException.cpp
 * @brief Implement Exceptions that can be thrown by List instances.
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Linked Lists
 * @date   June 1, 2021
 *
 * Implementall exception methods that can be generated and thrown by List
 * instances.
 */
#include "ListException.hpp"
#include <string>
using namespace std;

/**
 * @brief ListEmptyException constructor
 *
 * Constructor for exceptions used for our
 * List  class.
 *
 * @param message The exception message thrown when an error occurs.
 */
ListEmptyException::ListEmptyException(const string& message)
{
  this->message = message;
}

/**
 * @brief ListEmptyException destructor
 *
 * Destructor for exceptions used for our ListEmptyException
 * class.
 */
ListEmptyException::~ListEmptyException() {}

/**
 * @brief ListEmptyException message
 *
 * Accessor method to access/return message given when an exception occurs.
 *
 * @returns char* Returns a const old style c character array message for
 *   display/use by the process that catches this exception.
 */
const char* ListEmptyException::what() const throw()
{
  // what expects old style array of characters, so convert to that
  return message.c_str();
}

/**
 * @brief ListMemoryBoundsException constructor
 *
 * Constructor for exceptions used for our
 * List  class.
 *
 * @param message The exception message thrown when an error occurs.
 */
ListMemoryBoundsException::ListMemoryBoundsException(const string& message)
{
  this->message = message;
}

/**
 * @brief ListMemoryBoundsException destructor
 *
 * Destructor for exceptions used for our ListMemoryBoundsException
 * class.
 */
ListMemoryBoundsException::~ListMemoryBoundsException() {}

/**
 * @brief ListMemoryBoundsException message
 *
 * Accessor method to access/return message given when an exception occurs.
 *
 * @returns char* Returns a const old style c character array message for
 *   display/use by the process that catches this exception.
 */
const char* ListMemoryBoundsException::what() const throw()
{
  // what expects old style array of characters, so convert to that
  return message.c_str();
}

/**
 * @brief ListValueNotFoundException constructor
 *
 * Constructor for exceptions used for our
 * List  class.
 *
 * @param message The exception message thrown when an error occurs.
 */
ListValueNotFoundException::ListValueNotFoundException(const string& message)
{
  this->message = message;
}

/**
 * @brief ListValueNotFoundException destructor
 *
 * Destructor for exceptions used for our ListValueNotFoundException
 * class.
 */
ListValueNotFoundException::~ListValueNotFoundException() {}

/**
 * @brief ListValueNotFoundException message
 *
 * Accessor method to access/return message given when an exception occurs.
 *
 * @returns char* Returns a const old style c character array message for
 *   display/use by the process that catches this exception.
 */
const char* ListValueNotFoundException::what() const throw()
{
  // what expects old style array of characters, so convert to that
  return message.c_str();
}