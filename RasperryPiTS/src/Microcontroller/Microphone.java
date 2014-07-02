/**
 * 
 */
package Microcontroller;

/**
 * A microphone that recognizes sound levels
 * @author Christoph
 *
 */
public class Microphone extends Sensor 
{
	int[] values;
	/**
	 * @param id unique ID
	 * @param name of the Microphone
	 * @param mc Connected Mikrocontroller
	 */
	public Microphone(int id, String name, Microcontroller mc) {
		super(id, name, mc);
		values = new int[7];
	}

	/* (non-Javadoc)
	 * @see Microcontroller.Sensor#readData()
	 */
	@Override
	public String readData() 
	{
		String rawData;
		//send Message
		rawData = this.getMicrocontroller().sendMessage("getSound()");
		//save raw data
		String[] data = rawData.split(" ");
		for(int i = 0; i < 7; i++)
		{
			values[i] = Integer.parseInt(data[i]);
		}
		return rawData;
	}
}
