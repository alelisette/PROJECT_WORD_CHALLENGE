#include "obte_paraules.hpp"
#include "iter_subset.hpp"
#include "word_toolkit.hpp"

/**
 * Pre: s es un string passat per referencia i subs es n conjunt valid o 
 * sigui tots els indexos es troben entre [1,s.size()]
 * Post: Retorna un string que correspon als caracters de s seleccionats segons els indexos en 
 * subs ordenats canonicament
 * Cost: O(k*logk) on k es la mida de subs
*/
static string obte_subset_canonic(const string& s, const subset& subs) {
  string subs_can = ""; 
  for (nat i = 0; i < subs.size(); ++i) subs_can += s[subs[i]-1];

  subs_can = word_toolkit::anagrama_canonic(subs_can);
  return subs_can;
}

/**
 * Pre: paraules esta ordenat alfabeticament
 * Post: insereix p en la posicio adequada per mantenir l'ordre alfabetic de les paraules i 
 * si p ja hi es dins la llista no fa res
 * Cost: O(n) on n es la mida de les paraules
*/
static void insereix(list<string>& paraules, const string& p) {
  list<string>::iterator it = paraules.begin();
  list<string>::iterator end = paraules.end();
  while (it != end and *it < p) ++it;
  
  if (it == end or *it != p) paraules.insert(it, p);
}

/**
 * Pre: k <= s.size() i k>=3
 * Post: paraules conte totes les paraules que son anagrames dels subconjunts de longitud k de s 
 * Cost:
     * O((C(n, k)) * (k log k + m * (n_p + 1))),
     * on:
     * - C(n, k) es el nombre de combinacions de n elements agafats de k en k.
     * - k es la longitud dels subconjunts.
     * - m es el nombre de paraules obtingudes por A.mateix_anagrama_canonic.
     * - n_p es la mida actual de la llista `paraules`.
     * 
     * Nota:
     * - Generar subconjunts de longitud k te coste O(C(n, k)) on C fa referencia a la combinatoria.
     * - Obtenir la representacio canonica de cada subconjunt te cost O(k log k).
     * - Inserir les paraules trobades en la llista 'paraules' te cost proporcional a la mida
     *   actual de 'paraules'.
  */
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

/**
 * Pre: s.size() >= 3
 * Post: paraules conte totes les paraules que son anagrames de tots els subconjunts
 * de longitud entre 3 i s.size() de s.
 * Cost: 
 *    O(Σ(k=3..n) [ C(n, k) * (k log k + m * (n_p + 1)) ]),
     * on:
     * - C(n, k) es el nombre de combinacions de n elements agafats de k en k.
     * - k es la longitud actual dins del rang [3, n], on n = s.size().
     * - m es el nombre de paraules obtingudes per A.mateix_anagrama_canonic.
     * - n_p es la mida actual de la llista `paraules`.
     * Nota:
     * Aquest cost pot arribar a ser exponencial en funció del valor de n degut al terme de combinatoria C(n,k).
*/
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