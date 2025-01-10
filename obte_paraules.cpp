#include "obte_paraules.hpp"
#include "iter_subset.hpp"
#include "word_toolkit.hpp"

static string obte_subset_canonic(const string& s, const subset& subs) {
  string subs_can = ""; 
  for (nat i = 0; i < subs.size(); ++i) subs_can += s[subs[i]-1];

  subs_can = word_toolkit::anagrama_canonic(subs_can);
  return subs_can;
}

static void insereix(list<string>& paraules, const string& p) {
  list<string>::iterator it = paraules.begin();
  list<string>::iterator end = paraules.end();
  while (it != end and *it < p) ++it;
  
  if (it == end or *it != p) paraules.insert(it, p);
}

void obte_paraules::obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {
  if (k > s.size() or k < 3) {
    throw error(LongitudInvalida);
  }

  iter_subset itSub(s.size(), k);
  while (not itSub.end()) {
    string subs = obte_subset_canonic(s, *itSub);

    list<string> temp;
    A.mateix_anagrama_canonic(subs, temp);

    list<string>::iterator itTemp = temp.begin();
    list<string>::iterator endTemp = temp.end();
    while (itTemp != endTemp) {
      insereix(paraules, *itTemp);
      ++itTemp;
    }

    ++itSub;
  }
}

void obte_paraules::obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
  if (s.size() < 3) {
    throw error(LongitudInvalida);
  }

  for (nat k = 3; k <= s.size(); ++k) {
    list<string> paraulesK;
    obte_paraules(k, s, A, paraulesK);
    paraules.splice(paraules.end(), paraulesK);
  }
}