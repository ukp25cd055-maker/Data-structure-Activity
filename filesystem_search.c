#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Structure to represent a file/directory node
typedef struct {
    int id;
    char name[50];
    int isFile; // 1 if file, 0 if directory
} Node;

Node nodes[MAX];
int adj[MAX][MAX];
int n; // Total number of nodes

// Function to find node index by its ID
int getNodeIndex(int id) {
    for (int i = 0; i < n; i++) {
        if (nodes[i].id == id)
            return i;
    }
    return -1;
}

// Breadth-First Search (BFS)
void BFS(int startId, int targetId) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;
    int startIndex = getNodeIndex(startId);
    int targetIndex = getNodeIndex(targetId);

    if (startIndex == -1 || targetIndex == -1) {
        printf("Invalid start or target node ID!\n");
        return;
    }

    printf("\n--- BFS Traversal Order ---\n");
    queue[rear++] = startIndex;
    visited[startIndex] = 1;

    int found = 0;

    while (front < rear) {
        int current = queue[front++];
        printf("Visited: %s (ID: %d)\n", nodes[current].name, nodes[current].id);

        if (current == targetIndex) {
            found = 1;
            break;
        }

        for (int i = 0; i < n; i++) {
            if (adj[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    if (found)
        printf("Result: File/Directory '%s' FOUND using BFS!\n", nodes[targetIndex].name);
    else
        printf("Result: File/Directory '%s' NOT FOUND using BFS.\n", nodes[targetIndex].name);
}

// Helper function for Depth-First Search (DFS)
void DFSUtil(int current, int targetIndex, int visited[], int *found) {
    visited[current] = 1;
    printf("Visited: %s (ID: %d)\n", nodes[current].name, nodes[current].id);

    if (current == targetIndex) {
        *found = 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (adj[current][i] == 1 && !visited[i] && !(*found)) {
            DFSUtil(i, targetIndex, visited, found);
        }
    }
}

// Depth-First Search (DFS) wrapper
void DFS(int startId, int targetId) {
    int visited[MAX] = {0};
    int startIndex = getNodeIndex(startId);
    int targetIndex = getNodeIndex(targetId);

    if (startIndex == -1 || targetIndex == -1) {
        printf("Invalid start or target node ID!\n");
        return;
    }

    printf("\n--- DFS Traversal Order ---\n");
    int found = 0;
    DFSUtil(startIndex, targetIndex, visited, &found);

    if (found)
        printf("Result: File/Directory '%s' FOUND using DFS!\n", nodes[targetIndex].name);
    else
        printf("Result: File/Directory '%s' NOT FOUND using DFS.\n", nodes[targetIndex].name);
}

int main() {
    int edges, uId, vId;

    printf("Enter total number of nodes (files/directories): ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for node %d:\n", i + 1);
        printf("Node ID: ");
        scanf("%d", &nodes[i].id);
        printf("Name (e.g., root, folder, file.txt): ");
        scanf("%s", nodes[i].name);
        printf("Is it a file? (1 for File, 0 for Directory): ");
        scanf("%d", &nodes[i].isFile);
    }

    // Initialize adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    printf("\nEnter total number of connections (edges): ");
    scanf("%d", &edges);

    printf("Enter connections as pairs of Node IDs (e.g., parentId childId):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &uId, &vId);
        int u = getNodeIndex(uId);
        int v = getNodeIndex(vId);
        if (u != -1 && v != -1) {
            adj[u][v] = 1;
            adj[v][u] = 1; // Assuming undirected graph representation of file tree links
        } else {
            printf("Invalid node IDs entered for edge. Try again.\n");
            i--;
        }
    }

    int startId, targetId;
    printf("\nEnter Starting Node ID for search: ");
    scanf("%d", &startId);
    printf("Enter Target Node ID to search: ");
    scanf("%d", &targetId);

    // Execute BFS
    BFS(startId, targetId);

    // Execute DFS
    DFS(startId, targetId);

    return 0;
}