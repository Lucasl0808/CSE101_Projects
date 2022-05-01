/* Lucas Lee
 * luclee
 * pa4
 * CSE101-02 Spring 2022
 */
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

int main(void){
	List L = newList();
	int x = 100;
	int y = 101;
	int z = 200;
	append(L, &x);
	append(L, &y);
	append(L, &z);
	printf("length = %d\n", length(L));
	//printList(stdout, L);
	for(moveFront(L); index(L) >=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");
	moveFront(L);
	printf("index = %d\n", index(L));
	printf("current = %d\n", *(int *)front(L));
	printf("back = %d\n", *(int *)back(L));
	
	freeList(&L);
}
