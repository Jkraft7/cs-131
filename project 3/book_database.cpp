

// Include necessary header files.
//
// Do not put anything else in this section, i.e. comments, classes,
// functions, etc. Only #include directives.

#include "book_database.hpp"

#include <fstream>
#include <string>
#include <iterator>

#include "book.hpp"



const std::string kDatabaseFilename = "database.txt";

// Return a reference to the one and only instance of the database
BookDatabase& BookDatabase::instance() {
  static BookDatabase theInstance(kDatabaseFilename);
  return theInstance;
}

BookDatabase::BookDatabase(const std::string& filename) {
  std::ifstream fin(filename, std::ios::binary);

  // The file contains Books separated by whitespace. A Book has 4 pieces of
  // data delimited with a comma. This exactly matches the previous assignment
  // as to how Books are read.
  //
  //       Field            Type            Notes
  //  1.   Book's ISBN      String          Unique identifier (primary key), always enclosed in double quotes
  //  2.   Book's Title     String          May contain spaces, always enclosed in double quotes
  //  3.   Book's Author    String          May contain spaces, always enclosed in double quotes
  //  4.   Book's Price     Floating Point  In dollars
  //
  //  Example:
  //    "0001062417",  "Early aircraft",                 "Maurice F. Allward", 65.65
  //    "0000255406",  "Shadow maker \"1st edition)\"",  "Rosemary Sullivan",   8.08
  //    "0000385264",  "Der Karawanenkardinal",          "Heinz Gstrein",      35.18
  //
  // NOTE: Double quotes within the string are escaped with the backslash
  // character.
  //
  
  
  
  // HINT:  Use your Book's extraction operator to read Books, don't reinvent
  // that here. Read books until end of file, pushing each book into the data
  // store as they are read.
  Book new_book;
  while(!fin.eof())
  {
    fin >> new_book;
    data_store.push_back(new_book);
  }
  


  // NOTE: The file is intentionally not explicitly closed. The file is closed
  // when fin goes out of scope - for whatever reason. More precisely, the
  // object `fin` is destroyed when it goes out of scope and the file is closed
  // in the destructor. See RAII.
}

// Implement the rest of the interface, including functions find
// (recursively) and size.
std::size_t BookDatabase::size() const
{
  return data_store.size();
}

Book* BookDatabase::find(const std::string& isbn)
{
  int index = 0;
  return find(isbn, index); 
}

Book* BookDatabase::find(const std::string& isbn, int& index)
{
  if(index == (data_store.size()-1))
    return nullptr;
  else if(data_store[index].isbn() == isbn)
  {
    return &(data_store[index]);
  }
  else
  {
    index++;
    return BookDatabase::find(isbn, index);
  }
}
// Programming note:  An O(n) operation, like searching an unsorted vector,
// would not generally be implemented recursively. The depth of recursion
// may be greater than the program's function call stack size. But for this
// programming exercise, getting familiar with recursion is a goal.
