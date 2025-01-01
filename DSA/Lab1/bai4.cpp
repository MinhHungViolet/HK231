#include <bits/stdc++.h>
using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    // Constructor: set the values of title, authors, and publishingYear to empty strings and 0
    Book()
    {
        title = new char[1];
        title[0] = '\0';
        authors = new char[1];
        authors[0] = '\0';
        publishingYear = 0;
    }

    // Constructor: set the values of title, authors, and publishingYear to the given values
    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
        this->publishingYear = publishingYear;
    }

    // Copy constructor: create a new Book object with the same values as the given Book object
    Book(const Book& book)
    {
        title = new char[strlen(book.title) + 1];
        strcpy(title, book.title);
        authors = new char[strlen(book.authors) + 1];
        strcpy(authors, book.authors);
        publishingYear = book.publishingYear;
    }

    // Destructor: free the memory allocated for the title and authors strings
    ~Book()
    {
        delete[] title;
        delete[] authors;
    }

    // Set and get title
    void setTitle(const char* title)
    {
        delete[] this->title;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    const char* getTitle() const
    {
        return title;
    }

    // Set and get authors
    void setAuthors(const char* authors)
    {
        delete[] this->authors;
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    const char* getAuthors() const
    {
        return authors;
    }

    // Set and get publishingYear
    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    int getPublishingYear() const
    {
        return publishingYear;
    }
};