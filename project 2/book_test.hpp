// Unit tests for the Book class.

#include <sstream>
#include <string>

#include "book.hpp"
#include "doctest.hpp"

TEST_CASE("ConstructorsAndAssignment") {
  SUBCASE("DefaultConstructor") {
    Book b;
    CHECK_EQ("", b.title());
    CHECK_EQ("", b.author());
    CHECK_EQ("", b.isbn());
    CHECK_EQ(0.0, b.price());
  }

  SUBCASE("ConversionConstructor") {
    Book b("a", "b", "c", 8.0);
    CHECK_EQ("a", b.title());
    CHECK_EQ("b", b.author());
    CHECK_EQ("c", b.isbn());
    CHECK_EQ(8.0, b.price());
  }

  SUBCASE("CopyAssignmentConstructor") {
    Book b;
    b = Book("a", "b", "c", 8.0);
    CHECK_EQ("a", b.title());
    CHECK_EQ("b", b.author());
    CHECK_EQ("c", b.isbn());
    CHECK_EQ(8.0, b.price());
  }

  SUBCASE("CopyConstructor") {
    Book b("a", "b", "c", 8.0);
    Book c(b);
    CHECK_EQ("a", c.title());
    CHECK_EQ("b", c.author());
    CHECK_EQ("c", c.isbn());
    CHECK_EQ(8.0, c.price());
  }  
}

TEST_CASE("Accessors") {
  SUBCASE("DefaultObject") {
    Book b;
    CHECK_EQ("", b.title());
    CHECK_EQ("", b.author());
    CHECK_EQ("", b.isbn());
    CHECK_EQ(0.0, b.price());
  }

  SUBCASE("FullyInitializedObject") {
    Book b("a", "b", "c", 8.0);
    CHECK_EQ("a", b.title());
    CHECK_EQ("b", b.author());
    CHECK_EQ("c", b.isbn());
    CHECK_EQ(8.0, b.price());
  }
}

TEST_CASE("Modifiers") {
  Book b("a", "b", "c", 8.0);
  CHECK_EQ("a", b.title());
  CHECK_EQ("b", b.author());
  CHECK_EQ("c", b.isbn());
  CHECK_EQ(8.0, b.price());

  b.title("x");
  CHECK_EQ("x", b.title());
  CHECK_EQ("b", b.author());
  CHECK_EQ("c", b.isbn());
  CHECK_EQ(8.0, b.price());

  b.author("y");
  CHECK_EQ("x", b.title());
  CHECK_EQ("y", b.author());
  CHECK_EQ("c", b.isbn());
  CHECK_EQ(8.0, b.price());

  b.isbn("z");
  CHECK_EQ("x", b.title());
  CHECK_EQ("y", b.author());
  CHECK_EQ("z", b.isbn());
  CHECK_EQ(8.0, b.price());

  b.price(16.0);
  CHECK_EQ("x", b.title());
  CHECK_EQ("y", b.author());
  CHECK_EQ("z", b.isbn());
  CHECK_EQ(16.0, b.price());

  // Test methods return a reference to self.
  CHECK_EQ(&b, &b.title("a2"));
  CHECK_EQ(&b, &b.author("b2"));
  CHECK_EQ(&b, &b.isbn("c2"));
  CHECK_EQ(&b, &b.price(1.0));
  CHECK_EQ("a2", b.title());
  CHECK_EQ("b2", b.author());
  CHECK_EQ("c2", b.isbn());
  CHECK_EQ(1.0, b.price());

  // Test chaining.
  CHECK_EQ(&b, &(b.title("a3").author("b3").isbn("c3").price(-1.0)));
  CHECK_EQ("a3", b.title());
  CHECK_EQ("b3", b.author());
  CHECK_EQ("c3", b.isbn());
  CHECK_EQ(-1.0, b.price());
}

TEST_CASE("RelationalOperators") {
  Book b("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99),
      copy(b);

  const std::string different("different");
  const double different_price(1.0);

  SUBCASE("Equality") {
    CHECK(b == b);
    CHECK(b == copy);
    CHECK(b == Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK_FALSE(b == Book(different, b.author(), b.isbn(), b.price()));
    CHECK_FALSE(b == Book(b.title(), different, b.isbn(), b.price()));
    CHECK_FALSE(b == Book(b.title(), b.author(), different, b.price()));
    CHECK_FALSE(b == Book(b.title(), b.author(), b.isbn(), different_price));
  }

  SUBCASE("Inequality") {
    CHECK_FALSE(b != b);
    CHECK_FALSE(b != copy);
    CHECK_FALSE(b != Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK(b != Book(different, b.author(), b.isbn(), b.price()));
    CHECK(b != Book(b.title(), different, b.isbn(), b.price()));
    CHECK(b != Book(b.title(), b.author(), different, b.price()));
    CHECK(b != Book(b.title(), b.author(), b.isbn(), different_price));
  }

  SUBCASE("LessThan") {
    CHECK_FALSE(b < copy);
    CHECK_FALSE(b < Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK(b < Book("Z", b.author(), b.isbn(), b.price()));
    CHECK(b < Book(b.title(), "Z", b.isbn(), b.price()));
    CHECK(b < Book(b.title(), b.author(), "9999999999", b.price()));
    CHECK(b < Book(b.title(), b.author(), b.isbn(), 1000.0));
  }

  SUBCASE("LessThanOrEqual") {
    CHECK(b <= copy);
    CHECK(b <= Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK(b <= Book("Z", b.author(), b.isbn(), b.price()));
    CHECK(b <= Book(b.title(), "Z", b.isbn(), b.price()));
    CHECK(b <= Book(b.title(), b.author(), "9999999999", b.price()));
    CHECK(b <= Book(b.title(), b.author(), b.isbn(), 1000.0));
  }

  SUBCASE("GreaterThan") {
    CHECK_FALSE(b > copy);
    CHECK_FALSE(b > Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK(Book("Z", b.author(), b.isbn(), b.price()) > b);
    CHECK(Book(b.title(), "Z", b.isbn(), b.price()) > b);
    CHECK(Book(b.title(), b.author(), "9999999999", b.price()) > b);
    CHECK(Book(b.title(), b.author(), b.isbn(), 1000.0) > b);
  }

  SUBCASE("GreaterThanOrEqual") {
    CHECK(b >= copy);
    CHECK(b >= Book(b.title(), b.author(), b.isbn(), b.price()));
    CHECK(Book("Z", b.author(), b.isbn(), b.price()) >= b);
    CHECK(Book(b.title(), "Z", b.isbn(), b.price()) >= b);
    CHECK(Book(b.title(), b.author(), "9999999999", b.price()) >= b);
    CHECK(Book(b.title(), b.author(), b.isbn(), 1000.0) >= b);
  }

  SUBCASE("OrdersBy") {
    // ISBN first...
    CHECK(Book("B", "B", "A", 2.0) < Book("A", "A", "B", 1.0));
    // then author...
    CHECK(Book("B", "A", "T", 2.0) < Book("A", "B", "T", 1.0));
    // then title...
    CHECK(Book("A", "T", "T", 2.0) < Book("B", "T", "T", 1.0));
    // then price.
    CHECK(Book("T", "T", "T", 1.0) < Book("T", "T", "T", 2.0));
  }
}

TEST_CASE("StreamInsertion") {
  SUBCASE("ReturnsReferenceToStream") {
    std::stringstream ss;
    CHECK_EQ(&ss, &(ss << Book()));
  }

  SUBCASE("WithValues") {
    std::stringstream ss;
    ss << Book("title", "author", "isbn", 1.0);
    CHECK_EQ("\"isbn\",\"title\",\"author\",1\n", ss.str());
  }

  SUBCASE("WithEmptyValues") {
    std::stringstream ss;
    ss << Book();
    CHECK_EQ("\"\",\"\",\"\",0\n", ss.str());
  }

  SUBCASE("WithRealValues") {
    std::stringstream ss;
    ss << Book("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99);
    CHECK_EQ("\"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n", ss.str());
  }

  SUBCASE("ChainedInsertion") {
    std::stringstream ss;
    ss << Book("A", "B", "123", 1.0)
       << Book("D", "E", "456", 2.0)
       << Book("G", "H", "789", 3.0);
    CHECK_EQ("\"123\",\"A\",\"B\",1\n"
              "\"456\",\"D\",\"E\",2\n"
              "\"789\",\"G\",\"H\",3\n",
              ss.str());
  }
}

TEST_CASE("StreamExtraction") {
  SUBCASE("ReturnsReferenceToExtraction") {
    std::stringstream ss("\"\",\"\",\"\",0\n");
    Book b;
    CHECK_EQ(&ss, &(ss >> b));
  }

  SUBCASE("WithValues") {
    std::stringstream ss("\"isbn\",\"title\",\"author\",1\n");
    Book b;
    ss >> b;
    CHECK_EQ("isbn", b.isbn());
    CHECK_EQ("title", b.title());
    CHECK_EQ("author", b.author());
    CHECK_EQ(1.0, b.price());
  }

  SUBCASE("WithEmptyValues") {
    std::stringstream ss("\"\",\"\",\"\",0\n");
    Book b;
    ss >> b;
    CHECK_EQ("", b.isbn());
    CHECK_EQ("", b.title());
    CHECK_EQ("", b.author());
    CHECK_EQ(0.0, b.price());
  }

  SUBCASE("WithRealValues") {
    std::stringstream ss("\"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n");
    Book b;
    ss >> b;
    CHECK_EQ("9780064430173", b.isbn());
    CHECK_EQ("Goodnight Moon", b.title());
    CHECK_EQ("Margaret Wise Brown", b.author());
    CHECK_EQ(8.99, b.price());
  }

  SUBCASE("ChainedExtraction") {
    std::stringstream ss("\"123\",\"A\",\"B\",1\n"
      "\"456\",\"D\",\"E\",2\n"
      "\"789\",\"G\",\"H\",3\n");
    Book a, b, c;
    ss >> a >> b >> c;

    CHECK_EQ("123", a.isbn());
    CHECK_EQ("A", a.title());
    CHECK_EQ("B", a.author());
    CHECK_EQ(1, a.price());

    CHECK_EQ("456", b.isbn());
    CHECK_EQ("D", b.title());
    CHECK_EQ("E", b.author());
    CHECK_EQ(2, b.price());

    CHECK_EQ("789", c.isbn());
    CHECK_EQ("G", c.title());
    CHECK_EQ("H", c.author());
    CHECK_EQ(3, c.price());
  }
}