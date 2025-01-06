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

/* Cost temporal: O(n), on n és el nombre total de nodes del diccionari.
   Això inclou copiar el diccionari `D` i alliberar els recursos del diccionari original. */
diccionari& diccionari::operator=(const diccionari& D) throw(error) {
    if (this != &D) {
        node* aux = copia(D._arrel);
        esborra(_arrel);
        _arrel = aux;
        _numPal = D._numPal;
    }

    return *this;
}

/* Cost temporal: O(n), n = nombre de nodes al subarbre arrelat a arrel. */
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

/* Cost temporal: O(n), on n és el nombre total de nodes del diccionari.
   L'alliberament dels recursos recorre tots els nodes. */
diccionari::~diccionari() throw() {
    esborra(_arrel);
}

/* Cost temporal: O(n), n = nombre de nodes al subarbre arrelat a arrel. */
void diccionari::esborra(node* arrel) {
    if (arrel != nullptr) {
        esborra(arrel->_cen);
        esborra(arrel->_esq);
        esborra(arrel->_dre);
        delete arrel;
    }
}

/* Cost temporal: O(h), on h és l'alçada del TST.
   En el cas mitjà d'un TST equilibrat, h = O(log(n)).
   En el pitjor cas, h = O(n). */
void diccionari::insereix(const string& p) throw(error) {
    if (p != "") _arrel = insereix_aux(_arrel, p+'#', 0);
}

/* Cost temporal: O(h), on h és l'alçada del subarbre arrelat a arrel. 
   En un TST equilibrat, h = O(log(n)), on n és el nombre total de paraules al diccionari. */
diccionari::node* diccionari::insereix_aux(node* arrel, const string& paraulaNova, nat index) throw(error) {
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

    return arrel;
}

/* Cost temporal: O(h), on h és l'alçada del TST.
   En un TST equilibrat, h = O(log(n)), on n és el nombre de paraules al diccionari. 
   En el pitjor cas, si el TST està completament desequilibrat, h = O(n). */
string diccionari::prefix(const string& p) const throw(error) {
    string paraula = "";
    if (p != "") paraula = prefix_aux(_arrel, p+'#', 0);
    if (paraula != "") paraula.pop_back(); // Traiem el símbol # si cal
    return paraula;
}

/* Cost temporal: O(h), on h és l'alçada del subarbre arrelat a arrel. 
   En el cas mitjà d'un TST equilibrat, h = O(log(n)), on n és el nombre de paraules.
   En el pitjor cas, si el TST està completament desequilibrat, h = O(n). */
string diccionari::prefix_aux(node* arrel, const string& p, nat index) const throw(error) {
    string paraula = "";

    if (arrel != nullptr) {
        string sufix1 = "";
        string sufix2 = "";
        
        node* actual = arrel; // Mirem si hi ha una paraula sencera a aquest nivell
        while (actual->_esq != nullptr) actual = actual->_esq;
        if (actual->_lletra == '#') sufix1 += actual->_lletra;

        if (arrel->_lletra == p[index]) {
            sufix2 = arrel->_lletra;
            if (index < p.size()) sufix2 += prefix_aux(arrel->_cen, p, index+1); 
        }
        else if (p[index] < arrel->_lletra) sufix2 = prefix_aux(arrel->_esq, p, index);
        else sufix2 = prefix_aux(arrel->_dre, p, index);

        paraula = sufix1;
        if (sufix2 != "" and sufix2[sufix2.size()-1] == '#') paraula = sufix2;
    }

    return paraula;
}

/* Cost temporal: O(p + m * s), on:
   - p és el nombre de nodes explorats al TST.
   - m és el nombre de paraules que satisfan el patró.
   - s és la longitud mitjana del subpatró en el vector 'q'. */
void diccionari::satisfan_patro(const vector<string>& q, list<string>& L) const throw(error) {
    string actual = ""; // String temporal per construir paraules
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
                actual += arrel->_lletra;
                satisfan_patro_aux(arrel->_cen, patro, pos+1, actual, L);
                actual.pop_back();
            }
        }
        else if (arrel->_lletra == '#') L.push_back(actual);

        satisfan_patro_aux(arrel->_dre, patro, pos, actual, L);
    }
}

/* Cost temporal: O(n), on n és el nombre total de nodes al TST.
   Això es deu al fet que es recorre tot l'arbre per generar la llista de paraules amb longitud >= k. */
void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {
    llista_paraules_aux(_arrel, k, L, 0, "");
}

/* Cost temporal: O(p), on p és el nombre de nodes al subarbre arrelat a arrel.
   Si hi ha poques paraules amb longitud >= k, el cost serà proper a O(m), on m és el nombre de paraules afegides a L. */
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