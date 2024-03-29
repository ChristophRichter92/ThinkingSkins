/**
 * 
 */
package Microcontroller;

/**
 * RGB LEDs connected to a microcontroller, which are used as backlight
 * @author Christoph
 *
 */
/**
 * @author Christoph
 *
 */
public class Backlight extends Actor {

	/**
	 * @param id unique ID
	 * @param name of the Backlight
	 */
	public Backlight(int id, String name, Microcontroller mc) 
	{
		super(id, name, mc);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see Microcontroller.Actor#action(int[])
	 */
	@Override
	void action(int[] args) 
	{
		//no default action
	}
	
	/**
	 * activates LED backlight in default color (white)
	 */
	public void on()
	{
		System.out.println(this.getMicrocontroller().sendMessage("on()"));
	}
	
	/**
	 * turns the LED backlight off
	 */
	public void off()
	{
		System.out.println(this.getMicrocontroller().sendMessage("off()"));
	}
	
	/**
	 * changes the color of every LED
	 * @param r red parameter [0,255]
	 * @param g green parameter [0,255]
	 * @param b blue parameter [0,255]
	 */
	public void changeColor(int r, int g, int b)
	{
		this.getMicrocontroller().sendMessage("changeColor(" + r + "," + g + "," + b + ")");
	}

}
