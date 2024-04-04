#include <stdio.h>
#include <stdlib.h>


// Find set of an element i (uses path compression technique)
int comp(const void* a, const void* b){
    return ((int*)a)[2]-((int*)b)[2];
}
int findparent(int parent[], int node) {
    int par = parent[node];
    
    if(par==node){
        return node;
        
    }
    return findparent(parent, par);
    
    
}
// A function that does union of two sets of x and y (uses union by rank)
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

int kruskalMST(int n, int m, int graph[][3]) {
    int parent[n+1];
    int rank[n+1];
    int ans =0;
    for (int i =0; i<=n; i++){
        parent[i]=i;
        rank[i]=0;
    }
    
    qsort((void*)graph, m, sizeof(graph[0]), comp);

    for(int i = 0; i < m; i++){
        if(findparent(parent,graph[i][0]) != findparent(parent,graph[i][1])){
            ans += graph[i][2];
            unionSets(parent,rank,graph[i][0],graph[i][1]);
        }
    }
    return ans;

}


int main() {
    // File pointers for input and output files
    FILE *inputFile, *outputFile;
    
    // Open input file in read mode
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    
    // Open output file in write mode
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    
    // Read n and m from input file
    int n, m;
    fscanf(inputFile, "%d %d", &n, &m);
    
    // Read graph from input file
    int graph[m][3];
    for (int i = 0; i < m; ++i) {
        fscanf(inputFile, "%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    }
    
    // Call Kruskal's MST algorithm
    int result = kruskalMST(n, m, graph);
    
    // Write result to output file
    fprintf(outputFile, "%d\n", result);
    
    // Close input and output files
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}
