// Unit tests for the BookDatabase class.

#include "book_database.hpp"

#include "book.hpp"
#include "doctest.hpp"

TEST_CASE("Size") {
  BookDatabase& database = BookDatabase::instance();

  CHECK_EQ(database.size(), 210);
}

TEST_CASE("Find") {
  BookDatabase& database = BookDatabase::instance();

  SUBCASE("ReturnsNullptrForBookNotInDatabase") {
    CHECK(database.find("123XYZ789") == nullptr);
  }

  SUBCASE("ReturnsPointerForBookInDatabase") {
    Book* book_ptr = database.find("0001034359");
    REQUIRE(book_ptr != nullptr);
    Book expected_book = Book(
        "Tales of Hans Christian Andersen ; \n                     read by Michael Redgrave. (1st edition)",
        "Hans Christian Andersen", "0001034359", 99.92);
    CHECK_EQ(*book_ptr, expected_book);
  }

  SUBCASE("ReturnedPointerIsConsistent") {
    Book* book_ptr_one = database.find("0001034359");
    Book* book_ptr_two = database.find("0001034359");
    REQUIRE(book_ptr_one != nullptr);
    REQUIRE(book_ptr_two != nullptr);
    CHECK_EQ(book_ptr_one, book_ptr_two);
  }
}