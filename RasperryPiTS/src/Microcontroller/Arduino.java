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
	
	//Constructor
	/**
	 * @param id unique ID
	 * @param name name of the Arduino
	 * @param comPort name of the COM port the arduino is connected to
	 */
	public Arduino(int id, String name) {
		super(id, name);
		// TODO Auto-generated constructor stub
	}

	/**
	 * Sends a message via COM port to the connected microkontroller an receives 
	 */
	@Override
	public String sendMessage(String message)
	{
		SerialConnection con = new SerialConnection(9600, "COM4");//"/dev/ttyUSB0");
		String res = con.readAndWrite(message);
		return res;
	}
}
