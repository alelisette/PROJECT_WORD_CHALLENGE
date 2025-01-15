#include "anagrames.hpp"
#include "word_toolkit.hpp"

/* Cost temporal: O(1) */
anagrames::anagrames() throw(error) : diccionari() {

}

/* Cost temporal: O(n) on n és la mida de _taula */
anagrames::anagrames(const anagrames& A) throw(error) : diccionari(A)  {
  _taula = A._taula;
}

/* Cost temporal: O(n) on n és la mida de _taula */
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
 * Cost temporal: O(ps + log ts + max(tas, ts)), on:
 *  - 'ps' és la mida de p.
 *  - 'ts' és la mida de '_taula'.
 *  - 'tas' és la mida de la llista '_anagrames' associada al node amb el canònic 'canonic'.
 */
void anagrames::insereix(const string& p) throw(error) {
  diccionari::insereix(p); 

  string canonic = word_toolkit::anagrama_canonic(p); 
  int idx = cerca_dicotomica(canonic); 

  if (idx >= 0) {
    list<string>::iterator it = _taula[idx]._anagrames.begin();
    list<string>::iterator end = _taula[idx]._anagrames.end();

    while (it != end and *it < p) ++it;
    if (it == end or *it != p) {
      _taula[idx]._anagrames.insert(it, p); 
    }
  } else {
    int pos = -(idx + 1);

    node nou;
    nou._canonic = canonic;
    nou._anagrames.push_back(p);

    _taula.insert(_taula.begin() + pos, nou); 
  }
}

/** 
 * Cost temporal: O(as + ls + log n + m), on:
 *  - 'as' és la mida de a.
 *  - 'ls' és la mida que pot tenir L al principi.
 *  - 'n' és la mida de '_taula'.
 *  - 'm' és la mida de la llista '_anagrames' associada al node amb el canònic 'a'.
 */
void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
    if (not word_toolkit::es_canonic(a)) { 
      throw error(NoEsCanonic);
    }

    L.clear();

    int idx = cerca_dicotomica(a); 
    if (0 <= idx) {
        L = _taula[idx]._anagrames; 
    }
}

/* Cost temporal: O(log n), on 'n' és la mida de '_taula'. */
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