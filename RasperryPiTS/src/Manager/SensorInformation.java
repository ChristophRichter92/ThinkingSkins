/**
 * 
 */
package Manager;

import java.util.ArrayList;
import java.util.LinkedList;

import Microcontroller.Arduino;
import Microcontroller.Backlight;
import Microcontroller.DistanceSensor;
import Microcontroller.Microphone;
import Microcontroller.Sensor;


/**
 * This Class Stores the last x Sensor values and defines some Events
 * @author Christoph
 *
 */
public class SensorInformation implements Runnable
{
	//attrinutes
	private Arduino uno;
	
	private ArrayList<SensorListener> listeners;
	
	private LinkedList<Long> distanceBuffer;
	private LinkedList<Integer[]> soundLevelBuffer;
	private int maxCapacity;

	/**
	 * Constructor initialises the lists
	 */
	public SensorInformation(int maxCapacity) 
	{
		//init variables
		this.maxCapacity = maxCapacity;
		distanceBuffer = new LinkedList<Long>();
		soundLevelBuffer = new LinkedList<Integer[]>();
		listeners = new ArrayList<SensorListener>();
		
		//init Arduino
		uno = new Arduino(1, "Arduino1");
		//add available components
		uno.getConnectedSensors().add(new Microphone(2, "Microfon1", uno));
		uno.getConnectedSensors().add(new DistanceSensor(3, "Distance1", uno));	
		//uno.getConnectedActors().add(new Servo(4, "Servo1"));
		uno.getConnectedActors().add(new Backlight(5, "Backlight"));
		
	}
	
	/**
	 * Adds a Listener to the observers
	 * @param l the listener you want to add
	 */
	public void addListener(SensorListener l)
	{
		if(!listeners.contains(l))
		{
			listeners.add(l);
		}
	}
	
	/**
	 * Removes the specified listener from obsevrer list
	 * @param l the listener you want to remove
	 */
	public void removeListener(SensorListener l)
	{
		listeners.remove(l);
	}
	
	@Override
	public void run() 
	{
		updateSensorInformation();
		analyzeInformation();
	}
	
	/**
	 * get SensorValues from the Arduino saves them into a queue
	 */
	private void updateSensorInformation()
	{
		for(Sensor s : uno.getConnectedSensors())
		{
			if(s instanceof DistanceSensor)
			{
				distanceBuffer.add(((DistanceSensor) s).getDistance());
				if(distanceBuffer.size() < maxCapacity)
				{
					distanceBuffer.remove();
				}
			}
			else if(s instanceof Microphone)
			{
				soundLevelBuffer.add(((Microphone) s).getSoundLevel());
				if(soundLevelBuffer.size() < maxCapacity)
				{
					soundLevelBuffer.remove();
				}
			}
		}
	}
	
	/**
	 * Analyzes Sensor Information and fires events
	 */
	private void analyzeInformation()
	{
		if(distanceLow())
		{
			for(SensorListener l : listeners)
			{
				l.distanceIsLow();
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
		average = average/distanceBuffer.size();
		
		//compare to threshold
		if(average < threshold)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
