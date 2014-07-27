/**
 * 
 */
package Microcontroller;

/**
 * An actor connected to a microcontroller that can perform 
 * a certain action
 * 
 * @author Christoph
 * 
 */
public abstract class Actor extends Component {
	
	//attributes
	private Microcontroller microcontroller;

	/**
	 * @param id unique id
	 * @param name component name
	 */
	public Actor(int id, String name, Microcontroller mc) {
		super(id, name);
		this.microcontroller = mc;
	}
	
	//abstract methods
	/**
	 * performs a specific action
	 * @param args for execution
	 */
	abstract void action(int[] args);
	
	//getter methods
	/**
	 * @return the microcontroller
	 */
	public Microcontroller getMicrocontroller() {
		return microcontroller;
	}	
}
