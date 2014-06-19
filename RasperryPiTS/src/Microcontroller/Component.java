package Microcontroller;

public abstract class Component {
	//Attributes
	private int id;
	private String name;

	/**
	 * Constructor sets name and id
	 * @param id unique ID
	 * @param name Name of the Component
	 */
	public Component(int id, String name)
	{
		this.id = id;
		this.name = name;
	}

	
	//Methods
	/**
	 * @return the id
	 */
	public int getId() {
		return id;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
}
