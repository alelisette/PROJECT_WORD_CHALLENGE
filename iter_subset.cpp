#include "iter_subset.hpp"

iter_subset::iter_subset(nat n, nat k) throw(error) {
   if (n < k) _end = true;
   else _end = false;

   _n = n;
   _k = k;
   _ss = subset(k, 0);
   for (nat i = 0; i < k; ++i) _ss[i] = i+1;
}

iter_subset::iter_subset(const iter_subset& its) throw(error) {
   /*if (its._n < its._k) {
      _end = true;
      error err(31, "iter_subset", "Acces amb iterador de subconjunts invalid.");
      throw err;
   }*/

   _n = its._n;
   _k = its._k;
   _ss = subset(_k, 0);
   for (nat i = 0; i < _k; ++i) _ss[i] = its._ss[i];
   _end = its._end;
}

iter_subset &iter_subset::operator=(const iter_subset& its) throw(error){
   /*if (its._n < its._k) {
      _end = true;
      error err(31, "iter_subset", "Acces amb iterador de subconjunts invalid.");
      throw err;
   }*/

   if (this != &its) {
      _n = its._n;
      _k = its._k;
      _ss = subset(_k, 0);
      for (nat i = 0; i < _k; ++i) _ss[i] = its._ss[i];
      _end = its._end;
   }

   return *this;
}

iter_subset::~iter_subset() throw() {

}

bool iter_subset::end() const throw() {
   return _end;
}

subset iter_subset::operator*() const throw(error) {
   if (_end) {
      error err(31, "iter_subset", "Acces amb iterador de subconjunts invalid.");
      throw err;
   }

   return _ss;
}       

iter_subset& iter_subset::operator++() throw() {
   if (not _end) {
      int index = _k-1;
      while (0 <= index and _ss[index] == _n-_k+index+1) --index;

      if (index != -1) {
         ++_ss[index];
         for (nat i = index+1; i < _k; ++i) _ss[i] = _ss[index]+_k-i;
      }
      else if (_k == 0 or _ss[0] == _n-_k+1) _end = true;
   }

   return *this;
}

iter_subset iter_subset::operator++(int) throw() {
   iter_subset anterior = *this;

   if (not _end) {
      int index = _k-1;
      while (0 <= index and _ss[index] == _n-_k+index+1) --index;

      if (index != -1) {
         ++_ss[index];
         for (nat i = index+1; i < _k; ++i) _ss[i] = _ss[index]+_k-i;
      }
      else if (_k == 0 or _ss[0] == _n-_k+1) _end = true;
   }

   return anterior;
}

bool iter_subset::operator==(const iter_subset& c) const throw() {
   bool iguals = true;

   if (_n == c._n and _k == c._k) {
      nat i = 0;
      while (i < _k and iguals) {
         if (_ss[i] != c._ss[i]) iguals = false;
         ++i;
      }
   }
   else iguals = false;

   return iguals;
} 

bool iter_subset::operator!=(const iter_subset& c) const throw() {
   return not (*this == c);
}