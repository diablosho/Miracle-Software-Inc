
// DecipherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Decipher.h"
#include "DecipherDlg.h"
#include "DlgProxy.h"
#include "TABLE.h"
#include <vector>
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDecipherDlg dialog


IMPLEMENT_DYNAMIC(CDecipherDlg, CDialogEx);

CDecipherDlg::CDecipherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDecipherDlg::IDD, pParent)
	, m_strKey(_T(""))
	, m_strValidCharacters(_T(""))
	, m_strKeyLengthMax(_T(""))
	, m_strInputCipher(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CDecipherDlg::~CDecipherDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CDecipherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEY, m_strKey);
	DDX_Control(pDX, IDC_KEY, m_cKey);
	DDX_Control(pDX, IDC_VALID_CHARACTERS, m_cValidCharacters);
	DDX_Text(pDX, IDC_VALID_CHARACTERS, m_strValidCharacters);
	DDX_Control(pDX, IDC_KEY_LENGTH_MAX, m_cKeyLengthMax);
	DDX_Text(pDX, IDC_KEY_LENGTH_MAX, m_strKeyLengthMax);
	DDX_Control(pDX, IDC_ORIGINAL_CIPHER_TEXT, m_cInputCipher);
	DDX_Text(pDX, IDC_ORIGINAL_CIPHER_TEXT, m_strInputCipher);
	DDX_Control(pDX, IDC_POTENTIAL_SOLUTIONS, m_cListSolutions);
}

BEGIN_MESSAGE_MAP(CDecipherDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DE_SHIFT, &CDecipherDlg::OnBnClickedDeShift)
	ON_BN_CLICKED(IDC_DE_TRANSPOSE, &CDecipherDlg::OnBnClickedDeTranspose)
//	ON_LBN_SELCHANGE(IDC_POTENTIAL_SOLUTIONS, &CDecipherDlg::OnLbnSelchangePotentialSolutions)
ON_LBN_SELCHANGE(IDC_POTENTIAL_SOLUTIONS, &CDecipherDlg::OnSelchangePotentialSolutions)
ON_BN_CLICKED(IDC_SUBSTITUTE, &CDecipherDlg::OnBnClickedSubstitute)
END_MESSAGE_MAP()


// CDecipherDlg message handlers

BOOL CDecipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_strKeyLengthMax = "8";
	m_strInputCipher = "KUHPVIBQKVOSHWHXBPOFUXHRPVLLDDWVOSKWPREDDVVIDWQRBHBGLLBBPKQUNRVOHQEIRLWOKKRDD";
	m_strKey = "ABCDEFGH";
	m_strValidCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDecipherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDecipherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CDecipherDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CDecipherDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CDecipherDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CDecipherDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CDecipherDlg::OnSelchangePotentialSolutions()
{
	UpdateData(TRUE);
	m_cListSolutions.GetText(m_cListSolutions.GetCurSel(), m_strInputCipher);
	UpdateData(FALSE);
}


void CDecipherDlg::OnBnClickedDeShift()		//	WORKS
{
	/*		Basically, De-Shift:
				1.	Read down each columns, shifting each letter.
				2.	Checks for 100% Completeness once at least 50% of the table is composed of valid words.	*/
	char Alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	std::vector < char > newCipherStrings;
	CString newString;

	UpdateData(TRUE);
	m_cListSolutions.ResetContent();

	for (int K = 26; K >= 0; K--, newString = m_strInputCipher)
	{
		for (int i = 0; i < newString.GetLength(); i++)		//	For every letter in the Cipher-Text:
		{
			switch (m_strInputCipher.GetAt(i))
			{
			case 'A':	newString.SetAt(i, Alphabet[((K + 0) % 26)]);		break;
			case 'B':	newString.SetAt(i, Alphabet[((K + 1) % 26)]);		break;
			case 'C':	newString.SetAt(i, Alphabet[((K + 2) % 26)]);		break;
			case 'D':	newString.SetAt(i, Alphabet[((K + 3) % 26)]);		break;
			case 'E':	newString.SetAt(i, Alphabet[((K + 4) % 26)]);		break;
			case 'F':	newString.SetAt(i, Alphabet[((K + 5) % 26)]);		break;
			case 'G':	newString.SetAt(i, Alphabet[((K + 6) % 26)]);		break;
			case 'H':	newString.SetAt(i, Alphabet[((K + 7) % 26)]);		break;
			case 'I':	newString.SetAt(i, Alphabet[((K + 8) % 26)]);		break;
			case 'J':	newString.SetAt(i, Alphabet[((K + 9) % 26)]);		break;
			case 'K':	newString.SetAt(i, Alphabet[((K + 10) % 26)]);		break;
			case 'L':	newString.SetAt(i, Alphabet[((K + 11) % 26)]);		break;
			case 'M':	newString.SetAt(i, Alphabet[((K + 12) % 26)]);		break;
			case 'N':	newString.SetAt(i, Alphabet[((K + 13) % 26)]);		break;
			case 'O':	newString.SetAt(i, Alphabet[((K + 14) % 26)]);		break;
			case 'P':	newString.SetAt(i, Alphabet[((K + 15) % 26)]);		break;
			case 'Q':	newString.SetAt(i, Alphabet[((K + 16) % 26)]);		break;
			case 'R':	newString.SetAt(i, Alphabet[((K + 17) % 26)]);		break;
			case 'S':	newString.SetAt(i, Alphabet[((K + 18) % 26)]);		break;
			case 'T':	newString.SetAt(i, Alphabet[((K + 19) % 26)]);		break;
			case 'U':	newString.SetAt(i, Alphabet[((K + 20) % 26)]);		break;
			case 'V':	newString.SetAt(i, Alphabet[((K + 21) % 26)]);		break;
			case 'W':	newString.SetAt(i, Alphabet[((K + 22) % 26)]);		break;
			case 'X':	newString.SetAt(i, Alphabet[((K + 23) % 26)]);		break;
			case 'Y':	newString.SetAt(i, Alphabet[((K + 24) % 26)]);		break;
			case 'Z':	newString.SetAt(i, Alphabet[((K + 25) % 26)]);		break;
			default:	newString.SetAt(i, '-');							break;
			}
		}
		m_cListSolutions.AddString(newString);
	}
	
	m_cListSolutions.DeleteString(0);
	m_cListSolutions.SetCurSel(0);	
	UpdateData(FALSE);
	OnSelchangePotentialSolutions();
}


void CDecipherDlg::OnBnClickedDeTranspose()	//	WORKS
{
	/*		Basically, Transpose:
				1.	Writes the cipher-text in rows (top to bottom), making each row = key_length.
				2.	Shuffles the Columns according to the Alphabetical Order of the Key's letters.
				3.  Outputs the columns of the table (from left to right).
				We want to reverse that process...														*/

	UpdateData(TRUE);
	m_cListSolutions.ResetContent();

	if (m_cListSolutions.FindString(-1, m_strInputCipher) < 0)
		m_cListSolutions.AddString(m_strInputCipher);
	
	TABLE	TableToDecipher(m_strInputCipher, m_strKey, _ttoi(m_strKeyLengthMax));	//	Construct the Table to Reverse the Columnar Transposition on.
	CString resultString = NULL;

	m_strValidCharacters = TableToDecipher.m_strCharSet;
	
	for (int col = 0; col < _ttoi(m_strKeyLengthMax); col++)
		resultString += TableToDecipher.TABLE_COLS[col];
	m_cListSolutions.AddString(resultString);
	m_cListSolutions.SetCurSel(m_cListSolutions.GetCount() - 1);
	UpdateData(FALSE);
	OnSelchangePotentialSolutions();
}


//	MUST IMPLEMENT STILL
void CDecipherDlg::OnBnClickedSubstitute()
{
	/*	1.	CALCULATE THE WORKING-SET FOR CIPHER-TEXT
		2.	FOR EVERY ELEMENT IN THE WORKING-SET:
			A.	REPLACE ALL OCCURENCES IN THE CIPHER-TEXT OF THE 1ST WORKING-SET LETTER WITH ANOTHER LETTER
				AA.	REPEAT FOR THE ENTIRE ALPHABET, MAKING 26-P-(WORKING-SET-LENGTH) DIFFERENT STRINGS
			B.	ENSURING THAT THE CHARACTER REPLACEMENTS FROM (1AA) ARE NOT DUPLICATED, REPEAT STEP (1A).	*/
	FindCharacterSet(m_strInputCipher);
	Permute();
}


unsigned long int CDecipherDlg::fact(unsigned int n)
{
	if (n == 0)	return 1;
	return (n * fact(n - 1));
}


std::vector<CString> CDecipherDlg::Permute()
{
	UpdateData(TRUE);
	//CFile fileWorkingSetPermutations;
	//fileWorkingSetPermutations.Open(_T("Working_Set_Permutations_File.txt"), CFile::modeReadWrite | CFile::typeText);
	
	//	Generate starting working set
	CString newWorkingSetString("ABCDEFGHIJKLMNOPQRSTUVWXYZ");					//	Default Working Set
	int sizeWorkingSet = m_strValidCharacters.GetLength();
	newWorkingSetString.Delete(sizeWorkingSet, (newWorkingSetString.GetLength() - (sizeWorkingSet)));		//	Calculate the difference in lengths, and subtract from newWorkingSetString
	
	/*	GO THROUGH ALL THE PERMUTATIONS	*/
	for (unsigned long int countPermutations = 0, numberOfPermutations = (fact(26) / fact(26 - sizeWorkingSet)); countPermutations <= numberOfPermutations; countPermutations++)
	{
		/*	GO THROUGH ALL THE POSITIONS IN THE WORKING SET	*/
		for (int positionWorkingSetCharacter = sizeWorkingSet - 1; positionWorkingSetCharacter >= 0; positionWorkingSetCharacter--)
		{
			/*	IF THE CHARACTER IS OUT-OF-RANGE, ROLL IT OVER TO THE FIRST CHARACTER WITHIN THE RANGE	*/
			if (newWorkingSetString.GetAt(positionWorkingSetCharacter) > MAX_CHARACTER)
			{
				/*	IF WE AREN'T POSITIONED AT THE FIRST CHARACTER IN THE WORKING SET	*/
				if (positionWorkingSetCharacter > 0)
				{
					newWorkingSetString.SetAt(positionWorkingSetCharacter - 1, newWorkingSetString.GetAt(positionWorkingSetCharacter - 1) + 1);	//	Increment previous character
					newWorkingSetString.SetAt(positionWorkingSetCharacter, MIN_CHARACTER);														//	Rollover current character to 'A'
				}
				else		//	IF WE ARE POSITIONED AT THE FIRST CHARACTER IN THE WORKING SET
				{
					newWorkingSetString.SetAt(positionWorkingSetCharacter, MIN_CHARACTER);		//	ROLLOVER THE FIRST CHARACTER TO 'A'
				}
			}
		}

		//fileWorkingSetPermutations.Write((newWorkingSetString += '\n'), sizeWorkingSet);

	}
			/*		
			-	WHILE CHANGES HAVE BEEN MADE:
			--		LOOP THROUGH ALL CHARACTER POSITIONS IN THE WORKING SET.
			---		WHILE WE'RE NOT ON THE FIRST CHARACTER:
			----		LOOP THROUGH ALL THE CHARACTERS BEFORE OUR CURRENT POSITION:
			----		CHECK IF OUR CURRENT CHARACTER IS EQUAL TO ANY OF THE PREVIOUS CHARACTERS
			-----		IF IT IS, THEN INCREMENT OUR CURRENT CHARACTER,
			-----		RESET OUR CHARACTER POSITION, AND
			-----		RETRIP OUR changesMade FLAG
			---		MOVE ONE CHARACTER CLOSER TO THE BEGINNING.
			---		ONCE WE'RE AT THE FIRST CHARACTER, AND NO CHANGES WERE MADE TO GET US FROM THE LAST CHARACTER TO THE FIRST, THEN THE STRING IS UNIQUE
			----		WRITE IT TO THE FILE
			*/
			/*bool changesMade = false;
			do
			{
				for (int ThisCharacterPosition = sizeWorkingSet-1; ThisCharacterPosition >= 0; ThisCharacterPosition--)
				{
					for (int PreviousCharacterPosition = ThisCharacterPosition - 1; PreviousCharacterPosition >= 0; PreviousCharacterPosition--)
					{
						if (newWorkingSetString.GetAt(ThisCharacterPosition) == newWorkingSetString.GetAt(PreviousCharacterPosition))
						{
							newWorkingSetString.SetAt(ThisCharacterPosition, newWorkingSetString.GetAt(ThisCharacterPosition) + 1);
							ThisCharacterPosition = 18;
							PreviousCharacterPosition = ThisCharacterPosition - 1;
							changesMade = true;
						}
					}
				}
				
				fileWorkingSetPermutations.Write((newWorkingSetString += '\n'), sizeWorkingSet);
			}	while (changesMade == true);
		}
	}*/
	
	return std::vector<CString>();
}


/*	Determine the set of Unique Characters in the Cipher-Text Input String	*/
void CDecipherDlg::FindCharacterSet(CString m_strData)
{
	UpdateData(TRUE);
	CString CHAR_SET = NULL;
	char currentChar = NULL;
	int charPos = NULL;

	while (m_strData.GetLength() > 0)
	{
		currentChar = m_strData.GetAt(0);
		m_strData.Delete(0, 1);
		charPos = m_strData.Find(currentChar);
		if (charPos < 0)	//	currentChar Not Found anymore
		{
			charPos = 0;
			CHAR_SET.AppendChar(currentChar);
		}
	}

	std::sort(CHAR_SET.GetBuffer(), CHAR_SET.GetBuffer() + CHAR_SET.GetLength());
	m_strValidCharacters = CHAR_SET;

	UpdateData(FALSE);
}