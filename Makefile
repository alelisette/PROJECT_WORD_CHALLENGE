DEBUG_OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -std=c++17 
DEBUG_OPCIONS_WITHOUT_ERROR = -D_JUDGE_ -O2 -Wall -Wextra -std=c++11 
RELEASE_OPCIONS = -D_JUDGE_ -O2 -Wall -Wextra -Werror -std=c++17 

driver_joc_par.e: driver_joc_par.o obte_paraules.o anagrames.o word_toolkit.o diccionari.o iter_subset.o
	g++ -o driver_joc_par.e driver_joc_par.o obte_paraules.o anagrames.o word_toolkit.o diccionari.o iter_subset.o -lesin
	rm *.o 

# Canviar a $(RELEASE_OPCIONS) en producció
# Canviar a $(DEBUG_OPCIONS) quan s'incorporin els throws error
driver_joc_par.o: driver_joc_par.cpp obte_paraules.hpp anagrames.hpp iter_subset.hpp diccionari.hpp word_toolkit.hpp
	g++ -c driver_joc_par.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)  

obte_paraules.o: obte_paraules.cpp obte_paraules.hpp anagrames.hpp
	g++ -c obte_paraules.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)

anagrames.o: anagrames.cpp anagrames.hpp diccionari.hpp
	g++ -c anagrames.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)

word_toolkit.o: word_toolkit.cpp word_toolkit.hpp
	g++ -c word_toolkit.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)

diccionari.o: diccionari.cpp diccionari.hpp
	g++ -c diccionari.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)

iter_subset.o: iter_subset.cpp iter_subset.hpp
	g++ -c iter_subset.cpp $(DEBUG_OPCIONS_WITHOUT_ERROR)

clean:
	rm *.o
	rm *.exe
	rm *.gch