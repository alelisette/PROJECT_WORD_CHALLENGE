#include "word_toolkit.hpp"
#include <map>

// Cost temporal: O(n)
bool word_toolkit::es_canonic(const string& s) throw() {
    bool canonic = true;
    int i = 1;

    while (canonic and i < (int)s.size()) {
        if (s[i] < s[i-1]) canonic = false;
        ++i;
    }

    return canonic;
}

// Cost temporal: O(log(n))
string word_toolkit::anagrama_canonic(const string& s) throw() { 
    string canonic = s;
    sort(canonic.begin(), canonic.end()); // ? profe
    return canonic;
}


char mes_frequent(const string& excl, const list<string>& L) throw() {

}