#include "Book.h"

int main() {
    Book book("Test title", "Mr. NoName", 1450, "650-543-12-10-1239");

    book.displayInfo();

    try {
        Book test_year("123", "123", 1000, "123");
    }
    catch (std::exception e) {
        std::cout << "Handled error: " << e.what() << std::endl;
    }
}