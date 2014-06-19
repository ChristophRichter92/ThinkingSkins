/**
 * 
 */
package Microcontroller;

/**
 * @author Christoph
 *	A sensor connected to an microcontroller
 */
public abstract class Sensor extends Component {

	//attributes
	private Microcontroller microcontroller;
	
	/**
	 * @param id unique id
	 * @param name component name
	 */
	public Sensor(int id, String name, Microcontroller mc) {
		super(id, name);
		this.microcontroller = mc;
		// TODO Auto-generated constructor stub
	}
	
	//abstract methods
	/**
	 * Every sensor should return a specific value
	 * TODO maybe change data type
	 * @return
	 */
	abstract int readData();

	//getter methods
	/**
	 * @return the microcontroller
	 */
	public Microcontroller getMicrocontroller() {
		return microcontroller;
	}	
}
