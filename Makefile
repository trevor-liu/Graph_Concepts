graph_concepts: graph_concepts.o digraph.o
	g++ graph_concepts.o digraph.o -o graph_concepts

graph_concepts.o: graph_concepts.cpp
	g++ -c graph_concepts.cpp

digraph.o: digraph.cpp digraph.h
	g++ -c digraph.cpp

clean:
	rm *.o output

