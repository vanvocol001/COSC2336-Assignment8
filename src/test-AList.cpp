/** @file test-AList.cpp
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
#include "AList.hpp"
#include "ListException.hpp"
#include "ListIterator.hpp"
#include "catch.hpp"
#include <iostream>
using namespace std;

/** Test AList<int> concrete array implementation of list of integers
 */
TEST_CASE("AList<int> test integer list concrete array implementation", "[task0]")
{
  SECTION("test empty list is empty")
  {
    AList<int> empty;

    // empty lists should be empty
    CHECK(empty.getSize() == 0);
    CHECK(empty.getAllocationSize() == 0); // only for AList<>
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");

    // empty lists should compare as being equal
    AList<int> otherEmpty;
    CHECK(otherEmpty == empty);
    CHECK(empty == otherEmpty);

    // empty lists should complain if asked to get a value from them
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
    CHECK_THROWS_AS(empty[0], ListMemoryBoundsException);

    // empty list can be cleared and is still empty
    empty.clear();
    CHECK(empty.getSize() == 0);
    CHECK(empty.getAllocationSize() == 0); // only for AList<>
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");
  }

  SECTION("test array based constructor")
  {
    int values[] = {1, 3, -2, -4, 7};
    AList<int> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK(list.getAllocationSize() == 5); // only for AList<>
    CHECK_FALSE(list.isEmpty());
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
    CHECK_THROWS_AS(list[5], ListMemoryBoundsException);
    list[2] = 42;
    CHECK(list[2] == 42);
    CHECK(list.str() == "<list> size: 5 [ 1, 3, 42, -4, 7 ]");

    // test inserting on list, and that list allocation grows as expected
    list.insertBack(22);
    CHECK(list.getSize() == 6);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 22);
    CHECK(list.str() == "<list> size: 6 [ 1, 3, 42, -4, 7, 22 ]");

    list >> 38;
    CHECK(list.getSize() == 7);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == 1);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 7 [ 1, 3, 42, -4, 7, 22, 38 ]");

    list.insertFront(-22);
    CHECK(list.getSize() == 8);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == -22);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 8 [ -22, 1, 3, 42, -4, 7, 22, 38 ]");

    list << -38;
    CHECK(list.getSize() == 9);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == -38);
    CHECK(list.getBack() == 38);
    CHECK(list.str() == "<list> size: 9 [ -38, -22, 1, 3, 42, -4, 7, 22, 38 ]");
  }

  SECTION("test copy constructor")
  {
    int values[] = {3, 1, 4, 2};
    AList<int> list(4, values);
    AList<int> copy = list;

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
    AList<int> list(4, values);

    // list is not empty before clear
    CHECK(list.getSize() == 4);
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 4 [ 3, 1, 4, 2 ]");

    // list is empty after clear
    list.clear();
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // cleared list should be equal to empty list
    AList<int> empty;
    CHECK(list == empty);
    CHECK(empty == list);
  }

  SECTION("test deleting front values")
  {
    int values[] = {3, 1, 4};
    AList<int> list(3, values);

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 2);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ 1, 4 ]");

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 1);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ 4 ]");

    // delete from list front with 1 item, lists becomes empty
    list.deleteFront();
    CHECK(list.getSize() == 0);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from front of empty list should complain
    CHECK_THROWS_AS(list.deleteFront(), ListEmptyException);
  }

  SECTION("test deleting back values")
  {
    int values[] = {3, 1, 4};
    AList<int> list(3, values);

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 2);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ 3, 1 ]");

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 1);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ 3 ]");

    // delete from list back with 1 item, lists becomes empty
    list.deleteBack();
    CHECK(list.getSize() == 0);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from back of empty list should complain
    CHECK_THROWS_AS(list.deleteBack(), ListEmptyException);
  }

  SECTION("test delete value at index")
  {
    int values[] = {3, 1, 4, 2};
    AList<int> list(4, values);

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
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ 1 ]");

    // test delete and list becomes empty
    list.deleteIndex(0);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");
  }

  SECTION("test deletion of values from list")
  {
    int values[] = {1, 3, 2, 4, 3, 4, 5};
    AList<int> list(7, values);

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
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ 3, 3 ]");

    // test delete two values, list is now empty
    list.deleteValue(3);
    CHECK(list.getSize() == 0);
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");
  }

  SECTION("test list iteration")
  {
    int values[] = {3, 1, 4, 2};
    AList<int> list(4, values);

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

/** Test AList<string> concrete array implementation of list of strings
 */
TEST_CASE("AList<string> test string list concrete array implementation", "[task0]")
{
  SECTION("test empty list is empty")
  {
    AList<string> empty;

    // empty lists should be empty
    CHECK(empty.getSize() == 0);
    CHECK(empty.getAllocationSize() == 0); // only for AList<>
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");

    // empty lists should compare as being equal
    AList<string> otherEmpty;
    CHECK(otherEmpty == empty);
    CHECK(empty == otherEmpty);

    // empty lists should complain if asked to get a value from them
    CHECK_THROWS_AS(empty.getFront(), ListEmptyException);
    CHECK_THROWS_AS(empty.getBack(), ListEmptyException);
    CHECK_THROWS_AS(empty[0], ListMemoryBoundsException);

    // empty list can be cleared and is still empty
    empty.clear();
    CHECK(empty.getSize() == 0);
    CHECK(empty.getAllocationSize() == 0); // only for AList<>
    CHECK(empty.isEmpty());
    CHECK(empty.str() == "<list> size: 0 [ ]");
  }

  SECTION("test array based constructor")
  {
    string values[] = {"alpha", "charlie", "bravo", "delta", "golf"};
    AList<string> list(5, values);

    // nonempty list should not be empty
    CHECK(list.getSize() == 5);
    CHECK(list.getAllocationSize() == 5); // only for AList<>
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
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "too-too");
    CHECK(list.str() == "<list> size: 6 [ alpha, charlie, share-and-enjoy, delta, golf, too-too ]");

    list >> "three-ait";
    CHECK(list.getSize() == 7);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == "alpha");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() == "<list> size: 7 [ alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");

    list.insertFront("negative-too-too");
    CHECK(list.getSize() == 8);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == "negative-too-too");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() == "<list> size: 8 [ negative-too-too, alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");

    list << "negative-three-ait";
    CHECK(list.getSize() == 9);
    CHECK(list.getAllocationSize() == 10); // only for AList<>
    CHECK(list.getFront() == "negative-three-ait");
    CHECK(list.getBack() == "three-ait");
    CHECK(list.str() ==
          "<list> size: 9 [ negative-three-ait, negative-too-too, alpha, charlie, share-and-enjoy, delta, golf, too-too, three-ait ]");
  }

  SECTION("test copy constructor")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    AList<string> list(4, values);
    AList<string> copy = list;

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
    AList<string> list(4, values);

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
    AList<string> empty;
    CHECK(list == empty);
    CHECK(empty == list);
  }

  SECTION("test deleting front values")
  {
    string values[] = {"charlie", "alpha", "delta"};
    AList<string> list(3, values);

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 2);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ alpha, delta ]");

    // delete from list front with more than 1 item
    list.deleteFront();
    CHECK(list.getSize() == 1);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ delta ]");

    // delete from list front with 1 item, lists becomes empty
    list.deleteFront();
    CHECK(list.getSize() == 0);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from front of empty list should complain
    CHECK_THROWS_AS(list.deleteFront(), ListEmptyException);
  }

  SECTION("test deleting back values")
  {
    string values[] = {"charlie", "alpha", "delta"};
    AList<string> list(3, values);

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 2);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 2 [ charlie, alpha ]");

    // delete from list back with more than 1 item
    list.deleteBack();
    CHECK(list.getSize() == 1);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK_FALSE(list.isEmpty());
    CHECK(list.str() == "<list> size: 1 [ charlie ]");

    // delete from list back with 1 item, lists becomes empty
    list.deleteBack();
    CHECK(list.getSize() == 0);
    CHECK(list.getAllocationSize() == 3); // only for AList<>
    CHECK(list.isEmpty());
    CHECK(list.str() == "<list> size: 0 [ ]");

    // deleting from back of empty list should complain
    CHECK_THROWS_AS(list.deleteBack(), ListEmptyException);
  }

  SECTION("test delete value at index")
  {
    string values[] = {"charlie", "alpha", "delta", "bravo"};
    AList<string> list(4, values);

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
    AList<string> list(7, values);

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
    AList<string> list(4, values);

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
