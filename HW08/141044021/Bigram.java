public interface Bigram<T> {
	public void readFile( String filename) throws Exception ;
    public int numGrams();
    public int numOfGrams(T p1,T p2) ;
}
