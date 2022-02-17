#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    int vertexid = findVertexId(vertexName);
	
	if (vertexid != -1) throw DuplicateVertexNameException();
	
	else{
		struct GraphVertex newvertex;
		newvertex.name = vertexName;
		newvertex.edgeCount = 0;
		
		vertexList.push_back(newvertex);
	}
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
	if (fromVertexName == toVertexName) return false;
	
	int fromvertexid = findVertexId(fromVertexName), tovertexid = findVertexId(toVertexName);
	
	if (fromvertexid == -1 || tovertexid == -1) throw VertexNotFoundException();
	
	else if ((vertexList[fromvertexid]).edgeCount == MAX_EDGE_PER_VERTEX || (vertexList[tovertexid]).edgeCount == MAX_EDGE_PER_VERTEX) throw TooManyEdgeOnVertexExecption();
	
	else{
		
		int edgeid = findEdgeId(fromvertexid, tovertexid);
		
		if (edgeid != -1) return false;
		
		else{
			struct GraphEdge newedge;
			newedge.weight = weight;
			newedge.masked = false;
			newedge.vertexId0 = fromvertexid;
			newedge.vertexId1 = tovertexid;
			
			edgeList.push_back(newedge);
			
			(vertexList[fromvertexid].edgeIds)[vertexList[fromvertexid].edgeCount] = edgeList.size()-1;
			vertexList[fromvertexid].edgeCount++;
			
			(vertexList[tovertexid].edgeIds)[vertexList[tovertexid].edgeCount] = edgeList.size()-1;
			vertexList[tovertexid].edgeCount++;
			
			return true;
		}
	}
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    unsigned int fromvertexid = findVertexId(from), tovertexid = findVertexId(to);
    
    if (fromvertexid == -1 || tovertexid == -1) throw VertexNotFoundException();
    
    else{
    	
    	std::priority_queue<struct DistanceVertexIdPair> minheap;
    	struct DistanceVertexIdPair temppair(fromvertexid, 0);
    	
    	// Initialize vectors previous, distances and marked
    	
		std::vector<int> previous;
    	previous.resize(vertexList.size());
    	previous[fromvertexid] = -1;
    	
    	std::vector<int> distances;
    	distances.resize(vertexList.size());
    	distances[fromvertexid] = 0;
    	
    	std::vector<int> marked;
    	marked.resize(vertexList.size(), 0);
		
		unsigned int i = 0;
    	
    	minheap.push(temppair);
		
		while (i < vertexList.size()){
    		
    		if (i == fromvertexid){
    			i++;
    			continue;
			}
    		
    		else{
    			struct DistanceVertexIdPair newpair(i, LARGE_NUMBER);
    			minheap.push(newpair);
    			distances[i] = LARGE_NUMBER;
    			i++;
			}	
		}
    	
    	// Dijkstra's Shortest Path Algorithm with Minheap
    	
    	while (!minheap.empty()){
    		
    		struct DistanceVertexIdPair dvidpair = minheap.top();
    		minheap.pop();
    		struct GraphVertex poppedvertex = vertexList[dvidpair.vId];
    		
    		marked[dvidpair.vId] = 1;
    		
    		int j = 0;
    		
    		while (j < poppedvertex.edgeCount){
    			
    			struct GraphEdge edge = edgeList[poppedvertex.edgeIds[j]];
    			
    			if (edge.masked){
    				j++;
    				continue;
				}
    			
    			else{
    				
    				int othervertexid;
					int dist = dvidpair.currentWeight + edge.weight;
    				
					if (edge.vertexId0 == dvidpair.vId) othervertexid = edge.vertexId1;
					else othervertexid = edge.vertexId0;
					
					if (marked[othervertexid] == 1){
						j++;
						continue;
					}
    				
    				else if (dist < distances[othervertexid]){
    					
    					distances[othervertexid] = dist;
    					previous[othervertexid] = dvidpair.vId;
    					
    					struct DistanceVertexIdPair lessweightpair(othervertexid, dist);
    					minheap.push(lessweightpair);
    					
    					j++;
					}
					
					else{
						
						j++;
						continue;
					}
				}
			}	
		}
	    // Check if there is a path from fromvertexid to tovertexid by looking at marked vector
        // There is a path, fromvertex and tovertex are connected
        if (marked[tovertexid] == 1){
    	
    	    // Vector to store shortest path in reverse manner
		
		    std::vector<int> reversepath;
		    int previousid = tovertexid;
		
    	    reversepath.push_back(previousid);
    	
    	    while (previous[previousid] != -1){
    		    previousid = previous[previousid];
    		    reversepath.push_back(previousid);
		    }
		    // Fill the orderedVertexIdList with the opposite way of reversepath
		    while (!reversepath.empty()){
			    orderedVertexIdList.push_back(reversepath.back());
			    reversepath.pop_back();
		    }
		
		    return true;
    	
	    }
	    // There is no path, fromvertex and tovertex are not connected
	    else return false;
    }
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    unsigned int fromvertexid = findVertexId(from), tovertexid = findVertexId(to);
    
    if (fromvertexid == -1 || tovertexid == -1) throw VertexNotFoundException();
    
    else{
    	
    	UnMaskAllEdges();
    	std::vector<int> lastfoundpath;
    	
    	// There is at least one path from "from" to "to"
		if (ShortestPath(lastfoundpath, from, to) == true){
    		
    		int i = 1;
    		orderedVertexIdList.push_back(lastfoundpath);
    		
    		while (i < numberOfShortestPaths){
				
				int j = 0;
    			int maxweightedgeid = findEdgeId(lastfoundpath[0], lastfoundpath[1]);
    			
    			// Find the edge id of the edge with maximum weight on the path
				while (j < lastfoundpath.size() - 1){
    				
    				if (edgeList[findEdgeId(lastfoundpath[j], lastfoundpath[j+1])].weight > edgeList[maxweightedgeid].weight){
    					maxweightedgeid = findEdgeId(lastfoundpath[j], lastfoundpath[j+1]);
					}
					j++;
				}
    			
    			// Mask the edge with the maximum weight on the path
				edgeList[maxweightedgeid].masked = true;
				
				lastfoundpath.clear();
				
				if (ShortestPath(lastfoundpath, from, to) == true){
					
					orderedVertexIdList.push_back(lastfoundpath);
					i++;
				}
				
				else break;
			}
			
			UnMaskAllEdges();
			return i;
		}
		// There is no path
		else return 0;
	}
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    unsigned int i = 0;
    
    while (i < vertexNames.size()){
    	
		StringPair pair = vertexNames[i];
    	int vertex0id = findVertexId(pair.s0), vertex1id = findVertexId(pair.s1);
		
		if (vertex0id == -1 || vertex1id == -1) throw VertexNotFoundException();
		
		else{
			
			int edgeid = findEdgeId(vertex0id, vertex1id);
			
			if (edgeid != -1){
				
				edgeList[edgeid].masked = true;
			}
		}
		i++;
	}
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    unsigned int i = 0;
    
    while (i < vertexNames.size()){
    	
		StringPair pair = vertexNames[i];
    	int vertex0id = findVertexId(pair.s0), vertex1id = findVertexId(pair.s1);
		
		if (vertex0id == -1 || vertex1id == -1) throw VertexNotFoundException();
		
		else{
			
			int edgeid = findEdgeId(vertex0id, vertex1id);
			
			if (edgeid != -1){
				
				edgeList[edgeid].masked = false;
			}
		}
		i++;
	}
}

void Graph::UnMaskAllEdges()
{
    unsigned int i = 0;
    
    while (i < edgeList.size()){
    	
		edgeList[i].masked = false;
		i++;
	}
}

void Graph::MaskVertexEdges(const std::string& name)
{
    int vertexid = findVertexId(name);
    
    if (vertexid == -1) throw VertexNotFoundException();
    
    else{
    	
    	int edgenum = vertexList[vertexid].edgeCount, i = 0;
    	
    	while (i < edgenum){
    		
    		edgeList[(vertexList[vertexid].edgeIds)[i]].masked = true;
    		i++;
		}
	}
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    int vertexid = findVertexId(name);
    
    if (vertexid == -1) throw VertexNotFoundException();
    
    else{
    	
    	int edgenum = vertexList[vertexid].edgeCount, i = 0;
    	
    	while (i < edgenum){
    		
    		edgeList[(vertexList[vertexid].edgeIds)[i]].masked = false;
    		i++;
		}
	}
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    int v0id = findVertexId(vName0), v1id = findVertexId(vName1);
    
    if (v0id == -1 || v1id == -1) throw VertexNotFoundException();
    
    else{
    	int edgeid = findEdgeId(v0id, v1id);
    	
    	if (edgeid != -1){
    		edgeList[edgeid].weight = newWeight;
		}
	}
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    int edgeid = findEdgeId(vId0, vId1);
    
    if (edgeid != -1){
    	edgeList[edgeid].weight = newWeight;
	}
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return (int)vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return (int)edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    if (vertexId >= 0 && vertexId < vertexList.size()){
    	return vertexList[vertexId].name;
	}
	
	else return "";
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    unsigned int i = 0;
    int total_weight = 0;
    
    while (i < orderedVertexIdList.size()){
			
    	if (i == orderedVertexIdList.size() - 1){
    		break;
		}
		
		else{
			int fromvertexid = orderedVertexIdList[i], tovertexid = orderedVertexIdList[i+1];
    	
    		if (fromvertexid < 0 || fromvertexid >= vertexList.size() || tovertexid < 0 || tovertexid >= vertexList.size()){
    			throw VertexNotFoundException();
			}
			
			int edgeid = findEdgeId(fromvertexid, tovertexid);
			
			if (edgeid == -1){
				return -1;
			}
			
			else{
				total_weight += edgeList[edgeid].weight;
			}
		}
		
		i++;	
	}
	return total_weight;
}

int Graph::findVertexId(const std::string& vertexName) const
{
	int vertexid = -1;
	unsigned int i = 0;
	
	while (i < vertexList.size()){
		
		if (vertexList[i].name == vertexName){
			
			vertexid = i;
			break;
		}
		
		i++;
	}
	
	return vertexid;
}

int Graph::findEdgeId(int v0id, int v1id) const
{
	int edgeid = -1;
	unsigned int i = 0;
	
	while (i < edgeList.size()){
		
		if ((edgeList[i].vertexId0 == v0id && edgeList[i].vertexId1 == v1id) || (edgeList[i].vertexId1 == v0id && edgeList[i].vertexId0 == v1id)){
			
			edgeid = i;
			break;
		}
		
		i++;
	}
	
	return edgeid;
}
