//
// Created by Kacper on 5/24/2022.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include<cstdlib>
#include<ctime>

#include "manager.h"

using namespace std;

manager::manager(string db): database(db), key("Qsv32bja!4fa"){
    add_category(category("Base"));
    if(this->isCiphered()) {
        cipher_data();
        this->inject_data();
        this->ciphered = false;
    }
    if(!this->isCiphered()) {
        this->inject_data();
        this->ciphered = false;
    }
}
void manager::print_art() {
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    cout <<" __      __   _                    _                   __     ___                              _   _   __  _ \n"
           " \\ \\    / /__| |__ ___ _ __  ___  | |_ ___   ___ __ _ / _|___| _ \\__ _ _______ __ _____ _ _ __| | / | /  \\| |\n"
           "  \\ \\/\\/ / -_) / _/ _ \\ '  \\/ -_) |  _/ _ \\ (_-</ _` |  _/ -_)  _/ _` (_-<_-< V  V / _ \\ '_/ _` | | || () |_|\n"
           "   \\_/\\_/\\___|_\\__\\___/_|_|_\\___|  \\__\\___/ /__/\\__,_|_| \\___|_| \\__,_/__/__/\\_/\\_/\\___/_| \\__,_| |_(_)__/(_)\n"
           "                                                                                                             " << endl;
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    cout << "\nThank you for using my program. Creator - Kacper Gadomski (s24758)" << endl;
}
void manager::user_interface() {
    string line = "-------------------";
    print_art();
    while(true) {
        string userInput;
        cout << "\n" << line << " Menu " << line << endl;
        cout << "Last deciphered: " << "[" << this->timestamp << "]\n" << endl;
        cout << "[View passwords] - 'vp'" << endl;
        cout << "[View categories] - 'vc'" << endl;
        cout << "[Options] - 'o'" << endl;
        cout << "[Exit] - 'e'" << endl;
        cin >> userInput;
        if(userInput == "vp") {
            while(true) {
                cout << line << endl;
                this->list_passwords();
                cout << line << endl;
                cout << "[Back] - b" << endl;
                cin >> userInput;
                if (userInput == "b") {
                    break;
                }else {
                    cout << "\nWrong command! Try again!\n" << endl;
                }
            }
        }else if(userInput == "vc") {
            while(true) {
                cout << line << endl;
                this->list_categories();
                cout << line << endl;
                cout << "[Back] - b" << endl;
                cin >> userInput;
                if (userInput == "b") {
                    break;
                }else {
                    cout << "\nWrong command! Try again!\n" << endl;
                }
            }
        } else if(userInput == "o") {
            while(true) {
                cout << line << " Options " << line << endl;
                cout << "[Search password] - type 'search'" << endl;
                cout << "[Sort passwords] - type 'sort'" << endl;
                cout << "[Add password] - type 'addP'" << endl;
                cout << "[Edit password] - type 'edit'" << endl;
                cout << "[Erase password] - type 'eraseP'" << endl;
                cout << "[Add category] - type 'addC'" << endl;
                cout << "[Erase category] - type 'eraseC'" << endl;
                cout << "[Change admin password] - type 'change'" << endl;
                cout << "[Cipher data] - type 'cipher'" << endl;
                cout << line << endl;
                cout << "[Back] - type 'b'" << endl;
                cin >> userInput;
                if (userInput == "search") {
                    while(true) {
                        cout << "Please select by what you will be searching." << endl;
                        cout << "[Name] - type 'n'" << endl;
                        cout << "[Category] - type 'c'" << endl;
                        cout << "[Site] - type 's'" << endl;
                        cout << "[Login] - type 'l'" << endl;
                        cout << line << endl;
                        cout << "[Back] - type 'b'" << endl;
                        cin >> userInput;
                        if (userInput == "n") {
                            string name;
                            cout << "Please type the name of your password." << endl;
                            cin >> name;
                            this->search_password("name", name);
                            cout << "[Back] - type 'b'" << endl;
                            cin >> userInput;
                            if(userInput == "b") {
                                break;
                            } else {
                                cout << "Wrong command! Try again!" << endl;
                            }
                        } else if (userInput == "c") {
                            string category;
                            cout << "Please type the name of your category." << endl;
                            cin >> category;
                            this->search_password("category", category);
                            cout << "[Back] - type 'b'" << endl;
                            cin >> userInput;
                            if(userInput == "b") {
                                break;
                            } else {
                                cout << "Wrong command! Try again!" << endl;
                            }
                        } else if (userInput == "s") {
                            string site;
                            cout << "Please type the name of your site." << endl;
                            cin >> site;
                            this->search_password("site", site);
                            cout << "[Back] - type 'b'" << endl;
                            cin >> userInput;
                            if(userInput == "b") {
                                break;
                            } else {
                                cout << "Wrong command! Try again!" << endl;
                            }
                        } else if (userInput == "l") {
                            string login;
                            cout << "Please type the name of your website login." << endl;
                            cin >> login;
                            this->search_password("login", login);
                            cout << "[Back] - type 'b'" << endl;
                            cin >> userInput;
                            if(userInput == "b") {
                                break;
                            } else {
                                cout << "Wrong command! Try again!" << endl;
                            }
                        } else if(userInput == "b") {
                            break;
                        } else {
                            cout << "\nWrong command! Try again!\n" << endl;
                        }
                    }
                } else if (userInput == "sort") {
                    this->sort_passwords();
                    cout << "Passwords sorted!" << endl;
                } else if (userInput == "addP") {
                    string name;
                    string pass;
                    string category;
                    string site;
                    string login;
                    cout << "Please type in the name of your password." << endl;
                    cin >> name;
                    while(true) {
                            cout << "Please type in your desired password." << endl;
                            cin >> pass;
                            bool repeat = false;
                            for (password p: passwords) {
                                if (p.getPass() == pass) {
                                    repeat = true;
                                }
                            }
                            if(repeat) {
                                cout << "This password was used before! Are you sure you want to use it?" << endl;
                                cout << "[Yes] - type 'y'" << endl;
                                cout << "[No] - type 'n'" << endl;
                                cin >> userInput;
                                if (userInput == "y") {
                                    break;
                                } else if(userInput == "n") {

                                } else {
                                    cout << "Wrong command! Try again!" << endl;
                                }
                            }
                            int rating = rate_password(pass);
                            cout << "Your rating is: " << rating << "/5" << endl;
                            if(rating > 3) {
                                break;
                            }
                            if(rating <= 3) {
                                cout << "Your password is weak! Do you want to use a randomly generated password?" << endl;
                                cout << "[Yes] - type 'y'" << endl;
                                cout << "[No] - type 'n'" << endl;
                                cin >> userInput;
                                if(userInput == "y") {
                                    bool lower = false;
                                    bool upper = false;
                                    bool number = false;
                                    bool special = false;
                                    int length;
                                    cout << "Do you want lowercase in your password?" << endl;
                                    cout << "[Yes] - type 'y'" << endl;
                                    cout << "[No] - type 'n'" << endl;
                                    cin >> userInput;
                                    if(userInput == "y") {
                                        lower = true;
                                    } else if(userInput == "n") {
                                        lower = false;
                                    } else {
                                        cout << "\nWrong command! Try again!\n" << endl;
                                    }
                                    cout << "Do you want uppercase in your password?" << endl;
                                    cout << "[Yes] - type 'y'" << endl;
                                    cout << "[No] - type 'n'" << endl;
                                    cin >> userInput;
                                    if(userInput == "y") {
                                        upper = true;
                                    } else if(userInput == "n") {
                                        upper = false;
                                    } else {
                                        cout << "\nWrong command! Try again!\n" << endl;
                                    }
                                    cout << "Do you want numbers in your password?" << endl;
                                    cout << "[Yes] - type 'y'" << endl;
                                    cout << "[No] - type 'n'" << endl;
                                    cin >> userInput;
                                    if(userInput == "y") {
                                        number = true;
                                    } else if(userInput == "n") {
                                        number = false;
                                    } else {
                                        cout << "\nWrong command! Try again!\n" << endl;
                                    }
                                    cout << "Do you want special characters in your password?" << endl;
                                    cout << "[Yes] - type 'y'" << endl;
                                    cout << "[No] - type 'n'" << endl;
                                    cin >> userInput;
                                    if(userInput == "y") {
                                        special = true;
                                    } else if(userInput == "n") {
                                        special = false;
                                    } else {
                                        cout << "\nWrong command! Try again!\n" << endl;
                                    }
                                    cout << "How long do you want your password to be?" << endl;
                                    cin >> length;
                                    string randomPass = generate_random_password(length,lower,upper,number,special);
                                    cout << "Your random password is: " << randomPass << endl;
                                    cout << "Do you want to use it?" << endl;
                                    cout << "[Yes] - type 'y'" << endl;
                                    cout << "[No] - type 'n'" << endl;
                                    cin >> userInput;
                                    if(userInput == "y") {
                                        pass = randomPass;
                                        break;
                                    } else if(userInput == "n") {

                                    } else {
                                        cout << "\nWrong command! Try again!\n" << endl;
                                    }

                                } else if(userInput == "n") {
                                    break;
                                } else {
                                    cout << "Wrong command! Try again!" << endl;
                                }
                            }
                    }
                    cout << "Please type in the category your password will fall into." << endl;
                    cin >> category;
                    if(!this->check_category(category)) {
                        cout << "This category does not exist." << endl;
                        break;
                    }
                    cout << "Do you want to add a website and login to your password?" << endl;
                    cout << "Yes - type 'y'" << endl;
                    cout << "No - type 'n'" << endl;
                    cin >> userInput;
                    if (userInput == "y") {
                        cout << "Please type in your site name." << endl;
                        cin >> site;
                        cout << "Please type in your login name." << endl;
                        cin >> login;
                        add_password(password(name, pass, category, site, login));
                        cout << "Password added!" << endl;
                    } else if (userInput == "n") {
                        add_password(password(name, pass, category));
                        cout << "Password added!" << endl;
                    } else {
                        cout << "Wrong command! Try again!" << endl;
                    }

                } else if (userInput == "edit") {
                    while(true) {
                        string name;
                        cout << "Please type the name of the password that you want to edit." << endl;
                        cin >> name;
                        cout << "[Edit name] - type 'n'" << endl;
                        cout << "[Edit category] - type 'c'" << endl;
                        cout << "[Edit password] - type 'p'" << endl;
                        cout << "[Edit site] - type 's'" << endl;
                        cout << "[Edit login] - type 'l'" << endl;
                        cout << line << endl;
                        cout << "[Back] - type 'b'" << endl;
                        cin >> userInput;
                        if (userInput == "n") {
                            cout << "Please enter a new name for your password." << endl;
                            cin >> userInput;
                            edit_password(name,userInput, "name");
                            cout << "Name changed!" << endl;
                            break;
                        } else if(userInput == "c") {
                            cout << "Please enter a new category for your password." << endl;
                            cin >> userInput;
                            edit_password(name,userInput, "category");
                            cout << "Category changed!" << endl;
                            break;
                        } else if(userInput == "p") {
                            cout << "Please enter a new password." << endl;
                            cin >> userInput;
                            edit_password(name, userInput, "password");
                            cout << "Password changed!" << endl;
                            break;
                        } else if(userInput == "s") {
                            cout << "Please enter a new site for your password." << endl;
                            cin >> userInput;
                            edit_password(name, userInput, "site");
                            cout << "Site changed!" << endl;
                            break;
                        } else if(userInput == "l") {
                            cout << "Please enter a new login for your password." << endl;
                            cin >> userInput;
                            edit_password(name, userInput, "login");
                            cout << "Login changed!" << endl;
                            break;
                        } else if(userInput == "b") {
                            break;
                        }
                    }
                } else if (userInput == "eraseP") {
                    cout << "Please type the name of the password you want to remove." << endl;
                    cin >> userInput;
                    if(!is_password_present(userInput)) {
                        cout << "\nThis password does not exist.\n" << endl;
                    }
                    if(is_password_present(userInput)) {
                        erase_password(userInput);
                        cout << "Password erased!" << endl;
                    }
                } else if (userInput == "addC") {
                    cout << "Please type the name of the category you want to add." << endl;
                    cin >> userInput;
                    this->add_category(category(userInput));
                    cout << "Category added!" << endl;
                } else if (userInput == "eraseC") {
                    while(true) {
                        cout << "Please type the name of the category you want to erase." << endl;
                        cin >> userInput;
                        if (check_category(userInput)) {
                            this->erase_category(userInput);
                            cout << "Category erased!" << endl;
                            break;
                        } else {
                            cout << "Category does not exist! Please try again.\n" << endl;
                        }
                    }
                } else if(userInput == "change") {

                    cout << "Please enter current admin password." << endl;
                    cin >> userInput;
                    if(userInput == adminPassword) {
                        cout << "Please enter your new admin password." << endl;
                        cin >> userInput;
                        this->set_admin_password_in_database(adminPassword, userInput);
                        this->set_admin_password(userInput);
                        cout << "Admin password changed!" << endl;
                    } else {
                        cout << "Wrong password!" << endl;
                    }
                } else if(userInput == "cipher") {
                    if(isCiphered()) {
                        cout << "Your data is [ciphered]" << endl;
                        cout << "Do you want to decipher your data?" << endl;
                        cout << "[Yes] - type 'y'" << endl;
                        cout << "[No] - type 'n'" << endl;
                        cin >> userInput;
                        if(userInput == "y") {
                            this->cipher_data();
                            string ts = "T:";
                            ts.append(getTime());
                            set_timestamp(getTime());
                            set_timestamp_in_database(ts);
                            this->ciphered = false;
                            cout << "Data deciphered!" << endl;
                            break;
                        } else if(userInput == "n") {
                            break;
                        } else {
                            cout << "\nWrong command! Try again!\n" << endl;
                        }
                    }
                    if(!isCiphered()) {
                        cout << "Your data is [deciphered]" << endl;
                        cout << "Do you want to cipher your data?" << endl;
                        cout << "[Yes] - type 'y'" << endl;
                        cout << "[No] - type 'n'" << endl;
                        cin >> userInput;
                        if(userInput == "y") {
                            this->cipher_data();
                            this->ciphered = true;
                            cout << "Data ciphered!" << endl;
                            break;
                        } else if(userInput == "n") {
                            break;
                        } else {
                            cout << "\nWrong command! Try again!\n" << endl;
                        }
                    }
                } else if (userInput == "b") {
                    break;
                } else {
                    cout << "Wrong command! Try again!\n" << endl;
                    break;
                }
            }
        } else if(userInput == "e") {
            string ts = "T:";
            ts.append(getTime());
            set_timestamp(getTime());
            set_timestamp_in_database(ts);
            if(!isCiphered()) {
                cipher_data();
            }
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "\nWrong command! Try again!\n" << endl;
        }
    }
}
string manager::getTime() {
    std::time_t result = std::time(nullptr);
    string time = std::asctime(std::localtime(&result));
    time.pop_back();
    return time;
}
bool manager::isCiphered() {
    fstream file(this->database);
    string line;
    int val = 0;
    while(getline(file, line)) {
        switch (val) {
            case 0:
                if(line.at(0) == 'A' && line.at(1) == ':') {
                    val++;
                }
                break;
            case 1:
                if(line.at(0) == 'N' && line.at(1) == ':') {
                    val++;
                }
                break;
            case 2:
                if(line.at(0) == 'C' && line.at(1) == ':') {
                    val++;
                }
                break;
            case 3:
                if(line.at(0) == 'P' && line.at(1) == ':') {
                    val++;
                }
                break;
            case 4:
                if(line.at(0) == 'S' && line.at(1) == ':') {
                    val++;
                }
                break;
            case 5:
                if(line.at(0) == 'L' && line.at(1) == ':') {
                    val++;
                }
        }
    }
    if(val == 6) {
        return false;
    }
    return true;
}
int manager::rate_password(string n) {
    bool lower = false;
    bool upper = false;
    bool number = false;
    bool special = false;
    bool isLong = false;
    int index = 0;
    if(n.size() >= 8) {
        isLong = true;
    }
    for(int i = 0; i < n.size(); i++) {
        if(islower(n.at(i))) {
            lower = true;
        }
        if(isupper(n.at(i))) {
            upper = true;
        }
        if(isdigit(n.at(i))) {
            number = true;
        }
        if(!isalpha(n.at(i)) && !isdigit(n.at(i))) {
            special = true;
        }
    }
    if(lower) {
        index++;
    }
    if(upper) {
        index++;
    }
    if(number) {
        index++;
    }
    if(special) {
        index++;
    }
    if(isLong) {
        index++;
    }
    return index;
}
string manager::generate_random_password(int charLength, bool lower, bool upper, bool number, bool special) {
    srand(time(NULL));
    vector<char> temp = {'0','1','2','3','4','5','6','7','8','9','!','@','#','$','%','^','&','*','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    vector<char> final;
    if(lower) {
        for(int i = 0; i < temp.size(); i++) {
            if(islower(temp.at(i)) && isNotInVector(final, temp.at(i))) {
                final.push_back(temp[i]);
            }
        }
    }
    if(upper) {
        for(int i = 0; i < temp.size(); i++) {
            if(isupper(temp.at(i)) && isNotInVector(final, temp.at(i))) {
                final.push_back(temp[i]);
            }
        }
    }
    if(number) {
        for(int i = 0; i < temp.size(); i++) {
            if(isdigit(temp.at(i)) && isNotInVector(final, temp.at(i))) {
                final.push_back(temp[i]);
            }
        }
    }
    if(special) {
        for(int i = 0; i < temp.size(); i++) {
            if(!isalpha(temp.at(i)) && !isdigit(temp.at(i)) && isNotInVector(final, temp.at(i))) {
                final.push_back(temp[i]);
            }
        }
    }
    string result = "";
    for (int i = 0; i<charLength; i++) {
        result = result + final[rand() % final.size()];
    }

    return result;
}
bool manager::isNotInVector(vector<char>t1, char a) {
    for(int i = 0; i < t1.size();i++) {
        if(t1.at(i) == a) {
            return false;
        }
    }
    return true;
}
bool manager::check_password_in_data(password p) {
    ifstream file(database);
    string line;
    string pass;
    vector<string> passNames;
    while(getline(file, line)) {
        if(line.at(0) == 'N' && line.at(1) == ':') {
            pass = line;
            pass.erase(pass.begin());
            pass.erase(pass.begin());
            passNames.push_back(pass);
        }
    }
    for(string s: passNames) {
        if(s == p.getName()) {
            return true;
        }
    }
    return false;
}
void manager::cipher_data() {
    const char *fileDir = this->database.c_str();
    string keyP = this->key;
    FILE *file = fopen(fileDir, "r+");
    stringstream result;
    if(file != NULL) {
        int length = keyP.size();
        int character;
        int xorChar;
        int mod = 0;

        do {
            if (mod >= length) {
                mod = 0;
            }
            character = fgetc(file);
            xorChar = character ^ keyP[mod];
            mod++;
            if (character != EOF) {
                result.put(xorChar);
            }
        } while(character != EOF);
    }
    ofstream output(fileDir);
    output << result.rdbuf();
}
bool manager::is_password_present(string n) {
    int val = 0;
    for(password p: passwords) {
        if(p.getName() == n) {
            val ++;
        }
    }
    if(val == 0) {
        return false;
    }
    return true;
}
void manager::add_password_to_data(password p) {
    ifstream file1(database);
    fstream file;
    if(check_password_in_data(p) && !is_empty(file1)) {
        cout << "Password already exists in the database." << endl;
    }
    if(!check_password_in_data(p) && !is_empty(file1)) {
        file.open(database, ios::app);
        file << "\nN:" << p.getName();
        file << "\nC:" << p.getCategory();
        file << "\nP:" << p.getPass();
        file << "\nS:" << p.getSite();
        file << "\nL:" << p.getLogin();
        file.close();
    } else if(is_empty(file1)) {
            file.open(database, ios::app);
            file << "N:" << p.getName();
            file << "\nC:" << p.getCategory();
            file << "\nP:" << p.getPass();
            file << "\nS:" << p.getSite();
            file << "\nL:" << p.getLogin();
            file.close();
    }
}
bool manager::is_empty(std::ifstream &pFile) {
        return pFile.peek() == std::ifstream::traits_type::eof();
}
void manager::set_timestamp_in_database(string t) {
    int lineCount = 0;
    string line;

    fstream toVector(database);
    vector<string> dataContent;
    while(getline(toVector, line)) {
        dataContent.push_back(line);
    }
    for(int i = 0; i < dataContent.size(); i++) {
        if(dataContent[i].at(0) == 'T' && dataContent[i].at(1) == ':'){
            dataContent[i] = t;
        }
    }
    ofstream file(database);
    for(auto& it: dataContent) {
        if(&it == &dataContent.back()) {
            file << it;
        } else {
            file << it << endl;
        }
    }
}
void manager::set_admin_password_in_database(string adminPass, string text) {
    int lineCount = 0;
    string line;

    fstream toVector(database);
    vector<string> dataContent;
    while(getline(toVector, line)) {
        dataContent.push_back(line);
    }
    for(int i = 0; i < dataContent.size(); i++) {
        if(dataContent[i].at(0) == 'A'){
            string admin = dataContent[i];
            admin.erase(admin.begin());
            admin.erase(admin.begin());
            if(admin == adminPass) {
                string newAdmin = "A:";
                newAdmin.append(text);
                dataContent[i] = newAdmin;
            }
        }
    }
    ofstream file(database);
    for(auto& it: dataContent) {
        if(&it == &dataContent.back()) {
            file << it;
        } else {
            file << it << endl;
        }
    }
}
void manager::add_password(password p) {
    bool identical = false;
    for(password pas: passwords) {
        if(p.getName() == pas.getName()) {
            identical = true;
        }
    }
    if(check_category(p.getCategory())) {
        if(!identical) {
            categories.at(find_category_index(p.getCategory())).addPassword(p);
            if(isCiphered()) {
                cipher_data();
                add_password_to_data(p);
                passwords.push_back(p);
                cipher_data();
            }
            if(!isCiphered()) {
                add_password_to_data(p);
                passwords.push_back(p);
            }
        }
    }
}
int manager::find_category_index(string category_name) {
    int a = 0;
    for(category c: categories) {
        if(category_name == c.getCatName()) {
            break;
        }
        a++;
    }
    return a;
}
void manager::erase_password(string n) {
    int index = 0;
    for(password p: passwords) {
        if(p.getName() == n) {
            erase_password_from_database(p);
            passwords.erase(passwords.begin()+index);
        }
        index++;
    }
}
void manager::erase_password_from_database(password p) {
    int lineCount = 0;
    string line;

    fstream toVector(database);
    vector<string> dataContent;
    while(getline(toVector, line)) {
        dataContent.push_back(line);
    }
    bool secure = false;
    int length = dataContent.size();
    for(int i = 0; i < length; i++) {
        if (!dataContent.at(i).empty()) {
            if (dataContent[i].at(0) == 'N' && dataContent[i].at(1) == ':') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if (tmp == p.getName()) {
                    for (int j = lineCount; j < lineCount + 5; j++) {
                        dataContent.erase(dataContent.begin() + lineCount);
                    }
                    secure = true;
                }
            }
            lineCount++;
        }
        if(secure) {
            break;
        }
    }
    ofstream file(database);
    for(auto& it: dataContent) {
        if(&it == &dataContent.back()) {
            file << it;
        } else {
            file << it << endl;
        }
    }
}
void manager::add_category(category c) {
    if(!check_category(c.getCatName())){
        categories.push_back(c);
    }
}
void manager::erase_category(string cn) {
    int index = 0;
    for(int i = 0; i < categories.size(); i++) {
        if(categories.at(i).getCatName() == cn) {
            vector<password> pass = categories[i].getCatPass();
            for(password p: pass) {
                this->erase_password(p.getName());
            }
            categories.erase(categories.begin()+index);
        }
        index++;
    }
}
void manager::sort_passwords() {
    sort(passwords.begin(), passwords.end());
}
void manager::list_categories() {
    show_vec_c(categories);
}
void manager::set_timestamp(string t) {
    this->timestamp = t;
}
void manager::inject_data() {
    fstream file1(database);
    string segment;
    char delimiter = '\n';
    vector<string> name;
    vector<string> pass;
    vector<string> category;
    vector<string> site;
    vector<string> login;

    while(getline(file1,segment,delimiter)) {
        if(segment.at(0) == 'T' && segment.at(1) == ':') {
            string empty;
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            if(segment == empty) {
                std::time_t result = std::time(nullptr);
                string ts = "T:";
                string time = std::asctime(std::localtime(&result));
                time.pop_back();
                ts.append(time);
                set_timestamp(time);
                set_timestamp_in_database(ts);
            }
            if(segment != empty) {
                std::time_t result = std::time(nullptr);
                string ts = "T:";
                ts.append(segment);
                set_timestamp(segment);
                set_timestamp_in_database(ts);
            }
        } else if(segment.at(0) == 'A') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            set_admin_password(segment);
        } else if (segment.at(0) == 'N') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            name.push_back(segment);
        } else if (segment.at(0) == 'C') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            category.push_back(segment);
        } else if (segment.at(0) == 'P') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            pass.push_back(segment);
        } else if (segment.at(0) == 'S') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            site.push_back(segment);
        } else if (segment.at(0) == 'L') {
            segment.erase(segment.begin());
            segment.erase(segment.begin());
            login.push_back(segment);
        }
    }
    fstream file2(database);
    int linecount = 0;
    while (getline(file2, segment)) {
            ++linecount;
    }
    for(string s: category) {
        class category a(s);
        add_category(a);
    }
    for(int i = 0; i < linecount/5; i++) {
        password p(name.at(i), pass.at(i), category.at(i), site.at(i), login.at(i));
        bool identical = false;
        for(password pas: passwords) {
            if(p.getName() == pas.getName()) {
                identical = true;
            }
        }
        if(check_category(p.getCategory())) {
            if(!identical) {
                categories.at(find_category_index(p.getCategory())).addPassword(p);
                passwords.push_back(p);
            } else {
                cout << "Please select a different name for your password." << endl;
            }
        } else {
            cout << "This category does not exist. Please create a new category, or use an existing one." << endl;
        }
    }
}
void manager::search_password(string search_by, string text) {
    if(search_by == "name") {
        password tmp;
        int val = 0;
        for(password p: passwords) {
           if(p.getName() == text) {
               tmp = p;
               val++;
           }
       }
        if(val != 0) {
            cout << "-----------------------\n" << endl;
            cout << "Searched by: " << search_by << "\nFound: " << val << "\nResults: \n" << endl;
            cout << tmp;
            cout << "-----------------------" << endl;
        } else {
            cout << "No results." << endl;
        }
    } else if(search_by == "category") {
        vector<password> tmp;
        int val = 0;
        for(password p: passwords) {
            if(p.getCategory() == text) {
                val++;
                tmp.push_back(p);
            }
        }
        if(val != 0) {
            cout << "-----------------------\n" << endl;
            cout << "Searched by: " << search_by << "\nFound: " << val << "\nResults: \n" << endl;
            show_vec_p(tmp);
            cout << "-----------------------" << endl;
        } else {
            cout << "No identical results." << endl;
        }
    } else if(search_by == "site") {
        vector<password> tmp;
        int val = 0;
        for(password p: passwords) {
            if(p.getSite() == text) {
                val++;
                tmp.push_back(p);
            }
        }
        if(val != 0) {
            cout << "-----------------------\n" << endl;
            cout << "Searched by: " << search_by << "\nFound: " << val << "\nResults: \n" << endl;
            show_vec_p(tmp);
            cout << "-----------------------" << endl;
        } else {
            cout << "No identical results." << endl;
        }
    } else if(search_by == "login") {
        vector<password> tmp;
        int val = 0;
        for(password p: passwords) {
            if(p.getLogin() == text) {
                val++;
                tmp.push_back(p);
            }
        }
        if(val != 0) {
            cout << "-----------------------\n" << endl;
            cout << "Searched by: " << search_by << "\nFound: " << val << "\nResults: \n" << endl;
            show_vec_p(tmp);
            cout << "-----------------------" << endl;
        } else {
            cout << "No identical results." << endl;
        }
    } else {
        cout << "Incorrect search method." << endl;
    }
}
void manager::show_vec_p(vector<password> v) {
    for(password p: v) {
        cout << p;
    }
}
void manager::edit_password(string p, string n, string by) {
    password copy;
    password tmp;
    for(password pass: passwords) {
        if(pass.getName() == p) {
            tmp = pass;
        }
    }
    if(by == "name") {
        for(int i = 0; i < passwords.size(); i++) {
            if(passwords[i].getName() == p) {
                copy.setPass(passwords[i].getPass());
                copy.setLogin(passwords[i].getLogin());
                copy.setSite(passwords[i].getSite());
                copy.setCategory(passwords[i].getCategory());
                copy.setName(n);
                passwords[i] = copy;
            }
        }
    } else if(by == "category") {
        for(int i = 0; i < passwords.size(); i++) {
            if(passwords[i].getName() == p) {
                copy.setPass(passwords[i].getPass());
                copy.setLogin(passwords[i].getLogin());
                copy.setSite(passwords[i].getSite());
                copy.setCategory(n);
                copy.setName(passwords[i].getName());
                passwords[i] = copy;
            }
        }
    } else if(by == "password") {
        for(int i = 0; i < passwords.size(); i++) {
            if(passwords[i].getName() == p) {
                copy.setPass(n);
                copy.setLogin(passwords[i].getLogin());
                copy.setSite(passwords[i].getSite());
                copy.setCategory(passwords[i].getCategory());
                copy.setName(passwords[i].getName());
                passwords[i] = copy;
            }
        }
    } else if(by == "site") {
        for(int i = 0; i < passwords.size(); i++) {
            if(passwords[i].getName() == p) {
                copy.setPass(passwords[i].getPass());
                copy.setLogin(passwords[i].getLogin());
                copy.setSite(n);
                copy.setCategory(passwords[i].getCategory());
                copy.setName(passwords[i].getName());
                passwords[i] = copy;
            }
        }
    } else if(by == "login") {
        for(int i = 0; i < passwords.size(); i++) {
            if(passwords[i].getName() == p) {
                copy.setPass(passwords[i].getPass());
                copy.setLogin(n);
                copy.setSite(passwords[i].getSite());
                copy.setCategory(passwords[i].getCategory());
                copy.setName(passwords[i].getName());
                passwords[i] = copy;
            }
        }
    }
    edit_password_in_database(tmp, n, by);
}
void manager::edit_password_in_database(password p, string e, string by) {
    int lineCount = 1;
    string line;
    string pass;

    fstream toVector(database);
    vector<string> dataContent;
    while(getline(toVector, line)) {
        dataContent.push_back(line);
    }
    if(by == "name") {
        for(int i = 0; i < dataContent.size(); i++) {
            if(dataContent[i].at(0) == 'N') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if(tmp == p.getName()) {
                    string final = "N:";
                    final.append(e);
                    dataContent[i] = final;
                }
            }
        }
    } else if(by == "category") {
        for(int i = 0; i < dataContent.size(); i++) {
            if(dataContent[i].at(0) == 'N') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if(tmp == p.getName()) {
                    string final = "C:";
                    final.append(e);
                    dataContent[i+1] = final;
                }
            }
        }
    } else if(by == "password") {
        for(int i = 0; i < dataContent.size(); i++) {
            if(dataContent[i].at(0) == 'N') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if(tmp == p.getName()) {
                    string final = "P:";
                    final.append(e);
                    dataContent[i+2] = final;
                }
            }
        }
    } else if(by == "site") {
        for(int i = 0; i < dataContent.size(); i++) {
            if(dataContent[i].at(0) == 'N') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if(tmp == p.getName()) {
                    string final = "S:";
                    final.append(e);
                    dataContent[i+3] = final;
                }
            }
        }
    } else if(by == "login") {
        for(int i = 0; i < dataContent.size(); i++) {
            if(dataContent[i].at(0) == 'N') {
                string tmp = dataContent[i];
                tmp.erase(tmp.begin());
                tmp.erase(tmp.begin());
                if(tmp == p.getName()) {
                    string final = "L:";
                    final.append(e);
                    dataContent[i+4] = final;
                }
            }
        }
    }
    ofstream file(database);
    for(auto& it: dataContent) {
        if(&it == &dataContent.back()) {
            file << it;
        } else {
            file << it << endl;
        }
    }
}
string manager::get_admin_pass() {
    return this->adminPassword;
}
void manager::set_admin_password(string adminPass) {
    this->adminPassword = adminPass;
}
void manager::list_passwords() {
    for(password p: passwords) {
        cout << p;
    }
    cout << "Password amount: " << passwords.size() << endl;
}
void manager::show_vec_c(vector<category> v) {
    int amount = 0;
    cout << "Categories: \n" << endl;
    for(category c: v) {
        cout << c;
        amount++;
    }
    cout << "\nCategory amount: " << amount << endl;

}
bool manager::check_category(string category_name) {
    bool a = false;
    for(category c: categories) {
        if(c.getCatName() == category_name) {
            a = true;
        }
    }
    return a;
}
