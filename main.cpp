#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nodo {
	struct nodo* izquierdo;
	struct nodo* derecho;
	int dato;
	int FE;
}Nodo;

Nodo* Nuevo();
Nodo* Insertar(int, Nodo*);
Nodo* Balancear(Nodo*, int);
Nodo* RotIzquierda(Nodo*);
Nodo* RotDerecha(Nodo*);
Nodo* DobleRotIzquierda(Nodo*);
Nodo* DobleRotDerecha(Nodo*);
Nodo* Buscar(int dato, Nodo*);
Nodo* BuscarMayor(Nodo*);
Nodo* BuscarMenor(Nodo*);
Nodo* Suprimir(int, Nodo*);
Nodo* Cambiar(Nodo*, Nodo*);
int FactorEq(Nodo*);
int Altura(Nodo*p);
void VerPostOrden(Nodo*);
void VerEnOrden(Nodo*);
void VerPreOrden(Nodo*);
void Error();
void Menu();

int main(){
	int num, opc;
	Nodo *p;
	p = NULL;

	do {
		system("clear");
		Menu();
		scanf("%d", &opc);

		switch (opc) {
			case 1:
				system("clear");
				printf("Ingrese el dato a guardar:\t");
				scanf("%d", &num);

				if (Buscar(num, p) == NULL) {
					p = Insertar(num, p);
				}else {
					printf("El dato ya esta en el arbol\n");
				}

				getchar();
				getchar();
				break;
			case 2: 
				system("clear");
				printf("Ingrese el dato a buscar:\t");
				scanf("%d", &num);

				if (Buscar(num, p) != NULL){
					printf("El dato %d, se a encontrado\n", Buscar(num, p)->dato); 
				}else {
					printf("No se ha encontrado el dato %d\n", num);
				}

				getchar();
				getchar();
				break;
			case 3:
				system("clear");
				printf("Recorrido del arbol en Postorden\n");

				if (p != NULL) {
					VerPostOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}

				getchar();
				getchar();
				break;
			case 4:
				system("clear");
				printf("Recorrido del arbol en Orden\n");
	
				if (p != NULL) {
					VerEnOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 5:
				system("clear");
				printf("Recorrido del arbol en Preorden\n");
				
				if (p != NULL) {
					VerPreOrden(p);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 6:
				system("clear");
				
				if (p != NULL) {
					printf("El dato mayor es: %d\n", BuscarMayor(p)->dato);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 7:
				system("clear");

				if (p != NULL) {
					printf("El dato menor es: %d", BuscarMenor(p)->dato);
				}else {
					printf("El arbol esta vacio\n");
				}			

				getchar();
				getchar();
				break;
			case 8:
				system("clear");
				printf("Inserte el dato a eliminar: ");
				scanf("%d", &num);

				if (Buscar(num, p) != NULL){
					p = Suprimir(num, p);
					printf("Dato Eliminado\n");
				}else {
					printf("El dato %d no esta guardado\n", num);
				}

				getchar();
				getchar();
				break;
		}

	}while (opc != 9);
	
	return 0;
}

void Error(){
	perror("Memoria insuficiente!!\n");
	exit(1);
}

Nodo* Nuevo(){
	Nodo *p;
	p = (Nodo*) malloc(sizeof(Nodo));
	if(!p) Error();
	return (p);
}

Nodo* Insertar(int dato, Nodo *p){
	if(p == NULL){
		p = Nuevo();
		p->derecho = NULL;
		p->izquierdo = NULL;
		p->dato = dato;
		printf("Dato guardado");
		return (p);
	}

	if (dato < p->dato) {
		p->izquierdo = Insertar(dato, p->izquierdo);
	}else {
		p->derecho = Insertar(dato, p->derecho);
	}

	p->FE = FactorEq(p);

	if (fabs(p->FE) > 1) {
		p = Balancear(p, dato);
		p->FE = FactorEq(p);
		p->derecho->FE = FactorEq(p->derecho);
		p->izquierdo->FE = FactorEq(p->izquierdo);
	}

	return (p);
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

int FactorEq(Nodo* p){
	return (Altura(p->derecho) - Altura(p->izquierdo));
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

Nodo* Buscar(int dato, Nodo* p){
	if(p == NULL){
		return NULL;
	}

	if(dato == p->dato){
		return p;
	}

	if (dato < p->dato) {
		return (Buscar(dato, p->izquierdo));
	}else {
		return (Buscar(dato, p->derecho));
	}
}

void VerPostOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	VerPostOrden(p->izquierdo);
	VerPostOrden(p->derecho);

	printf("%d ", p->dato);
}

void VerEnOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	VerEnOrden(p->izquierdo);
	printf("%d ", p->dato);
	VerEnOrden(p->derecho);
}

void VerPreOrden(Nodo* p){
	if (p == NULL) {
		return;
	}

	printf("%d ", p->dato);
	VerPreOrden(p->izquierdo);
	VerPreOrden(p->derecho);
}

Nodo* BuscarMayor(Nodo* p){
	if (p->derecho == NULL) {
		return p;
	}

	return BuscarMayor(p->derecho);
}

Nodo* BuscarMenor(Nodo* p){
	if (p->izquierdo == NULL) {
		return p;
	}

	return BuscarMenor(p->izquierdo);
}

Nodo* Suprimir(int dato, Nodo* p){
	if (p == NULL) {
		return NULL;
	}

	if (dato < p->dato) {
		p->izquierdo = Suprimir(dato, p->izquierdo);
	}

	if (dato > p->dato) {
		p->derecho = Suprimir(dato, p->derecho);
	}

	if (p->dato == dato) {
		if (p->derecho == NULL) {
			p = p->izquierdo;
		}else if (p->izquierdo == NULL) {
			p = p->derecho;
		}else {
			p->derecho = Cambiar(p, p->derecho);
		}
	}

	return p;
}

Nodo* Cambiar(Nodo* p, Nodo* s){
	if (s->izquierdo == NULL) {
		p->dato = s->dato;
		s = s->derecho;
		return s;
	}

	s->izquierdo = Cambiar(p, s->izquierdo);

	return s;
}

void Menu(){
	printf("Escoja una opcion\n");
	printf("1.\tIngresar un dato\n");
	printf("2.\tBuscar un dato\n");
	printf("3.\tRecorrer el arbol en Postorden\n");
	printf("4.\tRecorrer el arbol en Orden\n");
	printf("5.\tRecorrer el arbol en Preorden\n");
	printf("6.\tBuscar dato mas grande\n");
	printf("7.\tBuscar el dato mas pequeño\n");
	printf("8.\tSuprimir un dato\n");
	printf("9.\tSalir\n");
}
