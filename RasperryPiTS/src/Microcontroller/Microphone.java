/**
 * 
 */
package Microcontroller;

/**
 * @author Christoph
 *
 */
public class Microphone extends Sensor {

	/**
	 * @param id
	 * @param name
	 * @param mc
	 */
	public Microphone(int id, String name, Microcontroller mc) {
		super(id, name, mc);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see Microcontroller.Sensor#readData()
	 */
	@Override
	int readData() {
		// TODO Auto-generated method stub
		return 0;
	}

}
