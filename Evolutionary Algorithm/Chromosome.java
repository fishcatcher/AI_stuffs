import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

enum Gene {X, Y, Z};

public class Chromosome {
	
	static public final int LENGTH = 100;
	
	public Chromosome() {
		gene = new Gene[LENGTH];
		
		for (int i=0; i<gene.length; i++) {
			gene[i] = generateGene();
		}
	}
	
	public Chromosome(Gene[] g) {
		Gene gg[] = new Gene[g.length];
		System.arraycopy(g, 0, gg, 0, g.length);
		gene = gg;
	}
	
	public void mutate() {			
		int r = ThreadLocalRandom.current().nextInt(gene.length/2, gene.length);
		List<Integer> indexList = new ArrayList<>();
		while (indexList.size() < r) {
			int v = rand.nextInt(gene.length);
			if (!indexList.contains(v)) {
				indexList.add(v);
			}
		}
		
		for (int i : indexList) {
			Gene g = generateGene();
			while(gene[i] == g) {
				g = generateGene();
			}
			gene[i] = g;
		}
	}
	
	public Chromosome crossOver(Chromosome c) {
		
		if (this.equals(c)) {
			return c;
		}
		
		Gene g[] = new Gene[LENGTH];
		int index = rand.nextInt(gene.length);
		while (index == 0 || index == gene.length-1) {
			index = rand.nextInt(gene.length);
		}
		System.arraycopy(this.getSequence(), 0, g, 0, index);
		System.arraycopy(c.getSequence(), index, g, index, gene.length - index);
		
		return new Chromosome(g);
	}
	
	public boolean isDuplicate(Chromosome c) {
		Gene g[] = c.getSequence();
		for (int i=0; i<gene.length; i++) {
			if (gene[i] != g[i]) {
				return false;
			}
		}
		return true;
	}
	
	
	public Gene[] getSequence() {
		return gene;
	}
	
	public void setHeuristicScore(Chromosome c) {
		score = 0;
		Gene g[] = c.getSequence();
		if (gene.length != g.length || this.equals(c)) {
			
			return;
		}
		
		for (int i=0; i<g.length; i++) {
			if (gene[i] == g[i]) {
				score++;
			}
		}

	}
	public int getHeuristicScore() {
		return score;
	}
	
	public void printSequence() {
		System.out.print("[");
		for (Gene g : gene) {
			switch (g) {
			case X:
				System.out.print("X ");
				break;
			case Y:
				System.out.print("Y ");
				break;
			case Z:
				System.out.print("Z ");
				break;
			}
		}
		System.out.println("] : " + score);
	}
	
	private Gene generateGene() {
		Gene gene = Gene.X;
		int n = rand.nextInt(3);	//0 - 1
		switch (n) {
		case 0:
			gene = Gene.X;
			break;
		case 1:
			gene = Gene.Y;
			break;
		case 2:
			gene = Gene.Z;
			break;
		}
		return gene;
	}
	
	private Gene gene[];
	private Random rand = new Random();
	private int score = 0;
}
