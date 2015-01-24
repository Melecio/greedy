/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Melecio Ponte <pontezambrano@gmail.com>
  *
  * @section Description
  *
  * Solve problem 1
  */

#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

/** Defining some types */
typedef vector<int> vi;
typedef pair<int, int> Node;
typedef pair<double, pair<Node, Node> > Edge;
typedef vector<Edge> ve;
typedef vector<Node> vn;
typedef map<Node, int> Mapping;
/******************************/

/**  UnionFind class */
class UnionFind {
    private: vi rep, rank;
             int numSets;    //number of disjoint sets
    public:
        /**
          * UnionFind class constructor
          * @param 'n' : number of elements
          */
        UnionFind(int n) {
            rep.assign(n, 0);
            for (int i = 0; i < n; i++) rep[i] = i;
            rank.assign(n, 0);
            numSets = n;
        }
        /**
          * Makes union operation over the sets of i and j
          * @param 'i' : element
          * @param 'j' : element
          */
        void unionSets(int i, int j) {
            if (! isSameSet(i, j)) {
                numSets--;
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) {
                    rep[y] = x;
                } else {
                    rep[x] = y;
                    if (rank[x] == rank[y]) rank[y]++;
                }
            }
        }
        /**
          * Finds the representing element of the set
          * @param 'i' : element
          * @return the representing element of the set of i
          */
        int findSet(int i) { return (rep[i] == i) ? i : rep[i] = findSet(rep[i]); }
         /**
           * Tells if two elements are in the same set
           * @param 'i' : element
           * @param 'j' : element
           * @return true, if i and j are in the same set; false in any other case
           */
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
         /**
           * Gets the number of disjoint sets
           * @return numSet
           */
        int getNumSets() { return numSets; }
};

 /**
   * Gets the euclidean distance of two nodes
   * @param 'e': edge
   * @return euclidean distance of e
   */
double euclidean(pair<Node, Node> e) {
    Node n1 = e.first, n2 = e.second;
    double x = n1.first - n2.first;
    x *= x;
    double y = n1.second - n2.second;
    y *= y;
    return sqrt(x + y);
}

/**
  * Gets the meters of standard and special lines 
  * @param 'edges' : list of edges
  * @param 'table' : mapping table
  * @param 'N'     : number of offices
  * @param 'R'     : maximum value of meters for standard lines
  * @param 'M'     : number of modems
  */
pair<double, double> kruskal(ve edges, Mapping table, int N, int R, int M) {
    double A = 0, B = 0;   //meters of standard and special lines, respectively
    UnionFind set(N);
    for (int i = 0; i < edges.size(); i++) {
        //checking if there are M connected components
        if (set.getNumSets() == M) break;    
        Node n1 = edges[i].second.first;
        Node n2 = edges[i].second.second;
        int v1 = table[n1];
        int v2 = table[n2];
        if (! set.isSameSet(v1, v2)) {
            set.unionSets(v1, v2);
            double w = edges[i].first;
            if (w <= R) A += w;
            else B += w;
        }
    }
    return pair<double, double>(A, B);
}

/**
  * Tells if e1 should go before e2
  * @param 'e1' : first edge
  * @param 'e2' : second edge
  * @return true, if weight of e1 is less than the weight of e2;
  *         false, in any other case
  */
bool compare(Edge e1, Edge e2) { return (e1.first < e2.first); }

int main(void) {
    int t;            //number of test cases
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        //N is the number of offices
        //R is the maximum value of meters for standard lines
        //M is number of modems
        //U is the cost of 1 meter of standard line
        //V is cost of 1 meter of special line
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
        for (int j = 0; j < N; j++) {   //generating all n(n-1)/2 possible edges
            for (int k = j+1; k < N; k++) {
                pair<Node, Node> nn = pair<Node, Node>(nodes[j], nodes[k]);
                edges.push_back(Edge(euclidean(nn), nn));
            }
        }
        sort(edges.begin(), edges.end(), &compare);
        pair<double, double> lines = kruskal(edges, table, N, R, M);
        printf("Caso #%d: %.3lf %.3lf\n", i, lines.first * U, lines.second * V);
    }
    return 0;
}
