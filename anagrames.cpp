#include "anagrames.hpp"
#include "word_toolkit.hpp"
#include<algorithm>

anagrames::anagrames() throw(error) : diccionari() { // Llamada al constructor base: crea diccionari vacío

}

anagrames::anagrames(const anagrames& A) throw(error) : diccionari(A)  {
      ana_taula = A.ana_taula;
}

anagrames& anagrames::operator=(const anagrames& A) throw(error) {
    if (this != &A) {
        // Asignamos la parte base (diccionari)
        diccionari::operator=(A);
        // Copiamos la tabla de anagramas
        ana_taula = A.ana_taula;
    }
    return *this;
  }

anagrames::~anagrames() throw() {

}

void anagrames::insereix(const string& p) throw(error) {
      // 1) Intentamos insertar en el diccionari (clase base).
  //    Si p ya existía, diccionari la ignora sin efectos.
  //    Suponemos que diccionari::insereix no lanza error si p ya está.
  //    También asumimos que, si ya existe, no hacemos nada más.
  //
  //    Si hace falta, se podría comprobar si p ya está:
  //    if (prefix(p) == p) return; // ya está, no hacemos nada
  //
  //    Pero asumimos que diccionari::insereix controla duplicados.
  //
  //    Llamamos a la base siempre, para que si es nueva, la meta.
  diccionari::insereix(p);

  // 2) Averiguar el anagrama canónico de p
  string c = to_canonic(p);

  // 3) Buscar en an_table si c ya existe
  int idx = find_canonic(c);

  if (idx >= 0) {
    // Ya existe un registro con canonic = c.
    // Insertamos p en la lista de palabras, si no estaba.
    // Como la lista la mantenemos en orden ascendente, lo hacemos con inserción ordenada.
    list<string>& lw = ana_taula[idx].words;
    // Para no insertar duplicados, podríamos comprobar si ya está.
    // Sin embargo, como 'diccionari' ya impide la inserción doble de p,
    // es muy probable que no esté duplicada. Aun así, revisamos:
    auto it = lw.begin();
    auto endit = lw.end();
    while (it != endit && *it < p) ++it;
    // si it == endit o *it != p, insertamos
    if (it == endit || *it != p) {
      lw.insert(it, p);
    }
  } else {
    // No existe un nodo con c; creamos uno y lo insertamos en la posición adecuada.
    // idx es -(pos+1), donde pos es la posición de inserción
    int pos = -(idx + 1);
    node nuevo;
    nuevo.canonic = c;
    // La primera palabra de su lista es p
    nuevo.words.push_back(p);

    // Insertamos en an_table para mantener el orden.
    // Como an_table es un vector, hay que hacer insert con la posición calculada.
    ana_taula.insert(ana_taula.begin() + pos, nuevo);
  }
}

void anagrames::mateix_anagrama_canonic(const string& a, list<string>& L) const throw(error) {
        // 1) Comprobamos si 'a' está en orden ascendente.
    //    Según el enunciado, si no lo está, lanzamos error.
    if (!word_toolkit::es_canonic(a)) {
        // Lanzamos el error
        throw error(NoEsCanonic);
    }

    // 2) Buscar 'a' en nuestro vector an_table.
    int idx = find_canonic(a);

    // 3) Si no se encuentra, la lista L queda vacía (no hay palabras con ese canónico).
    //    Si sí se encuentra, devolvemos la lista de palabras en L.
    if (idx < 0) {
        // No hay anagrama canónico = a
        L.clear();  // Lista vacía
    } else {
        // an_table[idx].words está ya ordenada ascendentemente.
        // Simplemente copiamos sus elementos en L.
        L = ana_taula[idx].words;  
        // `L` queda en orden ascendente, tal como pide el enunciado.
    }
  
}

  // Método auxiliar: dada una palabra p, retorna su anagrama canónico
  // (ordena las letras de p alfabéticamente).
string anagrames::to_canonic(const string& p) {
    string c = p;
    sort(c.begin(), c.end());  // usa <algorithm>
    return c;
  }

  // Búsqueda binaria del string 'a' en an_table, que está ordenado por nodeAC.canonic.
  // Devuelve:
  //   - índice >= 0 si se ha encontrado 'a'
  //   - número negativo -(pos-1) si no se ha encontrado, donde 'pos' es
  //     la posición donde se debería insertar para mantener el orden.
  //     (convención típica de algunas funciones de búsqueda binaria)
  int anagrames::find_canonic(const string &a) const {
    int left = 0;
    int right = (int)ana_taula.size() - 1;
    while (left <= right) {
      int mid = (left + right)/2;
      if (ana_taula[mid].canonic == a) {
        return mid;
      } else if (ana_taula[mid].canonic < a) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    // Si no se encontró, left es la posición de inserción
    // Por convención de búsqueda binaria, devolvemos -(left+1)
    return -(left+1);
  }




