import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Pool {
	
	static private final int SCALE = 5;
	static private final int FITNESS_SCALE = 50;
	static private final Random rand = new Random();
	
	public Pool(int n) {
		population = n;
		generation = 1;
		if (eval == null) {
			eval = new Chromosome();
		}
		chromosomeList = new ArrayList<>();
		
		while (chromosomeList.size() < population) {
			Chromosome c = new Chromosome();
			add(c);
		}
	}
	
	public Pool(int n, Chromosome c) {
		this(n);
		eval = c;
	}
	
	public void evolve() {
		do {
			int n1 = rand.nextInt(chromosomeList.size());
			int n2 = rand.nextInt(chromosomeList.size());
			
			if (n1 == n2) {
				continue;
			}
			
			Chromosome c1 = chromosomeList.get(n1);
			Chromosome c2 = chromosomeList.get(n2);
			Chromosome c3 = c1.crossOver(c2);
			c3.mutate();
			add(c3);
			//System.out.println("Current size: " + chromosomeList.size());
		} while (chromosomeList.size() < population*SCALE);
		
		generation++;
	}
	
	public void evaluate() {
		int best = -1;
		for (Chromosome c : chromosomeList) {
			c.setHeuristicScore(eval);
			if (c.getHeuristicScore() > best) {
				best = c.getHeuristicScore();
			}
		}
		
		List<Chromosome> newList = new ArrayList<>();
		
		while (newList.size() < FITNESS_SCALE && best >= 0) {
			for (Chromosome c : chromosomeList) {
				if (c.getHeuristicScore() == best) {
					boolean flag = false;
					for (Chromosome ch : newList) {
						if (c.isDuplicate(ch)) {
							flag = true;
							break;
						}
					}
					if (!flag) {
						newList.add(c);
					}
					if (newList.size() > FITNESS_SCALE) {
						break;
					}
				}
			}
			best--;
		}
		chromosomeList = newList;
		
	}
	
	public void setEvaluate(Chromosome c) {
		eval = c;
	}
	
	public int getGeneration() {
		return generation;
	}
	
	public int getPopulation() {
		return chromosomeList.size();
	}
	
	public void printEval() {
		eval.printSequence();
	}
	
	public void printBestFit() {
		for (Chromosome c : chromosomeList) {
			c.printSequence();
		}
	}
	
	public void printFirst() {
		chromosomeList.get(0).printSequence();
	}
	
	private boolean add(Chromosome c) {
		boolean flag = false;
		for (Chromosome ch : chromosomeList) {
			if (c.isDuplicate(ch)) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			chromosomeList.add(c);
		}
		return flag;
	}
	
	private List<Chromosome> chromosomeList;
	private Chromosome eval;
	private int population;
	private int generation;
	
}
