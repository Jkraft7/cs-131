#ifndef _book_database_hpp_
#define _book_database_hpp_



// Include necessary header files.
//
// Do not put anything else in this section, i.e. comments, classes,
// functions, etc.  Only #include directives.

#include <string>
#include <vector>
#include <iterator>
#include "book.hpp"


// BookDatabase is an in-memory datastore, mapping ISBN numbers to Books.
class BookDatabase {
 public:
  // Returns a reference to the one and only instance of the database.
  static BookDatabase& instance();

  // Returns a pointer to the book in the database with the given ISBN.
  //
  // If no book exists in the database with the given ISBN, returns nullptr.
  Book* find(const std::string& isbn);
  Book* find(const std::string& isbn, int& index);

  // Returns the number of books in the database.
  std::size_t size() const;                                                   

 private:
  // Constructs a BookDatabase using the data read from `filename`.
  //
  // The constructor is private to prevent more than one instance from
  // existing.
  BookDatabase(const std::string& filename);

  // Intentionally prohibit copies.
  BookDatabase(const BookDatabase& other) = delete;

  // Intentionally prohibit copy assignments.
  BookDatabase& operator=(const BookDatabase& rhs) = delete;


  
  // Private implementation details.
  //
  // Add any necessary private helper functions, member attributes, etc.
  std::vector<Book> data_store;
};

#endif