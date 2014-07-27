/**
 * 
 */
package Manager;

import java.util.ArrayList;

/**
 * This class should provide Information which are used to trigger 
 * specified events
 * @author Christoph
 *
 */
public abstract class Information implements Runnable
{
	//attributes
	protected ArrayList<SensorListener> listeners;

	/**
	 * 
	 */
	public Information() 
	{
		listeners = new ArrayList<SensorListener>();
	}
	
	//abstract methods
	public abstract void updateInformation();
	public abstract void analyzeInformation();
	
	//methods
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
}
