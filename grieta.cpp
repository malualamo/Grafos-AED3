#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n,m,v,u;
const int INF=10000000;
vector<vector<int>> capacity, adj;

//Edmonds-Karp:  https://cp-algorithms.com/graph/edmonds_karp.html#implementation

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    while(true){
        scanf("%d %d", &n, &m);
        if(n==0 && m==0){
            break;
        };

        capacity.assign(n+2,vector<int>(n+2,INF));
        adj.assign(n+1,{});

        // Ingreso las preferencias.
        for(int i=1; i<=n; i++){
            scanf("%d", &v);
            if(v==1) capacity[0][i]=1, adj[0].push_back(i); // 0 representa a Prim.
            else capacity[i][n+1]=1, adj[i].push_back(n+1); // n+1 representa  Kruskal
        }

        // Ingreso las amistades.
        for(int i=0; i<m; i++){
            scanf("%d %d", &u, &v);
            capacity[u][v]=1, adj[u].push_back(v);
            capacity[v][u]=1, adj[v].push_back(u);
        }

        // Calculamos el flujo maximo que es equivalente al valor del corte minimo.
        printf("%d\n", maxflow(0,n+1));
    }
    return 0;
}

