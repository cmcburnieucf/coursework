/* Carla J McBurnie
   Dr. Steinberg
   COP3503 Fall 2024
   Programming Assignment 5
*/

import java.util.*;
import java.io.*;

public class Railroad
{
    //***RAILROAD ATTRIBUTES***
    public Edge[] railroadList;
    private ArrayList<String> cities;
    private ArrayList<String> parentCities;
    private ArrayList<Integer> cityRanks;
    
    //***RAILROAD CONSTRUCTOR***
    public Railroad(int numTracks, String filename)
    {
        BufferedReader reader = null;
        ArrayList<Edge> railroadListTemp = new ArrayList<>();
        
        //initialize class's attributes
        cities = new ArrayList<>();
        parentCities = new ArrayList<>();
        cityRanks = new ArrayList<>();
        
        //read the file and extract each line
        try
        {
            //initialize the reader and temporary array
            reader = new BufferedReader(new FileReader(filename));
            String[] lineInfo = null;
            String line = null;
            
            //for each line read:
            for(int i = 0; i < numTracks; i++)
            {
                //save the line into a temporary array
                line = reader.readLine();
                lineInfo = line.split(" ");
                
                railroadListTemp.add(new Edge(lineInfo[0], lineInfo[1], Integer.parseInt(lineInfo[2])));
                
                int sourceCityIndex = cities.indexOf(lineInfo[0]);
                
                //if not already saved, add to the list of cities (aka vertices)
                if(sourceCityIndex == -1)
                {
                    cities.add(lineInfo[0]);
                    sourceCityIndex = cities.indexOf(lineInfo[0]);
                    parentCities.add(sourceCityIndex, lineInfo[0]);
                    cityRanks.add(sourceCityIndex, 0);
                }
                
                int destCityIndex = cities.indexOf(lineInfo[1]);
                
                //do the the same for the destination city
                if(destCityIndex == -1)
                {
                    cities.add(lineInfo[1]);
                    destCityIndex = cities.indexOf(lineInfo[1]);
                    parentCities.add(destCityIndex, lineInfo[1]);
                    cityRanks.add(destCityIndex, 0);
                }
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        //when all the data from the file is read
        //convert temporary ArrayList to an array and save it in the attribute
        railroadList = railroadListTemp.toArray(new Edge[0]);
        
        //sort the edges based on cost
        Arrays.sort(railroadList);
    }
    
    //***RAILROAD BUILD-RAILROAD METHOD***
    public String buildRailroad()
    {
        ArrayList<Edge> usedRailroads = new ArrayList<>();
        
        //Building Railroad with Kruskal's Algorithm and Disjoint Set's Union by Rank
        for(int i = 0; i < railroadList.length; i++)
        {
            //identify u and v, the names of source city and dest city, respectively
            String u = railroadList[i].getSourceName();
            String v = railroadList[i].getDestName();
            int uIndex = cities.indexOf(u);
            int vIndex = cities.indexOf(v);
            
            //find the parents of u and v
            int uParentIndex = findParentIndex(uIndex);
            int vParentIndex = findParentIndex(vIndex);
            String uParent = parentCities.get(uParentIndex);
            String vParent = parentCities.get(vParentIndex);
            
            //make sure there is no loop by comparing predecessor
            if(uParent.compareTo(vParent) != 0)
            {
                //if u's parent has a higher rank than v's parent
                if(cityRanks.get(uParentIndex) > cityRanks.get(vParentIndex))
                {
                    //append v's set to u's set
                    parentCities.set(vParentIndex, uParent);
                }
                //if v has a higher rank than u
                else if(cityRanks.get(uParentIndex) < cityRanks.get(vParentIndex))
                {
                    //append u's set to v's set
                    parentCities.set(uParentIndex, vParent);
                }
                //if the same rank
                else
                {
                    //append v's set to u's set anyway
                    parentCities.set(vParentIndex, uParent);
                    //update rank of u's set
                    cityRanks.set(uParentIndex, cityRanks.get(uParentIndex)+1);
                }
                usedRailroads.add(railroadList[i]); //add edge to solution system
            }
        }
        
        //build the return string
        StringBuilder resultString = new StringBuilder(usedRailroads.size());
        int totalCost = 0;
        
        for(int i = 0; i < usedRailroads.size(); i++)
        {
            resultString.append(usedRailroads.get(i).toString());
            totalCost += usedRailroads.get(i).getCost();
        }
        resultString.append("The cost of the railroad is $"+totalCost+".\n");
        
        return resultString.toString();
    }
    
    
    public int findParentIndex(int index)
    {
        if(cities.get(index) == parentCities.get(index))
            return index;
        
        int parentIndex = cities.indexOf(parentCities.get(index));
        
        return findParentIndex(parentIndex);
    }
    
    //***RAILROAD INNER CLASS: EDGE***
    //Inner Class for storing the vertices and edge costs
    public class Edge  implements Comparable<Edge>
    {
        private String sourceName;//name of source vertex
        private String destName; //name of destination vertex
        private int cost; 
        
        //edge constructor
        public Edge(String sourceName, String destName, int cost)
        {
            setSourceName(sourceName);
            setDestName(destName);
            setCost(cost);
        }
        
        public void setSourceName(String sourceName)
        {
            this.sourceName = sourceName;
        }
        
        public void setDestName(String destName)
        {
            this.destName = destName;
        }
        
        public void setCost(int cost)
        {
            this.cost = cost;
        }
        
        public String getSourceName()
        {
            return sourceName;
        } 
        
        public String getDestName()
        {
            return destName;
        }
        
        public int getCost()
        {
            return cost;
        }
        
        //Used for printing out the edge in the final solution
        public String toString()
        {
            if(getSourceName().compareTo(getDestName()) > 0)
                return "" + getDestName() + "---" + getSourceName() + "\t$" + getCost() + "\n";
                
            return "" + getSourceName() + "---" + getDestName() + "\t$" + getCost() + "\n";
        }
        
        //Used for sorting the array containing all edges
        public int compareTo(Edge comparedEdge)
        {
            //if edge 1 has a lower cost than edge 2
            if(getCost() < comparedEdge.getCost())
                return -1;
            //if edge 1 has a higher cost than edge 2
            else if(getCost() > comparedEdge.getCost())
                return 1;
            
            //if edge 1 has the same cost as edge 2
            return 0;
        }
    }
}










































