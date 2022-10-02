/** @file test-LList.cpp
 * @brief Unit tests for Assignment Overloading and Templates
 *
 * @author Derek Harter
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Sorting and Searching
 * @date   June 1, 2021
 *
 * Overload operators for our List user defined type and
 * templatize the class to containt any data type needed
 * in the list.
 *
 * This file contains test cases and individual unit tests for the
 * Assignment Overloading and Templates implementation.  This file uses
 * the catch2 unit test framework to define the test cases and test
 * assertions.
 */
#include "LList.hpp"
#include "ListException.hpp"
#include "ListIterator.hpp"
#include "catch.hpp"
#include <iostream>
using namespace std;

/** Task 1: Test LList insertBack() basic functionality.  For first task, initially
 * only have the default constructor until you get this first function
 * working.  So this method simply checks the function is present and can
 * insert items on an empty list.
 */

   TEST_CASE("LList test basic insertBack() functionality",
          "[task1]")
   {
   SECTION("test insert back on empty integer list")
   {
    LList<int> list;
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // list goes from empty to size 1
    list.insertBack(5);
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 5 ]");

    // list goes to size 2 now
    list.insertBack(7);
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 5, 7 ]");
   }

   SECTION("test insert back on empty string list")
   {
    LList<string> list;
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // list goes from empty to size 1
    list.insertBack("echo");
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ echo ]");

    // list goes to size 2 now
    list.insertBack("golf");
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ echo, golf ]");
   }
   }
 

/** Task 1: Test LList insertBack() and overloaded operator>> and constructors
 *    that use the append operations.
 */

   TEST_CASE("LList test insertBack() and overloaded operator>>",
          "[task1]")
   {
   SECTION("test array based constructor on integer list")
   {
    int values[] = {1, 3, -2, -4, 7};
    LList<int> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 5 [ 1, 3, -2, -4, 7 ]");

    // test indexing access
    CHECK(list[0] == 1);
    CHECK(list[1] == 3);
    CHECK(list[2] == -2);
    CHECK(list[3] == -4);
    CHECK(list[4] == 7);
    CHECK_THROWS_AS(list[-1], ListMemoryBoundsException);
    CHECK_THROWS_AS(list[5],  ListMemoryBoundsException);
    list[2] = 42;
    CHECK(list[2] == 42);
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 42, -4, 7 ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertBack(22);
    CHECK(list.getSize() == 6);
    CHECK(list.str() == "<list> size: 6 [ 1, 3, 42, -4, 7, 22 ]");

    list >> 38;
    CHECK(list.getSize() == 7);
    CHECK(list.str() == "<list> size: 7 [ 1, 3, 42, -4, 7, 22, 38 ]");
   }

   SECTION("test copy constructor on integer list")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);
    LList<int> copy = list;

    // copy should be equal to the list
    CHECK(copy == list);
    CHECK(list == copy);

    // copy is no longer equal
    list[1] = 5;
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);

    // now they are the same again
    copy[1] = 5;
    CHECK(copy == list);
    CHECK(list == copy);
   }

   SECTION("test array based constructor on string list")
   {
    string values[] = {"alpha", "charlie", "negative-bravo", "negative-delta", "golf"};
    LList<string> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, negative-bravo, negative-delta, golf ]");

    // test indexing access
    CHECK(list[0] == "alpha");
    CHECK(list[1] == "charlie");
    CHECK(list[2] == "negative-bravo");
    CHECK(list[3] == "negative-delta");
    CHECK(list[4] == "golf");
    CHECK_THROWS_AS(list[-1], ListMemoryBoundsException);
    CHECK_THROWS_AS(list[5],  ListMemoryBoundsException);
    list[2] = "life-universe-everything";
    CHECK(list[2] == "life-universe-everything");
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, life-universe-everything, negative-delta, golf ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertBack("victor");
    CHECK(list.getSize() == 6);
    CHECK(list.str() == "<list> size: 6 [ alpha, charlie, life-universe-everything, negative-delta, golf, victor ]");

    list >> "zulu";
    CHECK(list.getSize() == 7);
    CHECK(list.str() == "<list> size: 7 [ alpha, charlie, life-universe-everything, negative-delta, golf, victor, zulu ]");
   }

   SECTION("test copy constructor on integer list")
   {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);
    LList<string> copy = list;

    // copy should be equal to the list
    CHECK(copy == list);
    CHECK(list == copy);

    // copy is no longer equal
    list[1] = "echo";
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);

    // now they are the same again
    copy[1] = "echo";
    CHECK(copy == list);
    CHECK(list == copy);
   }
   }
 

/** Task 2: Test LList getFront() member accessor method
 */

   TEST_CASE("LList test getFront() member accessor method",
          "[task2]")
   {
   SECTION("test attempt to access empty int list throws expected exception")
   {
    LList<int> empty;
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
   }

   SECTION("test attempt to access empty string list throws expected exception")
   {
    LList<string> empty;
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
   }


   SECTION("test get front on integer list")
   {
    // list of size 1 should be able to get front item
    int values1[] = {5};
    LList<int> list1(1, values1);
    CHECK(list1.getFront() == 5);

    // list of size 2 should be able to get front item
    int values2[] = {3, 5};
    LList<int> list2(2, values2);
    CHECK(list2.getFront() == 3);

    // list of more items should be able to get the front item
    int values3[] = {7, 3, 5};
    LList<int> list3(3, values3);
    CHECK(list3.getFront() == 7);

    // if front item changes, we should get new value
    list1[0] = 42;
    CHECK(list1.getFront() == 42);
    list3[0] = 38;
    CHECK(list3.getFront() == 38);
   }

   SECTION("test get front on string list")
   {
    // list of size 1 should be able to get front item
    string values1[] = {"echo"};
    LList<string> list1(1, values1);
    CHECK(list1.getFront() == "echo");

    // list of size 2 should be able to get front item
    string values2[] = {"charlie", "echo"};
    LList<string> list2(2, values2);
    CHECK(list2.getFront() == "charlie");

    // list of more items should be able to get the front item
    string values3[] = {"golf", "charlie", "echo"};
    LList<string> list3(3, values3);
    CHECK(list3.getFront() == "golf");

    // if front item changes, we should get new value
    list1[0] = "thanks-for-the-fish";
    CHECK(list1.getFront() == "thanks-for-the-fish");
    list3[0] = "sierra";
    CHECK(list3.getFront() == "sierra");
   }
   }
 

/** Task 2: Test LList getBack() member accessor method
 */

   TEST_CASE("LList test getBack() member accessor method",
          "[task2]")
   {
   SECTION("test attempt to access empty int list throws expected exception")
   {
    LList<int> empty;
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
   }

   SECTION("test attempt to access empty string list throws expected exception")
   {
    LList<string> empty;
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
   }


   SECTION("test get back on integer list")
   {
    // list of size 1 should be able to get back item
    int values1[] = {5};
    LList<int> list1(1, values1);
    CHECK(list1.getBack() == 5);

    // list of size 2 should be able to get front item
    int values2[] = {5, 3};
    LList<int> list2(2, values2);
    CHECK(list2.getBack() == 3);

    // list of more items should be able to get the back item
    int values3[] = {5, 3, 7};
    LList<int> list3(3, values3);
    CHECK(list3.getBack() == 7);

    // if back item changes, we should get new value
    list1[0] = 42;
    CHECK(list1.getBack() == 42);
    list3[2] = 38;
    CHECK(list3.getBack() == 38);
   }

   SECTION("test get back on string list")
   {
    // list of size 1 should be able to get back item
    string values1[] = {"echo"};
    LList<string> list1(1, values1);
    CHECK(list1.getBack() == "echo");

    // list of size 2 should be able to get back item
    string values2[] = {"echo", "charlie"};
    LList<string> list2(2, values2);
    CHECK(list2.getBack() == "charlie");

    // list of more items should be able to get the back item
    string values3[] = {"echo", "charlie", "golf"};
    LList<string> list3(3, values3);
    CHECK(list3.getBack() == "golf");

    // if front item changes, we should get new value
    list1[0] = "thanks-for-the-fish";
    CHECK(list1.getBack() == "thanks-for-the-fish");
    list3[2] = "sierra";
    CHECK(list3.getBack() == "sierra");
   }
   }
 

/** Task 3: Test LList insertFront() basic functionality
 */

   TEST_CASE("LList test basic insertFront() functionality",
          "[task3]")
   {
   SECTION("test insert front on empty integer list")
   {
    LList<int> list;
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // list goes from empty to size 1
    list.insertFront(5);
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 5 ]");

    // list goes to size 2 now
    list.insertFront(7);
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 7, 5 ]");
   }

   SECTION("test insert front on empty string list")
   {
    LList<string> list;
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // list goes from empty to size 1
    list.insertFront("echo");
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ echo ]");

    // list goes to size 2 now
    list.insertFront("golf");
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ golf, echo ]");
   }
   }
 

/** Task 3: Test LList insertFront() and overloaded operator<<
 */

   TEST_CASE("LList test insertFront() and overloaded operator<<",
          "[task3]")
   {
   SECTION("test array based constructor on integer list")
   {
    int values[] = {1, 3, -2, -4, 7};
    LList<int> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 5 [ 1, 3, -2, -4, 7 ]");

    // test indexing access
    list[2] = 42;
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 42, -4, 7 ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertFront(22);
    CHECK(list.getSize() == 6);
    CHECK(list.str() == "<list> size: 6 [ 22, 1, 3, 42, -4, 7 ]");

    list << 38;
    CHECK(list.getSize() == 7);
    CHECK(list.str() == "<list> size: 7 [ 38, 22, 1, 3, 42, -4, 7 ]");
   }

   SECTION("test array based constructor on string list")
   {
    string values[] = {"alpha", "charlie", "negative-bravo", "negative-delta", "golf"};
    LList<string> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, negative-bravo, negative-delta, golf ]");

    // test indexing access
    list[2] = "life-universe-everything";
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, life-universe-everything, negative-delta, golf ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertFront("victor");
    CHECK(list.getSize() == 6);
    CHECK(list.str() == "<list> size: 6 [ victor, alpha, charlie, life-universe-everything, negative-delta, golf ]");

    list << "zulu";
    CHECK(list.getSize() == 7);
    CHECK(list.str() == "<list> size: 7 [ zulu, victor, alpha, charlie, life-universe-everything, negative-delta, golf ]");
   }
   }
 

/** Task 4: Test LList deleteIndex() mutator method
 */

   TEST_CASE("LList test deleteIndex() mutator method",
          "[task4]")
   {
   SECTION("test delete value at index from list of integers")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);

    // test request to delete invalid index
    CHECK_THROWS_AS(list.deleteIndex(-1), ListMemoryBoundsException);
    CHECK_THROWS_AS(list.deleteIndex(4), ListMemoryBoundsException);

    // single value from middle
    list.deleteIndex(2);
    CHECK(list.getSize() == 3);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 2);
    CHECK(list.str() == "<list> size: 3 [ 3, 1, 2 ]");

    // test delete first index
    list.deleteIndex(0);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 2);
    CHECK(list.str() == "<list> size: 2 [ 1, 2 ]");

    // test delete last index
    list.deleteIndex(1);
    CHECK(list.getSize() == 1);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 1 ]");

    // test delete and list becomes empty
    list.deleteIndex(0);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");
   }

   SECTION("test delete value at index from list of strings")
   {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);

    // test request to delete invalid index
    CHECK_THROWS_AS(list.deleteIndex(-1), ListMemoryBoundsException);
    CHECK_THROWS_AS(list.deleteIndex(4), ListMemoryBoundsException);

    // single value from middle
    list.deleteIndex(2);
    CHECK(list.getSize() == 3);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "bravo");
    CHECK(list.str() == "<list> size: 3 [ charlie, alpha, bravo ]");

    // test delete first index
    list.deleteIndex(0);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "bravo");
    CHECK(list.str() == "<list> size: 2 [ alpha, bravo ]");

    // test delete last index
    list.deleteIndex(1);
    CHECK(list.getSize() == 1);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "alpha");
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ alpha ]");

    // test delete and list becomes empty
    list.deleteIndex(0);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");
   }
   }
 

/** Task 5: Test LList deleteValue() mutator method
 */

   TEST_CASE("LList test deleteValue() mutator method",
          "[task5]")
   {
   SECTION("test deletion of values from list of integers")
   {
    int values[] = {1, 3, 2, 4, 3, 4, 5};
    LList<int> list(7, values);

    // test request of nonexistent value non empty list
    CHECK_THROWS_AS(list.deleteValue(6), ListValueNotFoundException);

    // single value from middle
    list.deleteValue(2);
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 5);
    CHECK(list.str() == "<list> size: 6 [ 1, 3, 4, 3, 4, 5 ]");

    // test delete back value
    list.deleteValue(5);
    CHECK(list.getSize() == 5);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 4);
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 4, 3, 4 ]");

    // test delete front value
    list.deleteValue(1);
    CHECK(list.getSize() == 4);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 4);
    CHECK(list.str() == "<list> size: 4 [ 3, 4, 3, 4 ]");

    // test delete two values, one is a back value
    list.deleteValue(4);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 3);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 3, 3 ]");

    // test delete two values, list is now empty
    list.deleteValue(3);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // test request of nonexistent value from empty list
    CHECK_THROWS_AS(list.deleteValue(6), ListValueNotFoundException);
   }

   SECTION("test deletion of values from list of strings")
   {
    string values[] = {"alpha", "charlie", "bravo", "delta", "charlie", "delta", "echo"};
    LList<string> list(7, values);

    // test request of nonexistent value from nonempty list
    CHECK_THROWS_AS(list.deleteValue("whisky"), ListValueNotFoundException);

    // single value from middle
    list.deleteValue("bravo");
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "echo");
    CHECK(list.str() == "<list> size: 6 [ alpha, charlie, delta, charlie, delta, echo ]");

    // test delete back value
    list.deleteValue("echo");
    CHECK(list.getSize() == 5);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "delta");
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, delta, charlie, delta ]");

    // test delete front value
    list.deleteValue("alpha");
    CHECK(list.getSize() == 4);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "delta");
    CHECK(list.str() == "<list> size: 4 [ charlie, delta, charlie, delta ]");

    // test delete two values, one is a back value
    list.deleteValue("delta");
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "charlie");
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ charlie, charlie ]");

    // test delete two values, list is now empty
    list.deleteValue("charlie");
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // test request of nonexistent value from empty list
    CHECK_THROWS_AS(list.deleteValue("whisky"), ListValueNotFoundException);
   }
   }
 

/** Tasks complete: LList<int> concrete linked list implementation of list of integers
 * Once you have completed tasks 1-5 and are passsing all of the above tests,
 * uncomment the final 2 tests here.  These perform a more complete set of tests
 * on the LList class, and in fact perform exactly the same set of tests performed
 * on the AList in the other unit test file.
 */

   TEST_CASE("LList<int> test integer list concrete linked list implementation",
          "[task5]")
   {
   SECTION("test empty list is empty")
   {
    LList<int> empty;

    // empty lists should be empty
    CHECK(empty.getSize() == 0);
    CHECK(empty.isEmpty() );
    CHECK(empty.str() == "<list> size: 0 [ ]");

    // empty lists should compare as being equal
    LList<int> otherEmpty;
    CHECK(otherEmpty == empty);
    CHECK(empty == otherEmpty);

    // empty lists should complain if asked to get a value from them
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
    CHECK_THROWS_AS(empty[0], ListMemoryBoundsException);

    // empty list can be cleared and is still empty
    empty.clear();
    CHECK(empty.getSize() == 0);
    CHECK(empty.isEmpty() );
    CHECK(empty.str() == "<list> size: 0 [ ]");
   }

   SECTION("test array based constructor")
   {
    int values[] = {1, 3, -2, -4, 7};
    LList<int> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 5 [ 1, 3, -2, -4, 7 ]");

    // test access to front and back
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 7);

    // test indexing access
    CHECK(list[0] == 1);
    CHECK(list[1] == 3);
    CHECK(list[2] == -2);
    CHECK(list[3] == -4);
    CHECK(list[4] == 7);
    CHECK_THROWS_AS(list[-1], ListMemoryBoundsException);
    CHECK_THROWS_AS(list[5],  ListMemoryBoundsException);
    list[2] = 42;
    CHECK(list[2] == 42);
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 42, -4, 7 ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertBack(22);
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 22);
    CHECK(list.str() == "<list> size: 6 [ 1, 3, 42, -4, 7, 22 ]");

    list >> 38;
    CHECK(list.getSize() == 7);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 7 [ 1, 3, 42, -4, 7, 22, 38 ]");

    list.insertFront(-22);
    CHECK(list.getSize() == 8);
    CHECK(list.getFront() == -22);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 8 [ -22, 1, 3, 42, -4, 7, 22, 38 ]");

    list << -38;
    CHECK(list.getSize() == 9);
    CHECK(list.getFront() == -38);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 9 [ -38, -22, 1, 3, 42, -4, 7, 22, 38 ]");
   }

   SECTION("test copy constructor")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);
    LList<int> copy = list;

    // copy should be equal to the list
    CHECK(copy == list);
    CHECK(list == copy);

    // copy is no longer equal
    list[1] = 5;
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);

    // now they are the same again
    copy[1] = 5;
    CHECK(copy == list);
    CHECK(list == copy);

    // now they are no longer equal, copy is 1 shorter
    copy.deleteValue(2);
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);
   }

   SECTION("test clear operation")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);

    // list is not empty before clear
    CHECK(list.getSize() == 4);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 4 [ 3, 1, 4, 2 ]");

    // list is empty after clear
    list.clear();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // cleared list should be equal to empty list
    LList<int> empty;
    CHECK(list == empty);
    CHECK(empty == list);
   }

   SECTION("test deleting front values")
   {
    int values[] = {3, 1, 4};
    LList<int> list(3, values);

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 1, 4 ]");

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 4 ]");

    // delete from list front with 1 item, lists becomes empty
    list.deleteFront();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from front of empty list should complain
    CHECK_THROWS_AS(list.deleteFront(), ListEmptyException);
   }

   SECTION("test deleting back values")
   {
    int values[] = {3, 1, 4};
    LList<int> list(3, values);

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 3, 1 ]");

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 3 ]");

    // delete from list back with 1 item, lists becomes empty
    list.deleteBack();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from back of empty list should complain
    CHECK_THROWS_AS(list.deleteBack(), ListEmptyException);
   }

   SECTION("test delete value at index")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);

    // test request to delete invalid index
    CHECK_THROWS_AS(list.deleteIndex(-1), ListMemoryBoundsException);
    CHECK_THROWS_AS(list.deleteIndex(4), ListMemoryBoundsException);

    // single value from middle
    list.deleteIndex(2);
    CHECK(list.getSize() == 3);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 2);
    CHECK(list.str() == "<list> size: 3 [ 3, 1, 2 ]");

    // test delete first index
    list.deleteIndex(0);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 2);
    CHECK(list.str() == "<list> size: 2 [ 1, 2 ]");

    // test delete last index
    list.deleteIndex(1);
    CHECK(list.getSize() == 1);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 1);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 1 [ 1 ]");

    // test delete and list becomes empty
    list.deleteIndex(0);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");

   }

   SECTION("test deletion of values from list")
   {
    int values[] = {1, 3, 2, 4, 3, 4, 5};
    LList<int> list(7, values);

    // test request of nonexistent value
    CHECK_THROWS_AS(list.deleteValue(6), ListValueNotFoundException);

    // single value from middle
    list.deleteValue(2);
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 5);
    CHECK(list.str() == "<list> size: 6 [ 1, 3, 4, 3, 4, 5 ]");

    // test delete back value
    list.deleteValue(5);
    CHECK(list.getSize() == 5);
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 4);
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 4, 3, 4 ]");

    // test delete front value
    list.deleteValue(1);
    CHECK(list.getSize() == 4);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 4);
    CHECK(list.str() == "<list> size: 4 [ 3, 4, 3, 4 ]");

    // test delete two values, one is a back value
    list.deleteValue(4);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == 3);
    CHECK(list.getBack() == 3);
    CHECK_FALSE(list.isEmpty() );
    CHECK(list.str() == "<list> size: 2 [ 3, 3 ]");

    // test delete two values, list is now empty
    list.deleteValue(3);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty() );
    CHECK(list.str() == "<list> size: 0 [ ]");
   }

   SECTION("test list iteration")
   {
    int values[] = {3, 1, 4, 2};
    LList<int> list(4, values);

    // iterate using the indexing operator[] of the list abstraction
    for (int index = 0; index < list.getSize(); index++)
    {
      CHECK(list[index] == values[index]);
    }

    // iterate using C++ explicit iterator object
    ListIterator<int> itr;
    int index = 0;
    for (itr = list.begin(); itr != list.end(); ++itr)
    {
      int item = *itr;
      CHECK(item == values[index]);
      index++;
    }

    // iterate using C++ range based iteration with cleaner syntax, but
    // these use the iterator objects behind the scenes
    index = 0;
    for (int value : list)
    {
      CHECK(value == values[index]);
      index++;
    }
   }
   }
 

/** Tasks complete: Test LList<string> concrete linked list
 *   implementation of list of strings
 */

TEST_CASE("LList<string> test string list concrete linked list implementation", "[task5]")
{
  SECTION("test empty list is empty")
  {
    LList<string> empty;

    // empty lists should be empty
    CHECK(empty.getSize() == 0);
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");

    // empty lists should compare as being equal
    LList<string> otherEmpty;
    CHECK(otherEmpty == empty);
    CHECK(empty == otherEmpty);

    // empty lists should complain if asked to get a value from them
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
    CHECK_THROWS_AS(empty[0], ListMemoryBoundsException);

    // empty list can be cleared and is still empty
    empty.clear();
    CHECK(empty.getSize() == 0);
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");
  }

  SECTION("test array based constructor")
  {
    string values[] = {"alpha", "charlie", "bravo", "delta", "golf"};
    LList<string> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, bravo, delta, golf ]");

    // test access to front and back
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "golf");

    // test indexing access
    CHECK(list[0] == "alpha");
    CHECK(list[1] == "charlie");
    CHECK(list[2] == "bravo");
    CHECK(list[3] == "delta");
    CHECK(list[4] == "golf");
    CHECK_THROWS_AS(list[-1], ListMemoryBoundsException);
    CHECK_THROWS_AS(list[5], ListMemoryBoundsException);
    list[2] = "share-and-enjoy";
    CHECK(list[2] == "share-and-enjoy");
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, share-and-enjoy, delta, golf ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertBack("too-too");
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "too-too");
    CHECK(list.str() == "<list> size: 6 [ alpha, charlie, share-and-enjoy, delta, golf, too-too ]");

    list >> "three-ait";
    CHECK(list.getSize() == 7);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() == "<list> size: 7 [ alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");

    list.insertFront("negative-too-too");
    CHECK(list.getSize() == 8);
    CHECK(list.getFront() == "negative-too-too");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() == "<list> size: 8 [ negative-too-too, alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");

    list << "negative-three-ait";
    CHECK(list.getSize() == 9);
    CHECK(list.getFront() == "negative-three-ait");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() ==
          "<list> size: 9 [ negative-three-ait, negative-too-too, alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");
  }

  SECTION("test copy constructor")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);
    LList<string> copy = list;

    // copy should be equal to the list
    CHECK(copy == list);
    CHECK(list == copy);

    // copy is no longer equal
    list[1] = "echo";
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);

    // now they are the same again
    copy[1] = "echo";
    CHECK(copy == list);
    CHECK(list == copy);

    // now they are no longer equal, copy is 1 shorter
    copy.deleteValue("bravo");
    CHECK_FALSE(copy == list);
    CHECK_FALSE(list == copy);
  }

  SECTION("test clear operation")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);

    // list is not empty before clear
    CHECK(list.getSize() == 4);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 4 [ charlie, alpha, delta, bravo ]");

    // list is empty after clear
    list.clear();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // cleared list should be equal to empty list
    LList<string> empty;
    CHECK(list == empty);
    CHECK(empty == list);
  }

  SECTION("test deleting front values")
  {
    string values[] = {"charlie", "alpha", "delta"};
    LList<string> list(3, values);

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ alpha, delta ]");

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ delta ]");

    // delete from list front with 1 item, lists becomes empty
    list.deleteFront();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from front of empty list should complain
    CHECK_THROWS_AS(list.deleteFront(), ListEmptyException);
  }

  SECTION("test deleting back values")
  {
    string values[] = {"charlie", "alpha", "delta"};
    LList<string> list(3, values);

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 2);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ charlie, alpha ]");

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 1);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ charlie ]");

    // delete from list back with 1 item, lists becomes empty
    list.deleteBack();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from back of empty list should complain
    CHECK_THROWS_AS(list.deleteBack(), ListEmptyException);
  }

  SECTION("test delete value at index")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);

    // test request to delete invalid index
    CHECK_THROWS_AS(list.deleteIndex(-1), ListMemoryBoundsException);
    CHECK_THROWS_AS(list.deleteIndex(4), ListMemoryBoundsException);

    // single value from middle
    list.deleteIndex(2);
    CHECK(list.getSize() == 3);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "bravo");
    CHECK(list.str() == "<list> size: 3 [ charlie, alpha, bravo ]");

    // test delete first index
    list.deleteIndex(0);
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "bravo");
    CHECK(list.str() == "<list> size: 2 [ alpha, bravo ]");

    // test delete last index
    list.deleteIndex(1);
    CHECK(list.getSize() == 1);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "alpha");
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ alpha ]");

    // test delete and list becomes empty
    list.deleteIndex(0);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");
  }

  SECTION("test deletion of values from list")
  {
    string values[] = {"alpha", "charlie", "bravo", "delta", "charlie", "delta", "echo"};
    LList<string> list(7, values);

    // test request of nonexistent value
    CHECK_THROWS_AS(list.deleteValue("whisky"), ListValueNotFoundException);

    // single value from middle
    list.deleteValue("bravo");
    CHECK(list.getSize() == 6);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "echo");
    CHECK(list.str() == "<list> size: 6 [ alpha, charlie, delta, charlie, delta, echo ]");

    // test delete back value
    list.deleteValue("echo");
    CHECK(list.getSize() == 5);
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "delta");
    CHECK(list.str() == "<list> size: 5 [ alpha, charlie, delta, charlie, delta ]");

    // test delete front value
    list.deleteValue("alpha");
    CHECK(list.getSize() == 4);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "delta");
    CHECK(list.str() == "<list> size: 4 [ charlie, delta, charlie, delta ]");

    // test delete two values, one is a back value
    list.deleteValue("delta");
    CHECK(list.getSize() == 2);
    CHECK(list.getFront() == "charlie");
    CHECK(list.getBack() == "charlie");
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ charlie, charlie ]");

    // test delete two values, list is now empty
    list.deleteValue("charlie");
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");
  }

  SECTION("test list iteration")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    LList<string> list(4, values);

    // iterate using the indexing operator[] of the list abstraction
    for (int index = 0; index < list.getSize(); index++)
    {
      CHECK(list[index] == values[index]);
    }

    // iterate using C++ explicit iterator object
    ListIterator<string> itr;
    int index = 0;
    for (itr = list.begin(); itr != list.end(); ++itr)
    {
      string value = *itr;
      CHECK(value == values[index]);
      index++;
    }

    // iterate using C++ range based iteration with cleaner syntax, but
    // these use the iterator objects behind the scenes
    index = 0;
    for (string value : list)
    {
      CHECK(value == values[index]);
      index++;
    }
  }
}

