/* Carla J McBurnie
   Dr. Steinberg
   COP3503 Fall 2024
   Programming Assignment 3
*/

import java.util.*;
import java.io.*;

public class GreedyChildren
{
    //array to hold sweet levels of the candies
    int[] greedFactors; 
    //array to hold greedy levels of the children
    int[] sweetFactors;
    //number of happy children in the end
    int numHappy; 
    //number of angry children in the end
    int numAngry;
    
    public GreedyChildren(int numCandies, int numChildren, String greedFile, String sweetFile){
        //transfer data from files to integer arrays
        greedFactors = read(greedFile, numChildren);
        sweetFactors = read(sweetFile, numCandies);
        
        //sort both arrays to make solving the problem easier
        Arrays.sort(greedFactors);
        Arrays.sort(sweetFactors);
        
        //initialize the counters
        numHappy = 0;
        numAngry = 0;
    }
    
    public void greedyCandy()
    {
        //save the sizes of the arrays into variables
        int gArrSize = greedFactors.length-1;
        int sArrSize = sweetFactors.length-1;
        
        /*
            iterate through the greedy array
            since it is the smaller one and it will end first
        */
        for(int i = gArrSize; i >= 0; i--)
        {
            if(sweetFactors[sArrSize] >= greedFactors[i]) //give it to the child
            {
                numHappy++; //increment the number of happy children
                //move pointer to next candy to show current candy is taken
                sArrSize--;
            }
            else //save the candy for the next child
                numAngry++;//increment the number of angry children
        }
    }
    
    public void display()
    {
        //display number of happy and angry at the end
        System.out.println("There are "+numHappy+" happy children.");
        System.out.println("There are "+numAngry+" angry children.");
    }
    
    public int[] read(String filename, int n)
    {
        int[] arr = new int[n]; //initialize resulting array
        
        BufferedReader reader = null;
        
        //counter to keep track of the current index
        int i = 0;
        
        try
        {
            reader = new BufferedReader(new FileReader(filename));
            String newline = null;
            
            //until end of file, keep reading
            while((newline = reader.readLine()) != null)
            {
                //add each string as integer in the array
                arr[i] = Integer.parseInt(newline);
                i++;
            }
            
            reader.close();
        }
        catch(Exception e)
        {
            //if error, print the error out
            e.printStackTrace();            
        }
        
        return arr; // return resulting array
    }
}