#include "anagrames.hpp"
#include "word_toolkit.hpp"

/* Cost temporal: O(1) */
anagrames::anagrames() throw(error) : diccionari() {

}

/* Cost temporal: O(L.size()) */
anagrames::anagrames(const anagrames& A) throw(error) : diccionari(A)  {
  _taula = A._taula;
}

/* Cost temporal: O(L.size()) */
anagrames& anagrames::operator=(const anagrames& A) throw(error) {
    if (this != &A) {
      diccionari::operator=(A);
      _taula = A._taula;
    }

    return *this;
  }

/* Cost temporal: O(1) */
anagrames::~anagrames() throw() {

}

/** 
 * Cost temporal: O(h + p.size() + log n + n + m), on:
 *  - 'h' és l'alçada del TST en 'diccionari::insereix'.
 *  - 'p.size()' és la mida de la paraula 'p' per calcular el canònic.
 *  - 'log n' és el cost de la cerca dicotòmica.
 *  - 'n' és la mida de '_taula' en el pitjor cas per la inserció.
 *  - 'm' és la mida de la llista d'anagrames per la inserció en ella.
 */
void anagrames::insereix(const string& p) throw(error) {
  diccionari::insereix(p); // Cost: O(h), h = alçada del TST diccionari

  string canonic = word_toolkit::anagrama_canonic(p); // Cost: O(p.size())
  int idx = cerca_dicotomica(canonic); // Cost: O(log n)

  if (idx >= 0) {
    list<string>::iterator it = _taula[idx]._anagrames.begin();
    list<string>::iterator end = _taula[idx]._anagrames.end();

    while (it != end and *it < p) ++it;
    if (it == end or *it != p) {
      _taula[idx]._anagrames.insert(it, p); // Cost: O(n), n = mida de _taula[idx]._anagrames
    }
  } else {
    int pos = -(idx + 1);

    node nou;
    nou._canonic = canonic;
    nou._anagrames.push_back(p);

    _taula.insert(_taula.begin() + pos, nou); // Cost: O(n), n = mida de _taula
  }
}

/** 
 * Cost temporal: O(a.size() + log n + m), on:
 *  - 'a.size()' és el cost de verificar si 'a' és canònic.
 *  - 'log n' és el cost de la cerca dicotòmica a '_taula'.
 *  - 'm' és la mida de la llista '_anagrames' associada al node amb el canònic 'a'.
 */
void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
    if (not word_toolkit::es_canonic(a)) { // Cost: O(a.size())
      throw error(NoEsCanonic);
    }

    L.clear(); // Cost: O(L.size())

    int idx = cerca_dicotomica(a); // Cost: O(log(_taula.size()))
    if (0 <= idx) {
        L = _taula[idx]._anagrames; // Cost: O(L.size())
    }
}

/* Cost temporal: O(log n), on 'n' és la mida de '_taula', ja que s'utilitza una cerca dicotòmica. */
int anagrames::cerca_dicotomica(const string &a) const {
  int esq = 0;
  int dre = (int)_taula.size() - 1;

  int pos = 0;
  bool trobat = false;
  while (esq <= dre and (not trobat)) {
    int mig = (esq + dre)/2;

    if (_taula[mig]._canonic == a) {
      pos = mig;
      trobat = true;
    } else if (_taula[mig]._canonic < a) {
      esq = mig + 1;
    } else {
      dre = mig - 1;
    }
  }

  if (not trobat) pos = -(esq+1);

  return pos;
}