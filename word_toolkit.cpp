#include "word_toolkit.hpp"

bool word_toolkit::es_canonic(const string& s) throw() {
    bool canonic = true;
    int i = 1;

    while (canonic and i < (int)s.size()) {
        if (s[i] < s[i-1]) canonic = false;
        ++i;
    }

    return canonic;
}