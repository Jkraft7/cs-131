#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <string>

#include "book.hpp"
#include "book_list.hpp"

bool BookList::containers_are_consistent() const {
  // If the sizes of the containers are not all equal, the containers are not
  // consistent.
  if (books_array_size_ != books_vector_.size()
      || books_array_size_ != books_dl_list_.size()
      || books_array_size_ !=  books_sl_list_size()) {
    return false;
  }

  // Element content and order must be equal to each other
  auto current_array_position = books_array_.cbegin();
  auto current_vector_position = books_vector_.cbegin();
  auto current_dl_list_position = books_dl_list_.cbegin();
  auto current_sl_list_position = books_sl_list_.cbegin();

  while (current_vector_position != books_vector_.cend()) {
    if (*current_array_position != *current_vector_position
        || *current_array_position != *current_dl_list_position
        || *current_array_position != *current_sl_list_position) {
      return false;
    }

    // Advance the iterators to the next element in unison
    ++current_array_position;
    ++current_vector_position;
    ++current_dl_list_position;
    ++current_sl_list_position;
  }

  return true;
}

std::size_t BookList::books_sl_list_size() const {
  ///////////////////////// TO-DO (1) //////////////////////////////
    // Some implementations of a singly-linked list maintain the size
    // (number of elements in the list). The std::forward_list class does not.
    // The size of the singly-linked list must be calculated on demand by
    // walking the list from beginning to end counting the number of elements
    // visited. The STL's std::distance() function does that, or you can write
    // your own loop.
  return std::distance(books_sl_list_.begin(),books_sl_list_.end());
  /////////////////////// END-TO-DO (1) ////////////////////////////
}

//
// Constructors, Assignments, and Destructor
//

BookList::BookList() = default;

BookList::BookList(const BookList& other) = default;

BookList::BookList(BookList&& other) = default;

BookList& BookList::operator=(const BookList& rhs) = default;

BookList& BookList::operator=(BookList&& rhs) = default;

BookList::~BookList() = default;

BookList::BookList(const std::initializer_list<Book>& init_list) {
  for (const Book& book : init_list) {
    insert(book, Position::BOTTOM);
  }

  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in initializer_list constructor");
  }
}

BookList& BookList::operator+=(const std::initializer_list<Book>& rhs) {
  ///////////////////////// TO-DO (2) //////////////////////////////
    // Concatenate the right hand side book list of books to this list by
    // repeatedly inserting at the bottom of this book list.
    //
    // The input type is a container of books accessible with iterators like
    // all the other containers. The constructor above gives an example. Use
    // BookList::insert() to insert at the bottom.
    for(const Book& book : rhs)
    {
      insert(book,Position::BOTTOM);
    }
    
  /////////////////////// END-TO-DO (2) ////////////////////////////

  // Verify the internal book list state is still consistent amongst the four containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in operator+= for initializer list");
  }
  return *this;
}

BookList& BookList::operator+=(const BookList& rhs) {
  ///////////////////////// TO-DO (3) //////////////////////////////
    // Concatenate the right hand side book list of books to this list by
    // repeatedly inserting at the bottom of this book list.
    //
    // All the rhs containers (array, vector, list, and forward_list) contain
    // the same information, so pick just one to traverse. Walk the container 
    // you picked, inserting its books to the bottom of this book list. Use
    // BookList::insert() to insert at the bottom.
    for(const Book& book : rhs.books_vector_)
        insert(book, Position::BOTTOM);
  /////////////////////// END-TO-DO (3) ////////////////////////////

  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in operator+= for BookList");
  }
  return *this;
}

//
// Queries
//

std::size_t BookList::size() const {
  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
      "Container consistency error in size");
  }

  ///////////////////////// TO-DO (4) //////////////////////////////
    // All the containers are the same size, so pick one and return the size of
    // that container.
    //
    // Since the forward_list has to calculate itssize on demand, stay away
    // from using that one.
  return books_vector_.size();
  /////////////////////// END-TO-DO (4) ////////////////////////////
}

std::size_t BookList::find(const Book& book) const {
  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in find");
  }

  ///////////////////////// TO-DO (5) //////////////////////////////
    // Locate the book in this book list and return the zero-based position of
    // that book. If the book does not exist, return the size of this book list
    // as an indicator the book does not exist.
    //
    // The book will be in the same position in all the containers
    // (array, vector, list, and forward_list) so pick just one of those to
    // search. The STL provides the find() function that is a perfect fit here,
    // but you may also write your own loop.
  auto iter = std::find(books_vector_.begin(),books_vector_.end(),book);
  if(iter != books_vector_.end())
  {
    int index = std::distance(books_vector_.begin(),iter);
    return index;
  }
  else
  {
    return books_vector_.size();
  }
  /////////////////////// END-TO-DO (5) ////////////////////////////
}

//
// Mutators
//

BookList& BookList::insert(const Book& book, Position position) {
  // Convert the TOP and BOTTOM enumerations to an offset and delegate the work.
  switch (position) {
    case Position::TOP: {
      insert(book, 0);
      break;
    }
    case Position::BOTTOM: {
      insert(book, size());
      break;
    }
  }
  return *this;
}

// Insert the new book at offset_from_top, which places it before the current
// book at that position.
BookList& BookList::insert(const Book& book, std::size_t offset_from_top) {
  // Validate offset parameter before attempting the insertion. As std::size_t
  // is an unsigned type, there is no need to check for negative offsets. And an
  // offset equal to the size of the list says to insert at the end (bottom) of
  // the list. Anything strictly greater than the current size is an error.
  if (offset_from_top > size()) {
    throw InvalidOffsetException(
        "Insertion position beyond end of current list size in insert");
  }
  //
  // Prevent duplicate entries
  //
  ///////////////////////// TO-DO (6) //////////////////////////////
    // Silently discard duplicate items from getting added to the book list.
    //
    // If the to-be-inserted book is already in the list, simply return.
  size_t isFound = find(book);
  if(isFound != books_vector_.size())
      return *this;
  /////////////////////// END-TO-DO (6) ////////////////////////////

  // Inserting into the book list means you insert the book into each of the
  // containers (array, vector, forward_list, and list).
  //
  // Because the data structure concept is different for each container, the
  // way a book gets inserted is a little different for each. You are to insert
  // the book into each container such that the ordering of all the containers
  // is the same. A check is made at the end of this function to verify the
  // contents of all four containers are indeed the same.

  //
  // Insert into array
  //

  {
    ///////////////////////// TO-DO (7) //////////////////////////////
      // Unlike the other containers, std::array has no insert() function, so
      // you have to write it yourself. Insert into the array by shifting all
      // the items at and after the insertion point (offset_from_top) to the
      // right, opening a gap in the array that can be populated with the given
      // book.
      //
      // Remember that arrays have fixed capacity and cannot grow, so make sure 
      // there is room in the array for another book before you start by
      // verifying books_array_size_ is less than books_array_.size(). If
      // not, throw a CapacityExceededException exception.
      //
      // Also remember that you must keep track of the number of valid books in
      // your array, so don't forget to adjust books_array_size_.
      //
    if (books_array_size_ >= books_array_.size()) {
      throw CapacityExceededException(
        "Capacity Exceeded Exception");
    }
    for(int i = books_array_size_;i > offset_from_top;i--)
    {
      books_array_[i] = books_array_[i-1];
    }
    books_array_[offset_from_top] = book;
    books_array_size_++;
  
  }  /////////////////////// END-TO-DO (7) ////////////////////////////
  
  //
  // Insert into vector
  //

  {
    ///////////////////////// TO-DO (8) //////////////////////////////
      // The vector STL container std::vector has an insert function, which can
      // be directly used here. But that function takes an iterator that points
      // to the book to insert before. You need to convert the zero-based
      // offset from the top to an iterator by advancing books_vector_.begin()
      // offset_from_top many times. The STL has a function called std::next() 
      // that does that, or you can use simple pointer arithmetic to calculate
      // it.
      //
      // Behind the scenes, std::vector::insert() shifts to the right
      // everything at and after the insertion point, just like you
      // did for the array above.
    auto iter2 = std::next(books_vector_.begin(),offset_from_top);
    books_vector_.insert(iter2,book);
    /////////////////////// END-TO-DO (8) ////////////////////////////
  }

  //
  // Insert into singly-linked list
  //

  {
    ///////////////////////// TO-DO (9) //////////////////////////////
      // The singly-linked list STL container std::forward_list has an insert
      // function, which can be directly used here. But that function inserts
      // AFTER the book pointed to, not before like the other containers. A
      // singly-linked list cannot look backwards, only forward. You need to
      // convert the zero-based offset from the top to an iterator by advancing
      // books_sl_list_.before_begin() offset_from_top many times. The STL has
      // a function called std::next() that does that, or you can write your own
      // loop.
    auto iter = books_sl_list_.before_begin();
    auto iter2 = std::next(iter,offset_from_top);
    books_sl_list_.insert_after(iter2,book);
    /////////////////////// END-TO-DO (9) ////////////////////////////
  }

  //
  // Insert into doubly-linked list
  //

  {
    ///////////////////////// TO-DO (10) //////////////////////////////
      // The doubly-linked list STL container std::list has an insert function,
      // which can be directly used here. But that function takes an iterator
      // that points to the book to insert before. You need to convert the
      // zero-based offset from the top to an iterator by advancing
      // books_dl_list_.begin() offset_from_top times. The STL has a function
      // called std::next() that does that, or you can write your own loop.
    auto iter = books_dl_list_.begin();
    auto iter2 = std::next(iter,offset_from_top);
    books_dl_list_.insert(iter2,book);
    /////////////////////// END-TO-DO (10) ////////////////////////////
  }

  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in insert");
  }
  return *this;
}

BookList& BookList::remove(const Book& book) {
  remove(find(book));
  return *this;
}

BookList& BookList::remove(std::size_t offset_from_top) {
  // Removing from the book list means you remove the book from each of the
  // containers (array, vector, list, and forward_list).
  //
  // Because the data structure concept is different for each container, the
  // way a book gets removed is a little different for each. You are to remove
  // the book from each container such that the ordering of all the containers
  // is the same. A check is made at the end of this function to verify the
  // contents of all four containers are indeed the same.

  // If offsetFromTop isn't a valid offset, no change occurs.
  if (offset_from_top >= size()) {
    return *this;
  }

  //
  // Remove from array
  //
  {
    ///////////////////////// TO-DO (11) //////////////////////////////
      // Close the hole created by shifting to the left everything at and after
      // the remove point.
      //
      // std::move() will be helpful, or write your own loop.  Also remember
      // that you must keep track of the number of valid books in your array,
      // so don't forget to adjust books_array_size_.
      //
      
      for(int i = offset_from_top; i < books_array_size_;++i)
      {
        books_array_[i] = books_array_[i+1];
      }
      books_array_size_--;
    /////////////////////// END-TO-DO (11) ////////////////////////////
  }

  //
  // Remove from vector
  //

  {
    ///////////////////////// TO-DO (12) //////////////////////////////
      // The vector STL container std::vector has an erase function, which can
      // be directly used here. But that function takes an iterator that points
      // to the book to be removed. You need to convert the zero-based offset
      // from the top to an iterator by advancing books_vector_.begin()
      // offset_from_top times. The STL has a function called std::next() that
      // does that, or you can use simple pointer arithmetic to calculate it.
      //
      // Behind the scenes, std::vector::erase() shifts to the left everything 
      // after the insertion point, just like you did for the array above.
      auto iter = books_vector_.begin();
      auto iter2 = std::next(iter,offset_from_top);
      books_vector_.erase(iter2);
      
    /////////////////////// END-TO-DO (12) ////////////////////////////
  }

  //
  // Remove from singly-linked list
  //

  {
    ///////////////////////// TO-DO (13) //////////////////////////////
      // The singly-linked list STL container std::forward_list has an erase
      // function, which can be directly used here. But that function erases
      // AFTER the book pointed to, not the one pointed to like the other
      // containers. A singly-linked list cannot look backwards, only forward.
      // You need to convert the zero-based offset from the top to an iterator
      // by advancing books_sl_list_.before_begin() offset_from_top many times.
      // The STL has a function called std::next() that does that, or you can
      // write your own loop.
     auto iter = books_sl_list_.before_begin();
     auto iter2 = std::next(iter,offset_from_top);
     books_sl_list_.erase_after(iter2);
    /////////////////////// END-TO-DO (13) ////////////////////////////
  }

  //
  // Remove from doubly-linked list
  //

  {
    ///////////////////////// TO-DO (14) //////////////////////////////
      // The doubly-linked list STL container std::list has an erase function,
      // which can be directly used here. But that function takes an iterator
      // that points to the book to remove. You need to convert the zero-based
      // offset from the top to an iterator by advancing books_dl_list_.begin()
      // offset_from_top many times. The STL has a function called std::next()
      // that does that, or you can write your own loop.
    auto iter = books_dl_list_.begin();
    auto iter2 = std::next(iter,offset_from_top);
    books_dl_list_.erase(iter2);
    /////////////////////// END-TO-DO (14) ////////////////////////////
  }

  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in remove");
  }
  return *this;
}

BookList& BookList::move_to_top(const Book& book) {
  ///////////////////////// TO-DO (15) //////////////////////////////
    // If the book exists, then remove and reinsert it. Else do nothing.
    //
    // Use BookList::find() to determine if the book exists in this book list.
    size_t exists = find(book);
    if(exists != books_vector_.size())
    {
      remove(book);
      insert(book,0);
    }
  /////////////////////// END-TO-DO (15) ////////////////////////////

  // Verify the internal book list state is still consistent amongst the four
  // containers.
  if (!containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in move_to_top");
  }
  return *this;
}

void BookList::swap(BookList& rhs) noexcept {
  if (this == &rhs) {
    return;
  }

  books_array_.swap(rhs.books_array_);
  books_vector_.swap(rhs.books_vector_);
  books_dl_list_.swap(rhs.books_dl_list_);
  books_sl_list_.swap(rhs.books_sl_list_);

  std::swap(books_array_size_, rhs.books_array_size_);
}

//
// Insertion and Extraction Operators
//

std::ostream& operator<<(std::ostream& stream, const BookList& book_list) {
  if (!book_list.containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in operator<<");
  }

  int count = 0;
  stream << book_list.size();
  for (auto&& book : book_list.books_sl_list_) {
    stream << '\n' << std::setw(5) << count++ << ":  " << book;
  }
  stream << '\n';
  return stream;
}

std::istream& operator>>(std::istream& stream, BookList& book_list) {
  if (!book_list.containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in operator>>");
  }
  std::string label_holder;
  size_t count;
  ///////////////////////// TO-DO (16) //////////////////////////////
    // Read in data from a stream and use it to fill in the data of a BookList
    // object. Create a function that will read the output created by the
    // ostream operator above into an object properly.
  Book book;
  BookList list;
  label_holder = ":  ";
  stream >> count;
  if(stream) 
  {
    for(int i = 0; i < count; i++)
    {
      stream >> label_holder >> book;
      list.insert(book,BookList::Position::BOTTOM);
    }
  }
  book_list = std::move(list);
  /////////////////////// END-TO-DO (16) ////////////////////////////
  return stream;
}

//
// Relational Operators
//

int BookList::compare(const BookList& other) const {
  if (!containers_are_consistent() || !other.containers_are_consistent()) {
    throw BookList::InvalidInternalStateException(
        "Container consistency error in compare");
  }

  ///////////////////////// TO-DO (17) //////////////////////////////
    // Compare this Booklist object with the other Booklist object. Return:
    // * a negative number if this Booklist object is less than the other 
    //   Booklist object,
    // * zero if this Booklist object is equal to the other Booklist object, and
    // * a positive number if this Booklist object is greater than the other
    //   Booklist object.
    //
    // Compare the size of the two Booklist objects first. If the sizes are
    // different, you have your answer: if size() < other.size() then return -1,
    // and so on.
    //
    // If the sizes are equal, then walk the lists from beginning to end
    // comparing the contents of the two books, one from this BookList and one
    // from the other BookList. The content of all the containers in a
    // BookList is the same - so pick one to walk. If the books are different,
    // you have your answer. If you get all the way to the end of the list and
    // found no books that are different, you have your answer: the lists are 
    // equal.
  if(size() < other.size())
    return -1;
  else if(size() > other.size())
    return 1;
  else
  {
    for(int i = 0; i < size();i++)
    {
      if(books_vector_[i] != other.books_vector_[i])
      {
        if(books_vector_[i] > other.books_vector_[i])
          return 1;
        else
          return -1;
      }
    }
    return 0;

  }
  /////////////////////// END-TO-DO (17) ////////////////////////////
}

bool operator==(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) == 0;
}

bool operator!=(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) != 0;
}

bool operator<(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) < 0;
}

bool operator<=(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) <= 0;
}

bool operator>(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) > 0;
}

bool operator>=(const BookList& lhs, const BookList& rhs) {
  return lhs.compare(rhs) >= 0;
}