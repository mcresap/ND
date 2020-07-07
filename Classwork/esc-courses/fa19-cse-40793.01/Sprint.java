import java.util.*;
import java.util.ArrayList;

public class Sprint implements RaceStrategy{
	@Override
	public ArrayList<Float> race(float distance, int speed)	{
		ArrayList<Float> status = new ArrayList<Float>();
		float currspeed;
		float maxspeed = (float) speed;
		
		if (distance >=2){
			currspeed = maxspeed * (float) 0.75; // 75% for everything after first 2 miles
		}
		else{
			currspeed = maxspeed; // max speed for first 2 miles
		}
	
		distance = distance + (currspeed/60);
	
		status.add(distance); // update current distance
		status.add(currspeed); //update current speed
		return status;
	}

}
