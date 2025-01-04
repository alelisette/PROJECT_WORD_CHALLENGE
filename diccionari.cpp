#include "diccionari.hpp"

diccionari::node::node(const char &lletra, node* esq, node* cen, node* dre) :
    _lletra(lletra), _esq(esq), _cen(cen), _dre(dre) {
}

diccionari::diccionari() throw(error) {
    _arrel = nullptr;
}

diccionari::diccionari(const diccionari& D) throw(error) {

}   

diccionari& diccionari::operator=(const diccionari& D) throw(error) {
    return *this;
}

diccionari::~diccionari() throw() {

}

void diccionari::insereix(const string& p) throw(error) {
    string paraulaNova = p + "#";
    _arrel = insereix_aux(_arrel, paraulaNova, 0);
}

diccionari::node* diccionari::insereix_aux(node* arrel, const string& paraulaNova, nat index) throw(error) {
    if (index < paraulaNova.size()) {
        if (arrel == NULL) {
            arrel = new node(paraulaNova[index], NULL, NULL, NULL);
            if (index < paraulaNova.size()-1) arrel->_cen = insereix_aux(arrel->_cen, paraulaNova, index+1);
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

void diccionari::llista_paraules(nat k, list<string>& L) const throw(error) {

}

nat diccionari::num_pal() const throw() {
    return 0;
}