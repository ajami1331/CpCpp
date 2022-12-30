#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#ifndef solution_h
#define solution_h 1


namespace solution
{
    void Solve()
    {
        int t;
        std::cin >> t;
        while (t--) {
            int n, m;
            std::cin >> n >> m;
            std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
            for (int i = 0; i < n; i++) {
                int x;
                std::cin >> x;
                pq.push(x);
            }
            for (int i = 0; i < m; i++) {
                int x;
                std::cin >> x;
                pq.pop();
                pq.push(x);
            }
            long long ans = 0;
            while (!pq.empty())
            {   
                ans += pq.top();
                pq.pop();
            }
            std::cout << ans << "\n";
        }
    }
}
#endif
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char* argv[])
{
#ifdef CLown1331
    const clock_t tStart = clock();
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    solution::Solve();
#ifdef CLown1331
    fprintf(stderr, "\n>> Runtime: %.10fs\n", static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC);
    utils::CreateFileForSubmission();
#endif
    return 0;
}
