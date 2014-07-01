/**
 * Represents a Microcontroller and provides several functions
 */
package Microcontroller;

import java.util.LinkedList;

/**
 * @author Christoph
 *
 */
public abstract class Microcontroller extends Component {

	//attributes
	protected final int BAUDRATE = 9600;
	private LinkedList<Sensor> connectedSensors;
	private LinkedList<Actor> connectedActors;
	
	/**
	 * @param id unique ID
	 * @param name Name of the microcontroller
	 */
	public Microcontroller(int id, String name)
	{
		super(id, name);
		//init lists
		connectedSensors = new LinkedList<Sensor>();
		connectedActors = new LinkedList<Actor>();
	}
	
	//abstract methods
	/**
	 * sends a message to the microcontroller and reveives its message
	 * @param message you want to send 
	 * @return message yoo get from the microcontroller
	 */
	abstract public String sendMessage(String message);
	
	//methods
	/**
	 * adds a sensor to the connected sensors of the microcontroller
	 * @param s the sensor you want to add
	 */
	void addSensor(Sensor s)
	{
		if(!connectedSensors.contains(s))
		{
			connectedSensors.add(s);
		}
	}
	
	/**
	 * removes a sensor to the connected sensors of the microcontroller
	 * @param s the sensor you want to remove
	 */
	void removeSensor(Sensor s)
	{
		if(connectedSensors.contains(s))
		{
			connectedSensors.remove(s);
		}
	}
	
	/**
	 * adds a actor to the connected sensors of the microcontroller
	 * @param a the actor you want to add
	 */
	void addActor(Actor a)
	{
		if(!connectedActors.contains(a))
		{
			connectedActors.add(a);
		}
	}
	
	/**
	 * removes a actor to the connected sensors of the microcontroller
	 * @param a the actor you want to remove
	 */
	void removeActor(Actor a)
	{
		if(connectedActors.contains(a))
		{
			connectedActors.remove(a);
		}
	}
	
	//Getter methods
	/**
	 * @return the connectedSensors
	 */
	public LinkedList<Sensor> getConnectedSensors() {
		return connectedSensors;
	}

	/**
	 * @return the connectedActors
	 */
	public LinkedList<Actor> getConnectedActors() {
		return connectedActors;
	}

	/**
	 * @return the bAUDRATE
	 */
	public int getBAUDRATE() {
		return BAUDRATE;
	}	
}
