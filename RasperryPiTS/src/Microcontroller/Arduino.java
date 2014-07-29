/**
 * 
 */
package Microcontroller;


/**
 * @author Christoph
 *
 */
public class Arduino extends Microcontroller {

	//attributes
	private SerialConnection con;	//serial connection to the arduino
	
	//Constructor
	/**
	 * @param id unique ID
	 * @param name name of the Arduino
	 */
	public Arduino(int id, String name) {
		super(id, name);
		con = new SerialConnection(9600, "/dev/ttyS80");//"dev/ttyACM0");///dev/ttyACM0");//"COM4");
	}

	/**
	 * Sends a message via COM port to the connected microkontroller an receives 
	 */
	@Override
	public String sendMessage(String message)
	{
		String res = con.readAndWrite(message);
		return res;
	}

	/**
	 * closes serial connection
	 */
	public void cleanUp() 
	{
		con.close();
	}
}
