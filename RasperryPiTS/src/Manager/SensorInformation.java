/**
 * 
 */
package Manager;

import java.util.LinkedList;

import Microcontroller.Arduino;
import Microcontroller.DistanceSensor;
import Microcontroller.Microcontroller;
import Microcontroller.Microphone;
import Microcontroller.Sensor;


/**
 * This Class Stores the last x Sensor values and defines some Events
 * @author Christoph
 *
 */
public class SensorInformation extends Information
{
	//attributes
	private Arduino uno;
		
	private LinkedList<Long> distanceBuffer;
	private LinkedList<Integer[]> soundLevelBuffer;
	private int maxCapacity;
	
	//globals var
	boolean distanceLow;
	boolean soundLow;
	boolean soundHigh;

	/**
	 * Constructor initialises the lists
	 */
	public SensorInformation(Microcontroller micro, int maxCapacity) 
	{
		//init variables
		this.maxCapacity = maxCapacity;
		distanceBuffer = new LinkedList<Long>();
		soundLevelBuffer = new LinkedList<Integer[]>();
		
		//init globals
		distanceLow = false;
		
		//init Arduino
		if(micro instanceof Arduino)
		{
			uno = (Arduino) micro;
		}
		else
		{
			//Error
			System.err.println("Please connect an Arduino");
		}
	}
	
	/**
	 * @return a copy of the distanceBuffer
	 */
	public LinkedList<Long> getDistanceBuffer() {
		LinkedList<Long> res = new LinkedList<Long>(distanceBuffer);
		return res;
	}

	/**
	 * @return a copy of the soundLevelBuffer
	 */
	public LinkedList<Integer[]> getSoundLevelBuffer() {
		LinkedList<Integer[]> res = new LinkedList<>(soundLevelBuffer);
		return res;
	}
	
	/**
	 * 
	 * @return the current sound level
	 */
	public Integer[] getCurrentSoundLevel()
	{
		return soundLevelBuffer.getLast();
	}
	
	@Override
	public void run() 
	{
		while(true)
		{
			updateInformation();
			analyzeInformation();
			//Wait for 10ms
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * get SensorValues from the Arduino saves them into a queue
	 */
	@Override
	public void updateInformation()
	{
		for(Sensor s : uno.getConnectedSensors())
		{
			if(s instanceof DistanceSensor)
			{
				distanceBuffer.add(((DistanceSensor) s).getDistance());
				if(distanceBuffer.size() > maxCapacity)
				{
					distanceBuffer.remove();
				}
			}
			else if(s instanceof Microphone)
			{
				soundLevelBuffer.add(((Microphone) s).getSoundLevel());
				if(soundLevelBuffer.size() > maxCapacity)
				{
					soundLevelBuffer.remove();
				}
			}
		}
	}
	
	/**
	 * Analyzes Sensor Information and fires events
	 */
	@Override
	public void analyzeInformation()
	{
		//distance
		if(distanceLow())
		{
			for(SensorListener l : listeners)
			{
				l.distanceIsLow();
			}
		}
		else
		{
			for(SensorListener l : listeners)
			{
				l.distanceIsNormal();
			}
		}
		//sound
		if(soundLow())
		{
			for(SensorListener l : listeners)
			{
				l.soundIsLow();
			}
		}
		else if(soundHigh())
		{
			for(SensorListener l : listeners)
			{
				l.soundIsHigh();
			}
		}
		else
		{
			for(SensorListener l : listeners)
			{
				l.soundIsNormal();
			}
		}
	}
	
	//Events
	//---------------------------------------------------------------------
	/**
	 * The average distance form any Object to the Sensor falls under a specified level
	 * @return true if the distance ist lower than the threshold
	 */
	private boolean distanceLow()
	{
		//get average
		final long threshold = 20;
		long average = 0;
		for(Long v : distanceBuffer)
		{
			average += v;
		}
		average = average/(distanceBuffer.size()+1);
		
		//compare to threshold //TODO only once
		if(average < threshold)
		{
			distanceLow = true;
			return true;
		}
		else
		{
			distanceLow = false;
			return false;
		}
	}
	
	private boolean soundLow()
	{
		final int threshold = 200;
		int average = 0;
		for(Integer[] level : soundLevelBuffer)
		{
			int max = 0;
			for(Integer i : level)
			{
				if(max < i)
				{
					i = max;
				}
			}
			average += max;
		}
		average = average/soundLevelBuffer.size();
		//compare to threshold //TODO only once
		if(average < threshold)
		{
			soundLow = true;
			return true;
		}
		else
		{
			soundLow = false;
			return false;
		}
	}
	
	/**
	 * 
	 * @return True if the sound level exeeds a threshold
	 */
	private boolean soundHigh()
	{
		final int threshold = 900;
		int average = 0;
		for(Integer[] level : soundLevelBuffer)
		{
			int max = 0;
			for(Integer i : level)
			{
				if(max < i)
				{
					i = max;
				}
			}
			average += max;
		}
		average = average+1/soundLevelBuffer.size();
		//compare to threshold //TODO only once
		if(average > threshold)
		{
			soundHigh = true;
			return true;
		}
		else
		{
			soundHigh = false;
			return false;
		}
	}
}
