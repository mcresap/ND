import java.io.*;

public class Main{
	public static void main(String[] args) throws InterruptedException{
		Race race = new Race();

		race.enrollHorse("Sam",22,new Sprint());
		race.enrollHorse("Molly",24,new Slow());
		race.enrollHorse("Joe",25,new Sprint());
		race.enrollHorse("Blizzard",25,new Slow());
		race.enrollHorse("Flicker",25,new Steady());
	}

}
