/* 
 * File:   Generics.h
 * Author: Hannes Ziegler
 *
 * Created on April 14, 2024, 11:02 AM
 * Porpose: WIP specification for all classes 
 */

#ifndef GENERICS_H
#define GENERICS_H

#include <iostream>
#include <cstring>
#include <type_traits>
#include <limits>

using namespace std;

inline void safeCStrNCpy(char* dest, string src, int max_len) {
    strncpy(dest, src.c_str(), max_len-1);
    dest[max_len-1] = '\0';
}

inline char getSingleChar() {
    char choice;
    cin.get(choice);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

template <typename T, typename enable_if<is_arithmetic<T>::value>::type* = nullptr>
void getNumeric(T& num) {
    cin >> num;
    while (cin.fail()) {
        cout << "Not a valid number, please try again\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> num;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

inline void safeGetLine(string& dest, unsigned int max_len) {
    while (true) {
        getline(cin, dest);
        if (dest.length() < max_len) break;
        else cout << "Input must be less than " << max_len-1 << " characters long.\n";
    }
}
inline void safeGetLine(string& dest, unsigned int min_len, unsigned int max_len) {
    while (true) {
        getline(cin, dest);
        if (dest.length() < max_len && dest.length() > min_len) break;
        else cout << "Input must be less than " << max_len-1 << " but greather thann " << min_len << " characters long.\n";
    }
}


#endif /* GENERICS_H */

