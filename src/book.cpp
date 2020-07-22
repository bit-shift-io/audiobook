#include "book.h"

Book::Book()
{
    duration = 0;
}

bool Book::operator==(const Book& rhs) {
    if (directory == rhs.directory)
            return true;
    return false;
}
