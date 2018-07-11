#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Tree{
	char atrib[1000];
	struct Tree *left;
	struct Tree *right;
};
typedef struct Tree tree;

struct Ramo{
	struct Tree *root;
};
typedef struct Ramo ramo;

struct pacote{
	tree *root;
	int val;
	char atributo[1000];
};
typedef struct pacote sedex;
tree *removeNo(tree *root,char atributo[1000], int val);

tree *bstFind(tree *root, char atributo[1000]){
	if(root==NULL){
		return NULL;
	}
	if (strcmp(atributo,root->atrib)==0){
		return root;
	}
	else if(strcmp(atributo,root->atrib)<0){
		return bstFind(root->left,atributo);
	}
	else{
		return bstFind(root->right, atributo);
	}
}
tree *criaNo(char atributo[1000]){
	tree *seed;
	seed=(tree*)malloc(sizeof(tree));
	strcpy(seed->atrib,atributo);
	seed->left = NULL;
	seed->right = NULL;
	return seed;
}
tree *insert(tree *root,int val, char atributo[1000]){
	if(root == NULL){
		root = criaNo(val,atributo);
		return root;
	}
	else if(strcmp(atributo,root->atrib) == 0){
		root->right = insert(root->right,val,atributo);
		return root;
	}
	else if(strcmp(atributo,root->atrib) < 0){
		root->left = insert(root->left,val,atributo);
		return root;
	}
	else{
		root->right = insert(root->right,val,atributo);	
		return root;
	}
}
sedex removeNoMin(tree *root){
	sedex pac;
	int t,i;
	if(root->left==NULL){
		pac.val = root->val;
		pac.root = root->right;
		strcpy(pac.atributo,root->atrib);
		free(root);
		return pac;
	}
	else {
		pac = removeNoMin(root->left);
		root->left = pac.root;
		pac.root = root;		
		return pac;	
	}
}
tree *removeNo(tree *root,char atributo[1000], int val){
	
	tree *r,*l;
	sedex pac;
	int i,t;
	if(root==NULL){
		return NULL;
	}
	else if(val != root->val && strcmp(atributo,root->atrib) < 0) {
		root->left = removeNo(root->left, atributo,val);
		return root;
	}
	else if(val != root->val && strcmp(atributo,root->atrib) > 0){
		root->right = removeNo(root->right, atributo,val);
		return root;
	}
	else if(val == root->val) {
		//printf("remove >%s\n", root->atrib);
		if(root -> left == NULL){
			r=root->right;
			if(root!=NULL){
				free(root);
			}
			return r;
		}
		else if(root->right == NULL){
			l=root->left;
			if(root!=NULL){
				free(root);
			}
			return l;
		}
		else{
			//printf("ok\n");
			pac = removeNoMin(root->right);
			root->right= pac.root;
			root->val=pac.val;
			strcpy(root->atrib,pac.atributo);
			return root;
		}
	}
	else{
		root->right = removeNo(root->right, atributo,val);
		return root;
	}
}
int main (){
	int n,i,tamMat,resp,j,k,l,m,w,t,p,o,*selec,linhas,coluna ,posi=0,index=0;
	char entrada[1000],***dados, **atributos, insert[1000],delet[1000];
	ramo **galho; // ligação entre as á
	tree *leaf;
	selec=(int*)malloc(sizeof(int));
	scanf("%d",&n);
	tamMat=n;
	dados =(char***)malloc(sizeof(char**)*n);
	atributos = (char**)malloc(sizeof(char*)*n);
	galho=(ramo**)malloc(sizeof(ramo*)*n);
	for(i=0;i<n;i++){
		galho[i]=(ramo*)malloc(sizeof(ramo)*n);
		dados[i] =(char**)malloc(sizeof(char*)*10000);
		atributos[i] = (char*)malloc(sizeof(char)*1000); 
	}
	j=0;
	k=0;
	for(i=0;i<n;i++){
		scanf(" %s",atributos[i]);
		//printf("%s -> %d |",atributos[i],i );
	}
	//printf("\n");
	while(scanf("%s", entrada)!= EOF){
		if(strcmp("SELECT", entrada)==0){
			scanf("%d", &m);
			selec=(int*)realloc(selec,sizeof(int)*m);
			for(i=0;i<m;i++){
				scanf(" %s", insert);
				////printf("&%s\n",insert );
				for(j=0;j<n;j++){
					if(strcmp(insert,atributos[j])==0){
						selec[i]=j;
						break;
					}
				}
			}
			scanf(" WHERE %s",insert);
			for(j=0;j<n;j++){
				if(strcmp(insert,atributos[j])==0){
					break;	
				}	
			}
			//printf(">%s>\n", insert);
			scanf(" %s",insert);
			leaf=bstFind(galho[j]->root,insert);
			while(leaf != NULL){
				for(l=0;l<m;l++){
					if(dados[selec[l]][leaf->val]!=NULL)
						printf("%s",dados[selec[l]][leaf->val]);
					else
						printf("?");
					if(l+1<m)
						printf(" ");
					else
						printf("\n");
				
				}
				leaf = bstFind(leaf->right,insert);
			}	
			printf("\n");
		}
		else if(strcmp("INSERT",entrada)==0){
			scanf("%d", &m);
			//printf("insere\n");
			for(i=0;i<m;i++){
				scanf(" %s", insert);
				for(j=0;j<n;j++){
					if(strcmp(insert,atributos[j])==0){
						break;
					}
				}
				dados[j][posi] = (char*)malloc(sizeof(char)*1000);
				scanf(" %s",insert);
				strcpy(dados[j][posi],insert);
				galho[j]->root=insert(galho[j]->root,posi,insert);
			}
			posi++;
		}
		else if(strcmp("DELETE",entrada)==0){
			scanf(" %s",delet);
			if(delet[0]=='!' || delet[0]=='*'){
				for(j=0;j<n;j++){
					if(strcmp(delet,atributos[j])==0){
						coluna=j;
						break;
					}
				}
				scanf(" %s", delet);
				leaf=bstFind(galho[j]->root,delet);
				if(leaf!=NULL){
					//printf(">%s<\n",leaf->atrib);
					t = leaf->val;
					for(i=0;i<n;i++){
						if(dados[i][t]!= NULL){
							//printf("<%s>\n",dados[i][t] );							
							galho[i]->root=removeNo(galho[i]->root,dados[i][t],t);
							dados[i][t] = NULL;
						}
					}
				}
			}		
		}
	}
	if(dados!=NULL){
		free(dados);
	}
	if(atributos!=NULL){
		free(atributos);
	}
	if(galho!=NULL){
		free(galho);
	}
	if(selec!=NULL){
		free(selec);
	}
	return 0;

}