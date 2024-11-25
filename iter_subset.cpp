#include "iter_subset.hpp"

iter_subset::iter_subset(nat n, nat k) throw(error) {
    if (n < k) throw runtime_error("Error: n < k");

    int nombreCombinatori;
    _mida = (nat)nombreCombinatori;

    node* anterior = nullptr;
    for (int i = 0; i < nombreCombinatori; ++i) {
        node* nouNode = new node;
        nouNode->info;
        nouNode->seg = nullptr;

        if (i == 0) _prim = nouNode;
        else anterior->seg = nouNode;
        anterior = nouNode;
    }
    _ult = anterior;
}