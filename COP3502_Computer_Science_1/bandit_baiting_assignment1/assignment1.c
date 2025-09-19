#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Location{
    
    char name[20]; //N
    long long int id; //D
    long long int food_level; //F
    long long int taken;
}location_t;

typedef struct ArrayList{
    
    int size;
    int max;
    location_t * arr; //array of locations
}list_t;

int addLocation(list_t * places);
void displayResults(list_t * places);

int main()
{
    //initializing array list
    list_t places;
    places.size = 0;
    places.max = 10;
    places.arr = (location_t *) malloc((places.max) * (sizeof(location_t)));
    
    int stopping_point = 0;
    
    //keep adding until END
    while(stopping_point == 0)
    {
        stopping_point = addLocation(&places);
    }
    
    displayResults(&places);
    
    free(places.arr);
    //free(places);
    
    return 0;
}


int addLocation(list_t * places)
{
    if(places->size == places->max)
    {
        //if full, double max size
        places->max *= 2;
        places->arr = (location_t *) realloc(places->arr, (places->max)*(sizeof(location_t)));
    }
    
    char new_name[20];
    long long int new_id;
    long long int new_food;
    
    scanf("%s%lld%lld", new_name, &new_id, &new_food);
    
    if(((strcmp(new_name, "END")) == 0) && (new_id == -1) && (new_food == -1))
    {
        return 1;
    }
    else if((new_id < -1000000000) && (new_id > 1000000000))
    {
        return 0;
    }
    else if((new_id < 0) && (new_id > 1000000000))
    {
        return 0;
    }
    else
    {
        int existence = 0;
        
        //loop through array to find same location
        for(int i = 0; i < places->size+1; i++)
        {
            if(((strcmp(new_name, places->arr[i].name)) == 0) && (new_id == places->arr[i].id))
            {
                //the place already exists so...
                existence++;
                
                //see if any food was taken
                if(new_food < places->arr[i].food_level)
                {
                    //if true, update the amount taken
                    places->arr[i].taken += ((places->arr[i].food_level) - (new_food));
                    printf("%lld\n", ((places->arr[i].food_level) - (new_food)));
                }
                else
                {
                    printf("0\n");
                }
                places->arr[i].food_level = new_food; //update food level
            }
        }
        
        
        if(existence == 0)
        {
            printf("New placement.\n");
            
            //adding new placement to array
            strcpy(places->arr[places->size].name, new_name);
            places->arr[places->size].id = new_id;
            places->arr[places->size].food_level = new_food;
            
            places->size++;
        }
        
        return 0;
    }
}

void displayResults(list_t * places)
{
    //merging the same locations into one
    for(int i = 0; i < places->size; i++)
    {
        //checking to see if the location was not already merged
        if(places->arr[i].taken != -1)
        {
            for(int j = 1; j < places->size; j++)
            {
                //checking to see if the location was not already merged
                if((places->arr[j].taken != -1) && (i != j))
                {
                    //same name means same location
                    if((strcmp(places->arr[i].name, places->arr[j].name)) == 0)
                    {
                        places->arr[i].taken += places->arr[j].taken;
                        
                        //getting rid of the other location
                        strcpy(places->arr[j].name, "NULL");
                        places->arr[j].id = -1;
                        places->arr[j].food_level = -1;
                        places->arr[j].taken = -1;
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < places->size; i++)
    {
        if(places->arr[i].taken != -1)
        {
            //displaying end results
            printf("%s ", places->arr[i].name);
            printf("%lld\n", places->arr[i].taken);
        }
    }
    
}

