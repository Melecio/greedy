#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

bool compare(ii a, ii b) { return (a.second < b.second); }

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        vii tasks;
        int nt;      //Number of tasks
        scanf("%d", &nt);
        while (nt--) {
            int a, b;
            scanf("%d %d", &a, &b);
            tasks.push_back(ii(a,b));
        }
        sort(tasks.begin(), tasks.end(), &compare);
        int last = 0, counter = 0;
        for (int i = 0; i < tasks.size(); i++) { 
            if (tasks[i].first >= last) {
                counter++; 
                last = tasks[i].second;
            }
        }
        printf("%d\n", counter);
    }
    return 0;
}
