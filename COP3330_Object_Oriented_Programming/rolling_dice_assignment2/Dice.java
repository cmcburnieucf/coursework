package assignment2;

public class Dice {
	private Die die1;
	private Die die2;
	
	/* A no argument constructor to initialize the two die
	 * No params
	 * No returns */
	public Dice(){
	    die1 = new Die();
	    die2 = new Die();
	}
	
	/* Gets the face value for each die and adds them together
	 * No params
	 * @return   the sum of the dice face values */
	public int getFaceValues(){
	    return die1.getFaceValue() + die2.getFaceValue();
	}
	
	/* A void method to use the Die rolling method to roll both die
	 * No params
	 * No returns */
	public void rollDice(){
	    die1.rollDie();
	    die2.rollDie();
	}
}
