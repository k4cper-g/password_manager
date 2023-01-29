#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "manager.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    while (true) {
        cout << "Please load a file.\n" << endl;
        cout << "[From program directory] - type 'pd'" << endl;
        cout << "[Insert own directory] - type 'id'" << endl;
        cout << "[Exit] - type 'e'" << endl;
        string userInput;
        cin >> userInput;
        if (userInput == "pd") {
            while(true) {
                cout << "Please insert program directory." << endl;
                cin >> userInput;
                fs::path p(userInput);
                vector<fs::path> files;
                if (fs::is_directory(userInput)) {
                    for (auto const &file: fs::directory_iterator(p)) {
                        if (file.is_regular_file()) {
                            if (file.path().extension() == "" || file.path().extension() == ".txt") {
                                files.push_back(file.path());
                            }
                        }
                    }
                } else {
                    cout << "\nWrong directory!\n" << endl;
                    break;
                }
                cout << "Please choose the file you prefer." << endl;
                for (int i = 0; i < files.size(); i++) {
                    cout << files.at(i) << " - type " << files.at(i).filename() << endl;
                }
                cin >> userInput;
                int val = 0;
                for (fs::path p: files) {
                    if (userInput == p.filename()) {
                        val++;
                        cout << "Please insert admin password." << endl;
                        cin >> userInput;
                        manager m(absolute(p).string());
                        if (userInput == m.get_admin_pass()) {
                            m.user_interface();
                            return 0;
                        } else {
                            cout << "\nWrong password!\n" << endl;
                            break;
                        }
                    }
                }
                if(val == 0) {
                        cout << "Wrong file name!" << endl;
                    }
                }
            } else if (userInput == "id") {
            while (true) {
                cout << "Please insert own directory." << endl;
                cin >> userInput;
                fs::path path = userInput;
                if (path.is_absolute()) {
                    cout << "Please insert admin password." << endl;
                    cin >> userInput;
                    manager m(userInput);
                    if (userInput == m.get_admin_pass()) {
                        m.user_interface();
                        return 0;
                    } else {
                        cout << "\nWrong password!\n" << endl;
                        break;
                    }
                } else {
                    cout << "\nWrong directory!\n" << endl;
                    break;
                }
            }
        }else if(userInput == "e") {
            cout << "Goodbye!" << endl;
            break;
        } else {
                cout << "\nWrong command! Try again!\n" << endl;
        }
    }
}