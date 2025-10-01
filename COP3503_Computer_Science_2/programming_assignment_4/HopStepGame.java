/* Name: Carla J McBurnie
 * Dr. Andrew Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 4
 */

import java.util.*;

public class HopStepGame
{
    //Regular Dynammic Solution Method
    public int minCost(int[] squares, int numSquares)
    {
        if(numSquares < 0) //a boundary check, just in case
            return 0;
        
        //if at the 2nd or 1st square, we reached the starting point
        if(numSquares <= 1)
            return squares[numSquares];
        
        //otherwise return calculated value
        return squares[numSquares] + Math.min(minCost(squares, numSquares-1), minCost(squares, numSquares-2));
    }
    
    //The Memoziation Method - Top-Down, Recursive
    public int minCostMemoization(int[] squares, int numSquares, int[] results)
    {
        //if value has already been calculated, return it
        if(results[numSquares] != 0)
            return results[numSquares];
        
        if(numSquares < 0) //just in case, a boundary check
            return 0;
        
        //if at the 2nd or 1st square, we reached the starting point
        if(numSquares <= 1)
        {
            //save the result in the memo array and return it
            results[numSquares] = squares[numSquares];
            return results[numSquares];
        }
        
        //otherwise, calculate, save, and return the minimum cost at that square
        results[numSquares] = squares[numSquares] + Math.min(minCost(squares, numSquares-1), minCost(squares, numSquares-2));
        return results[numSquares];
    }
    
    //The Tabulation Method - Bottom-up, Iterative
    public int minCostTabulation(int[] squares)
    {
        //create array to store the results of what's been calculated
        int[] results = new int[squares.length+1];
        
        //the starting point has no cost
        results[0] = 0;
        
        //save value of the first square
        results[1] = squares[0];
        
        //find min cost in iterative fashion
        for(int i = 2; i < squares.length+1; i++)
        {
            results[i] = squares[i-1] + Math.min(results[i-1], results[i-2]);
        }
        
        //return either the 2nd-to-last result or last result
        //depending on who is smaller
        return Math.min(results[squares.length], results[squares.length-1]);
    }
}

