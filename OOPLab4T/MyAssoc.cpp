#include <iostream>
#include <string>

class Books {
    struct Node {
        std::string ID_book;
        std::string name;
        Node* next;

        Node(const std::string& e, const std::string& p) : ID_book(e), name(p), next(nullptr) {}
    };

    Node* head;
    int errorCode;

public:
    enum ErrorCodes {
        NO_ERROR = 0,
        EMAIL_NOT_FOUND
    };

    Books() : head(nullptr), errorCode(NO_ERROR) {}

    ~Books() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void createAssociations(const std::string& email, const std::string& phone) {
        Node* newNode = new Node(email, phone);
        newNode->next = head;
        head = newNode;
    }

    std::string operator[](const std::string& email) {
        Node* current = head;
        while (current != nullptr) {
            if (current->ID_book == email) {
                errorCode = NO_ERROR;
                return current->name;
            }
            current = current->next;
        }
        errorCode = EMAIL_NOT_FOUND;
        return "";
    }

    std::string operator()(const std::string& email) {
        return (*this)[email];
    }

    int getErrorCode() const {
        return errorCode;
    }

    friend std::ostream& operator<<(std::ostream& os, const Books& assoc) {
        Node* current = assoc.head;
        while (current != nullptr) {
            os << "Email: " << current->ID_book << ", Phone: " << current->name << std::endl;
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Books& assoc) {
        std::string email, phone;
        while (is >> email >> phone) {
            assoc.createAssociations(email, phone);
        }
        return is;
    }
};


int main() {
    Books books;

    books.createAssociations("biba@gmail.com", "0951234567");
    books.createAssociations("boba@gmail.com", "0501234567");

    std::cout << "Books:" << std::endl;
    std::cout << books << std::endl;

    std::string emailToFind = "boba@gmail.com";
    std::string phone = books[emailToFind];
    if (books.getErrorCode() == Books::NO_ERROR) {
        std::cout << "Phone for email " << emailToFind << ": " << phone << std::endl;
    }
    else {
        std::cout << "Email " << emailToFind << " not found!" << std::endl;
    }

    std::string emailToFind2 = "biba@gmail.com";
    std::string phone2 = books(emailToFind2);
    if (!phone2.empty()) {
        std::cout << "Phone for email " << emailToFind2 << ": " << phone2 << std::endl;
    }
    else {
        std::cout << "Email " << emailToFind << " not found!" << std::endl;
    }

    return 0;
}

