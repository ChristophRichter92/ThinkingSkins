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
	SensorInformation information;
	
	/**
	 * Constructor
	 * @param microController the connected microcontroller
	 * @param informations the information to handle
	 */
	public SensorEventHandler(Microcontroller microController, SensorInformation information) 
	{
		this.microController = microController;
		this.information = information;
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

	@Override
	public void distanceIsLow() 
	{
		//Backlight green
		getBacklight().changeColor(0, 255, 0);
		//open position
		getServoController().open();
		System.out.println("distance Low");
	}
	
	@Override
	public void distanceIsNormal() 
	{
		//Backlight white
		getBacklight().changeColor(255, 255, 255);
		System.out.println("distance Normal");
	}

	@Override
	public void soundIsLow() 
	{
		//Backlight blue
		getBacklight().changeColor(0, 0, 255);
		//open position
		getServoController().open();
		System.out.println("Sound Low");
	}

	@Override
	public void soundIsHigh() 
	{
		//Backlight red
		getBacklight().changeColor(255, 0, 0);
		//close position
		getServoController().close();
		System.out.println("Sound High");
	}

	@Override
	public void soundIsNormal() 
	{
		//get sound level
		Integer[] level = information.getCurrentSoundLevel();
		int lower = 0;
		int upper = 0;
		for(int i = 0; i < 4; i++)
		{
			lower += level[i];
			upper += level[i+3];
		}
		//calculate average soundlevel and scale
		lower = lower/4/4;
		upper = upper/4/4;
		//set Backlight
		getBacklight().changeColor(lower, 0, upper);
		//set position
		getServoController().move(lower, upper);
		System.out.println("Sound Normal");
	}
}
