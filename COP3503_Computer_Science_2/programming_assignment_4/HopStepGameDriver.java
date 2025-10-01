/* Name:
 * Dr. Andrew Steinberg
 * COP3503 Fall 2024
 * Programming Assignment 4
 */


public class HopStepGameDriver {
    
    
    public static void main(String [] args)
	{
		HopStepGame tester = new HopStepGame();
		
		int count = 0;
		
		//Test Case 1
		int scenario1 [] = {10,15,20};
		int memo1 [] = new int [scenario1.length];
		System.out.println("Test Case 1 with " + scenario1.length + " squares.");
		
		
		int result1 = Math.min(tester.minCost(scenario1, scenario1.length - 1), tester.minCost(scenario1, scenario1.length - 2));
		int result2 = Math.min(tester.minCostMemoization(scenario1, scenario1.length - 1, memo1), tester.minCostMemoization(scenario1, scenario1.length - 2, memo1));
		int result3 = tester.minCostTabulation(scenario1);
		
		if(result1 == 15 && result1 == result2 && result2 == result3)
			System.out.println("Test Case 1 Passed!");
		else if(result1 != 15 || result2 != 15 ||result3 != 15)
			System.out.println("Test Case 1 didn't Passed! Incorrect result returned for one or more of the methods.");
		else if(result1 != result2 || result2 != result3)
			System.out.println("Test Case 1 didn't Passed! Not all methods are returning the same value.");
		else
			System.out.println("Test Case 1 didn't Passed!");
		
		//Test Case 2
		int scenario2 [] = {25,48,37,66,58,46};
		int memo2 [] = new int [scenario2.length];
		System.out.println("Test Case 2 with " + scenario2.length + " squares.");
		
		
		result1 = Math.min(tester.minCost(scenario2, scenario2.length - 1), tester.minCost(scenario2, scenario2.length - 2));
		result2 = Math.min(tester.minCostMemoization(scenario2, scenario2.length - 1, memo2), tester.minCostMemoization(scenario2, scenario2.length - 2, memo2));
		result3 = tester.minCostTabulation(scenario2);
		
		if(result1 == 120 && result1 == result2 && result2 == result3)
			System.out.println("Test Case 2 Passed!");
		else if(result1 != 120 || result2 != 120 ||result3 != 120)
			System.out.println("Test Case 2 didn't Passed! Incorrect result returned for one or more of the methods.");
		else if(result1 != result2 || result2 != result3)
			System.out.println("Test Case 2 didn't Passed! Not all methods are returning the same value.");
		else
			System.out.println("Test Case 2 didn't Passed!");
		
		//Test Case 3
		int scenario3 [] = {28,61,35,92,95,35,30,79,12,29,20,68,74,75,12,13,22,93,30,30,96,23,71,58,82};
		int memo3 [] = new int [scenario3.length];
		System.out.println("Test Case 3 with " + scenario3.length + " squares.");
		
		result1 = Math.min(tester.minCost(scenario3, scenario3.length - 1), tester.minCost(scenario3, scenario3.length - 2));
		result2 = Math.min(tester.minCostMemoization(scenario3, scenario3.length - 1, memo3), tester.minCostMemoization(scenario3, scenario3.length - 2, memo3));
		result3 = tester.minCostTabulation(scenario3);
		
		if(result1 == 469 && result1 == result2 && result2 == result3)
			System.out.println("Test Case 3 Passed!");
		else if(result1 != 469 || result2 != 469 ||result3 != 469)
			System.out.println("Test Case 3 didn't Passed! Incorrect result returned for one or more of the methods.");
		else if(result1 != result2 || result2 != result3)
			System.out.println("Test Case 3 didn't Passed! Not all methods are returning the same value.");
		else
			System.out.println("Test Case 3 didn't Passed!");
		
		//Test Case 4
		int scenario4 [] = {92,57,63,57,42,55,14,89,98,34,77,77,27,86,73,23,97,33,82,39,35,40,88,54,92,82,24,84,65,85,89,56,23,80,16};
		int memo4 [] = new int [scenario4.length];
		System.out.println("Test Case 4 with " + scenario4.length + " squares.");
		
		result1 = Math.min(tester.minCost(scenario4, scenario4.length - 1), tester.minCost(scenario4, scenario4.length - 2));
		result2 = Math.min(tester.minCostMemoization(scenario4, scenario4.length - 1, memo4), tester.minCostMemoization(scenario4, scenario4.length - 2, memo4));
		result3 = tester.minCostTabulation(scenario4);
		
		if(result1 == 933 && result1 == result2 && result2 == result3)
			System.out.println("Test Case 4 Passed!");
		else if(result1 != 933 || result2 != 933 ||result3 != 933)
			System.out.println("Test Case 4 didn't Passed! Incorrect result returned for one or more of the methods.");
		else if(result1 != result2 || result2 != result3)
			System.out.println("Test Case 4 didn't Passed! Not all methods are returning the same value.");
		else
			System.out.println("Test Case 4 didn't Passed!");
		
		//Test Case 5
		int scenario5 [] = {80,90,20,50,94,32,55,50,32,98,100,17,77,74,39,71,24,36,49,34,72,54,94,80,14,83,11,94,66,31,71,46,53,93,17,35,25,90,13,83,94,81};
		int memo5 [] = new int [scenario5.length];
		System.out.println("Test Case 5 with " + scenario5.length + " squares.");
		
		result1 = Math.min(tester.minCost(scenario5, scenario5.length - 1), tester.minCost(scenario5, scenario5.length - 2));
		result2 = Math.min(tester.minCostMemoization(scenario5, scenario5.length - 1, memo5), tester.minCostMemoization(scenario5, scenario5.length - 2, memo5));
		result3 = tester.minCostTabulation(scenario5);
		
		if(result1 == 1042 && result1 == result2 && result2 == result3)
			System.out.println("Test Case 5 Passed!");
		else if(result1 != 1042 || result2 != 1042 ||result3 != 1042)
			System.out.println("Test Case 5 didn't Passed! Incorrect result returned for one or more of the methods.");
		else if(result1 != result2 || result2 != result3)
			System.out.println("Test Case 5 didn't Passed! Not all methods are returning the same value.");
		else
			System.out.println("Test Case 5 didn't Passed!");
			
	}
}