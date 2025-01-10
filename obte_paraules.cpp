#include "obte_paraules.hpp"
#include "iter_subset.hpp"
#include "word_toolkit.hpp"
#include "obte_paraules.hpp"
#include "iter_subset.hpp"
#include "word_toolkit.hpp"

// --- FUNCIONES AUXILIARES ---

// Dado s y un subset (p.ej. {1,3,5}), construye la subcadena y la ordena.
// Se elimina la línea 'tmp.reserve(...)'.
static string build_canonic_from_subset(const string& s, const subset& subs) {
  // Recolectamos letras en un string temporal
  string tmp; 
  for (nat i = 0; i < subs.size(); ++i) {
    // Recordar: subs[i] va de 1..n
    tmp.push_back( s[ subs[i] - 1 ] );
  }
  // Ordenamos para obtener su anagrama canónico
  return word_toolkit::anagrama_canonic(tmp);
}

// Inserta w en L de forma que L siga ordenada ascendentemente (alfabética),
// y no inserta nada si w ya existe.
static void insert_in_order_no_dup(list<string>& L, const string& w) {
  list<string>::iterator it = L.begin();
  list<string>::iterator end_it = L.end();
    
  // Avanzar mientras *it < w
  while (it != end_it && *it < w) {
    ++it;
  }
  // Si no hemos llegado al final y *it == w, no insertamos (duplicado).
  // Si it == end_it o *it > w, insertamos.
  if (it == end_it || *it != w) {
    L.insert(it, w);
  }
}

// --- IMPLEMENTACIONES PEDIDAS ---

/* Pre:  Cert
   Post: Retorna la llista de paraules que es poden formar usant k lletres
          de la paraula s. Llança error si k és major que la longitud de s o k < 3. */
void obte_paraules::obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {

  // 1) Comprobación
  if (k > s.size() || k < 3) {
    throw error(LongitudInvalida);
  }

  // 2) Lista global (en orden alfabético, sin duplicados)
  list<string> paraules_global;

  // 3) Generamos todos los subsets de tamaño k
  iter_subset it(s.size(), k);
  while (!it.end()) {
    // 3.1) Obtenemos el subset
    subset subs = *it;

    // 3.2) Construimos su anagrama canónico
    string can = build_canonic_from_subset(s, subs);

    // 3.3) Pedimos a anagrames la lista de palabras con ese canónico
    list<string> Ltemp;
    A.mateix_anagrama_canonic(can, Ltemp);
    // Ltemp ya está ordenada alfabéticamente

    // 3.4) Insertamos cada palabra de Ltemp en paraules_global
    list<string>::iterator itL = Ltemp.begin();
    list<string>::iterator itLEnd = Ltemp.end();
    while (itL != itLEnd) {
      insert_in_order_no_dup(paraules_global, *itL);
      ++itL;
    }

    // Avanzamos al siguiente subset
    ++it;
  }

  // 4) Copiamos la lista resultante a 'paraules'
  //    (ya está en orden alfabético y sin duplicados)
  paraules = paraules_global;
}

/* Pre:  Cert
   Post: Retorna la llista de paraules que es poden formar usant 3 o més lletres
          de la paraula s. Ordenades de menor a mayor longitud y, a igual longitud,
          en orden alfabético. Lanza error si s.size() < 3. */
void obte_paraules::obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
  // 1) Comprobamos que s tiene al menos 3 letras
  if (s.size() < 3) {
    throw error(LongitudInvalida);
  }

  // 2) Lista global en orden alfabético (luego la reordenaremos)
  list<string> paraules_global;

  // 3) Para cada k desde 3 hasta s.size()
  for (nat k = 3; k <= s.size(); ++k) {
    iter_subset it(s.size(), k);
    while (!it.end()) {
      subset subs = *it;

      // Construimos canónico
      string can = build_canonic_from_subset(s, subs);

      // Obtenemos las palabras con ese canónico
      list<string> Ltemp;
      A.mateix_anagrama_canonic(can, Ltemp);

      // Insertamos sin duplicados, en orden alfabético
      list<string>::iterator itL = Ltemp.begin();
      list<string>::iterator itLEnd = Ltemp.end();
      while (itL != itLEnd) {
        insert_in_order_no_dup(paraules_global, *itL);
        ++itL;
      }
      ++it;
    }
  }

  // 4) Reordenamos la lista final según (longitud, alfabético)
  paraules_global.sort(
    [](const string& a, const string& b) {
      if (a.size() != b.size()) return a.size() < b.size();
      return a < b;
    }
  );

  // 5) Retornamos
  paraules = paraules_global;
}


  // --- IMPLEMENTACIONES PEDIDAS ---

  /* Pre:  Cert
     Post: Retorna la llista de paraules que es poden formar usant k lletres
            de la paraula s. Llança error si k és major que la longitud de s o k < 3. */
//void obte_paraules::obte_paraules(nat k, const string& s, const anagrames& A, list<string>& paraules) throw(error) {


  /* Pre:  Cert
     Post: Retorna la llista de paraules que es poden formar usant 3 o més lletres
            de la paraula s. Ordenades de menor a mayor longitud y, a igual longitud,
            en orden alfabético. Lanza error si s.size() < 3. */
//void obte_paraules::obte_paraules(const string& s, const anagrames& A, list<string>& paraules) throw(error) {
