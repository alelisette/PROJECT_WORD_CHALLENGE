#include "diccionari.hpp"
#include "word_toolkit.hpp"

diccionari::node::node(const char &lletra, node* esq, node* cen, node* dre) :
    _lletra(lletra), _esq(esq), _cen(cen), _dre(dre) {
}

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
        esborrra(arrel->_esq);
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
            arrel = new node(paraulaNova[index], nullptr, nullptr, nullptr);

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

void diccionari::satisfan_patro(const vector<string>& q, list<string>& L) const throw(error) {

}

void diccionari::satisfan_patro_aux(node* arrel, const vector<string>& q, list<string>& L) const throw(error) {

}

void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {

}

nat diccionari::num_pal() const throw() {
    return _numPal;
}