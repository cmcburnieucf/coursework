package assignment3;

public class LinkedList{
    private Node head;

    public LinkedList(){
        head = null;
    }
    
    /* A Checker Function 
     * to see if the linked list has any nodes or not
	 * No params
	 * @ return the value of the linked list head */
    public boolean isEmpty(){
        return (head == null);
    }
    
    /* A Getter Function 
     * to get the head node of the LinkedList object
	 * No params
	 * @ return the head object of the LinkedList object */
    public Node getHead(){
        return head;
    }
    
    /* A Setter Function 
     * to set the head object of the LinkedList object
	 * @param newHead: a node object to replace head object
	 * No returns */
    public void setHead(Node newHead){
        head = newHead;
    }
    
    /* A LinkedList Function 
     * to add nodes to end of the current LinkedList
	 * @param num: the element of the to-be-added node 
	 * No returns */
    public void addNode(int num){
        Node newNode = new Node(num);

        if(isEmpty()){
            head = newNode;
        }
        else{
            Node cur = head;
            while(cur.getNext() != null){
                cur = cur.getNext();
            }
            cur.setNext(newNode);
        }
    }
    
    /* A LinkedList Function 
     * to remove the node containing a specific number from LinkedList
	 * @param num: the number of the node object to be removed
	 * No returns */
    public void removeNode(int num){
        if(!isEmpty()){
            if(head.getItem() == num){
                head = head.getNext();
            }else{
                Node cur = head;
                while((cur.getNext() != null) && (cur.getNext().getItem() != num)){
                    cur = cur.getNext();
                }

                if(cur.getNext() != null){
                    cur.setNext(cur.getNext().getNext());
                }
            }

        }
    }
}
