import java.util.*;

public class Slow implements RaceStrategy{
	@Override
	public ArrayList<Float> race(float distance, int speed)	{
		ArrayList<Float> status = new ArrayList<Float>();
		float currspeed;
		float maxspeed = (float) speed;
		
		if (distance <= 6){
			currspeed = maxspeed * (float) 0.75; // do 75% for 6 miles 
		}
		else if (distance <= 9){
			currspeed = maxspeed * (float) 0.9; // do 90% for 3 miles
		}
		else{
			currspeed=maxspeed; // do 100% for 1 mile
		}

		distance = distance + (currspeed/60);
	
		status.add(distance);
		status.add(currspeed);
		return status;
	}

}
