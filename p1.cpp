#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> Node;
typedef pair<double, pair<Node, Node> > Edge;
typedef vector<Edge> ve;
typedef vector<Node> vn;
typedef map<Node, int> Mapping;

double euclidean(pair<Node, Node> e) {
    Node n1 = e.first, n2 = e.second;
    double x = n1.first - n2.first;
    x *= x;
    double y = n1.second - n2.second;
    y *= y;
    return sqrt(x + y);
}

class UnionFind {
    private: vi rep, rank, sizeOf;
             int numSets;
    public:
        UnionFind(int n) {
            rep.assign(n, 0);
            for (int i = 0; i < n; i++) rep[i] = i;
            sizeOf.assign(n, 1);
            rank.assign(n, 0);
            numSets = n;
        }
        void unionSets(int i, int j) {
            if (! isSameSet(i, j)) {
                numSets--;
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) {
                    rep[y] = x;
                    sizeOf[x] += sizeOf[y];
                } else {
                    rep[x] = y;
                    sizeOf[y] += sizeOf[x];
                    if (rank[x] == rank[y]) rank[y]++;
                }
            }
        }
        int findSet(int i) { return (rep[i] == i) ? i : rep[i] = findSet(rep[i]); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        int getNumSets() { return numSets; }
};

pair<double, double> kruskal(ve edges, Mapping table, int N, int R, int M) {
    int A = 0, B = 0;
    UnionFind set(N);
    for (int i = 0; i < edges.size(); i++) {
        if (set.getNumSets() == M) break;
        Node n1 = edges[i].second.first;
        Node n2 = edges[i].second.second;
        int v1 = table[n1];
        int v2 = table[n2];
        if (! set.isSameSet(v1, v2)) {
            set.unionSets(v1, v2);
            int w = edges[i].first;
            if (w <= R) A += w;
            else B += w;
        } 
    }
    return pair<double, double>(A, B);
}

bool compare(Edge e1, Edge e2) { return (e1.first < e2.first); }

int main(void) {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        int N, R, M, U, V;
        scanf("%d %d %d %d %d", &N, &R, &M, &U, &V);
        vn nodes;
        Mapping table; 
        for (int j = 0; j < N; j++) {
            int x, y;
            scanf("%d %d", &x, &y);
            nodes.push_back(Node(x,y));
            table[Node(x,y)] = j;
        } 
        ve edges;
        for (int j = 0; j < N; j++) {
            for (int k = j+1; k < N; k++) {
                pair<Node, Node> nn = pair<Node, Node>(nodes[j], nodes[k]);
                edges.push_back(Edge(euclidean(nn), nn));
            }
        }
        sort(edges.begin(), edges.end(), &compare);
        pair<double, double> lines = kruskal(edges, table, N, R, M);
        printf("%.3lf %.3lf\n", lines.first * U, lines.second * V);
    }
    return 0;
}
