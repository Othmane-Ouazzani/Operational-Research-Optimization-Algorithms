#include <stdlib.h>
#include <stdio.h>
#define infinie 1316134911

typedef struct Noeud
{
    int info;
    struct Noeud *suc;
} noeud;

typedef noeud *listeNoeuds;

typedef struct Arc
{
    noeud *S;
    noeud *D;
    float val;
    float cap;
    float born;
    int etat;
    struct Arc *suc;
} arc;

typedef arc *listeArcs;

typedef struct Graphe
{
    listeNoeuds LN;
    listeArcs LA;
} graphe;

noeud *creerNoeud(int v)
{
    noeud *n = NULL;

    n = (noeud *)malloc(sizeof(noeud));

    n->info = v;
    n->suc = NULL;

    return n;
}

arc *creerArc(noeud *NS, noeud *ND, float b, float v, int e, float c)
{
    arc *arc1 = NULL;

    arc1 = (arc *)malloc(sizeof(arc));

    arc1->D = ND;
    arc1->S = NS;
    arc1->val = v;
    arc1->cap = c;
    arc1->born = b;
    arc1->etat = e;
    arc1->suc = NULL;

    return arc1;
}

graphe creerGraphe()
{
    graphe graphe1;

    graphe1.LA = NULL;
    graphe1.LN = NULL;

    return graphe1;
}

int grapheEstVide(graphe G)
{
    if (!G.LN)
        return 1;

    return 0;
}

int aucunArc(graphe G)
{
    if (!G.LA)
        return 1;

    return 0;
}

void afficherNoeud(noeud *N,FILE** out)
{
    printf("%d", N->info);
    fprintf(*out,"%d", N->info);

}
int afficherNoeudsGraphe(graphe G,FILE** out)
{
    noeud *noeudTest = G.LN;

    if (!grapheEstVide(G))
    {
        while (noeudTest)
        {
            afficherNoeud(noeudTest,out);
            printf("\t");
            fprintf(*out,"\t");
            noeudTest = noeudTest->suc;
        }
        printf("\n");
        return 1;
    }
    return 0;
}

int afficherArcsGraphe(graphe G,FILE** out)
{
    arc *arcTest = G.LA;

    if (aucunArc(G) == 0)
    {
        // printf("les arcs du graphe : \n");

        while (arcTest)
        {
            printf("( ");
            fprintf(*out,"(");
            afficherNoeud(arcTest->S,out);
            printf(" , ");
            fprintf(*out," , ");
            afficherNoeud(arcTest->D,out);
            printf(" , %.0f[%.0f]) \n", arcTest->val, arcTest->cap);
            fprintf(*out," , %.0f[%.0f]) \n", arcTest->val, arcTest->cap);
            arcTest = arcTest->suc;
        }
        return 1;
    }
    return 0;
}


int afficherLISTE(graphe G,FILE** out)
{
    arc *arcTest;
    arcTest =G.LA;

    if (aucunArc(G) == 0)
    {
        printf("Chaine augmentente : \n");
        fprintf(*out,"Chaine augmentente : \n");


        while (arcTest)
        {
            printf("( ");
            fprintf(*out,"(");
            afficherNoeud(arcTest->S,out);
            printf(" , ");
            fprintf(*out," , ");
            afficherNoeud(arcTest->D,out);
            printf(" , %.0f[%.0f] ) , %d\n", arcTest->val, arcTest->cap, arcTest->etat);
            fprintf(*out," , %.0f[%.0f] ) , %d\n", arcTest->val, arcTest->cap, arcTest->etat);
            arcTest = arcTest->suc;
        }
        return 1;
    }
    return 0;
}

noeud *insererNoeud(int Ninfo, listeNoeuds *LN)
{
    noeud *noeudNew;
    noeudNew = *LN;
    if (!noeudNew)
    {
        *LN = creerNoeud(Ninfo);
        return *LN;
    }
    while (noeudNew)
    {
        if (noeudNew->info == Ninfo)
            return noeudNew;
        if (!noeudNew->suc)
        {
            noeudNew->suc = creerNoeud(Ninfo);
            return noeudNew->suc;
        }
        noeudNew = noeudNew->suc;
    }
    return noeudNew;
}

arc *insererArc(noeud *NS, noeud *ND, float b, float v, float c, int e, listeArcs *LA)
{
    arc *arcNew = *LA;
    if (!arcNew)
    {
        *LA = creerArc(NS, ND, b, v, e, c);
        return *LA;
    }
    while (arcNew)
    {
        if (arcNew->S->info == NS->info && arcNew->D->info == ND->info)
            return arcNew;
        if (!arcNew->suc)
        {
            arcNew->suc = creerArc(NS, ND, b, v, e, c);
            return arcNew->suc;
        }
        arcNew = arcNew->suc;
    }
    return arcNew;
}

noeud *insererNoeudGraphe(int v, graphe *G)
{
    return insererNoeud(v, &(G->LN));
}

arc *insererArcGraphe(int NS, int ND, float b, float v, float c, graphe *G)
{
    return insererArc(insererNoeud(NS, &G->LN), insererNoeud(ND, &G->LN), b, v, c, 0, &G->LA);
}

int existNoeud(int v, graphe G)
{
    noeud *noeudNew = G.LN;

    if (grapheEstVide(G))
        return 0;
    while (noeudNew)
    {
        if (noeudNew->info == v)
            return 1;
        noeudNew = noeudNew->suc;
    }
    return 0;
}

int existArc(int Sinfo, int Dinfo, graphe G)
{
    arc *arcNew = G.LA;

    if (aucunArc(G))
        return 0;
    while (arcNew)
    {
        if (arcNew->S->info == Sinfo && arcNew->D->info == Dinfo)
            return 1;
        arcNew = arcNew->suc;
    }

    return 0;
}

graphe GLOBALL=creerGraphe();//Declare Global Graph to store edges that we passed through


int chaineAugmentante(int infoS, int infoP, graphe G, graphe *GG)
{
    graphe A = G;
    if (existNoeud(infoS, G) && existNoeud(infoP, G))
    {
        if (existArc(infoS, infoP, G)) //If edge between S and P return 1, works as a stopping condition for recursion
        {
            while (A.LA)
            {

                if (A.LA->S->info == infoS && A.LA->D->info == infoP)
                {
                    if (A.LA->val < A.LA->cap)
                    {
                        insererArc(A.LA->S, A.LA->D, A.LA->born, A.LA->val, A.LA->cap, 1, &GG->LA);
                        return 1;
                    }
                }
                A.LA = A.LA->suc;
            }
        }
        graphe S = G;
        while (S.LA)  //In this loop,we look for successors and predecessors  (Direct or Indirect edges)
        {
            if (!existArc(S.LA->S->info, S.LA->D->info, GLOBALL)) //If !existArc(S,D,GLOBAL)  , Test if we haven't passed from this edge yes
            {
                if (S.LA->S->info == infoS)  //If S is the source of the edge,we mark it in GLOBAL
                {
                    insererArc(S.LA->S, S.LA->D, S.LA->born, S.LA->val, S.LA->cap, 1, &GLOBALL.LA);
                    if (S.LA->val < S.LA->cap)  //Test that we can go through this edge.
                    {
                        if (chaineAugmentante(S.LA->D->info, infoP, G, GG)) //Recursion to find a path from S to D, if found , We store all the edges that led to this path
                        {
                            insererArc(S.LA->S, S.LA->D, S.LA->born, S.LA->val, S.LA->cap, 1, &GG->LA);
                            return 1;
                        }
                    }
                }
                if (S.LA->D->info == infoS)  //Same thing but for predecessors
                {
                    insererArc(S.LA->S, S.LA->D, S.LA->born, S.LA->val, S.LA->cap, 1, &GLOBALL.LA);
                    if (S.LA->val > 0)
                    {
                        if (chaineAugmentante(S.LA->S->info, infoP, G, GG))
                        {
                            insererArc(S.LA->S, S.LA->D, S.LA->born, S.LA->val, S.LA->cap, -1, &GG->LA);
                            return 1;
                        }
                    }
                }
            }
            S.LA = S.LA->suc;
        }
    }
    return 0;
}
void fordFulkerson(int infoS, int infoP, graphe* G,FILE** out) //We can just use graphe G  instead of graphe* G since we just print the values right away.Unless we
// cant to
// change
// the graph
{
    int cout = 0;
    graphe GG;
    GG = creerGraphe();
    int i;
    while (chaineAugmentante(infoS, infoP, *G, &GG))
    {
        GLOBALL = creerGraphe();  //Empty Global graph to fill it again after being used in listAug
        int k = infinie;

        graphe AA = GG;//GG contains Chaine augmentante
        while (AA.LA) //Looking for the minimum value of Cap-Flux for both direct and indirect edges (1,-1)
        {
            if (AA.LA->etat == 1)
            {
                if (k > AA.LA->cap - AA.LA->val)
                    k = AA.LA->cap - AA.LA->val;
            }
            if (AA.LA->etat == -1)
            {
                if (k > AA.LA->val)
                    k = AA.LA->val;
            }
            AA.LA = AA.LA->suc;
        }
        afficherLISTE(GG,out);
        cout += k;// To calculate maximum flow,since every adde value passers passes by S and through D
        while (GG.LA) //Here we add or subtract the minimum value found of Cap-Flux  to/from  each edge of chaine augmentante
        {
            graphe A;
            A = *G;
            while (A.LA)//Cycle through original graph
            {
                if (A.LA->S->info == GG.LA->S->info && A.LA->D->info == GG.LA->D->info) //Find the edge and apply treatment
                {
                    if (GG.LA->etat == 1)
                        A.LA->val += k;
                    else
                        A.LA->val -= k;
                }
                A.LA = A.LA->suc;
            }

            GG.LA = GG.LA->suc;
        }
    }

    printf("La valeur de flot Max = %d\nLes flux :\n", cout);
    fprintf(*out,"La valeur de flot Max = %d\nLes flux :\n", cout);
    afficherArcsGraphe(*G,out);

}

int lireFichier(graphe *G, FILE **fp, char *nomFichier, int *p)
{
    *fp = fopen(nomFichier, "r");
    int infoS, infoD;
    float vArc;

    if (*fp != NULL)
    {
        int j, i = -2;
        while (!feof(*fp))
        {
            if (i == -2)
                fscanf(*fp, "%d\n", &j);
            else if (i == -1)
                fscanf(*fp, "%d\n", p);
            else
            {
                fscanf(*fp, "%d\t%d\t%f\n", &infoS, &infoD, &vArc);
                insererArcGraphe(infoS, infoD, 0, 0, vArc, G);
            }
            i++;
        }
        return j;
    }
    return NULL;
}

int main()
{
    int NS, NP;
    graphe G;
    G = creerGraphe();
    FILE *fp,*output;
    output = fopen("output.txt", "w+");
    char file[] = "file1.txt";
    NS = lireFichier(&G, &fp, file, &NP);
    printf("les arcs du graphe : \n");
    fprintf(output,"les arcs du graphe : \n");
    afficherArcsGraphe(G,&output);
    fordFulkerson(NS, NP, &G,&output);
    system("pause");
}
