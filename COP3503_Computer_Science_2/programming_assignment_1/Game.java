/*
* Carla McBurnie
* Dr. Steinberg
* COP3503 Fall 2024
* Programming Assignment 1
*/

import java.util.*;

public class Game
{
	private int[][] board = new int[8][8];
	private char[] moves = {'d','r','b'};
	private Random randObj;
	
	public Game(Random randObj){
	    this.randObj = randObj;
	    initBoard();
	}
	
	public char selectPlayerTwoMove(){
	    //if in last row, the only move that can be made is right
	    if(checkGivenRow(7) == 1){
	        return moves[1];
	    }
	    //if in last col, the only move that can be made is down
	    else if(checkGivenCol(7) == 1){
	        return moves[2];
	    }
	    //otherwise, do as you please
	    else{
	        return moves[randObj.nextInt(3)];
	    }
	    
	}
	
	public int play(){
	    char p2move = 'd';
	    int lastmove = 0;
	    
	    //first, move diagonal to get ahead of player 2
	    moveKnight('d', false);
	    
	    //player 2's Move
	    p2move = selectPlayerTwoMove();
	    moveKnight(p2move, false);
	    
	    //while Knight piece is not in last square:
	    while(board[7][7] != 1){
	        char p2MoveCpy;
	        
	        //if in last row, the only move you can do is right
	        if(checkGivenRow(7) == 1){
	            p2MoveCpy = 'r';
	        }
	        //if in last col, the only move you can do is bottom
	        else if(checkGivenCol(7) == 1){
	            p2MoveCpy = 'b';
	        }
	        //otherwise, copy the other player
	        else{
	            p2MoveCpy = p2move;
	        }
	        moveKnight(p2MoveCpy, false);
	        
	        //if, after your move, you won, end loop
	        if(board[7][7] == 1){
	            lastmove = 1;
	            break;
	        }
	        
	        //player 2's move
	        p2move = selectPlayerTwoMove();
	        moveKnight(p2move, false);
	        
	        //if, after your move, you lost, end loop
	        if(board[7][7] == 1){
	            lastmove = -1;
	            break;
	        }
	    }
	    
	    //return who won
	    return lastmove;
	}
	
	public int checkGivenRow(int n){
	    for(int i = 0; i < 8; i++){
	        if(board[n][i] == 1)
	            return 1;
	    }
	    return 0;
	}
	
	public int checkGivenCol(int n){
	    for(int i = 0; i < 8; i++){
	        if(board[i][n] == 1)
	            return 1;
	    }
	    return 0;
	}
	
	public void moveKnight(char val, boolean revert){
	    int r = 0;
	    int c = 0;
	    
	    //first find the knight piece
	    for(int i = 0; i < 8; i++){
	        for(int j = 1; j < 8; j++){
	            if(board[i][j] == 1){
	                r=i;
	                c=j;
	                break;
	            }
	        }
	    }
	    
	    board[r][c]=0;
	    
	    //assuming val is not an invalid move:
	    if(val == moves[0]){
	        if(revert == true){
	            //if not in first row or first col
	            if(checkGivenCol(0) != 1 && checkGivenRow(0) != 1){
	                //play reverse-diagonal: move up one row and left one col
	                board[r-1][c-1]=1;
	            }
	        }
	        else{
	            //if not in last row or last col
	            if(checkGivenCol(7) != 1 && checkGivenRow(7) != 1){
	                //play diagonal: move down one row and right one col
	                board[r+1][c+1]=1;
	            }
	        }
	    }
	    else if(val == moves[1]){
	        if(revert == true){
	            //if not in first col
	            if(checkGivenCol(0) != 1){
	                //play reverse-right: move left one col
	                board[r][c-1]=1;
	            }
	        }
	        else{
	            //if not in last col
	            if(checkGivenCol(7) != 1){
	                //play right: move right one col
	                board[r][c+1]=1;
	            }
	        }
	    }
	    else{
	        if(revert == true){
	            //if not in last row
	            if(checkGivenRow(0) != 1){
	                //play reverse-bottom: move up one row
	                board[r-1][c]=1;
	            }
	        }
	        else{
	            //if not in last row
	            if(checkGivenRow(7) != 1){
	                //play bottom: move down one row
	                board[r+1][c]=1;
	            }
	        }
	    }
	}
	
	public void initBoard(){
	    board[0][0] = 1;
	    for(int i = 0; i < 8; i++){
	        for(int j = 1; j < 8; j++){
	            board[i][j] = 0;
	        }
	    }
	}
	public void printBoard(){
        for(int i = 0; i < 8; i++){
            System.out.print((i+1)+" :");
            for(int j = 0; j < 8; j++){
                System.out.print(board[i][j]+" ");
            }
            System.out.println();
        }
        System.out.println();
    }
}