package assignment3;

import java.io.*;

public class LinkedListTester {
	public static void main(String[] args) {
		LinkedList newList = new LinkedList();
		
        BufferedReader reader = null;
        String line = null;
        
        //read in the file and save it in a string
        //assumption: all the integers are on one line separated by spaces
        try{
            reader = new BufferedReader(new FileReader("data.txt"));
            line = reader.readLine();
            reader.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }
        
        //after making sure input has been stored in string
        //separate the numbers and store them in the linked list
        if(line != null) {
        	String[] nums = line.split(" ");
        	for(int i = 0; i < nums.length; i++) {
        		if(Integer.parseInt(nums[i]) > 0) {
        			newList.addNode(Integer.parseInt(nums[i]));
        		}
        	}
        }
        else {
        	System.out.println("Line is Null");
        }
        
        //alter linked list by shrinking it
        newList = shrinkList(newList);
        
        BufferedWriter writer = null;
        //write altered linked list into new file
        try{
            writer = new BufferedWriter(new FileWriter("processed.txt", true));
            Node cur = newList.getHead();
            
            while(cur != null) {
            	writer.write((cur.toString()+" "));
            	cur = cur.getNext();
            }
            writer.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }
        
	}//end of main function
	
	public static LinkedList shrinkList(LinkedList listX){
	    int res = 0;
	    int count = -100;
	    
	    res = (listX.getHead().getItem()*2)+7;
	    if(listX.getHead().getNext().getItem() == res){
	        Node replacement = new Node(count);
	        count++;
	        replacement.setNext(listX.getHead().getNext().getNext());
	        listX.setHead(replacement);
	    }//end of if-case for head of linked list
	    
	    Node cur = listX.getHead();
	    
	    //while we have two nodes to possibly alter
	    //AND a connection with the previous node of the first possibly altered node
	    //go through the rest of the linked list
	    while((cur != null) && (cur.getNext() != null) && (cur.getNext().getNext() != null)){
	        res = (cur.getNext().getItem()*2)+7;
	        if(cur.getNext().getNext().getItem() == res){
	            //make replacement node
	            Node replacement = new Node(count);
	            count++;
	            //connect replacement node to last deleted node's next node
	            replacement.setNext(cur.getNext().getNext().getNext());
	            //connect replacement node to first deleted node's previous node
	            cur.setNext(replacement);
	        }
	        cur = cur.getNext();
	    }// end of while loop
	    
	    //final alterations
	    //assuming that cur.getNext().getNext() is null
	    //and you are adding to the tail
	    if((cur.getNext() != null)) {
	    	if(cur.getNext().getItem() >= 0) {
	    		Node finalCount = new Node(count);
	    		cur.getNext().setNext(finalCount);
	    	}
	    }
	    else {
	    	if(cur.getItem() >= 0) {
	    		Node finalCount = new Node(count);
	    		cur.setNext(finalCount);
	    	}
	    }
	    
	    //return altered list
	    return listX;
	}// end of shrinkList function
}
