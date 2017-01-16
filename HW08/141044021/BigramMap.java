import java.util.HashMap;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
 

public class BigramMap<T> implements Bigram<T> {

	public BigramMap(int dataType) {
		// TODO Auto-generated constructor stub
		dataTypeObj=dataType;
	}
	
	@Override
	public int numGrams() {
		// TODO Auto-generated method stub
		return bigramHashMap.size()-1;
	}
	@SuppressWarnings("unchecked")
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		String printOcc="";
		int numOfsize=0;
		
	    T[][]  tempGrams=(T[][]) new Object[bigramHashMap.size()*2+10][2];
	    int tempGramsUsed=0;
	    
	    int[] tempGramsOccur= new int[bigramHashMap.size()*2+10];
	    int tempGramsOccurUsed=0; 
	    
	    for (int i = 0; i < bigramHashMap.size() -1 ; i++) {
	        tempGrams[tempGramsUsed][0]=(T) bigramHashMap.get(i);
	        tempGrams[tempGramsUsed][1]=(T) bigramHashMap.get(i+1);
	        ++tempGramsUsed;
	                            //tempGrams.size()
	        for (int j = 0; j < tempGramsOccurUsed+1 ; j++) {
	        	//if(tempGrams[j][0]==bigramHashMap.get(i) && tempGrams[j][1]==bigramHashMap.get(i+1))
	            if(tempGrams[j][0].equals(bigramHashMap.get(i)) && tempGrams[j][1].equals(bigramHashMap.get(i+1)))
	            {++numOfsize;}
	        }
	        
	        int a=numOfGrams((T)bigramHashMap.get(i),(T)bigramHashMap.get(i+1));
	        tempGramsOccur[tempGramsOccurUsed]=a;
	        ++tempGramsOccurUsed;
	        
	        if (numOfsize>1) {
	            --tempGramsUsed;
	            --tempGramsOccurUsed;
	        }
	        
	        numOfsize=0;

	    }
	    
	    T temp;
	    int intTemp;
	                    //tempGramsOccur.size()
	    for(int i=0; i<tempGramsOccurUsed; i++)
	    {               //tempGramsOccur.size()-1
	        for(int j=tempGramsOccurUsed-1; j>i; j--)
	        {
	            if(tempGramsOccur[j]>tempGramsOccur[j-1])
	            {
	                intTemp=tempGramsOccur[j-1];
	                tempGramsOccur[j-1]=tempGramsOccur[j];
	                tempGramsOccur[j]=intTemp;
	                
	                temp=tempGrams[j-1][0];
	                tempGrams[j-1][0]=tempGrams[j][0];
	                tempGrams[j][0]=temp;
	                
	                temp=tempGrams[j-1][1];
	                tempGrams[j-1][1]=tempGrams[j][1];
	                tempGrams[j][1]=temp;
	                
	            }
	        }
	    }
	    for (int i = 0; i < tempGramsUsed; i++) {
	        printOcc+="{ ";
	        printOcc+=tempGrams[i][0];
	        printOcc+=" - ";
	        printOcc+=tempGrams[i][1];
	        printOcc+=" } - occurance >> ";
	        printOcc+=tempGramsOccur[i];
	        printOcc+='\n';
	    }
	    
		return printOcc;
	}
	@SuppressWarnings("unchecked")
	@Override
	public int numOfGrams(T p1, T p2) {
		// TODO Auto-generated method stub
	    int numOfsize=0;
	    for (int i = 0; i < bigramHashMap.size()-1; i++) {
	    	//if(bigramHashMap.get(i)==p1 && bigramHashMap.get(i+1)== p2)
	        if(bigramHashMap.get(i).equals(p1) && bigramHashMap.get(i+1).equals(p2) )
	            ++numOfsize;
	    }
	    return numOfsize;
	}
	@SuppressWarnings("unchecked")
	@Override
	public void readFile(String filename) throws Exception  {
		// TODO Auto-generated method stub
		Scanner inputFile = null;
		try{
			inputFile = new Scanner(new FileInputStream(filename));
		}
		catch (FileNotFoundException e){
			System.out.println("Dosya acılamadı !!!");
		}
		
	    int i=0;	

		if (dataTypeObj==1) {
		 	int newObject=0;
		 	while(inputFile.hasNext()){
		 		if(inputFile.hasNextInt()){
			 		newObject=inputFile.nextInt();
			 		bigramHashMap.put(i, newObject);
			 		++i;
		 		}else{
		 			throw new Exception("!! Bad data !!");
		 		}
	    	}
		}
		 else if (dataTypeObj==2) {
		 	String newObject=null;
		 	while(inputFile.hasNext()){
		 		if(inputFile.hasNext()){
			 		newObject=inputFile.next();
			 		bigramHashMap.put(i, newObject);
			 		++i;
		 		}
		 	}
		}
		 else if (dataTypeObj==3) {
		 	Double newObject=0.0;
		 	while(inputFile.hasNext()){
					try{	
			    		if( inputFile.hasNext() ){
			    			newObject=Double.parseDouble(inputFile.next());
				    		isDouble a= new isDouble();
			    			if (a.doubleCheck(newObject)) {
			    				bigramHashMap.put(i, newObject);
					    		++i;	
							}
			    			else{
			    				throw new Exception("!! Bad data !!");
			    			}
			    		}
					}catch (NumberFormatException e){
						throw new Exception("!! Bad data !!");
					}

		 	}
					
		}
		    
		if(i<1){
			throw new Exception("!! Empty File !!");
		}	
	}

	private  int dataTypeObj;
	@SuppressWarnings("unchecked")
	private HashMap<Integer, Object> bigramHashMap = new HashMap();
}
