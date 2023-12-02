package src.kruskalAlgorithm;

import java.util.ArrayList;
import java.util.Comparator;

import src.kruskalAlgorithm.kruskalEdge.KruskalEdge;

public class KruskalAlgorithm {
    public static ArrayList<KruskalEdge> kruskalMST(ArrayList<KruskalEdge> edges, int numVertices) {
        ArrayList<KruskalEdge> resultMST = new ArrayList<>();
        
        edges.sort(Comparator.comparingDouble(KruskalEdge::getWeight));
        
        int[] parent = new int[numVertices];
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
        }
        
        for (KruskalEdge edge : edges) {
            int rootSrc = find(parent, edge.getSrc());
            int rootDest = find(parent, edge.getDest());
            
            if (rootSrc != rootDest) {
                resultMST.add(edge);
                union(parent, rootSrc, rootDest);
            }
        }
        
        return resultMST;
    }

    private static int find(int[] parent, int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent, parent[vertex]);
        }
        return parent[vertex];
    }

    private static void union(int[] parent, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        parent[rootX] = rootY;
    }
}
