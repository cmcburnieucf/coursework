#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Family{
   
   int cat_index; //-1 if no cat
   int position; //what position the family is at
   int moves; //how many cages the family moves down by
   char suffix[4]; //letters added to cat's name
   
}family;

void calculateWeek(char ** cats, family * families, int size, int num_weeks)
{
    //calculating weekly cage layouts
    for(int i = 0; i < num_weeks; i++)
    {
        //iterate through the families, starting with family 1
        for(int j = 0; j < 3; j++)
        {
            //if a family needs to return a cat first
            if(families[j].cat_index != -1)
            {
                //modify family's foster cat's name
                strcat(cats[families[j].cat_index], families[j].suffix);
                //return cat
                families[j].cat_index = -1;
            }
            
            //if cat is not already taken
            if((families[j].position != families[((j+1)%3)].cat_index) && (families[j].position != families[((j+2)%3)].cat_index))
            {
                //take the cat
                families[j].cat_index = families[j].position;
            }
            
            //move the family down the cages
            families[j].position = (families[j].position + families[j].moves) % size;
        }
    }
    
    //printing results
    for(int i = 0; i < size; i++)
    {
        //if cat is with a foster family
        if((i == families[0].cat_index) || (i == families[1].cat_index) || (i == families[2].cat_index))
        {
            printf("No cat found.\n");
        }
        else
        {
            printf("%s\n", cats[i]);
        }
    }
}


int main()
{
    char ** cats = NULL;
    int size; //Holds the number of cats
    int num_weeks;//holds the number of weeks to pass
    family families[3]; //holds the foster families
    
    //initializing array
    for(int i = 0; i < 3; i++)
    {
        families[i].cat_index = -1;
        families[i].position = i;
    }
    families[0].moves = 2;
    strcpy(families[0].suffix, "Lee");
    families[1].moves = 3;
    strcpy(families[1].suffix, "Lyn");
    families[2].moves = 5;
    strcpy(families[2].suffix, "Eve");
    
    scanf("%d%d", &size, &num_weeks);
    
    //allocate memory for the 2D cats array
    cats = (char **) malloc(sizeof(char *) * size);
    
    //read in all the names while creating memory/space for them
    for(int i = 0; i < size; i++)
    {
        cats[i] = malloc(sizeof(char) * ((3 * num_weeks)+19+1));
        scanf("%s", cats[i]);
    }
    
    calculateWeek(cats, families, size, num_weeks);
    
    //freeing dynamic memory
    for(int i = 0; i < size; i++)
    {
        free(cats[i]);
    }
    free(cats);

    return 0;
}

