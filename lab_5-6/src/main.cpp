#include "Library.h"

inline void showMenu() {
    std::cout << "=== LIBRARY ==="          << std::endl;
    std::cout << "1. Show all books"        << std::endl;
    std::cout << "2. Show all users"        << std::endl;
    std::cout << "3. Add new book"          << std::endl;
    std::cout << "4. Register user"         << std::endl;
    std::cout << "5. Borrow book to user"   << std::endl;
    std::cout << "6. Return book from user" << std::endl;
    std::cout << "7. Find book by ISBN"     << std::endl;
    std::cout << "8. Show user profile"     << std::endl;
    std::cout << "9. Save to file"          << std::endl;
    std::cout << "0. Exit"                  << std::endl;
}

inline int getChoice() {
    std::string input;
    int choice;
    bool ok = false;
    while (!ok) {
        std::cout << "Your choice: ";
        if (!std::getline(std::cin, input)) continue;
        try
        {
            choice = std::stoi(input);
            ok = true;
        }
        catch(...)
        {
            std::cout << "Incorrect input, try again!" << std::endl;
        }
    }
    return choice;
}

int main() {
    Library lib;

    try {
        lib = Library(DEFAULT_SAVE_PATH);
    }
    catch (const std::exception& e) {
        std::cout << "An errror occured while trying to load from file: " << e.what() << std::endl;
    }

    // Мейн ~~кун~~ луп
    int choice;
    while (true) {
        showMenu();
        choice = getChoice();

        switch (choice) {
        case 0:
            return 0;
        case 1:
            lib.displayAllBooks();
            break;
        case 2:
            lib.displayAllUsers();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            lib.saveToFile();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }
    }
    
}