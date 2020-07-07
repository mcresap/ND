import java.util.*;
import java.io.*;
import java.lang.*;
import java.util.ArrayList;

public class Race{
	ArrayList<Horse> horses = new ArrayList<Horse>();
	ArrayList<Float> distances = new ArrayList<Float>();
	ArrayList<Integer> finishTime = new ArrayList<Integer>();

	int finish;
	int timer;

	public void enrollHorse(String name, int maxspeed, RaceStrategy strat) throws InterruptedException{
		Horse horsey = new Horse();
		horsey.setName(name);
		horsey.setMaxspeed(maxspeed);
		horsey.setCurrspeed(maxspeed);
		horsey.setStrategy(strat);
		horses.add(horsey);

		if (horses.size() == 5){
			start();
		}
	}

	public void start() throws InterruptedException {
		for (int i=0; i<5; i++){
			distances.add((float) 0);
			finishTime.add(-1);
		}
		timer=0;
		finish=0; //number horses that have finished

		run();
	}

	public void run() throws InterruptedException {
		while (finish<5){
			for (int i=0; i<5;i++){
				if (finishTime.get(i) != -1){
					continue;
				}
				ArrayList<Float> status = horses.get(i).getStrategy().race(distances.get(i),horses.get(i).getMaxspeed());

				distances.set(i, status.get(0));
				horses.get(i).setCurrspeed(status.get(1));

				if (distances.get(i)>10){
					finishTime.set(i,timer);
					finish +=1;
					System.out.println("\n" + horses.get(i).getName() + " has traveled " + distances.get(i) + " miles going " + horses.get(i).getCurrspeed() + " mph at time " + (float) timer + " minute(s).");
					System.out.println(horses.get(i).getName() + " has stopped at " + (float) timer);
				}
			}
			if ((timer-1)%10 == 0 || finish ==5){
				if (finish == 5) {
					System.out.println("\nFINAL:");
				}
				System.out.println("\nUpdate:");
				for (int i=0;i<5;i++){
					if (finishTime.get(i) == -1){
					
						System.out.println(horses.get(i).getName() + " has traveled " + distances.get(i) + " miles going " + horses.get(i).getCurrspeed() + " mph at time " + (float) timer + " minute(s).");
					}
					else{
						System.out.println("\n" + horses.get(i).getName() + " has traveled " + distances.get(i) + " miles going " + horses.get(i).getCurrspeed() + " mph at time " + (float)finishTime.get(i) + " minute(s).");
					}
				}
			}
			timer+=1;
			Thread.sleep(200);

		}
		winner();
	}

	public void winner() {
		float wintime=999999;
		int winhorse=0;
		for (int i=0;i<5;i++){
			if (finishTime.get(i) < wintime){
				wintime=(float)finishTime.get(i);
				winhorse =i;
			}
		}
		System.out.println("\nWinner is " + horses.get(winhorse).getName() + " at time " + wintime + " minute(s).\n");
	}

}
