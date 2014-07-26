/**
 * 
 */
package Microcontroller;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;


public class SerialConnection implements SerialPortEventListener
{
	//attributes
	private SerialPort serialPort ;         //defining serial port object
	private String portName;
	private CommPortIdentifier portId  = null;       //my COM port
	private static final int TIME_OUT = 2000;    //time in milliseconds
	private int baudRate = 9600; //baud rate to 9600bps
	private BufferedReader input;               //declaring my input buffer
	private OutputStream output;                //declaring output stream
	private String in;
	

	//constructor
	public SerialConnection(int baudRate, String portName) 
	{
		this.portName = portName;
		
        //Message
		System.out.println("Initializing:");
		
		initialize();
		portConnect();
		try {	//needed for timeout
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
        //Message
		System.out.println("-> done");
	}
	
	//methods
	/**
	 * initializes the serial connection
	 */
	private void initialize()
	{	
		CommPortIdentifier ports = null;      //to browse through each port identified
		@SuppressWarnings("rawtypes")
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers(); //store all available ports
        while(portEnum.hasMoreElements()) //browse through available ports
        {  
        	ports = (CommPortIdentifier)portEnum.nextElement();
            //following line checks whether there is the port i am looking for and whether it is serial
            if(ports.getPortType() == CommPortIdentifier.PORT_SERIAL&&ports.getName().equals(portName))
            { 
                System.out.println("Port found: " + portName);
                portId = ports;                  //initialize my port
                break;                                                                                     
            }         
        }
        //if serial port am looking for is not found
        if(portId==null)
        {
        	System.out.println("Port not found");
        	System.exit(1);
        }
	}
	
	/**
	 * Opens the wanted serial port
	 */
	private void portConnect()
	{
		//connect to port
        try
        {
        	serialPort = (SerialPort)portId.open(this.getClass().getName(),TIME_OUT);   
        	System.out.println("Port open succesful"); 
    
        	//set serial port parameters
        	serialPort.setSerialPortParams(baudRate,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
        }
        catch(PortInUseException e){
            System.out.println("Port already in use");
            System.exit(1);
        }
        catch(NullPointerException e2){
            System.out.println("COM port maybe disconnected");
        }
        catch(UnsupportedCommOperationException e3){
            System.out.println(e3.toString());
        }
       
        //input and output channels
        try
        {
        	//defining reader and output stream
        	input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
        	output =  serialPort.getOutputStream();
        	//adding listeners to input and output streams
        	serialPort.addEventListener(this);
        	serialPort.notifyOnDataAvailable(true);
        	serialPort.notifyOnOutputEmpty(true);
        }
        catch(Exception e)
        {
            System.out.println(e.toString());
        }
    }
	
	 /**
     * Handle serial events. Dispatches the event to event-specific
     * methods.
     * @param event The serial event
     */
    @Override
	public synchronized void serialEvent(SerialPortEvent event) 
	{ 	   
		if (event.getEventType() == SerialPortEvent.DATA_AVAILABLE) //Read data
		{ 
			try 
			{
				String inputLine=input.readLine();
				in = inputLine;
				notify();
			} 
			catch (Exception e) 
			{
				//System.err.println(e.toString());
			}
		}
		else if(event.getEventType() == SerialPortEvent.OUTPUT_BUFFER_EMPTY)
		{
		
		}
	}
	
	/**
	 * closes the opened port
	 */
	public synchronized void close()
	{
		if(serialPort!=null)
		{
            serialPort.close(); //close serial port
        }
        input = null;        //close input and output streams
        output = null;
    }
	
	/**
	 * Sends a message to the connected port
	 * @param message you want to send
	 * @throws InterruptedException 
	 */
	private synchronized void write(String message)
	{
		//portConnect();
		try 
		{
			output.write(message.getBytes());
			output.flush();
			wait();
		} 
		catch (IOException e) 
		{
			System.out.println("Can not write data");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * read input buffer
	 * @return read data
	 */
	private String read()
	{
		//portConnect();
		String res = "";
		res = in;
		//close();	
		return res;
	}
	
	/**
	 * write data and get response
	 * @param message you want to send
	 * @return response from the port
	 */
	public String readAndWrite(String message)
	{
		String res = "";
		write(message+'\n');
		res = read();
		return res;
	}
}