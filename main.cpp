


//
//  main.cpp
//  CppGraphTest
//
//  Created by Dave Duprey on 25/11/2019.
//  Copyright © 2019 Dave Duprey. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;


struct Edge {
    const int source;
    const int destination;
};
int find_vertices_size(const vector<Edge>& edges) { 
    unordered_set<int> vertices;
    for (const auto& edge : edges) {
        vertices.insert(edge.source);
        vertices.insert(edge.destination);  // An unordered set will ignore duplicate elements, so simply add all elements to ensure none are missing
    }
    return vertices.size(); //the vertices size is found as the size of the unordered set
}
bool does_a_vertex_end_wth_cycle(int checking_vertice, vector<vector<int>>& adj, vector<bool>& checked_vertices, int ancestor) { //main recursion to check the cycle for a node
    
    checked_vertices[checking_vertice] = true;

    for (int i : adj[checking_vertice]) {
        if (!checked_vertices[i]) {
            if (does_a_vertex_end_wth_cycle(i, adj, checked_vertices, checking_vertice)) // recursion occurs!, will loop until the next node is already checked
                return true;
        }
        else if (i != ancestor) { // If it has already been checked and is not its direct ancestor, it indicates a loop or cycle, which will cause the return to trigger a cascade of returns for all previous recursions
            return true;  /// only one cycle is detected enough to stop everything
        }
    }
    return false; // no cycle is detected after scanning whole node 
}



bool has_cycle(const vector<Edge>& edges) {
    int vertices_size = find_vertices_size(edges); /// get size of vertices, even if it is greater than 12 it will still work
    vector<vector<int>> adj(vertices_size); // Retrieve all nodes connected (adjacent) to a specific vertex
    for (const auto& edge : edges) {// this loop will retrieve all nodes connected (adjacent) to a specific vertex
        adj[edge.source].push_back(edge.destination);
        adj[edge.destination].push_back(edge.source);
    }

    vector<bool> checked_vertices(vertices_size, false); // the vector to know if a vertex is checked
    for (int u = 0; u < vertices_size; u++) {
        if (!checked_vertices[u]) {
            if (does_a_vertex_end_wth_cycle(u, adj, checked_vertices, -1))   // main recursion 
                return true;
        }
    }
    return false;

}


void report_results(bool cycle_found) {
    if (cycle_found)
        cout << "Graph contains a cycle\n";
    else
        cout << "Graph does NOT contain any cycles\n";
}


void check_for_cycles(const vector<Edge>& edges) {
    bool cycle_found = has_cycle(edges);
    report_results(cycle_found);
}


int main(int argc, const char* argv[]) {

  const vector<Edge> edges_with_cycle = {{0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11}, {5, 9}};
   const vector<Edge> edges_without_cycle = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} };
    
  check_for_cycles(edges_with_cycle);
   check_for_cycles(edges_without_cycle);
   /*
  // other testcases: with the cycles
   const vector<Edge> t1 = {{0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{2,6}};

    const vector<Edge> t2 = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{2,5} };
    const vector<Edge> t3 = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{2,5},{2,6} };
    const vector<Edge> t4 = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{2,9} };

    const vector<Edge> t5 = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{3,8} };
 // without circle and the vertices size is greater than 12
    const vector<Edge> t6 = { {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8}, {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11} ,{11,12},{12,13}};
    check_for_cycles(t1);
    check_for_cycles(t2);
    check_for_cycles(t3);
    check_for_cycles(t4); 
    check_for_cycles(t5);
    check_for_cycles(t6);*/
    cin.get();// to hang the app to see the result in the terminal (only if it is not run directly from the terminal)
    return 0;
}
