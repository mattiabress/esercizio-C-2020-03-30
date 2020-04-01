/*
 * fibonacci.c
 *
 *  Created on: 1 apr 2020
 *      Author: Mattia Bressan
 */

/*
 * ***
 * esercizio 2020-03-30*** (deve risultare un unico programma in C, scrivete tutto il codice sorgente in src/esercizio20200330.c)

	A - scrivere la seguente funzione:

	implementare una funzione che calcola la serie di Fibonacci:

	unsigned long fibonacci(unsigned int n);

	dove:
	fibonacci(0) = 0
	fibonacci(1) = 1
	fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1

	provare a scoprire quale è il valore massimo di n per cui fibonacci(n) restituisce un valore della serie corretto


	B - scrivere la seguente funzione:

	unsigned long * fibonacci_array(unsigned int n);

	questa funzione restituisce un array di unsigned long di dimensione n+1 (n è l'argomento della funzione)
	dove la cella i-ma contiene il valore di fibonacci(i).


	C - main() fa queste operazioni:

	calcola fibonacci_array(39) e lo assegna alla varibile 'fibonacci_result'  // fibonacci(39) = 63245986

	fare una copia dell'array fibonacci_result in 'fibonacci_result_copy' (i due array devono avere aree di memoria distinte)

	fibonacci_result_copy: fare il 'reverse' dell'array ('copiare' da esempio 004.1arrays-operations)

	su fibonacci_result_copy: applicare bubble_sort ('copiare' da esempio 004.1arrays-operations)

	confrontare fibonacci_result e fibonacci_result_copy, verificare che i due array siano uguali (scrivere su stdout il risultato).
	 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

unsigned long fibonacci(unsigned int n);
unsigned long * fibonacci_array(unsigned int n);
unsigned long * make_copy_of_array(unsigned long src_array [], unsigned int array_dimension);
void swap(unsigned long *x,unsigned long *y);
void bubblesort(unsigned long *array, int  size);
unsigned long * reverse(unsigned long * array,int  size);
unsigned long * reverse_unsigned_long(unsigned long * array, unsigned int i, unsigned int j);

int main(int argc, char *argv[]) {
	// fibonacci(39) = 63245986
	unsigned long x=fibonacci(39);
	printf("%ld \n",x);
	//fibonacci_array(39)
	int n=39;
	unsigned long * fibonacci_result=fibonacci_array(n);
	//fare una copia dell'array fibonacci_result in 'fibonacci_result_copy' (i due array devono avere aree di memoria distinte)
	unsigned long * fibonacci_result_copy=make_copy_of_array(fibonacci_result, n+1);
	//fibonacci_result_copy: fare il 'reverse' dell'array ('copiare' da esempio 004.1arrays-operations)
	fibonacci_result_copy=reverse(fibonacci_result_copy,n+1);
	//su fibonacci_result_copy: applicare bubble_sort ('copiare' da esempio 004.1arrays-operations)
	bubblesort(fibonacci_result_copy,n+1);

	//confronto
	for(int i=0;i<n+1;++i)
			printf("%ld ",fibonacci_result[i]);
	printf("\n");
	for(int i=0;i<n+1;++i)
		printf("%ld ",fibonacci_result_copy[i]);
	printf("\n");
	//sono uguali
	int cmp=memcmp(fibonacci_result,fibonacci_result_copy,(n+1) * sizeof(long));

	if(cmp==0)
		printf("sono uguali");
	else
		printf("diversi");


	return EXIT_SUCCESS;
	}

unsigned long fibonacci(unsigned int n){
	if(n==0)
		return 0;
	else if(n==1)
		return 1;
	else {
		//fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)  per n > 1
		unsigned long primo=0;
		unsigned long secondo=1;
		int i=1;
		unsigned long terzo=primo+secondo;
		while(i<n){
			terzo=primo+secondo;
			primo=secondo;
			secondo=terzo;
			++i;
			}
		return terzo;
		}
	}

unsigned long * fibonacci_array(unsigned int n){
	unsigned long * array;
	array=calloc(n+1,sizeof(long));
	for(int i=0;i<n+1;++i)
		array[i]=fibonacci(i);
	return array;
	}



//copia array
unsigned long * make_copy_of_array(unsigned long src_array [], unsigned int array_dimension) {

	if (src_array == NULL)
		return NULL;

	unsigned long * result;

	// allochiamo lo spazio di memoria per la copia
	result = malloc(array_dimension * sizeof(long));

	if (result == NULL) {
		return NULL;
	}

	memcpy(result, src_array, array_dimension * sizeof(long));

	return result;
}

void swap(unsigned long *x,unsigned long *y){
	unsigned long z=*x;
	*x=*y;
	*y=z;
	}

//void bubble_sort(int * array, int array_dimension) {


void bubblesort(unsigned long *array, int  size){
	if(size<0){
		perror("dimensione sbagliata");
		exit(EXIT_FAILURE);
		}
	int n=size;
	do{
		int newn=0;
		for(int i=1;i<n;++i){
			if(array[i-1]>array[i]){
				swap(&array[i-1],&array[i]);
				newn=i;
				}
			}
		n=newn;
	}while(n>1);
	}

unsigned long * reverse(unsigned long * array,int  size){
	return reverse_unsigned_long(array,0,size);
	}

unsigned long * reverse_unsigned_long(unsigned long * array, unsigned int i, unsigned int j){
	while (i < j)
		swap(&array[i++], &array[--j]);

	return array;
}

