//
// Created by Kacper on 5/24/2022.
//

#ifndef MENADZER_HASEL_PASSWORD_H
#define MENADZER_HASEL_PASSWORD_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class password {
private:
    string name;
    string pass;
    string category;
    string site;
    string login;
public:
    password();
    password(string name, string pass, string category);
    password(string name, string pass, string category, string site, string login);
    friend std::ostream &operator<<(std::ostream & s, password p);
    bool operator<(const password &p) const;

    string getName();
    void setName(string n);
    string getPass();
    void setPass(string p);
    string getCategory();
    void setCategory(string c);
    string getSite();
    void setSite(string s);
    string getLogin();
    void setLogin(string l);
};


#endif //MENADZER_HASEL_PASSWORD_H
