#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
    int top;//holds number of movements
    char * directions; //holds the movements of the elephants
    int max;
}stack;

typedef struct Elephant{
    int row; //holds current row location
    int col; //holds current column location
    stack memory;
}elephant;

void push(elephant * pests, int index, char direction);
void pop(elephant * pests, int index);
void addBait(int ** grid, int r, int c, int w);
int eatNGo(elephant * pests, int ** grid, int size);


int main()
{
    //creating a dynamic 2D grid
    int ** grid = (int **) malloc(501 * sizeof(int *));//allocating 500 rows
    
    for(int r = 0; r < 501; r++)//r stands for row
    {
        grid[r] = (int *) malloc(501 * sizeof(int));//allocating 501 columns
    }
    
    //initializing the grid
    //getting rid of all garbage values
    for(int i = 0; i < 501; i++)
    {
        for(int j = 0; j < 501; j++)
        {
            grid[i][j] = 0;
        }
    }
    
    int size;
    
    scanf("%d", &size);
    
    //allocating memory for array of elephants
    elephant * pests = (elephant *) malloc(sizeof(elephant) * size);
    
    //finding initial location for the elephants
    for(int i = 0; i < size; i++)
    {
        int r; //row id
        int c; //column id
        
        scanf("%d%d", &r, &c);
        
        pests[i].row = r;
        pests[i].col = c;
        
        //setting up the location memory
        pests[i].memory.directions = (char *) malloc(sizeof(char) * 24);
        pests[i].memory.max = 24;
        pests[i].memory.top = 0;
    }
    
    char word[5];
    
    while(strcmp(word, "QUIT") != 0)
    {
        char command[5];
        
        scanf("%s", command);
        
        if(strcmp(command, "BAIT") == 0)
        {
            int r;
            int c;
            int w;
            
            scanf("%d%d%d", &r, &c, &w);
            
            addBait(grid, r, c, w);
        }
        else if(strcmp(command, "HOUR") == 0)
        {
            printf("%d\n", eatNGo(pests, grid, size));
        }
        else if(strcmp(command, "QUIT") == 0)
        {
            strcpy(word, command);
        }
    }
    
    //print results
    for(int i = 0; i < size; i++)
    {
        printf("%d %d\n", pests[i].row, pests[i].col);
    }
    
    //free the dynamic memory
    for(int r = 0; r < 501; r++)//r stands for row
    {
        free(grid[r]);
    }
    
    free(grid);
    
    for(int i = 0; i < size; i++)
    {
        free(pests[i].memory.directions);
    }
    
    free(pests);
    
    return 0;
}


void push(elephant * pests, int index, char direction)
{
    if(pests[index].memory.top == pests[index].memory.max)//if stack is full
    {
        //double the size and reallocate the memory
        pests[index].memory.max *= 2;
        pests[index].memory.directions = (char *) realloc(pests[index].memory.directions, sizeof(char) * pests[index].memory.max);
    }
    
    //add recent movement to stack
    pests[index].memory.directions[(pests[index].memory.top)] = direction;
    (pests[index].memory.top)++;//update top of the stack
}


void pop(elephant * pests, int index)
{
    if(pests[index].memory.top > 0) //if stack is not empty
    {
        char direction = pests[index].memory.directions[(pests[index].memory.top)-1];
        
        if(direction == 'N')
        {
            pests[index].row++;
        }
        else if(direction == 'S')
        {
            pests[index].row--;
        }
        else if(direction == 'E')
        {
            pests[index].col--;
        }
        else if(direction == 'W')
        {
            pests[index].col++;
        }
        
        (pests[index].memory.top)--;//updating top of stack
    }
}


void addBait(int ** grid, int r, int c, int w)
{
    grid[r][c] = w;//place watermelons at cell
}


int eatNGo(elephant * pests, int ** grid, int size)
{
    int total = 0; //total watermelons eaten
    
    //move each elephant to nearest watermelon
    for(int i = 0; i < size; i++)
    {
        //variables to make things easier
        int r = pests[i].row;
        int c = pests[i].col;
        int current = grid[r][c]; //current location
        int north = grid[(r-1)][c]; //up a row = north
        int south = grid[(r+1)][c]; //down a row = south
        int east = grid[r][(c+1)]; //right to a column = east
        int west = grid[r][(c-1)]; //left to a column = west
        
        //if current location has watermelons, do not move
        if(current > 0)
        {
            pests[i].row = pests[i].row;
            pests[i].col = pests[i].col;
        }
        //if north has the most watermelons of other places
        else if((north > south) && (north > east) && (north > west) && (current == 0))
        {
            push(pests, i, 'N');
            (pests[i].row)--;
        }
        //if south has the most watermelons of other places
        else if((south > north) && (south > east) && (south > west) && (current == 0))
        {
            push(pests, i, 'S');
            (pests[i].row)++;
        }
        //if east has the most watermelons of other places
        else if((east > north) && (east > south) && (east > west) && (current == 0))
        {
            push(pests, i, 'E');
            (pests[i].col)++;
        }
        //if west has the most watermelons of other places
        else if((west > north) && (west > south) && (west > east) && (current == 0))
        {
            push(pests, i, 'W');
            (pests[i].col)--;
        }
        //if no nearby place has watermelons, retrace steps
        else if((north == 0) && (south == 0) && (east == 0) && (west == 0) && (current == 0))
        {
            pop(pests, i);
        }
    }
    
    //the watermelons are then eaten by the elephants
    for(int i = 0; i < size; i++)
    {
        //if there are watermelons at current location
        if(grid[(pests[i].row)][(pests[i].col)] > 0)
        {
            total += grid[(pests[i].row)][(pests[i].col)];
            grid[(pests[i].row)][(pests[i].col)] = 0;
        }
    }
    
    return total;
}
