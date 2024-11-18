#include "word_toolkit.hpp"

// Cost temporal: O(n), n = s.size()
bool word_toolkit::es_canonic(const string& s) throw() {
    bool canonic = true;
    int i = 1;

    while (canonic and i < (int)s.size()) {
        if (s[i] < s[i-1]) canonic = false;
        ++i;
    }

    return canonic;
}

// Cost temporal: O(n*log(n)), n = s.size()
string word_toolkit::anagrama_canonic(const string& s) throw() { 
    string canonic = s;
    sort(canonic.begin(), canonic.end());
    return canonic;
}

// Cost temporal: O(n^2), n = L.size()
char word_toolkit::mes_frequent(const string& excl, const list<string>& L) throw() {
    //cost constant  O(1)
    bool excl_array[26] = {false};
    for (int i = 0; i < excl.size(); ++i) {
        excl_array[i-'A'] = true; 
    }

    int freq_excl_array[26] = {0};
    iterador it = L.begin();
    while (it != L.end()) {
        string paraula = *it;
        for (int i = 0; i < paraula.size(); ++i) {
            char lletra = paraula[i];
            if (not excl_array[i-'A']) freq_excl_array[i-'A']++;
        }
    }

    int max_freq = 0;
    char c = '\0';
    for (int i = 0; i < freq_excl_array.size(); ++i) {
        if (max_freq < freq_excl_array[i]) {
            max_freq = freq_excl_array[i];
            c = i + 'A';
        } else if (max_freq == freq_excl_array[i]) {
            char d = i + 'A';
            if (d < c) c = d;
        }
    }

    return c;
}