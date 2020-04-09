// UMT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>

using namespace std;

/*
Regula 1: lungimea parolei sa fie intre 6 si 20 de caractere
Regula 2: parola ssa contina cel putin o litera mica, o litara mare si un numar
Regula 3: Nu trebuie sa fie trei caractere identice consecutive

1. Problema lungimii, cand lungimea este mai micã de 6, trebuie sa adaugam lungime prin inserarea caracterelor, 
atunci cand lungimea depaseste 20, vrem ss stergem caractere.

2. Lipsa de caractere si numere: atunci cand ne lipsesc majuscule, minuscule si/sau numere, putem completa parola introducand caractere sau inlocuind caractere.

3. Repetarea caracterelor: insertia, stergerea sau inlocuirea pot rezolva problema caracterelor repetate, cum ar fi un sir „bbbbb”, putem inlocui caracterul din mujloc; 
sau inseram caractere de douã ori, introducem un caracter diferit fata de cel din sir dupa a doua a respectiv a patra a pozitie, sau putem folosi ?tergea.
Evident cea mai eficienta cale este inlocuirea caracterului din mijloc.

*/

int strong_password(std::string s) {
    /*
    Daca string-ul are lungimea mai mica sau egala ca 3 este nevoie de a insera cel putin 3 caractere( pentru a satisface regula 2 ), iar aceste 3 caractere vor fi alese astfel incat sa indeplinesca regula 2.
    Regula 3 poate fi incalcata doar in cazul in care string-ul are trei caractere, dar se va rezolva prin inserarea unui caracter in aceea secventa.
    */
    if (s.size() <= 3) 
        return 6 - s.size();

    bool lower_case = false;
    bool upper_case = false;
    bool digit = false;

    char character = s[0];
    int size = 0;

    int insert = 0;
    int delete_1 = 0;
    int delete_2 = 0;

    for (int i = 0; i < s.size(); i++) {

        // Primele coditii din cele trei if-uri le-am adaugat pentru reducerea numarului de scrieri in variabile.
        if (!lower_case && s[i] >= 'a' && s[i] <= 'z')
            lower_case = true;

        if (!upper_case && s[i] >= 'A' && s[i] <= 'Z')
            upper_case = true;

        if (!digit && s[i] >= '0' && s[i] <= '9')
            digit = true;

        if (s[i] == character) {
            size++;
        }
        else  {
            // Daca sirul de caractere identice s-a terminat verificam daca are lungimea mai mare sau egala ca trei.
            if (size / 3) {
                

                if (size % 3 == 0) {
                    delete_1 += 1;
                }
                if (size % 3 == 1) {
                    delete_2 += 1;
                }
                
                // Numaram cate grupuri consecutive de cate 3 sunt in secventa.
                insert += size / 3;

            }

            character = s[i];
            size = 1;
           
        }

    }

    if (size / 3) {

        if (size % 3 == 0) {
            delete_1 += 1;
        }
        if (size % 3 == 1) {
            delete_2 += 1;
        }
        insert += size / 3;
    }

    //Calcularea caracterelor care lipsesc pentru indeplinirea regulii 2.
    int total_missing = (lower_case ? 0 : 1) + (upper_case ? 0 : 1) + (digit ? 0 : 1);

    /*
    Cand lungimea parolei este mai micã de 6, etapele pentru indeplinirea primelor doua reguli, realizeaza indeplinirea implicita celei de a treia reguli.
    In acest caz numarul de caractere repetate variaza de la [3,5], daca exista trei caractere repetate.
    De exemplu, daca exista cinci caractere repetate, atunci operatiile de adaugare si inlocuire rezolva si problema de repetare („ aaaaa "->" aaVaa7 ")
    */
    if (s.size() < 6) {
        return max(6 - (int)s.size(), max(total_missing, insert) );
    }

    /*
    In acest caz incercam sa nu utilizam operatia insertie, deoarece acest lucru poate face ca lungimea sa depaseasca restrictiile.
    Datoritã analizei anterioare, înlocuirea caracterelor este cea mai eficientã solu?ie.
    */
    if (s.size() <= 20 && s.size() >= 6) {
        return max(total_missing, insert);
    }


    /* Cazul in care parola contine mai mult de 20 de caractere.

    In aceasta situatie lungimea depa?este limita, indiferent de modul in care inlocuiti caracterele, lungimea nu va fi redusa, 
    dar nu putem sterge caracterele aleator (poate sa nu garanteze pasii minimi), asa ca atunci cand rezolvam al treilea caz, trebuie sa luam in 
    considerare si primul caz. Un truc este folosit aici: daca numarul de caractere repetate k este mai mare sau egal cu 3, nu il stergem caractere pentru a ajunge la o secventa de lungime 2, 
    ci mai intai il stergem pe cel mai apropiat (3n +2), atunci daca k este exact divizibil cu 3, devene k-1, 
    daca k % 3 = 1, atunci devine k-2. Avantajul acestei metode este ca 3n + 2 caractere repetitive pot inlocui cel mai eficient m caractere pentru a elimina repetarea.
    */
    int del = s.size() - 20;

    if (del <= delete_1) {
        insert -= del;
    }

    else if (del - delete_1 <= 2 * delete_2) {
        insert -= delete_1 + (del - delete_2) / 2;
    }

    else {
        insert -= delete_1 + delete_2 + (del - delete_1 - 2 * delete_2) / 3;
    }

    return del + max(insert, total_missing);
  
}

int main()
{
    string password;

    while (true) {
        cout << "Type password ";
        cin >> password;
        cout <<"Var 1: " << strong_password(password) <<'\n';
    }
}
