import java.sql.Connection;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Database
{
	static	Driver				dbDriver	=	null;
	static	Connection			conn		=	null;
	static	Statement			stmt		=	null;
	static	ResultSet			res			=	null;
	static	PreparedStatement	pst			=	null;
	
	public Database(String driver, String url, String uname, String pword) throws Exception
	{
		ConnectToCHAOSNet(driver, url, uname, pword);
		BuildTablesFromFiles();
	}
	
	public static void ConnectToCHAOSNet(String driver, String url, String uname, String pword) throws Exception
	{
		dbDriver = (Driver) Class.forName(driver).newInstance();
		conn	=	DriverManager.getConnection(url,uname,pword);
		System.out.println("OK  " + dbDriver);
	}
	
	public static void DropTables() throws SQLException
	{
		String	tempString	=	new	String();
		stmt	=	conn.createStatement();
		
		//	DELETE THESE DROP TABLES STATEMENTS ONCE THE DATABASE IS WORKING PROPERLY
		for (int tableNum = 0; tableNum < 4; tableNum++)
		{
			tempString = "DROP TABLE IF EXISTS ";
			switch (tableNum)
			{
			case 0:	tempString += "Player";		break;
			case 1:	tempString += "Treasure";	break;
			case 2:	tempString += "City";		break;
			case 3:	tempString += "Map";		break;
			}
			pst = conn.prepareStatement(tempString);
			pst.executeUpdate();
		}
		//	DELETE THESE DROP TABLES STATEMENTS ONCE THE DATABASE IS WORKING PROPERLY
	}
	
	public void Update(String Table, int PID, String place, int wealth)
	{
		try
		{
			pst	=	conn.prepareStatement("UPDATE Player SET place=?, wealth=? WHERE id = ?; ");
			pst.setString(1, place);
			pst.setInt(2, wealth);
			pst.setInt(3, PID);
			pst.executeUpdate();
		}
		catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	public static void BuildTablesFromFiles() throws SQLException
	{
		DropTables();
		
		pst.addBatch("CREATE TABLE IF NOT EXISTS Player "
					+"(id int NOT NULL, place varchar(6), wealth int, "
					+"PRIMARY KEY (id)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS Treasure "
					+"(place varchar(6), gold int, "
					+"PRIMARY KEY (place)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS Map "
					+"(place varchar(6) NOT NULL, treasurePlace varchar(6) NOT NULL, "
					+"PRIMARY KEY (place)); ");
		pst.addBatch("CREATE TABLE IF NOT EXISTS City "
					+"(place varchar(6), cost int, "
					+"PRIMARY KEY (place)); ");
		pst.addBatch("LOAD DATA LOCAL INFILE 'player.txt' INTO TABLE Player");
		pst.addBatch("LOAD DATA LOCAL INFILE 'treasure.txt' INTO TABLE Treasure");
		pst.addBatch("LOAD DATA LOCAL INFILE 'map.txt' INTO TABLE Map");
		pst.addBatch("LOAD DATA LOCAL INFILE 'city.txt' INTO TABLE City");
		pst.executeBatch();
	}
}