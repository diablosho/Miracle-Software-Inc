/* Name:	Brian Jones
 * Date:	9/21/2013
 * Class:	Comp 333
 * Assignment:	Project 1B - Recursive descent parser for simple assignment language
*/

import java.util.*;

public class AssignLangParser
{
	public static char nextChar;
	public static String tokens;
	public static int index = 0;
	public enum Error_Type { 	default_error,
								invalid_number,
								invalid_identifier,
								invalid_statement,
								missing_semicolon, 
								extra_semicolon,
								missing_dollar_sign}
	Error_Type	msgError	=	null;
	static Scanner keyboard = new Scanner(System.in);
	
	public static void error(Error_Type error)
	{
		System.out.print("\nSyntax error at char:  " + nextChar + ":  ");
		switch (error)
		{
		case invalid_number:		System.out.println("Invalid Number");		break;
		case invalid_identifier:	System.out.println("Invalid Identifier");	break;
		case invalid_statement:		System.out.println("Invalid Statement");	break;
		case missing_semicolon:		System.out.println("Missing Semicolon");	break;
		case extra_semicolon:		System.out.println("Extra Semicolon");		break;
		case missing_dollar_sign:	System.out.println("Missing '$'");			break;
		case default_error:			System.out.println("Unknown error");		break;
		}
		System.exit(1);
	}
	
	public static void getChar()
	{
		while (index < tokens.length() && Character.isWhitespace(tokens.charAt(index)))
			index++;
		if (index < tokens.length())
			nextChar = tokens.charAt(index++);
		else error(Error_Type.missing_dollar_sign);
	}
	
	public static void program()
	{
		stmtList();
		switch (nextChar)
		{
		case '$':	System.out.println("Successful parse");	break;
		default:	error(Error_Type.missing_dollar_sign);
		}
	}
	
	public static void stmtList()
	{
		stmt();
		switch (nextChar)
		{
		case ';':	getChar();	stmtList();		break;
		case '$':								break;
		default:	error(Error_Type.missing_semicolon);
		}
	}
	
	public static void stmt()
	{
		id();
		switch (nextChar)
		{
		case '=':	System.out.print(nextChar + " ");	getChar();	num();	break;
		default:	error(Error_Type.invalid_statement);
		}
		System.out.println("");
	}
	
	public static void id()
	{
		switch (nextChar)
		{
		case 'x':
		case 'y':
		case 'z':	System.out.print(nextChar + " ");		getChar();	return;
		case '$':	error(Error_Type.extra_semicolon);					return;
		default:	error(Error_Type.invalid_identifier);				return;
		}
	}
	
	public static void num()
	{
		if (!Character.isDigit(nextChar))		
			error(Error_Type.invalid_number);
		else
		{
			while (Character.isDigit(nextChar))
			{
				System.out.print(nextChar);
				getChar();
			}
		}
	}
	
	public static void main(String[] args)
	{
		System.out.print("Enter string to Parse:  ");
		tokens = keyboard.nextLine();
		
		getChar();
		program();
		System.out.println("Completed Parse");
	}
}