#include "book.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

//
// Constructors, Assignments, and Destructor
//

Book::Book(const std::string& title,
           const std::string& author,
           const std::string& isbn, 
           double price)
           : isbn_(isbn), title_(title),author_(author),price_(price) {}

Book::Book(const Book& other) = default;

Book& Book::operator=(const Book& rhs) = default;

// Destructor
Book::~Book() noexcept = default;

//
//  Accessors
//

const std::string& Book::isbn() const {
  return isbn_;
}

const std::string& Book::title() const {
 return title_;
}

const std::string& Book::author() const {
 return author_;
}

double Book::price() const {
 return price_;
}

std::string Book::isbn() {
 return isbn_;
}

std::string Book::title() {
 return title_;
}

std::string Book::author() {
 return author_;
}

//
// Modifiers
//

Book& Book::isbn(const std::string& new_isbn) {
  isbn_ = new_isbn;
  return *this;
}

Book& Book::title(const std::string& new_title) {
  title_ = new_title;
  return *this;
}

Book& Book::author(const std::string& new_author) {
  author_ = new_author;
  return *this;
}

Book& Book::price(double new_price) {
  price_ = new_price;
  return *this;
}

//
// Relational Operators
//

bool Book::operator==(const Book& rhs) const noexcept {
  // All attributes must be equal for the two books to be equal to the other. 
  //
  // This can be done in any order, so put the quickest and the most likely
  // to be different first.
  return (isbn_ == rhs.isbn_ && author_ == rhs.author_ && title_ == rhs.title_ && price_ == rhs.price_);
}

bool Book::operator!=(const Book& rhs) const noexcept {
  // Two books are unequal if any of their attributes are unequal.
  return !(*this == rhs);
}

bool Book::operator<(const Book& rhs) const noexcept {
  // Books are ordered (sorted) by ISBN, author, title, then price.
  if(isbn_ != rhs.isbn_)
    return isbn_ < rhs.isbn_;
  if(author_ != rhs.author_)
    return author_ < rhs.author_;
  if(title_ != rhs.title_)
    return title_ < rhs.title_;
  if(price_ != rhs.price_)
    return price_< rhs.price_;
  return false;
}

bool Book::operator<=(const Book& rhs) const noexcept {
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return *this < rhs || *this == rhs;
}

bool Book::operator>(const Book& rhs) const noexcept {
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return rhs < *this;
}

bool Book::operator>=(const Book& rhs) const noexcept {
  // Books are ordered (sorted) by ISBN, author, title, then price.
  return *this > rhs || *this == rhs;
}

//
// Insertion and Extraction Operators
//

std::istream & operator>>(std::istream& stream, Book& book) {
  
  // A lot can go wrong when reading from streams - no permission, wrong types,
  // end of file, etc. Minimal exception guarantee says there should be no side
  // affects if an error or exception occurs, so let's do our work in a local object
  // and move it into place at the end if all goes well.
  //
  // This function should be symmetrical with operator<< below.
  //
  // Assume fields are separated by commas and string attributes are enclosed
  // with double quotes.  For example:
  //    ISBN             | Title                 | Author             | Price
  //    -----------------+-----------------------+--------------------+-----
  //    "9789998287532",   "Over in the Meadow",   "Ezra Jack Keats",   91.11
  //
  //
  // Hint:  Use std::quoted to read and write quoted strings.  See
  //        1) https://en.cppreference.com/w/cpp/io/manip/quoted
  //        2) https://www.youtube.com/watch?v=Mu-GUZuU31A
  Book localItem;
  char delim = ',';
  stream >> std::quoted(localItem.isbn_) >> delim
  >> std::quoted(localItem.title_) >> delim 
  >> std::quoted(localItem.author_) >> delim
  >> localItem.price_;
  if(stream) book = std::move(localItem);
  return stream;

}

std::ostream& operator<<(std::ostream& stream, const Book& book) {
  char delim = ',';
  stream << std::quoted(book.isbn_) << delim
  << std::quoted(book.title_) << delim
  << std::quoted(book.author_) << delim
  << book.price_ << std::endl;
  return stream;
  // This function should be symmetrical with operator>> above.
}