package assignment2;

import java.util.Random;

public class Die {
	private int faceValue;
	
	/* A no argument constructor to 
	 * initialize a die with face value of 1
	 * No params
	 * No returns */
	public Die(){
	    setFaceValue(1);
	}
	/* An argument constructor to 
	 * initialize a die with face value of param
	 * @param   num: the number of the face value
	 * No returns */
	public Die(int num){
	    setFaceValue(num);
	}
	/* A void setter function to set face value of the die
	 * @param   num: the number of the face value
	 * No returns */
	public void setFaceValue(int num){
		//make sure face value is realistic
		//meaning in between 1 and 6 inclusive
	    if(num >= 1 && num <= 6) {
	    	faceValue = num;
	    }
	    else {
	    	//if not so, set it to a default value
	    	faceValue = 1;
	    }
		
	}
	/* A getter function to get the face value of the die
	 * no parameters
	 * @return   the face value of the die object */
	public int getFaceValue(){
	    return faceValue;
	}
	
	/* A void method to randomly assign numbers
	 * in between 1 and 6 (inclusive) to the die object
	 * to simulate rolling the die
	 * No params
	 * No returns */
	public void rollDie(){
	    Random randomNum = new Random();
	    int newFaceValue = randomNum.nextInt(6)+1;
	    setFaceValue(newFaceValue);
	}
}
