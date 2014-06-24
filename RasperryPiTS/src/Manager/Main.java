/**
 * 
 */
package Manager;

import Microcontroller.Arduino;

/**
 * @author Christoph
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		System.out.println("Nur ein Test");
		Arduino ard = new Arduino(1, "Arduino1");
		String out = ard.sendMessage("Hello");
		System.out.println("You: Hello");
		System.out.println("Arduino: " + out);
	}

}
