#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct dados {
	int *vetor, tam;
};
typedef struct dados data; 
int heapSize(int *vetor, int tam); 
int *bubbleUp(int *vetor, char rel,int tam,int tlogi);

int *dobra(int *vetor, int tam){
	int i,j=tam;
	tam=2*tam;
	vetor=(int*)realloc(vetor,sizeof(int)*tam);
	return vetor;
}
int heapFirtLeaf(int *vetor, int tam){
	int ret=1,ret2=1,i,j=0,logi;
	logi=heapSize(vetor, tam);
	//printf("logi :%d\n",logi );
	i=logi-1;
	while(i>0){
		j++;
		i=(i-1)/2;
	}
	j++;
	if(j>1){
		j--;
	}
	//printf("j %d\n",j );
	for(i=0;i<j;i++){
		ret=ret*2;
	}
	//printf("ret %d\n",ret );
	ret--;
	j--;
	//printf("ret :%d j:%d\n",ret, j );
	for(i=0;i<j;i++){
		ret2=ret2*2;
	}
	//printf("ret2 %d\n",ret2 );
	ret-=ret2;
	//printf("ret2-- %d\n",ret2 );
	return ret;
}
int heapSize(int *vetor, int tam){
	int i;
	if(tam==1){
		return 0;
	}
	for(i=0;i<tam;i++){
		if (vetor[i]==-1){
			return i;
		}
	}
	return i;
}
data insert(int *vetor,int valor, int tam, char rel, int tlogi){
	int t,j,i;
	data dadosp;
	//printf("tlogi %d\n",tlogi );
	if(tlogi+1==tam){
		j=tam-1;
		vetor=dobra(vetor,tam);
		tam*=2;
		vetor[tlogi]=valor;
		vetor[tlogi+1]=-1;
	}
	else {
		vetor[tlogi]=valor;
		vetor[tlogi+1]=-1;		
	}

	//printf("tamanho>%d< relacao '%c' valor>%d<\n",tam,rel,valor);
	//printf("vetor[%d] = val:%d\n",tlogi,valor);
	//printf(">>> ");
	//printf("\n");
	tlogi++;
	vetor = bubbleUp(vetor,rel,tam,tlogi);
	dadosp.tam=tam;
	dadosp.vetor=vetor;
	return dadosp;
}
int *heapify(int *vetor, int i, int logi, char rel){
	int aux,j,k,l,r,m;
	l=(2*i)+1;
	r=(2*i)+2;
	m=i;
	if(rel=='<'){
		if(l<logi && vetor[l] < vetor[m]){
			m=l;
		}
		if(r<logi && vetor[r] < vetor[m]){
			m=r;
		}
		if(m!=i){
			aux=vetor[i];
			vetor[i]=vetor[m];
			vetor[m]=aux;
			vetor = heapify(vetor,m,logi, rel);
		}
		return vetor;
	}
	else {

		if(l<logi && vetor[l] > vetor[m]){
			m=l;
		}
		if(r<logi && vetor[r] > vetor[m]){
			m=r;
		}
		if(m!=i){
			aux=vetor[i];
			vetor[i]=vetor[m];
			vetor[m]=aux;
			vetor = heapify(vetor,m,logi,rel);
		}
		return vetor;	
	}
}
int *bubbleUp(int *vetor, char rel,int tam, int tlogi){
	int i,aux,j;
	//menor
	if(rel=='<'){
		//printf("minimo\n");
		i=tlogi-1;
		//printf("tlogi %d\n",tlogi);
		while(i>0 && vetor[i] < vetor[(i-1)/2]){
			//printf("vetor[%d] :%d < %d: vetor [%d] | vetor[%d] :%d>sobe \n",i,vetor[i],vetor[(i-1)/2],(i-1)/2,i,vetor[i]);
			aux = vetor[i];
			vetor[i]=vetor[(i-1)/2];
			vetor[(i-1)/2] = aux;
			i=(i-1)/2;
			//printf("novo i >%d\n",i );
		}
	}
	else if(rel=='>'){
		//printf("maximo\n");
		i=tlogi-1;
		while(i>0  && vetor[i] > vetor[(i-1)/2]){
			//printf("vetor[%d] :%d > %d: vetor [%d] | vetor[%d] :%d>sobe \n",i,vetor[i],vetor[(i-1)/2],(i-1)/2,i,vetor[i]);
			aux = vetor[i];
			vetor[i]=vetor[(i-1)/2];
			vetor[(i-1)/2] = aux;
			i=(i-1)/2;
			//printf("novo i >%d\n",i );
		}
	}
	return vetor;
}
int *removeUltimo(int *vetor, int tam, char rel,int j){
	int i,k,logi;
	//printf("ultimo > %d\n",vetor[j-1]);
	j--;
	k=vetor[j];
	//printf("cabeca > %d\n",vetor[0]);
	vetor[j]=-1;
	vetor[0]=k;	
	vetor = heapify(vetor,0,j,rel);
	return vetor;
}
int main (){
	data dadosp;
	int *maxMenores, *minMaiores, miLogi, malogi, miTam, maTam,aux, max=-1;
	unsigned long int min=40000000000;
	int i,j,k,l,val,cmp=-1,a,b;
	char entrada[10];
	maxMenores=(int*)malloc(sizeof(int));
	minMaiores=(int*)malloc(sizeof(int));
	miTam=1;
	maTam=1;
	a=b=0;
	while(scanf(" %s", entrada)!=EOF){
		if(strcmp(entrada,"ADD")==0){
			scanf("%d",&val);
			if(val>-1){

				if(val>max){
					max=val;
				}
				if(val<min){
					min=val;
				}
				if(val>cmp){
					//printf("entra\n");
					dadosp=insert(minMaiores,val,miTam,'<',a);
					miTam=dadosp.tam;
					minMaiores=dadosp.vetor;
					a++;
					//printf("sai\n");
				}
				else {
					//printf("entrama\n");
					dadosp=insert(maxMenores,val,maTam,'>',b);
					maTam=dadosp.tam;
					maxMenores=dadosp.vetor;
					b++;
					//printf("saima\n");
				}
				//printf("a%d b%d\n",a,b);
				
				if(b>a){
					//printf("b>a\n");
					val=maxMenores[0];
					maxMenores=removeUltimo(maxMenores, maTam , '>',b);
					b--;
					//printf("maxMenores ");
					
					//printf("\n");
					dadosp=insert(minMaiores,val,miTam,'<',a);
					a++;
					miTam=dadosp.tam;
					minMaiores=dadosp.vetor;
				}
				else if((a-2 )== b) {
					//printf("2-a=b\n");
					val=minMaiores[0];
					minMaiores=removeUltimo(minMaiores, miTam, '<',a);
					a--;
					//printf("minMaiores ");
					
					//printf("\n");
					dadosp=insert(maxMenores,val,maTam,'>',b);
					b++;
					maTam=dadosp.tam;
					maxMenores=dadosp.vetor;
				}
				cmp=minMaiores[0];
			
				if(maTam==1){
					printf("%d %d %d\n",minMaiores[0],minMaiores[0],minMaiores[0]);
				}
				else{
					printf("%lu %d %d\n",min,minMaiores[0],max);
				}
			}
		}
		else if(strcmp(entrada,"SHOW")==0){
			printf("min> ");
			for(i=0;i<miTam;i++){
				printf("%d ", minMaiores[i]);
			}
			printf("\n");
			printf("max> ");
			for(i=0;i<maTam;i++){
				printf("%d ", maxMenores[i]);
			}
			printf("\n");
		}
		else if(strcmp(entrada,"MIN")==0){
			if(miTam==1 && maTam==1){
				printf("-1\n");
			}
			else {
				printf("%lu\n",min);
			}
		}
		else if(strcmp(entrada,"MAX")==0){
			if(miTam==1 && maTam==1){
				printf("-1\n");
			}
			else{
				printf("%d\n", max);
			}
		}
		else if(strcmp(entrada,"MED")==0){

			if(miTam==1 && maTam==1){
				printf("-1\n");
			}
			else{
				printf("%d\n",minMaiores[0]);	
			}	
		}
		else if(strcmp(entrada,"RES")==0){
			i=a+b;
			printf("%d\n",i);
			free(minMaiores);
			free(maxMenores);
			maxMenores=(int*)malloc(sizeof(int));
			minMaiores=(int*)malloc(sizeof(int));
			miTam=1;
			maTam=1;
			cmp=-1;
			max=-1;
			min=40000000000;
			a=b=0;
		}
		//printf("cmp >%d< val>%d<\n",cmp,val);	
	}
	free(minMaiores);
	free(maxMenores);
	//system("pause");
	return 0;
}