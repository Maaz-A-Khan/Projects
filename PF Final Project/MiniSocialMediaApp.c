#include <stdio.h>
#include <string.h>
#include<time.h>

void registeration();
void login();
void postMenu();
void createPost();
void viewPost();

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


void login(){
    char username[20],password[20],storedUsername[20],storedPassword[20];
    int found=0;
    
    FILE *file=fopen("users.txt","r");
    
    printf("\n-------------------\n");
    printf("-   Login Page    -");
	printf("\n-------------------\n");

    while(found==0){
        
        printf("\nEnter your username: ");
        fgets(username,sizeof(username),stdin);
        username[strcspn(username,"\n")]=0;

        printf("Enter your password: ");
        fgets(password,sizeof(password),stdin);
        password[strcspn(password,"\n")]=0;

        rewind(file);

        while (fgets(storedUsername,sizeof(storedUsername),file) != NULL) {
            storedUsername[strcspn(storedUsername, "\n")] = 0;

            fgets(storedPassword,sizeof(storedPassword),file);
            storedPassword[strcspn(storedPassword, "\n")] = 0;

            if(strcmp(username,storedUsername)==0 && strcmp(password,storedPassword)==0){
                printf("\n\n---Login Successful---\n\n\n");
                loggedIn=1;
                found=1;
                strcpy(currentUser,username);
                break;
            }
            

        }
        if (found==0){
            printf("Wrong password or username! ");
        }

    }
    fclose(file);
    
}

void postMenu(){
    int choice;

    while(run==1){
        printf("\n\n-------------------\n");
        printf("-  Post Menu  -");
        printf("\n-------------------\n\n");
        printf("- To Create a post = 1\n");
        printf("- To View posts    = 2\n");
        printf("- To Logout        = 0\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        getchar();

        switch (choice){
        case 1:
            createPost();
            break;

        case 2:
            viewPost();    
            break;


        case 0:
            printf("\n\n-- Good Bye ! --\n\n");
            run = 0;
			loggedIn = 0;
            printf("\n\n--You have successfuly logged out!--\n\n");
            break;

        default:
            printf("Invalid choice selected");
            break;
        }
    }
}


void createPost(){
	FILE *file=fopen("posts.txt","a+");
	post content;
	if (file == NULL) {
		printf("Error opening file!\n"); 
		return;
	}
	//asking user to select a post category
	int ch,x=0;
	strcpy(content.user,currentUser);
	printf("Choose a category for your Post:\n 1. Educational\n 2. Inspirational\n 3. Sports\n 4. Technology\n 5. Health and fitness\n 6. Travel\n 7. Food and cooking\n 8. Finance\n 9. Entertainment\n 10. Gaming\n 11. Environment\n Enter your choice: ");
    scanf("%d", &ch);
    while(x!=1){
		x=1;
	    switch (ch) {
	        case 1:
	            strcpy(content.category,"Educational");
	            break;
	        case 2:
	            strcpy(content.category,"Inspirational");
	            break;
	        case 3:
	            strcpy(content.category,"Sports");
	            break;
	        case 4:
	            strcpy(content.category,"Technology");
	            break;
	        case 5:
	            strcpy(content.category,"Health and Fitness");
	            break;
	        case 6:
	            strcpy(content.category,"Travel");
	            break;
	        case 7:
	            strcpy(content.category,"Food and Cooking");
	            break;
	        case 8:
	            strcpy(content.category,"Finance");
	            break;
	        case 9:
	            strcpy(content.category,"Entertainment");
	            break;
	        case 10:
	            strcpy(content.category,"Gaming");
	            break;
	        case 11:
	            strcpy(content.category,"Environment");
	            break;
	        default:
	            printf("\nInvalid choice. Try Again\n");
	            x=0;
	            break;
	    }
	}
	
	//getting time and date from system
	static char buffer[80];
    time_t t;
    struct tm *tm_info;
    time(&t);
    tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    strcpy(content.time,buffer);
    
    //inputting post from user
    getchar(); 
    printf("Enter your post (max 250 characters): \n");
    fgets(content.post, sizeof(content.post), stdin);
    content.post[strcspn(content.post, "\n")] = '\0'; 
    
    
    //putting everything into the file in a new line
    fprintf(file, "%s\n", content.user);
    fprintf(file, "%s\n", content.category);
    fprintf(file, "%s\n", content.time);
    fprintf(file, "%s\n", content.post);
}

void viewPost() {
    int choice, x, found = 0;
    char username[20], category[30];

    // Get user's choice for search type
    while (1) {
        printf("How do you want to search posts?\n");
        printf("1. By Category\n2. By Username\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Choose a category:\n 1. Educational\n 2. Inspirational\n 3. Sports\n 4. Technology\n 5. Health and fitness\n 6. Travel\n 7. Food and cooking\n 8. Finance\n 9. Entertainment\n 10. Gaming\n 11. Environment\n Enter your choice: ");
			scanf("%d",x);

            
            switch (x) {
                case 1: 
					strcpy(category, "Educational"); 
					break;
                case 2: 
					strcpy(category, "Inspirational"); 
					break;
                case 3: 
					strcpy(category, "Sports"); 
					break;
                case 4: 
					strcpy(category, "Technology"); 
					break;
                case 5: 
					strcpy(category, "Health and Fitness"); 
					break;
                case 6: 
					strcpy(category, "Travel"); 
					break;
                case 7: 
					strcpy(category, "Food and Cooking"); 
					break;
                case 8: 
					strcpy(category, "Finance"); 
					break;
                case 9: 
					strcpy(category, "Entertainment"); 
					break;
                case 10: 
					strcpy(category, "Gaming"); 
					break;
                case 11: 
					strcpy(category, "Environment"); 
					break;
                default:
                    printf("Invalid choice. Try again.\n");
                    continue;//if choice is invalid the line below are not gonna be executed
                    //instead the loop will reiterate from the start 
            }
            break;
        } else if (choice == 2) {
            printf("Enter the Username: ");
            getchar(); 
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = '\0'; 
            break; 
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    
    FILE *file = fopen("posts.txt", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    post search;
    while (1) {
    	//reading file 4 lines at a time
        if (fgets(search.user, sizeof(search.user), file) == NULL) break;
        if (fgets(search.category, sizeof(search.category), file) == NULL) break;
        if (fgets(search.time, sizeof(search.time), file) == NULL) break;
        if (fgets(search.post, sizeof(search.post), file) == NULL) break;

        search.user[strcspn(search.user, "\n")] = '\0';
        search.category[strcspn(search.category, "\n")] = '\0';
        search.time[strcspn(search.time, "\n")] = '\0';
        search.post[strcspn(search.post, "\n")] = '\0';

        //Checking for matching posts and displaying them :)
        if ((choice == 2 && strcmp(search.user, username) == 0) ||
            (choice == 1 && strcmp(search.category, category) == 0)) {
            printf("(Username): %s\n", search.user);
            printf("(Category): %s\n", search.category);
            printf("(Time & Date): %s\n", search.time);
            printf("(Post Text): %s\n", search.post);
            printf("-------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No matching posts found.\n");
    }

    fclose(file);
}

