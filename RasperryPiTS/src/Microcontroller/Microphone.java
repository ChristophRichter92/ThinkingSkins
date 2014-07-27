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
	Integer[] soundLevel;
	/**
	 * @param id unique ID
	 * @param name of the Microphone
	 * @param mc Connected Mikrocontroller
	 */
	public Microphone(int id, String name, Microcontroller mc) {
		super(id, name, mc);
		soundLevel = new Integer[7];
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
			soundLevel[i] = Integer.parseInt(data[i]);
		}
		return rawData;
	}

	/**
	 * A sound level contains 7 frequencies
	 * @return the soundLevel
	 */
	public Integer[] getSoundLevel() 
	{
		System.out.println(readData());
		return soundLevel;
	}
	
	
	
}
