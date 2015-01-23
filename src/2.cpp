/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Melecio Ponte <pontezambrano@gmail.com>
  *
  * @section Description
  *
  * Solve problem 2
  */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

/** Defining some types */
typedef pair<int, int> Edge;
typedef vector<Edge> ve;
typedef vector<int> vi;
typedef map<int, int> Mapping;
typedef Mapping::iterator mit;
/******************************/

/**  UnionFind class */
class UnionFind {
    private: vi rep, rank, sizeOf;
             int numSets;    //number of disjoint sets
             Mapping table;
    public:
        /**
          * UnionFind class constructor
          * @param 'n' : number of elements
          */
        UnionFind(int n) {
            rep.assign(n+1, 0);
            for (int i = 0; i < n+1; i++) rep[i] = i;
            sizeOf.assign(n+1, 1);
            rank.assign(n+1, 0);
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
                    sizeOf[x] += sizeOf[y];
                    table[x] = sizeOf[x];
                    if (table.find(y) != table.end())
                        table.erase(table.find(y));
                } else {
                    rep[x] = y;
                    sizeOf[y] += sizeOf[x];
                    if (rank[x] == rank[y]) rank[y]++;

                    table[y] = sizeOf[y];
                    if (table.find(x) != table.end())
                        table.erase(table.find(x));
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
         /**
           * Gets table
           * @return table 
           */
        Mapping getTable() { return table; }
};

/**
   * Gets how many pairs of nodes are disconnected 
   * @param 'N': number of nodes 
   * @return number of pairs of nodes
   */
int query(int N, Mapping table) {
    int discon = (N*(N-1))/2;
    for (mit it = table.begin(); it != table.end(); it++) {
        int nodes = it->second;
        int edges = nodes*(nodes - 1)/2;
        discon -= edges;
    }
    return discon;
}

/**
   * Removes the i-th element
   * @param 'index': i-th element
   * @return number of pairs of nodes
   */
void remove(int index, ve &edges) { edges.erase(edges.begin()+index-1); }

/**
  * Gets the size of every connected component
  * @param 'edges': list of edges 
  * @param 'N'    : number of nodes
  * @return a map that has the size of every disjoint set 
  *         (that are greater that one)
  */
Mapping process_edges(ve edges, int N) {
   UnionFind set(N);
   for (int i = 0; i < edges.size(); ++i) {
        if (! set.isSameSet(edges[i].first, edges[i].second)) 
            set.unionSets(edges[i].first, edges[i].second);
   }
   return set.getTable();
}


int main(void) {
    int cases;
    scanf("%d", &cases);
    getchar();  // Ignore blank line
    while (cases--) {
        getchar();  // Ignore blank line
        int offs;
        scanf("%d", &offs);
        ve adylist;
        for (int i = 0; i < offs-1; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            adylist.push_back(pair<int, int>(x, y));
        }
        int queries;
        scanf("%d", &queries);
        getchar();
        while (queries--) {
            char q;
            scanf("%c", &q);
            if (q == 'R') {
                int del;
                scanf("%d", &del);
                remove(del, adylist);
            } else {
                Mapping table = process_edges(adylist, offs);
                int rest = query(offs, table);
                printf("%d\n", rest);
            }
            getchar();
        }
        if (cases >= 1) printf("\n"); 
    }
}
