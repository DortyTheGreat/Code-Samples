/*
Orig



from random import random, randint

n = 22

tau = [[1] * n for _ in range(n)]
d = [list(map(float, input().split())) for _ in range(n)]


for iteration in range(100000):
    used = [0] * n
    start = randint(0, n - 1)
    used[start] = 1
    score = 0
    v = start
    edges = []
    for i in range(n - 1):
        probs = []
        s = 0
        for j in range(n):
            if used[j]:
                probs.append(0)
                continue
            p = 1 / d[v][j] * tau[v][j]
            s += p
            probs.append(p)
        for j in range(n):
            probs[j] /= s

        for j in range(1, n):
            probs[j] += probs[j - 1]
        p = random()

        for j in range(n):
            if p < probs[j]:
                edges.append((v, j))
                score += d[v][j]
                used[j] = 1
                # print(v, j)
                v = j
                break

    for u, v in edges:
        tau[u][v] += 1 / score

    for i in range(n):
        for j in range(n):
            tau[i][j] = 0.999 * tau[i][j]
        #     print(round(tau[i][j], 2), end=' ')
        # print()
    print(score)

for i in range(n):
    for j in range(n):
        print(round(tau[i][j], 2), end=' ')
    print()
print(*edges, sep='\n')

*/

#include <iostream>

using namespace std;


const int n = 22

double tau[n][n]; /// fill with 1











int main()
{

    for(int i = 0;i < n;++i){
        for(int i = 0;i < n;++i){
            tau[i][j] = 1;
        }
    }

    /// d = [list(map(float, input().split())) for _ in range(n)] ввод 2д массива

    bool used[n];

    for(int iteration = 0; iteration < 100000; ++iteration){


        for(int i = 0;i < n;++i){used[i] = 0;}
        start = randint(0, n - 1)
        used[start] = 1
        score = 0
        v = start
        edges = []
        for i in range(n - 1):
            probs = []
            s = 0
            for j in range(n):
                if used[j]:
                    probs.append(0)
                    continue
                p = 1 / d[v][j] * tau[v][j]
                s += p
                probs.append(p)
            for j in range(n):
                probs[j] /= s

            for j in range(1, n):
                probs[j] += probs[j - 1]
            p = random()

            for j in range(n):
                if p < probs[j]:
                    edges.append((v, j))
                    score += d[v][j]
                    used[j] = 1
                    # print(v, j)
                    v = j
                    break

        for u, v in edges:
            tau[u][v] += 1 / score

        for i in range(n):
            for j in range(n):
                tau[i][j] = 0.999 * tau[i][j]
            #     print(round(tau[i][j], 2), end=' ')
            # print()
        print(score)

for i in range(n):
    for j in range(n):
        print(round(tau[i][j], 2), end=' ')
    print()
print(*edges, sep='\n')


    cout << "Hello world!" << endl;
    return 0;
}
