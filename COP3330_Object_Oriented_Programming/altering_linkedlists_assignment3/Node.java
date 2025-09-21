package assignment3;

public class Node{
    private int item;
    private Node next;

    /* An argument constructor to initialize a Node object
	 * @param  num: the value for the new node
	 * No returns */
    public Node(int num){
        item = num;
        next = null;
    }
    
    /* A Getter Function 
     * to get the next node connected to node object
	 * No params
	 * @ return the attribute next of the node object */
    public Node getNext(){
        return next;
    }
    
    /* A Setter Function 
     * to set the next node connected to node object
	 * @param newNext: the new next Node to connect to Node object
	 * No returns */
    public void setNext(Node newNext){
        next = newNext;
    }
    
    /* A Getter Function 
     * to get the element of the node object
	 * No params
	 * @ return the attribute item(the element) of the node object */
    public int getItem(){
        return item;
    }
    
    /* Override To-String Function 
     * to get the String Version of the Node
	 * No params
	 * @ return the String version of the element of the node object */
    public String toString(){
        return ""+getItem();
    }
}