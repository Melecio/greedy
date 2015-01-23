#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef vector< vector<int> > graph;

int main(void) {
    int cases;

    scanf("%d", &cases);
    getchar(); // Ignore blank line
    // printf("Numero de casos: %d\n", cases);

    while (cases--) {
        getchar(); // Ignore blank line
        int offs;
        scanf("%d", &offs);
        // printf("Numero de oficinas: %d\n", offs);

        graph adylist;
        adylist.assign(offs+1, vector<int>());

        for (int i = 0; i < offs-1; ++i) {
            int x,y;
            scanf("%d %d", &x, &y);
            adylist[x].push_back(y);
            adylist[y].push_back(x);
        }

        for (int i = 1; i < adylist.size(); ++i) {
            sort(adylist[i].begin(), adylist[i].end());
        }


        // printf("------------------\n");
        // for (int i = 1; i < adylist.size(); ++i) {
        //     for (int j = 0; j < adylist[i].size(); ++j) {
        //         printf("Conexion: %d %d\n", i, adylist[i][j]);
        //     }
        // }
        // printf("------------------\n");

        int queries;
        scanf("%d", &queries);
        getchar();
        // printf("Queries: %d\n", queries);

        while(queries--) {
            char q;
            scanf("%c", &q);
            // printf("query: %c\n", q);

            if (q == 'R') {
                int del;
                scanf("%d", &del);
                // printf("%d\n", del);
            } else {
                // imprimir unreachable
            }
            getchar();
        }
    }


}

