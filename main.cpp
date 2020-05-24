#include <iostream>
#include <vector>

using namespace std;

class Book {
    string name;
    string author;
public:
    Book(const string name, const string author) {
        this->name = name;
        this->author = author;
    }

    const string &getName() const {
        return name;
    }

    const string &getAuthor() const {
        return author;
    }
};

class Library{
private:
    vector<const Book*> books;
public:
    void add_book(Book &book){
        books.push_back(&book);
    }

    int findBookByName(string name){
        size_t size = books.size();
        for (int i = 0; i < size; ++i){
            if ((books[i]->getName() == name)){
                return i;
            }
        }
        return -1;
    }

    int findBookByAuthor(string author){
        size_t size = books.size();
        for (int i = 0; i < size; ++i){
            if (books[i]->getAuthor() == author){
                return i;
            }
        }
        return -1;
    }

    Book* foundBook(int number){
        return (Book *)(books.at(number));
    }

    friend class Worker;
};

class Worker{
public:
//     Book* giveBook(string name, string author = "", Library* library) {
//        if (author == ""){
//            return giveBookByName(name, library);
//        } else {
//            return giveBookByAll(name, author, library);
//        }
//    }

    Book* giveBookByName(string name, Library *library){
        int findedBookByName = library->findBookByName(name);
        if (findedBookByName != -1){
            return (library->foundBook(findedBookByName));
        } else {
            throw invalid_argument("Can't find book by name");
        }
     }

    Book* giveBookByAll(string name, string author, Library *library){
        int findedBookByName = library->findBookByName(name);
        int findedBookByAuthor = library->findBookByAuthor(author);
        if ((findedBookByName != -1) && (findedBookByAuthor != -1) && (findedBookByAuthor == findedBookByName)){
            return (library->foundBook(findedBookByName));
        } else {
            throw invalid_argument("Can't find book by name and author");
        }
    }
};

int main() {
    Library library;
    Worker worker;
    Book book1("A", "b");
    Book book2("B", "c");
    library.add_book(book1);
    library.add_book(book2);
    try {
        cout << worker.giveBookByName("A", &library) << endl;
        cout << worker.giveBookByAll("A", "b", &library) << endl;
        cout << worker.giveBookByAll("D", "k", &library) << endl;
                cout << worker.giveBookByName("D", &library);
    } catch(invalid_argument a){
        cout << a.what() << endl;
    }
        return 0;
}