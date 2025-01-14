#include "diccionari.hpp"

/* Cost temporal: O(1) */
diccionari::diccionari() throw(error) {
    _arrel = nullptr;
    _numPal = 0;
}

/* Cost temporal: O(n), on n és el nombre total de nodes del diccionari original. */
diccionari::diccionari(const diccionari& D) throw(error) {
    _arrel = copia(D._arrel);
    _numPal = D._numPal;
}   

/* Cost temporal: O(n), on n és el nombre total de nodes del diccionari. */
diccionari& diccionari::operator=(const diccionari& D) throw(error) {
    if (this != &D) {
        node* aux = copia(D._arrel);
        esborra(_arrel);
        _arrel = aux;
        _numPal = D._numPal;
    }

    return *this;
}

/* Cost temporal: O(n), on n és el nombre de nodes al subarbre arrelat a arrel. */
diccionari::node* diccionari::copia(node* arrel) throw(error) {
    node* novaArrel = nullptr;
    
    if (arrel != nullptr) {
        novaArrel = new node;
        if (novaArrel == nullptr) throw error(0);

        novaArrel->_lletra = arrel->_lletra;
        novaArrel->_cen = copia(arrel->_cen);
        novaArrel->_esq = copia(arrel->_esq);
        novaArrel->_dre = copia(arrel->_dre);
    }

    return novaArrel;
}

/* Cost temporal: O(n), on n és el nombre total de nodes del diccionari. */
diccionari::~diccionari() throw() {
    esborra(_arrel);
}

/* Cost temporal: O(n), on n és el nombre de nodes al subarbre arrelat a arrel. */
void diccionari::esborra(node* arrel) {
    if (arrel != nullptr) {
        esborra(arrel->_cen);
        esborra(arrel->_esq);
        esborra(arrel->_dre);
        delete arrel;
    }
}

/* Cost temporal: O(n) on n és la mida de p+'#'
en el pitjor cas el cost sería O(27*n) ja que el nostre TST gestiona 27 símbols (26 lletres i #)
però 27 és una constant */
void diccionari::insereix(const string& p) throw(error) {
    if (p != "" and es_paraula_valida(p)) _arrel = insereix_aux(_arrel, p+'#', 0);
}

/* Cost temporal: O(n) on n és la mida de p */
bool diccionari::es_paraula_valida(const string& p) {
    bool valida = true;
    
    nat i = 0;
    while (valida and i < p.size()) {
        if (p[i] < 'A' or 'Z' < p[i]) valida = false;
        ++i;
    }

    return valida;
}

/* Cost temporal: O(n) on n és la mida de paraulaNova */
diccionari::node* diccionari::insereix_aux(node* arrel, const string& paraulaNova, nat index) throw(error) {
    if (arrel == nullptr) {
        arrel = new node;
        if (arrel == nullptr) throw error(0);
        
        arrel->_lletra = paraulaNova[index];
        arrel->_cen = nullptr;
        arrel->_esq = nullptr;
        arrel->_dre = nullptr;

        if (index < paraulaNova.size()-1) arrel->_cen = insereix_aux(arrel->_cen, paraulaNova, index+1);
        else ++_numPal;
    }
    else if (paraulaNova[index] < arrel->_lletra) arrel->_esq = insereix_aux(arrel->_esq, paraulaNova, index);
    else if (arrel->_lletra < paraulaNova[index]) arrel->_dre = insereix_aux(arrel->_dre, paraulaNova, index);
    else if (index < paraulaNova.size()-1) arrel->_cen = insereix_aux(arrel->_cen, paraulaNova, index+1);

    return arrel;
}

/* Cost temporal: O(n) on n és la mida de p */
string diccionari::prefix(const string& p) const throw(error) {
    string paraula;
    if (p != "") prefix_aux(_arrel, p+'#', 0, paraula);
    if (paraula != "") paraula.pop_back();
    return paraula;
}

/* Cost temporal: O(n) on n és la mida de p */
void diccionari::prefix_aux(node* arrel, const string& p, nat index, string& paraula) const throw(error) {
    if (arrel != nullptr) {     
        if (arrel->_lletra == p[index]) {
            paraula.push_back(arrel->_lletra);
            if (index < p.size()) prefix_aux(arrel->_cen, p, index+1, paraula); 
        }
        else if (p[index] < arrel->_lletra) prefix_aux(arrel->_esq, p, index, paraula); 
        else prefix_aux(arrel->_dre, p, index, paraula); 

        if (paraula == "" or paraula[paraula.size()-1] != '#') {
            if (paraula != "") paraula = paraula.substr(0, index);

            node* nodeAct = arrel;
            while (nodeAct->_esq != nullptr) nodeAct = nodeAct->_esq;
            if (nodeAct->_lletra == '#') paraula.push_back(nodeAct->_lletra); 
        }
    }
}

/* Cost temporal: O(p + m * s), on:
   - p és el nombre de nodes explorats al TST.
   - m és el nombre de paraules que satisfan el patró.
   - s és la longitud mitjana del subpatró en el vector 'q'. */
void diccionari::satisfan_patro(const vector<string>& q, list<string>& L) const throw(error) {
    string actual;
    satisfan_patro_aux(_arrel, q, 0, actual, L); 
}

/* Cost temporal: O(p + m * s), on:
   - p és el nombre de nodes al subarbre arrelat a arrel.
   - m és el nombre total de paraules que satisfan el patró.
   - s és la longitud mitjana del subpatró en el vector 'patro'.
   El cost mig depèn de l'esparsitat del patró dins del diccionari i de la distribució
   dels nodes en el TST. */
void diccionari::satisfan_patro_aux(node* arrel, const vector<string>& patro, nat pos, string& actual, list<string>& L) const throw(error) {
    if (arrel != nullptr) {
        satisfan_patro_aux(arrel->_esq, patro, pos, actual, L);

        if (pos < patro.size()) {
            string subpatro = patro[pos];

            if (subpatro.find(arrel->_lletra) != string::npos) { // Cost temporal de find: O(s), on s és la longitud del subpatró. 
                actual.push_back(arrel->_lletra);
                satisfan_patro_aux(arrel->_cen, patro, pos+1, actual, L);
                actual.pop_back();
            }
        }
        else if (arrel->_lletra == '#') L.push_back(actual);

        satisfan_patro_aux(arrel->_dre, patro, pos, actual, L);
    }
}

/* Cost temporal: O(n), on n és el nombre total de nodes al TST apuntat per _arrel. */
void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {
    llista_paraules_aux(_arrel, k, L, 0, "");
}

/* Cost temporal: O(n), on n és el nombre de nodes al subarbre arrelat a arrel. */
void diccionari::llista_paraules_aux(node* arrel, nat k, list<string>& L, nat nivell, string paraula) const throw(error) {
    if (arrel != nullptr) {
        llista_paraules_aux(arrel->_esq, k, L, nivell, paraula);

        if (arrel->_lletra != '#') llista_paraules_aux(arrel->_cen, k, L, nivell+1, paraula+arrel->_lletra);
        else if (k <= nivell) L.push_back(paraula);
        
        llista_paraules_aux(arrel->_dre, k, L, nivell, paraula);
    }
}

/* Cost temporal: O(1) */
nat diccionari::num_pal() const throw() {
    return _numPal;
}