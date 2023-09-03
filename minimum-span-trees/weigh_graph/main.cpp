#include <iostream>
#include <string>
#include "graph.h"
#include "read_graph.h"
#include "edge.h"

int main()
{
    std::string file = "test1.txt";
    int v = 8;
    dense_graph<double> g = dense_graph<double>(v, false);
    read_graph<dense_graph<double>, double> r(g, file);
    g.show();

    std::cout << "\n";

    sparse_graph<double> g1 = sparse_graph<double>(v, false);
    read_graph<sparse_graph<double>, double> r1(g1, file);
    g1.show();

}
