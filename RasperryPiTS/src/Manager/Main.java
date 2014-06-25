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
		Thread t=new Thread() 
		{
			public void run() 
			{
				System.out.println("Thinking Skins!");
				System.out.println("==============================");
				Arduino ard = new Arduino(1, "Arduino1");
				String out = ard.sendMessage("Hello");
				System.out.println("You: Hello");
				System.out.println("Arduino: " + out);
				
				int i = 0;
				while(i < 60)
				{
					String out2 = ard.sendMessage("Sound");
					System.out.println("You: Sound");
					System.out.println("Arduino: " + out2);
					
					String out3 = ard.sendMessage("getSound()");
					System.out.println("You: getSound()");
					System.out.println("Arduino: " + out3);
					
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					i++;
				}
				
				//clean up
				ard.cleanUp();
		        //Message
				System.out.println("End...");
				System.out.println("Good bye");
			}
		};
		t.start();		
	}
}
