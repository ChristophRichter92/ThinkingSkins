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
	public void distanceIsLow();
}
