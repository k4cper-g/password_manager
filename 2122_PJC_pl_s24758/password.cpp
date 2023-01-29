//
// Created by Kacper on 5/24/2022.
//

#include "password.h"
#include "category.h"
using namespace std;

password::password(): name("template"), pass("template"), category("template"), site("template"), login("template"){}
password::password(string name, string pass, string category): name(name), pass(pass), category(category),site("empty"), login("empty"){
}
password::password(string name, string pass, string category, string site, string login): name(name), pass(pass), category(category), site(site), login(login){
}
std::ostream &operator<<(std::ostream & s, password p){
    return s<< "Name: " << p.name << "\nPassword: " << p.pass << "\nCategory: " << p.category << "\nSite: " << p.site << "\nLogin: " << p.login << "\n" << endl;
}
string password::getName() {
    return this->name;
}
void password::setName(string n) {
    this->name = n;
}
string password::getPass() {
    return this->pass;
}
void password::setPass(string p) {
    this->pass = p;
}
string password::getCategory() {
    return this->category;
}
void password::setCategory(string c) {
    this->category = c;
}
string password::getSite() {
    return this->site;
}
void password::setSite(string s) {
    this->site = s;
}
string password::getLogin() {
    return this->login;
}
void password::setLogin(string l) {
    this->login = l;
}
bool password::operator<(const password &p) const {
    return this->name < p.name;
}
