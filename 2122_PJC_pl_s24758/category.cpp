//
// Created by Kacper on 5/24/2022.
//

#include "category.h"
using namespace std;

category::category() = default;
category::category(string cat_name): cat_name(cat_name) {}
category::category(string cat_name, vector<password> cat_pass): cat_name(cat_name), cat_pass(cat_pass){}
std::ostream &operator<<(std::ostream & s, category c) {
    return s<< c.cat_name << endl;
}

void category::addPassword(password p) {
    cat_pass.push_back(p);
}
string category::getCatName() {
    return this->cat_name;
}
void category::setCatName(string cn) {
    this->cat_name = cn;
}
vector<password> category::getCatPass() {
    return this->cat_pass;
}
void category::setCatPass(vector<password> cp) {
    this->cat_pass = cp;
}