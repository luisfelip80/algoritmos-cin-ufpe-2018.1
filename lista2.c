#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Data{
	char *palavra;
	int tam, *posi;
	uint32_t key;
};
typedef struct Data dados;
struct Hash{
	int tamanho,tMax;
	struct Data **tabela;	
};
typedef struct Hash hash;

hash *criaTabela ();
uint32_t dispersao();
uint32_t hashcode();
hash *Rehash();
hash *insere();

hash *criaTabela (int tamanho){
	uint32_t i;
	hash *tab;
	if(tamanho < 1){
		return tab;
	}
	if((tab = (hash*) malloc(sizeof(hash)))==NULL){
		return tab;
	}
	tab->tamanho = tamanho;
	tab->tMax=0;
	if((tab -> tabela = (dados**) malloc(sizeof(dados*)*tamanho))==NULL){
		return tab;
	}
	for(i=0;i<tamanho;i++){
		tab->tabela[i] = NULL;
	}
	return tab;
}
dados *criaMod(int k ){
	dados *mod;
	mod = (dados*) malloc(sizeof(dados));
	mod->palavra= (char*)malloc(sizeof(char)*k+1);
	mod->tam=1;
	mod->posi=(int*)malloc(sizeof(int));
	return mod;
}
uint32_t dispersao (int q,int w, uint32_t key){
	uint32_t novaKey;
	novaKey = (key + w )%q; 	
	//printf("%u\n",novaKey);
	return novaKey;
}
uint32_t hashcode(char kmer[200000], int k) {
		uint32_t c = 0;
		int i;
		for (i=0; i<k; i++){
			c = c*128 + kmer[i];
		}
		return c;
}
hash *Rehash(hash *tab, int q,int k){
	hash *Ntab;
	int w,i,j;
	uint32_t key,key0,key1,key01;
	int Q = (2*q)+1, *ret;
	Ntab=criaTabela(Q);
	Ntab->tMax = tab->tMax;
	for(i=0;i<q;i++){
		if(tab->tabela[i]!=NULL){
			w=1;			
			key0= tab->tabela[i]->key % Q;
			key=dispersao(Q,0,key0);

			if (Ntab->tabela[key] == NULL){
				Ntab->tabela[key] = tab->tabela[i];
			}
			else{
				key=dispersao(Q,w,key0);
				while(Ntab->tabela[key] != NULL){	
					w++;
					key=dispersao(Q,w,key0);
				}
				if (Ntab->tabela[key] == NULL){
					Ntab->tabela[key] = tab->tabela[i];
				}		
			}

		}
	}
	free(tab);
	//printf("vetor rehash %d\n",vetor );
	return Ntab;
}
hash *insere(hash *tab,uint32_t key,uint32_t key0,int q,char *aux,int posicao, uint32_t chave, int k){
	//printf(" key %d  w %d  q %d  aux %s  posi %d\n", key,w,q,aux,posicao );
	//printf("tam %d\n", tab->tabela[21]->tam);
	int w=1;
	if (tab->tabela[key] == NULL){
		tab->tabela[key] = criaMod(k);
		tab->tabela[key]->posi[0] = posicao;
		strcpy(tab->tabela[key]->palavra,aux);
		tab->tabela[key] -> key = chave;
		tab->tMax++;
	}
	else if(strcmp(tab->tabela[key]->palavra,aux)==0){
		//printf("%s - %s\n",aux,tab->tabela[key]->palavra );
		tab->tabela[key]->tam++;
		tab->tabela[key]->posi=(int*)realloc(tab->tabela[key]->posi,sizeof(int)*tab->tabela[key]->tam);
		tab->tabela[key]->posi [tab->tabela[key]->tam-1] = posicao;
	}
	else{
		key=dispersao(q,w,key0);
		while(tab->tabela[key] != NULL && strcmp(tab->tabela[key]->palavra,aux)!=0){	
			w++;
			key=dispersao(q,w,key0);
		}
		if (tab->tabela[key]== NULL){
			tab->tabela[key] = criaMod(k);
			tab->tabela[key]->posi[0]=posicao;
			strcpy(tab->tabela[key]->palavra,aux);
			tab->tabela[key] -> key = chave;
			tab->tMax++;
		}
		else if(strcmp(tab->tabela[key]->palavra,aux)==0) {
			//printf("%s - %s\n",aux,tab->tabela[key]->palavra );
			tab->tabela[key]->tam++;
			tab->tabela[key]->posi = (int*)realloc(tab->tabela[key]->posi,sizeof(int)*tab->tabela[key]->tam);
			tab->tabela[key]->posi[tab->tabela[key]->tam-1]=posicao;
		}
	}
	return tab;
}
uint32_t *search(hash *tab,uint32_t key,uint32_t key0,int q, char *aux){
	//printf("tam %d\n", tab->tabela[21]->tam);
	uint32_t i,*res=(uint32_t*)malloc(sizeof(uint32_t));
	int w=1;

	if (tab->tabela[key] == NULL){
		return NULL;
	}
	else if(strcmp(tab->tabela[key]->palavra, aux)==0){
		res[0] = key;
		return res;
	}
	else{
		key=dispersao(q,w,key0);
		while(tab->tabela[key] != NULL && strcmp(tab->tabela[key]->palavra, aux)!=0){	
			w++;
			key=dispersao(q,w,key0);
		}
		if (tab->tabela[key]== NULL){
			return NULL;
		}
		res[0] = key;
		return res;
	}
}
int main(){
	
	char hh,*erro=NULL,entrada[3000000],texto[10000], aux[200000];
	uint32_t key,key0,chave,pp, *res;
	hash *tab;
	float carga;
	int j,l=0,q,i,p,o,yy,k,ii,ww,u,r,*s,y,lui,cont;
	scanf(" %d %d", &k ,&q);
	tab = criaTabela(q);
	scanf(" $TXT %d",&y);
	yy=0;
	for(i=0;i<y;i++){
		scanf(" %[^\n]", texto);
		j=0;
		while(texto[j]!='\0'){
			entrada[yy]=texto[j]; 
			j++;
			yy++;
		}
		entrada[yy]='\n';
		yy++;
		//printf(">> %s\n", entrada);
	}
	yy--;
	entrada[yy]='\0';
	//printf(">%s<\n",entrada );
	//quebra a entrada e insere.
	//printf("%d\n",yy );
	for(j=0;j<yy-k;j++){
		//printf("ok2\n");
		key0=0;
		for(i=0;i<k && j+i < yy ;i++){
			aux[i] = entrada[j+i];
			key0 = key0*128 + entrada[j+i];
			//printf("%d\n",j+i);
		}
		if(i==k){
			chave = key0;
			key0=key0 % q;
			key=key0 % q;
			aux[i]='\0';
			//printf("j: %d >%s<\n",j,aux);
			//printf("ok3\n");
			tab=insere(tab,key,key0,q,aux,j,chave,k);
		 	//printf("ok4\n");
		 	carga = (float) tab->tMax/q;
		 	if(carga >= 0.5){
		 		//printf("opa\n");
		 		//printf("ok5\n");
		 		tab = Rehash(tab,q,k);
		 		//printf("ok6\n");
		 		q= (2*q)+1;
		 	}
		}
	 	//printf("palavra> %s  key>%d\n",aux,key);	 	
	}
	/*
	for(u=0;u<vetor-1;u++){
				printf(">%s<\n",clone[u]);
		}

	/*
	for(i=0;i<q;i++){
		if(tab->tabela[i]!=NULL){
			printf("%s : [%d]", tab->tabela[i]->palavra,i);			
			for(j=0;j<tab->tabela[i]->tam;j++){
				printf(" %d ", tab->tabela[i]->posi[j]);
			}
			printf("\n");
		}
	}
	*/
	//printf("procurar\n");
	scanf(" $CONSULTAS %d",&ww);
	for (i=0;i<ww;i++){
		l=0;
		scanf (" %[^\n]", texto);
		key0=0;
		yy = strlen(texto);
		for(j=0;j<k && j <=yy;j++){
			key0 = key0*128 + texto[j];
			aux[j] = texto[j];
		}
		printf("%d:",i);
		if(j<=yy){
			key0=key0 % q;
			key=key0 % q;
			aux[j]='\0';
			res=search(tab,key,key0,q,aux);
			//printf("c\n");
			if(res!=NULL){
				key=res[0];
				for(j=0; j < tab->tabela[key]->tam ; j++){
					lui=0;
					for(u=0;texto[u]!='\0';u++){
						if (texto[u] != entrada[tab->tabela[key]->posi[j]+u]){
							lui=1;
							break;
						}
					}
					if(lui==0){
						l=1;
						printf(" %d",tab->tabela[key]->posi[j]);
					}
				}
			}
		}
		if(l==0){
			printf(" ");
		}
		printf("\n");
	}
	j=1;
	s=(int*)calloc(q,sizeof(int));
	for(i=0;i<q;i++){
		if(tab->tabela[i]!=NULL){
			s[j]++;
			if(s[0]<s[j]){
				s[0]=s[j];
			}
		}
		else{
			j++;
		}
	}
	printf("%d %d %d\n",tab->tMax,q,s[0]);
	return 0;
}