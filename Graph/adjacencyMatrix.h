//Weighted Undirected Graph => Adjacency Matrix
//Storing INT_MAX if path doesn't exist
//For an edge entered with weight not specified, 1 is the default weight
#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<stack>

using namespace std;

class comparatorForMinHeap{
	public:
	bool operator()(const pair<int,int> &a,const pair<int,int> &b){
		return (a.second > b.second); //Comparing Costs
	}
};

template<typename T>
class WeightedUndirectedGraph{
	vector<vector<int> > M;
	vector<T> V;

	int getVertexIndex(const T &el){
		for(int i=0;i<V.size();i++){
			if (V[i] == el)
				return i;
		}
		return -1;
	}

	public:
	WeightedUndirectedGraph() {}
	WeightedUndirectedGraph(const vector<T> &v) : V(v){
		M.resize(V.size());
		for(int i=0;i<V.size();i++)
			M[i].resize(V.size(),INT_MAX);
	}

	void addEdge(const T &src,const T &dest,int weight=1){ //By default, taking 1 as weight between 2 vertices, if an edge exists between them
		int s = getVertexIndex(src);
		int d = getVertexIndex(dest);
		if(s == -1){
			V.push_back(src);
			vector<int> vec;
			for(int i=0;i<M.size()+1;i++)
				vec.push_back(INT_MAX);
			for(int i=0;i<M.size();i++)
				M[i].push_back(INT_MAX);
			s = M.size();
			M.push_back(vec);
		}
		if(d == -1){
			V.push_back(dest);
			vector<int> vec;
			for(int i=0;i<M.size()+1;i++)
				vec.push_back(INT_MAX);
			for(int i=0;i<M.size();i++)
				M[i].push_back(INT_MAX);
			d = M.size();
			M.push_back(vec);
		}
		M[s][d] = weight;
	}

	void deleteEdge(const T &src, const T &dest){
		int s = getVertexIndex(src);
		int d = getVertexIndex(dest);
		if( s==-1 || d==-1){
			cout << "Edge Doesn't Exist Between " << src << " and " << dest << " (For Deletion)" << endl;
			return;
		}
		M[s][d] = INT_MAX;
	}

	void updateWeight(const T &src, const T &dest,int weight){
		int s = getVertexIndex(src);
		int d = getVertexIndex(dest);
		if( s==-1 || d==-1){
			cout << "Edge Doesn't Exist Between " << src << " and " << dest << " (For Updation)" << endl;
			return;
		}
		M[s][d] = weight;
	}

	vector<int> getAdjacentVerticesIndices(const T &el) const{
		int elIndex = getVertexIndex(el);
		vector<int> v;
		if(elIndex == -1)
			return v;
		const vector<int> &elVec = M[elIndex];
		for(int i=0;i<elVec.size();i++){
			if(elVec[i] >= INT_MAX)
				continue;
			v.push_back(i);
		}
		return v;
	}

	vector<int> getAdjacentVerticesIndices(int elIndex) const{
		vector<int> v;
		if(elIndex == -1)
			return v;
		const vector<int> &elVec = M[elIndex];
		for(int i=0;i<elVec.size();i++){
			if(elVec[i] >= INT_MAX)
				continue;
			v.push_back(i);
		}
		return v;
	}

	void BFS() const{
		if(V.empty())
			return;
		cout << "Breadth First Search: ";
		vector<bool> visited(V.size(),false);

		for(int i=0;i<V.size();i++){ //Required Because Graph Might Not Be Connected
			if(visited[i])
				continue;

			queue<int> Q;
			visited[i] = true;
			Q.push(i);
			while(!Q.empty()){
				int current = Q.pop();
				vector<int> adjacentVertices = getAdjacentVerticesIndices(V[current]);
				vector<int>::const_iterator adj = adjacentVertices.begin();
				for(;adj!=adjacentVertices.end();adj++){
					if(visited[*adj])
						continue;
					visited[*adj] = true;
					Q.push(*adj);
				}
				cout << V[current] << " ";
			}
		}
		cout << endl;
	}

	void isConnected() const{ //BFS Traversal
		if(V.empty())
			return;
		vector<bool> visited(V.size(),false);

		for(int i=0;i<V.size();i++){
			if(visited[i])
				continue;
			if(i>0)
				return false;  //Graph Not Connected

			queue<int> Q;
			visited[i] = true;
			Q.push(i);
			while(!Q.empty()){
				int current = Q.pop();
				vector<int> adjacentVertices = getAdjacentVerticesIndices(V[current]);
				vector<int>::const_iterator adj = adjacentVertices.begin();
				for(;adj!=adjacentVertices.end();adj++){
					if(visited[*adj])
						continue;
					visited[*adj] = true;
					Q.push(*adj);
				}
			}
		}
		return true;
	}

	vector<vector<T> > findAllConnectedComponents() const{
		vector<vector<T> > allComp;
		if(V.empty())
			return  allComp;
		vector<bool> visited(V.size(),false);

		for(int i=0;i<V.size();i++){
			if(visited[i])
				continue;
			
			//After i>0 if it escapes the above if condition, then there exist multiple connected components
			//and for this iteration, new connected comp is being iterated upon
			vector<T> component;

			queue<int> Q;
			visited[i] = true;
			Q.push(i);
			while(!Q.empty()){
				int current = Q.pop();
				vector<int> adjacentVertices = getAdjacentVerticesIndices(V[current]);
				vector<int>::const_iterator adj = adjacentVertices.begin();
				for(;adj!=adjacentVertices.end();adj++){
					if(visited[*adj])
						continue;
					visited[*adj] = true;
					Q.push(*adj);
				}
				component.push_back(V[current]);
			}
			allComp.push_back(component);
		}
		return allComp;
	}

	private:
	void DFSHelper (int current,vector<bool> &visited) const{
		cout << V[current] << " ";
		vector<int> adjacentVertices = getAdjacentVerticesIndices(V[current]);
		vector<int>::const_iterator adj = adjacentVertices.begin();
		for(;adj!=adjacentVertices.end();adj++){
			if(visited[*adj])
				continue;
			visited[*adj] = true;
			DFSHelper(*adj,visited);
		}
	}

	public:
	void DFS() const{
		if(V.empty())
			return;
		cout << "Depth First Search: ";
		vector<bool> visited(V.size(),false);
		
		for(int i=0;i<V.size();i++){
			visited[i] = true;
			DFSHelper(i,visited);
		}
	}

	private:
	void dijkstra(priority_queue<pair<int,int> > &PQ,vector<int> &pi,vector<int> &D) const{
		vector<bool> poppedFromPQ(V.size(),false);
		while(!PQ.empty()){
			pair<int,int> temp = PQ.top();
			PQ.pop();
			int current = temp.first;
			D[current] = temp.second;
			poppedFromPQ[current] = true;
			
			vector<int> adjacentVertices = getAdjacentVerticesIndices(current);
			vector<int>::const_iterator adj = adjacentVertices.begin();
			for(;adj!=adjacentVertices.end();adj++){
				if(poppedFromPQ[*adj]) // If Vertex Is Popped From Priority Queue, We'll Continue
					continue;

				//Relaxation
				if( (D[current]+M[current][*adj]) < D[*adj]){
					D[*adj] = D[current]+M[current][*adj];
					pi[*adj] = current;
				}
			}
		}
	}

	public:
	void fillShortestPathInStack(const T &src,const T &dest,stack<T> &shortestPath) const{
		if(V.size() == 0)
			return;
		int s = getVertexIndex(src);
		if(s == -1)
			return;
		int d = getVertexIndex(dest);
		if(d == -1)
			return;
		
		//Using Dijkstra's Algorithm
		
		//Initialising
		vector<int> pi(V.size(),-1); //No Preceding Vertices Initially
		vector<int> D(V.size(),INT_MAX); //Initial Costs Will Be Infinity(From Source) Except For Source(0)
		D[s] = 0;
		priority_queue <pair<int,int>,vector<int,int>,comparatorForMinHeap()> PQ; // pair=> Vertex,Cost
		for(int i=0;i<V.size();i++){
			if(i==s)
				PQ.push(make_pair(i,0));
			else
				PQ.push(make_pair(i,INT_MAX));
		}
		dijkstra(PQ,pi,D);
		
		int index = d;
		while(index != s){
			if(index == -1){
				if(!shortestPath.empty())
					shortestPath.swap(stack<T>); //Clearing By Swapping Stack With Empty Stack
				return;
			}
			shortestPath.push(V[index]);
			index = pi[index];
		}
		shortestPath.push(V[s]);
	}

	void printShortestPath(const T &src, const T &dest) const{
		if(V.size() == 0)
			return;
		stack<T> shortestPath;
		fillShortestPathInStack(src,dest,shortestPath);
		cout << "Shortest Path: ";
		if(!shortestPath.empty())
			cout << "N/A";
		while(!shortestPath.empty())
			cout << shortestPath.pop() << " ";
		cout << endl;
	}
};

#endif
