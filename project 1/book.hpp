#ifndef _book_hpp_
#define _book_hpp_

#include <iostream>
#include <string>

// The Book class encapsulates basic information about a book that could be sold
// by a retailer such as Amazon or Barnes & Noble.
class Book {
  //
  // Insertion and Extraction Operators
  //

  friend std::ostream& operator<<(std::ostream& stream, const Book& book);
  friend std::istream& operator>>(std::istream& stream, Book& book);

 public:
  //
  // Constructors, Assignments, and Destructor
  //

  Book(const std::string& title = {},
       const std::string& author = {},
       const std::string& isbn = {},
       const double price = 0.0);

  Book& operator=(const Book& rhs);

  Book(const Book& other);

  ~Book() noexcept;

  //
  // Accessors
  //

  const std::string& isbn () const;
  const std::string& title () const;
  const std::string& author() const;
  double price () const;

  std::string isbn();
  std::string title();
  std::string author();

  //
  // Modifiers
  //

  Book& isbn (const std::string& new_isbn);
  Book& title (const std::string& new_title);
  Book& author(const std::string& new_author);
  Book& price (double new_price);

  //
  // Relational Operators
  //

  bool operator==(const Book& rhs) const noexcept;
  bool operator!=(const Book& rhs) const noexcept;
  bool operator<(const Book& rhs) const noexcept;
  bool operator<=(const Book& rhs) const noexcept;
  bool operator>(const Book& rhs) const noexcept;
  bool operator>=(const Book& rhs) const noexcept;

 private:
  // The 10 or 13 character international standard book number uniquely
  // identifying this book.
  //
  // Examples: "9790619213090" or "979010181X".
  std::string isbn_;

  // The name of the book.
  //
  // Example: "An Introduction to Programming with C++".
  std::string title_;

  // The book's author.
  //
  // Example: "Diane Zak".
  std::string author_;

  // The cost of the book in US dollars.
  //
  // Example: 31.99.
  double price_ = 0.0;
};

#endif