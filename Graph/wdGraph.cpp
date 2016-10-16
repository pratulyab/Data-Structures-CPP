#include "wdGraph.h"

int main(){
	
	wdGraph<int> G;
	/*
	G.addEdge(0,1,0);
	G.addEdge(0,4,0);
	G.addEdge(1,2,0);
	G.addEdge(1,3,INT_MAX);
	G.addEdge(1,4,0);
	G.addEdge(2,3,0);
	G.addEdge(3,4,INT_MAX);
	*/
	
	G.addEdge(1,2,8);
	G.addEdge(1,4,1);
	G.addEdge(2,3,1);
	G.addEdge(3,1,4);
	G.addEdge(4,2,2);
	G.addEdge(4,3,9);
	
	cout << G;
	vector<vector<int> > M = G.getAdjacencyMatrix();

	for(int i=0;i<M.size();i++){
		for(int j=0;j<M.size();j++){
			if(M[i][j] == INT_MAX)
				cout << "N ";
			else
				cout << M[i][j] << " ";
		}
		cout << endl;
	}

	vector<int> V = G.getVerticesInAscendingOrder();
	for(int i=0;i<V.size();i++)
		cout << V[i] << " ";
	cout << endl;

return 0;
}
