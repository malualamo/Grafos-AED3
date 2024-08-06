#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <stdio.h>

using namespace std;

vector<int> distancia, distancia_t, res;
vector<bool> processed;
vector<vector<pair<int,int>>> adj, adj_t;
vector<tuple<int,int,int>> bid;
priority_queue<pair<int,int>> q;
int n,m,k,s,t,d,l,c1;
const int inf=10000000;

void dijkstra(int s){
    distancia[s] = 0;
    q.push({0, s});

    while (!q.empty()) {
        int a = q.top().second;
        q.pop();

        if (processed[a]) {
            continue;
        }

        processed[a] = true;

        for (auto& u : adj[a]) {
            int b = u.first, w = u.second;

            if (distancia[a] + w < distancia[b]) {
                distancia[b] = distancia[a] + w;
                q.push({-distancia[b], b});
            }

        }
    }
}

void dijkstra_t(int t){
    distancia_t[t]=0;
    q.push({0, t});

    while (!q.empty()) {
        int a = q.top().second;
        q.pop();

        if (processed[a]) {
            continue;
        }

        processed[a] = true;

        for (auto& u : adj_t[a]) {
            int b = u.first, w = u.second;

            if (distancia_t[a] + w < distancia_t[b]) {
                distancia_t[b] = distancia_t[a] + w;
                q.push({-distancia_t[b], b});
            }

        }
    }
}

int main() {
    int c;
    scanf("%d", &c);

    while(c--){
        scanf("%d %d %d %d %d", &n, &m, &k, &s, &t);

        // Reinicio las variables.

        processed.assign(n+2, false);
        distancia.assign(n+2, inf), distancia_t.assign(n+2, inf);
        adj.assign(n+1, {});
        adj_t.assign(n+1, {});
        bid={};


        // Inicializacion.
        for(int i=0; i<m; i++){
            scanf("%d %d %d", &d, &c1, &l);
            adj[d].push_back({c1,l});
            adj_t[c1].push_back({d,l});
        }


        for(int i=0;i<k;i++){
            scanf("%d %d %d", &d, &c1, &l);
            bid.push_back({d,c1,l});
        }

        // Calculo dijkstra
        dijkstra(s);

        processed.assign(n+1,false); // Reinicio.

        dijkstra_t(t);

        int long_min=distancia[t];
        for(auto& e : bid){
            int u=get<0>(e), v=get<1>(e), w=get<2>(e);
            int st = min(distancia[u]+w+distancia_t[v], distancia[v]+w+distancia_t[u]);
            long_min=min(st,long_min);
        }

        if(long_min != inf) res.push_back(long_min);//printf("%d\n", long_min);
        else res.push_back(-1); //printf("-1\n");

    }
    for(int i=0; i<res.size(); i++){
        cout << res[i] << endl;
    }
    return 0;
}