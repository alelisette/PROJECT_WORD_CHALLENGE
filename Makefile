# DEBUG_OPCIONS = -ansi -D_JUDGE_ -D_GLIBCXX_DEBUG -Wall -Wextra -Wno-deprecated -Wno-unused-parameter -std=c++17
# DEBUG_OPCIONS_WITHOUT_ERROR = -ansi -D_JUDGE_ -O2 -Wall -Wextra -Wno-deprecated -Wno-unused-parameter -std=c++11
# DEBUG_OPCIONS_WITHOUT_ERROR = -D_JUDGE_ -O2 -Wall -Wextra -std=c++11
# RELEASE_OPCIONS = -ansi -D_JUDGE_ -O2 -Wall -Wextra -Werror -std=c++17
OPCIONS = -std=c++14 -g -O0 -Wall -Wno-deprecated -Werror
# OPCIONS = -std=c++11 -c -Wall -Werror

driver_joc_par.e: driver_joc_par.o obte_paraules.o anagrames.o word_toolkit.o diccionari.o iter_subset.o
	g++ -o driver_joc_par.e driver_joc_par.o obte_paraules.o anagrames.o word_toolkit.o diccionari.o iter_subset.o -lesin

driver_joc_par.o: driver_joc_par.cpp obte_paraules.hpp anagrames.hpp iter_subset.hpp diccionari.hpp word_toolkit.hpp
	g++ -c driver_joc_par.cpp $(OPCIONS)

obte_paraules.o: obte_paraules.cpp obte_paraules.hpp anagrames.hpp
	g++ -c obte_paraules.cpp $(OPCIONS)

anagrames.o: anagrames.cpp anagrames.hpp diccionari.hpp
	g++ -c anagrames.cpp $(OPCIONS)

word_toolkit.o: word_toolkit.cpp word_toolkit.hpp
	g++ -c word_toolkit.cpp $(OPCIONS)

diccionari.o: diccionari.cpp diccionari.hpp
	g++ -c diccionari.cpp $(OPCIONS)

iter_subset.o: iter_subset.cpp iter_subset.hpp
	g++ -c iter_subset.cpp $(OPCIONS)

clean:
	rm *.o
	rm *.e
	rm *.gch