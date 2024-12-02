#include "iter_subset.hpp"

/* Cost: O(k) */
iter_subset::iter_subset(nat n, nat k) throw(error) {
   if (n < k) _end = true;
   else _end = false;

   _n = n;
   _k = k;
   _ss = subset(k, 0);
   for (nat i = 0; i < k; ++i) _ss[i] = i+1;
}

/* Cost: O(k) */
iter_subset::iter_subset(const iter_subset& its) throw(error) {
   _n = its._n;
   _k = its._k;
   _ss = subset(_k, 0);
   for (nat i = 0; i < _k; ++i) _ss[i] = its._ss[i];
   _end = its._end;
}

/* Cost: O(k) */
iter_subset &iter_subset::operator=(const iter_subset& its) throw(error){
   if (this != &its) {
      iter_subset aux(its);
      
      swap(_n, aux._n);
      swap(_k, aux._k);
      swap(_ss, aux._ss);
      swap(_end, aux._end);
   }

   return *this;
}

/* Cost: O(1) */
iter_subset::~iter_subset() throw() {

}

/* Cost: O(1) */
bool iter_subset::end() const throw() {
   return _end;
}

/* Cost: O(k) */
subset iter_subset::operator*() const throw(error) {
   if (_end) {
      error err(IterSubsetIncorr);
      throw err;
   }

   return _ss;
}       

/* Cost: O(k) */
iter_subset& iter_subset::operator++() throw() {
   if (not _end) {
      int index = _k-1;
      while (0 <= index and _ss[index] == _n-_k+index+1) --index;

      if (index != -1) {
         ++_ss[index];
         for (nat i = index+1; i < _k; ++i) _ss[i] = _ss[i-1]+1;
      }
      else if (_k == 0 or _ss[0] == _n-_k+1) _end = true;
   }

   return *this;
}

/* Cost: O(k) */
iter_subset iter_subset::operator++(int) throw() {
   iter_subset anterior = *this;
   operator++();
   return anterior;
}

/* Cost: O(k) */
bool iter_subset::operator==(const iter_subset& c) const throw() {
   bool iguals = true;

   if (_k == c._k and _end == c._end and (_k == 0 or _n == c._n)) {
      nat i = 0;
      while (i < _k and iguals) {
         if (_ss[i] != c._ss[i]) iguals = false;
         ++i;
      }
   }
   else iguals = false;

   return iguals;
} 

/* Cost: O(k) */
bool iter_subset::operator!=(const iter_subset& c) const throw() {
   return not (*this == c);
}