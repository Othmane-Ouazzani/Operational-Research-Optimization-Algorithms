#include<stdio.h>
#include<stdlib.h>

typedef struct Noeud{
	int info;
	struct Noeud* suc;
} noeud;

typedef noeud* list_noeuds;

typedef struct Arc {
	noeud* s;
	noeud* d;
	float val;
	struct Arc* suc;

}arc;

typedef arc* list_arcs;

typedef struct Graph{
	list_noeuds LN;
	list_arcs LA;
}graph;

typedef struct str_chemin {
	noeud* Dest;
	noeud* Interm;
	float c;
	int etat;
	struct str_chemin *suc;
}cheminDijkstra;

typedef cheminDijkstra *listeDijkstra;

typedef struct node {
	int n;
	struct node *next;
}Node;

typedef  Node* list_int;

int y=0;
Node *newNode(int x) {
	Node *pnt = (Node *) malloc (sizeof(Node));
	pnt -> n = x;
	pnt -> next = NULL;
	return pnt;
}
Node *findNode(Node *top, int k) {

	if (top==NULL || top -> n == k)
		return top;
	else{
		return findNode(top -> next, k);
	}

}
int node_exist(list_int tab,int k){
	Node* cur;
	for(cur=tab;cur!=NULL;cur = cur->next)
	  if(cur->n == k) return 1;
	return 0;
}
void printList(Node *top) {
	if (top != NULL) {
		printf("%d -> ", top -> n);
		printList(top -> next);
	}
	else
		printf("NULL\n");
}
int countNodes(Node *top) {
    if (top == NULL)
        return 0;
    else
        return 1 + countNodes(top -> next);
}
void add(list_int* L,int n){
	Node* item = newNode(n);
	if(*L==NULL) *L = item;
	else {
		item->next = *L;
		*L = item;
	}
}
int copy(list_int src, list_int* destn){
	Node* cur_src;
	for(cur_src = src;cur_src!=NULL;cur_src=cur_src->next){
	     add(destn,cur_src->n);
	}
	return 1;
}
void clear(list_int* L){
	Node* cur_L;
	for(cur_L = *L;cur_L!=NULL;cur_L=*L){
	     *L = (*L)->next;
		 free(cur_L);
	}

}
noeud* cree_noeud(int v){
	noeud* n;
	n= (noeud*) malloc(sizeof(noeud));
	n->info = v;
	n->suc = NULL;
	return n;
}
arc* cree_arc(noeud* NS,noeud* ND,float v){
	arc* a;
	a = (arc*) malloc(sizeof(arc));
	a->d = ND;
	a->s = NS;
	a->val = v;
	a->suc = NULL;
return a;
}
graph cree_graph() {
	graph g;
	g.LA = NULL;
	g.LN = NULL;
	return g;
}
int graph_est_vide(graph g){
	return g.LN == NULL;

}
int aucun_arc(graph g) {
	return g.LA == NULL;
}
int afficher_noeuds(graph g){
	noeud* N = g.LN;
	if(graph_est_vide(g))
	    return 0;

	while(N != NULL){
		printf("Noeud(%d)\n",N->info);
		N = N->suc;
	}
	return 1;

}
int afficher_arcs(graph g){
	arc* N = g.LA;
	if(aucun_arc(g))
	    return 0;

	while(N != NULL){
		printf("(%d,%d)[%f]\n",N->s->info,N->d->info,N->val);
		N = N->suc;
	}
	return 1;

}
int exist_noeud(int info,graph g){
	noeud* N = g.LN;
	if(graph_est_vide(g))
	    return 0;

	while(N != NULL){
	    if(N->info == info) return 1;
		N = N->suc;
	}
	return 0;
}
int exist_arc(int Sinfo,int Dinfo,graph g){
	arc* N = g.LA;
	if(aucun_arc(g))
	    return 0;

	while(N != NULL){
	    if(N->d->info == Dinfo && N->s->info == Sinfo) return 1;
		N = N->suc;
	}
	return 0;
}
noeud* inserer_noeud(int info , list_noeuds* ln){

	noeud* L = *ln;
	noeud* h = L;
		while(L != NULL){
	    if(L->info == info) return L;
	    h = L;
		L = L->suc;
	}
	h->suc = cree_noeud(info);
	return h->suc;
}
arc* inserer_arc(noeud* NS,noeud* ND,float v , list_arcs* la){
	arc* L = *la;
	arc* A;
		while(L != NULL){
	    if(L->d->info == ND->info && L->s->info == NS->info && L->val==v) return L;
		A = L;
		L = L->suc;
	}
	A->suc = cree_arc(NS,ND,v);
	return A->suc;

}
noeud* inserer_noeud_g(int info , graph* g){
	if(graph_est_vide(*g)) return g->LN = cree_noeud(info);
	return inserer_noeud(info,&g->LN);
}
arc* inserer_arc_g(int NS,int ND,float v , graph* g){
	noeud *ns=inserer_noeud_g(NS , g),*nd=inserer_noeud_g(ND , g);
	if(aucun_arc(*g)) return g->LA = cree_arc(ns,nd,v);
	return inserer_arc(ns,nd,v,&g->LA);
}
int supprimer_arc(int Sinfo,int Dinfo,graph* g){
	arc* N = g->LA;
	arc* L=N;
	arc* H;
	if(aucun_arc(*g)) return 0;
	while(N != NULL){
	    if(N->d->info == Dinfo && N->s->info == Sinfo) break;
	    L=N;
		N = N->suc;
	}

    if(N == NULL) return 0;
	/*if(L->suc == NULL) {
		g->LA = NULL;
		return 1;
	}*/
	if(L == N) {
		H = L;
	    g->LA = g->LA->suc;
	    H->suc = NULL;
	    free(H);
	    return 1;
	}
	H = L->suc;
	L->suc = H->suc;
	H->suc = NULL;
	free(H);
	return 1;
}
int supprimer_noeud(int info, graph *g) {
	noeud* N = g->LN;
	noeud* L=N;
	noeud* H;

	arc* A = g->LA;
	arc* A2;

	if(graph_est_vide(*g)) return 0;
	while(N != NULL){
	    if(N->info == info ) break;
	    L=N;
		N = N->suc;
	}

	while(A != NULL){

		if(A->s->info == info || A->d->info == info) {
			A2 = A->suc;
			printf("%d\n",supprimer_arc(A->s->info,A->d->info,g));
            A = A2;
			continue;
		}
		A = A->suc;
	}


	if(N == NULL) return 0;
	if(N->suc == NULL) {
		g->LN = NULL;
		return 1;
	}
	if(L == N) {
		H = N;
	    g->LN = g->LN->suc;
	    H->suc = NULL;
	    free(H);
	return 1;
	}
	H = L->suc;
	L->suc = H->suc;
	H->suc = NULL;
	free(H);
	return 1;
}
int demi_deg_exter(int info, graph g){
	int count=0;
	arc* A = g.LA;
	if(!exist_noeud( info, g)) return 0;
	while(A != NULL){
		if(A->s->info == info) count++;
		A= A->suc;
	}
	return count;
}
int demi_deg_inter(int info, graph g){
	int count=0;
	arc* A = g.LA;
	if(!exist_noeud( info, g)) return 0;
	while(A != NULL){
		if(A->d->info == info) count++;
		A= A->suc;
	}
	return count;
}

int read_file(graph* G,char* nomFichier) {
	FILE* fp;
	fp = fopen(nomFichier,"r");
	int infoS,infoD;
	float vArc;
	int src = -1;

	if(fp!=NULL){
		while(!feof(fp)) {
			if (src == -1)
				fscanf(fp, "%d\n", &src);
			fscanf(fp,"%d\t%d\t%f\n",&infoS,&infoD,&vArc);
			inserer_arc_g(infoS,infoD,vArc,G);
		}
	}
	return src;
}
void fitch_suc(list_int tab1,list_int* tab2,list_int* tab3,graph g){
	Node* cur_tab1;
	arc* cur_la;
	clear(tab2);
	for(cur_tab1=tab1;cur_tab1!=NULL;cur_tab1=cur_tab1->next){
		for(cur_la=g.LA;cur_la!=NULL;cur_la=cur_la->suc){
		    if( cur_tab1->n == cur_la->s->info && findNode(*tab3,cur_la->d->info)==NULL ) {
		    	add(tab3,cur_la->d->info);
		    	add(tab2,cur_la->d->info);

			}
		}
	}
}
int exist_chemin(int S,int D,graph g){
	list_int tab1,tab2,passed;
	tab1=tab2=passed=NULL;
	if(!exist_noeud(S,g) || !exist_noeud(D,g)) return 0;
	add(&tab1,S);
	add(&passed,S);
	while(findNode(passed,D)==NULL && countNodes(tab1)!=0){
		fitch_suc(tab1,&tab2,&passed,g);
		clear(&tab1);
		copy(tab2,&tab1);
	}
	if(findNode(passed,D)!=NULL) return 1;
	if(countNodes(tab1)==0) return 0;

}
void insererNoeudDijkstra(noeud* N,int infoS, graph G,listeDijkstra *L) {
	list_arcs Q;
	listeDijkstra P,R;
	P = (cheminDijkstra *) malloc(sizeof(cheminDijkstra));
	P->Dest = N;
	P->Interm = N;
	P->suc = NULL;
	if(N->info == infoS) {
		P->etat = 1;
		P->c = 0;
	}
	else {
		P->etat = 0;
		P->c = 99999;
	}
	Q = G.LA;

	while(Q!=NULL && (Q->s->info != infoS || Q->d!= N))
		Q = Q->suc;

	if(Q != NULL) {
		P->Interm = Q->s;
		P->c = Q->val;
	}

	if(*L == NULL)
		*L = P;
	else {
		R = *L;
		while (R->suc !=NULL)
			R = R->suc;
		R->suc = P;
	}
}

void Dijkstra(graph G, int infoS,listeDijkstra *L){
	noeud * N;
	arc* arcTraverse;
	listeDijkstra listeDijikstraTraverser;
	listeDijkstra cheminNoeudAtester;
	int existeValeurAtester;
	if (!exist_noeud(infoS,G)) return;
	N = G.LN;

	while(N != NULL) {
		insererNoeudDijkstra(N,infoS,G,L);
		N = N->suc;
	}

	do {
		listeDijikstraTraverser = *L;

		cheminNoeudAtester = NULL;

		arcTraverse = NULL;

		existeValeurAtester = -1;

		float valueMinimum = 99999;


		//Trouver W
		while(listeDijikstraTraverser) {
			if(valueMinimum > listeDijikstraTraverser->c && listeDijikstraTraverser->etat == 0) {
				valueMinimum = listeDijikstraTraverser->c;
				existeValeurAtester = 1;
				cheminNoeudAtester = listeDijikstraTraverser;
			}
			listeDijikstraTraverser = listeDijikstraTraverser->suc;
		}



		// Mise A jours la liste des chemins
		if(existeValeurAtester == 1 ) {
			listeDijikstraTraverser = *L;

			while(listeDijikstraTraverser) {
				if(listeDijikstraTraverser->etat == 0) {
					if(listeDijikstraTraverser->Dest->info == cheminNoeudAtester->Dest->info)
						listeDijikstraTraverser->etat = 1;

					else {
						arcTraverse = G.LA;

						while(arcTraverse != NULL && (arcTraverse->s != cheminNoeudAtester->Dest || arcTraverse->d != listeDijikstraTraverser->Dest))
							arcTraverse = arcTraverse->suc;

						if(arcTraverse != NULL && (cheminNoeudAtester->c + arcTraverse->val) < listeDijikstraTraverser->c){
							listeDijikstraTraverser->c = cheminNoeudAtester->c + arcTraverse->val;
							listeDijikstraTraverser->Interm = cheminNoeudAtester->Dest;
						}

					}
				}
				listeDijikstraTraverser = listeDijikstraTraverser->suc;
			}
		}
	}while(existeValeurAtester == 1);



}
void afficherDijkstra(int infoS,int infoD, listeDijkstra L,graph g,FILE **out) {
	listeDijkstra listeTraverse = L;

	if(!exist_chemin(infoS,infoD,g)) {
		printf("Il n'existe aucun chemin\n");
		fprintf(*out,"IL n'existe aucun chemin\n");
		return;
	}
	if(infoS == infoD) {
		while(listeTraverse) {
			if(listeTraverse->Dest->info == infoD){
				printf("%d",listeTraverse->Dest->info);
				fprintf(*out,"%d",listeTraverse->Dest->info);
				break;
			}

		listeTraverse = listeTraverse->suc;
		}
	}

	else{

		while(listeTraverse) {
			if(listeTraverse->Dest->info == infoD){
				if(listeTraverse->Dest->info != listeTraverse->Interm->info)
					afficherDijkstra(infoS,listeTraverse->Interm->info,L,g,out);

			    printf("---->%d",listeTraverse->Dest->info);
			    fprintf(*out, "--->%d", listeTraverse->Dest->info);
			}

			listeTraverse = listeTraverse->suc;
		}
	}



}
void printDJList(listeDijkstra top) {
	if (top != NULL) {
		printf("(%d,%d,%.0f) -> ", top->Dest->info,top->Interm->info,top->c);
		printDJList(top -> suc);
	}
	else
		printf("NULL\n");
}
float get_cost(int dest,listeDijkstra top){
	listeDijkstra cur;
	for(cur=top;cur!=NULL;cur=cur->suc)
	   if(cur->Dest->info == dest) return cur->c;
    return 0;
}

int main(){
    int src;
	graph G;
	noeud* cur_ln;
	FILE *out;
	float cost;


	out = fopen("output.txt", "w+");
	G = cree_graph();
	listeDijkstra listeDij = NULL;
	src = read_file(&G,"input.txt");
	printf("--------------------------------la list des noeuds : -------------------------------------\n");
	afficher_noeuds(G);
	printf("------------------------------------------------------------------------------------------\n");
	printf("--------------------------------la list des arcs : -------------------------------------\n");
	afficher_arcs(G);
	printf("------------------------------------------------------------------------------------------\n");

	Dijkstra(G,src,&listeDij);

	for(cur_ln=G.LN;cur_ln != NULL;cur_ln = cur_ln->suc){


		cost = get_cost(cur_ln->info,listeDij);
		printf("Chemin entre %d et %d : ", src, cur_ln->info);
		fprintf(out, "Chemin entre %d et %d : ",src,cur_ln->info);
		afficherDijkstra(src,cur_ln->info,listeDij,G,&out);
        if(cost != 99999.000000) {
            printf("\nle cout : %.1f\n", cost);
            fprintf(out, "\nle cout : %f\n", cost);
            //printf("\n");
        }
	}

return 0;
}
