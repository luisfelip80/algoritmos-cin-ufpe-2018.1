#include <iostream>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Grafo{
private:
	int V;
	list<pair<int, int> > * adj;

public:

	Grafo(int V){
		this->V = V;
		adj = new list<pair<int, int> >[V];
	}
	void addAresta(int v1, int v2, int custo){
		adj[v1].push_back(make_pair(v2, custo));
	}

	int *dijkstra(int orig){
		int *dist = new int[V];
		int visitados[V];
		priority_queue < pair<int, int>,
		vector<pair<int, int> >, greater<pair<int, int> > > pq;

		for(int i = 0; i < V; i++){
			dist[i] = INFINITO;
			visitados[i] = false;
		}
		dist[orig] = 0;
		pq.push(make_pair(dist[orig], orig));
		while(!pq.empty()){
			pair<int, int> p = pq.top();
			int u = p.second;
			pq.pop();
			if(visitados[u] == false){
				visitados[u] = true;

				list<pair<int, int> >::iterator it;
				for(it = adj[u].begin(); it != adj[u].end(); it++){
					int v = it->first;
					int custo_aresta = it->second;
					if(dist[v] > (dist[u] + custo_aresta)){
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		return dist;
	}
};

int main(){	
	int  n,m,u,v,d, *conec,*dijk;
	int i,j,k,l,val,a,b,con=0,marcador;
	int *dist;
	while(scanf("%d %d",&n,&m)!=EOF){

		Grafo g(n);
		int *conec = new int[n];
		for(i=0;i<n;i++){
			conec[i]=0;
		}
		for(i=0;i<m;i++){
			scanf("%d %d %d",&u,&v,&d);
			g.addAresta(u,v,d);
			conec[u]++;
			g.addAresta(v,u,d);
			conec[v]++;			
		}
		for(i=0;i<n;i++){
			if(conec[i]>2 || conec[i]==1){
				break;
			}
		}
		cout<<"caso "<<con<<'\n';
		dijk = g.dijkstra(i);
		marcador=0;
		for(k=0; k < n;k++){
			if(marcador == 0 && (conec[k]>2 || conec[k]==1)){
				cout << dijk[k];
				marcador=1;
			}
			else if(marcador == 1 && (conec[k]>2 || conec[k]==1)){
				cout<<' '<< dijk[k];
			}
		}
		cout<<"\n\n";
		getc(stdin);
		con++;	
		n=0;
		m=0;
	}
	return 0;
}