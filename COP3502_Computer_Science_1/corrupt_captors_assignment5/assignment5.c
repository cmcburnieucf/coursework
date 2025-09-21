#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int hat_size; //priority
    int location; //value/key
    long long int food; //other data
    struct Node *left, *right, *parent; //connections
}node;

node * createNode(int location, int hat_size, node * parent)
{
    node * new_node = (node *) malloc(sizeof(node));
    new_node->location = location;
    new_node->hat_size = hat_size;
    new_node->food = 0;
    new_node->left = new_node->right = NULL;
    new_node->parent = parent;
    
    return new_node;
}

//Find the Node that is closest to given location
node * findClosest(node * root, int value, node * end_point)
{
    if(root == NULL)
    {
        return NULL;
    }
    
    int best_dist = 1000000001;
    
    node * tmp = root;
    node * closest_tmp = NULL;
    
    //while not at designated point, look among the hierachy 
    while(tmp != end_point)
    {
        if(tmp == end_point)
        {
            break;
        }
        
        int tmp_dist = abs(((tmp->location)-(value)));
        int left_dist = 1000000001;
        int right_dist = 1000000001;
        
        //checking for one-child cases
        if((tmp->left != NULL) && (tmp->left != end_point))
        {
            left_dist = abs(((tmp->left->location)-(value)));
        }
        if((tmp->right != NULL) && (tmp->right != end_point))
        {
            right_dist = abs(((tmp->right->location)-(value)));
        }
        
        if((right_dist < left_dist) && (right_dist <= tmp_dist))//right node is closest
        {
            if(right_dist < best_dist)//if better than best difference
            {
                best_dist = right_dist;
                closest_tmp = tmp->right;
            }
            tmp = tmp->right;
        }
        else if((left_dist < right_dist) && (left_dist <= tmp_dist))//left node is closest
        {
            if(left_dist < best_dist)//if better than best difference
            {
                best_dist = left_dist;
                closest_tmp = tmp->left;
            }
            tmp = tmp->left;
        }
        else if((tmp_dist < left_dist) && (tmp_dist < right_dist)) //current node is closest
        {
            if((tmp_dist < best_dist) && (tmp != end_point))
            {
                best_dist = tmp_dist;
                closest_tmp = tmp;
            }
                
            if(value < tmp->location)
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
        }
    }
    
    return closest_tmp;
}

//LEFT rotation, given node
node * rotateLeft(node * root)
{
    if((root == NULL) && (root->right == NULL))
    {
        return NULL;
    }
    
    node * parent = root->parent;
    node * child = root->right;
    node * grandchild = child->left;
    
    child->parent = parent;
    
    if((parent != NULL) && (root == parent->right))
    {
        parent->right = child;
    }
    else if((parent != NULL) && (parent == parent->left))
    {
        parent->left = child;
    }
    
    root->parent = child;
    
    if(grandchild != NULL)
    {
        grandchild->parent = root;
    }
    
    root->right = grandchild;
    child->left = root;
    
    return child;
}

//RIGHT rotation, given node
node * rotateRight(node * root)
{
    if((root == NULL)&&(root->left == NULL))
    {
        return NULL;
    }
    node * parent = root->parent;//parent->parent
    node * child = root->left;
    node * grandchild = child->right;
    
    child->parent = parent;
    
    if((parent != NULL) && (root == parent->right))
    {
        parent->right = child;
    }
    else if((parent != NULL) && (root == parent->left))
    {
        parent->left = child;
    }
    
    root->parent = child;
    
    if(grandchild != NULL)
    {
        grandchild->parent = root;
    }
    
    root->left = grandchild;
    child->right = root;
    
    return child;
}

node * placeHat(node * root, int location, int hat_size)
{
    if(root == NULL)
    {
        return NULL;
    }
    
    //find closest node
    node * closest = findClosest(root, location, NULL);
    
    //make sure result is not NULL
    if(closest == NULL)
    {
        return root;
    }
    
    if(hat_size > closest->hat_size)
    {
        closest->hat_size = hat_size;
    }
    
    //place new leader in proper place by rotation
    //make sure new leader has a parent too
    while((closest->parent != NULL) && (closest->hat_size > closest->parent->hat_size))
    {
        if(closest->parent->left == closest)
        {
            closest = rotateRight(closest->parent);
        }
        else
        {
            closest = rotateLeft(closest->parent);
        }
    }
    
    if(closest->parent == NULL)
    {
        root = closest;
    }
    
    return root;
}

void steal(node * root, int location, int food)
{
    if(root == NULL)
    {
        return;
    }
    
    //find closest raccoon
    node * temp = findClosest(root, location, NULL);
    
    while((temp->parent != NULL) && (food > 0))
    {
        temp->food += food/2;
        food -= food/2;
        
        temp = temp->parent;
    }
    
    //if at root, the raccoon at root takes all the leftovers
    if((temp->parent == NULL) && (food > 0))
    {
        temp->food += food;
    }
}

node * add(node * root, node * parent, int location, int hat_size)
{
    if(root == NULL)
    {
        root = createNode(location, hat_size, parent);
        return root;
    }
    
    //using location as determining factor for greater than and less than
    if(location < root->location)//look left if less than
    {
        root->left = add(root->left, root, location, hat_size);
        
        //move the raccoon with bigger hat up
        if(root->left->hat_size > root->hat_size)
        {
            root = rotateRight(root);
        }
    }
    else//look right if greater than, assuming no duplicates
    {
        root->right = add(root->right, root, location, hat_size);
        
        //move the raccoon with bigger hat up
        if(root->right->hat_size > root->hat_size)
        {
            root = rotateLeft(root);
        }
    }
    
    return root;
}

node * capture(node * root, int location)
{
    if(root == NULL)
    {
        return root;
    }
    
    //find and save exact location of to-be-removed node
    node * cur = findClosest(root, location, NULL);
    node * cur_parent = cur->parent;
    
    printf("Captured Food Amnt: %lld\n", cur->food);
    
    //if to-be-removed node has children (it is not a leaf node)
    if(!((cur->left == NULL) && (cur->right == NULL)))
    {
        node * best_candidate;
        
        //get best candidate from each side of to-be-removed node
        node * best_left;
        node * best_right;
        node * best_parent;
        
        best_left = findClosest(cur->left, location, NULL);
        best_right = findClosest(cur->right, location, NULL);
        best_parent = findClosest(root, location, cur);
        
        int left_dist = 1000000001;
        if(best_left != NULL)
        {
            left_dist = abs(((best_left->location)-(location)));
        }
        
        int right_dist = 1000000001;
        if(best_right != NULL)
        {
            right_dist = abs(((best_right->location)-(location)));
        }
        
        int parent_dist = 1000000001;
        if(best_parent != NULL)
        {
            parent_dist = abs(((best_parent->location)-(location)));
        }
        
        if((left_dist < right_dist) && (left_dist < parent_dist))
        {
            //best candidate from left side is closer
            best_candidate = best_left;
        }
        else if((right_dist < left_dist) && (right_dist < parent_dist))
        {
            //best candidate from right side is closer
            best_candidate = best_right;
        }
        else if((parent_dist < left_dist) && (parent_dist < right_dist))
        {
            //best candidate from above current node is closer
            best_candidate = best_parent;
        }
        else
        {
            //best candidates from all sides are equidistant
            //so compare hat sizes; smaller hat = better candidate
            if(best_left->hat_size < best_right->hat_size)
            {
                //best candidate from the left is better by hat size
                best_candidate = best_left;
            }
            else
            {
                //best candidate from the right is better by hat size
                best_candidate = best_right;
            }
            //don't need to compare parent hat size bc that one will always be bigger    
        }
        
        //swap data between best candidate and to-be-removed node
        //ONLY if it is left child or right child
        if((best_candidate == best_left) || (best_candidate == best_right))
        {
            best_candidate->hat_size = cur->hat_size;
            cur->location = best_candidate->location;
            cur->food = best_candidate->food;
            
            node * temp = best_candidate;
            best_candidate = cur;
            cur = temp;
        }
        
        //if deleted node is not at the bottom after swapping, bring it down
        if(!((cur->left == NULL) && (cur->right == NULL)))
        {
            while(!((cur->left == NULL) && (cur->right == NULL)))
            {
                if(cur->left == NULL) //can only go right
                {
                    rotateLeft(cur);
                }
                else if(cur->right == NULL)
                {
                    rotateRight(cur); //can only go left
                }
                else //both child nodes exist, so go with bigger hat
                {
                    if(cur->left->hat_size > cur->right->hat_size)
                    {
                        rotateRight(cur);
                    }
                    else
                    {
                        rotateLeft(cur);
                    }
                }
                
                if((cur->left == NULL) && (cur->right == NULL))
                {
                    break;
                }
            }
        }
    }
    
    if(cur->parent->left == cur)
    {
        cur->parent->left = NULL;
    }
    else
    {
        cur->parent->right = NULL;
    }
    
    free(cur);
    cur = NULL;
    
    return root;
}

void printTree(node * root)
{
    if(root == NULL)
    {
        return;
    }
    
    printf("%d %lld\n", root->location, root->food);
    printTree(root->left);
    printTree(root->right);
}

void freeTree(node * root)
{
    if(root == NULL)
    {
        return;
    }
    
    //use post order to free the tree
    //free children (if not already freed), and then free parent
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    node* root = NULL;
    
    int stop = 0;
    
    while(!stop)
    {
        char command[8];
        int location;
        int hat_size;
        
        scanf("%s", command);
        
        //if command is ADD
        if((strcmp(command, "ADD")) == 0)
        {
            scanf("%d%d", &location, &hat_size);
            root = add(root, NULL, location, hat_size);
        }
        //if command is CAPTURE
        else if((strcmp(command, "CAPTURE")) == 0)
        {
            scanf("%d", &location);
            root = capture(root, location);
        }
        //if command is HAT
        else if((strcmp(command, "HAT")) == 0)
        {
            scanf("%d%d", &location, &hat_size);
            root = placeHat(root, location, hat_size);
        }
        //if command is STEAL
        else if((strcmp(command, "STEAL")) == 0)
        {
            long long int food_size;
            scanf("%d%lld", &location, &food_size);
            steal(root, location, food_size);
        }
        //if none of them, assume it is quit
        else
        {
            stop = 1;
            printTree(root);
            break;
        }
    }
    
    //free the memory; delete all nodes
    freeTree(root);
    
    return 0;
}

