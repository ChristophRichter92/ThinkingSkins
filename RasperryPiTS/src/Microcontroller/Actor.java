/**
 * 
 */
package Microcontroller;

/**
 * @author Christoph
 * An actor connected to a microcontroller that can perform 
 * a certain action
 */
public abstract class Actor extends Component {
	
	//attributes
	private Microcontroller microcontroller;

	/**
	 * @param id unique id
	 * @param name component name
	 */
	public Actor(int id, String name) {
		super(id, name);
		// TODO Auto-generated constructor stub
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
