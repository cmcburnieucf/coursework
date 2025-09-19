#include <stdio.h>
#include <stdlib.h>

typedef struct CozyData{
    int cat_ids[15];
    int cat_count;
    int data;
    
}cozydata;

int ** cozy_lvls;//same as saying int cozy_lvls[15][15];
int ** cozy_bases;//same as saying int cozy_bases[3][15];
cozydata * cozyDataBase; //same as saying cozydata cozyDataBase[15];
int db_size = 0; //holds current size of database
int db_max; //holds max size of database
/*
in used array and combo array,
0 = not used, not in combo
1 = used, in combo
*/
int * used; //same as saying int used[15];
int * combo;//same as saying int combo[15];
int combo_len = 0;//the number of elements in combo

//for conditions in C: if(x != 0) {..} is the same as if(x){..}

//initial parameters: index=0, cur_size=0, size=size
//function determines all combinations without using cozy bases
void catCombinations(int cur_size, int size)
{
    //if we reached the max cats house can have
    if(cur_size == (size-2))
    {
        return;//go back to outer loop
    }
    
    for(int i = 0; i < size; i++)
    {
        if(used[i])//skip all the used values
        {
            continue;
        }
        if(combo_len > 0)//if there are other cats
        {
            int sum = 0;
            //check if database is full
            if(db_size == db_max)
            {
                //double the size of database
                cozyDataBase = (cozydata *) realloc(cozyDataBase, sizeof(cozydata) * (2*db_max));
                db_max *= 2;//set to the size of new database
            }
            //getting rid of any garbage values
            for(int j = 0; j < size; j++)
            {
                cozyDataBase[db_size].cat_ids[j] = 0;
            }
            for(int j = 0; j < size; j++)
            {
                //if combo[j] == 1, AKA if cat #j is in combo
                if(combo[j])
                {
                    //add other cats from the combo to database
                    cozyDataBase[db_size].cat_ids[j] = 1;
                    cozyDataBase[db_size].cat_count++;
                    sum += cozy_lvls[i][j];
                    sum += cozy_lvls[j][i];
                }
            }
            //add current cat to database too
            cozyDataBase[db_size].cat_ids[i] = 1;
            cozyDataBase[db_size].cat_count++;
            //add non-house-dependent cozy level to database
            cozyDataBase[db_index].data = sum;
            db_size++;//increase after adding data to database
        }
        combo[i] = 1;
        combo_len++;//add current cat to number of cats in house
        used[i] = 1;
        catCombinations(cur_size+1, size);//moving to inner loop
        //undoing updates as we go back to outer loop
        combo_len--;
        combo[i] = 0;
    }
    
    //resetting used array for current loop and further inner loops
    for(int i = cur_size; i < size; i++)
    {
        used[i] = 0;
    }
}



void housePermutations(int * db_combo)
{
    
    
    
}






//initial arguments: count = 0, cur_size = 0, size = size
void houseCombinations(int sum, int cur_size, int size, int * db_combo, int * db_used)
{
    //if we reached the end,
    //assuming the combination satisfies all houses
    if(cur_size == 3)
    {
        housePermutations(db_combo);
        return;
    }
    
    //going through each index of the database
    for(int i = 0; i < db_size; i++)
    {
        int possibility = 1;
        
        //if at second or third house
        if(cur_size > 0)
        {
            //compare and make sure the same cat is not in two places
            for(int j = 0; j < db_size; j++)
            {
                //check if it is in combo
                if(db_combo[j] == 1)
                {
                    for(int k = 0; k < db_size; k++)
                    {
                        if(db_combo[k] == 1)
                        {
                            if(cur_size == 1)
                            {
                                
                            }
                            else if(cur_size == 2)
                            {
                                for(int m = 0; m < db_size; m++)
                                {
                                    if(db_combo[m] == 1)
                                    {
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        if(possibility != 1)
        {
            continue;
        }
        
        sum += cozyDataBase[i].cat_count;
        int remaining = sum - size;
        //at second house
        if((cur_size == 1) && (remaining <= 0))
        {
            sum -= cozyDataBase[i].cat_count;
            continue;
        }
        //at third house
        else if((cur_size == 2) && ((remaining > 0) || (remaining < 0)))
        {
            sum -= cozyDataBase[i].cat_count;
            continue;
        }
        
        db_combo[i] = 1;
        db_used[i] = 1;
        
        houseCombinations(sum, cur_size+1, size, db_combo, db_used);
        //removing updates
        db_combo[i] = 0;
    }
    //resetting used array for current loop and further inner loops
    for(int i = 0; i < cur_size; i++)
    {
        used[i] = 0;
    }
}


/*
1st iteration = 0, 2nd iteration = 1, 3rd iteration = 2
using test case 4:
1st iteration: 2 or 1 correct
2nd iteration: 2 + 2 = 4, not correct, 2 + 1 correct
3rd iteration: 2 + 2 + 2 = 6, not correct, 2 + 1 + 2 = 5 not correct, 2 + 1 + 1 correct







*/

int main()
{
    int size;
    
    printf("Enter number of cats: ");
    scanf("%d", &size);
    
    //allocating memory to dynamic array rows
    cozy_bases = (int **) malloc(sizeof(int *) * 3);
    cozy_lvls = (int **) malloc(sizeof(int *) * size);
    
    //allocating memory to used, combo, and database arrays
    used = (int *) malloc(sizeof(int) * size);
    combo = (int *) malloc(sizeof(int) * size);
    cozyDataBase = (cozydata *) malloc(sizeof(cozydata) * (size*2));
    db_max = size*2;
    
    for(int i = 0; i < size; i++)
    {
        //allocating memory to the cozy_lvls columns
        cozy_lvls[i] = (int *) malloc(sizeof(int) * size);
        //at the same time, initializing used array and combo array
        used[i] = 0;
        combo[i] = 0;
    }
    for(int i = 0; i < 3; i++)
    {
        //allocating memory to the cozy_bases columns
        cozy_bases[i] = (int *) malloc(sizeof(int) * size);
    }
    
    //gathering input
    for(int i = 0; i < size; i++)
    {
        printf("Enter cozy bases: ");//get rid of later
        scanf("%d%d%d", &cozy_bases[0][i], &cozy_bases[1][i], &cozy_bases[2][i]);
    }
    for(int i = 0; i < size; i++)
    {
        printf("Enter cozy levels: ");//get rid of later
        for(int j = 0; j < size; j++)
        {
            scanf("%d", &cozy_lvls[i][j]);
        }
    }
    
    //entering the cozy bases in database
    for(int i = 0; i < size; i++)
    {
        //check if database is full
        if(db_index == db_max)
        {
            //if so, double the size of database
            cozyDataBase = (cozydata *) realloc(cozyDataBase, sizeof(cozydata) * (2*db_max));
            db_max *= 2;//set to the size of new database
        }
        
        cozyDataBase[db_size].cat_ids[i] = 1;
        cozyDataBase[db_size].cat_count[i] = 1;
        cozyDataBase[db_size].data[i] = 0;
    }
    
    //calling recursive function
    //cur_size = 0 because we have added no cats yet
    //size = number of cats user said there was 
    catCombinations(0, size);
    
    //hold the ids of the database structures that work well as a combo
    int * db_combo = (int *) malloc(sizeof(int) * db_size);
    //hold the ids of database structure that have been used
    int * db_used = (int *) malloc(sizeof(int) * db_size);
    //initialize combo and used array
    for(int i = 0; i < db_index; i++)
    {
        db_combo[i] = 0;
        db_used[i] = 0;
    }
    
    //using the database,
    //find all combinations that would work
    //while at the same time, finding the max coziness
    houseCombinations(0, 0, size, db_combo, db_used);
    
    //freeing allocated memory
    free(cozyDataBase);
    cozyDataBase = NULL;
    free(used);
    used = NULL;
    free(combo);
    combo = NULL;
    
    free(db_used);
    db_used = NULL;
    free(db_combo);
    db_combo = NULL;
    
    for(int i = 0; i < size; i++)
    {
        free(cozy_lvls[i]);
        cozy_lvls[i] = NULL;
    }
    for(int i = 0; i < 3; i++)
    {
        free(cozy_bases[i]);
        cozy_bases[i] = NULL;
    }
    free(cozy_lvls);
    cozy_lvls = NULL;
    free(cozy_bases);
    cozy_bases = NULL;
    
    return 0;
}














































