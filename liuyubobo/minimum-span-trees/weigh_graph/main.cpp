#include <iostream>
#include <string>
#include "graph.h"
#include "read_graph.h"
// #include "lazy_prim.h"
#include "edge.h"
#include "heap.h"
#include "lazy_prim_plus.h"
#include "kruska.h"
#include "index_heap.h"
#include "dijkstra.h"
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

    // lazy_prim<sparse_graph<double>, double> lp(g1);
    // std::vector<edge<double>> mst = lp.mst_edges();
    // for (int i = 0; i < mst.size(); i++) std::cout << mst[i] << "\n";

    kruska<sparse_graph<double>, double> krk(g1);
    std::vector<edge<double>> mst2 = krk.mst_edges();
    for (int i = 0; i < mst2.size(); i++) std::cout << mst2[i] << "\n";

    djkstra<sparse_graph<double>, double> dj(g1, 0);
    for (int i = 1; i < 5; i++)
    {
        std::cout << i << " : " << dj.dist_at(i) << "\n";
        dj.show_path(i);
        std::cout << "---------" << "\n";
    }
    
}
