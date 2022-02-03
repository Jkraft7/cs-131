// Unit tests for the Checkout class.

#include "checkout.hpp"

#include <stack>

#include "book.hpp"
#include "book_database.hpp"
#include "doctest.hpp"

TEST_CASE("ShopForBooks") {
  Checkout checkout;
  checkout.shop_for_books();
  
  SUBCASE("CartSize") {
    CHECK_EQ(checkout.my_cart().size(), 5);
  }

  SUBCASE("BookOrder") {
    std::vector<Book> books = {
        Book("Like the Animals", "", "9780895656926", 0.0),
        Book("131 Answer Key", "", "54782169785", 0.0),
        Book("Les Mis", "", "0140444300", 0.0),
        Book("Eat pray love", "", "9780399576775", 0.0),
        Book("Hunger Games", "", "9780545310581", 0.0),
    };
    std::vector<Book>::iterator iter = books.begin();

    std::stack<Book> copy = checkout.my_cart();
    while (!copy.empty() && iter != books.end()) {
      CHECK_EQ(copy.top(), *iter);
      copy.pop();
      iter++;
    }

    CHECK(copy.empty());
    CHECK_EQ(iter, books.end());
  }
}

TEST_CASE("SwitchCarts") {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();

  SUBCASE("CartSize") {
    CHECK_EQ(checkout.working_cart().size(), 5);
  }

  SUBCASE("BookOrder") {
    std::vector<Book> books = {
        Book("Like the Animals", "", "9780895656926", 0.0),
        Book("131 Answer Key", "", "54782169785", 0.0),
        Book("Les Mis", "", "0140444300", 0.0),
        Book("Eat pray love", "", "9780399576775", 0.0),
        Book("Hunger Games", "", "9780545310581", 0.0),
    };
    std::vector<Book>::iterator iter = books.begin();

    std::stack<Book> copy = checkout.working_cart();
    while (!copy.empty() && iter != books.end()) {
      CHECK_EQ(copy.top(), *iter);
      copy.pop();
      iter++;
    }

    CHECK(copy.empty());
    CHECK_EQ(iter, books.end());
  }

  SUBCASE("CarefullyMoveBooks:QuantityOne") {
    Book q = Book("Q", "", "", 0.0);
    std::stack<Book> broken = std::stack<Book>({q});
    std::stack<Book> working = std::stack<Book>({
        Book("A", "", "", 0.0), Book("B", "", "", 0.0), Book("C", "", "", 0.0) 
    });
    std::stack<Book> working_expected = working;
    working_expected.push(q);
    std::stack<Book> spare = std::stack<Book>({
      Book("X", "", "", 0.0), Book("Y", "", "", 0.0), Book("Z", "", "", 0.0) 
    });
    std::stack<Book> spare_copy = spare;
    checkout.carefully_move_books(1, broken, working, spare);
    CHECK_EQ(broken.size(), 0);
    CHECK_EQ(spare, spare_copy);
    CHECK_EQ(working, working_expected);
  }

  SUBCASE("CarefullyMoveBooks:QuantityBig") {
    
  }
}

TEST_CASE("MoveBooksToCheckout") {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();
  checkout.move_books_to_checkout();

  SUBCASE("CheckoutSize") {
    CHECK_EQ(checkout.checkout_counter().size(), 5);
  }

  SUBCASE("BookOrder") {
    std::vector<Book> books = {
        Book("Like the Animals", "", "9780895656926", 0.0),
        Book("131 Answer Key", "", "54782169785", 0.0),
        Book("Les Mis", "", "0140444300", 0.0),
        Book("Eat pray love", "", "9780399576775", 0.0),
        Book("Hunger Games", "", "9780545310581", 0.0),
    };
    std::vector<Book>::iterator iter = books.begin();

    std::queue<Book> copy = checkout.checkout_counter();
    while (!copy.empty() && iter != books.end()) {
      CHECK_EQ(copy.front(), *iter);
      copy.pop();
      iter++;
    }

    CHECK(copy.empty());
    CHECK_EQ(iter, books.end());
  }
}

TEST_CASE("DoCheckout") {
  Checkout checkout;
  checkout.shop_for_books();
  checkout.switch_carts();
  checkout.move_books_to_checkout();
  checkout.do_checkout();
  
  SUBCASE("AmountDue") {
    CHECK_EQ(checkout.amount_due(), doctest::Approx(238.48));
  }
}