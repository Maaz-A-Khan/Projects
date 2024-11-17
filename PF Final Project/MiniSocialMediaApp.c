#include <stdio.h>
#include <string.h>
#include<time.h>

//username length=20
int run=1,loggedIn=0;
char currentUser[20];


typedef struct{
	char user[20] , time[30], category[30], post[251];
}post;

int main(void){
    int choice;

    while (run==1){
        if (loggedIn==1){
            postMenu();
        }else{
            printf("------------------------\n");
            printf("---Welcome to Tweet---");
            printf("\n------------------------\n\n");
            printf("-Login      = 1\n");
            printf("-Register   = 2\n");
            printf("\n\n-To exit    =0\n");
            printf("\nChoose an option:");
            scanf("%d",&choice);
            getchar();
            
            switch (choice){
            case 1:
                login();
                break;
            
            case 2:
                registeration();
                break;

            case 0:
                printf("Good Bye !");
                run=0;
                break;

            default:
                printf("Invalid option");
                break;
            }
        }
    }

}