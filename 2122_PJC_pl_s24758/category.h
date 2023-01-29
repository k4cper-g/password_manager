//
// Created by Kacper on 5/24/2022.
//

#ifndef MENADZER_HASEL_CATEGORY_H
#define MENADZER_HASEL_CATEGORY_H

#include "password.h"


class category {
private:
    string cat_name;
    vector<password> cat_pass;
public:
    category();
    category(string cat_name);
    category(string cat_name, vector<password> cat_pass);
    friend std::ostream &operator<<(std::ostream & s, category p);

    void addPassword(password p);
    string getCatName();
    void setCatName(string cn);
    vector<password> getCatPass();
    void setCatPass(vector<password> cp);
};

#endif //MENADZER_HASEL_CATEGORY_H
