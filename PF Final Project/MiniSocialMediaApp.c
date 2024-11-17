#include <stdio.h>
#include <string.h>
#include<time.h>

//username length=20
int run=1,loggedIn=0;
char currentUser[20];


typedef struct{
	char user[20] , time[30], category[30], post[251];
}post;