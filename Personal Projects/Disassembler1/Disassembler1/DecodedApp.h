#pragma once
class CDecodedApp
{
public:
	CDecodedApp(void);
	~CDecodedApp(void);
	CString PE[5];	// [0] = MZ Header, [1] = File Header, [2] = Optional Header, [3] = Section Header, [4] = Section Header
};

