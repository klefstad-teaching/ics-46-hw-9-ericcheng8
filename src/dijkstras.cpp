#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source}); // greater<> compares first element first
    distance[source] = 0;

    while (!pq.empty()) {
        pair<int, int> current = pq.top();
        pq.pop();

        int u = current.second;

        if (visited[u]) continue;

        visited[u] = true;

        for (auto &e : G[u]) {
            int v = e.dst; // destination
            int weight = e.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int i = destination; i != -1; i = previous[i]) {
        path.insert(path.begin(), i);
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl << "Total cost is " << total << endl;
}
