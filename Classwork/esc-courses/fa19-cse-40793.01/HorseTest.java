import static org.junit.Assert.assertEquals;
import org.junit.Test;

public class HorseTest {
	@Test
	public void testMaxHorses(){
		Race temp = new Race();
	/*	Horse horses = new Horse();
		libby.setName("Libby");
		libby.setMaxspeed(21);
		libby.setCurrspeed(21);
		libby.setStrategy(Slow());
		horses.add(libby);

		Fred.setName("Fred");
		Fred.setMaxspeed(25);
		Fred.setCurrspeed(25);
		Fred.setStrategy(Steady());
		horses.add(Fred);
		
		Lisa.setName("Lisa");
		Lisa.setMaxspeed(20);
		Lisa.setCurrspeed(20);
		Lisa.setStrategy(Sprint());
		horses.add(Lisa);

		John.setName("John");
		John.setMaxspeed(22);
		John.setCurrspeed(22);
		John.setStrategy(Slow());
		horses.add(John);
 
		Will.setName("Will");
		Will.setMaxspeed(23);
		Will.setCurrspeed(23);
		Will.setStrategy(Sprint());
		horses.add(Will);

		Clare.setName("Clare");
		Clare.setMaxspeed(24);
		Clare.setCurrspeed(24);
		Clare.setStrategy(Stead());
		horses.add(Clare);*/
		try {
			temp.enrollHorse("Libby", 21, new Steady());
			temp.enrollHorse("Fred",25,new Steady());
			temp.enrollHorse("John",22,new Slow());
			temp.enrollHorse("Lisa",20,new Sprint());
			temp.enrollHorse("Will",23,new Sprint());
			temp.enrollHorse("Clare",24,new Steady());
		} catch(InterruptedException e) {
    		Thread.currentThread().interrupt();
		}		
	/*	temp.enrollHorse("Libby",21,new Slow());
		temp.enrollHorse("Fred",25,new Steady());
		temp.enrollHorse("John",22,new Slow());
		temp.enrollHorse("Lisa",20,new Sprint());
		temp.enrollHorse("Will",23,new Sprint());
		temp.enrollHorse("Clare",24,new Steady());*/
		if (temp.horses.size() > 5){
			System.out.println("\nERROR: Cannot have more than 5 horses racing at once.\n");
		}
	}

	@Test
	public void testAllFinished(){
		Race temp = new Race();
		try {
			temp.enrollHorse("Libby", 21, new Steady());
			temp.enrollHorse("Fred",5,new Steady());
			temp.enrollHorse("John",22,new Slow());
			temp.enrollHorse("Lisa",20,new Sprint());
			temp.enrollHorse("Will",23,new Sprint());
		} catch(InterruptedException e) {
    		Thread.currentThread().interrupt();
		}	
		/*if (temp.finish != 5){
			System.out.println("\nERROR: Not all horses finished.\n");
		}*/
		if (temp.timer > 50){
			System.out.println("\nERROR: One or more horses are extremely slow and are probably not cut out for racing.\n");
		}
	}

	@Test
	public void testEnoughHorses(){
		Race temp = new Race();
		try {
			temp.enrollHorse("Libby", 21, new Steady());
			temp.enrollHorse("John",22,new Slow());
		} catch(InterruptedException e) {
    		Thread.currentThread().interrupt();
		}	
		if (temp.horses.size() < 5){
			System.out.println("\nERROR: You might want more horses racing to make it more interesting.\n");
		}
	}

/*	
	@Test
	public void testAllFinished(){
		Race temp = new Race();
		temp.enrollHorse("Libby",21,new Slow());
		temp.enrollHorse("Fred",25,new Steady());
		temp.enrollHorse("John",22,new Slow());
		temp.enrollHorse("Lisa",20,new Sprint());
		temp.enrollHorse("Will",23,new Sprint());
		if (temp.finish != 5){
			System.out.println("\nNot all horses finished.\n");
		}
	}

	@Test
	public void testWin(){
		Race temp = new Race();
		temp.enrollHorse("Libby",100,new Slow());
		temp.enrollHorse("Fred",25,new Steady());
		temp.enrollHorse("John",22,new Slow());
		temp.enrollHorse("Lisa",20,new Sprint());
		temp.enrollHorse("Will",23,new Sprint());
		assertEquals(temp, "Winner is Libby");
		//assertEquals(temp.winner.get(5), "Libby");
	
	}*/

}
