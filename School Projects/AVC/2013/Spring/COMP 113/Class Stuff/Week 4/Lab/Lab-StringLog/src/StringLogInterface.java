//----------------------------------------------------------------------
// StringLogInterface.java     by Dale/Joyce/Weems             Chapter 2
//
// Interface for a class that implements a log of Strings.
// A log "remembers" the elements placed into it.
//
// A log must have a "name".
//----------------------------------------------------------------------

public interface StringLogInterface
{
  	// Precondition:   This StringLog is not full.
  	//
  	// Places element into this StringLog.
  	void insert(String element);

  	// Returns true if this StringLog is full, otherwise returns false.
  	boolean isFull();

	// Returns the number of Strings in this StringLog.
  	int size();

  	// Returns true if element is in this StringLog,
  	// otherwise returns false.
  	// Ignores case differences when doing string comparison.
  	boolean contains(String element);

  	// Makes this StringLog empty.
  	void clear();

	// Returns the name of this StringLog.
  	String getName();

  	// Returns a nicely formatted string representing this StringLog.
  	String toString();

  /*----------------Newly added------------------*/

  	// Returns true if this StringLog is empty, otherwise returns false.
 	boolean isEmpty();

  	// Returns how many times element occurs in this StringLog.
  	int howMany(String element);

  	// Places element into this StringLog unless an
  	// identical string (case insensitive match)
  	// is already in this StringLog.
  	//
	// Assumes StringLog not full if insertion required.
	public boolean uniqInsert(String element);

	// Deletes one occurrence of element from this StringLog,
	// if possible, and returns true. Otherwise returns false.
	public boolean delete(String element);

	// Deletes all occurrences of element from this StringLog,
	// if any, and returns the number of deletions.
	public int deleteAll(String element);

	// Precondition: this log contains at least one string
	//
	// Returns smallest element in this StringLog
	public String smallest();
}
