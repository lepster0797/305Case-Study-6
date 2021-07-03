/* Code was written by AHMAD ALIF BIN JAMIL on 2/07/2021 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Write a complete program to perform the following task:
a) Define a struct named, Players to store the following data:
    i. Player’s name
    ii. Player’s team number
    iii. The number of score goal
    iv. The number of yellow cards
b) Declare an array variable of type Players, named info to store data for 50 Players.
c) Define a function for each of the following with at least one parameter.

    i. readPlayer: read the Players data into array info.
    ii. findPlayerName: find the Players’ name that were given yellow cards and
    display their names along with the number of yellow cards.
    iii. highestScore: find and display the player name

*/
//Declaring Player struct. 
typedef struct Players{
   char name[25];
   int team_number; 
   int goal;
   int yellow_card; 
}players;

//players info[50];

//function prototypes
void readPlayer(FILE *fp, struct Players);
void findPlayerName(struct Players *, size_t);
void highestScore(struct Players *, size_t);

int comparator(const void *v1 , const void *v2){ //go read  https://www.cplusplus.com/reference/cstdlib/qsort/
    
    //making struct pointers that point to v1 and v2
    const struct Players *elem1 =  v1; 
    const struct Players *elem2 =  v2;
    //elem1 and elem2 are going to be accesssing the .goal member of the Players struct
    
    //if elem 1 is greater than elem2, if it is elem1 goes first before elem2
    if(elem1->goal > elem2 ->goal){
        return -1;
    }
    //if elem1 and elem2 are equal do nothing
    else if(elem1->goal == elem2->goal){
        return 0;
    }
    //if elem1 is less than elem2 then elem 1 goes AFTER elem2
    else if(elem1->goal < elem2->goal){
        return 1;
    }
}

void highestScore(struct Players info[25], size_t n) //basically im just sorting everything and displaying the one with the highest goals :) 
{
    //qsort() sorts the array by goals in descending order and puts the highest goal scored at the start of array at index 0
    //go read  https://www.cplusplus.com/reference/cstdlib/qsort/
    qsort(info,n,sizeof(players),comparator); 
    printf("\nProgram: %s has the highest goals at %d total! \n",info[0].name, info[0].goal );
    printf("\nPlayer Name: %s\nTeam Number: %d\nGoals: %d\nYellow Cards: %d\n" ,info[0].name,  info[0].team_number, info[0].goal, info[0].yellow_card);
}
void readPlayers(FILE *fp , struct Players * info){   //parses the playerdata.txt file and stores it inside of the struct

    //some variables
    char name[25];                                     //variable
    int team_number, goal , yellow_card, i = 0;        //more variables
    const unsigned MAX_LENGTH = 256;                   //more variables, max length because i want to scan for a maximum of 256 characters :)
    char buffer[MAX_LENGTH];                           //more variables
   
   //go google fgets() 
   //looping through the text file, storing each line inside a "buffer"
    while(fgets(buffer, MAX_LENGTH, fp) != NULL){      //takes stuff from text file, stores it in "buffer"

        //taking the line inside the buffer and storing it inside these variables, 
        sscanf(buffer, "%s%d%d%d", name, &team_number, &goal, &yellow_card);

            //assigning the values from the above variables to the current indexed array.
            strcpy(info[i].name, name);
            info[i].team_number = team_number;
            info[i].goal = goal;
            info[i].yellow_card = yellow_card;

            i++;
    }

    fclose(fp); // closes the file
    return; 
    
}

//this thing lets u search the known list
void findPlayerName(struct Players * info, size_t n){   

    //some variables n stuff                                                    
    char search_key[25];                                        //creating a search_key of chartype size of 25
    printf("Me: I want to look for a player who got a yellow card! \n");
    printf("\nProgram: Who do you want to search for?\n");
    scanf(" %s", &search_key);                                  //getting input for search_key
    int found = 1;                                              //found variable
    char name[25];                                              //name variable
    int yellowcard = 0;                                         //yellowcard variable
    printf("\nLooking for : %s \n" , search_key);

    //loops through the array 
   for(int i = 0; i < n; i++){
       //comparing the name in the search_key to the name of the currently indexed array.
       if(strcmp(info[i].name,search_key) == 0){
           //if it's the same copy them into local variables
            strcpy(name,info[i].name);
            yellowcard = info[i].yellow_card;
            //set found = 0 because if not it'll mess the program up, stupid C language
            found = 0;  
            break;
        //if not , set found = 1
       }else
       {
           found = 1; 
       }     
    }
        //checking the value of found
        if(found == 0){
            printf("\nPlayer Name: %s \nYellow Cards: %d" ,name, yellowcard);
        }
        else{
            printf("\nNope, doesnt exist.");
        }   

}
//main function//
int main(){

    char *filename = "../ASS305/playerdata.txt";            //Opening playerdata.txt
    struct Players info[50];                                //declaring a struct instance as an array
    int i = 0, isContinue = 1 , option;                     //some variables
    size_t n = 50;                                          //array size
    FILE *playerdata = fopen(filename, "r");                //open file name = defined as 'filename' , storing inside variable playerdata.
    
    //check to see if playerdata is empty ornot , if it's empty theres something wrong with opening it.
    if(playerdata == NULL) {
        printf("Error in opening file\n"); 
        return 1;
}   
    
    //calling readPlayers function to read and parse the textfile
    readPlayers(playerdata, info);                    

    //all the crap u see in the command line is done inside the while loop
    while(isContinue == 1){
        printf("\n\nWhat do you want to do?");
        printf("\n1 - Look for a player who got a yellow card.");
        printf("\n2 - Look at the highest score. \n");
        scanf(" %d", &option);

        if(option == 1){ //if option is one, call findPlayerName
            system("cls");
            findPlayerName(info, n);
        }
        else if(option == 2){ //if option is 2, call highestScore
            system("cls"); 
            highestScore(info, n);
        } 
        //ask user if they wanna use the program again 
        printf("\nProgram: Do you want to keep using the program? \n1-Yes\n2-No\n"); 
        scanf("%d",&isContinue);    
        if(isContinue == 1){

            //clears the command line, cls = clear screen
            system("cls");
            printf("Program : Hi again!");
        }
        else
            printf("Goodbye :)");
    }          
        return 0;
    
}  
