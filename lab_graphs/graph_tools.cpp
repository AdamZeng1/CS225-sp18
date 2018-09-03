/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::min
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
	/*
	//TODO: YOUR CODE HERE
	int edge_min;
	bool initial = false;
	Edge ret;
	vector<Edge> edgeset = graph.getEdges();
	//vector<bool> visited_vec(edgeset.size(),false); 
	//Edge out = BFS(graph, graph.getStartingVertex());
	for (auto & edge : edgeset)
	{
		if (!initial) {
			initial = true;
			edge_min = graph.getEdgeWeight(edge.source, edge.dest);
			ret = edge;
		}
		else {
			if (graph.getEdgeWeight(edge.source, edge.dest) < edge_min) {
				edge_min = graph.getEdgeWeight(edge.source, edge.dest);
				ret = edge;
			}	
		}
	}
	ret = graph.setEdgeLabel(ret.source, ret.dest, "MIN");
	*/
	Edge out = BFS(graph, graph.getStartingVertex());
	return out.getWeight();
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
	//TODO: YOUR CODE HERE
	vector<Vertex> vertex_set = graph.getVertices();
	unordered_map<Vertex,int> distance_map;
	distance_map[start] = 0;
	unordered_map<Vertex,Vertex> parent_map;
	parent_map[start] = start;
	unordered_map<Vertex,bool> visited_map;
	for (auto & vertex : vertex_set)
	{
		visited_map[vertex] = false;
	}
	queue<Vertex> q;
	visited_map[start] = true;
	q.push(start);
	while (!q.empty())
	{
		Vertex v = q.front();
		q.pop();
		for (auto & neigh : graph.getAdjacent(v)) {
			// visited
			if (visited_map[neigh] == false)
			{
				visited_map[neigh] = true;
				q.push(neigh);
				distance_map[neigh] = distance_map[v] + 1;
				parent_map[neigh] = v;
			}
			// unvisitd
		}
	}
	Vertex vertex_lablel = end;
	while (parent_map[vertex_lablel]!=vertex_lablel)
	{
		Edge ret = graph.getEdge(vertex_lablel,parent_map[vertex_lablel]);
		ret = graph.setEdgeLabel(ret.source, ret.dest, "MINPATH");
		vertex_lablel = parent_map[vertex_lablel];
	}
	return distance_map[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
	//TODO: YOUR CODE HERE
	vector<Edge> edgeset = graph.getEdges();
	std::sort(edgeset.begin(),edgeset.end());
	DisjointSets dsets;
	//map Vertex to index
	unordered_map<Vertex,int> map;
	int index = 0;
	vector<Vertex> vertex_vec = graph.getVertices();
	for (auto & vertex : vertex_vec) {
		map[vertex] = index;
		index++;
	}
	// add vertexs into the disjointset
	dsets.addelements(vertex_vec.size());
	//choose edges
	int set_number = vertex_vec.size();
	int i = 0;
	while (set_number>1) {
		Vertex v1 = edgeset[i].source;
		Vertex v2 = edgeset[i].dest;
		int index_v1 = map[v1];
		int index_v2 = map[v2];
		if (dsets.find(index_v1) != dsets.find(index_v2)) {
			set_number--;
			dsets.setunion(index_v1, index_v2);
			Edge ret = graph.setEdgeLabel(v1, v2, "MST");
		}
		i++;
	}

}

Edge GraphTools::BFS(Graph& graph, Vertex start)
{
	int edge_min;
	bool initial = false;
	Edge ret;
	vector<Vertex> vertex_vec = graph.getVertices();
	unordered_map<Vertex,bool> visited_map;
	for (auto & vertex : vertex_vec)
	{
		visited_map[vertex] = false;
	}
	queue<Vertex> q;
	visited_map[start] = true;
	q.push(start);
	while (!q.empty())
	{
		Vertex v = q.front();
		q.pop();
		for (auto & neigh : graph.getAdjacent(v)) {
			// visited
			if (visited_map[neigh] == false)
			{
				visited_map[neigh] = true;
				q.push(neigh);
				// set edge_min
				if (!initial) {
					initial = true;
					edge_min = graph.getEdgeWeight(v, neigh);
					ret = graph.getEdge(v,neigh);
				}
				else {
					if (graph.getEdgeWeight(v, neigh) < edge_min) {
						edge_min = graph.getEdgeWeight(v, neigh);
						ret = graph.getEdge(v,neigh);
					}
				}
			// label edge
			Edge visit = graph.setEdgeLabel(v, neigh, "DISCOVERY");
			}
			// unvisited
			else {
				// set edge_min
				if (!initial) {
					initial = true;
					edge_min = graph.getEdgeWeight(v, neigh);
					ret = graph.getEdge(v,neigh);
				}
				else {
					if (graph.getEdgeWeight(v, neigh) < edge_min) {
						edge_min = graph.getEdgeWeight(v, neigh);
						ret = graph.getEdge(v,neigh);
					}
				}
				Edge visit = graph.setEdgeLabel(v, neigh, "UNEXPLORED");
			}
		}
	}
	ret = graph.setEdgeLabel(ret.source, ret.dest, "MIN");
	return ret;
}