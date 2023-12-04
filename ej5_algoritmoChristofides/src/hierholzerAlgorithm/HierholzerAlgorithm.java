package src.hierholzerAlgorithm;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Stack;

import src.hierholzerAlgorithm.hierholzerEdge.HierholzerEdge;

public class HierholzerAlgorithm {
 
    public static ArrayList<HierholzerEdge> hierholzer(ArrayList<HierholzerEdge> edges) {
        Map<Integer, List<HierholzerEdge>> graph = new HashMap<>();
        Stack<Integer> stack = new Stack<>();
        ArrayList<HierholzerEdge> eulerianPath = new ArrayList<>();

        for (HierholzerEdge edge : edges) {
            graph.putIfAbsent(edge.getSrc(), new ArrayList<>());
            graph.get(edge.getSrc()).add(edge);
        }

        stack.push(edges.get(0).getSrc());
        while (!stack.isEmpty()) {
            int current = stack.peek();
            if (graph.containsKey(current) && !graph.get(current).isEmpty()) {
                HierholzerEdge nextEdge = graph.get(current).remove(0);
                stack.push(nextEdge.getDest());
                eulerianPath.add(nextEdge);
            } else {
                stack.pop();
            }
        }

        return eulerianPath;
    }   

}
