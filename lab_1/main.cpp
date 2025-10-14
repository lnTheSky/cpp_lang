#include <iostream>
#include <fstream>
#include <iomanip>

#define MAX_LEN_NAME      50
#define MAX_LEN_AUTHOR    50
#define MAX_TRACKED_BOOKS 1000

#define SAVE_FILENAME  "books.txt"

using namespace std;

struct Book {
    char     name[MAX_LEN_NAME];
    char     author[MAX_LEN_AUTHOR];
    int      year;
    float    rating;
};

Book  books[MAX_TRACKED_BOOKS];
int   booksCount = 0;

void saveBookToFile(const char *filename, Book book) {
    ofstream fout(filename, ios::app);

    if (!fout)
    {
        cout << "An error occured while opening file!" << endl;
        return;
    }

    fout << book.name << " " << book.author << " " << book.year << " " << book.rating << endl;

    fout.close();
}

void loadBooksFromFile(const char *filename) {
    ifstream fin(filename);

    if (!fin)
        return;

    while (fin >> books[booksCount].name >> books[booksCount].author >> books[booksCount].year >> books[booksCount].rating)
    {
        booksCount++;
    }

    fin.close();
}

void showStats() {

    if (booksCount == 0) {
        cout << endl << "There's no tracked books" << endl;
        return;
    }

    float total_rating = 0;
    float average_rating;
    float highest_rating = 0;

    for (int i = 0; i < booksCount; i++) {
        if (books[i].rating > highest_rating) { highest_rating = books[i].rating; }
        total_rating += books[i].rating;
    }

    average_rating = total_rating / booksCount;

    cout << endl << "--- Statistics ---" << endl;
    cout << "Total tracked books: " << booksCount << endl;
    cout << "Average rating: " << average_rating << endl;
    cout << "Highest rating: " << highest_rating << endl;
}

void showBooks() {
    
    if (booksCount == 0) {
        cout << endl << "There's no tracked books" << endl;
        return;
    }

    // Table header
    cout << endl << "-------------- Tracked books --------------" << endl;
    cout << left << setw(12) << "Name" \
                 << setw(12) << "Author" \
                 << setw(12) << "Year" \
                 << setw(12) << "Rating" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 0; i < booksCount; i++) {
        cout << left << setw(12) << books[i].name \
                     << setw(12) << books[i].author \
                     << setw(12) << books[i].year \
                     << setw(12) << books[i].rating << endl;
    }
}

void addBook() {

    if (booksCount >= MAX_TRACKED_BOOKS) {
        cout << "Limit of tracked books exceeded!" << endl;
        return;
    }

    Book book;

    cout << "Enter book name: ";
    cin >> setw(MAX_LEN_NAME) >> book.name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter book author: ";
    cin >> setw(MAX_LEN_AUTHOR) >> book.author;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter book year: ";
    while (!(cin >> book.year)) {
        cout << "Wrong format! Try again" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.sync();
        cout << "Enter book year: ";
    }

    cout << "Enter rating (0-10): ";
    while (!(cin >> book.rating)) {
        cout << "Wrong format! Try again" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.sync();
        cout << "Enter rating (0-10): ";
    }

    books[booksCount++] = book;
    saveBookToFile(SAVE_FILENAME, book);

    cout << "Book has been added!" << endl;

}

void printMenu() {
    cout << endl << "=== Book tracker ===" << endl;
    cout << "1. Add book" << endl;
    cout << "2. Show all books" << endl;
    cout << "3. Show stats" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose option: ";
}

int main() {
    loadBooksFromFile(SAVE_FILENAME);

    int menu_option;

    do {
        printMenu();
        while (!(cin >> menu_option) || cin.get() != '\n') {
            cout << endl << "Wrong option! Try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.sync();
            cout << "Choose option: ";
        }

        switch (menu_option)
        {
        case 1:
            addBook();
            break;
        case 2:
            showBooks();
            break;
        case 3:
            showStats();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << endl << "There's no option: " << menu_option << endl;
            break;
        }

    } while (menu_option != 4);

    return 0;
}
