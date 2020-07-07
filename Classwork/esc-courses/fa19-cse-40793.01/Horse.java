import java.io.*;
import java.util.*;


public class Horse{
	private String name;
	private int maxspeed;
	private float currspeed;
	private RaceStrategy strat;

	public Horse(){ //constructor
		this.name="Libby";
		this.maxspeed=24;
		this.currspeed=this.maxspeed;
		this.strat=new Steady();
	}

	public void setName(String n){ //setter
		this.name=n;
	}
	public void setMaxspeed(int maxs){ //setter
		this.maxspeed = maxs;
	}
	public void setCurrspeed(float currs){ //setter
		this.currspeed=currs;
	}
	public void setStrategy(RaceStrategy strategy){ //setter
		this.strat = strategy;
	}

	public String getName(){ //getter
		return this.name;
	}
	public Integer getMaxspeed(){ //getter
		return this.maxspeed;
	}	
	public Float getCurrspeed(){ //getter
		return this.currspeed;
	}
	public RaceStrategy getStrategy(){ //getter
		return this.strat;
	}
	
}
