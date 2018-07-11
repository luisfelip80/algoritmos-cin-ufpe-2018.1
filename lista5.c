#include <stdio.h>
#include <stdlib.h>

typedef struct LISTA{//lista de adjacências. grafo
	int node;
	struct LISTA *next;
}lista;
typedef struct FILA{
	int node;
	struct FILA *next;
}fila;
fila *enqueue(fila *linha,int num){
	fila *novo,*cur=linha;
	if(linha==NULL){
		linha = (fila*)malloc(sizeof(fila));
		linha->node = num;
		linha->next = NULL;
		return linha;
	}
	else{
		while(cur->next!=NULL){
			cur=cur->next;
		}
		novo = (fila*)malloc(sizeof(fila));
		novo->node = num;
		novo->next = NULL;
		cur->next=novo;
		return linha;
	}
}
void *bfs(lista **grafo,int *p,int o){
	int i,u,val;
	int *resp=(int*)calloc(sizeof(int),3);	
	lista *e;
	fila *nova=NULL;
	
	if(p[o]==0){
		////printf(">>>%d\n",o);
		nova = enqueue(nova,o);
		p[o] = 1;
		////printf("%d - visitado\n",o);
		while(nova!=NULL){
			u=nova->node;
			nova=nova->next;
			////printf("u:%d\n",u);
			e = grafo[u];
			while(e!=NULL){
				val = e->node;
				////printf("val %d\n",val);
				if(p[val]==0){
					p[val] = 1;
					////printf("%d - visitado\n",val);
					nova = enqueue(nova,val);
					////printf("%d na fila\n", val);
				}
				e = e->next;
			}
			////printf("\n");	
		}	
	}
	return resp;
}

lista **adja(lista **marc,int a, int b){
	lista *aux, *cur=marc[a];
	if(marc[a]==NULL){
		aux = (lista*)malloc(sizeof(lista));
		aux->node = b;
		aux->next = NULL;
		marc[a] = aux;
		return marc;
	}
	else{
		while(cur->next !=NULL){
			cur=cur->next;
		}
		aux = (lista*)malloc(sizeof(lista));
		aux->node = b;
		aux->next = NULL;
		cur->next = aux;
		return marc;
	}
}
int main(){	
	int  salva,ponto=0,*res,n,r,c,i,j,k,ant=0,u,*p,v,l,val=0,a,b,caso=0,marcador, **node;
	char **jogo,play2,win,aux,play,entrada[102],lin[100],col[100];
	no *grafo_nos=NULL;
	lista **list=NULL,*cur;
	fila *fila_A=NULL;
	res = (int*)malloc(sizeof(int));
	res[0]=0;
	scanf("%d",&n);
	p = (int*)malloc(sizeof(int)*n); // vetor 
	list = (lista**)malloc(sizeof(lista*));
	
		for(i=0;i<n;i++){
			if(ant!=n){
				jogo[i]=(char*)calloc(sizeof(char),n);
				node[i] = (int*)calloc(sizeof(int),n);
			}
			for(j=0;j<n;j++){
				jogo[i][j]=' ';
				node[i][j] = val;
				list[val]=NULL;
				p[val]=1;
				val++;
			}
		}
		//printf("a\n");
		scanf(" %c\n",&play);
		if(play == 'W'){
			play2 = 'B';
		}
		else
			play2='W';
		//printf("b\n");
		while(fgets(entrada,100,stdin),entrada[0]!='\n'){
			//printf("c\n");
			for(i=0;entrada[i]!=32;i++){
				lin[i]=entrada[i];
			}
			lin[i]='\0';
			j=0;
			for(i++;entrada[i]!='\0';i++,j++){
				col[j]=entrada[i];
			}
			col[j]='\0';
			r=atoi(lin);
			c=atoi(col);
			jogo[r][c] = play;
			//printf("d\n");
			if(r == 0 && play == 'W'){
				//printf("w em 0");
				//printf("[%c][%d][%d]\n", jogo[r][c],r,c);
			}
			else if(c == 0 && play == 'B'){
				//printf("b em 0 ");
				//printf("[%c][%d][%d]\n", jogo[r][c],r,c);
			}
			if(r-1 >= 0){
				if(jogo[r-1][c]==play){// linha acima.
					//printf("1\n");
					u = node[r][c];
					v = node[r-1][c];
					p[u]=0;
					p[v]=0;
					adja(list,u,v);
					adja(list,v,u);
					grafo_nos[u].lin = r;
					grafo_nos[u].col = c;
					grafo_nos[v].lin = r-1;
					grafo_nos[v].col = c;

				}
				if(c+1<n){
					if(jogo[r-1][c+1]==play){//diagonal direita acima.
						//printf("2\n");
						u = node[r][c];
						v = node[r-1][c+1];
						//printf("ol\n");
						p[u]=0;
						p[v]=0;
						adja(list,u,v);
						adja(list,v,u);
						grafo_nos[u].lin = r;
						grafo_nos[u].col = c;
						grafo_nos[v].lin = r-1;
						grafo_nos[v].col = c+1;
					}
				}
			}
			if(r+1 < n){
				if(jogo[r+1][c]==play){// linha abaixo.
					//printf("3\n");
					u = node[r][c];
					v = node[r+1][c];
					p[u]=0;
					p[v]=0;
					adja(list,u,v);
					adja(list,v,u);
					grafo_nos[u].lin = r;
					grafo_nos[u].col = c;
					grafo_nos[v].lin = r+1;
					grafo_nos[v].col = c;
				}
				if(c-1>=0){
					if(jogo[r+1][c-1]==play){//diagonal esquerda abaixo.
						//printf("4\n");
						u = node[r][c];
						v = node[r+1][c-1];
						p[u]=0;
						p[v]=0;
						//printf("4a\n");
						adja(list,u,v);
						//printf("4b\n");
						adja(list,v,u);
						//printf("4c\n");
						grafo_nos[u].lin = r;
						grafo_nos[u].col = c;
						grafo_nos[v].lin = r+1;
						grafo_nos[v].col = c-1;
					}
				}
			}
			if(c-1 >= 0){
				if(jogo[r][c-1]==play){//esquerda.
					//printf("5\n");
					u = node[r][c];
					v = node[r][c-1];
					p[u]=0;
					p[v]=0;
					adja(list,u,v);
					adja(list,v,u);
					grafo_nos[u].lin = r;
					grafo_nos[u].col = c;
					grafo_nos[v].lin = r;
					grafo_nos[v].col = c-1;
				}
			}
			if(c+1 < n){
				if(jogo[r][c+1]==play){//direita.
					//printf("6\n");
					u = node[r][c];
					v = node[r][c+1];
					p[u]=0;
					p[v]=0;
					adja(list,u,v);
					adja(list,v,u);
					grafo_nos[u].lin = r;
					grafo_nos[u].col = c;
					grafo_nos[v].lin = r;
					grafo_nos[v].col = c+1;
				}
			}
			//printf("e\n");
			aux = play;
			play = play2;
			play2 = aux;
		}
		for(i=0;i<n;i++){
			if(jogo[i][0]=='B'){
				//printf("mande b\n");
				if(p[node[i][0]]==0){
					res = bfs(list,grafo_nos,p);
				}
			}
			if(res[0]==1){
				ponto=1;
				salva=res[1];
				win = 'B';
				break;
			}
		}
		for(i=0;i<n && ponto == 0;i++){
			if(jogo[0][i]=='W' ){
				//printf("mande w\n");
				if(p[node[0][i]]==0){
					res = bfs(list,grafo_nos,p,node[0][i],'W',n);
				}
			}
			if(res[0]==1){
				ponto=1;
				salva=res[1];
				win='W';
				break;
			}
		}
		res[0]=0;
		if(ponto==1){
			ponto=0;
			printf("%c %d\n\n",win,salva);
		}
		ant=n;
	}
	return 0;
}