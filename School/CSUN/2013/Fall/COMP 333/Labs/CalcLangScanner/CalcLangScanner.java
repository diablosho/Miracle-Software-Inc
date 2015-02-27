/* Name:	Brian Jones
 * Date:	9/21/2013
 * Class:	Comp 333
 * Assignment:	Project 1A - Calculator Language Lexicon 
 */

class Lexicon
{
	String[]	Token			=	new String[100];
	String		stringToScan	=	null;
	char		currentChar		=	' ';
	int			currentIndex	=	0,
				currentToken	=	0,
				stringLength	=	0;
	
	public Lexicon(String inputString)
	{
		stringToScan = inputString;
		stringLength = stringToScan.length();
		InitializeArray(Token, 100);
		Tokenize(stringToScan);
	}
	
	public void InitializeArray(String[] array, int size)
	{
		for (int i = 0; i < size; i++)		array[i] = "";
	}
	
	public char getChar(int stringIndex)
	{
		if (!isEOF())	return	stringToScan.charAt(stringIndex);
		else			return 	stringToScan.charAt(stringLength-1);
	}
	
	public boolean isOperator()
	{
		switch (currentChar)
		{
		case '(':	return true;
		case ')':	return true;
		case '+':	return true;
		case '-':	return true;
		case '*':	return true;
		case '/':	return true;
		case ';':	return true;
		case '=':	return true;
		case '.':	return true;
		default:	return false;
		}
	}
	
	public void OutputOperator()
	{
		switch (currentChar)
		{
		case '(':	Token[currentToken] = "\tlparen";		break;
		case ')':	Token[currentToken] = "\trparen";		break;
		case '+':	Token[currentToken] = "op:\t+";			break;
		case '-':	Token[currentToken] = "op:\t-";			break;
		case '*':	Token[currentToken] = "op:\t*";			break;
		case '/':	Token[currentToken] = "op:\t/";			break;
		case ';':	Token[currentToken] = "\tsemicolon";	break;
		case '=':	Token[currentToken] = "\tassign";		break;
		case '.':	Token[currentToken] = "\tperiod";		break;
		}
	}
	
	public void skipWhiteSpace()
	{
		while (Character.isSpaceChar(currentChar) && !isEOF())		
			currentChar = getChar(++currentIndex);
	}
	
	public void FinishToken()
	{
		currentToken++;
		currentChar = getChar(++currentIndex);
	}
	
	public boolean isEOF()
	{
		if (currentIndex >= stringLength)	return true;
		else								return false;
	}
	
	public void Tokenize(String scanString)
	{
		currentChar = getChar(currentIndex);
		do
		{
			skipWhiteSpace();
					
			if (isOperator())
			{
				OutputOperator();
				FinishToken();				
			}
			else if (Character.isSpaceChar(currentChar))
				FinishToken();	
			else if (Character.isDigit(currentChar))
			{
				Token[currentToken] = "number:\t";
				while ((Character.isDigit(currentChar) || (isOperator() && currentChar == '.')) 
						&& !isEOF())
				{
					Token[currentToken] += currentChar;
					if (!isEOF())	currentChar = getChar(++currentIndex);
				}
				currentToken++;
			}
			else if (Character.isLetter(currentChar))
			{
				while ((Character.isLetterOrDigit(currentChar)				|| 
						!(Character.isSpaceChar(currentChar)))				&& 
						!(isOperator())										&&
						!(isEOF())											&&
						!(	Token[currentToken].equalsIgnoreCase("read")	||
							Token[currentToken].equalsIgnoreCase("write")))
				{
					Token[currentToken] += currentChar;
					currentChar = getChar(++currentIndex);
				}

				if (!(	Token[currentToken].equalsIgnoreCase("read") || 
						Token[currentToken].equalsIgnoreCase("write")))
				{
					String temp = Token[currentToken];
					Token[currentToken] = "id:\t" + temp;
				}
				currentToken++;
			}
			else
			{
				Token[currentToken++]	= "ERROR:  Unknown Symbol (\'" + currentChar + "\')";
				break;
			}
			
		}	while (!isEOF());		
	}
}

public class CalcLangScanner
{
	public static void main(String[] args)
	{
		String[] stringsToAnalyze	=	{	"read x ;  y = ( x + 7) * z ; write y  .",
											"age2 = age1 + 15 ; ",
											"u = 3.145  +  radius ;",
											"reader =  10 -  -87 ;",
											"chara$ter = 34 ;",
											"q123werty   ;  ;+  .",
											"a   b    c    d       =   60       ",
											"if ( x  =  10 ) u = 7 ; a = 5   ."
										};
		Lexicon analyzer[]			=	new Lexicon[stringsToAnalyze.length];
		
		for (int i = 0; i < stringsToAnalyze.length; i++)
		{
			analyzer[i]	= new Lexicon(stringsToAnalyze[i]);
			System.out.println("Sample Input:\t\"" + stringsToAnalyze[i] + "\"");
			for (int j = 0; j < analyzer[i].currentToken; j++)
				System.out.println(analyzer[i].Token[j]);
			System.out.println("");
		}
	}
}