/**
 * 
 */
package Manager;

import java.util.EventListener;

/**
 * @author Christoph
 *
 */
public interface SensorListener extends EventListener 
{
	//the distance to an object in front of the fassade
	public void distanceIsLow();
	public void distanceIsNormal();
	
	//it is not that noisy
	public void soundIsLow();
	public void soundIsHigh();
	public void soundIsNormal();
	
	//gestures
	public void present();

}
