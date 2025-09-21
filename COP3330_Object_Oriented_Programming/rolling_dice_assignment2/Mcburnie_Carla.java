package assignment2;

public class Mcburnie_Carla {
	public static void main(String[] args) {
		//array to keep track of occurrences of the dice values
	    int[] occurrences = new int[11];
	    
	    Dice testDice = new Dice(); //dice used for testing
	    
	    //loop for rolling the dice 1000 times
	    for(int i = 0; i < 1000; i++){
	        testDice.rollDice();
	        //add the value of rolled dice to the array for record
	        occurrences[testDice.getFaceValues()-2]++;
	    }
	    
	    //loop for printing out all occurrences
	    for(int i = 0; i < 11; i++){
	        System.out.println("Number of "+ (i+2) +"s are "+ occurrences[i]);
	    }
	    
	    System.out.println("Graph");
	    
	    int y = 150; //y-axis label
	    
	    //loop for printing entire graph
	    for(int i = 0; i < 7; i++){
	    	//an if-elseif-else case used 
	    	//to determine the formatting of the y-xis
	    	if(y > 75) {
	    		//print just the line because all 3 digits are filled
	    		System.out.print(y + "|");
	    	}
	    	else if(y < 100 && y > 0) {
	    		//print a space, the number, and the line
	    		//because one more digit needs to be filled in
	    		System.out.print(" " + y + "|");
	    	}
	    	else {
	    		//print two spaces, the number, and the line
	    		//because two more digits need to be filled in
	    		System.out.print("  " + y + "|");
	    	}
	    	//end of y-axis formatting if-elseif-else case
	    	
	    	//loop for printing the stars on the graph
	        for(int j = 0; j < 11; j++){
	            if(occurrences[j] > y){
	                System.out.print("*  ");
	            }
	            else{
	                System.out.print("   ");
	            }
	        } //end of inner loop
	        
	        //print new line and decrease y
	        //to move to the next lower label on y-axis
	        System.out.println();
	        y -= 25;
	    } //end of outer for loop
	    
        //print x-axis
	    System.out.println("    --------------------------------");
	    System.out.println("    2  3  4  5  6  7  8  9 10 11 12 ");
	}//end of main function


}
