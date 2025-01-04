#include "diccionari.hpp"
#include "word_toolkit.hpp"

diccionari::diccionari() throw(error) {
    _arrel = nullptr;
    _numPal = 0;
}

diccionari::diccionari(const diccionari& D) throw(error) {
    _arrel = copia(D._arrel);
}   

diccionari& diccionari::operator=(const diccionari& D) throw(error) {
    if (this != &D) {
        node* aux = copia(D._arrel);
        esborra(_arrel);
        _arrel = aux;
    }

    return *this;
}

diccionari::node* diccionari::copia(node* arrel) {
    node* novaArrel = nullptr;
    
    if (arrel != nullptr) {
        novaArrel = new node;
        novaArrel->_lletra = arrel->_lletra;
        novaArrel->_cen = copia(arrel->_cen);
        novaArrel->_esq = copia(arrel->_esq);
        novaArrel->_dre = copia(arrel->_dre);
    }

    return novaArrel;
}

diccionari::~diccionari() throw() {
    esborra(_arrel);
}

void diccionari::esborra(node* arrel) {
    if (arrel != nullptr) {
        esborra(arrel->_cen);
        esborra(arrel->_esq);
        esborra(arrel->_dre);
        delete arrel;
    }
}

void diccionari::insereix(const string& p) throw(error) {
    _arrel = insereix_aux(_arrel, p+'#', 0);
}

diccionari::node* diccionari::insereix_aux(node* arrel, const string& paraulaNova, nat index) throw(error) {
    if (index < paraulaNova.size()) {
        if (arrel == nullptr) {
            arrel = new node;
            arrel->_lletra = paraulaNova[index];
            arrel->_cen = nullptr;
            arrel->_esq = nullptr;
            arrel->_dre = nullptr;

            if (index < paraulaNova.size()-1) arrel->_cen = insereix_aux(arrel->_cen, paraulaNova, index+1);
            else ++_numPal; // Hem acabat d'inserir la paraula nova
        }
        else if (paraulaNova[index] < arrel->_lletra) arrel->_esq = insereix_aux(arrel->_esq, paraulaNova, index);
        else if (arrel->_lletra < paraulaNova[index]) arrel->_dre = insereix_aux(arrel->_dre, paraulaNova, index);
        else arrel->_cen = insereix_aux(arrel->_cen, paraulaNova, index+1);
    }

    return arrel;
}

string diccionari::prefix(const string& p) const throw(error) {
    string prefix = "";
    if (0 < p.size()) prefix = prefix_aux(_arrel, p+'#', 0);
    return prefix;
}

string diccionari::prefix_aux(node* arrel, const string& p, nat index) const throw(error) {
    string prefix = "";

    if (arrel != nullptr and p[index] != '#') {
        if (arrel->_lletra == p[index]) {
            prefix += arrel->_lletra;
            if (index < p.size()-1) prefix += prefix_aux(arrel->_cen, p, index+1);  
        }
        else if (p[index] < arrel->_lletra)  prefix = prefix_aux(arrel->_esq, p, index);
        else prefix = prefix_aux(arrel->_dre, p, index);
    }

    return prefix;
}
//EL COST DOMINANT SERA:
//O(n⋅klogk): Si el patrón tiene muchos subpatrones largos.
//O(m⋅log⁡k)O(m⋅logk): Si el árbol TST es grande y el patrón es corto.

//Cost: O(n⋅klogk+m⋅logk) on n: Longitud del patrón (número de posiciones), k: Longitud promedio de los subpatrones, m: Número de nodos en el TST
void diccionari::satisfan_patro(const vector<string>& q, list<string>& L) const throw(error) {
 
    // Crear una copia de `q` donde cada subpatrón estará ordenado
    vector<string> subpatro(q.size());
    for (unsigned int i = 0; i < q.size(); ++i) {
        subpatro[i] = word_toolkit::anagrama_canonic(q[i]); // Ordenar cada subpatrón con anagrama_canonic
    }

    string pactual; // Cadena temporal para construir palabras
    satisfan_patro_aux(_arrel, subpatro, 0, pactual, L); // Llamada auxiliar recursivo
}

//Cost: O(m⋅logk)
void diccionari::satisfan_patro_aux(node* arrel, const vector<string>& q, nat pos, string& actual, list<string>& L) const throw(error) {
    if (arrel == nullptr) return; // Caso base: nodo vacío

    // Recorrer el subárbol izquierdo
    satisfan_patro_aux(arrel->_esq, q, pos, actual, L);

    // Si estamos dentro de los límites del patrón
    if (pos < q.size()) {
        const string& subpatron = q[pos]; // Subpatrón correspondiente
        if (conte_lletra(subpatron, arrel->_lletra, 0, subpatron.size() - 1)) {
            actual += arrel->_lletra; // Añadir la letra a la palabra actual

            // Llamada recursiva al hijo central para la siguiente posición del patrón
            satisfan_patro_aux(arrel->_cen, q, pos + 1, actual, L);

            actual.pop_back(); // Retroceder: eliminar la última letra
        }
    } else {
        // Si hemos llegado al final del patrón, comprobar si estamos en el final de una palabra
        if (arrel->_lletra == '#') {
            L.push_back(actual); // Añadir la palabra completa a la lista de resultados
        }
    }

    // Recorrer el subárbol derecho
    satisfan_patro_aux(arrel->_dre, q, pos, actual, L);
}

//Cost: O(logk)
// Función auxiliar: Divide y vencerás para buscar una letra en un subpatrón ordenado
bool diccionari::conte_lletra(const string& subpatron, char letra, int inicio, int fin)  const {
    if (inicio > fin) return false; // Caso base: la letra no está en el rango

    int mig = (inicio + fin) / 2;

    if (subpatron[mig] == letra) {
        return true; // La letra coincide con el punto medio
    } else if (letra < subpatron[mig]) {
        return conte_lletra(subpatron, letra, inicio, mig - 1); // Buscar en la mitad izquierda
    } else {
        return conte_lletra(subpatron, letra, mig + 1, fin); // Buscar en la mitad derecha
    }
}


void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {
    llista_paraules_aux(_arrel, k, L, 0, "");
}

void diccionari::llista_paraules_aux(node* arrel, nat k, list<string>& L, nat nivell, string paraula) const throw(error) {
    if (arrel != nullptr) {
        llista_paraules_aux(_arrel->_esq, k, L, nivell, paraula);

        if (arrel->_lletra != '#') llista_paraules_aux(_arrel->_cen, k, L, nivell+1, paraula+arrel->_lletra);
        else if (k <= nivell) L.push_back(paraula);
        
        llista_paraules_aux(_arrel->_dre, k, L, nivell, paraula);
    }
}

nat diccionari::num_pal() const throw() {
    return _numPal;
}