#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <limits>
#include <cctype>

using namespace std;

class MobileNo {
private:
    string number;

public:
    void setNumber(const string& n) {
        number = n;
    }

    string getNumber() const {
        return number;
    }
};

class User {
private:
    string name;
    string email;
    string password;
    MobileNo mobileNo;

public:
    void setName(const string& n) {
        name = n;
    }

    void setEmail(const string& e) {
        email = e;
    }

    void setPassword(const string& p) {
        password = p;
    }

    void setMobileNo(const MobileNo& m) {
        mobileNo = m;
    }

    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    string getPassword() const {
        return password;
    }

    MobileNo getMobileNo() const {
        return mobileNo;
    }
};

class Validation {
public:
    bool isValidEmail(const string& email) const {
        const regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
        return regex_match(email, pattern);
    }

    bool isValidPassword(const string& password) const {
        if (password.length() < 8) {
            return false;
        }

        bool hasUpper = false;
        bool hasDigit = false;
        bool hasSpecial = false;

        for (char ch : password) {
            if (isupper(static_cast<unsigned char>(ch))) {
                hasUpper = true;
            } else if (isdigit(static_cast<unsigned char>(ch))) {
                hasDigit = true;
            } else if (!isalnum(static_cast<unsigned char>(ch))) {
                hasSpecial = true;
            }
        }

        return hasUpper && hasDigit && hasSpecial;
    }

    bool isValidPhoneNumber(const string& number) const {
        const regex pattern(R"(^[0-9]{10}$)");
        return regex_match(number, pattern);
    }
};

class Login {
public:
    bool authenticate(const vector<User>& users, const string& email, const string& password) const {
        for (const User& user : users) {
            if (user.getEmail() == email && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }
};

class RegistrationForm {
private:
    vector<User> users;
    Validation validation;
    Login login;

public:
    void showMenu() {
        cout << "\n===== Registration System =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
    }

    void registerUser() {
        User user;
        string name, email, password, phone;

        cout << "\n=== Registration Form ===\n";
        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter password: ";
        getline(cin, password);

        cout << "Enter mobile number: ";
        getline(cin, phone);

        if (!validation.isValidEmail(email)) {
            cout << "Invalid email format.\n";
            return;
        }

        if (!validation.isValidPassword(password)) {
            cout << "Password must be at least 8 characters long and include an uppercase letter, a digit, and a special character.\n";
            return;
        }

        if (!validation.isValidPhoneNumber(phone)) {
            cout << "Mobile number must contain exactly 10 digits.\n";
            return;
        }

        if (isEmailTaken(email)) {
            cout << "This email is already registered.\n";
            return;
        }

        MobileNo mobile;
        mobile.setNumber(phone);

        user.setName(name);
        user.setEmail(email);
        user.setPassword(password);
        user.setMobileNo(mobile);

        users.push_back(user);
        cout << "Registration successful!\n";
    }

    void loginUser() {
        string email, password;

        cout << "\n=== Login ===\n";
        cout << "Enter email: ";
        getline(cin, email);

        cout << "Enter password: ";
        getline(cin, password);

        if (login.authenticate(users, email, password)) {
            cout << "Login successful! Welcome back.\n";
        } else {
            cout << "Invalid email or password.\n";
        }
    }

private:
    bool isEmailTaken(const string& email) const {
        for (const User& user : users) {
            if (user.getEmail() == email) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    RegistrationForm form;
    int choice;

    do {
        form.showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            form.registerUser();
            break;
        case 2:
            form.loginUser();
            break;
        case 3:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}

