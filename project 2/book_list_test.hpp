// Unit tests for the BookList class.

#include <sstream>
#include <string>

#include "book.hpp"
#include "book_list.hpp"
#include "doctest.hpp"

TEST_CASE("ConstructorsAndAssignment") {
  const Book book_1("book_1"),
      book_2("book_2"),
      book_3("book_3"),
      book_4("book_4"),
      book_5("book_5"),
      book_6("book_6");

  SUBCASE("DefaultConstructor") {
    const BookList list;
    CHECK_EQ(0U, list.size());
  }

  SUBCASE("CopyConstructor") {
    const BookList list1 = {book_2, book_3, book_1, book_4};
    const BookList list2(list1);
    CHECK_EQ(list1, list2);
  }

  SUBCASE("InitializerListConstructor") {
    BookList list;
    list.insert(book_3);
    list.insert(book_4, BookList::Position::BOTTOM);
    list.insert(book_1, 1U);
    list.insert(book_2);

    const BookList expected = {book_2, book_3, book_1, book_4};
    CHECK_EQ(4U, list.size());
    CHECK_EQ(expected, list);
  }
}

TEST_CASE("Accessors") {
  const Book book_1("book_1"),
      book_2("book_2"),
      book_3("book_3"),
      book_4("book_4"),
      book_5("book_5"),
      book_6("book_6");

  BookList list1 = {book_2, book_3, book_1, book_4};
  list1 += {book_3, book_1, book_2, book_5};

  BookList list2 = {book_2, book_6, book_1, book_4};
  list1 += list2;

  const BookList expected = {book_2, book_3, book_1, book_4, book_5, book_6};

  CHECK_EQ(6U, list1.size());
  CHECK_EQ(expected, list1);
  CHECK_EQ(0U, list1.find(book_2));
  CHECK_EQ(1U, list1.find(book_3));
  CHECK_EQ(2U, list1.find(book_1));
  CHECK_EQ(3U, list1.find(book_4));
  CHECK_EQ(4U, list1.find(book_5));
  CHECK_EQ(5U, list1.find(book_6));
  CHECK_EQ(6U, list1.find(Book("Unincluded Book")));
}

TEST_CASE("Modifiers") {
  const Book book_1("book_1"),
      book_2("book_2"),
      book_3("book_3"),
      book_4("book_4"),
      book_5("book_5"),
      book_6("book_6");
  BookList list = {book_2, book_1, book_4, book_5, book_6};

  SUBCASE("RemoveByBook") {
    // Removing an item from the middle.
    CHECK_EQ(&list, &list.remove(book_1));
    CHECK_EQ(list, BookList({book_2, book_4, book_5, book_6}));

    // Removing an item from the back.
    CHECK_EQ(&list, &list.remove(book_6));
    CHECK_EQ(list, BookList({book_2, book_4, book_5}));

    // Removing an item from the front.
    CHECK_EQ(&list, &list.remove(book_2));
    CHECK_EQ(list, BookList({book_4, book_5}));

    // Removing a non-existent book.
    CHECK_EQ(&list, &list.remove(Book("not there")));
    CHECK_EQ(list, BookList({book_4, book_5}));
  }

  SUBCASE("RemoveByPosition") {
    // Removing an item from the middle.
    CHECK_EQ(&list, &list.remove(1U));
    CHECK_EQ(list, BookList({book_2, book_4, book_5, book_6}));

    // Removing an item from the back.
    CHECK_EQ(&list, &list.remove(3U));
    CHECK_EQ(list, BookList({book_2, book_4, book_5}));

    // Removing an item from the front.
    CHECK_EQ(&list, &list.remove(0U));
    CHECK_EQ(list, BookList({book_4, book_5}));

    // Removing a non-existent book.
    CHECK_EQ(&list, &list.remove(10U));
    CHECK_EQ(list, BookList({book_4, book_5}));
  }

  SUBCASE("MoveToTop") {
    BookList list = {book_2, book_1, book_4, book_5, book_6};

    CHECK_EQ(&list, &list.move_to_top(book_5));
    list.move_to_top(book_6);
    list.move_to_top(book_6);
    list.move_to_top(book_5);
    list.move_to_top(book_4);
    CHECK_EQ(&list, &list.move_to_top({"not there"}));

    const BookList expected = {book_4, book_5, book_6, book_2, book_1};

    CHECK_EQ(expected, list);
  }


  SUBCASE("Insert") {
    BookList list;

    CHECK_THROWS_AS(
      {
        for (int i = 0; i < 12; ++i) {
          list.insert(Book{"Book-" + std::to_string(i)});
        }
      }, BookList::CapacityExceededException);
  }

  SUBCASE("Chaining") {
    Book a("a"), b("b");
    BookList list = {b};

    CHECK_EQ(&list, &(list.insert(a).move_to_top(b).remove(0)));
    CHECK_EQ(list.size(), 1);
    CHECK_EQ(list, BookList({a}));
  }
}

TEST_CASE("RelationalOperators") {
  SUBCASE("Comparison") {
    const Book a("a"), b("b");
    const BookList list_a = {a};
    const BookList list_b = {b};
    CHECK(list_a < list_b);
    CHECK(list_a <= list_b);
    CHECK(list_a != list_b);
    CHECK(list_b > list_a);
    CHECK(list_b >= list_a);

    CHECK_FALSE(list_b < list_a);
    CHECK_FALSE(list_b <= list_a);
    CHECK_FALSE(list_b == list_a);
    CHECK_FALSE(list_a > list_b);
    CHECK_FALSE(list_a >= list_b);

    const BookList list_ab = {a, b};
    CHECK(list_a < list_ab);
    CHECK(list_a <= list_ab);
    CHECK(list_ab > list_a);
    CHECK(list_ab >= list_a);
    CHECK(list_ab != list_a);
    CHECK_FALSE(list_ab == list_a);
  }
}

TEST_CASE("StreamInsertion") {
  SUBCASE("ReturnsReference") {
    std::stringstream ss;
    CHECK_EQ(&ss, &(ss << Book()));
  }

  SUBCASE("WithEmptyBookList") {
    std::stringstream ss;
    ss << BookList();
    CHECK_EQ("0\n", ss.str());
  }

  SUBCASE("WithOneBook") {
    std::stringstream ss;
    ss << BookList({Book("title", "author", "isbn", 1.0)});
    CHECK_EQ("1\n    0:  \"isbn\",\"title\",\"author\",1\n\n", ss.str());
  }

  SUBCASE("WithOneRealBook") {
    std::stringstream ss;
    ss << BookList({Book("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99)});
    CHECK_EQ("1\n    0:  \"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n\n", ss.str());
  }

  SUBCASE("WithMultipleBooks") {
    std::stringstream ss;
    BookList list = {
        Book("A", "B", "123", 1.0),
        Book("D", "E", "456", 2.0),
        Book("G", "H", "789", 3.0)
    };
    ss << list;
    CHECK_EQ("3\n    0:  \"123\",\"A\",\"B\",1\n\n    1:  \"456\",\"D\",\"E\",2\n\n    2:  \"789\",\"G\",\"H\",3\n\n",
              ss.str());
  }

  SUBCASE("WithMultipleLists") {
    std::stringstream ss;
    const BookList list_1 = {
        Book("A", "B", "123", 1.0),
        Book("D", "E", "456", 2.0)
    };
    const BookList list_2 = {Book("G", "H", "789", 3.0)};

    ss << list_1 << list_2;
    CHECK_EQ("2\n    0:  \"123\",\"A\",\"B\",1\n\n    1:  \"456\",\"D\",\"E\",2\n\n1\n    0:  \"789\",\"G\",\"H\",3\n\n",
              ss.str());
  }
}

TEST_CASE("StreamExtraction") {
  SUBCASE("ReturnsReference") {
    std::stringstream ss("1\n 0:\"\",\"\",\"\",0\n");
    BookList b;
    CHECK_EQ(&ss, &(ss >> b));
  }

  SUBCASE("WithEmptyList") {
    std::stringstream ss("1\n 0: \"\",\"\",\"\",0\n");
    BookList list;
    ss >> list;
    CHECK_EQ(BookList({Book("", "", "", 0)}), list);
  }

  SUBCASE("WithOneBook") {
    std::stringstream ss("1\n 0:  \"isbn\",\"title\",\"author\",1\n\n");
    BookList list;
    ss >> list;
    CHECK_EQ(BookList({Book("title", "author", "isbn", 1.0)}), list);
  }


  SUBCASE("WithOneRealBook") {
    std::stringstream ss("1\n 0:  \"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n\n");
    BookList list;
    ss >> list;
    CHECK_EQ(BookList({Book("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99)}), list);
  }

  SUBCASE("WithMultipleBooks") {
    std::stringstream ss("3\n 0:  \"123\", \"A\", \"B\", 1\n 1:  \"456\", \"D\", \"E\", 2\n 2:  \"789\", \"G\", \"H\", 3\n\n");
    BookList list;
    ss >> list;
    CHECK_EQ(list,BookList({
        Book("A", "B", "123", 1.0),
        Book("D", "E", "456", 2.0),
        Book("G", "H", "789", 3.0)
    }));
  }

  SUBCASE("WithMultipleLists") {
    std::stringstream ss("2\n 0:  \"123\", \"A\", \"B\", 1\n 1:  \"456\", \"D\", \"E\", 2\n\n1\n 2:  \"789\", \"G\", \"H\", 3\n");
    BookList list1, list2;
    ss >> list1 >> list2;
    CHECK_EQ(list1, BookList({Book("A", "B", "123", 1.0),
      Book("D", "E", "456", 2.0)}));

    CHECK_EQ(list2, BookList({Book("G", "H", "789", 3.0)
    }));
  }
}