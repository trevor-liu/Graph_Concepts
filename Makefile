graph_concepts: graph_concepts.o digraph.o
	g++ -std=c++11 graph_concepts.o digraph.o -o graph_concepts

graph_concepts.o: graph_concepts.cpp
	g++ -std=c++11 -c graph_concepts.cpp

digraph.o: digraph.cpp digraph.h
	g++ -std=c++11 -c digraph.cpp

clean:
	rm *.o graph_concepts

