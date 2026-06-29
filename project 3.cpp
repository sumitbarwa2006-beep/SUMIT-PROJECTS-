#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string BOOK_FILE = "books.txt";
const string MEMBER_FILE = "members.txt";

class Book {
public:
    string bookId;
    string title;
    string author;
    int quantity;
    int available;

    Book(string id, string t, string a, int q) {
        bookId = id;
        title = t;
        author = a;
        quantity = q;
        available = q;
    }

    void showDetails() {
        cout << "ID: " << bookId << " | Title: " << title << " | Author: " << author << endl;
        cout << "Total Copies: " << quantity << " | Available: " << available << endl;
    }
};

class Member {
public:
    string memberId;
    string name;
    vector<string> borrowedBooks;

    Member(string id, string n) {
        memberId = id;
        name = n;
    }

    void showDetails() {
        cout << "ID: " << memberId << " | Name: " << name << endl;
        if (!borrowedBooks.empty()) {
            cout << "Borrowed Books:" << endl;
            for (string bookId : borrowedBooks) {
                cout << "- " << bookId << endl;
            }
        } else {
            cout << "No borrowed books" << endl;
        }
    }
};

class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Member> members;

public:
    LibraryManagementSystem() {
        loadData();
    }

    void addBook() {
        string bookId, title, author;
        int quantity;

        cout << "Enter Book ID: ";
        cin >> bookId;
        cout << "Enter Book Title: ";
        cin >> title;
        cout << "Enter Author Name: ";
        cin >> author;
        cout << "Enter Number of Copies: ";
        cin >> quantity;

        Book newBook(bookId, title, author, quantity);
        books.push_back(newBook);
        saveData();
        cout << "Book added successfully!\n" << endl;
    }

    void addMember() {
        string memberId, name;

        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Member Name: ";
        cin >> name;

        Member newMember(memberId, name);
        members.push_back(newMember);
        saveData();
        cout << "Member added successfully!\n" << endl;
    }

    void searchBooks() {
        string keyword;
        cout << "Enter title or author to search: ";
        cin >> keyword;

        bool found = false;
        for (Book &book : books) {
            string lowerTitle = book.title;
            string lowerAuthor = book.author;

            for (char &ch : lowerTitle) ch = tolower(ch);
            for (char &ch : lowerAuthor) ch = tolower(ch);

            string lowerKeyword = keyword;
            for (char &ch : lowerKeyword) ch = tolower(ch);

            if (lowerTitle.find(lowerKeyword) != string::npos || lowerAuthor.find(lowerKeyword) != string::npos) {
                book.showDetails();
                cout << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No matching books found.\n" << endl;
        }
    }

    void issueBook() {
        string memberId, bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Book ID: ";
        cin >> bookId;

        Member *member = getMember(memberId);
        Book *book = getBook(bookId);

        if (member == nullptr) {
            cout << "Member not found!\n" << endl;
            return;
        }

        if (book == nullptr) {
            cout << "Book not found!\n" << endl;
            return;
        }

        if (book->available <= 0) {
            cout << "Book is currently unavailable.\n" << endl;
            return;
        }

        book->available--;
        member->borrowedBooks.push_back(bookId);
        saveData();
        cout << "Book issued successfully!\n" << endl;
    }

    void returnBook() {
        string memberId, bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Book ID: ";
        cin >> bookId;

        Member *member = getMember(memberId);
        Book *book = getBook(bookId);

        if (member == nullptr) {
            cout << "Member not found!\n" << endl;
            return;
        }

        if (book == nullptr) {
            cout << "Book not found!\n" << endl;
            return;
        }

        bool found = false;
        for (int i = 0; i < member->borrowedBooks.size(); i++) {
            if (member->borrowedBooks[i] == bookId) {
                member->borrowedBooks.erase(member->borrowedBooks.begin() + i);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "This member did not borrow this book.\n" << endl;
            return;
        }

        book->available++;
        saveData();
        cout << "Book returned successfully!\n" << endl;
    }

    void showAllBooks() {
        if (books.empty()) {
            cout << "No books available.\n" << endl;
            return;
        }

        cout << "Books in Library:" << endl;
        for (Book &book : books) {
            book.showDetails();
            cout << endl;
        }
    }

    void showAllMembers() {
        if (members.empty()) {
            cout << "No members registered.\n" << endl;
            return;
        }

        cout << "Library Members:" << endl;
        for (Member &member : members) {
            member.showDetails();
            cout << endl;
        }
    }

    void run() {
        while (true) {
            cout << "===== Library Management System =====" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Add Member" << endl;
            cout << "3. Search Book" << endl;
            cout << "4. Issue Book" << endl;
            cout << "5. Return Book" << endl;
            cout << "6. Show All Books" << endl;
            cout << "7. Show All Members" << endl;
            cout << "8. Exit" << endl;
            cout << "===================================" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                addBook();
            } else if (choice == 2) {
                addMember();
            } else if (choice == 3) {
                searchBooks();
            } else if (choice == 4) {
                issueBook();
            } else if (choice == 5) {
                returnBook();
            } else if (choice == 6) {
                showAllBooks();
            } else if (choice == 7) {
                showAllMembers();
            } else if (choice == 8) {
                cout << "Goodbye!" << endl;
                break;
            } else {
                cout << "Invalid choice. Please try again.\n" << endl;
            }
        }
    }

private:
    void loadData() {
        loadBooks();
        loadMembers();
    }

    void loadBooks() {
        ifstream input(BOOK_FILE);
        if (!input) {
            return;
        }

        string line;
        while (getline(input, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string bookId, title, author, quantity, available;
            getline(ss, bookId, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, quantity, '|');
            getline(ss, available, '|');

            books.push_back(Book(bookId, title, author, stoi(quantity)));
            books.back().available = stoi(available);
        }
    }

    void loadMembers() {
        ifstream input(MEMBER_FILE);
        if (!input) {
            return;
        }

        string line;
        while (getline(input, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string part;
            vector<string> parts;
            while (getline(ss, part, '|')) {
                parts.push_back(part);
            }

            if (parts.empty()) {
                continue;
            }

            Member member(parts[0], parts[1]);
            for (size_t i = 2; i < parts.size(); i++) {
                member.borrowedBooks.push_back(parts[i]);
            }
            members.push_back(member);
        }
    }

    void saveData() {
        ofstream outBook(BOOK_FILE, ios::trunc);
        for (Book &book : books) {
            outBook << book.bookId << "|" << book.title << "|" << book.author << "|"
                    << book.quantity << "|" << book.available << "\n";
        }
        outBook.close();

        ofstream outMember(MEMBER_FILE, ios::trunc);
        for (Member &member : members) {
            outMember << member.memberId << "|" << member.name;
            for (string &bookId : member.borrowedBooks) {
                outMember << "|" << bookId;
            }
            outMember << "\n";
        }
        outMember.close();
    }

    Member *getMember(string id) {
        for (Member &member : members) {
            if (member.memberId == id) {
                return &member;
            }
        }
        return nullptr;
    }

    Book *getBook(string id) {
        for (Book &book : books) {
            if (book.bookId == id) {
                return &book;
            }
        }
        return nullptr;
    }
};

int main() {
    LibraryManagementSystem library;
    library.run();
    return 0;
}
