#include "word_toolkit.hpp"
#include <algorithm>

/* Cost temporal: O(n), n = s.size() */
bool word_toolkit::es_canonic(const string& s) throw() {
    bool canonic = true;
    int i = 1;

    while (canonic and i < (int)s.size()) {
        if (s[i] < s[i-1]) canonic = false;
        ++i;
    }

    return canonic;
}

/* Cost temporal: O(n*log(n)), n = s.size() */
string word_toolkit::anagrama_canonic(const string& s) throw() { 
    string canonic = s;
    sort(canonic.begin(), canonic.end());
    return canonic;
}

/* Cost temporal: O(m + n*l), m = excl.size(), n = L.size(), 
   l és la longitud mitjana de les paraules dins L. */
char word_toolkit::mes_frequent(const string& excl, const list<string>& L) throw() {
    bool excl_array[26] = {false};
    for (unsigned int i = 0; i < excl.size(); ++i) {
        excl_array[excl[i]-'A'] = true; 
    }

    int freq_excl_array[26] = {0};
    list<string>::const_iterator it = L.begin();
    while (it != L.end()) {
        string paraula = *it;
        for (unsigned int i = 0; i < paraula.size(); ++i) {
            unsigned int index_char = paraula[i]-'A';
            if (not excl_array[index_char]) ++freq_excl_array[index_char];
        }

        ++it;
    }

    int max_freq = 0;
    char c = '\0';
    for (unsigned int i = 0; i < 26; ++i) {
        if (max_freq < freq_excl_array[i]) {
            max_freq = freq_excl_array[i];
            c = i + 'A';
        } else if (max_freq == freq_excl_array[i] and c != '\0') {
            char d = i + 'A';
            if (d < c) c = d;
        }
    }

    return c;
}