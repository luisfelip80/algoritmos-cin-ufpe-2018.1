#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam 1000 

struct Node{
	char nome[tam];
	struct Node *prox;
};

struct Head{
	char title[tam];
	struct Node *prox;
	struct Head *next;
};

typedef struct Head head;
typedef struct Node node;

int t,t1,t2,lisPosi=0,play=0,nxt=0;
char playL[20][tam];
node *rep;
node *cursor;
head *cabeca;

node *matrix(char title[tam]){
	
	head *novaLista = (head*) malloc(sizeof(head));
	node *novoSentinela = (node *) malloc (sizeof(node));
	head *cur=cabeca;
	while(cur->next != NULL){
		cur=cur->next;
	}
	strcpy(novaLista->title,title);
	cur->next=novaLista;
	novaLista->next=NULL;
	novaLista->prox=novoSentinela;
	novoSentinela -> prox = NULL;
	
	return novoSentinela;
}
node *lists(char nome[tam]){
	head *cur=cabeca;
	while(cur!=NULL){
		if(strcmp(cur->title,nome)==0){
			return cur->prox;
		}
		cur=cur->next;
	}
	return matrix(nome);
}
node *search(node *lista, char musica[tam]){
	node *cur = lista;
	node *ant = cur;
	t=0;
	while (cur!=NULL){
		ant=cur;
		cur=cur->prox;
		if(cur!=NULL){
			if(strcmp(cur->nome,musica)==0)
				return ant;
		}
	}
	//printf(" %p %s %s\n", ant, ant->nome, cur->nome);
	return NULL;
}
void initialize(){
	
	cabeca=(head *) malloc (sizeof(head));
	strcpy(cabeca->title,"epilef");
	cabeca->prox=NULL;
	cabeca->next=NULL;
	rep=(node *) malloc (sizeof(node));
	rep->prox=NULL;
}
void add(node *lista, char nome[tam]){
	node *cur=lista;
	node *novo=(node *) malloc(sizeof(node));
	
	strcpy(novo->nome,nome);
	novo->prox = NULL;
	
	if(cur->prox==NULL){
		lista -> prox = novo;
	}
	else{
		
		while(cur->prox != NULL){
			cur = cur->prox;
		}
		cur->prox = novo;
	}
}
void del (node *lista, char nome[tam]){
	int i;
	node *cur = search(lista,nome);
	node *musica_anterior = cur;
	node *musica_procurada = cur->prox;
	cur=musica_procurada->prox;//cur vai para musica após a produrada.
	musica_anterior->prox = cur;//musica anterior à procurada aponta para a música após ela. 
	free(musica_procurada);
}
void swap (node *lista, char nome1[tam], char nome2[tam]){

	char nome[tam];
	node *musica_1 = search(lista, nome1);
	node *musica_2 = search(lista, nome2);	
	musica_1=musica_1->prox;
	musica_2=musica_2->prox;
	strcpy(nome,musica_1->nome);
	strcpy(musica_1->nome,musica_2->nome);
	strcpy(musica_2->nome,nome);	
}
void show(node *lista){
	node *cur = lista;
	printf("\n");
	while (cur!= NULL){
		printf("%s %p\n",cur->nome,cur);
		cur=cur->prox;
	}
	printf("\n");
}
void copy(node *recp, node *lista){
	node *cur = lista->prox;
	node *seta = recp;
	while(cur!=NULL){
		add(seta,cur->nome);
		cur=cur->prox;
	}
}
void Free(node *lista){
	if(lista->prox!=NULL){
		node *pNode,*at;
		
		at = lista->prox;
		while(at != NULL){
			pNode = at->prox;
			free(at);
			at = pNode;
		}
	}
}
void choice(char comm[tam]){
	int i,j=0;
	char list[tam],music1[tam],music2[tam];
	FILE *arq;
	node *cur;
	
	if(comm[0]=='P' && comm[2] == 'V' ){
		if(cursor!=rep && cursor != rep->prox && cursor!=NULL){
			cursor = search(rep,cursor->nome);
		}
		else if(cursor==NULL){
			cursor=rep;
			while(cursor->prox!=NULL)
				cursor=cursor->prox;

		}
	}
	else if(strcmp(comm,"NXT")==0){
		
		if(cursor!= NULL && cursor->prox == NULL && strcmp(cursor->nome,"elEx1sasfd")!=0){
			add(rep, "elEx1sasfd");
			cursor=cursor->prox;
		}

		else if(cursor!= NULL && strcmp(cursor->nome,"elEx1sasfd")!=0){
			cursor=cursor->prox;
		}
	}
	else if(strcmp(comm,"CLR")==0){
		Free(rep);
		rep=(node*)malloc(sizeof(node));
		rep->prox=NULL;
		cursor=rep;
	}
	else if(strcmp(comm,"SHOW")==0){
		
		show(rep);
	}
	else if(strcmp(comm,"INF")==0){
		
		if(cursor!=NULL && rep->prox!=NULL && cur!=rep && strcmp(cursor->nome,"elEx1sasfd")!=0){
			printf("%s\n", cursor->nome);	
		}
		else {
			printf("UNKNOWN\n");
		}
	}
	//  DEL - ADD
	else if(comm[0]=='A' || comm[0]=='D'){
		for(i=4;comm[i]!=32;i++){
			list[j]=comm[i];
			j++;
		}
		list[j] = '\0';
		j=0;
		for(i++;comm[i]!='\0';i++){
			music1[j]=comm[i];
			j++;
		}
		music1[j] = '\0';
		cur=lists(list);
		// ADD
		if(comm[1]=='D'){
			add(cur,music1);
		}
		// DEL
		else if(comm[1]=='E'){
			del(cur,music1);
		}
	}
	//  SWAP
	else if(comm[0]=='S'){
		for(i=4;comm[i]!=32;i++){
			list[j]=comm[i];
			j++;
		}
		list[j] = '\0';
		j=0;
		for(i++;comm[i]!=32;i++){
			music1[j]=comm[i];
			j++;
		}
		music1[j] = '\0';
		j=0;
		for(i++;comm[i]!='\0';i++){
			music2[j]=comm[i];
			j++;
		}
		music2[j] = '\0';
		cur=lists(list);
		swap(cur,music1,music2);
	}
	//  PLS - PLP
	else if(comm[0]=='P'){
		//  PLS
		if(comm[2]=='S'){
			j=0;
			for(i=4;comm[i]!='\0';i++){
				music1[j]=comm[i];
				j++;
			}
			music1[j] = '\0';
			node *tt = search(rep,"elEx1sasfd");
			if(rep->prox==NULL){
				add(rep,music1);
				cursor=rep->prox;
			}
			else if(tt != NULL){
				tt=tt->prox;
				strcpy(tt->nome,music1);
			}
			else if (rep->prox!=NULL){
				add(rep,music1);

			}
		}
		// PLP
		else if(comm[2]=='P'){
			j=0;
			for(i=4;comm[i]!='\0';i++){
				list[j]=comm[i];
				j++;
			}
			list[j] = '\0';
			Free(rep);
			rep=(node*)malloc(sizeof(node));
			rep->prox=NULL;
			cur=lists(list);
			copy(rep,cur);
			cursor=rep->prox;
		}
	}
}
int main(void){
	int i,a,n;
	char comand[tam];
	FILE *arq;
	initialize();	
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf(" %[^\n]", comand);
		choice(comand);		
	}
	Free(rep);
	if(cabeca!=NULL){
		head *cab=cabeca->next;
		while(cab!=NULL){
			Free(cab->prox);
			cab=cab->next;
		}
		head *pNode,*at;
		
		at = cabeca->next;
		while(at != NULL){
			pNode = at->next;
			free(at);
			at = pNode;
		}
	}
	return 0;
}