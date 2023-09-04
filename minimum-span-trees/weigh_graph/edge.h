#pragma once
#include <iostream>

template<typename Weight>
class edge
{
    int a, b;       // 两顶点
    Weight weight;
public:
    edge(int a, int b, Weight w) :a(a), b(b), weight(w) {}
    edge() { }
    ~edge() { }
    int v() { return a; }   // 获取顶点a
    int w() { return b; }   // 获取顶点b
    Weight wt() { return weight; }

    // 返回这个点的另一个点
    int other(int x) 
    {
        assert(x == a || x == b);
        return x == a ? b : a;
    }
    friend std::ostream& operator<<(std::ostream& out, const edge<Weight> &e)
    {
        out << e.a << "-" << e.b << ": " << e.weight << "\n";
        return out;
    }
    bool operator<(edge<Weight> &e) { return weight > e.wt(); }
    bool operator<=(edge<Weight> &e) { return weight >= e.wt(); }
    bool operator>(edge<Weight> &e) { return weight < e.wt(); }
    bool operator>=(edge<Weight> &e) { return weight <= e.wt(); }
    bool operator==(edge<Weight> &e) { return weight == e.wt(); }

};