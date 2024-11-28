#include "iter_subset.hpp"

iter_subset::iter_subset(nat n, nat k) throw(error) {
   if (n < k) throw runtime_error("Error: n < k");

   _n = n;
   _k = k;
   
   vector<nat> info;
   for (nat i = 0; i < k; ++i) info.push_back(i+1);
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
iter_subset::iter_subset(const iter_subset& its) throw(error) {
   /*node* p = its._prim;
   while (p != nullptr) {
      node* actual = new node;
      actual->info = p->info;
      actual->seg = p->seg;

      if (p == its._prim) _prim = actual;
      if (p == its._ult) _ult = actual;
      p = p->seg;
   }*/
}

iter_subset &iter_subset::operator=(const iter_subset& its) throw(error){
   return *this;
}

iter_subset::~iter_subset() throw() {

}

bool iter_subset::end() const throw() {
   return true;
}

subset iter_subset::operator*() const throw(error) {
   return _ss;
}       

iter_subset& iter_subset::operator++() throw() {
   return *this;
}

iter_subset iter_subset::operator++(int) throw() {
   return *this;
}

bool iter_subset::operator==(const iter_subset& c) const throw() {
   return true;
} 

bool iter_subset::operator!=(const iter_subset& c) const throw() {
   return true;
}