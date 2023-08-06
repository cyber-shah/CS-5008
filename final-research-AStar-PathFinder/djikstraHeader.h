#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hashmap.h"

#define INF 9999
#define MAX_NODES 100

/**
 * A node is represented by the following :
 * 1. The node number.
 * 2. The distance from the source node.
*/
struct Node {
    char *name;
    int index;
    int distance;
} typedef Node;


/**
 * A graph is represented by the following :
 * 1. The adjacency matrix is a 2D array of integers.
 * 2. The number of nodes in the graph.
 * 3. The number of edges in the graph.
*/
struct Graph {
    int numberOfNodes;
    int numberOfEdges;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    Node *nodes[MAX_NODES];
} typedef Graph;

/**
 * 
*/
struct distArray {
    int nodeIndex;
    int distance;
} typedef distArray;


/**
 * adds a node to the graph with the given name.
 * creates a node, and adds it to graph.
 * 
 * @param 
*/
int add_to_graph(Graph* graph, char *nodeName) {
    // 1. get the index
    int index = graph->numberOfNodes;

    // 2. create the node
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = strdup(nodeName);
    node->index = index;
    node->distance = INF;

    // 3. add node to the graph
    graph->nodes[index] = node;
    graph->numberOfNodes++;

    return index;
}


/**
 * Sets the edge index based on the source and destination.
 * For example : set_edge_distance(&graph, "paris", "lille", 50)
 * 
 * 
*/
int set_edge_distance(Graph *graph, 
                      char *src, char *dest, int weight) {
    
    int src_index = -1; int dest_index = -1;
    
    // find the index of the source node.
    for (int i = 0; i < graph->numberOfNodes; i++) {
        if (strcmp(graph->nodes[i]->name, src) ) {
            src_index = i;
        }
        else if (strcmp(graph->nodes[i]->name, dest) ) {
            dest_index = i;
        }
    }

    // if node not found return
    if (src_index == -1 || dest_index == -1) {
        return -1;
    }

    // if node found edit the distance
    graph->adjacencyMatrix [src_index] [dest_index] = weight;
    return 1;
}

/**
 * initializes a graph to have no nodes or edges.
 * and all edges to have a weight of infinity.
 * 
 * Example : adjacencyMatrix[i][j] = distance from node i to node j.
 *  
 * @param graph the graph to initialize.
*/
Graph* initializeGraph() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->numberOfNodes = 0;
    graph->numberOfEdges = 0;
    graph->adjacencyMatrix[MAX_NODES][MAX_NODES] = INF;
    return graph;
}

/**
 * Finds the unvisited node with the minimum distance.
 * 
 * @param visited_list the array of visited_list nodes.
 * @param distArray the array of nodes with their distance from the source node.
 * @returns node_index with the minimum distance.
*/
int find_min_distance_node(bool visited_list[], int distances_list[]) {
    int minDistance = INF;
    int node_index = -1;

    // for all nodes if unvisited and distance less than minDistance.
    for (int i = 0; i < MAX_NODES; i++) {
        if (visited_list[i] == false && distances_list[i] <= minDistance) {
            minDistance = distances_list[i];
            node_index = i;
        }
    }
    return node_index;
}

/**
 * This function is the implementation of the djikstra algorithm.
 * here distance = sum of weights of edges from source node to the current node.
 *                  or the distance from the source node to the current node.
 * 1. find the node with the minimum distance to visit next.
 * 2. Loop over all of its adjacent nodes.
 *      2.1 Relax all the adjacent nodes unvisited nodes. (why?)
 *              because we visit a node only when we have found the shortest path to it 
 *              and there is no other shorter path.
 *      2.2 If the new distance is less than the current distance, update the distance.
 * 3. Pick the smallest distance node from unvisited nodes.
 * 4. Repeat steps 2 and 3 until all the nodes are visited_list.
 * 5. Keep updating the distance array.
 * 
 * @param sourceNode the source node.
 * @param graph the graph to find the shortest path.
*/
void djikstra(int sourceNode, Graph *graph) {

    // initialize all the visited_list nodes to false.
    bool visited_list [MAX_NODES] = {false};
    // array of nodes - to store the distance from the source node.
    int distances_list[MAX_NODES] = {INF};

    distances_list[sourceNode] = 0;

    // loop through all the nodes
    for (int i = 0; i < (graph->numberOfNodes - 1); ++i) {
        // finds the node with the minimum distance to visit next.
        int minDistanceNode = find_min_distance_node(visited_list, distances_list);

        // mark the node as visited
        visited_list[minDistanceNode] == true;

        // loop through all the nodes.
        for (int j = 0; j < graph->numberOfNodes; ++j) {
            // relax all the adjacent unvisited nodes. adjacent means distance != INF
            if (visited_list[j] == false && graph->adjacencyMatrix[minDistanceNode][j] != INF) {
                int newDistance = distances_list [minDistanceNode] 
                                  + graph->adjacencyMatrix[minDistanceNode][j];
                if (newDistance < distances_list[j]) {
                    // update the distance
                    distances_list[j] = newDistance;
                }
            }
        }

    }
}



void free_graph(Graph *graph) {
    for (int i = 0; i < graph->numberOfNodes; i++) {
        free(graph->nodes[i]);
    }
    free(graph);
}