package x86ISA;
import java.io.IOException;
import java.sql.*;

public class Database
{
	String		driver			=	"sun.jdbc.odbc.JdbcOdbcDriver",
				url				=	"JDBC:ODBC:Driver={Microsoft Access Driver (*.mdb, *.accdb)}; DBQ=",
				username		=	"",
				password		=	"";
	Driver		dbDriver;
	Connection	dbConnection;
	Statement	dbStatement;
	
	public Database(String DBFile)	//	Assuming ACCESS Database file from this point on...
	{
		String pathDBFile;
		try
		{
			url += (pathDBFile = new java.io.File(DBFile).getCanonicalPath()) + ";";
			dbDriver		=	(Driver)Class.forName(driver).newInstance();
			dbConnection	=	DriverManager.getConnection(url);
			dbStatement		=	dbConnection.createStatement();
			System.out.println("OK  " + dbDriver);
		}
		catch (IOException e)				{	e.printStackTrace();	}
		catch (InstantiationException e)	{	e.printStackTrace();	}
		catch (IllegalAccessException e)	{	e.printStackTrace();	}
		catch (ClassNotFoundException e)	{	e.printStackTrace();	}
		catch (SQLException e)				{	e.printStackTrace();	}
	}
}