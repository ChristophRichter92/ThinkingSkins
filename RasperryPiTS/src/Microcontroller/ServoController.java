/**
 * 
 */
package Microcontroller;

/**
 * This class controlles 2 Servos which move the front of the facade  
 * @author Christoph
 *
 */
public class ServoController extends Actor {

	/**
	 * @param id
	 * @param name
	 */
	public ServoController(int id, String name) {
		super(id, name);
		// TODO Auto-generated constructor stub
	}

	/**
	 * Moves Servos up, down, left, right like an old screensaver
	 */
	@Override
	public void action(int[] args) 
	{
		// TODO Auto-generated method stub
		//screensaver
	}
	
	/**
	 * Moves servos to open position
	 */
	public void open()
	{
		this.getMicrocontroller().sendMessage("open()");
	}
	
	/**
	 * Moves servos to closed position
	 */
	public void close()
	{
		this.getMicrocontroller().sendMessage("close()");
	}

	/**
	 * Moves servos in specified position
	 * @param x x-Coordinate
	 * @param y y-Coordinate
	 */
	public void move(int x, int y)
	{
		this.getMicrocontroller().sendMessage("move(" + x + ", " + y + ")");
	}

}
