/**
 * 
 */
package Manager;

import Microcontroller.Arduino;
import Microcontroller.Backlight;
import Microcontroller.DistanceSensor;
import Microcontroller.Microphone;
import Microcontroller.ServoController;

/**
 * @author Christoph
 *
 */
public class Main 
{
	//Global attributes
	static Arduino uno;
	static SensorInformation si;
	static SensorEventHandler seh;
	
	/**
	 * Configures the connected Microcontroller
	 */
	public static void initializeSystem()
	{
		uno = new Arduino(1, "Arduino1");
		//add available components
		uno.getConnectedSensors().add(new Microphone(2, "Microfon1", uno));
		uno.getConnectedSensors().add(new DistanceSensor(3, "Distance1", uno));	
		uno.getConnectedActors().add(new ServoController(4, "Servo1"));
		uno.getConnectedActors().add(new Backlight(5, "Backlight"));
	}
	
	/**
	 * Initializes Event Handling
	 */
	public static void initEventHandling()
	{
		//Create objects
		si = new SensorInformation(uno, 20);
		seh = new SensorEventHandler(uno);
		//register listener
		si.addListener(seh);
		//start thread
		si.run();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		//init
		initializeSystem();
		initEventHandling();
		
		Thread t=new Thread() 
		{
			public void run() 
			{
				System.out.println("Thinking Skins!");
				System.out.println("==============================");
				String out = uno.sendMessage("Hello");
				System.out.println("You: Hello");
				System.out.println("Arduino: " + out);
				
				int i = 0;
				while(i < 60)
				{
					Microphone mic = (Microphone) uno.getConnectedSensors().get(0);
					String out3 = mic.readData();
					System.out.println("Microphone value: ");
					System.out.println(out3);
					
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					i++;
				}
				
				//clean up
				uno.cleanUp();
		        //Message
				System.out.println("End...");
				System.out.println("Good bye");
			}
		};
		t.start();		
	}
}
