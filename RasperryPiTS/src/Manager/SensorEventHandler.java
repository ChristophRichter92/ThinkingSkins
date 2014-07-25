/**
 * 
 */
package Manager;

import Microcontroller.Actor;
import Microcontroller.Backlight;
import Microcontroller.Microcontroller;
import Microcontroller.ServoController;

/**
 * Dispatches a certain action according to an fired event
 * @author Christoph
 *
 */
public class SensorEventHandler implements SensorListener 
{
	//Attributes
	Microcontroller microController;
	
	/**
	 * Constructor
	 */
	public SensorEventHandler(Microcontroller microController) 
	{
		this.microController = microController;
	}

	/* (non-Javadoc)
	 * @see Manager.SensorListener#distanceIsLow()
	 */
	@Override
	public void distanceIsLow() 
	{
		//Backlight green
		getBacklight().changeColor(0, 255, 0);
		//open position
		getServoController().open();
	}
	
	/**
	 * Gets the connected Backlight
	 * @return the Backlight
	 */
	private Backlight getBacklight()
	{
		for(Actor a : microController.getConnectedActors())
		{
			if(a instanceof Backlight)
			{
				return (Backlight) a;
			}
		}
		//no Backlight found
		System.err.println("No Backlight connected");
		return null;
	}
	
	/**
	 * Gets to connected servoController
	 * @return the ServoController
	 */
	private ServoController getServoController()
	{
		for(Actor a : microController.getConnectedActors())
		{
			if(a instanceof ServoController)
			{
				return (ServoController) a;
			}
		}
		//no ServoController found
		System.err.println("No ServoController connected");
		return null;
	}
}
