/**
 * 
 */
package Microcontroller;

/**
 * Distance Sensor connected to the Microcontroller
 * @author Christoph
 *
 */
public class DistanceSensor extends Sensor 
{
	//attribures
	private long distance = 0;

	/**
	 * @param id
	 * @param name
	 * @param mc
	 */
	public DistanceSensor(int id, String name, Microcontroller mc) {
		super(id, name, mc);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see Microcontroller.Sensor#readData()
	 */
	/**
	 * Get distance data from sensor
	 * @return Returns the distance to a certain object in front of the sensor
	 */
	@Override
	public String readData() 
	{
		String result = this.getMicrocontroller().sendMessage("getDistance()");
		distance = Long.parseLong(result);
		return result;
	}

	/**
	 * @return the distance read from the sensor
	 */
	public long getDistance() {
		System.out.println(readData());
		return distance;
	}

}
