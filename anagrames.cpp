#include "anagrames.hpp"
#include "word_toolkit.hpp"

anagrames::anagrames() throw(error) {
    diccionari();
}

anagrames::anagrames(const anagrames& A) throw(error) {

}

anagrames& anagrames::operator=(const anagrames& A) throw(error) {
    return *this;
}

anagrames::~anagrames() throw() {

}

void anagrames::insereix(const string& p) throw(error) {
    
}

void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
    if (not word_toolkit::es_canonic(a)) {
        error err(NoEsCanonic);
        throw err;
    }
    // L.clear();

    list<string> M;
    vector<string> patro(a.size());
    for (nat i = 0; i < a.size(); ++i) {
        string subpatro = "";
        for (nat j = 0; j < a.size(); ++j) subpatro += a[j];
        patro[i] = subpatro;
    }

    satisfan_patro(patro, M);
    for (list<int>::iterator it = M.begin(); it != M.end(); ++it) {
        if (word_toolkit::anagrama_canonic(*it) == a)  L.push_back(*it);
    }
}