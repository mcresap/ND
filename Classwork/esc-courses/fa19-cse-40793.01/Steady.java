import java.util.*;

public class Steady implements RaceStrategy{
	@Override
	public ArrayList<Float> race(float distance, int speed)	{
		ArrayList<Float> status = new ArrayList<Float>();
		float currspeed;
		float maxspeed = (float) speed;
		
		currspeed=maxspeed * (float) 0.8; // run whole race at 80% speed
			
		distance = distance + (currspeed/60);
	
		status.add(distance); // update current distance
		status.add(currspeed); //update current speed
		return status;
	}

}
