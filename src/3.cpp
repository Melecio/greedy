/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Melecio Ponte <pontezambrano@gmail.com>
  *
  * @section Description
  *
  * Solve problem 3
  */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/** Defining some types */
typedef pair<int, int> task;
typedef vector<task> vii;
/******************************/

/**
  * Tells if a should go before b
  * @param 'a' : task a
  * @param 'b' : task b
  * @return true, if a ends before b
  *         false, in any other case
  */
bool compare(task a, task b) { return (a.second < b.second); }

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
            tasks.push_back(task(a,b));
        }
        //sorting tasks by selecting those with lesser finish time
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
