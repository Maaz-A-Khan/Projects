#include <stdio.h>
#include <string.h>
#include<time.h>

void registeration();

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


void registeration(){
    char username[20],password[20],storedUsername[20];
    int error=1;
    
    FILE *file=fopen("users.txt","a+");
    
    printf("\n-------------------\n");
    printf("-Registration Page-");
	printf("\n-------------------\n");

    while(error==1){
        
        printf("\nEnter a username: ");
        fgets(username,sizeof(username),stdin);
        username[strcspn(username,"\n")]=0;

        error=0;
        rewind(file);
        
        while (fgets(storedUsername,sizeof(storedUsername),file) != NULL) {
            storedUsername[strcspn(storedUsername,"\n")]=0;

            if (strcmp(username,storedUsername)==0){
                printf("Username already taken, Try another one");
                error=1;
                break;
            }
            fgets(storedUsername,sizeof(storedUsername),file);
        }        
    }

    printf("Enter a password: ");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password, "\n")] = 0;

    fprintf(file,"%s\n%s\n",username,password);

    fclose(file);
    
    printf("\n---User registered successfully!---\n\n\n");
}
