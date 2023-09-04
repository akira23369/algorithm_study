#include <iostream>
#include <string>
#include "graph.h"
#include "read_graph.h"
#include "lazy_prim.h"
#include "edge.h"
#include "heap.h"

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

    lazy_prim<sparse_graph<double>, double> lp(g1);
    std::vector<edge<double>> mst = lp.mst_edges();
    for (int i = 0; i < mst.size(); i++) std::cout << mst[i] << "\n";
}
