//----------------------------------------------------------------------
// ArrayStringLog.java        by Dale/Joyce/Weems              Chapter 2
//								updated by Lee
// Implements StringLogInterface using an array to hold the strings.
//----------------------------------------------------------------------

public class ArrayStringLog implements StringLogInterface
{
  protected String name;              // name of this StringLog
  protected String[] log;             // array that holds strings
  protected int lastIndex = -1;       // index of last string in array

  // Precondition:   maxSize > 0
  //
  // Instantiates and returns a reference to an empty ArrayStringLog
  // object with name "name" and room for maxSize strings.
  public ArrayStringLog(String name, int maxSize)
  {
    log = new String[maxSize];
    this.name = name;
  }

  // Instantiates and returns a reference to an empty ArrayStringLog
  // object with name "name" and room for 10000 strings.
  public ArrayStringLog(String name)
  {
    log = new String[10000];
    this.name = name;
  }

  // Precondition:   This StringLog is not full.
  //
  // Places element into this StringLog.
  public void insert(String element)
  {
    lastIndex++;
    log[lastIndex] = element;
  }

  // Returns true if this StringLog is full, otherwise returns false.
  public boolean isFull()
  {
    if (lastIndex == (log.length - 1))
      return true;
    else
      return false;
  }

  // Returns the number of Strings in this StringLog.
  public int size()
  {
    return (lastIndex + 1);
  }

  // Returns true if element is in this StringLog,
  // otherwise returns false.
  // Ignores case differences when doing string comparison.
  public boolean contains(String element)
  {
    int location = 0;
    while (location <= lastIndex)
    {
      if (element.equalsIgnoreCase(log[location]))  // if they match
        return true;
      else
        location++;
    }
   return false;
  }

  // Makes this StringLog empty.
  public void clear()
  {
    for (int i = 0; i <= lastIndex; i++)
      log[i] = null;
    lastIndex = -1;
  }

  // Returns the name of this StringLog.
  public String getName()
  {
    return name;
  }

  // Returns a nicely formatted string representing this StringLog.
  public String toString()
  {
    String logString = "Log: " + name + "\n\n";

    for (int i = 0; i <= lastIndex; i++)
      logString = logString + (i+1) + ". " + log[i] + "\n";

    return logString;
  }

/*-----------------HW2_Problems_21-26------------------------*/
  	// Returns true if this StringLog is empty, otherwise returns false.
  	public boolean isEmpty(){
		if (lastIndex == (- 1))
			return true;
		else
			return false;
	}

	// Returns how many times element occurs in this StringLog.
	public int howMany(String element){
		int count = 0;
		for (int location = 0; location <= lastIndex; location++)
			if (element.equalsIgnoreCase(log[location])) // if they match
				count++;
		return count;
	}

	// Places element into this StringLog unless an
	// identical string (case insensitive match)
	// is already in this StringLog.
	//
	// Assumes StringLog not full if insertion required.
	public boolean uniqInsert(String element){
		if (this.contains(element))
			return false;
		else{
			this.insert(element);
			return true;
		}
	}

	// Deletes one occurence of element from this StringLog,
	// if possible, and returns true. Otherwise returns false.
	public boolean delete(String element){
		boolean moreToSearch;
		int location = 0;
		boolean found = false;
		moreToSearch = (location <= lastIndex);
		while (moreToSearch && !found){
			if (element.equalsIgnoreCase(log[location]))
				found = true;
			else{
				location++;
				moreToSearch = (location <= lastIndex);
			}
		}
		if (found){
			log[location] = log[lastIndex];
			log[lastIndex] = null;
			lastIndex--;
		}
		return found;
	}

	// Deletes all occurences of element from this StringLog,
	// if any, and returns the number of deletions.
	public int deleteAll(String element){
		int count = 0;
		while (this.delete(element))
			count++;
		return count;
	}

	// Precondition: this log contains at least one string
	//
	// Returns smallest element in this StringLog
	public String smallest(){
		String small = log[0];
		for (int i = 1; i <= lastIndex; i++)
			if (small.compareTo(log[i]) > 0)
				small = log[i];
		return small;
	}
}