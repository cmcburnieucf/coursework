#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  long long int data;
  struct Node *next;
} node;

typedef struct Stack {
  node *top;
} stack;

void push(stack * stack, long long int value)
{
    node * new_node = (node *) malloc(sizeof(node));
    new_node->data = value;
    
    new_node->next = stack->top;
    stack->top = new_node;
}

void pop(stack * stack)
{
    if(stack->top == NULL)
    {
        return;
    }
    
    node * temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    
}

//using merge sort to sort shop wealth from least to greatest
void mergeSortArray(long long int * shops, int len)
{
    //base case
    if(len <= 1)//if empty or just one element
    {
        return;
    }
    
    //first divide array into smaller pieces...
    int half_len = len / 2;
    
    //recursion on first half
    mergeSortArray(shops, half_len);
    //recursion on last half
    mergeSortArray(&shops[half_len], (len - half_len));
    
    //create temporary array to hold new sorted array TEMPORARILY
    long long int * temp_arr = (long long int *) malloc(sizeof(long long int) * len);
    
    int fh_index = 0; //index for the first half
    int lh_index = 0; //index for the last half
    
    //merge second half and last half in a sorted order
    //remember: i is for the index of the temporary array
    for(int i = 0; i < len; i++)
    {
        //if first half is empty
        //or we are done going through it...
        if(fh_index == half_len)
        {
            temp_arr[i] = shops[(half_len + lh_index)];
            lh_index++;
        }
        //if last half is empty
        //or we are done going through it...
        else if(lh_index == (len - half_len))
        {
            temp_arr[i] = shops[fh_index];
            fh_index++;
        }
        //if value from first half is smaller than value from second half...
        else if(shops[fh_index] <= shops[(half_len + lh_index)])
        {
            temp_arr[i] = shops[fh_index];
            fh_index++;
        }
        //if value from first half is larger than value from second half...
        else
        {
            temp_arr[i] = shops[(half_len + lh_index)];
            lh_index++;
        }
    }
    
    //copy over sorted data from temp array to real array
    for(int i = 0; i < len; i++)
    {
        shops[i] = temp_arr[i];
    }
    
    free(temp_arr);
}


//functions returns the number of bought shops
int buyoutShops(stack * buyables, stack * unbuyables, long long int bts, long long int highest_wealth)
{
    int bought_shops = 0;
    
    //check to see if goal is already met
    if(bts > highest_wealth)
    {
        return bought_shops;
    }
    
    //if goal has not been met, buy some shops
    while((bts <= highest_wealth))
    {
        //if there is nothing else to buy
        if(buyables->top == NULL)
        {
            break;
        }
        //greatest buyable wealth is top of buyable stack
        //add that value to bts wealth
        bts += buyables->top->data;
        bought_shops++;//increase counter
        
        //once used, remove from buyable stack
        pop(buyables);
        
        //before proceeding, check if goal is met
        if(bts > highest_wealth)
        {
            break;
        }
        
        //if not, then look for more buyables shops from unbuyable stack
        if(unbuyables->top != NULL)
        {
            while((unbuyables->top->data < bts) && (unbuyables->top != NULL))
            {
                push(buyables, unbuyables->top->data);
                pop(unbuyables);
            }
        }
    }
    
    //check final result
    if(bts <= highest_wealth)
    {
        //if goal was not met...
        return -1;
    }
    else
    {
        return bought_shops;
    }
}

int main()
{
    int num_shops;//store the number of other shops
    long long int bts;//store amount of BTS wealth
    long long int highest_wealth; //store highest wealth
    scanf("%d%lld", &num_shops, &bts);
    
    //an dynamic array to store the wealth of the other shops
    //num_shops also serves as the length of the array
    long long int * shops = (long long int *) malloc(sizeof(long long int) * num_shops);
    
    int buyable_count = 0;
    int unbuyable_count = 0;
    
    //enter in data and store that data
    for(int i = 0; i < num_shops; i++)
    {
        scanf("%lld", &shops[i]);
        //while doing so, find number of shops bts can buy
        if(shops[i] < bts)
        {
            buyable_count++;
        }
        else
        {
            unbuyable_count++;
        }
    }
    
    long long int * buyable_shops = (long long int *) malloc(sizeof(long long int) * buyable_count);
    long long int * unbuyable_shops = (long long int *) malloc(sizeof(long long int) * unbuyable_count);
    
    int buyable_index = 0;
    int unbuyable_index = 0;
    
    //split shops into buyables and unbuyables
    for(int i = 0; i < num_shops; i++)
    {
        if(shops[i] < bts)
        {
            buyable_shops[buyable_index] = shops[i];
            buyable_index++;
        }
        else
        {
            unbuyable_shops[unbuyable_index] = shops[i];
            unbuyable_index++;
        }
    }
    
    //free no longer need array
    free(shops);
    
    //sort buyables and unbuyables with merge sort
    mergeSortArray(buyable_shops, buyable_count);
    mergeSortArray(unbuyable_shops, unbuyable_count);
    
    highest_wealth = unbuyable_shops[unbuyable_count-1];
    
    //create and initialize buyable and unbuyable stacks
    stack * buyables = (stack *) malloc(sizeof(stack));
    buyables->top = NULL;
    stack * unbuyables = (stack *) malloc(sizeof(stack));
    unbuyables->top = NULL;
    
    //store buyable shops in buyable stack
    //the top is the one with the greatest wealth
    for(int i = 0; i < buyable_count; i++)
    {
        push(buyables, buyable_shops[i]);
    }
    //store unbuyable shops in unbuyable stack
    //the top is the one with the least wealth
    for(int i = (unbuyable_count-1); i > -1; i--)
    {
        push(unbuyables, unbuyable_shops[i]);
    }
    
    //free no longer needed arrays
    free(buyable_shops);
    free(unbuyable_shops);
    
    //find number of shops bought
    int bought_shops = buyoutShops(buyables, unbuyables, bts, highest_wealth);
    printf("%d\n", bought_shops);//print results
    
    //delete stacks
    while(buyables->top != NULL)
    {
        pop(buyables);
    }
    free(buyables);
    
    while(unbuyables->top != NULL)
    {
        pop(unbuyables);
    }
    free(unbuyables);

    return 0;
}

