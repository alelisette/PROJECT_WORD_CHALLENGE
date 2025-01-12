#include "obte_paraules.hpp"
#include "iter_subset.hpp"
#include "word_toolkit.hpp"

/**
 * Pre: s es un string passat per referencia i subs és un conjunt valid o 
 * sigui tots els indexos es troben entre [1,s.size()].
 * Post: Retorna substring que correspon als caracters de s seleccionats segons els indexos 
 * en subs. Com que subs i s estan ordenats, el substring també està ordenat alfabèticament.
 * Cost: O(k) on k es la mida de subs.
*/
static string obte_subset(const string& s, const subset& subs) {
  string substring = ""; 
  for (nat i = 0; i < subs.size(); ++i) substring += s[subs[i]-1];
  return substring; 
}

/**
 * Pre: k <= s.size() i k>=3
 * Post: paraules conte totes les paraules que son anagrames dels subconjunts de longitud k de s 
 * Cost:
     * O((C(n, k)) * (k + m + (p + m))),
     * on:
     * - C(n, k) es el nombre de combinacions de n elements agafats de k en k.
     * - k es la longitud dels subset.
     * - m es el nombre de paraules obtingudes por A.mateix_anagrama_canonic.
     * - p es la mida actual de la llista `paraules`.
     * 
     * Nota:
     * - Generar subconjunts de longitud k te coste O(C(n, k)) on C fa referencia a la combinatoria.
     * - Obtenir la representacio el substring de sCanonic a partir del subset té cost O(k).
     * - Com que temp i paraules són llistes ordenades, combinar els seus resultats es fa amb 
     * merge i això té cost O(p + m);
  */
void obte_paraules::obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {
  if (k > s.size() or k < 3) {
    throw error(LongitudInvalida);
  }

  string sCanonic = word_toolkit::anagrama_canonic(s);
  list<string> temp;
  iter_subset itSub(s.size(), k);
  while (not itSub.end()) {
    string subs = obte_subset(sCanonic, *itSub); 

    A.mateix_anagrama_canonic(subs, temp);
    paraules.merge(temp);

    ++itSub;
  }

  paraules.unique();
}

/**
 * Pre: s.size() >= 3
 * Post: paraules conte totes les paraules que son anagrames de tots els subconjunts
 * de longitud entre 3 i s.size() de s.
 * Cost: 
 *   * O(Σ(k=3..n) [C(n, k) * (k + m + p + m ]),
     * on:
     * - [ C(n, k) * (k + m + p + m ] és el cost de obte_paraules(k, s, A, paraulesK).
     * Nota:
     * Aquest cost pot arribar a ser exponencial en funció del valor de n degut al terme de combinatoria C(n,k).
*/
void obte_paraules::obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
  if (s.size() < 3) {
    throw error(LongitudInvalida);
  }

  list<string> paraulesK;
  for (nat k = 3; k <= s.size(); ++k) {
    obte_paraules(k, s, A, paraulesK);
    paraules.splice(paraules.end(), paraulesK);
  }
}