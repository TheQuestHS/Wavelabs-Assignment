#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Create adjacency matrix to represent the network
    vector<vector<int>> adjMatrix(n + 1, vector<int>(n + 1, -1));
    for (const auto& time : times) {
        int u = time[0];
        int v = time[1];
        int w = time[2];
        adjMatrix[u][v] = w;
    }

    // Create distance array to store minimum time to reach each node
    vector<int> distance(n + 1, INT_MAX);

    // Create priority queue for Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, k});
    distance[k] = 0;

    while (!pq.empty()) {
        int currNode = pq.top().second;
        int currTime = pq.top().first;
        pq.pop();

        // Check if the current time to reach the current node is greater than the stored distance
        if (currTime > distance[currNode])
            continue;

        // Iterate through all adjacent nodes
        for (int nextNode = 1; nextNode <= n; ++nextNode) {
            // Check if there is a connection between the current node and the next node
            if (adjMatrix[currNode][nextNode] != -1) {
                int totalTime = currTime + adjMatrix[currNode][nextNode];

                // If the new total time is smaller, update the distance and push the node to the priority queue
                if (totalTime < distance[nextNode]) {
                    distance[nextNode] = totalTime;
                    pq.push({totalTime, nextNode});
                }
            }
        }
    }

    // Find the maximum time in the distance array
    int maxTime = 0;
    for (int i = 1; i <= n; ++i) {
        if (distance[i] == INT_MAX)
            return -1;
        maxTime = max(maxTime, distance[i]);
    }

    return maxTime;
}

int main() {
    int n = 4;  // Number of nodes
    int k = 2;  // Source node to send signal
    
    vector<vector<int>> times = {
        {1, 2, 1},
        {2, 3, 2},
        {1, 3, 4},
        {2, 4, 3},
        {4, 3, 2}
    };

    int minTime = networkDelayTime(times, n, k);
    cout << "Minimum time for all nodes to receive the signal: " << minTime << endl;

return 0;
}