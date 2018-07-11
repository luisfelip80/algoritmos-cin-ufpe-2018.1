#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MIN -2147483648;
int maior=INT_MIN;
int travel(int m,int n, int s,int i,int j, int k,int di, int dj, int dk, int ***tabuleiro,int ***atalhos){
	int valor,caminho,back;
	if( atalhos[i][j][k]==1 || (i == di && j == dj && k == dk)){
		return tabuleiro[i][j][k];
	}
	else{
			caminho=0;
			if(i-1 >= 0 && i != di){
				valor = travel(m,n,s,i-1,j,k,di,dj,dk,tabuleiro,atalhos);
				if(caminho < valor)
					caminho = valor;
			}
			if(j+1 <= n-1 && j != dj){
				valor = travel(m,n,s,i,j+1,k,di,dj,dk,tabuleiro,atalhos);
				if(caminho < valor)
					caminho = valor;
			}
			if (k+1 <= s-1 && k != dk){
				valor = travel(m,n,s,i,j,k+1,di,dj,dk,tabuleiro,atalhos);
				if(caminho < valor)
					caminho = valor;
			}
			back = caminho + tabuleiro[i][j][k];
			atalhos[i][j][k] = 1;
			tabuleiro[i][j][k] += caminho; 
			return back;
	}
}
int main(){
	int i,j,k,Ji,Jj,Jk,l=0,***tabela,***atalhos,n,m,s,Dn,Dm,Ds,I,J,K,p,v,total, *valores;
	scanf("%d %d %d",&m,&n,&s);
	scanf("%d %d %d",&Dm,&Dn,&Ds);
	total = m * n * s;
	valores = (int*) malloc(sizeof(int)*total);
	for(i=0;i<total;i++){
		scanf("%d", &valores[i]); 
	}
	scanf("%d",&p);
	
	tabela = (int***)malloc(sizeof(int**)*m);
	atalhos = (int***)malloc(sizeof(int**)*m);
	for(i=0;i<m;i++){
		tabela[i] = (int**)malloc(sizeof(int*)*n);
		atalhos[i] = (int**)malloc(sizeof(int*)*n);
		for(j=0;j<n;j++){
			tabela[i][j] = (int*)malloc(sizeof(int)*s);
			atalhos[i][j] = (int*)malloc(sizeof(int)*s);
			for(k=0;k<s;k++){
				tabela[i][j][k] = valores [l];
				atalhos[i][j][k]=0;
				l++;
			}
		}
	}
	for(i=0;i<p;i++){
		scanf("%d %d %d",&Ji,&Jj,&Jk);
		maior = travel(m,n,s,Ji,Jj,Jk,Dm,Dn,Ds,tabela,atalhos);	
		printf("%d\n", maior);
		maior = INT_MIN;
	}
	return 0;
}