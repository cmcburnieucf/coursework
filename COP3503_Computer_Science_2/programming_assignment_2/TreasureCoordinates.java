/* Carla McBurnie
 * Dr. Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 2
 */


import java.util.*;

public class TreasureCoordinates
{
	public ArrayList<String> determineCoordinates(String coordinates)
	{
        ArrayList<String> result = new ArrayList<>();
        determineCoordinatesR(result, coordinates, 0, 0, coordinates.length());
        return result;
    }
    
    /*Notes for the Function Below: 
    * i = 1, because at index 0 and index len-1, the parentheses are there
    * @ param arr: the ArrayList you will add all possible coordinates to
    * @ param coordinates: stores the string being used
    * @ param task: task keeps track of what task we are at. 
    *   There are three tasks:
    *   task 0, where we place the comma to separate two (potentially) floats
    *   task 1, where we place a decimal to make the first float
    *   task 2, where we place a decimal to make the second float
    * @ param cIndex: keeps track of the index of where the comma is 
    * @ param len: stores the current length of the string
    */
    public void determineCoordinatesR(ArrayList<String> arr, String coordinates, int task, int cIndex, int len)
    {
        //if at the very last task of placing the decimal point on second number:
        if(task == 2)
        { 
            for(int i = cIndex; i < len-1; i++)
            {
                if(((len-1)-i) > 1)
                {
                    //boundary check
                    if(coordinateOk(coordinates, 3, cIndex, i, len))
                    {
                        String newCoordinates = addPunctuation(coordinates, i, len, ".");
                        arr.add(newCoordinates);
                    }
                }
            }
            return;
        }
        //if at the task of placing the decimal point on first number:
        else if(task == 1)
        {
            for(int i = 1; i < cIndex; i++)
            {
                if((cIndex-i) > 1)
                {
                    //boundary check
                    if(coordinateOk(coordinates, 2, cIndex, i, len))
                    {
                        String newCoordinates = addPunctuation(coordinates, i, len, ".");
                        determineCoordinatesR(arr, newCoordinates, task+1, cIndex+3, len+1);
                        arr.add(newCoordinates);
                    }
                }
                else
                {
                    //boundary check
                    if((cIndex-1 == 1) || (!(checkForAllZeroes(coordinates, 1, cIndex)) && (coordinates.charAt(1) != '0')))
                        determineCoordinatesR(arr, coordinates, task+1, cIndex+2, len);
                }
            }
        }
        //if at the task of placing the comma to form two numbers
        else
        {
            for(int i = 1; i < len-2; i++)
            {
                String newCoordinates = addPunctuation(coordinates, i, len, ", ");
                
                /*
                * recursive call to place the decimal point
                * only place decimal point if there are more than 2 numbers
                * make sure to consider the parentheses
                */
                if(len > 4)
                    determineCoordinatesR(arr, newCoordinates, task+1, i+1, len+2);
                
                //boundary check
                if(coordinateOk(coordinates, 1, i, 0, len))
                    arr.add(newCoordinates);
                    
            }
        }
        
        return;
    }
    
    public String addPunctuation(String text, int ssIndex, int len, String punctuation)
    {
        /* create 2 substrings
        * One from the beginning of the string
        * to the index that separate the two substrings
        * And one from that same index to the end of the string
        * and merge them together with a comma
        */
        String leftSubString = text.substring(0, ssIndex+1);
        String rightSubString = text.substring(ssIndex+1, len);
        return (leftSubString + punctuation + rightSubString);
    }
    
    
    public boolean coordinateOk(String coordinates, int separator, int cIndex, int dIndex, int len)
    {
        //in the case of placing the comma
        if(separator == 1)
        {
            if((cIndex != 1) && (coordinates.charAt(1) == '0'))
                return false;
            
            if(coordinates.charAt(cIndex+1) == '0')
                return false;
            
        }
        //in the case of placing the decimal point
        else if(separator == 2)
        {
            //check first floating-point number
            if((dIndex != 1) && (coordinates.charAt(1) == '0'))
                return false;
            
            if(checkForAllZeroes(coordinates, dIndex+1, cIndex))
                return false;
        }
        else
        {
            //check second floating-point number
            if((dIndex != cIndex) && (coordinates.charAt(cIndex) == '0'))
                return false;
            
            if(checkForAllZeroes(coordinates, dIndex+1, len-1))
                return false;
        }
        return true;
    }
    
    public boolean checkForAllZeroes(String coordinates, int beginIndex, int endIndex)
    {
        boolean allZeroes = true;
        for(int i = beginIndex; i < endIndex; i++)
        {
            if(coordinates.charAt(i) == '.' || coordinates.charAt(i) == ',')
                continue;
            else if(coordinates.charAt(i) != '0')
            {
                allZeroes = false;
                break;
            }
                
        }
        return allZeroes;
    }
    
}