#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#define N   2
#define NN (N*2)
typedef char TipCheie;
typedef struct Nod
{
	TipCheie cheie[31];
	struct Pagina* p;
	int contor;
}Nod;

typedef struct Pagina
{
	int m;
	struct Pagina* p0;
	Nod e[NN + 1];
}Pagina;
Nod v;
Pagina* insereaza(Pagina *pag, TipCheie x[], Nod *nod){
	int i, s, d, mij;
	Pagina *q, *r;

	if (!nod)
	{
		strcpy(v.cheie, x);
		v.contor = 1;
		v.p = NULL;
	}
	else
		v = *nod;

	if (pag == NULL)
	{
		pag = (Pagina*)calloc(sizeof(Pagina), 1);
		pag->e[++pag->m] = v;

		return pag;
	}
	s = 1;
	d = pag->m;
	while (s <= d)
	{
		mij = (s + d) / 2;
		if (strcmp(pag->e[mij].cheie, x)==0)
		{
			pag->e[mij].contor++;
			return pag;
		}
		if (strcmp(x,pag->e[mij].cheie)<0)
			d = mij - 1;
		else
			s = mij + 1;
	}
	if (pag->p0 == NULL || nod)
	{
		if (pag->m < NN)
		{
			++pag->m;
			for (i = pag->m; i > d + 1; i--)
				pag->e[i] = pag->e[i - 1];
			pag->e[i] = v;
		}
		else
		{
			Pagina *a = pag;
			Pagina *b = (Pagina*)calloc(sizeof(Pagina), 1);
			pag = (Pagina*)calloc(sizeof(Pagina), 1);
			for (i = 1; i <= N; i++)
				b->e[i] = a->e[i + N];
			a->m = b->m = N;
			if (v.cheie > a->e[N].cheie && v.cheie < b->e[1].cheie)
				pag->e[++pag->m] = v;
			else{
				if (strcmp(v.cheie, a->e[N].cheie)<0){
					pag->e[++pag->m] = a->e[N];
					for (i = a->m; i > 1 && a->e[i - 1].cheie > v.cheie; i--)
						a->e[i] = a->e[i - 1];
					a->e[i] = v;
				}
				else
				{
					pag->e[++pag->m] = b->e[1];
					for (i = 1; i < b->m && b->e[i + 1].cheie < v.cheie; i++)
						b->e[i] = b->e[i + 1];
					b->e[i] = v;
				}
			}
			b->p0 = pag->e[1].p;
			pag->p0 = a;
			pag->e[1].p = b;
		}
	}
	else{
		if (d == 0)
			q = pag->p0;
		else
			q = pag->e[d].p;
		r = insereaza(q, x, NULL);
		if (r != q){
			pag = insereaza(pag, r->e[1].cheie, &r->e[1]);
			free(r);
		}
	}
	return pag;
}

void preordine(Pagina *arbore)
{
	int i;
	if (!arbore)
		return;
	for (i = 1; i <= arbore->m; i++)
		printf("%s ", arbore->e[i].cheie);
    preordine(arbore->p0);
    for (i = 1; i <= arbore->m; i++)
        preordine(arbore->e[i].p);
}
int main(){
    Pagina *radacina = NULL;
    int i;
    int n;
    scanf("%d",&n);
    char x[31];
    for (i = 1; i <= n; i++){
        scanf("%s",&x);
        radacina = insereaza(radacina, x, NULL);
    }
    preordine(radacina);
    printf("\n\n");

}