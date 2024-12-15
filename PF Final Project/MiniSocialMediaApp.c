#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//username length=20

void registeration();
int login(char *currentUser);
void postMenu(char *currentUser);
void createPost(char *currentUser);
void viewPost();
void xorEncryptDecrypt(char *text);
void deleteUserPosts(char *currentUser);

typedef struct{
	char user[20] , time[30], category[30], post[251];
}post;

int main(void){
    int choice,run=1,loggedIn=0;
    char currentUser[20]="";


    while (run==1){
        if (loggedIn==1){
            postMenu(currentUser);
            loggedIn=0;
        }else{
            printf("------------------------\n");
            printf("---Welcome to Post Vault---");
            printf("\n------------------------\n\n");
            printf("-Login      = 1\n");
            printf("-Register   = 2\n");
            printf("\n-To exit    = 0\n");
            printf("\nChoose an option:");
            scanf("%d",&choice);
            getchar();
            
            switch (choice){
            case 1:
                loggedIn=login(currentUser);
                break;
            
            case 2:
                registeration();
                break;
            

            case 0:
            	printf("\n\n-- Good Bye ! --\n\n");
            	printf("\n\n--You have exited the app--\n\n");
                run=0;
                break;

            default:
                printf("\n\n-------------------------\n");
    			printf("-Invalid choice selected-");
    			printf("\n-------------------------\n\n");
                break;
            }
        }
    }
    return 0;
}

void registeration(){
    char username[20],password[20],storedUsername[20];
    int error=1;
    
    FILE *file=fopen("users.txt","a+");
    if (file == NULL) {
		printf("Error opening file!\n"); 
		return;
	}
    
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
    xorEncryptDecrypt(password);
    password[strcspn(password, "\n")] = 0;

    fprintf(file,"%s\n%s\n",username,password);

    fclose(file);
    
    printf("\n---User registered successfully!---\n\n\n");
}

int login(char *currentUser){
    char username[20],password[20],storedUsername[20],storedPassword[20];
    int found=0;
    
    FILE *file=fopen("users.txt","r");
    if (file == NULL) {
		printf("\nError opening file!\n"); 
		return 0;
	}
    
    printf("\n-------------------\n");
    printf("-   Login Page    -");
	printf("\n-------------------\n");

    while(found==0){
        
        printf("\nEnter your username: ");
        fgets(username,sizeof(username),stdin);
        username[strcspn(username,"\n")]=0;

        printf("Enter your password: ");
        fgets(password,sizeof(password),stdin);
        xorEncryptDecrypt(password);
        password[strcspn(password,"\n")]=0;

        rewind(file);

        while (fgets(storedUsername,sizeof(storedUsername),file) != NULL) {
            storedUsername[strcspn(storedUsername, "\n")] = 0;

            fgets(storedPassword,sizeof(storedPassword),file);
            storedPassword[strcspn(storedPassword, "\n")] = 0;

            if(strcmp(username,storedUsername)==0 && strcmp(password,storedPassword)==0){
                printf("\n\n---Login Successful---\n\n");
                found=1;
                strcpy(currentUser,username);
                fclose(file);
                return 1;
            }
        }

        printf("Wrong password or username! ");
    }

    fclose(file);
    return 0;
}

void postMenu(char *currentUser){
    int choice;

    while(1){
        printf("\n\n-------------------\n");
        printf("-  Post Menu  -");
        printf("\n-------------------\n\n");
        printf("- To Create a post     = 1\n");
        printf("- To View posts        = 2\n");
        printf("- To Delete your Posts = 3\n\n");
        printf("- To Logout            = 0\n\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice);
        getchar();

        switch (choice){
        case 1:
            createPost(currentUser);
            break;

        case 2:
            viewPost();    
            break;
            
        case 3:
        	deleteUserPosts(currentUser);
        	break;

        case 0:
            printf("\n\n-- Good Bye ! --\n\n");
            printf("--You have successfuly logged out!--\n\n");
            return;

        default:
            printf("\n\n-------------------------\n");
    		printf("-Invalid choice selected-");
    		printf("\n-------------------------\n\n");
            break;
        }
    }
}

void createPost(char *currentUser){
	FILE *file=fopen("posts.txt","a+");
	post content;
	if (file == NULL) {
		printf("Error opening file!\n"); 
		return;
	}
	//asking user to select a post category
	int ch,x=0;
	strcpy(content.user,currentUser);
	printf("\n\n-------------------\n");
    printf("-  Create post  -");
    printf("\n-------------------\n\n");
	
	while(x!=1){
	printf("Choose a category for your Post:\n\n 1. Educational\n 2. Inspirational\n 3. Sports\n 4. Technology\n 5. Health and fitness\n 6. Travel\n 7. Food and cooking\n 8. Finance\n 9. Entertainment\n 10. Gaming\n 11. Environment\n\nEnter your choice: ");
    scanf("%d", &ch);
    
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
	            printf("\n\n-------------------------\n");
    			printf("-Invalid choice selected-");
    			printf("\n-------------------------\n\n");
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
    printf("\nEnter your post (max 250 characters): \n");
    fgets(content.post,sizeof(content.post),stdin);
    content.post[strcspn(content.post, "\n")] = '\0'; 
    
    
    //putting everything into the file in a new line
    fprintf(file, "%s\n", content.user);
    fprintf(file, "%s\n", content.category);
    fprintf(file, "%s\n", content.time);
    fprintf(file, "%s\n", content.post);
    
    fclose(file);
}


void viewPost() {
	
    int choice, x, found = 0;
    char username[20], category[30];

    // Get user's choice for search type
    while (1) {
    	printf("\n\n-------------------\n");
    	printf("-  Search post  -");
    	printf("\n-------------------\n\n");
        printf("How do you want to search posts?\n\n");
        printf("1. By Category\n2. By Username\n\nEnter your choice: ");
		scanf("%d", &choice);
        printf("\n-----------------\n");

        if (choice == 1) {
            printf("\nChoose a category:\n\n 1. Educational\n 2. Inspirational\n 3. Sports\n 4. Technology\n 5. Health and fitness\n 6. Travel\n 7. Food and cooking\n 8. Finance\n 9. Entertainment\n 10. Gaming\n 11. Environment\n\nEnter your choice: ");
			scanf("%d",&x);

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
                    printf("\n\n-------------------------\n");
    				printf("-Invalid choice selected-");
    				printf("\n-------------------------\n\n");
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
        	printf("\n\n-------------------------\n");
    		printf("-Invalid choice selected-");
    		printf("\n-------------------------\n\n");
        }
    }

    
    FILE *file = fopen("posts.txt", "r");
    if (file==NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    post search;
    printf("\n\n-------------------\n");
    printf("-    Posts    -");
    printf("\n-------------------\n\n");
    while (1) {
    	//reading file 4 lines at a time
    	if (fgets(search.user, sizeof(search.user), file) == NULL) {
        	break;
	    }
	    if (fgets(search.category, sizeof(search.category), file) == NULL) {
	        break;
	    }
	    if (fgets(search.time, sizeof(search.time), file) == NULL) {
	        break;
	    }
	    if (fgets(search.post, sizeof(search.post), file) == NULL) {
	        break;
	    }
	    
	    search.user[strcspn(search.user, "\n")] = '\0';
	    search.category[strcspn(search.category, "\n")] = '\0';
	    search.time[strcspn(search.time, "\n")] = '\0';
	    search.post[strcspn(search.post, "\n")] = '\0';
        //strcspn(search.user, "\n")  gives the where \n is located so we can remove it

        //Checking for matching posts and displaying them :)
        if ((choice == 2 && strcmp(search.user, username) == 0) ||
            (choice == 1 && strcmp(search.category, category) == 0)) {
            printf("\n(Username): %s\n", search.user);
            printf("(Category): %s\n", search.category);
            printf("(Time & Date): %s\n", search.time);
            printf("(Post Text): %s\n", search.post);
            printf("-------------------------------\n");
            found = 1;
        }
    }

    if (found==0) {
        printf("No matching posts found.\n");
    }

    fclose(file);
}

void xorEncryptDecrypt(char *text) {
	char key = 'K'; // Fixed key
    int textLength = strlen(text); //text length for the loop 
    for (int i = 0;i<textLength; i++) {
        text[i] = text[i] ^ key;
    }
}

void deleteUserPosts(char *currentUser) {
    post content;
    int postCount = 0, choice = 0, currentPost = 0;
    FILE *file = fopen("posts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        if (file != NULL) fclose(file);
        if (tempFile != NULL) fclose(tempFile);
        return;
    }

    // First, display all posts by the user
    printf("\n\n-------------------\n");
    printf("-  Your Posts  -");
    printf("\n-------------------\n\n");
    
    while (1) {
        if (fgets(content.user, sizeof(content.user), file) == NULL)
            break;
        if (fgets(content.category, sizeof(content.category), file) == NULL)
            break;
        if (fgets(content.time, sizeof(content.time), file) == NULL)
            break;
        if (fgets(content.post, sizeof(content.post), file) == NULL)
            break;

        // Removing \n
        content.user[strcspn(content.user, "\n")] = '\0';
        content.category[strcspn(content.category, "\n")] = '\0';
        content.time[strcspn(content.time, "\n")] = '\0';
        content.post[strcspn(content.post, "\n")] = '\0';

        if (strcmp(content.user, currentUser) == 0) {
            postCount++;
            printf("\nPost %d:\n", postCount);
            printf("Category: %s\n", content.category);
            printf("Time & Date: %s\n", content.time);
            printf("Post Text: %s\n", content.post);
            printf("-------------------------------\n");
        }
    }

    if (postCount == 0) {
        printf("No posts found for user '%s'.\n", currentUser);
        fclose(file);
        fclose(tempFile);
        remove("temp.txt");
        return;
    }

    // Prompt the user to select a post to delete
    while (1) {
        printf("Enter the number of the post to delete (1-%d): ", postCount);
        scanf("%d", &choice);
        getchar();
        if (choice >= 1 && choice <= postCount) break;
        printf("Invalid choice. Please try again.\n");
    }

    rewind(file); // Rewind to start of file for processing

    // Copy all posts except the chosen one to the temp file
    postCount = 0;
    while (1) {
        if (fgets(content.user, sizeof(content.user), file) == NULL)
            break;
        if (fgets(content.category, sizeof(content.category), file) == NULL)
            break;
        if (fgets(content.time, sizeof(content.time), file) == NULL)
            break;
        if (fgets(content.post, sizeof(content.post), file) == NULL)
            break;

        // Removing \n
        content.user[strcspn(content.user, "\n")] = '\0';
        content.category[strcspn(content.category, "\n")] = '\0';
        content.time[strcspn(content.time, "\n")] = '\0';
        content.post[strcspn(content.post, "\n")] = '\0';

        if (strcmp(content.user, currentUser) == 0) {
            currentPost++;
            if (currentPost == choice) {
                // Skip the post the user wants to delete
                continue;
            }
        }

        // Write all other posts to the temp file
        fprintf(tempFile, "%s\n%s\n%s\n%s\n", content.user, content.category, content.time, content.post);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temp file
    if (remove("posts.txt") != 0 || rename("temp.txt", "posts.txt") != 0) {
        printf("Error updating posts file.\n");
    } else {
        printf("\n--- Post %d deleted successfully! ---\n", choice);
    }
}
