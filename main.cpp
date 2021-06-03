#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nodo{
	int FE;
	int dato;
	nodo* izquierdo;
	nodo* derecho;
}Nodo;

Nodo* Nuevo();
Nodo* Insertar(Nodo*, int);
Nodo* Balancear(Nodo*, int);
Nodo* RotIzquierda(Nodo*);
Nodo* RotDerecha(Nodo*);
Nodo* DobleRotIzquierda(Nodo*);
Nodo* DobleRotDerecha(Nodo*);
int Altura(Nodo*);
int FactorEq(Nodo*);
void RecorrerEnOrden(Nodo*);

int main(){
	Nodo* p;
	p = NULL;
	int num;

	while (1) {
		printf("Inserte un dato\n");
		scanf("%d", &num);

		if (num == 666) {
			break;
		}

		p = Insertar(p, num);
	}

	RecorrerEnOrden(p);
	getchar();
	return 0;
}

Nodo* Nuevo(){
	Nodo* p;
	p = (Nodo*) malloc(sizeof(Nodo));

	if (!p) {
		printf("ERROR!!\tMemoria insuficiente\n");
		exit(1);
	}

	return p;
}

Nodo* Insertar(Nodo* p, int dato){
	if (p == NULL) {
		p = Nuevo();
		p->derecho = NULL;
		p->izquierdo = NULL;
		p->dato = dato;
		p->FE = 0;
		return p;
	}

	if (dato < p->dato) {
		p->izquierdo = Insertar(p->izquierdo, dato);
	}else {
		p->derecho = Insertar(p->derecho,dato);
	}
	
	p->FE = FactorEq(p);

	if (fabs(p->FE) > 1) {
		p = Balancear(p, dato);
		p->FE = FactorEq(p);
		p->derecho->FE = FactorEq(p->derecho);
		p->izquierdo->FE = FactorEq(p->izquierdo);
	}
	
	return p;
}

int Altura(Nodo* p){
	int h = 0;

	if (p != NULL) {
		h += 1;
		
		if (p->derecho == NULL && p->izquierdo == NULL) {
			return h;
		}else {
			if (p->derecho != NULL && p->izquierdo != NULL) {
				int i, d;
				i = Altura(p->izquierdo);
				d = Altura(p->derecho);

				if (i != d) {
					return (i > d ? h+=i: h+=d);
				}else {
					return h+=i;
				}
			}else {
				h += Altura(p->izquierdo);
				h += Altura(p->derecho); 
			}
		} 
	}

	return h;
}

int FactorEq(Nodo* p){
	return (Altura(p->derecho) - Altura(p->izquierdo));
}

void RecorrerEnOrden(Nodo* p){
	if (p == NULL) {
	 return;
	}	

	printf("%d\t:\t%d\n", p->dato, p->FE);
	RecorrerEnOrden(p->izquierdo);
	RecorrerEnOrden(p->derecho);
}

Nodo* Balancear(Nodo* p, int dato){

	if (dato < p->dato) {
		if (dato < p->izquierdo->dato) {
			p = RotIzquierda(p);
		}else {
			p = DobleRotIzquierda(p);
		}
	}

	if (dato > p->dato) {
		if (dato > p->derecho->dato) {
			p = RotDerecha(p);
		}else {
			p = DobleRotDerecha(p);
		}
	}

	return p;
}

Nodo* RotDerecha(Nodo* p){
	Nodo * q;
	q = p->derecho;
	p->derecho = q->izquierdo;
	q->izquierdo = p;
	return q;
}

Nodo* RotIzquierda(Nodo* p){
	Nodo* q;
	q = p->izquierdo;
	p->izquierdo = q->derecho;
	q->derecho = p;
	return q;
}

Nodo* DobleRotDerecha(Nodo* p){
	p->derecho = RotIzquierda(p->derecho);
	return (RotDerecha(p));
}

Nodo* DobleRotIzquierda(Nodo* p){
	p->izquierdo = RotDerecha(p->izquierdo);
	return  (RotIzquierda(p));
}

