//
// Created by Kacper on 5/24/2022.
//

#ifndef MENADZER_HASEL_MANAGER_H
#define MENADZER_HASEL_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "password.h"
#include "category.h"

using namespace std;

class manager {
private:
    vector<password> passwords;
    vector<category> categories;
    string adminPassword;
    string key;
    string database;
    string timestamp;
    bool ciphered;
public:
    manager(string db);

    //user commands

    /** Wyszukuje haslo za pomoca dwoch zmiennych podanych jako parametry.
     *
     * @param search_by - Zmienna string, okresla pod jaka kategoria szukamy hasla.
     * @param text - Zmienna string, okresla czego dokladnie szukamy.
     */
    void search_password(string search_by, string text);
    /** Sortuje hasla
     *
     */
    void sort_passwords();
    /** Dodaje haslo podane przez parametr jednoczesnie do "vector<password>passwords" oraz do bazy danych.
     *
     * @param p - Zmienna password, okresla haslo ktore chcemy dodac.
     */
    void add_password(password p);
    /** Edytuje haslo za pomoca trzech zmiennych jednoczesnie w "vector<password>passwords" jak i w bazie danych.
     *
     * @param p - Zmienna string okreslajaca nazwe hasla.
     * @param n - Zmienna string okreslajaca to co pojawi sie w miejscu w ktorym edytujemy haslo.
     * @param by - Zmienna string okreslajaca co chcemy dokladnie edytowac w hasle.
     */
    void edit_password(string p, string n,string by);
    /** Usuwa haslo za pomoca podanej zmiennej.
     *
     * @param n - Zmienna string okreslajaca nazwe hasla ktore chcemy usunac.
     */
    void erase_password(string n);
    /** Sprawdza czy podany znak znajduje sie w wektorze.
     *
     * @param t1 - Zmienna typu vector<char> ktora okresla wektor w ktorym chcemy sprawdzic znak.
     * @param a - Zmienna typu char ktora okresla znak ktory chcemy sprawdzic.
     * @return - Zwraca true lub false w zaleznosci od tego czy znak znajduje sie w wektorze czy nie.
     */
    bool isNotInVector(vector<char>t1, char a);
    /** Dodaje kategorie do "vector<category>categories".
     *
     * @param c - Zmienna string okreslajaca nazwe kategorii ktora chcemy dodac.
     */
    void add_category(category c);
    /** Usuwa kategorie poprzez podana zmienna.
     *
     * @param cn - Zmienna string okreslajaca nazwe kategorii ktora chcemy usunac.
     */
    void erase_category(string cn);

    //program commands

    /** Wypisuje wszystkie hasla z "vector<password>passwords" na konsole.
     *
     */
    void list_passwords();
    /** Wypisuje wszystkie kategorie z "vector<category>categories" na konsole.
     *
     */
    void list_categories();
    /** Ocenia haslo pod katem bezpieczenstwa na piecio-poziomowej skali.
     * Pierwszy punkt - Male litery.
     * Drugi punkt - Duze litery.
     * Trzeci punkt - Cyfry.
     * Czwarty punkt - Znaki specjalne.
     * Piaty punkt - Rozmiar hasla powyzej 8 znakow.
     *
     * @param n - Zmienna string ktora okresla nazwe ocenianego hasla.
     * @return - Zwraca zmienna int index ktora okresla ile punktow zdobylo haslo.
     */
    int rate_password(string n);
    /**
     *
     * @param charLength
     * @param upper
     * @param lower
     * @param number
     * @param special
     * @return
     */
    string generate_random_password(int charLength, bool upper, bool lower, bool number, bool special);
    /** Wyswietla hasla znajdujace sie w podanym wektorze.
     *
     * @param p - Zmienna vector<password> okreslajaca hasla ktore metoda bedzie listowac.
     */
    void show_vec_p(vector<password> p);
    /** Wyswietla kategorie znajdujace sie w podanym wektorze.
     *
     * @param v - Zmienna vector<category> okreslajaca kategorie ktore metoda bedzie listowac.
     */
    void show_vec_c(vector<category> v);
    /** Wstrzykuje dane z bazy danych do glownej klasy manager.
     *
     */
    void inject_data();
    /** Szyfruje dane za pomoca klucza przechowywanego w glownej klasie.
     *
     */
    void cipher_data();
    /** Dodaje haslo podane przez parametr do bazy danych.
     *
     * @param p - Zmienna password ktora jest dodawana do bazy danych.
     */
    void add_password_to_data(password p);
    /** Wskazuje czy baza danych jest zaszyfrowana.
     *
     * @return - Zwraca wartosc true lub false w zaleznosci od tego czy baza danych jest zaszyfrowana czy nie.
     */
    bool isCiphered();
    /** Usuwa haslo podane przez parametr z bazy danych.
     *
     * @param p - Zmienna password ktora jest usuwana z bazy danych.
     */
    void erase_password_from_database(password p);
    /** Edytuje haslo w bazie danych za pomoca trzech parametrow.
     *
     * @param p - Zmienna password ktora okresla jakie haslo chcemy edytowac.
     * @param by - Zmienna string ktora okresla poprzez jakie kryterium chcemy je edytowac.
     * @param e - Zmienna string ktora zawiera w sobie to co pojawi sie na miejscu edycji.
     */
    void edit_password_in_database(password p, string by, string e);
    /** Wyszukuje index z "vector<category> categories" na ktorym znajduje sie podana poprzez parametr kategoria.
     *
     * @param category_name - Zmienna string okreslajaca nazwe kategorii ktorej index chcemy odnalezc.
     * @return - Zwraca zmienna int ktora jest indexem na ktorym znajduje sie kategoria.
     */
    int find_category_index(string category_name);
    /** Sprawdza czy podana przez parametr kategoria znajduje sie w "vector<category>categories".
     *
     * @param category_name - Zmienna string ktora okresla nazwe kategorii ktora chcemy sprawdzic.
     * @return - Zwraca true lub false w zaleznosci od tego czy kategoria znajduje sie w "vector<category>categories".
     */
    bool check_category(string category_name);
    /** Sprawdza czy haslo podane przez parametr znajduje sie w bazie danych.
     *
     * @param p - Zmienna password ktora okresla haslo ktore chcemy sprawdzic.
     * @return - Zwraca true lub false w zaleznosci od tego czy haslo znajduje sie w bazie danych.
     */
    bool check_password_in_data(password p);
    /** Sprawdza czy haslo podane poprzez parametr znajduje sie w "vector<password>passwords".
     *
     * @param n - Zmienna string ktora okresla nazwe hasla ktore chcemy znalezc.
     * @return - Zwraca wartosc true lub false w zaleznosci od tego czy haslo sie znajduje czy nie.
     */
    bool is_password_present(string n);
    /** Sprawdza czy plik podany poprzez parametr jest pusty czy nie.
     *
     * @param pFile - Zmienna ifstream ktora okresla plik ktory chcemy sprawdzic.
     * @return - Zwraca wartosci true lub false w zaleznosci od tego czy jest pusty czy nie.
     */
    bool is_empty(std::ifstream& pFile);
    /** Pojemnik dla calego interfejsu uzytkownika. Znajduje sie w nim wiekszosc interakcji uzytkownika.
     *
     */
    void user_interface();
    /** Drukuje ASCII art.
     *
     */
    void print_art();
    /** Zwraca aktualny czas bez ostatniego znaku \n.
     *
     * @return - Zwraca zmienna string ktora jest aktualnym czasem.
     */
    string getTime();
    /** Ustawia timestamp glownej klasy manager za pomoca zmiennej.
     *
     * @param t - Zmienna typu string, okresla timestamp klasy.
     */
    void set_timestamp(string t);
    /** Ustawia timestamp glownej klasy manager w bazie danych za pomoca zmiennej.
     *
     * @param t - Zmienna typu string, okresla timestamp ktory bedzie wprowadzany do bazy danych.
     */
    void set_timestamp_in_database(string t);
    /** Ustawia haslo glowne uzytkownika ktore wymagane jest, aby korzystac z programu.
     *
     * @param adminPass - Zmienna typu string, okresla haslo glowne uzytkownika.
     */
    void set_admin_password(string adminPass);
    /** Ustawia haslo glowne uzytkownika w bazie danych.
     *
     * @param adminPass - Zmienna string ktore sluzy do wyszukania aktualnego hasla glownego.
     * @param text - Zmienna string ktora okresla nowe haslo glowne.
     */
    void set_admin_password_in_database(string adminPass, string text);
    /** Zwraca haslo glowne uzytkownika
     *
     * @return - Zwraca zmienna string ktora jest haslem glownym uzytkownika.
     */
    string get_admin_pass();
};


#endif //MENADZER_HASEL_MANAGER_H
