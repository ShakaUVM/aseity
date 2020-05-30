aseity: aseity.cc
	g++ -pthread -std=c++17 -O3 -o aseity aseity.cc

clean:
	rm -f *.o aseity
