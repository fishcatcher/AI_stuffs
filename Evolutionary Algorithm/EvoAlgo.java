
public class EvoAlgo {

	public static void main(String[] args) {
		
		System.out.println("START");
		Chromosome eval = new Chromosome();
		Pool pool = new Pool(50, eval);

		int fitness_scale = 5;
		while (pool.getGeneration() < fitness_scale) {
			pool.evolve();
			pool.evaluate();
		}
		
		pool.printBestFit();
		System.out.println("Population is: " + pool.getPopulation());
		
		
		System.out.println("Evaluation Chromosome:");
		pool.printEval();
		System.out.println("Best Fit Chromosome:");
		pool.printFirst();
		System.out.println("DONE");
		
	}
}
