#ifndef _checkout_hpp_
#define _checkout_hpp_

#include <queue>
#include <stack>

#include "book.hpp"
#include "book_database.hpp"

// Checkout is a class that encapsulates the checkout process: adding books to
// a shopping cart, switching from a broken shopping cart to a working shopping
// cart, moving the books to the checkout counter, and being rung up by the
// cashier.
class Checkout {
 public:
  // 
  Checkout();

  // Adds a fixed collection of books to the shopping cart, making sure to keep
  // the heaviest books on the bottom.
  void shop_for_books();

  // Moves the books from the broken shopping cart to a working shopping cart,
  // being certain to not smash any books in the process.
  void switch_carts();

  // Moves the books from the working shopping cart to the checkout counter.
  void move_books_to_checkout();

  // Rings up the order, computing a total and printing a receipt.
  void do_checkout();

  // Returns the original shopping cart.
  //
  // Exposed for testing.
  std::stack<Book> my_cart() const;

  // Returns the working shopping cart.
  //
  // Exposed for testing.
  std::stack<Book> working_cart() const;

  // Returns the checkout counter.
  //
  // Exposed for testing.
  std::queue<Book> checkout_counter() const;

  // Returns the amount due for the books.
  //
  // Exposed for testing.
  double amount_due() const;

  // A (recursive) helper method to move books from a broken cart to a working
  // cart while respecting book ordering.
  //
  // NOTE: This is public for testing visibility.
  void carefully_move_books(
      std::size_t quantity, std::stack<Book>& broken_cart,
      std::stack<Book>& working_cart, std::stack<Book>& spare_cart);

 private:
  // The database of books and prices used during checkout.
  BookDatabase& book_database_;

  // The stack of books in the original shopping cart.
  std::stack<Book> my_cart_;

  // The stack of books in the working shopping cart.
  std::stack<Book> working_cart_;

  // The queue of books at the checkout counter.
  std::queue<Book> checkout_counter_;

  // The amount due for the books.
  double amount_due_;
};

#endif