#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
//#include <time.h>

typedef struct Node{
    
    int subtrie_amount;
    int amount;
    struct Node * children[32]; // 0 to v, index 0 to 32
    //             Conversion Chart
    // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
    //  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
    //--------------------------------------------
    // 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
    //  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  
}node;


//prototypes
int findIndex(char character);
node * addResponse(node * trie_root, char * response, int food);
node * changeResponse(node * trie_root, char * response, char * new_response);
void findSum(node * trie_root, char * response);
void deleteTrie(node * trie_root);

int findIndex(char character)
{
    int res = (int)character;
    
    //if greater than or equal to the ASCII value of a
    if(res >= 97) 
    {
        //use this for characters a - v
        res -= 87;
    }
    else
    {
        //use this for characters 0 - 9
        res -= 48;
    }
    
    return res;
}


node * addResponse(node * trie_root, char * response, int food)
{
    node * cur = trie_root;
    //the root accounts for the food in the entire trie
    cur->subtrie_amount += food; 
    
    int index = 0;
    int size = strlen(response);
    
    while(index < size)//while not end of word(aka response)
    {
        int child_index = findIndex(response[index]);// getting correct child index
        
        if(cur->children[child_index] == NULL)//if letter does not already exist
        {
            //create a new node for letter
            cur->children[child_index] = (node *) malloc(sizeof(node));
            cur->children[child_index]->subtrie_amount = 0; //safeguard against garbage values
            cur->children[child_index]->amount = 0; //safeguard against garbage values
        }
        
        if(index == (size-1))//if at last letter
        {
            cur->children[child_index]->amount += food;
        }
        
        cur->children[child_index]->subtrie_amount += food;
        
        //go to next letter
        cur = cur->children[child_index];
        index++;
    }
    
    return trie_root;
}


node * changeResponse(node * trie_root, char * response, char * new_response)
{
    node * cur = trie_root;
    int index = -1; //-1 to account for the root
    int size = strlen(response);
    int loss;
    
    node * new_cur = trie_root;
    int new_index = -1; //-1 to account for the root
    
    //find amount for given response through path transversal
    while(index < (size-1))
    {
        if(cur == NULL)
        {
            break;
        }
        
        int child_index = findIndex(response[(index+1)]);
        cur = cur->children[child_index];
        index++;
    }
    
    int transfer_amount = cur->amount;
    cur->amount = 0;
    
    //remove the amount from the path
    while(new_index < size)
    {
        if(new_cur == NULL)
        {
            break;
        }
        
        new_cur->subtrie_amount -= transfer_amount;
        
        //stop at current node; job is finished
        if(new_index == (size-1))
        {
            break;
        }
        
        int child_index = findIndex(response[(new_index+1)]);
        new_cur = new_cur->children[child_index];
        new_index++;
    }
    
    return addResponse(trie_root, new_response, transfer_amount);
}


void findSum(node * trie_root, char * response)
{
    node * cur = trie_root;
    
    int index = 0;
    int size = strlen(response);
    int sum = 0;
    
    while(index < size)
    {
        if(cur == NULL)
        {
            break;
        }
        sum += cur->amount;
        int child_index = findIndex(response[index]);
        cur = cur->children[child_index];
        index++;
    }
    
    if(cur != NULL)
    {
        sum += cur->subtrie_amount;
        printf("%d %d\n", cur->subtrie_amount, sum);
    }
    else
    {
        printf("0 %d\n", sum);
    }
}


void deleteTrie(node * trie_root)
{
    if(trie_root == NULL) return;
    
    for(int i = 0; i < 32; i++)
    {
        deleteTrie(trie_root->children[i]);
    }
    
    free(trie_root);
    trie_root = NULL;
}


int main()
{
    node * trie_root = (node *) malloc(sizeof(node));
    trie_root->subtrie_amount = 0;
    trie_root->amount = 0;
    int stop = 0;
    
    while(!stop)
    {
        char command[7];
        char response[100001];
        int food;
        char new_response[100001];
        
        scanf("%s", command);
        
        if(strcmp(command, "ADD") == 0)
        {
            scanf("%s%d", response, &food);
            trie_root = addResponse(trie_root, response, food);
        }
        else if(strcmp(command, "CHANGE") == 0)
        {
            scanf("%s%s", response, new_response);
            trie_root = changeResponse(trie_root, response, new_response);
        }
        else if(strcmp(command, "SUM") == 0)
        {
            scanf("%s", response);
            findSum(trie_root, response);
        }
        else
        {
            stop = 1;
            break;
        }
    }
    
    deleteTrie(trie_root);

    return 0;
}
