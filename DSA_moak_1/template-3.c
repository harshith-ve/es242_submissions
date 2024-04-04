#include <stdio.h>
#include <stdlib.h>

int findParent(int parent[], int node) {
    int par = parent[node];
    
    if(par==node){
        return node;
        
    }
    return findparent(parent, par);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rx = findparent(parent, x);
    int ry = findparent(parent, y);
    if( rank[rx]>rank[ry]){
        parent[ry] = rx;
    }else{
        parent[rx] = ry;
        if(rank[rx] ==  rank[ry]){
            rank[ry]+=1;
        }
    }
}

int number_of_provinces(int parent[], int n) {
    
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int n, m; // Number of nodes and edges
    fscanf(inputFile, "%d %d", &n, &m);

    // Initialize parent and rank arrays
    int parent[n];
    int rank[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Read edges and union corresponding sets
    for (int i = 0; i < m; i++) {
        int a, b;
        fscanf(inputFile, "%d %d", &a, &b);
        unionSets(parent, rank, a, b);
    }

    // Count the number of connected components
    int provinces = number_of_provinces(parent, n);

    fprintf(outputFile, "%d\n", provinces);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
