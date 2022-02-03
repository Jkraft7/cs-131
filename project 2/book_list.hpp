#ifndef _book_list_hpp_
#define _book_list_hpp_

#include <array>
#include <cstddef>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "book.hpp"

class BookList {
  //
  // Insertion and Extraction Operators
  //

  friend std::ostream& operator<<(
      std::ostream& stream, const BookList& book_list);

  friend std::istream& operator>>(std::istream& stream, BookList& book_list);

 public:
  //
  // Types and Exceptions
  //

  enum class Position {TOP, BOTTOM};

  // Thrown if internal data structures become inconsistent with each other.
  struct InvalidInternalStateException : std::domain_error {
    using domain_error::domain_error;
  };

  // Thrown if more books are inserted than will fit.
  struct CapacityExceededException : std::length_error {
    using length_error::length_error;
  };

  // Thrown if an attempt to insert beyond the current size is made.
  struct InvalidOffsetException : std::logic_error {
    using logic_error ::logic_error; 
  };

  //
  // Constructors, Assignments, and Destructor
  // 

  // This constructor constructs an empty book list.
  BookList();

  // The copy constructor constructs a book list as a copy of another book list.
  BookList(const BookList& other);

  // The move constructor constructs a book list by moving another book list.
  BookList(BookList&& other); 

  // The copy assignment operator assigns the book list a copy of another book list.
  BookList& operator=(const BookList& rhs);

  // The move assignment operator assigns the book list by moving another book list.
  BookList& operator=(BookList&& rhs);

  // This constructor constructs a book list from a list of books.
  BookList(const std::initializer_list<Book>& init_list);

  // Adds a list of books to this book list.
  BookList& operator+=(const std::initializer_list<Book>& rhs);

  // Adds the rhs list of books to this list.
  BookList& operator+=(const BookList& rhs);

  // The destructor.
  ~BookList();

  //
  // Queries
  //

  // Returns the number of books in this book list.
  std::size_t size() const;

  // Returns the (zero-based) offset from the top of the list for book.
  //
  // If the book is not in the list, returns size().
  std::size_t find(const Book& book) const;

  //
  // Mutators
  //

  // Adds the book to the book list in the specified position.
  //
  // If the book is already in the book list, the method does nothing.
  BookList& insert(const Book& book, Position position = Position::TOP);

  // Adds the book before the existing book at the specified offset.
  //
  // If the book is already in the book list, the method does nothing.
  BookList& insert(const Book& book, std::size_t offset_from_top);

  // Removes the book from the book list.
  //
  // If the book is not in the book list, the method does nothing.
  BookList& remove(const Book& book);

  // Removes the book at the offset.
  //
  // If the offset is past the size of the book list, the method does nothing.
  BookList& remove(std::size_t offset_from_top);

  // Locates the book, removes the book from its current location, and inserts
  // the book at the top of the book list.
  BookList& move_to_top(const Book& book);

  // Swaps the book list with the `rhs` book list.
  void swap(BookList& rhs) noexcept;

  //
  // Comparisons
  //

  // Returns a negative number if this book list is less than the other
  // book list, zero if this book list is equal to the other book list,
  // and a positive number if this book list is greater than the other
  // book list.
  int compare(const BookList& other) const;

 private:
  // Returns whether the four containers are mutually consistent with
  // each other.
  bool containers_are_consistent() const;

  // Returns the size of the std::forward_list, since it doesn't maintain
  // its own size.
  std::size_t books_sl_list_size() const;

  // The number of books in books_array.
  std::size_t books_array_size_ = 0;

  // The array container.
  std::array<Book, 11> books_array_;

  // The vector container.
  std::vector<Book> books_vector_;

  // The singly-linked list container.
  std::forward_list<Book> books_sl_list_;  

  // The doubly-linked list container.
  std::list<Book> books_dl_list_;
};

//
// Relational Operators
//

// Returns whether `lhs` and `rhs` are equal.
bool operator==(const BookList& lhs, const BookList& rhs);

// Returns whether `lhs` and `rhs` are not equal.
bool operator!=(const BookList& lhs, const BookList& rhs);

// Returns whether `lhs` is less than `rhs`.
bool operator<(const BookList& lhs, const BookList& rhs);

// Returns whether `lhs` is less than or equal to `rhs`.
bool operator<=(const BookList& lhs, const BookList& rhs);

// Returns whether `lhs` is greater than `rhs`.
bool operator>(const BookList& lhs, const BookList& rhs);

// Returns whether `lhs` is greater than or equal to `rhs`.
bool operator>=(const BookList& lhs, const BookList& rhs);

#endif