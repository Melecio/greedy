#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

typedef pair<int, int> Edge;
typedef vector<Edge> ve;
typedef vector<int> vi;
typedef map<int, int> Mapping;
typedef Mapping::iterator mit;


class UnionFind {
    private: vi rep, rank, sizeOf;
             int numSets;
             Mapping table;
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
        int findSet(int i) { return (rep[i] == i) ? i : rep[i] = findSet(rep[i]); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        int getNumSets() { return numSets; }
        Mapping getTable() { return table; }
};


int query(int N, Mapping table) {
    // The number of all possible edges in a graph given N nodes is determined
    // by the
    int discon = (N*(N-1))/2;

    for (mit it = table.begin(); it != table.end(); it++) {
        int nodes = it->second;
        int edges = nodes*(nodes - 1)/2;
        discon -= edges;
    }

    return discon;
}

void remove(int index, ve &edges) {
    edges.erase(edges.begin()+index-1);
}

Mapping process_edges(ve edges, int N) {
   UnionFind set(N);

   for (int i = 0; i < edges.size(); ++i) {
        if (! set.isSameSet(edges[i].first, edges[i].second)) {
            set.unionSets(edges[i].first, edges[i].second);
        }
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

        UnionFind set(offs);
        // std::cout << "-------------------" << std::endl;
        // process_edges(adylist, offs, table);
        // std::cout << "-------------------" << std::endl;

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

