// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "Game.h"

class CDebugWindow *DbgWnd;
class Crusade* CSade;

extern void PutLogList(char * cMsg);
extern char G_cTxt[512];
extern char	G_cData50000[50000];
extern void PutLogFileList(char * cStr);
extern void PutAdminLogFileList(char * cStr);
extern void PutItemLogFileList(char * cStr);
extern void PutLogEventFileList(char * cStr);
extern void PutHackLogFileList(char * cStr);
extern void PutPvPLogFileList(char * cStr);
extern FILE * pLogFile;
extern HWND	G_hWnd;

#pragma warning (disable : 4996 6011 6001 4244 4018 6385 6386 26451 6054 4267 6053 6031)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern BOOL	G_bIsThread;
extern unsigned __stdcall ThreadProc(void *ch);

// Move lock para 800 x 600
int _tmp_iMoveLocX[9][47] = {
	// 0   1   2   3   4   5   6   7   8   9  10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46
	// 0
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	// 1
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//2
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, -1 },
	//3
	{ 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//4
	{ 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1 },
	//5
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1 },
	//7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1 }
};

int _tmp_iMoveLocY[9][47] = {
	// 0   1   2   3   4   5   6   7   8   9  10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46
	// 0
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//1
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, -1 },
	//3
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//4
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, -1 },
	//5
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//6
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, -1 },
	//7
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 18, 19, 20, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	//8
	{ 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 }
};

char _tmp_cTmpDirX[9] =
{
	0, 0, 1, 1, 1, 0, -1, -1, -1
};

char _tmp_cTmpDirY[9] =
{
	0, -1, -1, 0, 1, 1, 1, 0, -1
};

char _tmp_cEmptyPosX[25] = { 0, 1, 1, 0, -1, -1, -1, 0, 1, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1, 0, 1, 2 };
char _tmp_cEmptyPosY[25] = { 0, 0, 1, 1, 1, 0, -1, -1, -1, -1, 0, 1, 2, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2 };

int ITEMSPREAD_FIEXD_COORD[25][2] =
{
	{ 0, 0 },	//1
	{ 1, 0 },	//2
	{ 1, 1 },	//3
	{ 0, 1 },	//4
	{ -1, 1 },	//5
	{ -1, 0 },	//6
	{ -1, -1 },	//7
	{ 0, -1 },	//8
	{ 1, -1 },	//9
	{ 2, -1 },	//10
	{ 2, 0 },	//11
	{ 2, 1 },	//12
	{ 2, 2 },	//13
	{ 1, 2 },	//14
	{ 0, 2 },	//15
	{ -1, 2 },	//16
	{ -2, 2 },	//17
	{ -2, 1 },	//18
	{ -2, 0 },	//19
	{ -2, -1 },	//20
	{ -2, -2 },	//21
	{ -1, -2 },	//22
	{ 0, -2 },	//23
	{ 1, -2 },	//24
	{ 2, -2 },	//25
};

/*********************************************************************************************************************
**  CGame::CGame(HWND hWnd)																							**
**  DESCRIPTION			:: general variable initializer																**
**  LAST_UPDATED		:: March 13, 2005; 9:27 AM; Hypnotoad														**
**	RETURN_VALUE		:: none																						**
**  NOTES				::	- m_bIsWLServerAvailable is new															**
**							- m_cServerName changed from m_cServerName[11] to m_cServerName[12]						**
**							- set m_sForceRecallTime to 0															**
**							- /// Highlighted 1 /// is incorrect													**
**							- missing <17> variables																**
**							- <6> unidentified variables															**
**	MODIFICATION		::	- Added external variable initialization to:											**
**							m_bEnemyKillMode, m_iEnemyKillAdjust													**
**							m_bAdminSecurity m_sRaidTimeMonday m_sRaidTimeTuesday m_sRaidTimeWednesday				**
**							m_sRaidTimeThursday m_sRaidTimeFriday m_sRaidTimeSaturday m_sRaidTimeSunday				**
**							m_sCharPointLimit m_sSlateSuccessRate													**
**********************************************************************************************************************/
CGame::CGame(HWND hWnd)
{
	int i, x;
	m_bIsGameServerRegistered = FALSE;
	ReceivedAllConfig		= FALSE;
	m_bIsGameStarted = FALSE;
	m_hWnd           = hWnd;
	m_pMainLogSock   = NULL;
	m_pGateSock      = NULL;
	m_bIsLogSockAvailable   = FALSE;
	m_bIsGateSockAvailable  = FALSE;
	m_bIsItemAvailable      = FALSE;
	m_bIsBuildItemAvailable = FALSE;
	m_bIsNpcAvailable       = FALSE;
	m_bIsMagicAvailable     = FALSE;
	m_bIsSkillAvailable     = FALSE;
	m_bIsQuestAvailable     = FALSE;
	m_bIsPotionAvailable    = FALSE;
	m_bIsWLServerAvailable  = FALSE; // new
	ZeroMemory(m_cServerName, sizeof(m_cServerName)); // changed to 12
	m_sForceRecallTime = 0; // new
	for (i = 0; i < DEF_MAXCLIENTS; i++) m_pClientList[i] = NULL;
	for (i = 0; i < DEF_MAXMAPS; i++) m_pMapList[i] = NULL;
	for (i = 0; i < DEF_MAXITEMTYPES; i++) m_pItemConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXNPCTYPES; i++) m_pNpcConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXNPCS; i++) m_pNpcList[i] = NULL;
	for (i = 0; i < DEF_MSGQUENESIZE; i++) m_pMsgQuene[i] = NULL;
	for (i = 0; i < DEF_MAXMAGICTYPE; i++) m_pMagicConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXSKILLTYPE; i++) m_pSkillConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXQUESTTYPE; i++) m_pQuestConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXDYNAMICOBJECTS; i++) m_pDynamicObjectList[i] = NULL;
	for (i = 0; i < DEF_MAXDELAYEVENTS; i++) m_pDelayEventList[i] = NULL;
	for (i = 0; i < DEF_MAXNOTIFYMSGS; i++) m_pNoticeMsgList[i] = NULL;
	for (i = 0; i < DEF_MAXFISHS; i++) m_pFish[i] = NULL;
	for (i = 0; i < DEF_MAXMINERALS; i++) m_pMineral[i] = NULL;
	for (i = 0; i < DEF_MAXPOTIONTYPES; i++) {
		m_pPotionConfigList[i] = NULL;
		m_pCraftingConfigList[i] = NULL;// Crafting
	}
	for (i = 0; i < DEF_MAXSUBLOGSOCK; i++) {
		m_pSubLogSock[i] = NULL;
		m_bIsSubLogSockAvailable[i] = FALSE;

	}
	for (i = 0; i < DEF_MAXBUILDITEMS; i++) m_pBuildItemList[i] = NULL;
	for (i = 0; i < DEF_MAXDUPITEMID; i++) m_pDupItemIDList[i] = NULL;
	//// Highlighted 1 ///
	for (i = 0; i < DEF_MAXCLIENTS; i++) { // asm is 5000, this is 2000 ?
		m_stPartyInfo[i].iTotalMembers = 0;
		for(x = 0; x < DEF_MAXPARTYMEMBERS; x++) 
			m_stPartyInfo[i].iIndex[x] = 0;
	}
	//// End Highlight ///
	m_iQueneHead = 0;
	m_iQueneTail = 0;
	m_iTotalClients = 0;
	m_iMaxClients   = 0;
	m_iTotalMaps    = 0;
	m_iTotalGameServerClients    = 0;
	m_iTotalGameServerMaxClients = 0;
	m_MaxUserSysTime.wHour   = 0;
	m_MaxUserSysTime.wMinute = 0;
	m_bIsServerShutdowned = FALSE;
	m_cShutDownCode = 0;
	m_iMiddlelandMapIndex = -1;
	m_iBTFieldMapIndex = -1;
	m_iGodHMapIndex = -1;
	m_iRampartMapIndex = -1;
	m_iAresdenOccupyTiles = 0;
	m_iElvineOccupyTiles  = 0;
	m_iCurMsgs = 0;
	m_iMaxMsgs = 0;
	m_pNoticementData = 0;
	
	m_iAutoRebootingCount	= 0;
	m_bReceivedItemList = FALSE;
	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////Modifications////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	m_bEnemyKillMode		= FALSE; 
	m_iEnemyKillAdjust      = 1; 
	m_bAdminSecurity = FALSE;
	m_sRaidTimeMonday		= 0; 
	m_sRaidTimeTuesday      = 0; 
	m_sRaidTimeWednesday	= 0; 
	m_sRaidTimeThursday     = 0; 
	m_sRaidTimeFriday		= 0; 
	m_sRaidTimeSaturday     = 0; 
	m_sRaidTimeSunday		= 0;
	m_sCharPointLimit		= 0;
	m_sSlateSuccessRate		= 0;
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	m_dwHeldenianWarTime	= 15*60*1000;  // 15 minutes before effective War start
	m_dwHeldenianEndTime	= 105*60*1000; // 90 minutes effective battle
	m_bNpcItemConfig = FALSE;
	m_iNotifyCleanMap = TRUE;

	m_iExpSetting = 0;

	m_iClearMapTime = 0;
	m_iGoldRate = 0;
	m_iGuildCost = 0;
	m_iDKCost = 0;
}

CGame::~CGame()
{
}

/*********************************************************************************************************************
**  BOOL CGame::bAccept																								**
**  DESCRIPTION			:: function following player connect														**
**  LAST_UPDATED		:: March 13, 2005; 9:34 AM; Hypnotoad														**
**	RETURN_VALUE		:: BOOL																						**
**  NOTES				::	- added (m_bIsWLServerAvailable == FALSE)												**
**							- modified "<%d> New client: %s" to "<%d> Client connected: (%s)"						**
**							- added "Maximum Players: %d" code														**
**  MODIFICATION		::	- added print message if CLOSE_ANYWAY													**
**********************************************************************************************************************/
BOOL CGame::bAccept(class XSocket * pXSock)
{
	int i, x, iTotalip = 0;
	class XSocket * pTmpSock;
	if ((m_bIsGateSockAvailable == FALSE)  || (m_bIsLogSockAvailable == FALSE)   || 
		(m_bIsItemAvailable == FALSE)      || (m_bIsNpcAvailable == FALSE)       || 
		(m_bIsMagicAvailable == FALSE)     || (m_bIsSkillAvailable == FALSE)     || 
		(m_bIsPotionAvailable == FALSE)    || (m_bOnExitProcess == TRUE)         || 
		(m_bIsQuestAvailable == FALSE)     || (m_bIsBuildItemAvailable == FALSE) || 
		(m_bIsGameStarted == FALSE))
		goto CLOSE_ANYWAY;
	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] == NULL) {	
			m_pClientList[i] = new class CClient(m_hWnd);
			bAddClientShortCut(i);
			m_pClientList[i]->m_dwSPTime = m_pClientList[i]->m_dwMPTime = m_pClientList[i]->m_dwHPTime = 
				m_pClientList[i]->m_dwAutoSaveTime = m_pClientList[i]->m_dwTime = m_pClientList[i]->m_dwHungerTime = 
					m_pClientList[i]->m_dwExpStockTime = m_pClientList[i]->m_dwRecentAttackTime = 
						m_pClientList[i]->m_dwAutoExpTime = m_pClientList[i]->m_dwSpeedHackCheckTime = timeGetTime();
			pXSock->bAccept(m_pClientList[i]->m_pXSock, WM_ONCLIENTSOCKETEVENT + i); 
			ZeroMemory(m_pClientList[i]->m_cIPaddress, sizeof(m_pClientList[i]->m_cIPaddress));
			m_pClientList[i]->m_pXSock->iGetPeerAddress(m_pClientList[i]->m_cIPaddress);
#ifdef ANTI_HAX
			//centu: Anti-Downer
			for (x = 1; x < DEF_MAXCLIENTS; x++) 
			if(m_pClientList[x] != NULL) { 
				if(strcmp(m_pClientList[x]->m_cIPaddress, m_pClientList[i]->m_cIPaddress) == 0) iTotalip++; 
			} 
			if(iTotalip > 10) {
				delete m_pClientList[i]; 
				m_pClientList[i] = NULL; 
				return FALSE; 
			} 
			if(strlen(m_pClientList[i]->m_cIPaddress) < 10) { 
				delete m_pClientList[i]; 
				m_pClientList[i] = NULL; 
				return FALSE; 
			}
#endif
			wsprintf(G_cTxt,"<%d> Client connected: (%s)", i, m_pClientList[i]->m_cIPaddress);
			PutLogList(G_cTxt);
			m_iTotalClients++;
			if (m_iTotalClients > m_iMaxClients) { 
				m_iMaxClients = m_iTotalClients;
				
			}
			return TRUE;
		}
CLOSE_ANYWAY:;
	/****MODIFICATION****/
	PutLogList("(!) bAccept->CLOSE_ANYWAY");
	/********END*********/
	pTmpSock = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
	pXSock->bAccept(pTmpSock, NULL); 
	delete pTmpSock;
	return FALSE;
}

/*********************************************************************************************************************
**  void CGame::OnClientSocketEvent																					**
**  DESCRIPTION			:: socket connection manager																**
**  LAST_UPDATED		:: March 13, 2005; 9:58 AM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- removed DEF_XSOCKEVENT_BLOCK															**
**							- modified DeleteClient																	**
**	MODIFICATION		::	- Added Logout Hack Check code															**
**********************************************************************************************************************/
void CGame::OnClientSocketEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
 UINT iTmp;
 int iClientH, iRet;
 DWORD dwTime = timeGetTime();

	iTmp = WM_ONCLIENTSOCKETEVENT;
	iClientH = (int)(message - iTmp);
// SNOOPY: Trying to trap 004030B6 error
// 004030D0  |> 8B4D F4        MOV ECX,DWORD PTR SS:[EBP-C]
// 004030D3  |. 8B55 FC        MOV EDX,DWORD PTR SS:[EBP-4]
// 004030D6  |. 837C8A 7C 00   CMP DWORD PTR DS:[EDX+ECX*4+7C],0
// 004030DB  |. 75 05          JNZ SHORT HGserver.004030E2
// 004030DD  |. E9 AB020000    JMP HGserver.0040338D
// 004030E2  |> 8B45 10        MOV EAX,DWORD PTR SS:[EBP+10]
	if (iClientH <= 0) return;	

	if (m_pClientList[iClientH] == NULL) return;
	iRet = m_pClientList[iClientH]->m_pXSock->iOnSocketEvent(wParam, lParam);
	switch (iRet) {
	case DEF_XSOCKEVENT_READCOMPLETE:
		OnClientRead(iClientH);
		m_pClientList[iClientH]->m_dwTime = timeGetTime();
		break;
	
	case DEF_XSOCKEVENT_CONFIRMCODENOTMATCH:
		wsprintf(G_cTxt,"<%d> Confirmcode notmatch!", iClientH);
		PutLogList(G_cTxt);
		DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE);
		break;
	case DEF_XSOCKEVENT_MSGSIZETOOLARGE:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		wsprintf(G_cTxt,"<%d> Client connection Lost! (%s)", iClientH, m_pClientList[iClientH]->m_cIPaddress);
		PutLogList(G_cTxt); 
		/****MODIFICATION****/
		if ((dwTime - m_pClientList[iClientH]->m_dwLogoutHackCheck) < 10000) { // 1000 -> 10000
			wsprintf(G_cTxt, "Logout Hack: (%s) Player: (%s) - disconnected within 10 seconds of most recent damage. Hack? Lag?", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
		}
		/********END*********/
		DeleteClient(iClientH, TRUE, TRUE, TRUE, FALSE);
		break;
	}													    
}

/*********************************************************************************************************************
**  BOOL CGame::bInit()		   																						**
**  DESCRIPTION			:: general variable initializer																**
**  LAST_UPDATED		:: March 13, 2005; 8:00 PM; Hypnotoad														**
**	RETURN_VALUE		:: BOOL																						**
**  NOTES				::	- Added Nulliy to "m_pTeleportDestination[i]"											**
**							- reduced MaxLevel from 3500 to 300														**
**							- changed DEF_MAXGATESERVERSTOCKMSGSIZE from 10000 to 30000								**
**							- added m_bIsApocalypseStarter, m_bIsApocalypseGateOpen, m_cApocalypseMapName,			**
**							  m_bHeldinianDuty, m_bF10pressed, m_cHeldenianMapName, m_bIsHeldenianReady				**
**							- missing <13> variables																**
**							- <6> variables unidentified															**
**	MODIFICATION		::	- Added read to Settings.cfg, AdminList.cfg, BannedList.cfg, AdminSettings.cfg			**
**							- Added Admin and Banned List initialization											**
**							- Added initialization to Apocalypse end/start and Heldenian Timer						**
**********************************************************************************************************************/
BOOL CGame::bInit()		   
{
 char * cp, cTxt[120];
 DWORD * dwp;
 WORD * wp;
 int  i;
 SYSTEMTIME SysTime;
 DWORD dwTime = timeGetTime();

	PutLogList("(!) INITIALIZING GAME SERVER...");
	for (i = 0; i < DEF_MAXCLIENTS+1; i++) 
		m_iClientShortCut[i] = 0;
	if (m_pMainLogSock != NULL) delete m_pMainLogSock;
	if (m_pGateSock != NULL) delete m_pGateSock;
	for (i = 0; i < DEF_MAXSUBLOGSOCK; i++)
		if (m_pSubLogSock[i] != NULL) delete m_pSubLogSock[i];
	for (i = 0; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) delete m_pClientList[i];
	for (i = 0; i < DEF_MAXNPCS; i++)
		if (m_pNpcList[i] != NULL) delete m_pNpcList[i];
	for (i = 0; i < DEF_MAXMAPS; i++)
		if (m_pMapList[i] != NULL) delete m_pMapList[i];
	for (i = 0; i < DEF_MAXITEMTYPES; i++)
		if (m_pItemConfigList[i] != NULL) delete m_pItemConfigList[i];
	for (i = 0; i < DEF_MAXNPCTYPES; i++)
		if (m_pNpcConfigList[i] != NULL) delete m_pNpcConfigList[i];
	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		if (m_pMagicConfigList[i] != NULL) delete m_pMagicConfigList[i];
	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		if (m_pSkillConfigList[i] != NULL) delete m_pSkillConfigList[i];
	for (i = 0; i < DEF_MAXQUESTTYPE; i++)
		if (m_pQuestConfigList[i] != NULL) delete m_pQuestConfigList[i];
	for (i = 0; i < DEF_MAXDYNAMICOBJECTS; i++)
		if (m_pDynamicObjectList[i] != NULL) delete m_pDynamicObjectList[i];
	for (i = 0; i < DEF_MAXDELAYEVENTS; i++)
		if (m_pDelayEventList[i] != NULL) delete m_pDelayEventList[i];
	for (i = 0; i < DEF_MAXNOTIFYMSGS; i++)
		if (m_pNoticeMsgList[i] != NULL) delete m_pNoticeMsgList[i];
	for (i = 0; i < DEF_MAXFISHS; i++)
		if (m_pFish[i] != NULL) delete m_pFish[i];
	for (i = 0; i < DEF_MAXMINERALS; i++)
		if (m_pMineral[i] != NULL) delete m_pMineral[i];
	for (i = 0; i < DEF_MAXPOTIONTYPES; i++) {
		if (m_pPotionConfigList[i] != NULL) delete m_pPotionConfigList[i];
		if (m_pCraftingConfigList[i] != NULL) delete m_pCraftingConfigList[i];	// Crafting
	}
	for (i = 0; i < DEF_MAXBUILDITEMS; i++) 
		if (m_pBuildItemList[i] != NULL) delete m_pBuildItemList[i];

	for (i = 0; i < DEF_MAXNPCTYPES; i++)
		m_iNpcConstructionPoint[i] = NULL;
	for (i = 0; i < DEF_MAXSCHEDULE; i++) {
		m_stCrusadeWarSchedule[i].iDay = -1;
		m_stCrusadeWarSchedule[i].iHour = -1;
		m_stCrusadeWarSchedule[i].iMinute = -1;
	}	
	m_iNpcConstructionPoint[1]  = 100; // MS
	m_iNpcConstructionPoint[2]  = 100; // MS
	m_iNpcConstructionPoint[3]  = 100; // MS
	m_iNpcConstructionPoint[4]  = 100; // MS
	m_iNpcConstructionPoint[5]  = 100; // MS
	m_iNpcConstructionPoint[6]  = 100; // MS
	m_iNpcConstructionPoint[43] = 1000; // LWB
	m_iNpcConstructionPoint[44] = 2000; // GHK
	m_iNpcConstructionPoint[45] = 3000; // GHKABS
	m_iNpcConstructionPoint[46] = 2000; // TK
	m_iNpcConstructionPoint[47] = 3000; // BG
	m_iNpcConstructionPoint[51] = 1500; // Catapult
	m_bIsGameStarted = FALSE;
	m_pMainLogSock = NULL;
	m_pGateSock = NULL;
	m_bIsLogSockAvailable   = FALSE;
	m_bIsGateSockAvailable  = FALSE;
	m_bIsItemAvailable      = FALSE;
	m_bIsBuildItemAvailable = FALSE;
	m_bIsNpcAvailable       = FALSE;
	m_bIsMagicAvailable     = FALSE;
	m_bIsSkillAvailable     = FALSE;
	m_bIsQuestAvailable     = FALSE;
	m_bIsPotionAvailable    = FALSE;
	m_bIsWLServerAvailable  = FALSE;
	for (i = 0; i < DEF_MAXCLIENTS; i++)
		m_pClientList[i] = NULL;
	for (i = 0; i < DEF_MAXMAPS; i++)
		m_pMapList[i] = NULL;
	for (i = 0; i < DEF_MAXITEMTYPES; i++)
		m_pItemConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXNPCTYPES; i++)
		m_pNpcConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXNPCS; i++)
		m_pNpcList[i] = NULL;
	for (i = 0; i < DEF_MSGQUENESIZE; i++)
		m_pMsgQuene[i] = NULL;
	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		m_pMagicConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		m_pSkillConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXQUESTTYPE; i++)
		m_pQuestConfigList[i] = NULL;
	for (i = 0; i < DEF_MAXDYNAMICOBJECTS; i++)
		m_pDynamicObjectList[i] = NULL;
	for (i = 0; i < DEF_MAXDELAYEVENTS; i++)
		m_pDelayEventList[i] = NULL;
	for (i = 0; i < DEF_MAXNOTIFYMSGS; i++)
		m_pNoticeMsgList[i] = NULL;
	for (i = 0; i < DEF_MAXFISHS; i++)
		m_pFish[i] = NULL;
	for (i = 0; i < DEF_MAXMINERALS; i++)
		m_pMineral[i] = NULL;
	for (i = 0; i < DEF_MAXPOTIONTYPES; i++) {
		m_pPotionConfigList[i] = NULL;
		m_pCraftingConfigList[i] = NULL;	// Crafting
	}
	for (i = 0; i < DEF_MAXSUBLOGSOCK; i++) {
		m_pSubLogSock[i] = NULL;
		m_bIsSubLogSockAvailable[i] = FALSE;
	}
	for (i = 0; i < DEF_MAXBUILDITEMS; i++) 
		m_pBuildItemList[i] = NULL;
	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
		ZeroMemory(m_stCrusadeStructures[i].cMapName, sizeof(m_stCrusadeStructures[i].cMapName));
		m_stCrusadeStructures[i].cType = NULL;
		m_stCrusadeStructures[i].dX    = NULL;
		m_stCrusadeStructures[i].dY    = NULL;
	}
	// new
	for (i = 0; i < DEF_MAXTELEPORTDESTINATION; i++)
		m_pTeleportDestination[i] = NULL;
	for (i = 0; i < DEF_MAXGUILDS; i++)
		m_pGuildTeleportLoc[i].m_iV1 = NULL;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
		m_stMiddleCrusadeStructureInfo[i].cType = NULL;
		m_stMiddleCrusadeStructureInfo[i].cSide = NULL;
		m_stMiddleCrusadeStructureInfo[i].sX = NULL;
		m_stMiddleCrusadeStructureInfo[i].sY = NULL;
	}
	m_iTotalMiddleCrusadeStructures = 0;
	m_pNoticementData = NULL;
	m_iQueneHead = 0;
	m_iQueneTail = 0;
	m_iTotalClients = 0;
	m_iMaxClients   = 0;
	m_iTotalMaps    = 0;
	m_iTotalGameServerClients    = 0;
	m_iTotalGameServerMaxClients = 0;
	m_MaxUserSysTime.wHour   = 0;
	m_MaxUserSysTime.wMinute = 0;
	m_bIsServerShutdowned = FALSE;
	m_cShutDownCode = 0;
	m_iMiddlelandMapIndex = -1;
	m_iAresdenMapIndex    = -1;
	m_iElvineMapIndex     = -1;
	m_iAresdenOccupyTiles = 0;
	m_iElvineOccupyTiles  = 0;
	m_iSubLogSockInitIndex   = 0;
	m_iCurMsgs = 0;
	m_iMaxMsgs = 0;
	///////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////Modifications////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < DEF_MAXAPOCALYPSE; i++) {
		m_stApocalypseScheduleStart[i].iDay = -1;
		m_stApocalypseScheduleStart[i].iHour = -1;
		m_stApocalypseScheduleStart[i].iMinute = -1;
	}
	for (i = 0; i < DEF_MAXHELDENIAN; i++) {
		m_stHeldenianSchedule[i].iDay = -1;
		m_stHeldenianSchedule[i].StartiHour = -1;
		m_stHeldenianSchedule[i].StartiMinute = -1;
	}

	
	for (i = 0; i < DEF_MAXADMINS; i++) {
		ZeroMemory(m_stAdminList[i].m_cGMName, sizeof(m_stAdminList[i].m_cGMName));
	}

	for (i = 0; i < DEF_MAXBANNED; i++) {
		ZeroMemory(m_stBannedList[i].m_cBannedIPaddress, sizeof(m_stBannedList[i].m_cBannedIPaddress));
	}
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	
	m_iStrategicStatus = 0;
	m_iCollectedMana[0] = 0;
	m_iCollectedMana[1] = 0;
	m_iCollectedMana[2] = 0;
	m_iAresdenMana = 0;
	m_iElvineMana  = 0;
	m_dwSpecialEventTime = m_dwWhetherTime = m_dwGameTime1 = m_dwGameTime2 = m_dwGameTime3 = 
		m_dwGameTime4 = m_dwGameTime5 = m_dwGameTime6 = m_dwFishTime = dwTime;
	m_bIsSpecialEventTime = FALSE;
	GetLocalTime(&SysTime);
	m_dwCanFightzoneReserveTime = dwTime - ((SysTime.wHour%2)*60*60 + SysTime.wMinute*60)*1000;
	for(i =0; i < DEF_MAXFIGHTZONE; i++) 
		m_iFightZoneReserve[i] = 0 ;
	m_iFightzoneNoForceRecall = 0;
	for (i = 1; i < DEF_MAXEXPTABLE; i++) { //centu - lvl jump fixed
		m_iLevelExpTable[i] = iGetLevelExp(i);
	}
	
	m_iLevelExp20     = m_iLevelExpTable[DEF_LEVELLIMIT];
	m_iGameServerMode = 0;
	if (bReadProgramConfigFile("GServer.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! GServer.cfg file contents error!");
		return FALSE;	
	}
	if (bReadProgramConfigFile2("..\\GameConfigs\\Server.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! Server.cfg file contents error!");
		return FALSE;
	}
	/****MODIFICATION****/
	if (bReadSettingsConfigFile("..\\GameConfigs\\Settings.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! Settings.cfg file contents error!");
		return FALSE;
	}
	if (bReadAdminListConfigFile("..\\GameConfigs\\AdminList.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! AdminList.cfg file contents error!");
		return FALSE;
	}
	if (bReadBannedListConfigFile("..\\GameConfigs\\BannedList.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! BannedList.cfg file contents error!");
		return FALSE;
	}
	if (bReadAdminSetConfigFile("..\\GameConfigs\\AdminSettings.cfg") == FALSE) {
		PutLogList(" ");
		PutLogList("(!!!) CRITICAL ERROR! Cannot execute server! AdminSettings.cfg file contents error!");
		return FALSE;
	}
	/********END*********/
	srand((unsigned)time(NULL));   
	m_pMainLogSock = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
	m_pMainLogSock->bConnect(m_cLogServerAddr, m_iLogServerPort, WM_ONLOGSOCKETEVENT);
	m_pMainLogSock->bInitBufferSize(DEF_MSGBUFFERSIZE);
	wsprintf(cTxt, "(!) Try to Connect main-log-socket... Addr:%s  Port:%d", m_cLogServerAddr, m_iLogServerPort);
	PutLogList(cTxt);
	m_pGateSock = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
	m_pGateSock->bConnect(m_cGateServerAddr, m_iGateServerPort, WM_ONGATESOCKETEVENT);
	m_pGateSock->bInitBufferSize(DEF_MSGBUFFERSIZE);
	m_iGateSockConnRetryTimes = 1;
	wsprintf(cTxt, "(!) Try to Connect Gate Server... Addr:%s  Port:%d", m_cGateServerAddr, m_iGateServerPort);
	PutLogList(cTxt);
	// modification - m_bF5pressed
	m_bF1pressed = m_bF4pressed = m_bF12pressed = m_bF5pressed = FALSE; 
	m_bOnExitProcess = FALSE;
	for (i = 0; i <= 100; i++) {
		m_iSkillSSNpoint[i] = _iCalcSkillSSNpoint(i);
	}
	GetLocalTime(&SysTime);
	// centu - day/night time
	if (SysTime.wHour >= 19 || SysTime.wHour <= 6)  
		 m_cDayOrNight = 2;
	else m_cDayOrNight = 1;

	bReadNotifyMsgListFile("..\\GameConfigs\\notice.txt");
	m_dwNoticeTime = dwTime;
	m_iCurSubLogSockIndex    = 0;
	m_iSubLogSockFailCount   = 0;
	m_iSubLogSockActiveCount = 0;
	m_pNoticementData      = NULL;
	m_dwNoticementDataSize = 0;
	m_dwMapSectorInfoTime = dwTime;
	m_iMapSectorInfoUpdateCount = 0;
	m_iCrusadeCount  = NULL;
	m_bIsCrusadeMode = FALSE;
	m_wServerID_GSS = iDice(1,65535);
	// changed DEF_MAXGATESERVERSTOCKMSGSIZE from 10000 to 30000
	ZeroMemory(m_cGateServerStockMsg, sizeof(m_cGateServerStockMsg));
	cp = (char *)m_cGateServerStockMsg;
	dwp = (DWORD *)cp;
	*dwp = MSGID_SERVERSTOCKMSG;
	cp += 4;
	wp = (WORD *)cp;
	*wp = DEF_MSGTYPE_CONFIRM;
	cp += 2;
	m_iIndexGSS = 6;
	m_dwCrusadeGUID   = NULL;
	m_iCrusadeWinnerSide = NULL;
	m_iLastCrusadeWinner = 0;
	// <MISSING_VARIABLE_HERE> 107704h - unknown variable and unreferenced!
	m_bIsCrusadeWarStarter = FALSE;
	m_iLatestCrusadeDayOfWeek = -1;
	m_iFinalShutdownCount = 0;
	m_bIsApocalypseMode = FALSE;
	m_bIsApocalypseStarter = FALSE; // new
	m_bIsApocalypseGateOpen = FALSE; // new
	ZeroMemory(m_cApocalypseMapName, sizeof(m_cApocalypseMapName)); // new
	bDeathmatch = FALSE;
	iLastKill = -1;
	iTotalKills = 0;
	dwTimeLastKill = dwTime;
	iDGtop1=iDGtop2=iDGtop3=iDGtop4=iDGtop5=iDGtop6=iDGtop7=iDGtop8=iDGtop9=iDGtop10=0;
	// 	Heldenian
	m_bIsHeldenianMode			 = FALSE;
	m_bHeldenianWarInitiated	 = FALSE;
	m_cHeldenianType			 = 0;
	m_sLastHeldenianWinner		 = 0; 
	m_cHeldenianWinner			 = -1;
	m_dwHeldenianGUID			 = NULL;
	m_dwHeldenianWarStartTime	 = 0;
	m_dwHeldenianFinishTime		 = 0;
	m_cHeldenianFirstDestroyedTowerWinner = -1;
	m_iHeldenianAresdenDead		 = 0;
	m_iHeldenianElvineDead		 = 0;
	m_iHeldenianAresdenFlags	 = 0;
	m_iHeldenianElvineFlags		 = 0;
	m_iHeldenianAresdenLeftTower = 0;
	m_iHeldenianElvineLeftTower  = 0;
	ZeroMemory(m_cHeldenianMapName, sizeof(m_cHeldenianMapName)); // new
	m_bF10pressed = FALSE; // new

	m_dwCleanTime = dwTime;

	//50Cent - Capture The Flag
	m_sFlagCountWin = 0;
	m_bIsCTFMode = false;
	m_bIsElvineFlagCaptured = false;
	m_bIsAresdenFlagCaptured = false;
	m_iFlagCarrierIndex = -1;

	return TRUE;
}

/*********************************************************************************************************************
**  void CGame::OnClientRead																						**
**  DESCRIPTION			:: reports error message if client data invalid												**
**  LAST_UPDATED		:: March 13, 2005; 8:25 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				:: none																						**
**	MODIFICATION		:: none																						**
**********************************************************************************************************************/
void CGame::OnClientRead(int iClientH)
{
 char  * pData, cKey;
 DWORD  dwMsgSize;
	
	if (m_pClientList[iClientH] == NULL) return;
	pData = m_pClientList[iClientH]->m_pXSock->pGetRcvDataPointer(&dwMsgSize, &cKey);
	if (bPutMsgQuene(DEF_MSGFROM_CLIENT, pData, dwMsgSize, iClientH, cKey) == FALSE) {
		PutLogList("@@@@@@ CRITICAL ERROR in MsgQuene!!! (OnClientRead) @@@@@@");
	}
}

/*********************************************************************************************************************
**  void CGame::DisplayInfo																							**
**  DESCRIPTION			:: prints header																			**
**  LAST_UPDATED		:: March 13, 2005; 9:06 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				:: none																						**
**	MODIFICATION		:: links to GayDave to print personalized message											**
**********************************************************************************************************************/
void CGame::DisplayInfo(HDC hdc)
{
 char cTxt[350];  
 int  i, iLine;

    TextOut(hdc, 650, 4, "[Server Config]", 15);
    wsprintf(cTxt, "Server Name: %s", m_cServerName);
    TextOut(hdc, 605, 40, cTxt, strlen(cTxt));
    wsprintf(cTxt, "Max Level: %d", m_iPlayerMaxLevel);
    TextOut(hdc, 605, 55, cTxt, strlen(cTxt));
    wsprintf(cTxt, "Max Stats: %d", m_sCharStatLimit-11);
    TextOut(hdc, 605, 70, cTxt, strlen(cTxt));
    wsprintf(cTxt, "Players Online: %d/%d", m_iTotalClients, m_iMaxClients);
    TextOut(hdc, 605, 85, cTxt, strlen(cTxt));
    ZeroMemory(cTxt, sizeof(cTxt));
    TextOut(hdc, 602, 220, "   ", 3);
    TextOut(hdc, 605, 130, "__________________________", 26);
    TextOut(hdc, 605, 160, "[MAPS]                  [MOBS]", 30);

    iLine = 0;
    for (i = 0; i < DEF_MAXMAPS; i++)
    if (m_pMapList[i] != NULL) {
        ZeroMemory(G_cTxt, sizeof(G_cTxt));
        wsprintf(G_cTxt, m_pMapList[i]->m_cName);
        TextOut(hdc, 605, 175 + iLine*14, G_cTxt, strlen(G_cTxt));
        wsprintf(G_cTxt, "%d",m_pMapList[i]->m_iTotalActiveObject);
        TextOut(hdc, 740, 175 + iLine*14, G_cTxt, strlen(G_cTxt));
        iLine++;
    }
 
}

/*********************************************************************************************************************
**  void CGame::ClientMotionHandler																					**
**  DESCRIPTION			:: controls most client actions																**
**  LAST_UPDATED		:: March 13, 2005; 10:19 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				:: - in DEF_OBJECTATTACKMOVE iRet 1's iClientMotion_Attack_Handler bResponse set to TRUE	**
**	MODIFICATION		:: - added checks and logging to 2 variants of magic hacks (instant packet, speed)			**
**********************************************************************************************************************/
void CGame::ClientMotionHandler(int iClientH, char * pData)
{
 DWORD * dwp, dwClientTime;
 WORD * wp, wCommand, wTargetObjectID;
 short * sp, sX, sY, dX, dY, wType;
 char  * cp, cDir;
 int   iRet, iTemp;
	
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;
	
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wCommand = *wp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;

	cDir = *cp;
	cp++;

	sp = (short *)cp;
	dX = *sp;
	cp += 2;

	sp = (short *)cp;
	dY = *sp;
	cp += 2;

	sp = (short *)cp;
	wType = *sp;
	cp += 2;

	if ((wCommand == DEF_OBJECTATTACK) || (wCommand == DEF_OBJECTATTACKMOVE)) {
		wp = (WORD *)cp;
		wTargetObjectID = *wp;
		cp += 2;
	}
	dwp = (DWORD *)cp;
	dwClientTime = *dwp;
	cp += 4;

#ifdef ANTI_HAX
	CheckDenialServiceAttack(iClientH, dwClientTime);
#endif

	m_pClientList[iClientH]->m_dwLastActionTime = m_pClientList[iClientH]->m_dwAFKCheckTime = timeGetTime();

	switch (wCommand) {
	case DEF_OBJECTSTOP:
		iRet = iClientMotion_Stop_Handler(iClientH, sX, sY, cDir);
		if (iRet == 1) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTSTOP, NULL, NULL, NULL);
		}
		else if (iRet == 2) {
			SendObjectMotionRejectMsg(iClientH);
		}
		break;

	case DEF_OBJECTRUN:
		iRet = iClientMotion_Move_Handler(iClientH, sX, sY, cDir, 1);
		if (iRet == 1) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTRUN, NULL, NULL, NULL);
		}
		if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_iHP <= 0)) {
			ClientKilledHandler(iClientH, NULL, NULL, 1);
		}
		bCheckClientMoveFrequency(iClientH, dwClientTime);
		break;

	case DEF_OBJECTMOVE:
		iRet = iClientMotion_Move_Handler(iClientH, sX, sY, cDir, 2);
		if (iRet == 1) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
		}
		if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_iHP <= 0)) {
			ClientKilledHandler(iClientH, NULL, NULL, 1);
		}
		bCheckClientMoveFrequency(iClientH, dwClientTime);
		break;

	case DEF_OBJECTDAMAGEMOVE:
		iRet = iClientMotion_Move_Handler(iClientH, sX, sY, cDir, 0);
		if (iRet == 1) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGEMOVE, m_pClientList[iClientH]->m_iLastDamage, NULL, NULL);
		}
		if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_iHP <= 0)) {
			ClientKilledHandler(iClientH, NULL, NULL, 1);
		}
		break;

	case DEF_OBJECTATTACKMOVE:
		iRet = iClientMotion_Move_Handler(iClientH, sX, sY, cDir, 0);
		if ((iRet == 1) && (m_pClientList[iClientH] != NULL)) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTATTACKMOVE, NULL, NULL, NULL);
			// changed bResponse to TRUE
			iClientMotion_Attack_Handler(iClientH, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, dX, dY, wType, cDir, wTargetObjectID, FALSE, TRUE);
		}
		if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_iHP <= 0)) {
			ClientKilledHandler(iClientH, NULL, NULL, 1);
		}
		bCheckClientAttackFrequency(iClientH, dwClientTime);
		break;

	case DEF_OBJECTATTACK:
		_CheckAttackType(iClientH, &wType);
		iRet = iClientMotion_Attack_Handler(iClientH, sX, sY, dX, dY, wType, cDir, wTargetObjectID, TRUE, FALSE);
		if (iRet == 1) {
			if (wType >= 20) {
				m_pClientList[iClientH]->m_iSuperAttackLeft--;
				if (m_pClientList[iClientH]->m_iSuperAttackLeft < 0) m_pClientList[iClientH]->m_iSuperAttackLeft = 0;
			}
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, wType);
		}
		else if (iRet == 2) {
			SendObjectMotionRejectMsg(iClientH);
		}
		bCheckClientAttackFrequency(iClientH, dwClientTime);
		break;

	case DEF_OBJECTGETITEM:
		iRet = iClientMotion_GetItem_Handler(iClientH, sX, sY, cDir);
		if (iRet == 1) {
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTGETITEM, NULL, NULL, NULL);
		}
		else if (iRet == 2) {
			SendObjectMotionRejectMsg(iClientH);
		}
		break;

	case DEF_OBJECTMAGIC:
		iRet = iClientMotion_Magic_Handler(iClientH, sX, sY, cDir);
		if (iRet == 1) {
			/****MODIFICATION****/
			if (m_pClientList[iClientH]->m_bMagicPauseTime == FALSE) {
				m_pClientList[iClientH]->m_bMagicPauseTime = TRUE;
				iTemp = 10;
				SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTMAGIC, dX, iTemp, NULL);
				m_pClientList[iClientH]->m_iSpellCount++;
				bCheckClientMagicFrequency(iClientH, dwClientTime);
			}
			else {
				wsprintf(G_cTxt, "(!) Cast Delay Hack: (%s) Player: (%s) - player casting too fast.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
				PutHackLogFileList(G_cTxt);
				DeleteClient(iClientH, TRUE, TRUE);
			}
			/********END*********/
		}
		else if (iRet == 2) {
			SendObjectMotionRejectMsg(iClientH);
		}
		break;

	default:
		break;
	}
}

/*********************************************************************************************************************
**  int CGame::iClientMotion_Move_Handler(int iClientH, short sX, short sY, char cDir, char cMoveType)				**
**  DESCRIPTION			:: Handles how player or npc run, walk, attack, or get flown by attack						**
**  LAST_UPDATED		:: March 14, 2005; 11:34 AM; Hypnotoad														**
**	RETURN_VALUE		:: int																						**
**  NOTES				::	- added speed hack detection															**
**							- cMoveType changed from bRun															**
**							- added apocalypse gate teleporter														**
**							- added motion isBlocked (1050)															**
**	MODIFICATION		:: none																						**
**********************************************************************************************************************/
int CGame::iClientMotion_Move_Handler(int iClientH, short sX, short sY, char cDir, char cMoveType)
{
 char  * cp, cData[3000];
 class CTile * pTile;
 DWORD * dwp, dwTime;
 WORD  * wp, wObjectID;
 short * sp, dX, dY, sDOtype, pTopItem, wV1, wV2;
 int   * ip, iRet, iSize, iDamage, iTemp, iTemp2;
 BOOL  bRet, bIsBlocked = FALSE;
 char cTemp[11];

	if (m_pClientList[iClientH] == NULL) return 0;
	if ((cDir <= 0) || (cDir > 8))       return 0;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return 0;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return 0;
	if ((sX != m_pClientList[iClientH]->m_sX) && (sY != m_pClientList[iClientH]->m_sY)) return 2;

	
	dwTime = timeGetTime();
	m_pClientList[iClientH]->m_dwLastActionTime = dwTime;
	
	// new - speed hack detection
	if (cMoveType == 2) {
		if (m_pClientList[iClientH]->m_iRecentWalkTime <= dwTime - 16) {
			m_pClientList[iClientH]->m_iRecentWalkTime = dwTime;
		}
		else if ((m_pClientList[iClientH]->m_sV1 >= 1) && (dwTime < m_pClientList[iClientH]->m_iRecentWalkTime)) {
			bIsBlocked = TRUE;
			m_pClientList[iClientH]->m_sV1 = 0;	
		}
		else {
			m_pClientList[iClientH]->m_sV1++;	
		}
		m_pClientList[iClientH]->m_iRecentWalkTime = dwTime;
		if (bIsBlocked == FALSE) m_pClientList[iClientH]->m_iMoveMsgRecvCount++;
		if ((m_pClientList[iClientH]->m_iMoveMsgRecvCount >= 3) && (m_pClientList[iClientH]->m_dwMoveLAT != 0)) {
			if ((m_pClientList[iClientH]->m_dwMoveLAT - dwTime) < 20) {
				wsprintf(G_cTxt, "(!) 3.51 Walk Speeder: (%s) Player: (%s) walk difference: %d. Speed Hack?", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, (dwTime - m_pClientList[iClientH]->m_dwMoveLAT));
				PutHackLogFileList(G_cTxt);
				bIsBlocked = TRUE;
			}
		}
		m_pClientList[iClientH]->m_dwMoveLAT = dwTime;
		m_pClientList[iClientH]->m_iMoveMsgRecvCount = 0;
	}
	else if (cMoveType == 1) {
		if (m_pClientList[iClientH]->m_iRecentRunTime <= dwTime - 8) {
			m_pClientList[iClientH]->m_iRecentRunTime = dwTime;
		}
		else if ((m_pClientList[iClientH]->m_sV1 >= 1) && (dwTime < m_pClientList[iClientH]->m_iRecentRunTime)) {
			bIsBlocked = TRUE;
			m_pClientList[iClientH]->m_sV1 = 0;
		}
		else {
			m_pClientList[iClientH]->m_sV1++;
		}
		m_pClientList[iClientH]->m_iRecentRunTime = dwTime;
		if (bIsBlocked == FALSE) m_pClientList[iClientH]->m_iRunMsgRecvCount++;
		if ((m_pClientList[iClientH]->m_iRunMsgRecvCount >= 3) && (m_pClientList[iClientH]->m_dwRunLAT != 0)) {
			if ((dwTime - m_pClientList[iClientH]->m_dwRunLAT) < 12) {
				wsprintf(G_cTxt, "(!) 3.51 Run Speeder: (%s) Player: (%s) run difference: %d. Speed Hack?", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, (dwTime - m_pClientList[iClientH]->m_dwRunLAT));
				PutHackLogFileList(G_cTxt);
				bIsBlocked = TRUE;
			}
		}
		m_pClientList[iClientH]->m_dwRunLAT	= dwTime;
		m_pClientList[iClientH]->m_iRunMsgRecvCount = 0;
	}
	else if (cMoveType > 3) cMoveType -= 4; // Move type 4+ indicates move generated by server, not client !
	// end speed hack detection

	
	
	ClearSkillUsingStatus(iClientH);	
	dX = m_pClientList[iClientH]->m_sX;
	dY = m_pClientList[iClientH]->m_sY;
	switch (cDir) {
		case 1:	dY--; break;
		case 2:	dX++; dY--;	break;
		case 3:	dX++; break;
		case 4:	dX++; dY++;	break;
		case 5: dY++; break;
		case 6:	dX--; dY++;	break;
		case 7:	dX--; break;
		case 8:	dX--; dY--;	break;
	}
	pTopItem = 0;
	bRet = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bGetMoveable(dX, dY, &sDOtype, &pTopItem);
	if (m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) bRet = FALSE;
	if ((bRet == TRUE) && (bIsBlocked == FALSE)) {
		if (m_pClientList[iClientH]->m_iQuest != NULL) _bCheckIsQuestCompleted(iClientH);
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(1, iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
		m_pClientList[iClientH]->m_sX   = dX;
		m_pClientList[iClientH]->m_sY   = dY;
		m_pClientList[iClientH]->m_cDir = cDir;
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, dX, dY);
		if (sDOtype == DEF_DYNAMICOBJECT_SPIKE) {
			
			if ((m_pClientList[iClientH]->m_sAppr2 & 0xF000) != 0) {
				iDamage = iDice(2,4);
				if (m_pClientList[iClientH]->m_iAdminUserLevel == 0)
					m_pClientList[iClientH]->m_iHP -= iDamage;
			}
		}
		if (m_pClientList[iClientH]->m_iHP <= 0) m_pClientList[iClientH]->m_iHP = 0;
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_RESPONSE_MOTION;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_OBJECTMOVE_CONFIRM;
		
		cp = (char *)(cData + DEF_INDEX2_MSGTYPE+2);
		
		sp  = (short *)cp;
		*sp = (short)(dX - 13); 
		cp += 2;
		
		sp  = (short *)cp;
		*sp = (short)(dY - 10); 
		cp += 2;
		
		*cp = cDir;
		cp++;
		if (cMoveType == 1) {
			if (m_pClientList[iClientH]->m_iSP > 0) {
				*cp = 0;
				if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
					m_pClientList[iClientH]->m_iSP--;
					*cp = 1;
				}
			}
			else {
				*cp = 0;
				if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
					m_pClientList[iClientH]->m_iSP--;
					*cp = 1;
				}
				if (m_pClientList[iClientH]->m_iSP < -10) {
					m_pClientList[iClientH]->m_iSP = 0;
					DeleteClient(iClientH, TRUE, TRUE);
					return 0;
				}
			}
		}
		else *cp = 0;
		cp++;

		pTile = (class CTile *)(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_pTile + dX + dY*m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY);
		*cp = (char)pTile->m_iOccupyStatus;
		cp++;
		
		ip = (int *)cp;
		*ip = m_pClientList[iClientH]->m_iHP;
		cp += 4;
		
		iSize = iComposeMoveMapData((short)(dX - 13), (short)(dY - 10), iClientH, cDir, cp);	
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, iSize + 12 + 1 + 4);
		switch (iRet) {
		case DEF_XSOCKEVENT_QUENEFULL:
		case DEF_XSOCKEVENT_SOCKETERROR:
		case DEF_XSOCKEVENT_CRITICALERROR:
		case DEF_XSOCKEVENT_SOCKETCLOSED:
			DeleteClient(iClientH, TRUE, TRUE, TRUE, FALSE);
			return 0;
		}
		// new - apocalypse gate teleport
		if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsGateAvailable == TRUE) {	
			bRet = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bApocalypseGateTeleporter(dX, dY, &*cTemp, &wV1, &wV2);
			if (bRet) {
				RequestTeleportHandler(iClientH, "2   ", cTemp, wV1, wV2);
			}
		}
		// end - apocalypse gate teleport
	}
	else {
		// new motion
		m_pClientList[iClientH]->m_bIsMoveBlocked = TRUE;
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_RESPONSE_MOTION;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		if (bIsBlocked == TRUE) *dwp = DEF_OBJECTMOTION_BLOCKED;
			else *wp = DEF_OBJECTMOVE_REJECT;

		wObjectID = (WORD)iClientH;

		cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);

		wp  = (WORD *)cp;
		*wp = wObjectID;
		cp += 2;

		sp  = (short *)cp;
		sX  = m_pClientList[wObjectID]->m_sX;
		*sp = sX;
		cp += 2;

		sp  = (short *)cp;
		sY  = m_pClientList[wObjectID]->m_sY;
		*sp = sY;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sType;
		cp += 2;

		*cp = m_pClientList[wObjectID]->m_cDir;
		cp++;

		memcpy(cp, m_pClientList[wObjectID]->m_cCharName, 10);
		cp += 10;

		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr1;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr2;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr3;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr4;
		cp += 2;

		ip  = (int *)cp;
		*ip = m_pClientList[wObjectID]->m_iApprColor;
		cp += 4;
		
		// new
		ip  = (int *)cp;
		iTemp = m_pClientList[wObjectID]->m_iStatus;
		iTemp = 0x0FFFFFFF & iTemp;
		iTemp2 = iGetPlayerABSStatus(wObjectID, iClientH);
		iTemp  = (iTemp | (iTemp2 << 28));
		*ip = iTemp;
		cp += 4;

		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 42);
		
		switch (iRet) {
		case DEF_XSOCKEVENT_QUENEFULL:
		case DEF_XSOCKEVENT_SOCKETERROR:
		case DEF_XSOCKEVENT_CRITICALERROR:
		case DEF_XSOCKEVENT_SOCKETCLOSED:
			DeleteClient(iClientH, TRUE, TRUE);
			break;
		}
		return 0;
	}

	return 1;
}

/*********************************************************************************************************************
**  void CGame::RequestInitPlayerHandler(int iClientH, char * pData, char cKey)										**
**  DESCRIPTION			:: player login varifier																	**
**  LAST_UPDATED		:: March 14, 2005; 9:52 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- expanded DeleteClient and bSendMsgToLS												**
**	MODIFICATION		:: none																						**
**********************************************************************************************************************/
void CGame::RequestInitPlayerHandler(int iClientH, char * pData, char cKey)
{
 int i;
 char * cp, cCharName[11], cAccountName[11], cAccountPassword[11], cTxt[120];
 BOOL bIsObserverMode;
	
	// SNOOPY; added trap for faultlly client ID
	if (iClientH < 1) return;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == TRUE) return;

	ZeroMemory(cCharName, sizeof(cCharName));
	ZeroMemory(cAccountName, sizeof(cAccountName));
	ZeroMemory(cAccountPassword, sizeof(cAccountPassword));

	ZeroMemory(m_pClientList[iClientH]->m_cCharName, sizeof(m_pClientList[iClientH]->m_cCharName));
	ZeroMemory(m_pClientList[iClientH]->m_cAccountName, sizeof(m_pClientList[iClientH]->m_cAccountName));
	ZeroMemory(m_pClientList[iClientH]->m_cAccountPassword, sizeof(m_pClientList[iClientH]->m_cAccountPassword));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cCharName, cp, 10);
	cp += 10;

	ZeroMemory(cTxt, sizeof(cTxt));
	memcpy(cTxt, cCharName, 10);
	m_Misc.bDecode(cKey, cTxt);
	ZeroMemory(cCharName, sizeof(cCharName));
	memcpy(cCharName, cTxt, 10);


	memcpy(cAccountName, cp, 10);
	cp += 10;
	
	ZeroMemory(cTxt, sizeof(cTxt));
	memcpy(cTxt, cAccountName, 10);
	m_Misc.bDecode(cKey, cTxt);
	ZeroMemory(cAccountName, sizeof(cAccountName));
	memcpy(cAccountName, cTxt, 10);

	memcpy(cAccountPassword, cp, 10);
	cp += 10;

	ZeroMemory(cTxt, sizeof(cTxt));
	memcpy(cTxt, cAccountPassword, 10);
	m_Misc.bDecode(cKey, cTxt);
	ZeroMemory(cAccountPassword, sizeof(cAccountPassword));
	memcpy(cAccountPassword, cTxt, 10);
	
	bIsObserverMode = (BOOL)*cp;
	cp++;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
	if ((m_pClientList[i] != NULL) && (iClientH != i) && (memcmp(m_pClientList[i]->m_cAccountName, cAccountName, 10) == 0)) {
		if (memcmp(m_pClientList[i]->m_cAccountPassword, cAccountPassword, 10) == 0) { 
			wsprintf(G_cTxt, "(!) <%d> Duplicate account player! Deleted with data save : CharName(%s) AccntName(%s) IP(%s)", i, m_pClientList[i]->m_cCharName, m_pClientList[i]->m_cAccountName, m_pClientList[i]->m_cIPaddress);
			PutLogList(G_cTxt);
			DeleteClient(i, TRUE, TRUE, FALSE);
		}
		else {
			memcpy(m_pClientList[iClientH]->m_cCharName, cCharName, 10);
			memcpy(m_pClientList[iClientH]->m_cAccountName, cAccountName, 10);
			memcpy(m_pClientList[iClientH]->m_cAccountPassword, cAccountPassword, 10);
			DeleteClient(iClientH, FALSE, FALSE, FALSE);
			return;
		}
	}	
	
	for (i = 1; i < DEF_MAXCLIENTS; i++)
	if ((m_pClientList[i] != NULL) && (iClientH != i) && (memcmp(m_pClientList[i]->m_cCharName, cCharName, 10) == 0)) {
		if (memcmp(m_pClientList[i]->m_cAccountPassword, cAccountPassword, 10) == 0) { 
			wsprintf(G_cTxt, "(!) <%d> Duplicate player! Deleted with data save : CharName(%s) IP(%s)", i, m_pClientList[i]->m_cCharName, m_pClientList[i]->m_cIPaddress);
			PutLogList(G_cTxt);
			DeleteClient(i, TRUE, TRUE, FALSE);	
		}
		else {
			memcpy(m_pClientList[iClientH]->m_cCharName, cCharName, 10);
			memcpy(m_pClientList[iClientH]->m_cAccountName, cAccountName, 10);
			memcpy(m_pClientList[iClientH]->m_cAccountPassword, cAccountPassword, 10);
			DeleteClient(iClientH, FALSE, FALSE, TRUE, FALSE); // added TRUE at 4
			return;
		}
	}

	memcpy(m_pClientList[iClientH]->m_cCharName, cCharName, 10);
	memcpy(m_pClientList[iClientH]->m_cAccountName, cAccountName, 10);
	memcpy(m_pClientList[iClientH]->m_cAccountPassword, cAccountPassword, 10);
	m_pClientList[iClientH]->m_bIsObserverMode = bIsObserverMode;
	bSendMsgToLS(MSGID_REQUEST_PLAYERDATA, iClientH, TRUE); // added TRUE to 3
}

/*********************************************************************************************************************
**  void CGame::RequestInitDataHandler																				**
**  DESCRIPTION			:: manages player data/variables on enter zone												**
**  LAST_UPDATED		:: March 15, 2005; 7:32 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- added bIsResurrected to save process time												**
**						 	- added m_cWarType																		**
**						 	- expanded DeleteClient to include TRUE(4)												**
**						 	- missing <4> cp++																		**
**						 	- added temporary position list to stop items from scrambling on enter zone				**
**						 	- added checks to _iGetArrowItemIndex, and CalcTotalItemEffect							**
**						 	- forces player above 100 and in own town to become citizen								**
**						 	- completely redid force recall on login												**
**						 	- m_bIsInsideEnemyBuilding stores if have been inside enemy buildings					**
**						 	- now heldinain compatible (stores GUID and summon points)								**
**						 	- changed "fightzone" to "fight"														**
**						 	- notifies player if apocalypse gate is open as he enters zone							**
**	MODIFICATION		:: none																						**
**********************************************************************************************************************/
void CGame::RequestInitDataHandler(int iClientH, char * pData, char cKey, BOOL bIsResurrected)
{
 short * sp, sSummonPoints;
 DWORD * dwp;
 WORD  * wp;
 char  * cp, cPlayerName[11], cTxt[120], cPoints;
 int   * ip, i, iTotalItemA, iTotalItemB, iSize, iRet;
 SYSTEMTIME SysTime;
 char  * pBuffer = NULL;
 int iMapSide, iMapSide2;
 BOOL bIsItemListNull;
 POINT TempItemPosList[DEF_MAXITEMS];

	if (m_pClientList[iClientH] == NULL) return;
	pBuffer = new char [DEF_MSGBUFFERSIZE+1];
	ZeroMemory(pBuffer, DEF_MSGBUFFERSIZE+1);

	// new - check to save time process time when resurrecting
	if (bIsResurrected == FALSE) {
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
		ZeroMemory(cPlayerName, sizeof(cPlayerName));

		memcpy(cPlayerName, cp, 10);
		ZeroMemory(cTxt, sizeof(cTxt));

		memcpy(cTxt, cPlayerName, 10);
		m_Misc.bDecode(cKey, cTxt);

		ZeroMemory(cPlayerName, sizeof(cPlayerName));
		memcpy(cPlayerName, cTxt, 10);

		if (memcmp(m_pClientList[iClientH]->m_cCharName, cPlayerName, 10) != 0) {
			DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE); // added TRUE to 4
			return;
		}
	}
	dwp  = (DWORD *)(pBuffer + DEF_INDEX4_MSGID);
	*dwp = MSGID_PLAYERCHARACTERCONTENTS;
	wp   = (WORD *) (pBuffer + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_MSGTYPE_CONFIRM;

	cp = (char *)(pBuffer + DEF_INDEX2_MSGTYPE + 2);
//6
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iHP;
	cp  += 4;
//10
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iMP;
	cp  += 4;
//14
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iSP;
	cp  += 4;
//18
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iDefenseRatio;
	cp  += 4;
//22
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iHitRatio;
	cp  += 4;
//26
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iLevel;
	cp  += 4;
//30
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iStr;		
	cp  += 4;
//34
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iInt;					
	cp  += 4;
//38
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iVit;								
	cp  += 4;
//42
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iDex;			
	cp  += 4;
//46
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iMag;						
	cp  += 4;
//50
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iCharisma;
	cp  += 4;
//54
	wp = (WORD *)cp; 
	*wp = m_pClientList[iClientH]->m_iLU_Pool;
	cp += 2;
//56
	*cp = m_pClientList[iClientH]->m_cWarType; // new
	cp++;
//57
	*cp = 0; // missing data
	cp++;
//58
	*cp = 0; // missing data
	cp++;
//59
	*cp = 0; // missing data
	cp++;
//60
	*cp = 0; // missing data
	cp++;
//61
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iExp;
	cp  += 4;
//65
	ip = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iEnemyKillCount;
	cp  += 4;
//69
	ip = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iMaxEK;
	cp  += 4;
//73
	ip = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iPKCount;
	cp  += 4;
//77
	ip = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iRewardGold;
	cp  += 4;
//81
	memcpy(cp, m_pClientList[iClientH]->m_cLocation, 10);
	cp  += 10;
//91
	memcpy(cp, m_pClientList[iClientH]->m_cGuildName, 20);
	cp  += 20;
//111
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iGuildRank;
	cp  += 4;
//115
	*cp = (char)m_pClientList[iClientH]->m_iSuperAttackLeft;
	cp++;
//116
	ip   = (int *)cp;
	*ip  = m_pClientList[iClientH]->m_iFightzoneNumber;
	cp  += 4;
//120
	ip = (int*)cp;
	*ip = m_pClientList[iClientH]->m_iDeaths;
	cp += 4;
//124
	ip = (int*)cp;
	*ip = m_pClientList[iClientH]->m_iWantedLevel; // Wanted System
	cp += 4;
 //128
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(pBuffer, 128);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, TRUE, TRUE, TRUE, FALSE); // added TRUE (4)
		if(pBuffer != NULL) delete[] pBuffer;
		return;
	}

	dwp  = (DWORD *)(pBuffer + DEF_INDEX4_MSGID);
	*dwp = MSGID_PLAYERITEMLISTCONTENTS;
	wp   = (WORD *) (pBuffer + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_MSGTYPE_CONFIRM;

	iTotalItemA = 0;
	for (i = 0; i < DEF_MAXITEMS; i++)
		if (m_pClientList[iClientH]->m_pItemList[i] != NULL) 
			iTotalItemA++;

	// new
	bIsItemListNull = FALSE;
	if (!bIsItemListNull) {
		bIsItemListNull = TRUE;
		for (i = 0; i < DEF_MAXITEMS-1; i++) {
			if ((m_pClientList[iClientH]->m_pItemList[i] == NULL) && (m_pClientList[iClientH] != NULL)) {
				m_pClientList[iClientH]->m_ItemPosList[i].x = TempItemPosList[i].x; 
				m_pClientList[iClientH]->m_ItemPosList[i].y = TempItemPosList[i].y;
				bIsItemListNull = FALSE;
			}
		}
	}
	m_pClientList[iClientH]->m_cArrowIndex = _iGetArrowItemIndex(iClientH); // new
	CalcTotalItemEffect(iClientH, -1, FALSE); // new

	cp = (char *)(pBuffer + DEF_INDEX2_MSGTYPE + 2);
	*cp = iTotalItemA;
	cp++;

	for (i = 0; i < iTotalItemA; i++) {
		if (m_pClientList[iClientH]->m_pItemList[i] == NULL) {
			wsprintf(G_cTxt, "RequestInitDataHandler error: Client(%s) Item(%d)", m_pClientList[iClientH]->m_cCharName, i);
			PutLogFileList(G_cTxt);

			DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE); // added TRUE (4)
			if(pBuffer != NULL) delete[] pBuffer;
			return;
		}

		memcpy(cp, m_pClientList[iClientH]->m_pItemList[i]->m_cName, 20);
		cp += 20;

		dwp  = (DWORD *)cp;
		*dwp = m_pClientList[iClientH]->m_pItemList[i]->m_dwCount;
		cp += 4;

		*cp = m_pClientList[iClientH]->m_pItemList[i]->m_cItemType;
		cp++;

		*cp = m_pClientList[iClientH]->m_pItemList[i]->m_cEquipPos;
		cp++;

		*cp = (char)m_pClientList[iClientH]->m_bIsItemEquipped[i];
		cp++;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemList[i]->m_sLevelLimit;
		cp += 2;

		*cp = m_pClientList[iClientH]->m_pItemList[i]->m_cGenderLimit;
		cp++;

		wp = (WORD *)cp;
		*wp = m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan;
		cp += 2;

		wp = (WORD *)cp;
		*wp = m_pClientList[iClientH]->m_pItemList[i]->m_wWeight;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemList[i]->m_sSprite;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemList[i]->m_sSpriteFrame;
		cp += 2;

		*cp = m_pClientList[iClientH]->m_pItemList[i]->m_cItemColor;
		cp++;

		*cp = (char)m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue2; 
		cp++;

		dwp =(DWORD *)cp;
		*dwp = m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute;
		cp += 4;
	}
	iTotalItemB = 0;
	for (i = 0; i < DEF_MAXBANKITEMS; i++)
		if (m_pClientList[iClientH]->m_pItemInBankList[i] != NULL) 
			iTotalItemB++;

	*cp = iTotalItemB;
	cp++;

	for (i = 0; i < iTotalItemB; i++) {
		if (m_pClientList[iClientH]->m_pItemInBankList[i] == NULL) {
			wsprintf(G_cTxt, "RequestInitDataHandler error: Client(%s) Bank-Item(%d)", m_pClientList[iClientH]->m_cCharName, i);
			PutLogFileList(G_cTxt);

			DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE); // added TRUE (4)
			if(pBuffer != NULL) delete[] pBuffer;
			return;
		}
		memcpy(cp, m_pClientList[iClientH]->m_pItemInBankList[i]->m_cName, 20);
		cp += 20;

		dwp  = (DWORD *)cp;
		*dwp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwCount;
		cp += 4;

		*cp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemType;
		cp++;

		*cp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_cEquipPos;
		cp++;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_sLevelLimit;
		cp += 2;

		*cp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_cGenderLimit;
		cp++;

		wp = (WORD *)cp;
		*wp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan;
		cp += 2;

		wp = (WORD *)cp;
		*wp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_wWeight;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_sSprite;
		cp += 2;

		sp  = (short *)cp;
		*sp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_sSpriteFrame;
		cp += 2;

		*cp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemColor;
		cp++;

		*cp = (char)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue2; 
		cp++;

		dwp =(DWORD *)cp;
		*dwp = m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute;
		cp += 4;
	}

	for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
		*cp = m_pClientList[iClientH]->m_cMagicMastery[i];
		cp++;
	}

	for (i = 0; i < DEF_MAXSKILLTYPE; i++) {
		*cp = m_pClientList[iClientH]->m_cSkillMastery[i];
		cp++;
	}

	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(pBuffer, 6 + 1 + iTotalItemA*44 + iTotalItemB*43 + DEF_MAXMAGICTYPE + DEF_MAXSKILLTYPE);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, TRUE, TRUE, TRUE, FALSE); // added TRUE (4)
		if(pBuffer != NULL) delete[] pBuffer;
		return;
	}
		
	dwp  = (DWORD *)(pBuffer + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_INITDATA;
	wp   = (WORD *)(pBuffer + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_MSGTYPE_CONFIRM;

	cp = (char *)(pBuffer + DEF_INDEX2_MSGTYPE + 2);

	if (m_pClientList[iClientH]->m_bIsObserverMode == FALSE)
		bGetEmptyPosition(&m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_cMapIndex);
	else GetMapInitialPoint(m_pClientList[iClientH]->m_cMapIndex, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY);

	wp  = (WORD *)cp;
	*wp = iClientH;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sX - 14 - 5;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sY - 12 - 5;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sType;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr1;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr2;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr3;
	cp += 2;

	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr4;
	cp += 2;

	ip  = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iApprColor;
	cp += 4;

	ip  = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iStatus;
	cp += 4;

	memcpy(cp, m_pClientList[iClientH]->m_cMapName, 10);
	cp += 10;

	memcpy(cp, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, 10);
	cp += 10;

	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFixedDayMode == TRUE) 
		*cp = 1;
	else *cp = m_cDayOrNight;
	cp++;

	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFixedDayMode == TRUE) 
		*cp = NULL;
	else *cp = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus;
	cp++;

	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iContribution;
	cp += 4;

	if (m_pClientList[iClientH]->m_bIsObserverMode == FALSE) {
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	}

	*cp = (char)m_pClientList[iClientH]->m_bIsObserverMode;
	cp++;

	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iRating;
	cp += 4;

	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iHP;
	cp += 4;

	// new
	if (m_pClientList[iClientH]->m_pIsProcessingAllowed == TRUE) {
		cPoints = 0;
		if ((m_pClientList[iClientH]->m_cSide != m_sLastHeldenianWinner) && (m_sLastHeldenianWinner != 0)) {
			cPoints = 100;
		}
	}
	*cp = cPoints;
	cp++;

	iSize = iComposeInitMapData(m_pClientList[iClientH]->m_sX - 13, m_pClientList[iClientH]->m_sY - 10, iClientH, cp );
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(pBuffer, 85 + iSize); // SephirotH fix - 66
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, TRUE, TRUE, TRUE, FALSE); // new TRUE (4)
		if (pBuffer != NULL) delete[] pBuffer;
		return;
	}
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_LOG, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL);
	// new
	if ((m_pClientList[iClientH]->m_iLevel > 100) && (m_pClientList[iClientH]->m_bIsInCombatantOnlyZone == TRUE)) {
		ForceChangePlayMode(iClientH, TRUE);
	}

	if ((m_pClientList[iClientH]->m_cSide == 1) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "elvine", 6) == 0)  && 
		(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
		m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
		CheckForceRecallTime(iClientH);
	}
	else if ((m_pClientList[iClientH]->m_cSide == 2) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "aresden", 7) == 0) &&
		(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
		m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
		CheckForceRecallTime(iClientH);
	}
	else if ((m_pClientList[iClientH]->m_cSide == 0) && (m_bIsCrusadeMode == TRUE)) {
		if ((strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvine") == 0) ||
			(strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "aresden") == 0)) {
			if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) {
				m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
				m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 1;
			}
		}
		if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) {
			m_pClientList[iClientH]->m_bIsWarLocation = FALSE;
			m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
			m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 0;
		}
	}

	iMapSide = iGetMapLocationSide(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName);
	if (iMapSide > 3) iMapSide2 = iMapSide - 2;
	else iMapSide2 = iMapSide;
	m_pClientList[iClientH]->m_bIsInsideEnemyBuilding = FALSE; // new
	if ((m_pClientList[iClientH]->m_cSide != iMapSide2) && (iMapSide != 0)) {
		if ((iMapSide <= 2) && (m_pClientList[iClientH]->m_iAdminUserLevel < 1)) {
			if (m_pClientList[iClientH]->m_cSide != 0) {
				m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
				m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 1;
				m_pClientList[iClientH]->m_bIsInsideEnemyBuilding = TRUE; // new
			}
		}
	}
	else{
		if ((m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_bIsFightZone == TRUE) &&
			(m_iFightzoneNoForceRecall == FALSE) && 
			(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
			m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
			m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
			GetLocalTime(&SysTime);
			m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 2*60*20 - ((SysTime.wHour%2)*20*60 + SysTime.wMinute*20) - 2*20;
		}
		else{
			if ((memcmp(m_pMapList[ m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "arejail", 7) == 0) ||
				(memcmp(m_pMapList[ m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "elvjail", 7) == 0)) {
				if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) {
					m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
					m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
					if (m_pClientList[iClientH]->m_iTimeLeft_ForceRecall == 0) {
						m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 100;
					}
					else if (m_pClientList[iClientH]->m_iTimeLeft_ForceRecall > 100) {
						m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 100;
					}
				}
			}
		}
	}

	if (m_pClientList[iClientH]->m_iTimeLeft_ForceRecall > 0) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FORCERECALLTIME,  m_pClientList[iClientH]->m_iTimeLeft_ForceRecall , NULL, NULL, NULL);
		wsprintf(G_cTxt,"(!) Game Server Force Recall Time  %d (%d)min", m_pClientList[iClientH]->m_iTimeLeft_ForceRecall, m_pClientList[iClientH]->m_iTimeLeft_ForceRecall/20) ;
		PutLogList(G_cTxt);
	}

	if (m_pClientList[iClientH]->m_iGizonItemUpgradeLeft < 0) {
		m_pClientList[iClientH]->m_iGizonItemUpgradeLeft = 0;
	}

	if ((memcmp(m_pClientList[iClientH]->m_cMapName, "fightzone1", 10) != 0) && (bDeathmatch))
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_DEATHMATCHSTART, NULL, NULL, NULL, NULL);

	if ((memcmp(m_pClientList[iClientH]->m_cMapName, "fightzone1", 10) == 0) && (bDeathmatch))
	{
		m_pClientList[iClientH]->m_iDGKills = 0; 
		m_pClientList[iClientH]->m_iDGDeaths = 0;
		RefreshDeathmatch(iClientH); // Morla 2.3 - actualiza el deathmach
	}

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SAFEATTACKMODE, NULL, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_DOWNSKILLINDEXSET, m_pClientList[iClientH]->m_iDownSkillIndex, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ITEMPOSLIST, NULL, NULL, NULL, NULL);		
	_SendQuestContents(iClientH);
	_CheckQuestEnvironment(iClientH);

	if (m_pClientList[iClientH]->m_iSpecialAbilityTime == 0) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SPECIALABILITYENABLED, NULL, NULL, NULL, NULL);
	}

	if (m_bIsCrusadeMode == TRUE) {
		if (m_pClientList[iClientH]->m_dwCrusadeGUID == 0) {
			m_pClientList[iClientH]->m_iCrusadeDuty			= 0;
			m_pClientList[iClientH]->m_iConstructionPoint	= 0;
			m_pClientList[iClientH]->m_dwCrusadeGUID		= m_dwCrusadeGUID;
		}
		else if (m_pClientList[iClientH]->m_dwCrusadeGUID != m_dwCrusadeGUID) {
			m_pClientList[iClientH]->m_iCrusadeDuty       = 0;
			m_pClientList[iClientH]->m_iConstructionPoint = 0;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
			m_pClientList[iClientH]->m_dwCrusadeGUID = m_dwCrusadeGUID;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, 0, NULL, -1);		
		}
		m_pClientList[iClientH]->m_cWarType = 1;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, m_pClientList[iClientH]->m_iCrusadeDuty, NULL, NULL);
	}
	// Heldenian
	else if (m_bIsHeldenianMode == TRUE) 
	{	sSummonPoints = 10000 + m_pClientList[iClientH]->m_iCharisma*100;
		if (m_pClientList[iClientH]->m_dwHeldenianGUID == NULL) 
		{	m_pClientList[iClientH]->m_dwHeldenianGUID    = m_dwHeldenianGUID;
			m_pClientList[iClientH]->m_iConstructionPoint = sSummonPoints;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
			if (   (m_pMapList[m_pClientList[iClientH]->m_cMapIndex] != NULL) 
				&& (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsHeldenianMap == 1))
			{	// Player connecting on Heldenian map, and not been advised of Heldenian start will recall
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_0BE8, NULL , NULL, NULL, NULL);	
				m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 3;
			}
		}else if (m_pClientList[iClientH]->m_dwHeldenianGUID != m_dwHeldenianGUID) 
		{	m_pClientList[iClientH]->m_dwHeldenianGUID    = m_dwHeldenianGUID;
			m_pClientList[iClientH]->m_iConstructionPoint = sSummonPoints;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
			if (   (m_pMapList[m_pClientList[iClientH]->m_cMapIndex] != 0) 
				&& (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsHeldenianMap == 1))
			{	// Player connecting on Heldenian map, and not been advised of this Heldenian start will recall
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_0BE8, NULL , NULL, NULL, NULL);	
				m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 3;
		}	}
		if (m_cHeldenianWinner == -1) 
		{	if (m_bHeldenianWarInitiated == TRUE) 
			{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANSTART, NULL, NULL, NULL, NULL);
			}else
			{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANTELEPORT, NULL, NULL, NULL, NULL);
			}
		}else // Force recall loosers
		{	if (   (m_pClientList[iClientH]->m_cSide != m_cHeldenianWinner)
				&& (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsHeldenianMap == 1))
			{	m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 2;
		}	}
		m_pClientList[iClientH]->m_cWarType = 2;// character have been informed of heldenian starting...
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iClientH]->m_iConstructionPoint, m_pClientList[iClientH]->m_iWarContribution, 1, NULL);
		UpdateHeldenianStatus(iClientH);
	}
	else if ((m_pClientList[iClientH]->m_cWarType == 1) && (m_pClientList[iClientH]->m_dwCrusadeGUID == m_dwCrusadeGUID)) {
		m_pClientList[iClientH]->m_iCrusadeDuty = 0;
		m_pClientList[iClientH]->m_iConstructionPoint = 0;
	}
	else if ((m_pClientList[iClientH]->m_dwCrusadeGUID != 0) && (m_pClientList[iClientH]->m_cWarType == 1)) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, NULL, NULL, -1);
	}
	// The Heldenian he has participated is over...
	else if ( (m_pClientList[iClientH]->m_dwHeldenianGUID == m_dwHeldenianGUID)
			&& (m_pClientList[iClientH]->m_dwHeldenianGUID != NULL)) 
	{	m_pClientList[iClientH]->m_iConstructionPoint = 0;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANEND, NULL, NULL, NULL, NULL);
		m_pClientList[iClientH]->m_cWarType = 0; // Character is informed of Hedenian end... so he'll get XP later
	}
	else {
		m_pClientList[iClientH]->m_iWarContribution = 0; 
		m_pClientList[iClientH]->m_dwCrusadeGUID = 0;
		m_pClientList[iClientH]->m_iConstructionPoint = 0;
	}
	// new fightzone changed to fight
	if (memcmp(m_pClientList[iClientH]->m_cMapName, "fight", 5) == 0) {
		wsprintf(G_cTxt, "Char(%s)-Enter(%s) Observer(%d)", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_cMapName, m_pClientList[iClientH]->m_bIsObserverMode);
		PutLogEventFileList(G_cTxt);
	}
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iClientH]->m_iConstructionPoint, m_pClientList[iClientH]->m_iWarContribution, 1, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GIZONITEMUPGRADELEFT, m_pClientList[iClientH]->m_iGizonItemUpgradeLeft, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAJESTIC_LEVEL, m_pClientList[iClientH]->m_iMajesticLevel, NULL, NULL, NULL, NULL);
	
	//50Cent - Critical Count Login Fix
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);

	// centu - sends max stats to client, and receive it when log in
	SendNotifyMsg(NULL, iClientH, DEF_MAX_STATS, m_sCharStatLimit - 11, NULL, NULL, NULL);
	
	// SNOOPY: Send gate positions if applicable.
	Notify_ApocalypseGateState(iClientH);

	if (m_pClientList[iClientH]->m_iLU_Pool < 3) m_pClientList[iClientH]->m_iLU_Pool = 3;

}

/*********************************************************************************************************************
**  void CGame::DeleteClient(int iClientH, BOOL bSave, BOOL bNotify, BOOL bCountLogout, BOOL bForceCloseConn)		**
**  DESCRIPTION			:: manages disconnect player																**
**  LAST_UPDATED		:: March 16, 2005; 12:02 AM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				:: n/a																						**
**	MODIFICATION		:: n/a																						**
**********************************************************************************************************************/
void CGame::DeleteClient(int iClientH, BOOL bSave, BOOL bNotify, BOOL bCountLogout, BOOL bForceCloseConn)
{
	int i, iExH;
	char * cp, cData[120], cTmpMap[30];
	DWORD * dwp;
	WORD * wp;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == TRUE) {
		if (memcmp(m_pClientList[iClientH]->m_cMapName, "fight", 5) == 0) {
			wsprintf(G_cTxt, "Char(%s)-Exit(%s)", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_cMapName);
			PutLogEventFileList(G_cTxt);
		}

		if (m_pClientList[iClientH]->m_cExchangeMode != 0) {
			iExH = m_pClientList[iClientH]->m_iExchangeH;
			_ClearExchangeStatus(iExH);
			_ClearExchangeStatus(iClientH);
		}

		if ((m_pClientList[iClientH]->m_iAllocatedFish != NULL) && (m_pFish[m_pClientList[iClientH]->m_iAllocatedFish] != NULL)) 
			m_pFish[m_pClientList[iClientH]->m_iAllocatedFish]->m_sEngagingCount--;

		if (bNotify == TRUE)
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_LOG, DEF_MSGTYPE_REJECT, NULL, NULL, NULL);

		RemoveFromTarget(iClientH, DEF_OWNERTYPE_PLAYER);

		for (i = 1; i < DEF_MAXCLIENTS; i++) 
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_iWhisperPlayerIndex	== iClientH)) {
				m_pClientList[i]->m_iWhisperPlayerIndex = -1;
				SendNotifyMsg(NULL, i, DEF_NOTIFY_WHISPERMODEOFF, NULL, NULL, NULL, m_pClientList[iClientH]->m_cCharName);
			}

			ZeroMemory(cData, sizeof(cData));
			cp = (char *)cData;
			*cp = GSM_DISCONNECT;
			cp++;
			memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
			cp += 10;
			bStockMsgToGateServer(cData, 11);

			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(2, iClientH, DEF_OWNERTYPE_PLAYER,
				m_pClientList[iClientH]->m_sX, 
				m_pClientList[iClientH]->m_sY);

			bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, NULL);
	}

	if ((bSave == TRUE) && (m_pClientList[iClientH]->m_bIsOnServerChange == FALSE)) {
		
		if (m_pClientList[iClientH]->m_bIsKilled == TRUE) {
			m_pClientList[iClientH]->m_sX = -1;
			m_pClientList[iClientH]->m_sY = -1;

			strcpy(cTmpMap,m_pClientList[iClientH]->m_cMapName) ;

			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));

			if (m_pClientList[iClientH]->m_cSide == 0) {
				strcpy(m_pClientList[iClientH]->m_cMapName, "default");
			}
			else {
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "are", 3) == 0) {
					if (m_bIsCrusadeMode == TRUE) {
						if (m_pClientList[iClientH]->m_iDeadPenaltyTime > 0) {
							ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
							strcpy(m_pClientList[iClientH]->m_cLockedMapName, "aresden");
							m_pClientList[iClientH]->m_iLockedMapTime = 60*5;
							m_pClientList[iClientH]->m_iDeadPenaltyTime = 60*10;
						}
						else {
							m_pClientList[iClientH]->m_iDeadPenaltyTime = 60*10;
						}
					}

					if (strcmp(cTmpMap, "elvine") == 0){
						strcpy(m_pClientList[iClientH]->m_cLockedMapName, "elvjail");
						m_pClientList[iClientH]->m_iLockedMapTime = 60 ;
						memcpy(m_pClientList[iClientH]->m_cMapName, "elvjail", 7);
					}else if (m_pClientList[iClientH]->m_iLevel > 80)
						memcpy(m_pClientList[iClientH]->m_cMapName, "cityhall_1", 10);
					else memcpy(m_pClientList[iClientH]->m_cMapName, "arefarm", 7);
				}
				else {
					if (m_bIsCrusadeMode == TRUE) {
						if (m_pClientList[iClientH]->m_iDeadPenaltyTime > 0) {
							ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
							strcpy(m_pClientList[iClientH]->m_cLockedMapName, "elvine");
							m_pClientList[iClientH]->m_iLockedMapTime = 60*5;
							m_pClientList[iClientH]->m_iDeadPenaltyTime = 60*10;
						}
						else {
							m_pClientList[iClientH]->m_iDeadPenaltyTime = 60*10;
						}
					}
					if (strcmp(cTmpMap, "aresden") == 0){
						strcpy(m_pClientList[iClientH]->m_cLockedMapName, "arejail");
						m_pClientList[iClientH]->m_iLockedMapTime = 60 ;
						memcpy(m_pClientList[iClientH]->m_cMapName, "arejail", 7);

					}else if (m_pClientList[iClientH]->m_iLevel > 80)
						memcpy(m_pClientList[iClientH]->m_cMapName, "cityhall_2", 10);
					else memcpy(m_pClientList[iClientH]->m_cMapName, "elvfarm", 7);
				}
			}
		}
		else if (bForceCloseConn == TRUE) {
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			memcpy(m_pClientList[iClientH]->m_cMapName, "bisle", 5);
			m_pClientList[iClientH]->m_sX = -1;
			m_pClientList[iClientH]->m_sY = -1;

			ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
			strcpy(m_pClientList[iClientH]->m_cLockedMapName, "bisle");
			m_pClientList[iClientH]->m_iLockedMapTime = 10*60;
		}

		if (m_pClientList[iClientH]->m_bIsObserverMode == TRUE) {
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			if (m_pClientList[iClientH]->m_cSide == 0) {
				switch (iDice(1,2)) {
				case 1:
					memcpy(m_pClientList[iClientH]->m_cMapName, "aresden", 7);
					break;
				case 2:
					memcpy(m_pClientList[iClientH]->m_cMapName, "elvine", 6);
					break;
				}
			}
			else {
				memcpy(m_pClientList[iClientH]->m_cMapName, m_pClientList[iClientH]->m_cLocation, 10);
			}
			m_pClientList[iClientH]->m_sX = -1;
			m_pClientList[iClientH]->m_sY = -1;
		}

		if (memcmp(m_pClientList[iClientH]->m_cMapName, "fight", 5) == 0) {
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			if (m_pClientList[iClientH]->m_cSide == 0) {
				switch (iDice(1,2)) {
				case 1:
					memcpy(m_pClientList[iClientH]->m_cMapName, "aresden", 7);
					break;
				case 2:
					memcpy(m_pClientList[iClientH]->m_cMapName, "elvine", 6);
					break;
				}
			}
			else {
				memcpy(m_pClientList[iClientH]->m_cMapName, m_pClientList[iClientH]->m_cLocation, 10);
			}
			m_pClientList[iClientH]->m_sX = -1;
			m_pClientList[iClientH]->m_sY = -1;
		}

		if (m_pClientList[iClientH]->m_bIsInitComplete == TRUE) {
			if (m_pClientList[iClientH]->m_iPartyID != NULL) {
				ZeroMemory(cData, sizeof(cData));
				cp = (char *)cData;

				dwp = (DWORD *)cp;
				*dwp = MSGID_PARTYOPERATION;
				cp += 4;

				wp = (WORD*)cp;
				*wp = 4;
				cp += 2;

				wp = (WORD *)cp;
				*wp = iClientH;
				cp += 2;

				memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
				cp += 10;

				wp = (WORD *)cp;
				*wp = m_pClientList[iClientH]->m_iPartyID;
				cp += 2;
		
				SendMsgToGateServer(MSGID_PARTYOPERATION, iClientH, cData);
			}
			if (bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATALOGOUT, iClientH, bCountLogout) == FALSE) LocalSavePlayerData(iClientH);
		}
		else bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATALOGOUT, iClientH, bCountLogout);
	}
	else {
		if (m_pClientList[iClientH]->m_bIsOnServerChange == FALSE) {
			if (m_pClientList[iClientH]->m_iPartyID != NULL) {
				ZeroMemory(cData, sizeof(cData));
				cp = (char *)cData;

				dwp = (DWORD *)cp;
				*dwp = MSGID_PARTYOPERATION;
				cp += 4;

				wp = (WORD*)cp;
				*wp = 4;
				cp += 2;

				wp = (WORD *)cp;
				*wp = iClientH;
				cp += 2;

				memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
				cp += 10;

				wp = (WORD *)cp;
				*wp = m_pClientList[iClientH]->m_iPartyID;
				cp += 2;

				SendMsgToGateServer(MSGID_PARTYOPERATION, iClientH, cData);
			}

			bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATALOGOUT, iClientH, bCountLogout);
		}
		else {
			if (m_pClientList[iClientH]->m_iPartyID != NULL) {
				ZeroMemory(cData, sizeof(cData));
				cp = (char *)cData;

				dwp = (DWORD *)cp;
				*dwp = MSGID_PARTYOPERATION;
				cp += 4;

				wp = (WORD*)cp;
				*wp = 7;
				cp += 2;

				wp = (WORD *)cp;
				*wp = NULL;
				cp += 2;

				memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
				cp += 10;

				wp = (WORD *)cp;
				*wp = m_pClientList[iClientH]->m_iPartyID;
				cp += 2;
			
				SendMsgToGateServer(MSGID_PARTYOPERATION, iClientH, cData);
			}

			bSendMsgToLS(MSGID_REQUEST_SETACCOUNTWAITSTATUS, iClientH, FALSE); 
		}
	}

	if (m_pClientList[iClientH]->m_iPartyID != NULL) {
		for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
			if (m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] == iClientH) {
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] = 0;
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers--;
				wsprintf(G_cTxt, "PartyID:%d member:%d Out(Delete) Total:%d", m_pClientList[iClientH]->m_iPartyID, iClientH, m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers);
				PutLogList(G_cTxt);
				break;
			}
		}
		for (i = 0; i < DEF_MAXPARTYMEMBERS - 1; i++) {
			if ((m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] == 0) && (m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i + 1] != 0)) {
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] = m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i + 1];
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i + 1] = 0;
			}
		}
	}

	// centu - refresh when player gets dc/cl
	if ((memcmp(m_pClientList[iClientH]->m_cMapName, "fightzone1", 10) == 0) && (bDeathmatch))
		RefreshDeathmatch(iClientH); // Morla 2.3 - actualiza el deathmach

	//50Cent - Capture The Flag
	if (bCheckIfIsFlagCarrier(iClientH))
	{
		SetFlagCarrierFlag(iClientH, false);
		SetIceFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
	}

	m_iTotalClients--;

	delete m_pClientList[iClientH];
	m_pClientList[iClientH] = NULL;

	RemoveClientShortCut(iClientH);
}

/*********************************************************************************************************************
**  void CGame::OnTimer(char cType)																					**
**  DESCRIPTION			:: events occuring automatically after a set period of time									**
**  LAST_UPDATED		:: March 17, 2005; 2:24 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- added "&& (m_bIsWLServerAvailable == TRUE)" to list of Send Messages <commented>		**
**							- changed m_iSubLogSockInitIndex location												**
**							- added new functions ApocalypseWarStarter(), AutomaticApocalypseEnd(),					**
**							DoAbaddonThunderDamageHandler(), HeldenianWarStarter(), AutomaticHeldenianEnd(),		**
**							AutomatedHeldenianTimer()																**
**	MODIFICATION		::  n/a			 																			**
**********************************************************************************************************************/
void CGame::OnTimer(char cType)
{
 DWORD dwTime = timeGetTime();
 int i;
	NpcProcess();
	MsgProcess();
	if ((dwTime - m_dwGameTime2) > 3000) {
		CheckClientResponseTime();
		SendMsgToGateServer(MSGID_GAMESERVERALIVE, NULL, NULL);
		CheckDayOrNightMode();
		InvalidateRect(G_hWnd, NULL, TRUE);
		_CheckGateSockConnection();
		if ((m_bIsGameStarted == FALSE)     && (m_bIsItemAvailable == TRUE)      && 
			(m_bIsNpcAvailable == TRUE)     && (m_bIsGateSockAvailable == TRUE)  &&
			(m_bIsLogSockAvailable == TRUE) && (m_bIsMagicAvailable == TRUE)     &&
			(m_bIsSkillAvailable == TRUE)   && (m_bIsPotionAvailable == TRUE)   &&
			(m_bIsQuestAvailable == TRUE)   && (m_bIsBuildItemAvailable == TRUE) && 
			(m_iSubLogSockActiveCount == DEF_MAXSUBLOGSOCK)) { 
			PutLogList("Sending start message...");
			SendMessage(m_hWnd, WM_USER_STARTGAMESIGNAL, NULL, NULL);
			m_bIsGameStarted = TRUE;
		}
		m_dwGameTime2 = dwTime;
	}
	if ((dwTime - m_dwGameTime6) > 1000) {
		DelayEventProcessor();
		SendStockMsgToGateServer();
		if (m_iFinalShutdownCount != 0) {
			m_iFinalShutdownCount--;
			wsprintf(G_cTxt, "Final Shutdown...%d", m_iFinalShutdownCount);
			PutLogList(G_cTxt);
			if (m_iFinalShutdownCount <= 1) {
				SendMessage(m_hWnd, WM_CLOSE, NULL, NULL);
				return;
				
			}
		}
		// new location
		if (m_iSubLogSockInitIndex < DEF_MAXSUBLOGSOCK) {
			m_pSubLogSock[m_iSubLogSockInitIndex] = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
			m_pSubLogSock[m_iSubLogSockInitIndex]->bConnect(m_cLogServerAddr, m_iLogServerPort, (WM_ONLOGSOCKETEVENT + m_iSubLogSockInitIndex + 1));
			m_pSubLogSock[m_iSubLogSockInitIndex]->bInitBufferSize(DEF_MSGBUFFERSIZE);
			wsprintf(G_cTxt, "(!) Try to connect sub-log-socket(%d)... Addr:%s  Port:%d", m_iSubLogSockInitIndex, m_cLogServerAddr, m_iLogServerPort);
			PutLogList(G_cTxt);
			m_iSubLogSockInitIndex++;
		}
		m_dwGameTime6 = dwTime; // moved
	}
	if ((dwTime - m_dwGameTime3) > 3000) {
		SyncMiddlelandMapInfo();
		CheckDynamicObjectList();
		DynamicObjectEffectProcessor();
		NoticeHandler();
		SpecialEventHandler();
		
		//SNOOPY:Check if Apocalypse Gate nedd to be closed
		OpenCloseApocalypseGate();
		m_dwGameTime3 = dwTime;
	}

	if (m_iNotifyCleanMap == TRUE)
	{	
		if ((dwTime - m_dwCleanTime) > (m_iClearMapTime-30)*1000) // 30 sec
		{	
			for (i = 1; i < DEF_MAXCLIENTS; i++) 
			{	if (m_pClientList[i] != NULL) 
				{	
					SendNotifyMsg(NULL, i, DEF_NOTIFY_IPACCOUNTINFO, NULL, NULL, NULL, "The maps will be cleaned in 30 seconds. Get drops!");					
				}
				m_iNotifyCleanMap = FALSE;
			}	
		}
	}
	
	if ((dwTime - m_dwCleanTime) > m_iClearMapTime*1000) // 2700*1000 = 45 min 1800*1000 = 30 min 3600*1000 = 1h	
	{	ClearMap();
		m_dwCleanTime = dwTime;
	}

	if ((dwTime - m_dwGameTime4) > 600) { // time millisecond = *60*10*10
		MobGenerator();

		m_dwGameTime4 = dwTime;
	}
	if ((dwTime - m_dwGameTime5) > 180000) {
		m_dwGameTime5 = dwTime;
		srand((unsigned)time(NULL));   
	}
	if ((dwTime - m_dwFishTime) > 4000) {
		FishProcessor();
		FishGenerator();
		SendCollectedMana();
		if ((m_bIsCrusadeMode == FALSE) && (m_bIsCrusadeWarStarter == TRUE)) CrusadeWarStarter();
		if ((m_bIsApocalypseStarter == TRUE) && (m_bIsApocalypseMode == FALSE)) ApocalypseStarter();
		if ((m_bIsHeldenianReady == TRUE) && (m_bIsHeldenianMode == FALSE)) HeldenianWarStarter();
		if (m_bIsApocalypseMode == TRUE) DoAbaddonThunderDamageHandler(-1); // -1 only affects Abaddon map
		//SNOOPY: check if Heldenian war must be started or finished.
		if (m_bIsHeldenianMode == TRUE)		  
		{	HeldenianStartWarNow();
			HeldenianEndWarNow();
		}
		AFKChecker();
		m_dwFishTime = dwTime;
	}
	
	if ((dwTime - m_dwWhetherTime) > 20000) {
		WeatherProcessor();
		SendThunders();
		m_dwWhetherTime = dwTime;
	}
	
	if ((dwTime - m_dwCanFightzoneReserveTime) > 7200000) {
		m_dwCanFightzoneReserveTime = dwTime;
	}

	if ((m_bIsServerShutdowned == FALSE) && (m_bOnExitProcess == TRUE) && ((dwTime - m_dwExitProcessTime) > 1000*2)) {
		if (_iForcePlayerDisconect(15) == 0) {
			PutLogList("(!) GAME SERVER SHUTDOWN PROCESS COMPLETED! All players are disconnected.");
			m_bIsServerShutdowned = TRUE;
			if ((m_cShutDownCode == 3) || (m_cShutDownCode == 4)) {
				PutLogFileList("(!!!) AUTO-SERVER-REBOOTING!");
				bInit();
				m_iAutoRebootingCount++;
			}
			else {
				if (m_iFinalShutdownCount == 0)	m_iFinalShutdownCount = 20;
			}
		}
		m_dwExitProcessTime = dwTime;
	}

	if ((dwTime - m_dwMapSectorInfoTime) > 10000) {
		
		MineralGenerator();
		
		m_dwMapSectorInfoTime = dwTime;
	}
}

void CGame::SendThunders()
{

	for (int i = 0; i < DEF_MAXMAPS; i++)
		if (m_pMapList[i] != NULL)
			if (m_pMapList[i]->m_cWhetherStatus == 2 || m_pMapList[i]->m_cWhetherStatus == 3)
				DoAbaddonThunderDamageHandler(i);
}

/*********************************************************************************************************************
**  void CGame::OnTimer(char cType)																					**
**  DESCRIPTION			:: events occuring indefinately while a player is connected									**
**  LAST_UPDATED		:: March 17, 2005; 2:24 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- changed autosave message to log server's bFlag to TRUE								**
**							- increased exp gained in autoexp. now level rather than level/2						**
**							- recall player if crusade is false and is a civilian inside a combatant only zone		**
**							- simplified alot of tasks to improve serverside latency								**
**	MODIFICATION		::  - includes link to _bCheckCharacterData to check for inconsistancies (see that function)**
**********************************************************************************************************************/
void CGame::CheckClientResponseTime()
{
 int i, iPlusTime, iMaxSuperAttack;
 short sTemp;
 DWORD dwTime;
 short sItemIndex;

	dwTime = timeGetTime();
	for (i = 1; i < DEF_MAXCLIENTS; i++) {
		if (m_pClientList[i] != NULL) {		
			if ((dwTime - m_pClientList[i]->m_dwTime) > DEF_CLIENTTIMEOUT ) {
				if (m_pClientList[i]->m_bIsInitComplete == TRUE) {
					wsprintf(G_cTxt, "Client Timeout: %s", m_pClientList[i]->m_cIPaddress);
					PutLogList(G_cTxt);
					DeleteClient(i, TRUE, TRUE, TRUE, FALSE);
				}
				else if ((dwTime - m_pClientList[i]->m_dwTime) > DEF_CLIENTTIMEOUT) {
					DeleteClient(i, FALSE, FALSE, TRUE, FALSE);
				}
			}
			else if (m_pClientList[i]->m_bIsInitComplete == TRUE) {
				m_pClientList[i]->m_iTimeLeft_ShutUp--;
				if (m_pClientList[i]->m_iTimeLeft_ShutUp < 0) m_pClientList[i]->m_iTimeLeft_ShutUp = 0;
				m_pClientList[i]->m_iTimeLeft_Rating--;
				if (m_pClientList[i]->m_iTimeLeft_Rating < 0) m_pClientList[i]->m_iTimeLeft_Rating = 0;
				
				if (((dwTime - m_pClientList[i]->m_dwHungerTime) > DEF_HUNGERTIME) && (m_pClientList[i]->m_bIsKilled == FALSE)) {
					if ((m_pClientList[i]->m_iLevel > DEF_LEVELLIMIT) && (m_pClientList[i]->m_iAdminUserLevel < 1 )) 
					
					{
						m_pClientList[i]->m_iHungerStatus--;
						SendNotifyMsg(NULL, i, DEF_NOTIFY_HUNGER, m_pClientList[i]->m_iHungerStatus, NULL, NULL, NULL); // MORLA2 - Muestra el hunger status
					}
					if (m_pClientList[i]->m_iHungerStatus <= 0) m_pClientList[i]->m_iHungerStatus = 0;
					m_pClientList[i]->m_dwHungerTime = dwTime;
					
					if ( (m_pClientList[i]->m_iHP > 0) && (m_pClientList[i]->m_iHungerStatus < 100) ) { // MORLA2 - Para que informe el hunger constantemente
						SendNotifyMsg(NULL, i, DEF_NOTIFY_HUNGER, m_pClientList[i]->m_iHungerStatus, NULL, NULL, NULL);
					}
				}

				/*****MODIFICATION*****/
				// checks all player data for general and packet errors
				if (_bCheckCharacterData(i) == FALSE) {
					DeleteClient(i, TRUE, TRUE);
					break;	
				}
				/*********END**********/
				// Snoopy added Tile where you can't stay (behind crusade structures)
				if (   (m_bIsCrusadeMode == TRUE)
					&& (m_pClientList[i]->m_iAdminUserLevel == 0)
					&& (m_pMapList[m_pClientList[i]->m_cMapIndex]->bGetIsStayAllowedTile(m_pClientList[i]->m_sX, m_pClientList[i]->m_sY) == FALSE))
				{	char iDir = (char)iDice(1,7);
					if (iDir >= 5) iDir++;
					int iDamage = m_pClientList[i]->m_iHP/8 + iDice(1,20);					
					if (iDamage < 40) iDamage = 30 + iDice(1,20);
					if (iDamage > m_pClientList[i]->m_iHP) iDamage = m_pClientList[i]->m_iHP -1;
					m_pClientList[i]->m_iHP -= iDamage;					
					m_pClientList[i]->m_iLastDamage = iDamage;		
					m_pClientList[i]->m_dwRecentAttackTime = dwTime;
					SendNotifyMsg(NULL, i, DEF_NOTIFY_DAMAGEMOVE, iDir, iDamage, 0, NULL);
				}
				if ((m_pClientList[i]->m_iHungerStatus <= 40) && (m_pClientList[i]->m_iHungerStatus >= 0)) 
					iPlusTime = (40 - m_pClientList[i]->m_iHungerStatus)*1000;
				else iPlusTime = 0;
				iPlusTime = abs(iPlusTime);
				if ((dwTime - m_pClientList[i]->m_dwHPTime) > (DWORD)(DEF_HPUPTIME + iPlusTime)) {
					TimeHitPointsUp(i);
					m_pClientList[i]->m_dwHPTime = dwTime;
				}
				if ((dwTime - m_pClientList[i]->m_dwMPTime) > (DWORD)(DEF_MPUPTIME + iPlusTime)) {
					TimeManaPointsUp(i);
					m_pClientList[i]->m_dwMPTime = dwTime;
				}
				if ((dwTime - m_pClientList[i]->m_dwSPTime) > (DWORD)(DEF_SPUPTIME + iPlusTime)) {
					TimeStaminarPointsUp(i);
					m_pClientList[i]->m_dwSPTime = dwTime;
				}
				if ((m_pClientList[i]->m_bIsPoisoned == TRUE) && ((dwTime - m_pClientList[i]->m_dwPoisonTime) > DEF_POISONTIME)) {
					PoisonEffect(i, NULL);
					m_pClientList[i]->m_dwPoisonTime = dwTime;
				}
				if ((m_pMapList[m_pClientList[i]->m_cMapIndex]->m_bIsFightZone == FALSE) &&	((dwTime - m_pClientList[i]->m_dwAutoSaveTime) > (DWORD)DEF_AUTOSAVETIME)) {
					bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA, i, TRUE); 
					m_pClientList[i]->m_dwAutoSaveTime = dwTime;
				}
				if ((dwTime - m_pClientList[i]->m_dwExpStockTime) > (DWORD)DEF_EXPSTOCKTIME) {
					m_pClientList[i]->m_dwExpStockTime = dwTime;
					
					CheckUniqueItemEquipment(i);
					CheckCrusadeResultCalculation(i);
					CheckHeldenianResultCalculation(i); // new
				}
				
				// SNOOPY: Added shinning DemonSlayer if Demon/GG around
				sItemIndex = m_pClientList[i]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];	
				if(sItemIndex != -1) 
				{	if(m_pClientList[i]->m_pItemList[sItemIndex]->m_sIDnum == 616)   // DS equiped
					{	if(SpecialWeapon_DS(i) == true )
						{	sTemp = m_pClientList[i]->m_sAppr4;
							sTemp = sTemp | 0x0004;		
						}else
						{	sTemp = m_pClientList[i]->m_sAppr4;
							sTemp = sTemp & 0xFFFB;					
						}
						if (m_pClientList[i]->m_sAppr4 != sTemp) // has changed
						{	m_pClientList[i]->m_sAppr4 = sTemp;
							SendEventToNearClient_TypeA(i, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
				}	}	}
				if (m_pClientList[i]->m_iSpecialAbilityTime == 3) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_SPECIALABILITYENABLED, NULL, NULL, NULL, NULL);
					sItemIndex = m_pClientList[i]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
					if (sItemIndex != -1) {
						if ((m_pClientList[i]->m_pItemList[sItemIndex]->m_sIDnum == 865) || (m_pClientList[i]->m_pItemList[sItemIndex]->m_sIDnum == 866)) {
							if(((m_pClientList[i]->m_iInt+m_pClientList[i]->m_iAngelicInt) > 99) && ((m_pClientList[i]->m_iMag+m_pClientList[i]->m_iAngelicMag) > 99)){
								m_pClientList[i]->m_cMagicMastery[94] = TRUE;
								SendNotifyMsg(NULL, i, DEF_NOTIFY_RESUR_ON, NULL, NULL, NULL, NULL);
							}
						}
					}
				}
				m_pClientList[i]->m_iSpecialAbilityTime -= 3;
				if (m_pClientList[i]->m_iSpecialAbilityTime < 0) m_pClientList[i]->m_iSpecialAbilityTime = 0;
				if (m_pClientList[i]->m_bIsSpecialAbilityEnabled == TRUE) {
					if (((dwTime - m_pClientList[i]->m_dwSpecialAbilityStartTime)/1000) > m_pClientList[i]->m_iSpecialAbilityLastSec) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_SPECIALABILITYSTATUS, 3, NULL, NULL, NULL);
						m_pClientList[i]->m_bIsSpecialAbilityEnabled = FALSE;
						m_pClientList[i]->m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC;
						sTemp = m_pClientList[i]->m_sAppr4;
						sTemp = 0xFF0F & sTemp;
						m_pClientList[i]->m_sAppr4 = sTemp;
						SendEventToNearClient_TypeA(i, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
					}
				}
				m_pClientList[i]->m_iLockedMapTime -= 3;
				if (m_pClientList[i]->m_iLockedMapTime < 0) {
					m_pClientList[i]->m_iLockedMapTime = 0;
					ZeroMemory(m_pClientList[i]->m_cLockedMapName, sizeof(m_pClientList[i]->m_cLockedMapName));
					strcpy(m_pClientList[i]->m_cLockedMapName, "NONE");
				}
				// changed to include ImpossibleZone recall
				m_pClientList[i]->m_iDeadPenaltyTime -= 3;
				if (m_pClientList[i]->m_iDeadPenaltyTime < 0) m_pClientList[i]->m_iDeadPenaltyTime = 0;	
				if (m_pClientList[i]->m_bIsWarLocation == TRUE) {
					if ((m_bIsCrusadeMode != FALSE) && (m_pClientList[i]->m_bIsInsideEnemyBuilding == TRUE)) {
						m_pClientList[i]->m_iTimeLeft_ForceRecall--;
						if (m_pClientList[i]->m_iTimeLeft_ForceRecall <= 0) {
							m_pClientList[i]->m_iTimeLeft_ForceRecall = 0;
							m_pClientList[i]->m_dwWarBeginTime = dwTime;
							m_pClientList[i]->m_bIsWarLocation = FALSE;
							SendNotifyMsg(NULL, i, DEF_NOTIFY_TOBERECALLED, NULL, NULL, NULL, NULL);
							RequestTeleportHandler(i, "0   ");
						}
					}
					if (m_pClientList[i]->m_bIsImpossibleZone == TRUE) {
						m_pClientList[i]->m_iTimeLeft_ForceRecall--;
						if (m_pClientList[i]->m_iTimeLeft_ForceRecall <= 0) {
							m_pClientList[i]->m_iTimeLeft_ForceRecall = 0;
							m_pClientList[i]->m_bIsImpossibleZone = FALSE;
							SendNotifyMsg(NULL, i, DEF_NOTIFY_TOBERECALLED, NULL, NULL, NULL, NULL);
							RequestTeleportHandler(i, "0   ");
						}
					}
				}
				// Every 3 seconds, give Hero flag effect if Flag set arround...
				if (   (m_bHeldenianWarInitiated == TRUE)
					&& (bCheckHeldenianMap(i, DEF_OWNERTYPE_PLAYER) == 1)) 
				{		SetHeroFlag(i, DEF_OWNERTYPE_PLAYER, TRUE);
				}else 
				{		SetHeroFlag(i, DEF_OWNERTYPE_PLAYER, FALSE);
				}

				
				if (m_pClientList[i]->m_iSkillMsgRecvCount >= 2) {
					DeleteClient(i, TRUE, TRUE, TRUE, FALSE);
				}
				else {
					m_pClientList[i]->m_iSkillMsgRecvCount = 0;
				}

				if ((m_pClientList[i]->m_iLevel < m_pMapList[m_pClientList[i]->m_cMapIndex]->m_iLevelLimit) && 
					(m_pClientList[i]->m_iAdminUserLevel < 1)) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_TOBERECALLED, NULL, NULL, NULL, NULL);
					RequestTeleportHandler(i, "0   ");
				}

				if ((m_pMapList[m_pClientList[i]->m_cMapIndex]->m_iUpperLevelLimit != 0) &&
					(m_pClientList[i]->m_iLevel > m_pMapList[m_pClientList[i]->m_cMapIndex]->m_iUpperLevelLimit) && 
					(m_pClientList[i]->m_iAdminUserLevel < 1)) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_TOBERECALLED, NULL, NULL, NULL, NULL);
					RequestTeleportHandler(i, "0   ");
				}

				// new - recall player if crusade is false and is a civilian inside a combatant only zone
				
				if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[i]->m_bIsInCombatantOnlyZone == TRUE) && (m_pMapList[i]->m_bIsCitizenLimit == TRUE)) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_TOBERECALLED, NULL, NULL, NULL, NULL);
					RequestTeleportHandler(i, "0   ");

				}

				// KaoZureS - Heldenian Maps Auto Recall
				
				if ((m_bIsHeldenianMode == FALSE) &&
				((memcmp(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_cName, "BtField", 7) == 0) ||
				(memcmp(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_cName, "GodH", 4) == 0) ||
				(memcmp(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_cName, "HRampart", 8) == 0)) &&
				(m_pClientList[i]->m_cSide != m_sLastHeldenianWinner) && (m_pClientList[i]->m_iAdminUserLevel == 0)) {
					if (m_pClientList[i]->m_cSide == 1) {
						RequestTeleportHandler(i, "2   ", "aresden", -1, -1); }
					else { RequestTeleportHandler(i, "2   ", "elvine", -1, -1); }
				}

				// Recall clients from apocalypse map if not Apocalypse time
				
				if (   (m_pMapList[m_pClientList[i]->m_cMapIndex]->m_bIsApocalypseMap == TRUE) 
					&& (m_bIsApocalypseMode == FALSE)
					&& (m_pClientList[i]->m_iAdminUserLevel == 0))
				{	m_pClientList[i]->m_bIsWarLocation = TRUE;
					m_pClientList[i]->m_iTimeLeft_ForceRecall = 0;				
				}


				// SNOOPY:added Apoc teleport Gates here		
				Use_ApocalypseGate(i);
				
			
				m_pClientList[i]->m_iSuperAttackCount++;
				if (m_pClientList[i]->m_iSuperAttackCount > 12) 
				{
					m_pClientList[i]->m_iSuperAttackCount = 0;
					iMaxSuperAttack = ((m_pClientList[i]->m_iLevel + m_pClientList[i]->m_iMajesticLevel) / 10);
					if (m_pClientList[i]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[i]->m_iSuperAttackLeft++;
					SendNotifyMsg(NULL, i, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
				}
				
				
				m_pClientList[i]->m_iTimeLeft_FirmStaminar--;
				if (m_pClientList[i]->m_iTimeLeft_FirmStaminar < 0) m_pClientList[i]->m_iTimeLeft_FirmStaminar = 0;
				
				if (m_pClientList[i]->m_bIsSendingMapStatus == TRUE) _SendMapStatus(i);
				if (m_pClientList[i]->m_iConstructionPoint > 0) {
					CheckCommanderConstructionPoint(i);
				}
			}
		}
	}
}

/*********************************************************************************************************************
**  void CGame::OnMainLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam)									**
**  DESCRIPTION			:: main log socket connection manager														**
**  LAST_UPDATED		:: March 17, 2005; 4:41 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- removed DEF_XSOCKEVENT_BLOCK															**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
void CGame::OnMainLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
 int   iRet;
	
	if (m_pMainLogSock == NULL) return;
	iRet = m_pMainLogSock->iOnSocketEvent(wParam, lParam);
	switch (iRet) {
	case DEF_XSOCKEVENT_CONNECTIONESTABLISH:
		PutLogList("(!!!) Main-log-socket connected!");
		break;
		
	case DEF_XSOCKEVENT_READCOMPLETE:
		OnMainLogRead();
		break;

	case DEF_XSOCKEVENT_CONFIRMCODENOTMATCH:
	case DEF_XSOCKEVENT_MSGSIZETOOLARGE:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		delete m_pMainLogSock;
		m_pMainLogSock = NULL;
		PutLogList("(!!!) Main-log-socket connection lost!");
		m_bIsLogSockAvailable = FALSE;
		if (m_bOnExitProcess == FALSE) {
			m_cShutDownCode      = 3;
			m_bOnExitProcess     = TRUE;
			m_dwExitProcessTime  = timeGetTime();
			PutLogList("(!!!) GAME SERVER SHUTDOWN PROCESS BEGIN(by main-log-socket connection Lost)!!!");
		}
		break;
	}
}

/*********************************************************************************************************************
**  void CGame::OnMainLogRead()																						**
**  DESCRIPTION			:: report critical error if mainlog isn't available											**
**  LAST_UPDATED		:: March 17, 2005; 4:42 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	n/a																						**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
void CGame::OnMainLogRead()
{
 DWORD dwMsgSize;
 char * pData, cKey;

	pData = m_pMainLogSock->pGetRcvDataPointer(&dwMsgSize, &cKey);

	if (bPutMsgQuene(DEF_MSGFROM_LOGSERVER, pData, dwMsgSize, NULL, cKey) == FALSE) {
		PutLogList("@@@@@@ CRITICAL ERROR in MsgQuene!!! (OnMainLogRead) @@@@@@");
	}	
}


BOOL CGame::bSendMsgToLS(DWORD dwMsg, int iClientH, BOOL bFlag, char* pData)
{
 DWORD * dwp;
 WORD  * wp;
 int     iRet, i, iSize;
 char    cCharName[12], cAccountName[11], cAccountPassword[11], cAddress[16], cGuildName[21], cTxt[120], * cp;
 char    cGuildLoc[11], cTemp[120];
 int   * ip, iSendSize;	

	// v1.41
	ZeroMemory(G_cData50000, sizeof(G_cData50000));
	ZeroMemory(cCharName, sizeof(cCharName));
	ZeroMemory(cAccountName, sizeof(cAccountName));
	ZeroMemory(cAccountPassword, sizeof(cAccountPassword));
	ZeroMemory(cAddress,   sizeof(cAddress));
	ZeroMemory(cGuildName, sizeof(cGuildName));
	ZeroMemory(cGuildLoc,  sizeof(cGuildLoc));

	switch (dwMsg) {
	case MSGID_SENDSERVERSHUTDOWNMSG:
		if (m_pMainLogSock == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_SENDSERVERSHUTDOWNMSG;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		iRet = m_pMainLogSock->iSendMsg(G_cData50000, 6);
		break;

	case MSGID_REQUEST_CREATENEWGUILD:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;	
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_CREATENEWGUILD;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cAccountName, m_pClientList[iClientH]->m_cAccountName, 10);
		memcpy(cAccountPassword, m_pClientList[iClientH]->m_cAccountPassword, 10);
		memcpy(cGuildName, m_pClientList[iClientH]->m_cGuildName, 20);
		memcpy(cGuildLoc, m_pClientList[iClientH]->m_cLocation, 10);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountPassword, 10);
		cp += 10;
		memcpy((char *)cp, cGuildName, 20);
		cp += 20;
		memcpy((char *)cp, cGuildLoc, 10);
		cp += 10;
		ip = (int *)cp;
		*ip = m_pClientList[iClientH]->m_iGuildGUID;
		cp += 4;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 75);
		iSendSize = 75;
		break;

	case MSGID_REQUEST_SAVEPLAYERDATA_REPLY:
	case MSGID_REQUEST_SAVEPLAYERDATA:
	case MSGID_REQUEST_SAVEPLAYERDATALOGOUT:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;		
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = dwMsg;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cAccountName, m_pClientList[iClientH]->m_cAccountName, 10);
		memcpy(cAccountPassword, m_pClientList[iClientH]->m_cAccountPassword, 10);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountPassword, 10);
		cp += 10;

#ifdef DEF_DBGAMESERVER
		// v2.14 DB 저장 속도 향상 
		dwp = (DWORD*)cp;
		*dwp = m_pClientList[iClientH]->m_dwCharID;
		cp += 4;
#endif
		*cp = (char)bFlag;
		cp++;
		iSize = _iComposePlayerDataFileContents(iClientH, cp);

		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 41 + iSize);
		iSendSize = 41 + iSize;

		break;
		
	case MSGID_GAMEMASTERLOG:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		if (pData == NULL) return FALSE ;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_GAMEMASTERLOG;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		iSize =  strlen(pData) ;
		memcpy((char *)cp, pData, iSize);
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 6 + iSize);
		iSendSize = 6 + iSize;
		break;

	case MSGID_GAMEITEMLOG:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (pData == NULL) return FALSE ;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_GAMEITEMLOG;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		iSize =  strlen(pData) ;
		memcpy((char *)cp, pData, iSize);
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 6 + iSize);
		iSendSize = 6 + iSize;
		break;

	
	case MSGID_GAMESERVERSHUTDOWNED:
		if (m_pMainLogSock == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_GAMESERVERSHUTDOWNED;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		iRet = m_pMainLogSock->iSendMsg(G_cData50000, 6);
		iSendSize = 6;
		break;

	case MSGID_REQUEST_SETACCOUNTWAITSTATUS:
	case MSGID_REQUEST_SETACCOUNTINITSTATUS:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = dwMsg;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cp, m_pClientList[iClientH]->m_cAccountName, 10);
		cp += 10;
		ip = (int *)cp;
		*ip = m_pClientList[iClientH]->m_iLevel;
		cp += 4;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 20);
		iSendSize = 20; // 16
		break;

	case MSGID_ENTERGAMECONFIRM:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_ENTERGAMECONFIRM;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cp, m_pClientList[iClientH]->m_cAccountName, 10);
		cp += 10;
		memcpy(cp, m_pClientList[iClientH]->m_cAccountPassword, 10);
		cp += 10;
		memcpy(cp, m_cServerName, 10);
		cp += 10;
		ZeroMemory(cTxt, sizeof(cTxt));
		m_pClientList[iClientH]->m_pXSock->iGetPeerAddress(cTxt);
		memcpy(cp, cTxt, 16);
		cp += 16;
		ip = (int *)cp;
		*ip = m_pClientList[iClientH]->m_iLevel;
		cp += 4;
		wsprintf(G_cTxt, "Confirmed. Account: (%s) Name: (%s) Level: (%d)", m_pClientList[iClientH]->m_cAccountName, m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iLevel);
		PutLogList(G_cTxt);

		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 56);
		iSendSize = 56;
		break;
	
	case MSGID_REQUEST_REGISTERGAMESERVER:
		if (m_pMainLogSock == NULL) return FALSE;		
		wsprintf(cTxt, "(!) Try to register game server(%s)", m_cServerName);
		PutLogList(cTxt);
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_REGISTERGAMESERVER;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cAccountName, m_cServerName, 10);
		if (m_iGameServerMode == 1)	{
			memcpy(cAddress, m_cGameServerAddrExternal, strlen(m_cGameServerAddrExternal));
		}
		else if (m_iGameServerMode == 2)	{
			memcpy(cAddress, m_cGameServerAddr, strlen(m_cGameServerAddr));
		}
		memcpy(cp, cAccountName, 10);
		cp += 10;
		memcpy(cp, cAddress, 16);
		cp += 16;
		wp  = (WORD *)cp;
		*wp = m_iGameServerPort;
		cp += 2;
		*cp = m_iTotalMaps;
		cp++;
		
		for (i = 0; i < m_iTotalMaps; i++) {
			memcpy(cp, m_pMapList[i]->m_cName, 11);
			cp += 11;
		}
		iRet = m_pMainLogSock->iSendMsg(G_cData50000, 35 + m_iTotalMaps*11);
		
		iSendSize = 35 + m_iTotalMaps * 11;
		break;

	case MSGID_REQUEST_PLAYERDATA:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_PLAYERDATA;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		if (strlen(m_pClientList[iClientH]->m_cCharName) == 0) PutLogList("(X) CharName NULL!");
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cAccountName, m_pClientList[iClientH]->m_cAccountName, 10);
		memcpy(cAccountPassword, m_pClientList[iClientH]->m_cAccountPassword, 10);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountPassword, 10);
		cp += 10;
		ZeroMemory(cTemp, sizeof(cTemp));
		iRet = m_pClientList[iClientH]->m_pXSock->iGetPeerAddress(cTemp);
		memcpy((char *)cp, cTemp, 15);
		cp += 15;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 52);
		iSendSize = 52;
		break;

	case MSGID_REQUEST_NOSAVELOGOUT:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_NOSAVELOGOUT;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cAccountName, m_pClientList[iClientH]->m_cAccountName, 10);
		memcpy(cAccountPassword, m_pClientList[iClientH]->m_cAccountPassword, 10);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountPassword, 10);
		cp += 10;
		*cp = (char)bFlag;
		cp++;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 37);
		iSendSize = 37;
		break;

	case MSGID_REQUEST_DISBANDGUILD:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_DISBANDGUILD;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cAccountName, m_pClientList[iClientH]->m_cAccountName, 10);
		memcpy(cAccountPassword, m_pClientList[iClientH]->m_cAccountPassword, 10);
		memcpy(cGuildName, m_pClientList[iClientH]->m_cGuildName, 20);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountName, 10);
		cp += 10;
		memcpy((char *)cp, cAccountPassword, 10);
		cp += 10;
		memcpy((char *)cp, cGuildName, 20);
		cp += 20;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 56);
		iSendSize = 56;
		break;

	case MSGID_3D001242h:
	case MSGID_3D00123Eh:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_3D001242h;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 6);
		iSendSize = 6;
		break;
		
	case MSGID_REQUEST_HELDENIAN_WINNER: // Sub-log-socket	
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;		
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_HELDENIAN_WINNER;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		if (m_cHeldenianWinner == 1)
			memcpy(cp, "aresden", 7);
		else if (m_cHeldenianWinner == 2)
			memcpy(cp, "elvine", 6);
		else 
			memcpy(cp, "draw", 4);
		cp += 7;
		ip = (int *)cp;
		ip = (int *)m_dwHeldenianWarStartTime;
		cp += 4;
		ip = (int *)cp;
		ip = (int *)m_dwHeldenianFinishTime;
		cp += 4;
		ip = (int *)cp;
		ip = (int *)m_cHeldenianType;
		cp += 4;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 21);
		iSendSize = 21;
		break;
	
	case MSGID_REQUEST_UPDATEGUILDINFO_NEWGUILDSMAN:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_UPDATEGUILDINFO_NEWGUILDSMAN;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cGuildName, m_pClientList[iClientH]->m_cGuildName, 20);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cGuildName, 20);
		cp += 20;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 36);
		iSendSize = 36;
		break;

	case MSGID_REQUEST_UPDATEGUILDINFO_DELGUILDSMAN:
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		dwp  = (DWORD *)(G_cData50000 + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_UPDATEGUILDINFO_DELGUILDSMAN;
		wp   = (WORD *)(G_cData50000 + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		cp = (char *)(G_cData50000 + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cCharName, m_pClientList[iClientH]->m_cCharName, 10);
		memcpy(cGuildName, m_pClientList[iClientH]->m_cGuildName, 20);
		memcpy((char *)cp, cCharName, 10);
		cp += 10;
		memcpy((char *)cp, cGuildName, 20);
		cp += 20;
		iRet = m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, 36);
		iSendSize = 36;
		break;
	}

	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		wsprintf(G_cTxt, "(!!!) Sub-log-socket(%d) send error!", m_iCurSubLogSockIndex);
		PutLogList(G_cTxt);
		PutLogFileList(G_cTxt);
		delete m_pSubLogSock[m_iCurSubLogSockIndex];
		m_pSubLogSock[m_iCurSubLogSockIndex] = NULL;
		m_bIsSubLogSockAvailable[m_iCurSubLogSockIndex] = FALSE;
		m_iSubLogSockActiveCount--;
		m_pSubLogSock[m_iCurSubLogSockIndex] = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
		m_pSubLogSock[m_iCurSubLogSockIndex]->bConnect(m_cLogServerAddr, m_iLogServerPort, (WM_ONLOGSOCKETEVENT + m_iCurSubLogSockIndex + 1));
		m_pSubLogSock[m_iCurSubLogSockIndex]->bInitBufferSize(DEF_MSGBUFFERSIZE);
		wsprintf(G_cTxt, "(!) Try to reconnect sub-log-socket(%d)... Addr:%s  Port:%d", m_iCurSubLogSockIndex, m_cLogServerAddr, m_iLogServerPort);
		PutLogList(G_cTxt);		
		m_iSubLogSockFailCount++;
		if (_bCheckSubLogSocketIndex() == FALSE) return FALSE;
		m_pSubLogSock[m_iCurSubLogSockIndex]->iSendMsg(G_cData50000, iSendSize);
		return FALSE;
	}

	return TRUE;
}

/*********************************************************************************************************************
**  void CGame::ResponsePlayerDataHandler(char * pData, DWORD dwSize)												**
**  DESCRIPTION			:: action taken following player login														**
**  LAST_UPDATED		:: March 17, 2005; 6:24 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- new code inside LOGRESMSGTYPE_REJECT 													**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
void CGame::ResponsePlayerDataHandler(char * pData, DWORD dwSize)
{
 char * cp, cCharName[11], cTxt[120], cData[120];
 int  i; 
 DWORD * dwp;
 WORD  * wp;
 
	// centu - fix for wl src
	if (dwSize >= DEF_MSGBUFFERSIZE+1) return;

	ZeroMemory(cCharName, sizeof(cCharName));
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cCharName, cp, 10);
	cp += 10;
	for (i = 1; i < DEF_MAXCLIENTS; i++) 
	if (m_pClientList[i] != NULL) {
		if (memcmp(m_pClientList[i]->m_cCharName, cCharName, 10) == 0) {
			wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
			switch (*wp) {
			case DEF_LOGRESMSGTYPE_CONFIRM:
				InitPlayerData(i, pData, dwSize); 
				break;
	
			case DEF_LOGRESMSGTYPE_REJECT:
				// new
				
					ZeroMemory(cData, sizeof(cData));
					dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
					*dwp = MSGID_RESPONSE_INITPLAYER;
					wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
					*wp  = DEF_MSGTYPE_CONFIRM;
					m_pClientList[i]->m_pXSock->iSendMsg(cData, 6);
				
				// end
				wsprintf(G_cTxt, "(HACK?) Not existing character(%s) data request! Rejected!", m_pClientList[i]->m_cCharName);
				PutLogList(G_cTxt);
				DeleteClient(i, FALSE, FALSE, TRUE, FALSE);
				break;
			
			default:
				break;
			}				
			return;
		}	
	}
	wsprintf(cTxt, "(!)Non-existing player data received from Log server: CharName(%s)", cCharName);
	PutLogList(cTxt);
}

/*********************************************************************************************************************
**  BOOL CGame::bReadProgramConfigFile(char * cFn)																	**
**  DESCRIPTION			:: function that reads GServer.cfg															**
**  LAST_UPDATED		:: March 17, 2005; 12:09 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- with DMZ walkaround is internet and lan option necissary?								**
**							- does dns work? (unable to test)														**
**	MODIFICATION		::	- game-server-internal-address (internal lan ip address)								**
**							- game-server-external-address (DNS Server)												**
**							- game-server-mode (if inside LAN put "LAN" if not put "INTERNET" (without quotes)		**
**							- gate-server-dns (if set to "true" put in alphabetical dns address)					**
**							- log-server-dns (both dns options benefitial if ip is dynamic and server is no-ip.com	**
**********************************************************************************************************************/
BOOL CGame::bReadProgramConfigFile(char * cFn)
{	
	FILE * pFile;
	HANDLE hFile;
	DWORD  dwFileSize;
	char * cp, * token, cReadMode, cTxt[120], cGSMode[16] = "";
	char seps[] = "= \t\n";	
	class CStrTok * pStrTok;

	cReadMode = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen(cFn, "rt");
	if (pFile != NULL) {
	
		PutLogList("(!) Reading configuration file...");
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();
		while( token != NULL )   {

			if (cReadMode != 0) {
				switch (cReadMode) {
				case 1:
					if (strlen(token) > 10) {
						wsprintf(cTxt, "(!!!) Game server name(%s) must within 10 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cServerName, token);
					wsprintf(cTxt, "(*) Game server name : %s", m_cServerName);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 2:
					
					m_iGameServerPort = atoi(token);
					wsprintf(cTxt, "(*) Game server port : %d", m_iGameServerPort);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 5:
					if (strlen(token) > 10) {
						wsprintf(cTxt, "(!!!) CRITICAL ERROR! Map name(%s) must within 10 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					if (_bRegisterMap(token) == FALSE) {
						return FALSE;
					}
					cReadMode = 0;
					break;

				
				}
			}
			else {
				if (memcmp(token, "game-server-name", 16) == 0)					cReadMode = 1;
				if (memcmp(token, "game-server-port", 16) == 0)					cReadMode = 2;
				
				if (memcmp(token, "game-server-map", 15) == 0)					cReadMode = 5;
				

			}
			token = pStrTok->pGet();
		}
		delete pStrTok;
		fclose(pFile);
		return TRUE;
	}

	return FALSE;
}

BOOL CGame::bReadProgramConfigFile2(char* cFn)
{
	FILE* pFile;
	HANDLE hFile;
	DWORD  dwFileSize;
	char* cp, * token, cReadMode, cTxt[120], cGSMode[16] = "";
	char seps[] = "= \t\n";
	class CStrTok* pStrTok;

	cReadMode = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
	pFile = fopen(cFn, "rt");
	if (pFile != NULL) {

		PutLogList("(!) Reading configuration file...");
		cp = new char[dwFileSize + 2];
		ZeroMemory(cp, dwFileSize + 2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();
		while (token != NULL) {

			if (cReadMode != 0) {
				switch (cReadMode) {

				case 3:
					ZeroMemory(m_cLogServerAddr, sizeof(m_cLogServerAddr));
					if (strlen(token) > 15) {
						wsprintf(cTxt, "(!!!) Log server address(%s) must within 15 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cLogServerAddr, token);
					wsprintf(cTxt, "(*) Log server address : %s", m_cLogServerAddr);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 4:
					m_iLogServerPort = atoi(token);
					wsprintf(cTxt, "(*) Log server port : %d", m_iLogServerPort);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 6:
					ZeroMemory(m_cGateServerAddr, sizeof(m_cGateServerAddr));

					if (strlen(token) > 15) {
						wsprintf(cTxt, "(!!!) Gate server address(%s) must within 15 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cGateServerAddr, token);
					wsprintf(cTxt, "(*) Gate server address : %s", m_cGateServerAddr);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 7:
					m_iGateServerPort = atoi(token);
					wsprintf(cTxt, "(*) Gate server port : %d", m_iGateServerPort);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 8:
					ZeroMemory(m_cGameServerAddrInternal, sizeof(m_cGameServerAddrInternal));
					if (strlen(token) > 15) {
						wsprintf(cTxt, "(!!!) Internal (LAN) Game server address(%s) must within 15 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cGameServerAddrInternal, token);
					wsprintf(cTxt, "(*) Internal (LAN) Game server address : %s", m_cGameServerAddrInternal);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 9:
					ZeroMemory(m_cGameServerAddrExternal, sizeof(m_cGameServerAddrExternal));
					if (strlen(token) > 15) {
						wsprintf(cTxt, "(!!!) External (Internet) Game server address(%s) must within 15 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cGameServerAddrExternal, token);
					wsprintf(cTxt, "(*) External (Internet) Game server address : %s", m_cGameServerAddrExternal);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 10:
					ZeroMemory(m_cGameServerAddr, sizeof(m_cGameServerAddr));
					if (strlen(token) > 15) {
						wsprintf(cTxt, "(!!!) Game server address(%s) must within 15 chars!", token);
						PutLogList(cTxt);
						return FALSE;
					}
					strcpy(m_cGameServerAddr, token);
					wsprintf(cTxt, "(*) Game server address : %s", m_cGameServerAddr);
					PutLogList(cTxt);
					cReadMode = 0;
					break;

				case 11:
					if ((memcmp(token, "lan", 3) == 0) || (memcmp(token, "LAN", 3) == 0))
					{
						m_iGameServerMode = 1;
						memcpy(cGSMode, "LAN", 3);
					}
					if ((memcmp(token, "internet", 8) == 0) || (memcmp(token, "INTERNET", 8) == 0))
					{
						m_iGameServerMode = 2;
						memcpy(cGSMode, "INTERNET", 8);
					}
					if (m_iGameServerMode == 0)
					{
						wsprintf(cTxt, "(!!!) Game server mode(%s) must be either LAN/lan/INTERNET/internet", token);
						PutLogList(cTxt);
						return FALSE;
					}
					else if (m_iGameServerMode == 1) // Default address is always internal in ROUTER mode
					{
						ZeroMemory(m_cGameServerAddr, sizeof(m_cGameServerAddr));
						strcpy(m_cGameServerAddr, m_cGameServerAddrInternal);
					}
					else if (m_iGameServerMode == 2) // Internal are always normal in INTERNET mode
					{
						ZeroMemory(m_cGameServerAddrInternal, sizeof(m_cGameServerAddrInternal));
						strcpy(m_cGameServerAddrInternal, m_cGameServerAddr);
						ZeroMemory(m_cGameServerAddrExternal, sizeof(m_cGameServerAddrExternal));
						strcpy(m_cGameServerAddrExternal, m_cGameServerAddr);
					}
					wsprintf(cTxt, "(*) Game server mode : %s", cGSMode);
					PutLogList(cTxt);
					cReadMode = 0;
					break;
				}
			}
			else {
				
				if (memcmp(token, "log-server-address", 18) == 0)				cReadMode = 3;
				if (memcmp(token, "internal-log-server-port", 24) == 0)			cReadMode = 4;
				
				if (memcmp(token, "gate-server-address", 19) == 0)				cReadMode = 6;
				if (memcmp(token, "gate-server-port", 16) == 0)					cReadMode = 7;

				if (memcmp(token, "game-server-internal-address", 28) == 0)		cReadMode = 8; // modification
				if (memcmp(token, "game-server-external-address", 28) == 0)		cReadMode = 9; // modification
				if (memcmp(token, "game-server-address", 19) == 0)				cReadMode = 10;// modification
				if (memcmp(token, "game-server-mode", 16) == 0)					cReadMode = 11;// modification

			}
			token = pStrTok->pGet();
		}
		delete pStrTok;
		fclose(pFile);
		return TRUE;
	}

	return FALSE;
}

/*********************************************************************************************************************
**  BOOL CGame::_bDecodePlayerDatafileContents(int iClientH, char * pData, DWORD dwSize)							**
**  DESCRIPTION			:: decodes <PLAYERNAME>.txt file in Character folder										**
**  LAST_UPDATED		:: March 17, 2005; 12:42 PM; Hypnotoad														**
**	RETURN_VALUE		:: BOOL																						**
**  NOTES				::	- MOST OF THIS FUNCTION UPGRADE IS IGNORED DUE TO MYSQL<->ASCII ISSUES					**
**							- changed stat point checks code														**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
#ifdef DEF_DBGAMESERVER
BOOL CGame::_bDecodePlayerDatafileContents(int iClientH, char* pData, DWORD dwSize)
{
	char  cTmpName[12], cTxt[120], cItemName[22];
	char* cp, cItemEquip, * pContents;
	int    i, iTotalGold, iNotUsedItemPrice;
	class  CStrTok* pStrTok;
	short  sTmpType, sTmpAppr1, sItemIndex, sItemInBankIndex, sSkillIndex, sSkillID;
	BOOL   bRet;
	short* sp;
	int    iTemp, * ip;
	SYSTEMTIME SysTime;
	__int64 iDateSum1, iDateSum2;
	BOOL   bIsNotUsedItemFound = FALSE;
	DWORD* dwp, dTemp;


	if (m_pClientList[iClientH] == NULL) return FALSE;

	// 소지품 검사용 
	iTotalGold = 0;
	sItemIndex = 0;
	sItemInBankIndex = 0;
	iNotUsedItemPrice = 0;

	cp = pData;

	// v2.14 DB 저장 속도 향상 
	dwp = (DWORD*)cp;
	m_pClientList[iClientH]->m_dwCharID = (DWORD)* dwp;
	cp += 4;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_sCharIDnum1 = *sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_sCharIDnum2 = *sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_sCharIDnum3 = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iLevel = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iStr = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iVit = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iDex = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iInt = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iMag = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iCharisma = (short)* sp;
	cp += 2;

	m_pClientList[iClientH]->m_iLuck = 10;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iExp = (int)* ip;
	cp += 4;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Str = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Vit = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Dex = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Int = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Mag = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cLU_Char = (short)* sp;
	cp += 2;

	m_pClientList[iClientH]->m_cSex = (char)* cp;
	cp++;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cSkin = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cHairStyle = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cHairColor = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_cUnderwear = (short)* sp;
	cp += 2;

	ip = (int*)cp;
	cp += 4;

	sp = (short*)cp;
	cp += 2;

	sp = (short*)cp;
	cp += 2;

	sp = (short*)cp;
	cp += 2;

	sp = (short*)cp;
	cp += 2;


	ZeroMemory(m_pClientList[iClientH]->m_cLocation, sizeof(m_pClientList[iClientH]->m_cLocation));
	memcpy(m_pClientList[iClientH]->m_cLocation, cp, 10);
	cp += 10;


	ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
	memcpy(m_pClientList[iClientH]->m_cMapName, cp, 10);
	ZeroMemory(cTmpName, sizeof(cTmpName));
	strcpy(cTmpName, m_pClientList[iClientH]->m_cMapName);

	for (i = 0; i < DEF_MAXMAPS; i++)
		if ((m_pMapList[i] != NULL) && (memcmp(m_pMapList[i]->m_cName, cTmpName, 10) == 0)) {
			// 맵의 인덱스는 i이다.
			m_pClientList[iClientH]->m_cMapIndex = (char)i;
		}

	if (m_pClientList[iClientH]->m_cMapIndex == -1) {
		// 만약 플레이어가 속한 맵이 존재하지 않는다면 (이런 경우는 발생하기 힘들다. 로그 서버에서 먼저 검색한 후 접속하기 때문)
		wsprintf(cTxt, "(!) Player(%s) tries to enter unknown map : %s", m_pClientList[iClientH]->m_cCharName, cTmpName);
		PutLogList(cTxt);
		return FALSE;
	}
	cp += 10;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_sX = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_sY = (short)* sp;
	cp += 2;

	ZeroMemory(m_pClientList[iClientH]->m_cProfile, sizeof(m_pClientList[iClientH]->m_cProfile));

	strcpy(m_pClientList[iClientH]->m_cProfile, cp);

	cp += 100;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iAdminUserLevel = (short)* sp;
	cp += 2;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iContribution = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iSpecialAbilityTime = (int)* ip;
	cp += 4;

	ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
	memcpy(m_pClientList[iClientH]->m_cLockedMapName, cp, 10);
	cp += 10;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iLockedMapTime = (int)* ip;
	cp += 4;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iPenaltyBlockYear = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iPenaltyBlockMonth = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iPenaltyBlockDay = (short)* sp;
	cp += 2;

	ZeroMemory(m_pClientList[iClientH]->m_cGuildName, sizeof(m_pClientList[iClientH]->m_cGuildName));
	memcpy(m_pClientList[iClientH]->m_cGuildName, cp, 20);
	cp += 20;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iGuildGUID = (int)* ip;
	cp += 4;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iGuildRank = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iFightzoneNumber = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iReserveTime = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iFightZoneTicketNumber = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iQuest = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iQuestID = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iCurQuestCount = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iQuestRewardType = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iQuestRewardAmount = (short)* sp;
	cp += 2;

	m_pClientList[iClientH]->m_bIsQuestCompleted = (BOOL)* cp;
	cp++;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iSpecialEventID = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iWarContribution = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iCrusadeDuty = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_dwCrusadeGUID = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iConstructionPoint = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iRating = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iHP = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iMP = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iSP = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iEnemyKillCount = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iPKCount = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iRewardGold = (int)* ip;
	cp += 4;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iHungerStatus = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	m_pClientList[iClientH]->m_iSuperAttackLeft = (short)* sp;
	cp += 2;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iTimeLeft_ShutUp = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iTimeLeft_Rating = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar = (int)* ip;
	cp += 4;

	ip = (int*)cp;
	m_pClientList[iClientH]->m_iDeadPenaltyTime = (int)* ip;
	cp += 4;

	// V2.1 성후니 파티제를 위해서 추가 
	ip = (int*)cp;
	m_pClientList[iClientH]->m_iPartyID = (int)* ip;
	cp += 4;

	// v2.15 지존 패치를 위해 추가 
	ip = (int*)cp;
	m_pClientList[iClientH]->m_iGizonItemUpgradeLeft = (int)* ip;
	cp += 4;

	ZeroMemory(m_pClientList[iClientH]->m_cMagicMastery, sizeof(m_pClientList[iClientH]->m_cMagicMastery));

	for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
		m_pClientList[iClientH]->m_cMagicMastery[i] = *cp - 48;
		cp++;
	}


	sp = (short*)cp;
	m_pClientList[iClientH]->m_iDownSkillIndex = (short)* sp;
	cp += 2;

	sp = (short*)cp;
	sSkillIndex = (short)* sp;
	cp += 2;

	for (i = 0; i < DEF_MAXSKILLTYPE; i++) {
		m_pClientList[iClientH]->m_cSkillMastery[i] = 0;
		m_pClientList[iClientH]->m_iSkillSSN[i] = 0;
	}

	for (i = 0; i < sSkillIndex; i++) {

		sp = (short*)cp;
		sSkillID = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_cSkillMastery[sSkillID] = (short)* sp;
		cp += 2;

		ip = (int*)cp;
		m_pClientList[iClientH]->m_iSkillSSN[sSkillID] = (int)* ip;
		cp += 4;

	}

	sp = (short*)cp;
	sItemIndex = (short)* sp;
	cp += 2;


	// 아이템 장착 상태 초기화한 후 설정한다.
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++)
		m_pClientList[iClientH]->m_sItemEquipmentStatus[i] = -1;

	// 아이템 장착상태를 초기화한다.
	for (i = 0; i < DEF_MAXITEMS; i++)
		m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;


	for (i = 0; i < sItemIndex; i++) {

		m_pClientList[iClientH]->m_pItemList[i] = new class CItem;

		ZeroMemory(cItemName, sizeof(cItemName));
		strcpy(cItemName, cp);

		if (_bInitItemAttr(m_pClientList[iClientH]->m_pItemList[i], cItemName) == FALSE) {
			// 플레이어가 소지한 아이템이 리스트에 없다. 에러
			wsprintf(cTxt, "(!!!) Client(%s)-Item(%s) is not existing Item! Conection closed.", m_pClientList[iClientH]->m_cCharName, cItemName);
			PutLogList(cTxt);

			return FALSE;
		}
		cp += 20;

		// 성후니 수정  
		dwp = (DWORD*)cp;
		dTemp = (DWORD)* dwp;

		if (dTemp < 0) dTemp = 1;
		//만약 중량이 초과되었다면 1개로 줄인다.

		if (iGetItemWeight(m_pClientList[iClientH]->m_pItemList[i], dTemp) > _iCalcMaxLoad(iClientH)) {
			dTemp = 1;
			wsprintf(G_cTxt, "(!) Character (%s) Item(%s) Counts have Overflow", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_pItemList[i]->m_cName);
			PutLogFileList(G_cTxt);
			PutLogList(G_cTxt);
		}

		m_pClientList[iClientH]->m_pItemList[i]->m_dwCount = (DWORD)dTemp;

		// v1.3 소지하고 있는 골드의 총 합을 검사한다. 
		if (memcmp(m_pClientList[iClientH]->m_pItemList[i]->m_cName, "Gold", 4) == 0)
			iTotalGold += dTemp;

		cp += 4;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectType = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue1 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue2 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue3 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_cItemColor = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue1 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue2 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue3 = (short)* sp;
		cp += 2;

		ip = (int*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan = (int)* ip;
		cp += 4;

		ip = (int*)cp;
		m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute = (int)* ip;
		cp += 4;

		cItemEquip = (char)* cp;

		if ((cItemEquip == '1') && (m_pClientList[iClientH]->m_pItemList[i] != NULL)) {
			// 장착될 수 있는 성질의 아이템이라면 장착 
			if (m_pClientList[iClientH]->m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_EQUIP)
				m_pClientList[iClientH]->m_bIsItemEquipped[i] = TRUE;
			else m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;
		}
		else m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;

		if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_bIsItemEquipped[i] == TRUE)) {
			// 아이템이 장착되어 있다면 장착 효과를 계산한다.
			if (bEquipItemHandler(iClientH, i) == FALSE) // FALSE
				m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE; // 만약 특성치 변동으로 장착된 아이템이 장착되지 않아야 한다면 장착 안한것을 표시 
		}
		cp++;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_ItemPosList[i].x = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_ItemPosList[i].y = (short)* sp;
		if (m_pClientList[iClientH]->m_ItemPosList[i].y < -10) m_pClientList[iClientH]->m_ItemPosList[i].y = -10;
		cp += 2;


		// v1.41 아이템이 Custom-Made라면 설정치를 재조정한다. 
		if ((m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute & 0x00000001) != NULL) {
			// 최대 수명이 ItemSpecialEffectValue1
			m_pClientList[iClientH]->m_pItemList[i]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue1;
			// 무기나 방어구의 경우 가중치 ItemSpecialEffectValue2
		}

		// v2.16 2002-5-21 고광현수정 
		int iValue = (m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute & 0xF0000000) >> 28;
		if (iValue > 0) {
			// 업그레이드 된 아이템. 방어구나 방패라면 최대 수명을 ItemSpecialEffectValue1로 설정한다.
			switch (m_pClientList[iClientH]->m_pItemList[i]->m_cCategory) {
			case 5: // 방패 
			case 6: // 방어구 
				m_pClientList[iClientH]->m_pItemList[i]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue1;
				break;
			}
		}

		// v1.42 희귀 아이템 플래그가 설정되어 있다면 최대 수명, 스피드, 무게 등을 재설정 해야 한다. 
		_AdjustRareItemValue(m_pClientList[iClientH]->m_pItemList[i]);

		// v1.41 현재 수명 최대 수명을 능가하면 버그이므로 되돌린다.
		if (m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan > m_pClientList[iClientH]->m_pItemList[i]->m_wMaxLifeSpan)
			m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan = m_pClientList[iClientH]->m_pItemList[i]->m_wMaxLifeSpan;

		// v1.433
		if ((m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan == 0) &&
			(m_pClientList[iClientH]->m_pItemList[i]->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ALTERITEMDROP)) {
			// 로그 남긴다. 
			wsprintf(G_cTxt, "(!) character (%s) have the GemStone of Sacrifice to lifespan 0 !", m_pClientList[iClientH]->m_cCharName);
			PutLogFileList(G_cTxt);
			// 수명 1로 환원 
			m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan = 1;
		}

		// v1.4 이제 이 아이템이 현재 사용이 인정된 아이템인가를 찾는다. 
		if (m_pClientList[iClientH]->m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_NOTUSED) {
			iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemList[i]->m_wPrice;
			delete m_pClientList[iClientH]->m_pItemList[i];
			m_pClientList[iClientH]->m_pItemList[i] = NULL;

			// v1.41
			bIsNotUsedItemFound = TRUE;
		}
		else
			if (_bCheckDupItemID(m_pClientList[iClientH]->m_pItemList[i]) == TRUE) {
				// v1.42 복제된 아이템들을 삭제한다.
				_bItemLog(DEF_ITEMLOG_DUPITEMID, iClientH, NULL, m_pClientList[iClientH]->m_pItemList[i]);

				iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemList[i]->m_wPrice;
				delete m_pClientList[iClientH]->m_pItemList[i];
				m_pClientList[iClientH]->m_pItemList[i] = NULL;
			}

	}


	sp = (short*)cp;
	sItemInBankIndex = (short)* sp;
	cp += 2;

	for (i = 0; i < sItemInBankIndex; i++) {

		m_pClientList[iClientH]->m_pItemInBankList[i] = new class CItem;
		ZeroMemory(cItemName, sizeof(cItemName));
		memcpy(cItemName, cp, 20);

		if (_bInitItemAttr(m_pClientList[iClientH]->m_pItemInBankList[i], cItemName) == FALSE) {
			// 플레이어가 소지한 아이템이 리스트에 없다. 에러
			wsprintf(cTxt, "(!!!) Client(%s)-Item(%s) is not existing Item! Conection closed.", m_pClientList[iClientH]->m_cCharName, cItemName);
			PutLogList(cTxt);


			return FALSE;
		}
		cp += 20;

		// 성후니 수정 
		dwp = (DWORD*)cp;
		dTemp = (DWORD)* dwp;

		if (dTemp < 0) dTemp = 1;
		//만약 중량이 초과되었다면 1개로 줄인다.
		if (iGetItemWeight(m_pClientList[iClientH]->m_pItemInBankList[i], dTemp) > _iCalcMaxLoad(iClientH)) {
			dTemp = 1;
			wsprintf(G_cTxt, "(!) character (%s) have the GemStone of Sacrifice to lifespan 0 !", m_pClientList[iClientH]->m_cCharName);
			PutLogFileList(G_cTxt);
			PutLogList(G_cTxt);
		}

		m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwCount = (DWORD)dTemp;

		// v1.3 소지하고 있는 골드의 총 합을 검사한다. 
		if (memcmp(m_pClientList[iClientH]->m_pItemInBankList[i]->m_cName, "Gold", 4) == 0)
			iTotalGold += dTemp;

		cp += 4;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectType = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue1 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue2 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue3 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemColor = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue1 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue2 = (short)* sp;
		cp += 2;

		sp = (short*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue3 = (short)* sp;
		cp += 2;

		ip = (int*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan = (int)* ip;
		cp += 4;

		ip = (int*)cp;
		m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute = (int)* ip;
		cp += 4;


		// v1.41 아이템이 Custom-Made라면 설정치를 재조정한다. 
		if ((m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute & 0x00000001) != NULL) {
			// 최대 수명이 ItemSpecialEffectValue1
			m_pClientList[iClientH]->m_pItemInBankList[i]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue1;
			// 무기나 방어구의 경우 가중치 ItemSpecialEffectValue2
		}

		// v2.16 2002-6-11 고광현수정 
		int iValue = (m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute & 0xF0000000) >> 28;
		if (iValue > 0) {
			// 업그레이드 된 아이템. 방어구나 방패라면 최대 수명을 ItemSpecialEffectValue1로 설정한다.
			switch (m_pClientList[iClientH]->m_pItemInBankList[i]->m_cCategory) {
			case 5: // 방패 
			case 6: // 방어구 
				m_pClientList[iClientH]->m_pItemInBankList[i]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue1;
				break;
			}
		}

		// v1.42 희귀 아이템 플래그가 설정되어 있다면 최대 수명, 스피드, 무게 등을 재설정 해야 한다. 
		_AdjustRareItemValue(m_pClientList[iClientH]->m_pItemInBankList[i]);

		// v1.41 현재 수명 최대 수명을 능가하면 버그이므로 되돌린다.
		if (m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan > m_pClientList[iClientH]->m_pItemInBankList[i]->m_wMaxLifeSpan)
			m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan = m_pClientList[iClientH]->m_pItemInBankList[i]->m_wMaxLifeSpan;

		// v1.433
		if ((m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan == 0) &&
			(m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ALTERITEMDROP)) {
			// 로그 남긴다. 
			wsprintf(G_cTxt, "(!) 캐릭터(%s) 수명 0짜리 희생석 소지!", m_pClientList[iClientH]->m_cCharName);
			PutLogFileList(G_cTxt);
			// 수명 1로 환원 
			m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan = 1;
		}

		// v1.4 이제 이 아이템이 현재 사용이 인정된 아이템인가를 찾는다. 
		if (m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemType == DEF_ITEMTYPE_NOTUSED) {
			iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemInBankList[i]->m_wPrice;
			delete m_pClientList[iClientH]->m_pItemInBankList[i];
			m_pClientList[iClientH]->m_pItemInBankList[i] = NULL;

			// v1.41
			bIsNotUsedItemFound = TRUE;
		}
		else
			if (_bCheckDupItemID(m_pClientList[iClientH]->m_pItemInBankList[i]) == TRUE) {
				// v1.42 복제된 아이템들을 삭제한다.
				_bItemLog(DEF_ITEMLOG_DUPITEMID, iClientH, NULL, m_pClientList[iClientH]->m_pItemInBankList[i]);

				iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemInBankList[i]->m_wPrice;
				delete m_pClientList[iClientH]->m_pItemInBankList[i];
				m_pClientList[iClientH]->m_pItemInBankList[i] = NULL;
			}

	}



	// 읽혀진 플레이어 데이터를 검사해서 오류가 없는지를 확인하여 리턴값을 결정한다.
	bRet = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bIsValidLoc(m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	if (bRet == FALSE) {
		GetMapInitialPoint(m_pClientList[iClientH]->m_cMapIndex, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY);
		
	}

	// 특성치 값에 오류가 있는지 검사 ==========================================================================
	if ((m_pClientList[iClientH]->m_cLU_Str > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Str < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Vit > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Vit < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Dex > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Dex < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Int > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Int < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Mag > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Mag < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Char > DEF_TOTALLEVELUPPOINT) || (m_pClientList[iClientH]->m_cLU_Char < 0))
		return FALSE;

	if ((m_pClientList[iClientH]->m_cLU_Str + m_pClientList[iClientH]->m_cLU_Vit + m_pClientList[iClientH]->m_cLU_Dex +
		m_pClientList[iClientH]->m_cLU_Int + m_pClientList[iClientH]->m_cLU_Mag + m_pClientList[iClientH]->m_cLU_Char) > DEF_TOTALLEVELUPPOINT)
		return FALSE;

	if ((m_pClientList[iClientH]->m_iStr < 10) || (m_pClientList[iClientH]->m_iStr > DEF_CHARPOINTLIMIT))
		return FALSE;

	if ((m_pClientList[iClientH]->m_iDex < 10) || (m_pClientList[iClientH]->m_iDex > DEF_CHARPOINTLIMIT))
		return FALSE;

	if ((m_pClientList[iClientH]->m_iVit < 10) || (m_pClientList[iClientH]->m_iVit > DEF_CHARPOINTLIMIT))
		return FALSE;

	if ((m_pClientList[iClientH]->m_iInt < 10) || (m_pClientList[iClientH]->m_iInt > DEF_CHARPOINTLIMIT))
		return FALSE;

	if ((m_pClientList[iClientH]->m_iMag < 10) || (m_pClientList[iClientH]->m_iMag > DEF_CHARPOINTLIMIT))
		return FALSE;

	if ((m_pClientList[iClientH]->m_iCharisma < 10) || (m_pClientList[iClientH]->m_iCharisma > DEF_CHARPOINTLIMIT))
		return FALSE;

	//특성치의 총 합이 맞지 않다면 역시 접속 불가. 
	if ((m_pClientList[iClientH]->m_iStr + m_pClientList[iClientH]->m_iDex + m_pClientList[iClientH]->m_iVit +
		m_pClientList[iClientH]->m_iInt + m_pClientList[iClientH]->m_iMag + m_pClientList[iClientH]->m_iCharisma)
		!= ((m_pClientList[iClientH]->m_iLevel - 1) * 3 + 70)) return FALSE;



	// v1.4 계정이름이나 캐릭터 이름에 잘못된 코드가 들어가 있다면 접속 불가.
	if ((m_Misc.bCheckValidName(m_pClientList[iClientH]->m_cCharName) == FALSE) || (m_Misc.bCheckValidName(m_pClientList[iClientH]->m_cAccountName) == FALSE))
		return FALSE;

	// v1.4 징계 먹은 캐릭터의 징계기간 안이면 접속 불가
	if (m_pClientList[iClientH]->m_iPenaltyBlockYear != 0) {
		GetLocalTime(&SysTime);
		iDateSum1 = (__int64)(m_pClientList[iClientH]->m_iPenaltyBlockYear * 10000 + m_pClientList[iClientH]->m_iPenaltyBlockMonth * 100 + m_pClientList[iClientH]->m_iPenaltyBlockDay);
		iDateSum2 = (__int64)(SysTime.wYear * 10000 + SysTime.wMonth * 100 + SysTime.wDay);
		if (iDateSum1 >= iDateSum2) return FALSE;
	}

	// v1.4311-3 추가 유효하지 않은 사투장 예약을 가지고 있으면 초기화 
	if (m_pClientList[iClientH]->m_iReserveTime != 0) {
		GetLocalTime(&SysTime);
		iDateSum1 = (__int64)m_pClientList[iClientH]->m_iReserveTime;
		iDateSum2 = (__int64)(SysTime.wMonth * 10000 + SysTime.wDay * 100 + SysTime.wHour);
		if (iDateSum2 >= iDateSum1) {
			// 예약이 취소됨 
			SendNotifyMsg(NULL, i, DEF_NOTIFY_FIGHTZONERESERVE, -2, NULL, NULL, NULL);
			m_pClientList[iClientH]->m_iFightzoneNumber = 0;
			m_pClientList[iClientH]->m_iReserveTime = 0;
			m_pClientList[iClientH]->m_iFightZoneTicketNumber = 0;
		}
	}

	// v1.42 잘못 입력된 운영자 레벨 값을 클리어 
	if (m_pClientList[iClientH]->m_iAdminUserLevel < 0) m_pClientList[iClientH]->m_iAdminUserLevel = 0;

	// ============================================================================================================


	// 내용을 바탕으로 Appearance를 계산, 할당한다.
	if (m_pClientList[iClientH]->m_cSex == 1) {
		// 남자이다. 
		sTmpType = 1;
	}
	else if (m_pClientList[iClientH]->m_cSex == 2) {
		// 여자이다.
		sTmpType = 4;
	}

	switch (m_pClientList[iClientH]->m_cSkin) {
	case 1:
		// 백인이면 그대로.
		break;
	case 2:
		sTmpType += 1;
		break;
	case 3:
		sTmpType += 2;
		break;
	}

	// v1.41 운영자 암행용 
	if (m_pClientList[iClientH]->m_iAdminUserLevel >= 10)
		sTmpType = m_pClientList[iClientH]->m_iAdminUserLevel;

	sTmpAppr1 = (m_pClientList[iClientH]->m_cHairStyle << 8) | (m_pClientList[iClientH]->m_cHairColor << 4) | (m_pClientList[iClientH]->m_cUnderwear);

	m_pClientList[iClientH]->m_sType = sTmpType;
	m_pClientList[iClientH]->m_sAppr1 = sTmpAppr1;

	// 소지품 총 중량계산 
	iCalcTotalWeight(iClientH);


	if (m_pClientList[iClientH]->m_sCharIDnum1 == 0) {
		// v1.3 이 캐릭터의 ID 번호가 부여되지 않은 상태이다. 할당한다. 
		int _i, _iTemp1, _iTemp2;
		short _sID1, _sID2, _sID3;

		_iTemp1 = 1;
		_iTemp2 = 1;
		for (_i = 0; _i < 10; _i++) {
			_iTemp1 += m_pClientList[iClientH]->m_cCharName[_i];
			_iTemp2 += abs(m_pClientList[iClientH]->m_cCharName[_i] ^ m_pClientList[iClientH]->m_cCharName[_i]);
		}

		_sID1 = (short)timeGetTime();
		_sID2 = (short)_iTemp1;
		_sID3 = (short)_iTemp2;

		m_pClientList[iClientH]->m_sCharIDnum1 = _sID1;
		m_pClientList[iClientH]->m_sCharIDnum2 = _sID2;
		m_pClientList[iClientH]->m_sCharIDnum3 = _sID3;
	}

	// v1.4 없어진 아이템에 대한 보상금을 지급. 
	m_pClientList[iClientH]->m_iRewardGold += iNotUsedItemPrice;

	// 
	m_pClientList[iClientH]->m_iSpeedHackCheckExp = m_pClientList[iClientH]->m_iExp;


	return TRUE;
}

int CGame::_iComposePlayerDataFileContents(int iClientH, char* pData)
{

	char sql[256];
	char  cTxt[120], cTmp[21];
	char* cp;

	int   i, * ip;
	short* sp, * pIDX;
	short Skillidx, Itemidx, BankItemidx;
	int   iFlag = 0;
	BOOL	bFind = FALSE;
	DWORD* dwp, dTemp;

	if (m_pClientList[iClientH] == NULL) return 0;

	cp = pData;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sCharIDnum1;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sCharIDnum2;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sCharIDnum3;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iLevel;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iStr;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iVit;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iDex;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iInt;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iMag;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iCharisma;
	cp += 2;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iExp;
	cp += 4;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Str;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Vit;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Dex;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Int;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Mag;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cLU_Char;
	cp += 2;

	*cp = (char)m_pClientList[iClientH]->m_cSex;
	cp++;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cSkin;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cHairStyle;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cHairColor;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_cUnderwear;
	cp += 2;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iApprColor;
	cp += 4;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sAppr1;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sAppr2;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sAppr3;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sAppr4;
	cp += 2;

	memcpy(cp, m_pClientList[iClientH]->m_cLocation, 10);
	cp += 10;

	memcpy(cp, m_pClientList[iClientH]->m_cMapName, 10);
	cp += 10;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sX;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_sY;
	cp += 2;

	if (strlen(m_pClientList[iClientH]->m_cProfile) == 0) {
		strcpy(cp, "__________");
	}
	else strcpy(cp, m_pClientList[iClientH]->m_cProfile);

	cp += 100;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iAdminUserLevel;
	cp += 2;

	if (m_pClientList[iClientH]->m_iContribution < 0) m_pClientList[iClientH]->m_iContribution = 0;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iContribution;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iSpecialAbilityTime;
	cp += 4;

	memcpy(cp, m_pClientList[iClientH]->m_cLockedMapName, 10);
	cp += 10;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iLockedMapTime;
	cp += 4;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iPenaltyBlockYear;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iPenaltyBlockMonth;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iPenaltyBlockDay;
	cp += 2;


	if (m_pClientList[iClientH]->m_iGuildRank != -1) {
		// GuildRank가 -1이면 길드이름은 무의미하다.
		memcpy(cp, m_pClientList[iClientH]->m_cGuildName, 20);
	}
	else strcpy(cp, "NONE");
	cp += 20;

	if (m_pClientList[iClientH]->m_iGuildRank != -1) {
		// GuildRank가 -1이면 길드GUID는 무의미하다.
		ip = (int*)cp;
		*ip = (int)m_pClientList[iClientH]->m_iGuildGUID;
	}
	else {
		ip = (int*)cp;
		*ip = (int)-1;
	}
	cp += 4;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iGuildRank;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iFightzoneNumber;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iReserveTime;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iFightZoneTicketNumber;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iQuest;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iQuestID;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iCurQuestCount;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iQuestRewardType;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iQuestRewardAmount;
	cp += 2;

	*cp = (char)m_pClientList[iClientH]->m_bIsQuestCompleted;
	cp++;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iSpecialEventID;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iWarContribution;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iCrusadeDuty;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_dwCrusadeGUID;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iConstructionPoint;
	cp += 4;


	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iRating;
	cp += 4;

	if (m_pClientList[iClientH]->m_iHP <= 0)
		m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH);

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iHP;
	cp += 4;

	if (m_pClientList[iClientH]->m_iMP <= 0)
		m_pClientList[iClientH]->m_iMP = 30;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iMP;
	cp += 4;

	if (m_pClientList[iClientH]->m_iSP < 0)
		m_pClientList[iClientH]->m_iSP = 20;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iSP;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iEnemyKillCount;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iPKCount;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iRewardGold;
	cp += 4;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iHungerStatus;
	cp += 2;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iSuperAttackLeft;
	cp += 2;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iTimeLeft_ShutUp;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iTimeLeft_Rating;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iTimeLeft_ForceRecall;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar;
	cp += 4;

	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iDeadPenaltyTime;
	cp += 4;

	// V2.1 성후니 파티제를 위해서 추가 
	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iPartyID;
	cp += 4;

	// v2.15 지존 패치를 위해 추가 
	ip = (int*)cp;
	*ip = (int)m_pClientList[iClientH]->m_iGizonItemUpgradeLeft;
	cp += 4;

	ZeroMemory(cTxt, sizeof(cTxt));

	for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
		wsprintf(cTmp, "%d", (int)m_pClientList[iClientH]->m_cMagicMastery[i]);
		strcat(cTxt, cTmp);
	}

	memcpy(cp, cTxt, 100);
	cp += 100;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iDownSkillIndex; ;
	cp += 2;

	pIDX = (short*)cp;
	cp += 2;

	Skillidx = 0;

	for (i = 0; i < 60; i++) {
		if (m_pClientList[iClientH]->m_cSkillMastery[i] > 0) {
			sp = (short*)cp;
			*sp = (short)i;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_cSkillMastery[i];
			cp += 2;

			ip = (int*)cp;
			*ip = (int)m_pClientList[iClientH]->m_iSkillSSN[i];
			cp += 4;

			Skillidx++;
		}
	}

	*pIDX = (short)Skillidx;

	Itemidx = 0;

	pIDX = (short*)cp;
	cp += 2;

	for (i = 0; i < DEF_MAXITEMS; i++) {
		if (m_pClientList[iClientH]->m_pItemList[i] != NULL) {

			memcpy(cp, m_pClientList[iClientH]->m_pItemList[i]->m_cName, 20);
			cp += 20;

			dwp = (DWORD*)cp;
			*dwp = (DWORD)m_pClientList[iClientH]->m_pItemList[i]->m_dwCount;
			cp += 4;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectType;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue1;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue2;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue3;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_cItemColor;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue1;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue2;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue3;
			cp += 2;

			ip = (int*)cp;
			*ip = (int)m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan;
			cp += 4;

			ip = (int*)cp;
			*ip = (int)m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute;
			cp += 4;

			*cp = (char)m_pClientList[iClientH]->m_bIsItemEquipped[i];
			cp++;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_ItemPosList[i].x;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_ItemPosList[i].y;
			cp += 2;

			Itemidx++;
		}
	}

	// v2.13 성후니 추가 DB 부하를 줄이기 위한 변수
	*cp = (char)m_pClientList[iClientH]->m_bIsBankModified;
	cp++;

	*pIDX = (short)Itemidx;
	pIDX = (short*)cp;
	cp += 2;

	BankItemidx = 0;

	for (i = 0; i < DEF_MAXBANKITEMS; i++) {

		if (m_pClientList[iClientH]->m_pItemInBankList[i] != NULL) {
			memcpy(cp, m_pClientList[iClientH]->m_pItemInBankList[i]->m_cName, 20);
			cp += 20;

			dwp = (DWORD*)cp;
			*dwp = (DWORD)m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwCount;
			cp += 4;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectType;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue1;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue2;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue3;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemColor;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue1;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue2;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue3;
			cp += 2;

			ip = (int*)cp;
			*ip = (int)m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan;
			cp += 4;

			ip = (int*)cp;
			*ip = (int)m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute;
			cp += 4;

			BankItemidx++;
		}
	}

	*pIDX = (short)BankItemidx;

	iFlag += m_pClientList[iClientH]->m_sCharIDnum1 + m_pClientList[iClientH]->m_iGuildGUID + m_pClientList[iClientH]->m_iDownSkillIndex + Skillidx + Itemidx + BankItemidx;

	//	ip = (int *) cp ;
	//	*ip = (int) iFlag ;

	return (582 + 4 + 8 * Skillidx + 2 + 55 * Itemidx + 2 + 50 * BankItemidx + 4);
}
#else
BOOL CGame::_bDecodePlayerDatafileContents(int iClientH, char * pData, DWORD dwSize)
{
	char * pContents, * token, * pOriginContents, cTmpName[11], cTxt[120];
	char   seps[] = "= \t\n";
	char   cReadModeA, cReadModeB;
	int    i, iItemIndex, iItemInBankIndex, iTotalGold, iNotUsedItemPrice;
	class  CStrTok * pStrTok;
	short  sTmpType, sTmpAppr1;
	BOOL   bRet;
	int    iTemp;
	SYSTEMTIME SysTime;
	long iDateSum1, iDateSum2;
	BOOL   bIsNotUsedItemFound = FALSE;

	if (m_pClientList[iClientH] == NULL) return FALSE;

	iTotalGold = 0;
	iItemIndex = 0;
	iItemInBankIndex  = 0;
	iNotUsedItemPrice = 0;
	cReadModeA = 0;
	cReadModeB = 0;

	pContents = new char[dwSize+2];
	ZeroMemory(pContents, dwSize+2);
	memcpy(pContents, pData, dwSize);
	pOriginContents = pContents;
	pStrTok = new class CStrTok(pContents, seps);
	token = pStrTok->pGet();

	while( token != NULL ) {
		if (cReadModeA != 0) {
			switch (cReadModeA) {
			case 1:
				// 횉횄쨌쨔��횑쩐챤째징 쩌횙횉횠��횜쨈횂 쨍횎 ��횑쨍짠��쨩 쩐챵쨈횂쨈횢. 
				ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
				strcpy(m_pClientList[iClientH]->m_cMapName, token);
				// ��횑횁짝 ��횑 쨍횎��횉 ��횓쨉짝쩍쨘째짧��쨩 횄짙쩐횈 횉횘쨈챌횉횗쨈횢. 
				ZeroMemory(cTmpName, sizeof(cTmpName));
				strcpy(cTmpName, token);
				for (i = 0; i < DEF_MAXMAPS; i++)
					if ((m_pMapList[i] != NULL)	&& (memcmp(m_pMapList[i]->m_cName, cTmpName, 10) == 0)) {
						// 쨍횎��횉 ��횓쨉짝쩍쨘쨈횂 i��횑쨈횢.
						m_pClientList[iClientH]->m_cMapIndex = (char)i;
					}

					if (m_pClientList[iClientH]->m_cMapIndex == -1) {
						wsprintf(cTxt, "(!) Player(%s) tries to enter unknown map : %s", m_pClientList[iClientH]->m_cCharName, cTmpName); 
						PutLogList(cTxt);
						delete[] pContents;
						delete pStrTok;
						return FALSE;
					}

					cReadModeA = 0;
					break;

			case 2:
				// 횉횄쨌쨔��횑쩐챤��횉 쨍횎쨩처��횉 ��짠횆징 X
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_sX = atoi(token);
				cReadModeA = 0;
				break;

			case 3:
				// 횉횄쨌쨔��횑쩐챤��횉 쨍횎쨩처��횉 ��짠횆징 Y
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_sY = atoi(token);
				cReadModeA = 0;
				break;

			case 4:
				// 횉횄쨌쨔��횑쩐챤��횉 째챔횁짚 쨩처횇횂쨍짝 쩐챵쨈횂쨈횢. <- ��횑 짹창쨈횋��쨘 횉철��챌 쩐짼횁철 쩐횎쨈횂쨈횢. 째챔횁짚횁짚쨘쨍쨈횂 쨘째쨉쨉쨌횓 ��체쨈횧쨉횉쨔횉쨌횓 
				
				cReadModeA = 0;
				break;

			case 5:
				// 쩌횘횁철횉횕째챠 ��횜쨈횂 쩐횈��횑횇횤 횁짚쨘쨍쨍짝 ��횖쩐챤 횄횎짹창횊짯 횉횗쨈횢.
				switch(cReadModeB) {
			case 1:
				// New 07/05/2004
				// v2.12
				if (iItemIndex >= DEF_MAXITEMS) {
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				// token째짧��쨘 쩐횈��횑횇횤��횉 ��횑쨍짠. ��횑 ��횑쨍짠��쨩 째징횁첩 쩐횈��횑횇횤��횉 횈짱쩌쨘��쨩 m_pItemConfigList쩔징쩌짯 횄짙쩐횈 횉횘쨈챌횉횗쨈횢.
				if (_bInitItemAttr(m_pClientList[iClientH]->m_pItemList[iItemIndex], token) == FALSE) {
					// 횉횄쨌쨔��횑쩐챤째징 쩌횘횁철횉횗 쩐횈��횑횇횤��횑 쨍짰쩍쨘횈짰쩔징 쩐첩쨈횢. 쩔징쨌짱
					wsprintf(cTxt, "(!!!) Client(%s)-Item(%s) is not existing Item! Conection closed.", m_pClientList[iClientH]->m_cCharName, token); 
					PutLogList(cTxt);

					// Debug code @@@@@@@@@@@@@@@
					HANDLE hFile;
					DWORD  nWrite;
					hFile = CreateFile("Error.Log", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
					WriteFile(hFile, (char *)pContents, dwSize+2, &nWrite, NULL);
					CloseHandle(hFile);
					///////////// @@@@@@@@@@@@@@@

					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				cReadModeB = 2;
				break;

			case 2:
				// m_dwCount
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				// 째쨔쩌철째징 쨍쨋��횑쨀횎쩍쨘��횑쨍챕 1��쨍쨌횓 쩌쩌횈횄쨉횊쨈횢.
				iTemp = atoi(token);
				if (iTemp < 0) iTemp = 1;
				//쨍쨍쩐횪 횁횩쨌짰��횑 횄횎째첬쨉횉쩐첬쨈횢쨍챕 1째쨀쨌횓 횁횢��횓쨈횢.
				if ( iGetItemWeight(m_pClientList[iClientH]->m_pItemList[iItemIndex], iTemp) > _iCalcMaxLoad(iClientH) ) {
					iTemp = 1;
					wsprintf(G_cTxt, "(!) Player�(%s) Item (%s) too heavy for player to carry", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_cName);
					PutLogFileList(G_cTxt);
					PutLogList(G_cTxt);
				}

				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_dwCount = (DWORD)iTemp;
				cReadModeB = 3;

				// v1.3 쩌횘횁철횉횕째챠 ��횜쨈횂 째챰쨉책��횉 횄횗 횉횛��쨩 째횏쨩챌횉횗쨈횢. 
				if (memcmp(m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_cName, "Gold", 4) == 0)
					iTotalGold += iTemp;
				break;

			case 3:
				// m_sTouchEffectType
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectType = atoi(token);
				cReadModeB = 4;
				break;

			case 4:
				// m_sTouchEffectValue1
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue1 = atoi(token);
				cReadModeB = 5;
				break;

			case 5:
				// m_sTouchEffectValue2
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue2 = atoi(token);
				cReadModeB = 6;
				break;

			case 6:
				// m_sTouchEffectValue3
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue3 = atoi(token);
				cReadModeB = 7;
				break;

			case 7:
				// m_cItemColor
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_cItemColor = atoi(token);
				cReadModeB = 8;
				break;

			case 8:
				// m_sItemSpecEffectValue1
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sItemSpecEffectValue1 = atoi(token);
				cReadModeB = 9;
				break;

			case 9:
				// m_sItemSpecEffectValue2
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sItemSpecEffectValue2 = atoi(token);
				cReadModeB = 10;
				break;

			case 10:
				// m_sItemSpecEffectValue3
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sItemSpecEffectValue3 = atoi(token);
				cReadModeB = 11;
				break;

			case 11:
				// m_wCurLifeSpan
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wCurLifeSpan = atoi(token);
				cReadModeB = 12;
				break;

			case 12:
				// m_dwAttribute
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_dwAttribute = atoi(token);

				// v1.4 째쨀��횓 째챠��짱 쩐횈��횑횇횤��쨩 횊짰��횓횉횗쨈횢. 
				if (m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectType == DEF_ITET_UNIQUE_OWNER) {
					if ( (m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue1 != m_pClientList[iClientH]->m_sCharIDnum1) ||
						(m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue2 != m_pClientList[iClientH]->m_sCharIDnum2) ||
						(m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue3 != m_pClientList[iClientH]->m_sCharIDnum3) ) {
							// ��횣쩍횇��횉 째횒��횑 쩐횈쨈횗 쩐횈��횑횇횤��쨩 째짰째챠 ��횜쨈횢. 
							wsprintf(cTxt, "(!) Player(%s) Item(%s) %d %d %d - %d %d %d", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_cName,
								m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue1,
								m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue2,
								m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sTouchEffectValue3,
								m_pClientList[iClientH]->m_sCharIDnum1,
								m_pClientList[iClientH]->m_sCharIDnum2,
								m_pClientList[iClientH]->m_sCharIDnum3); 
							PutLogList(cTxt);
							
						}
				}

				cReadModeA = 0;
				cReadModeB = 0;

				// v1.41 쩐횈��횑횇횤��횑 Custom-Made쨋처쨍챕 쩌쨀횁짚횆징쨍짝 ��챌횁쨋횁짚횉횗쨈횢. 
				if ((m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_dwAttribute & 0x00000001 ) != NULL) {
					// 횄횜쨈챘 쩌철쨍챠��횑 ItemSpecialEffectValue1
					m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sItemSpecEffectValue1;
					// 쨔짬짹창쨀짧 쨔챈쩐챤짹쨍��횉 째챈쩔챙 째징횁횩횆징 ItemSpecialEffectValue2
				}

				// v1.42 횊챰짹횒 쩐횈��횑횇횤 횉횄쨌징짹횞째징 쩌쨀횁짚쨉횉쩐챤 ��횜쨈횢쨍챕 횄횜쨈챘 쩌철쨍챠, 쩍쨘횉횉쨉책, 쨔짬째횚 쨉챤��쨩 ��챌쩌쨀횁짚 횉횠쩐횩 횉횗쨈횢. 
				_AdjustRareItemValue(m_pClientList[iClientH]->m_pItemList[iItemIndex]);

				// v1.41 횉철��챌 쩌철쨍챠 횄횜쨈챘 쩌철쨍챠��쨩 쨈횋째징횉횕쨍챕 쨔철짹횞��횑쨔횉쨌횓 쨉횉쨉쨔쨍째쨈횢.
				

				// v1.433
				if ((m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wCurLifeSpan == 0) && 
					(m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ALTERITEMDROP)) {
						// 쨌횓짹횞 쨀짼짹채쨈횢. 
						wsprintf(G_cTxt, "(!) Player�(%s) DEF_ITEMEFFECTTYPE_ALTERITEMDROP !", m_pClientList[iClientH]->m_cCharName);
						PutLogFileList(G_cTxt);
						// 쩌철쨍챠 1쨌횓 횊짱쩔첩 
						m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wCurLifeSpan = 1;
					}

					// v2.05 +쨈챘쨔횑횁철쨌첫 쩐횈��횑횇횤 횈짱쩌쨘횆징쨌횓 횁짚쨘쨍 쨘짱째챈, 쨘짱횊짱 
					bCheckAndConvertPlusWeaponItem(iClientH, iItemIndex);

					// v1.4 ��횑횁짝 ��횑 쩐횈��횑횇횤��횑 횉철��챌 쨩챌쩔챘��횑 ��횓횁짚쨉횊 쩐횈��횑횇횤��횓째징쨍짝 횄짙쨈횂쨈횢. 
					if (m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_cItemType == DEF_ITEMTYPE_NOTUSED) {
						iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wPrice;
						delete m_pClientList[iClientH]->m_pItemList[iItemIndex];
						m_pClientList[iClientH]->m_pItemList[iItemIndex] = NULL;

						// v1.41
						bIsNotUsedItemFound = TRUE;
					}
					else
						if (_bCheckDupItemID(m_pClientList[iClientH]->m_pItemList[iItemIndex]) == TRUE) {
							// v1.42 쨘쨔횁짝쨉횊 쩐횈��횑횇횤쨉챕��쨩 쨩챔횁짝횉횗쨈횢.
							_bItemLog(DEF_ITEMLOG_DUPITEMID, iClientH, NULL, m_pClientList[iClientH]->m_pItemList[iItemIndex]);

							iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemList[iItemIndex]->m_wPrice;
							delete m_pClientList[iClientH]->m_pItemList[iItemIndex];
							m_pClientList[iClientH]->m_pItemList[iItemIndex] = NULL;
						}
						else iItemIndex++;
						break;
				}
				break;

			case 6:
				// 횆쨀쨍짱횇횒��횉 쩌쨘쨘째 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cSex = atoi(token);
				cReadModeA = 0;
				break;

			case 7:
				// 횆쨀쨍짱횇횒��횉 횉횉쨘횓쨩철 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cSkin = atoi(token);
				cReadModeA = 0;
				break;

			case 8:
				// 횆쨀쨍짱횇횒��횉 횉챙쩐챤 쩍쨘횇쨍��횕 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cHairStyle = atoi(token);
				cReadModeA = 0;
				break;

			case 9:
				// 횆쨀쨍짱횇횒��횉 쨍횙쨍짰쨩철 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cHairColor = atoi(token);
				cReadModeA = 0;
				break;

			case 10:
				// 횆쨀쨍짱횇횒��횉 쩌횙쩔횎쨩철
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cUnderwear = atoi(token);
				cReadModeA = 0;
				break;

			case 11:
				// 쩐횈��횑횇횤 ��책횂첩 쨩처횇횂째징 쨔횦쨉책쩍횄 쨍쨋횁철쨍쨌��횑쩐챤쩐횩 횉횗쨈횢!!!!!

				// 쩐횈��횑횇횤 ��책횂첩 쨩처횇횂 횄횎짹창횊짯횉횗 횊횆 쩌쨀횁짚횉횗쨈횢.
				for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) 
					m_pClientList[iClientH]->m_sItemEquipmentStatus[i] = -1;

				// 쩐횈��횑횇횤 ��책횂첩쨩처횇횂쨍짝 횄횎짹창횊짯횉횗쨈횢.
				for (i = 0; i < DEF_MAXITEMS; i++) 
					m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;

				// v1.41 쨩챌쩔챘횉횕횁철 쩐횎쨈횂 쩐횈��횑횇횤��쨩 쩌횘횁철횉횕째챠 ��횜쩐첬쨈횢쨍챕 ��책횂첩쨩처횇횂쨍짝 쨍챨쨉횓 쨔짬쩍횄. 
				if (bIsNotUsedItemFound == FALSE) {
					for (i = 0; i < DEF_MAXITEMS; i++) {
						wsprintf(cTxt, "%d", token[i]);
						if ((token[i] == '1') && (m_pClientList[iClientH]->m_pItemList[i] != NULL)) {
							// ��책횂첩쨉횋 쩌철 ��횜쨈횂 쩌쨘횁첬��횉 쩐횈��횑횇횤��횑쨋처쨍챕 ��책횂첩 
							if (m_pClientList[iClientH]->m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_EQUIP) 
								m_pClientList[iClientH]->m_bIsItemEquipped[i] = TRUE;
							else m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;
						}
						else m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE;

						if ((m_pClientList[iClientH] != NULL) && (m_pClientList[iClientH]->m_bIsItemEquipped[i] == TRUE)) {
							// 쩐횈��횑횇횤��횑 ��책횂첩쨉횉쩐챤 ��횜쨈횢쨍챕 ��책횂첩 횊쩔째첬쨍짝 째챔쨩챗횉횗쨈횢.
							if (bEquipItemHandler(iClientH, i) == FALSE) // FALSE
								m_pClientList[iClientH]->m_bIsItemEquipped[i] = FALSE; // 쨍쨍쩐횪 횈짱쩌쨘횆징 쨘짱쨉쩔��쨍쨌횓 ��책횂첩쨉횊 쩐횈��횑횇횤��횑 ��책횂첩쨉횉횁철 쩐횎쩐횈쩐횩 횉횗쨈횢쨍챕 ��책횂첩 쩐횊횉횗째횒��쨩 횉짜쩍횄 
						}
					}
				}

				cReadModeA = 0;
				break;

			case 12:
				// 쩌횘쩌횙 짹챈쨉책��횑쨍짠��쨩 횄횎짹창횊짯횉횗쨈횢.
				// 짹챈쨉책 ��횑쨍짠��쨘 횄횜쨈챘 20��횣 
				ZeroMemory(m_pClientList[iClientH]->m_cGuildName, sizeof(m_pClientList[iClientH]->m_cGuildName));
				strcpy(m_pClientList[iClientH]->m_cGuildName, token);
				cReadModeA = 0;
				break;

			case 13:
				// 짹챈쨉책 쨌짤횇짤 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iGuildRank = atoi(token);
				cReadModeA = 0;
				break;

			case 14:
				// HP 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iHP = atoi(token);
				cReadModeA = 0;
				break;

			case 15:
				// DefenseRatio 쨩챌쩔챘횉횕횁철 쩐횎쨈횂쨈횢. 쨔짬��횉쨔횑횉횠 횁체 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				cReadModeA = 0;
				break;

			case 16:
				// HitRatio  쨩챌쩔챘횉횕횁철 쩐횎쨈횂쨈횢. 쨔짬��횉쨔횑횉횠 횁체 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				cReadModeA = 0;
				break;

			case 17:
				// Level  
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iLevel = atoi(token);
				cReadModeA = 0;
				break;

			case 18:
				// Str 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iStr = atoi(token);
				cReadModeA = 0;
				break;

			case 19:
				// Int 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iInt = atoi(token);
				cReadModeA = 0;
				break;

			case 20:
				// Vit 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iVit = atoi(token);
				cReadModeA = 0;
				break;

			case 21:
				// Dex 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iDex = atoi(token);
				cReadModeA = 0;
				break;

			case 22:
				// Mag 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iMag = atoi(token);
				cReadModeA = 0;
				break;

			case 23:
				// Charisma 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iCharisma = atoi(token);
				cReadModeA = 0;
				break;

			case 24:
				// Luck 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iLuck = atoi(token);
				cReadModeA = 0;
				break;

			case 25:
				// Exp 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iExp = atoi(token);
				cReadModeA = 0;
				break;

			case 26:
				// Magic-Mastery 쩌쨀횁짚횉횗쨈횢. // 0��횑쨍챕 쨩챌쩔챘 쨘횘째징. 1��횑쨍챕 쨔챔쩔챤 쨩처횇횂.
				for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
					m_pClientList[iClientH]->m_cMagicMastery[i] = token[i] - 48;
				}
				cReadModeA = 0;
				break;

			case 27:
				// Skill-Mastery 쩌쨀횁짚횉횗쨈횢.
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_cSkillMastery[cReadModeB] = atoi(token);
				cReadModeB++;

				if (cReadModeB >= DEF_MAXSKILLTYPE) {
					cReadModeA = 0;
					cReadModeB = 0;
				}
				break;
				//
			case 28:
				// Warehouse쩔징 쨍횄째횥쨀챠 쩐횈��횑횇횤 횁짚쨘쨍쨍짝 ��횖쩐챤 횄횎짹창횊짯 횉횗쨈횢.
				switch(cReadModeB) {
			case 1:
				if (iItemInBankIndex >= DEF_MAXBANKITEMS) {
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				// token째짧��쨘 쩐횈��횑횇횤��횉 ��횑쨍짠. ��횑 ��횑쨍짠��쨩 째징횁첩 쩐횈��횑횇횤��횉 횈짱쩌쨘��쨩 m_pItemConfigList쩔징쩌짯 횄짙쩐횈 횉횘쨈챌횉횗쨈횢.
				if (_bInitItemAttr(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex], token) == FALSE) {
					// 횉횄쨌쨔��횑쩐챤째징 ��첬��책횉횕째챠 ��횜쨈횂 쩐횈��횑횇횤��횑 쨍짰쩍쨘횈짰쩔징 쩐첩쨈횢. 쩔징쨌짱
					wsprintf(cTxt, "(!!!) Client(%s)-Bank Item(%s) is not existing Item! Conection closed.", m_pClientList[iClientH]->m_cCharName, token); 
					PutLogList(cTxt);

					// Debug code @@@@@@@@@@@@@@@
					HANDLE hFile;
					DWORD  nWrite;
					hFile = CreateFile("Error.Log", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
					WriteFile(hFile, (char *)pOriginContents, dwSize+2, &nWrite, NULL);
					CloseHandle(hFile);
					///////////// @@@@@@@@@@@@@@@

					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				cReadModeB = 2;
				break;

			case 2:
				// m_dwCount
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				// 째쨔쩌철째징 쨍쨋��횑쨀횎쩍쨘��횑쨍챕 1��쨍쨌횓 쩌쩌횈횄쨉횊쨈횢.
				iTemp = atoi(token);
				if (iTemp < 0) iTemp = 1;

				// 쨍쨍쩐횪 째징횁첬 쩌철 ��횜쨈횂 횁횩쨌짰��횑 횄횎째첬쨉횊 쩐횈��횑횇횤��횑 ��횜쨈횢쨍챕 1째쨀쨌횓 횁횢��횓쨈횢.
				if ( iGetItemWeight(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex], iTemp) > _iCalcMaxLoad(iClientH) ) {
					iTemp = 1;
					wsprintf(G_cTxt, "(!) Player(%s) Item(%s) _iCalcMaxLoad !", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_cName);
					PutLogFileList(G_cTxt);
					PutLogList(G_cTxt);
				}

				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_dwCount = (DWORD)iTemp;
				cReadModeB = 3;

				// v1.3 쩌횘횁철횉횕째챠 ��횜쨈횂 째챰쨉책��횉 횄횗 횉횛��쨩 째횏쨩챌횉횗쨈횢. 
				if (memcmp(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_cName, "Gold", 4) == 0)
					iTotalGold += iTemp;
				break;

			case 3:
				// m_sTouchEffectType
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sTouchEffectType = atoi(token);
				cReadModeB = 4;
				break;

			case 4:
				// m_sTouchEffectValue1
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sTouchEffectValue1 = atoi(token);
				cReadModeB = 5;
				break;

			case 5:
				// m_sTouchEffectValue2
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sTouchEffectValue2 = atoi(token);
				cReadModeB = 6;
				break;

			case 6:
				// m_sTouchEffectValue3
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sTouchEffectValue3 = atoi(token);
				cReadModeB = 7;
				break;

			case 7:
				// m_cItemColor
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_cItemColor = atoi(token);
				cReadModeB = 8;
				break;

			case 8:
				// m_sItemSpecEffectValue1
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemSpecEffectValue1 = atoi(token);
				cReadModeB = 9;
				break;

			case 9:
				// m_sItemSpecEffectValue2
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemSpecEffectValue2 = atoi(token);
				cReadModeB = 10;
				break;

			case 10:
				// m_sItemSpecEffectValue3
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemSpecEffectValue3 = atoi(token);
				cReadModeB = 11;
				break;

			case 11:
				// m_wCurLifeSpan
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wCurLifeSpan = atoi(token);

				cReadModeB = 12;
				break;


			case 12:
				// m_dwAttribute
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_dwAttribute = atoi(token);
				cReadModeA = 0;
				cReadModeB = 0;

				// v1.41 쩐횈��횑횇횤��횑 Custom-Made쨋처쨍챕 쩌쨀횁짚횆징쨍짝 ��챌횁쨋횁짚횉횗쨈횢. 
				if ((m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_dwAttribute & 0x00000001) != NULL) {
					// 횄횜쨈챘 쩌철쨍챠��횑 ItemSpecialEffectValue1
					m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemSpecEffectValue1;
					// 쨔짬짹창쨀짧 쨔챈쩐챤짹쨍��횉 째챈쩔챙 째징횁횩횆징 ItemSpecialEffectValue2

				}

				// v2.16 2002-5-21 째챠짹짚횉철쩌철횁짚 
				int iValue = (m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_dwAttribute & 0xF0000000) >> 28;
				if (iValue > 0) {
					// 쩐첨짹횞쨌쨔��횑쨉책 쨉횊 쩐횈��횑횇횤. 쨔챈쩐챤짹쨍쨀짧 쨔챈횈횖쨋처쨍챕 횄횜쨈챘 쩌철쨍챠��쨩 ItemSpecialEffectValue1쨌횓 쩌쨀횁짚횉횗쨈횢.
					switch (m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_cCategory) {
			case 5: // 쨔챈횈횖 
			case 6: // 쨔챈쩐챤짹쨍 
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wMaxLifeSpan = m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemSpecEffectValue1;
				break;
					}
				}

				// v1.42 횊챰짹횒 쩐횈��횑횇횤 횉횄쨌징짹횞째징 쩌쨀횁짚쨉횉쩐챤 ��횜쨈횢쨍챕 횄횜쨈챘 쩌철쨍챠, 쩍쨘횉횉쨉책, 쨔짬째횚 쨉챤��쨩 ��챌쩌쨀횁짚 횉횠쩐횩 횉횗쨈횢. 
				_AdjustRareItemValue(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]);

				// v1.41 쩌철쨍챠��횑 횄횜쨈챘쩌철쨍챠��쨩 횄횎째첬횉횗쨈횢쨍챕 쨔철짹횞��횑쨔횉쨌횓 쨉횉쨉쨔쨍째쨈횢.
				

				// v1.433
				if ((m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wCurLifeSpan == 0) && 
					(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ALTERITEMDROP)) {
						// 쨌횓짹횞 쨀짼짹채쨈횢. 
						wsprintf(G_cTxt, "(!) Player�(%s) DEF_ITEMEFFECTTYPE_ALTERITEMDROP !", m_pClientList[iClientH]->m_cCharName);
						PutLogFileList(G_cTxt);
						// 쩌철쨍챠 1쨌횓 횊짱쩔첩 
						m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wCurLifeSpan = 1;
					}

					// v1.4 ��횑횁짝 ��횑 쩐횈��횑횇횤��횑 횉철��챌 쨩챌쩔챘��횑 ��횓횁짚쨉횊 쩐횈��횑횇횤��횓째징쨍짝 횄짙쨈횂쨈횢. 
					if (m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_cItemType == DEF_ITEMTYPE_NOTUSED) {
						iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wPrice;
						delete m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex];
						m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex] = NULL;
					}
					else 
						if (_bCheckDupItemID(m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]) == TRUE) {
							// v1.42 쨘쨔횁짝쨉횊 쩐횈��횑횇횤쨉챕��쨩 쨩챔횁짝횉횗쨈횢.
							_bItemLog(DEF_ITEMLOG_DUPITEMID, iClientH, NULL, m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]);

							iNotUsedItemPrice += m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex]->m_wPrice;
							delete m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex];
							m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex] = NULL;		
						}
						else iItemInBankIndex++;
						break;
				}
				break;
				//

			case 29:
				// 횉횄쨌쨔��횑쩐챤 쩌횘쩌횙��횉 쨍쨋��쨩��쨩 횄횎짹창횊짯횉횗쨈횢.
				ZeroMemory(m_pClientList[iClientH]->m_cLocation, sizeof(m_pClientList[iClientH]->m_cLocation));
				strcpy(m_pClientList[iClientH]->m_cLocation, token);
				if (memcmp(m_pClientList[iClientH]->m_cLocation+3,"hunter",6) == 0)
					m_pClientList[iClientH]->m_bIsPlayerCivil = TRUE;
				cReadModeA = 0;
				break;


			case 30:
				// m_iMP
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iMP = atoi(token);
				cReadModeA = 0;
				break;

			case 31:
				// m_iSP
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iSP = atoi(token);
				cReadModeA = 0;
				break;

			case 32:
				// m_cLU_Pool
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iLU_Pool = atoi(token);
				cReadModeA = 0;
				break;
			
			case 38:
				// m_iEnemyKillCount
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iEnemyKillCount = atoi(token);
				cReadModeA = 0;
				break;

			case 39:
				// m_iPKCount
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iPKCount = atoi(token);
				cReadModeA = 0;
				break;

			case 40:
				// m_iRewardGold
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iRewardGold = atoi(token);
				cReadModeA = 0;
				break;

			case 41:
				// Skill-SSN 쩌쨀횁짚횉횗쨈횢.
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iSkillSSN[cReadModeB] = atoi(token);
				cReadModeB++;

				if (cReadModeB >= DEF_MAXSKILLTYPE) {
					cReadModeA = 0;
					cReadModeB = 0;
				}
				break;

			case 42:
				if (token != NULL) {
					ZeroMemory(m_pClientList[iClientH]->m_cProfile, sizeof(m_pClientList[iClientH]->m_cProfile));
					strcpy(m_pClientList[iClientH]->m_cProfile, token);
				}
				cReadModeA = 0;
				break;

			case 43:
				// Hunger-Status 쩌쨀횁짚횉횗쨈횢.
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iHungerStatus = atoi(token);
				cReadModeA = 0;
				break;

				case 44:
				// AdminUserLevel
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iAdminUserLevel = 0; //Default it to 0
				if (atoi(token) > 0) {
				for (i = 0; i < DEF_MAXADMINS; i++) {
					if(strlen(m_stAdminList[i].m_cGMName) == 0) break; //No more GM's on list
						if ((strlen(m_stAdminList[i].m_cGMName)) == (strlen(m_pClientList[iClientH]->m_cCharName))) {
							if(memcmp(m_stAdminList[i].m_cGMName,m_pClientList[iClientH]->m_cCharName,strlen(m_pClientList[iClientH]->m_cCharName)) == 0){
								m_pClientList[iClientH]->m_iAdminUserLevel = atoi(token);
								break; //Break goes to cReadModeA = 0, so no need to do it again
							}
						}
					}
				}
				cReadModeA = 0;
				break;
				
				

			case 45:
				// TimeLeft_ShutUp
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iTimeLeft_ShutUp = atoi(token);
				cReadModeA = 0;
				break;

			case 46:
				// TimeLeft_Rating
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iTimeLeft_Rating = atoi(token);
				cReadModeA = 0;
				break;

			case 47:
				// Rating
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iRating = atoi(token);
				cReadModeA = 0;
				break;

			case 48:
				// Guild GUID: ��횑��체쩔징 쨩첵쩌쨘쨉횉쩐첬쨈첩 짹챈쨉책쨉챕��쨘 쨍챨쨉횓 -1��횑 쨉횉 쨔철쨍짹 째횒��횑쨈횢.
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iGuildGUID = atoi(token);
				cReadModeA = 0;
				break;

			case 49:
				// Down Skill Index
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iDownSkillIndex = atoi(token);
				cReadModeA = 0;
				break;

			case 50:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_ItemPosList[cReadModeB-1].x = atoi(token);
				cReadModeB++;
				if (cReadModeB > 50) {
					cReadModeA = 0;
					cReadModeB = 0;
				}
				break;

			case 51:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_ItemPosList[cReadModeB-1].y = atoi(token);
				// v1.3 ��횩쨍첩쨉횊 ��짠횆징째짧��쨩 쨘쨍횁짚횉횗쨈횢. 
				if (m_pClientList[iClientH]->m_ItemPosList[cReadModeB-1].y < -10) m_pClientList[iClientH]->m_ItemPosList[cReadModeB-1].y = -10;
				cReadModeB++;
				if (cReadModeB > 50) {
					cReadModeA = 0;
					cReadModeB = 0;
				}
				break;

			case 52:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_sCharIDnum1 = atoi(token);
				cReadModeA = 0;
				break;

			case 53:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_sCharIDnum2 = atoi(token);
				cReadModeA = 0;
				break;

			case 54:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_sCharIDnum3 = atoi(token);
				cReadModeA = 0;
				break;

			case 55:
				switch (cReadModeB) {
			case 1:
				// Penalty Block Year
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iPenaltyBlockYear = atoi(token);

				cReadModeB = 2;
				break;

			case 2:
				// Penalty Block Month
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iPenaltyBlockMonth = atoi(token);

				cReadModeB = 3;
				break;

			case 3:
				// Penalty Block day
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iPenaltyBlockDay = atoi(token);

				cReadModeA = 0;
				cReadModeB = 0;
				break;
				}
				break;

			case 56:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iQuest = atoi(token);
				cReadModeA = 0;
				break;

			case 57:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iCurQuestCount = atoi(token);
				cReadModeA = 0;
				break;

			case 58:
				cReadModeA = 0;
				break;

			case 59:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iQuestRewardType = atoi(token);
				cReadModeA = 0;
				break;

			case 60:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iQuestRewardAmount = atoi(token);
				cReadModeA = 0;
				break;

			case 61:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iContribution = atoi(token);
				cReadModeA = 0;
				break;

			case 62:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iQuestID = atoi(token);
				cReadModeA = 0;
				break;

			case 63:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_bIsQuestCompleted = (BOOL)atoi(token);
				cReadModeA = 0;
				break;

			case 64:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = (BOOL)atoi(token);
				cReadModeA = 0;
				break;

			case 65:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar = (BOOL)atoi(token);
				cReadModeA = 0;
				break;

			case 66:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iSpecialEventID = (BOOL)atoi(token);
				cReadModeA = 0;
				break;

				// v1.4311-3 횄횩째징 쨩챌횇천��책 쩔쨔쩐횪쩔징 째체째챔쨉횊 횈횆��횕 쨀쨩쩔챘 ��횖짹창 
			case 67:
				switch (cReadModeB) {
			case 1:
				// FightZone Number
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iFightzoneNumber = atoi(token);

				cReadModeB = 2;
				break;

			case 2:
				// 쩔쨔쩐횪횉횗 쩍횄째짙 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iReserveTime = atoi(token);


				cReadModeB = 3;
				break;
			case 3:
				// 쨀짼��쨘 횈쩌횆횕쩌첵��횣 
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iFightZoneTicketNumber = atoi(token);

				cReadModeA = 0;
				cReadModeB = 0;
				break;

				}
				break;

			case 70:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iSuperAttackLeft = (BOOL)atoi(token);
				cReadModeA = 0;
				break;

			case 71:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iSpecialAbilityTime = atoi(token);
				cReadModeA = 0;
				break;

			case 72:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iWarContribution = atoi(token);
				cReadModeA = 0;
				break;

			case 73:
				if (strlen(token) > 10) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
				strcpy(m_pClientList[iClientH]->m_cLockedMapName, token);
				cReadModeA = 0;
				break;

			case 74:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iLockedMapTime = atoi(token);
				cReadModeA = 0;
				break;

			case 75:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iCrusadeDuty = atoi(token);
				cReadModeA = 0;
				break;

			case 76:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iConstructionPoint = atoi(token);
				cReadModeA = 0;
				break;

			case 77:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_dwCrusadeGUID = atoi(token);
				cReadModeA = 0;
				break;

			case 78:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iDeadPenaltyTime = atoi(token);
				cReadModeA = 0;
				break;

			case 79: // v2.06 12-4
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iPartyID = atoi(token);
				if (m_pClientList[iClientH]->m_iPartyID != NULL) m_pClientList[iClientH]->m_iPartyStatus = DEF_PARTYSTATUS_CONFIRM;
				cReadModeA = 0;
				break;

			case 80: // v2.15 횁철횁쨍쩐횈��횑횇횤쩐첨짹횞쨌쨔��횑쨉책
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iGizonItemUpgradeLeft = atoi(token);
				if (m_pClientList[iClientH]->m_iGizonItemUpgradeLeft < 0) m_pClientList[iClientH]->m_iGizonItemUpgradeLeft = 0;
				cReadModeA = 0;
				break;

			case 81: 
				if (strlen(token) > 21) strcpy(token, m_pClientList[iClientH]->m_cIPaddress); 
				ZeroMemory(m_pClientList[iClientH]->m_cIP2, sizeof(m_pClientList[iClientH]->m_cIP2)); 
				strcpy(m_pClientList[iClientH]->m_cIP2, token); 
				cReadModeA = 0; 
				break;

			case 82:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_dwHeldenianGUID = atoi(token);
				cReadModeA = 0;
				break;

				
			case 83:
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}

				m_pClientList[iClientH]->m_iMajesticLevel = atoi(token);
				cReadModeA = 0;
				break;

			case 84:
				// m_iMaxEK
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iMaxEK = atoi(token);
				cReadModeA = 0;
				break;

			case 85:
				// m_iDeaths MORLA 2.2 - Nuevos datos para el pj
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iDeaths = atoi(token);
				cReadModeA = 0;
				break;

			case 86:
				// m_iDGPoints
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iDGPoints = atoi(token);
				cReadModeA = 0;
				break;

			case 87:
				// character-DGKills
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iDGKills = atoi(token);
				cReadModeA = 0;
				break;

			case 88:
				// character-DGDeaths
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iTotalDGDeaths = atoi(token);
				cReadModeA = 0;
				break;

			case 89:
				// character-Kills
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName); 
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iTotalDGKills = atoi(token);
				cReadModeA = 0;
				break;

			case 90:
				// Wanted System
				if (_bGetIsStringIsNumber(token) == FALSE) {
					wsprintf(cTxt, "(!!!) Player(%s) data file error! wrong Data format - Connection closed. ", m_pClientList[iClientH]->m_cCharName);
					PutLogList(cTxt);
					delete[] pContents;
					delete pStrTok;
					return FALSE;
				}
				m_pClientList[iClientH]->m_iWantedLevel   = atoi(token);
				cReadModeA = 0;
				break;

			}
		}
		else {
			if (memcmp(token, "character-loc-map", 17) == 0)		 cReadModeA = 1;
			if (memcmp(token, "character-loc-x", 15) == 0)			 cReadModeA = 2;
			if (memcmp(token, "character-loc-y", 15) == 0)			 cReadModeA = 3;
			if (memcmp(token, "character-account-status", 21) == 0)  cReadModeA = 4;
			if (memcmp(token, "character-item", 14) == 0) {
				cReadModeA = 5;
				cReadModeB = 1;
				m_pClientList[iClientH]->m_pItemList[iItemIndex] = new class CItem;
			}
			if (memcmp(token, "character-bank-item", 18) == 0) {
				cReadModeA = 28;
				cReadModeB = 1;
				m_pClientList[iClientH]->m_pItemInBankList[iItemInBankIndex] = new class CItem;
			}
			if (memcmp(token, "sex-status", 10) == 0)        cReadModeA = 6;
			if (memcmp(token, "skin-status", 11) == 0)       cReadModeA = 7;
			if (memcmp(token, "hairstyle-status", 16) == 0)  cReadModeA = 8;
			if (memcmp(token, "haircolor-status", 16) == 0)  cReadModeA = 9;
			if (memcmp(token, "underwear-status", 16) == 0)  cReadModeA = 10;
			if (memcmp(token, "item-equip-status", 17) == 0)    cReadModeA = 11;
			if (memcmp(token, "character-guild-name", 20) == 0) cReadModeA = 12;
			if (memcmp(token, "character-guild-rank", 20) == 0) cReadModeA = 13;
			if (memcmp(token, "character-HP", 12) == 0)         cReadModeA = 14;
			if (memcmp(token, "character-DefenseRatio",22)==0)  cReadModeA = 15;
			if (memcmp(token, "character-HitRatio", 18) == 0)   cReadModeA = 16;
			if (memcmp(token, "character-LEVEL", 15) == 0)      cReadModeA = 17;
			if (memcmp(token, "character-STR", 13) == 0)        cReadModeA = 18;
			if (memcmp(token, "character-INT", 13) == 0)        cReadModeA = 19;
			if (memcmp(token, "character-VIT", 13) == 0)        cReadModeA = 20;
			if (memcmp(token, "character-DEX", 13) == 0)        cReadModeA = 21;
			if (memcmp(token, "character-MAG", 13) == 0)        cReadModeA = 22;
			if (memcmp(token, "character-CHARISMA", 18) == 0)   cReadModeA = 23;
			if (memcmp(token, "character-LUCK", 14) == 0)       cReadModeA = 24;
			if (memcmp(token, "character-EXP", 13) == 0)        cReadModeA = 25;
			if (memcmp(token, "magic-mastery", 13) == 0)        cReadModeA = 26;
			if (memcmp(token, "skill-mastery", 13) == 0) {
				cReadModeA = 27;
				cReadModeB = 0;
			}
			if (memcmp(token, "character-location", 18) == 0)   cReadModeA = 29;
			if (memcmp(token, "character-MP", 12) == 0)         cReadModeA = 30;
			if (memcmp(token, "character-SP", 12) == 0)         cReadModeA = 31;
			if (memcmp(token, "character-LU_Pool", 17) == 0)     cReadModeA = 32;
			
			if (memcmp(token, "character-EK-Count",18) == 0)    cReadModeA = 38;
			if (memcmp(token, "character-PK-Count",18) == 0)    cReadModeA = 39;
			if (memcmp(token, "character-reward-gold",21) == 0) cReadModeA = 40;
			if (memcmp(token, "skill-SSN", 9) == 0) 			cReadModeA = 41;
			if (memcmp(token, "character-profile", 17) == 0)	cReadModeA = 42;
			if (memcmp(token, "hunger-status", 13) == 0) 		cReadModeA = 43;
			if (memcmp(token, "admin-user-level", 16) == 0) 	cReadModeA = 44;
			if (memcmp(token, "timeleft-shutup", 15) == 0) 		cReadModeA = 45;
			if (memcmp(token, "timeleft-rating", 15) == 0) 		cReadModeA = 46;
			if (memcmp(token, "character-RATING", 16) == 0)	    cReadModeA = 47;
			if (memcmp(token, "character-guild-GUID", 20) == 0) cReadModeA = 48;
			if (memcmp(token, "character-downskillindex", 24) == 0) cReadModeA = 49;
			if (memcmp(token, "item-position-x", 16) == 0) {
				cReadModeA = 50;
				cReadModeB = 1;
			}
			if (memcmp(token, "item-position-y", 16) == 0) {
				cReadModeA = 51;
				cReadModeB = 1;
			}
			if (memcmp(token, "character-IDnum1",16) == 0)		cReadModeA = 52;
			if (memcmp(token, "character-IDnum2",16) == 0)		cReadModeA = 53;
			if (memcmp(token, "character-IDnum3",16) == 0)		cReadModeA = 54;
			if (memcmp(token, "penalty-block-date",18) == 0) {
				cReadModeA = 55;
				cReadModeB = 1;
			}
			if (memcmp(token, "character-quest-number",22) == 0) cReadModeA = 56;
			if (memcmp(token, "current-quest-count",19) == 0)	 cReadModeA = 57;
			if (memcmp(token, "quest-reward-type", 17) == 0)    cReadModeA = 59;
			if (memcmp(token, "quest-reward-amount", 19) == 0)  cReadModeA = 60;
			if (memcmp(token, "character-contribution", 22) == 0)   cReadModeA = 61;
			if (memcmp(token, "character-quest-ID",18) == 0)        cReadModeA = 62;
			if (memcmp(token, "character-quest-completed",25) == 0) cReadModeA = 63;
			if (memcmp(token, "timeleft-force-recall", 21) == 0)	cReadModeA = 64;
			if (memcmp(token, "timeleft-firm-staminar", 22) == 0)	cReadModeA = 65;
			if (memcmp(token, "special-event-id", 16) == 0)			cReadModeA = 66;
			if (memcmp(token, "super-attack-left", 17) == 0)		cReadModeA = 70;
			if (memcmp(token, "reserved-fightzone-id", 21) == 0)	{
				cReadModeA = 67;
				cReadModeB = 1;
			}
			if (memcmp(token, "special-ability-time", 20) == 0)       cReadModeA = 71; 
			if (memcmp(token, "character-war-contribution", 26) == 0) cReadModeA = 72; 
			if (memcmp(token, "locked-map-name", 15) == 0) cReadModeA = 73;
			if (memcmp(token, "locked-map-time", 15) == 0) cReadModeA = 74;
			if (memcmp(token, "crusade-job", 11) == 0)     cReadModeA = 75;
			if (memcmp(token, "construct-point", 15) == 0) cReadModeA = 76;
			if (memcmp(token, "crusade-GUID", 12) == 0)    cReadModeA = 77;
			if (memcmp(token, "dead-penalty-time", 17) == 0) cReadModeA = 78;
			if (memcmp(token, "party-id", 8) == 0)           cReadModeA = 79;
			if (memcmp(token, "gizon-item-upgrade-left", 23) == 0) cReadModeA = 80;


			if (memcmp(token, "ip2", 3)== 0) cReadModeA = 81;

			if (memcmp(token, "heldenian-GUID", 14) == 0)    cReadModeA = 82;

			if (memcmp(token, "majestic-level", 14) == 0) cReadModeA = 83;

			if (memcmp(token, "max-ek", 6) == 0) cReadModeA = 84;

			if (memcmp(token, "character-Deaths", 16) == 0)    cReadModeA = 85; // MORLA 2.2 - Nuevos datos para el PJ
			if (memcmp(token, "character-DGPoints", 18) == 0)    cReadModeA = 86;
			if (memcmp(token, "character-DGKills", 17) == 0)    cReadModeA = 87;
			if (memcmp(token, "character-TotalDGDeaths", 23) == 0)    cReadModeA = 88;
			if (memcmp(token, "character-TotalDGKills", 22) == 0)    cReadModeA = 89;
			if (memcmp(token, "character-wanted-level", 22) == 0)    cReadModeA = 90; // // Wanted System

			if (memcmp(token, "[EOF]", 5) == 0) goto DPDC_STOP_DECODING;
		}
		token = pStrTok->pGet();
	}													  

DPDC_STOP_DECODING:;	

	delete pStrTok;
	delete[] pContents;
	if ((cReadModeA != 0) || (cReadModeB != 0)) {
		wsprintf(cTxt, "(!!!) Player(%s) data file contents error(%d %d)! Connection closed.", m_pClientList[iClientH]->m_cCharName, cReadModeA, cReadModeB);
		PutLogList(cTxt);
		// Debug code @@@@@@@@@@@@@@@
		HANDLE hFile2;
		DWORD  nWrite2;
		hFile2 = CreateFile("Error.Log", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, NULL, NULL);
		WriteFile(hFile2, (char *)pOriginContents, dwSize+2, &nWrite2, NULL);
		CloseHandle(hFile2);
		///////////// @@@@@@@@@@@@@@@
		return FALSE;
	}

	// verified all data below
	bRet = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bIsValidLoc(m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	if (bRet == FALSE) {
		GetMapInitialPoint(m_pClientList[iClientH]->m_cMapIndex, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_cLocation);
	}
	if (m_pClientList[iClientH]->m_iLU_Pool < 3) m_pClientList[iClientH]->m_iLU_Pool = 3;
	if ((m_pClientList[iClientH]->m_iStr < 10) || (m_pClientList[iClientH]->m_iStr > m_sCharStatLimit - 11)) return FALSE;
	if ((m_pClientList[iClientH]->m_iDex < 10) || (m_pClientList[iClientH]->m_iDex > m_sCharStatLimit - 11)) return FALSE;
	if ((m_pClientList[iClientH]->m_iVit < 10) || (m_pClientList[iClientH]->m_iVit > m_sCharStatLimit-11)) return FALSE;
	if ((m_pClientList[iClientH]->m_iInt < 10) || (m_pClientList[iClientH]->m_iInt > m_sCharStatLimit - 11)) return FALSE;
	if ((m_pClientList[iClientH]->m_iMag < 10) || (m_pClientList[iClientH]->m_iMag > m_sCharStatLimit - 11)) return FALSE;
	if ((m_pClientList[iClientH]->m_iCharisma < 10) || (m_pClientList[iClientH]->m_iCharisma > m_sCharStatLimit-11)) return FALSE;
	
	int cStatPointTotal = m_pClientList[iClientH]->m_iStr + m_pClientList[iClientH]->m_iDex + m_pClientList[iClientH]->m_iVit +
		m_pClientList[iClientH]->m_iInt + m_pClientList[iClientH]->m_iMag + m_pClientList[iClientH]->m_iCharisma;
	
	if ((cStatPointTotal + (m_pClientList[iClientH]->m_iLU_Pool-3)) != ((m_pClientList[iClientH]->m_iLevel-1)*3 + 70)) {
		if (cStatPointTotal > ((m_pClientList[iClientH]->m_iLevel-1)*3 + 70)) return FALSE;
		m_pClientList[iClientH]->m_iLU_Pool = ((m_pClientList[iClientH]->m_iLevel-1)*3 + 73) - ((m_pClientList[iClientH]->m_iStr + m_pClientList[iClientH]->m_iDex + m_pClientList[iClientH]->m_iVit + m_pClientList[iClientH]->m_iInt + m_pClientList[iClientH]->m_iMag + m_pClientList[iClientH]->m_iCharisma));
	}
	if (m_Misc.bCheckValidName(m_pClientList[iClientH]->m_cAccountName) == FALSE) return FALSE;
	if (m_pClientList[iClientH]->m_iPenaltyBlockYear != 0) {
		GetLocalTime(&SysTime);
		iDateSum1 = (long)m_pClientList[iClientH]->m_iPenaltyBlockYear*10000 + m_pClientList[iClientH]->m_iPenaltyBlockMonth*100 + m_pClientList[iClientH]->m_iPenaltyBlockDay;
		iDateSum2 = (long)SysTime.wYear*10000 + SysTime.wMonth*100 + SysTime.wDay;
		if (iDateSum1 >= iDateSum2) return FALSE;
	}
	if (m_pClientList[iClientH]->m_iReserveTime != 0) {
		GetLocalTime(&SysTime);
		iDateSum1 = (long)m_pClientList[iClientH]->m_iReserveTime;
		iDateSum2 = (long)SysTime.wMonth*10000 + SysTime.wDay*100 + SysTime.wHour;
		if (iDateSum2 >= iDateSum1) {
			// SNOOPY: Bug here ii wrong, should be iClientH
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FIGHTZONERESERVE, -2, NULL, NULL, NULL);
			m_pClientList[iClientH]->m_iFightzoneNumber = 0; 
			m_pClientList[iClientH]->m_iReserveTime = 0;
			m_pClientList[iClientH]->m_iFightZoneTicketNumber = 0;
		}
	}
	if (m_pClientList[iClientH]->m_iAdminUserLevel < 0) m_pClientList[iClientH]->m_iAdminUserLevel = 0;
	if (m_pClientList[iClientH]->m_cSex == 1) {
		sTmpType = 1;
	}
	else if (m_pClientList[iClientH]->m_cSex == 2) {
		sTmpType = 4; 
	}
	switch (m_pClientList[iClientH]->m_cSkin) {
	case 1:
		break;
	case 2:
		sTmpType ++;
		break;
	case 3:
		sTmpType += 2;
		break;
	}
	if (m_pClientList[iClientH]->m_iAdminUserLevel >= 10) sTmpType = m_pClientList[iClientH]->m_iAdminUserLevel;
	sTmpAppr1 = (m_pClientList[iClientH]->m_cHairStyle << 8) | (m_pClientList[iClientH]->m_cHairColor << 4) | (m_pClientList[iClientH]->m_cUnderwear);
	m_pClientList[iClientH]->m_sType  = sTmpType;
	m_pClientList[iClientH]->m_sAppr1 = sTmpAppr1;
	iCalcTotalWeight(iClientH);
	if (m_pClientList[iClientH]->m_sCharIDnum1 == 0) {
		int _i, _iTemp1, _iTemp2;
		short _sID1, _sID2, _sID3;
		_iTemp1 = 1;
		_iTemp2 = 1;
		for (_i = 0; _i < 10; _i++) {
			_iTemp1 += m_pClientList[iClientH]->m_cCharName[_i];
			_iTemp2 += abs(m_pClientList[iClientH]->m_cCharName[_i] ^ m_pClientList[iClientH]->m_cCharName[_i]);
		}
		_sID1 = (short)timeGetTime(); 
		_sID2 = (short)_iTemp1; 
		_sID3 = (short)_iTemp2; 
		m_pClientList[iClientH]->m_sCharIDnum1 = _sID1;
		m_pClientList[iClientH]->m_sCharIDnum2 = _sID2;
		m_pClientList[iClientH]->m_sCharIDnum3 = _sID3;
	}
	m_pClientList[iClientH]->m_iRewardGold += iNotUsedItemPrice;
	m_pClientList[iClientH]->m_iSpeedHackCheckExp = m_pClientList[iClientH]->m_iExp;
	return TRUE;
}


int CGame::_iComposePlayerDataFileContents(int iClientH, char * pData)
{
 SYSTEMTIME SysTime;
 char  cTxt[120], cTmp[21];
 POINT TempItemPosList[DEF_MAXITEMS];
 int   i;

	if (m_pClientList[iClientH] == NULL) return 0;

	GetLocalTime(&SysTime);
	strcat(pData, "[FILE-DATE]\n\n");
	
	wsprintf(cTxt, "file-saved-date: %d %d %d %d %d\n", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	strcat(pData, cTxt);
	strcat(pData, "\n");
		
	// ��횑쨍짠 ��첬��책
	strcat(pData, "[NAME-ACCOUNT]\n\n");
	strcat(pData, "character-name     = ");
	strcat(pData, m_pClientList[iClientH]->m_cCharName);
	strcat(pData, "\n");
	strcat(pData, "account-name       = ");
	strcat(pData, m_pClientList[iClientH]->m_cAccountName);
	strcat(pData, "\n\n");

	strcat(pData, "[STATUS]\n\n");
	// 횆쨀쨍짱횇횒 횉횁쨌횓횉횎 
	strcat(pData, "character-profile 	=");
	if (strlen(m_pClientList[iClientH]->m_cProfile) == 0) {
		// 횆쨀쨍짱횇횒 횉횁쨌횓횉횎��횑 쩌쨀횁짚쨉횉횁철 쩐횎쩐횘쨈횢쨍챕 
		strcat(pData, "__________");
	}
	else strcat(pData, m_pClientList[iClientH]->m_cProfile);
	strcat(pData, "\n");

	// 횉횄쨌쨔��횑쩐챤 쩌횘쩌횙 ��짠횆징
	strcat(pData, "character-location   = ");
	strcat(pData, m_pClientList[iClientH]->m_cLocation);
	strcat(pData, "\n");

	/// 짹챈쨉책 쨩처횇횂 
	strcat(pData, "character-guild-name = ");
	if (m_pClientList[iClientH]->m_iGuildRank != -1) {
		// GuildRank째징 -1��횑쨍챕 짹챈쨉책��횑쨍짠��쨘 쨔짬��횉쨔횑횉횕쨈횢.
		strcat(pData, m_pClientList[iClientH]->m_cGuildName);
	}
	else strcat(pData, "NONE");
	strcat(pData, "\n");
	
	// 짹챈쨉책 GUID 
	strcat(pData, "character-guild-GUID = ");
	if (m_pClientList[iClientH]->m_iGuildRank != -1) {
		// GuildRank째징 -1��횑쨍챕 짹챈쨉책GUID쨈횂 쨔짬��횉쨔횑횉횕쨈횢.
		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "%d", m_pClientList[iClientH]->m_iGuildGUID);
		strcat(pData, cTxt);
	}
	else strcat(pData, "-1");
	strcat(pData, "\n");
		
	// 짹챈쨉책 쩌첩��짠
	strcat(pData, "character-guild-rank = ");
	itoa( m_pClientList[iClientH]->m_iGuildRank, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");

	strcat(pData, "character-loc-map = ");
	strcat(pData, m_pClientList[iClientH]->m_cMapName);
	strcat(pData, "\n");
	// X횁횂횉짜 ��첬��책 
	strcat(pData, "character-loc-x   = ");
	itoa( m_pClientList[iClientH]->m_sX, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	// Y횁횂횉짜 ��첬��책 
	strcat(pData, "character-loc-y   = ");
	itoa( m_pClientList[iClientH]->m_sY, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n\n");
	//
	if (m_pClientList[iClientH]->m_iHP <= 0) m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH);
	wsprintf(cTxt, "character-HP       = %d", m_pClientList[iClientH]->m_iHP);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	if (m_pClientList[iClientH]->m_iMP < 0) m_pClientList[iClientH]->m_iMP = 0;
	wsprintf(cTxt, "character-MP       = %d",  m_pClientList[iClientH]->m_iMP);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	if (m_pClientList[iClientH]->m_iSP < 0) m_pClientList[iClientH]->m_iSP = 0; // v1.1
	wsprintf(cTxt, "character-SP       = %d",  m_pClientList[iClientH]->m_iSP);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-LEVEL    = %d", m_pClientList[iClientH]->m_iLevel);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-RATING   = %d", m_pClientList[iClientH]->m_iRating);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-STR      = %d", m_pClientList[iClientH]->m_iStr);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-INT      = %d", m_pClientList[iClientH]->m_iInt);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-VIT      = %d", m_pClientList[iClientH]->m_iVit);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-DEX      = %d", m_pClientList[iClientH]->m_iDex);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-MAG      = %d", m_pClientList[iClientH]->m_iMag);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-CHARISMA = %d", m_pClientList[iClientH]->m_iCharisma);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-LUCK     = %d", m_pClientList[iClientH]->m_iLuck);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-EXP      = %d", m_pClientList[iClientH]->m_iExp);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-LU_Pool  = %d", m_pClientList[iClientH]->m_iLU_Pool);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-EK-Count = %d", m_pClientList[iClientH]->m_iEnemyKillCount);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-PK-Count = %d", m_pClientList[iClientH]->m_iPKCount);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-reward-gold = %d", m_pClientList[iClientH]->m_iRewardGold);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-downskillindex = %d", m_pClientList[iClientH]->m_iDownSkillIndex);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-IDnum1 = %d", m_pClientList[iClientH]->m_sCharIDnum1);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-IDnum2 = %d", m_pClientList[iClientH]->m_sCharIDnum2);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-IDnum3 = %d", m_pClientList[iClientH]->m_sCharIDnum3);
	strcat(pData, cTxt);
	strcat(pData,"\n");


	wsprintf(cTxt, "party-rank = %d", m_pClientList[iClientH]->m_iPartyRank);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	

	//
	// 횉횄쨌쨔��횑쩐챤 횈짱쩌쨘횆징 ��횚쨌횂 
	strcat(pData, "sex-status       = ");
	itoa( m_pClientList[iClientH]->m_cSex, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "skin-status      = ");
	itoa( m_pClientList[iClientH]->m_cSkin, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "hairstyle-status = ");
	itoa( m_pClientList[iClientH]->m_cHairStyle, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "haircolor-status = ");
	itoa( m_pClientList[iClientH]->m_cHairColor, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "underwear-status = ");
	itoa( m_pClientList[iClientH]->m_cUnderwear, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");

	wsprintf(cTxt, "hunger-status    = %d", m_pClientList[iClientH]->m_iHungerStatus);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "timeleft-shutup  = %d", m_pClientList[iClientH]->m_iTimeLeft_ShutUp);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "timeleft-rating  = %d", m_pClientList[iClientH]->m_iTimeLeft_Rating);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "timeleft-force-recall  = %d", m_pClientList[iClientH]->m_iTimeLeft_ForceRecall);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "timeleft-firm-staminar = %d", m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "admin-user-level = %d", m_pClientList[iClientH]->m_iAdminUserLevel);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "penalty-block-date = %d %d %d", m_pClientList[iClientH]->m_iPenaltyBlockYear, m_pClientList[iClientH]->m_iPenaltyBlockMonth, m_pClientList[iClientH]->m_iPenaltyBlockDay);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-quest-number = %d", m_pClientList[iClientH]->m_iQuest);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-quest-ID     = %d", m_pClientList[iClientH]->m_iQuestID);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "current-quest-count    = %d", m_pClientList[iClientH]->m_iCurQuestCount);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "quest-reward-type      = %d", m_pClientList[iClientH]->m_iQuestRewardType);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "quest-reward-amount    = %d", m_pClientList[iClientH]->m_iQuestRewardAmount);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-contribution = %d", m_pClientList[iClientH]->m_iContribution);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-war-contribution = %d", m_pClientList[iClientH]->m_iWarContribution);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-quest-completed = %d", (int)m_pClientList[iClientH]->m_bIsQuestCompleted);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "special-event-id = %d", m_pClientList[iClientH]->m_iSpecialEventID);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "super-attack-left = %d", m_pClientList[iClientH]->m_iSuperAttackLeft);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// v1.4311-3 횄횩째징 쩔첫쨉책쩌짯쨔철쩔징 쨩챌횇천��책 째체쨌횄 쨘짱쩌철쨍짝 쨘쨍쨀쩍쨈횢.
	// 쨩챌횇천��책 쩔쨔쩐횪 째체쨌횄쨉횊 쨀쨩쩔챘 ��첬��책 reserved-fightzone-id 쩔쨔쩐횪쨉횊 쨩챌횇천��책쨔첩횊짙/쨀짱횂짜쨔횞쩍횄째짙/쨀짼��쨘횈쩌횆횕째쨔쩌철
	wsprintf(cTxt, "reserved-fightzone-id = %d %d %d", m_pClientList[iClientH]->m_iFightzoneNumber, m_pClientList[iClientH]->m_iReserveTime,m_pClientList[iClientH]->m_iFightZoneTicketNumber  );
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// 횈짱쩌철 쨈횋쨌횂 쨔횩횊횜쩔챘 쨀짼��쨘 쩍횄째짙
	wsprintf(cTxt, "special-ability-time = %d", m_pClientList[iClientH]->m_iSpecialAbilityTime);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// ��찼짹채 쨍횎 ��횑쨍짠
	wsprintf(cTxt, "locked-map-name = %s", m_pClientList[iClientH]->m_cLockedMapName);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// ��찼짹채 쨍횎 쩍횄째짙
	wsprintf(cTxt, "locked-map-time = %d", m_pClientList[iClientH]->m_iLockedMapTime);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// 횇짤쨌챌쩌쩌��횑쨉책쩔징쩌짯 쨍횄��쨘 횁첨횄짜.
	wsprintf(cTxt, "crusade-job = %d", m_pClientList[iClientH]->m_iCrusadeDuty);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// 횇짤쨌챌쩌쩌��횑쨉책 째챠��짱 쩐횈��횑쨉챨 
	wsprintf(cTxt, "crusade-GUID = %d", m_pClientList[iClientH]->m_dwCrusadeGUID);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "construct-point = %d", m_pClientList[iClientH]->m_iConstructionPoint);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// v2.04 쨩챌쨍횁쩍횄 횈채쨀횓횈쩌 횇쨍��횙 
	wsprintf(cTxt, "dead-penalty-time = %d", m_pClientList[iClientH]->m_iDeadPenaltyTime);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// v2.06 12-4 횈횆횈쩌 쩐횈��횑쨉챨
	wsprintf(cTxt, "party-id = %d", m_pClientList[iClientH]->m_iPartyID);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// v2.15 횁철횁쨍쩐횈��횑횇횤쩐첨짹횞쨌쨔��횑쨉책
	
	wsprintf(cTxt, "majestic-level = %d", m_pClientList[iClientH]->m_iMajesticLevel);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	
	wsprintf(cTxt, "gizon-item-upgrade-left = %d", m_pClientList[iClientH]->m_iGizonItemUpgradeLeft);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	// MORLA 2.2- Nuevos datos para el pj
	wsprintf(cTxt, "character-Deaths = %d", m_pClientList[iClientH]->m_iDeaths);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-TotalDGKills = %d", m_pClientList[iClientH]->m_iTotalDGKills);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-DGPoints = %d", m_pClientList[iClientH]->m_iDGPoints);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-TotalDGDeaths = %d", m_pClientList[iClientH]->m_iTotalDGDeaths);
	strcat(pData, cTxt);
	strcat(pData,"\n");
	
	wsprintf(cTxt, "character-DGKills = %d", m_pClientList[iClientH]->m_iDGKills);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "max-ek = %d", m_pClientList[iClientH]->m_iMaxEK);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	strcat(pData, "ip2 = "); 
	strcat(pData, m_pClientList[iClientH]->m_cIP2); 
	strcat(pData, "\n"); 
	
	strcat(pData, "ip = "); 
	strcat(pData, m_pClientList[iClientH]->m_cIPaddress); 
	strcat(pData, "\n");

	wsprintf(cTxt, "heldenian-GUID = %d", m_pClientList[iClientH]->m_dwHeldenianGUID);
	strcat(pData, cTxt);
	strcat(pData,"\n");

	wsprintf(cTxt, "character-wanted-level = %d", m_pClientList[iClientH]->m_iWantedLevel);
	strcat(pData, cTxt);
	strcat(pData, "\n");

	strcat(pData,"\n\n");

	// 횆쨀쨍짱횇횒��횉 쩔횥횉체횉짜횉철 Appr4째쨀쨍짝 ��첬��책횉횗쨈횢. ��횑째횒��쨘 째횚��횙쩌짯쨔철쩔징쩌짯쨈횂 쨩챌쩔챘횉횕횁철 쩐횎��쨍쨍챌 쨌횓짹횞쩌짯쨔철->횇짭쨋처��횑쩐챨횈짰째짙쩔징 쨩챌쩔챘쨉횊쨈횢.
	strcat(pData, "appr1 = ");
	itoa( m_pClientList[iClientH]->m_sAppr1, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "appr2 = ");
	// ��체횇천쨍챨쨉책 횉횄쨌징짹횞쨍짝 횇짭쨍짰쩐챤횉횗쨈횢.
	itoa( m_pClientList[iClientH]->m_sAppr2, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "appr3 = ");
	itoa( m_pClientList[iClientH]->m_sAppr3, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	strcat(pData, "appr4 = ");
	itoa( m_pClientList[iClientH]->m_sAppr4, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n");
	// v1.4 ApprColor
	strcat(pData, "appr-color = ");
	itoa( m_pClientList[iClientH]->m_iApprColor, cTxt, 10);
	strcat(pData, cTxt);
	strcat(pData, "\n\n");

	// 쩐횈��횑횇횤 횁짚쨘쨍 ��첬��책 
	strcat(pData, "[ITEMLIST]\n\n");

	for (i = 0; i < DEF_MAXITEMS; i++) { // v1.4
		TempItemPosList[i].x = 40;
		TempItemPosList[i].y = 30;
	}
	

	// 째짖째짖��횉 쩐횈��횑횇횤��쨩 ��첬��책횉횗쨈횢.
	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pClientList[iClientH]->m_pItemList[i] != NULL) {
		// v1.4 쩐횈��횑횇횤 쩌첩쩌짯쨍짝 ��챌쨔챔횆징횉횗쨈횢. 
		TempItemPosList[i].x = m_pClientList[iClientH]->m_ItemPosList[i].x;
		TempItemPosList[i].y = m_pClientList[iClientH]->m_ItemPosList[i].y;
		
		
		strcat(pData, "character-item = ");
		memset(cTmp, ' ', 21);
		strcpy(cTmp, m_pClientList[iClientH]->m_pItemList[i]->m_cName);
		cTmp[strlen(m_pClientList[iClientH]->m_pItemList[i]->m_cName)] = (char)' ';
		cTmp[20] = NULL;
		strcat(pData, cTmp);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_dwCount, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectType, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue1, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue2, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sTouchEffectValue3, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_cItemColor, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue1, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue2, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_sItemSpecEffectValue3, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_wCurLifeSpan, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemList[i]->m_dwAttribute, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, "\n");
	}
	strcat(pData, "\n\n");

	// v1.4 ��챌 째챔쨩챗쨉횊 쩐횈��횑횇횤 ��짠횆징 짹창쩐챦 
	for (i = 0; i < DEF_MAXITEMS; i++) {
		m_pClientList[iClientH]->m_ItemPosList[i].x = TempItemPosList[i].x; 
		m_pClientList[iClientH]->m_ItemPosList[i].y = TempItemPosList[i].y;
	}

	//m_cAccountName
	for (i = 0; i < DEF_MAXBANKITEMS; i++)
	if (m_pClientList[iClientH]->m_pItemInBankList[i] != NULL) {
		strcat(pData, "character-bank-item = ");
		memset(cTmp, ' ', 21);
		strcpy(cTmp, m_pClientList[iClientH]->m_pItemInBankList[i]->m_cName);
		cTmp[strlen(m_pClientList[iClientH]->m_pItemInBankList[i]->m_cName)] = (char)' ';
		cTmp[20] = NULL;
		strcat(pData, cTmp);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwCount, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectType, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue1, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue2, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sTouchEffectValue3, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_cItemColor, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue1, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue2, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_sItemSpecEffectValue3, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_wCurLifeSpan, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, " ");
		itoa( m_pClientList[iClientH]->m_pItemInBankList[i]->m_dwAttribute, cTxt, 10);
		strcat(pData, cTxt);
		strcat(pData, "\n");
	}
	strcat(pData, "\n\n");

	
	strcat(pData, "[MAGIC-SKILL-MASTERY]\n\n");

	strcat(pData, "//------------------012345678901234567890123456789012345678901234567890");
	strcat(pData,"\n");

	strcat(pData, "magic-mastery     = ");
	for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
		wsprintf(cTxt,"%d", (int)m_pClientList[iClientH]->m_cMagicMastery[i]);
		strcat(pData, cTxt);
	}
	strcat(pData, "\n");
	
	strcat(pData, "skill-mastery     = ");
			
	
	for (i = 0; i < 60; i++) {
		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "%d ", m_pClientList[iClientH]->m_cSkillMastery[i]);

		strcat(pData, cTxt); // 횄횎짹창째짧 ��횚쨌횂
	}
	strcat(pData,"\n");
			
	strcat(pData, "skill-SSN     = ");
	for (i = 0; i < 60; i++) {
		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "%d ", m_pClientList[iClientH]->m_iSkillSSN[i]);

		strcat(pData, cTxt); // 횄횎짹창째짧 ��횚쨌횂
	}
	strcat(pData,"\n");
	
	// 쩐횈��횑횇횤 ��책횂첩 쨩처횇횂쨍짝 ��첬��책횉횗쨈횢. 쨔횦쨉책쩍횄 쨍횉 쨍쨋횁철쨍쨌쩔징 ��횜쩐챤쩐횩 횉횚.
	strcat(pData, "[ITEM-EQUIP-STATUS]\n\n");
	strcat(pData, "item-equip-status = ");
	
	ZeroMemory(cTxt, sizeof(cTxt));
	strcpy(cTxt, "00000000000000000000000000000000000000000000000000");
	              
	int iEP = 0;
	for (i = 0; i < DEF_MAXITEMS; i++) 
	if (m_pClientList[iClientH]->m_pItemList[i] != NULL) {
		if ((m_pClientList[iClientH]->m_bIsItemEquipped[i] == TRUE) && 
			(m_pClientList[iClientH]->m_pItemList[i]->m_cItemType == DEF_ITEMTYPE_EQUIP)) {
			 cTxt[iEP] = '1';
		}
		iEP++;
	}
	strcat(pData, cTxt);
	strcat(pData, "\n");

	
	strcat(pData, "item-position-x = ");
	for (i = 0; i < DEF_MAXITEMS; i++) {
		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "%d ", m_pClientList[iClientH]->m_ItemPosList[i].x);
		strcat(pData, cTxt);
	}
	strcat(pData, "\n");
	
	strcat(pData, "item-position-y = ");
	for (i = 0; i < DEF_MAXITEMS; i++) {
		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "%d ", m_pClientList[iClientH]->m_ItemPosList[i].y);
		strcat(pData, cTxt);
	}
	strcat(pData, "\n\n");
	
	strcat(pData, "[EOF]");
	strcat(pData, "\n\n\n\n");

	return strlen(pData);
}
#endif

/*********************************************************************************************************************
**  BOOL CGame::_bGetIsStringIsNumber(char * pStr)																	**
**  DESCRIPTION			:: checks if valid ASCII value																**
**  LAST_UPDATED		:: March 17, 2005; 2:24 PM; Hypnotoad														**
**	RETURN_VALUE		:: BOOL																						**
**  NOTES				::	n/a																						**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
BOOL CGame::_bGetIsStringIsNumber(char * pStr)
{
 int i;
	for (i = 0; i < (int)strlen(pStr); i++)
	if ((pStr[i] != '-') && ((pStr[i] < (char)'0') || (pStr[i] > (char)'9'))) return FALSE;
	
	return TRUE;
}

/*********************************************************************************************************************
**  void CGame::ChatMsgHandler(int iClientH, char * pData, DWORD dwMsgSize)											**
**  DESCRIPTION			:: manages chatting																			**
**  LAST_UPDATED		:: March 18, 2005; 7:28 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- new Crop DeleteNpc after specific amount of time										**
**							- disabled /setobservermode																**
**							- "/gns " changed to 5 to work correctly !												**
**	MODIFICATION		::	- all chat is logged if enabled 														**
**							- /enableadmincreateitem is disabled													**
**							- REMOVED" /blueball, /redball, /yellowball, /weather, /time, /checkstatus, /summonguild**
**							/summondeath, /kill, /revive, /unsummondemon, /setserk, /setfreeze, /setstatus, /storm	**
**							- ADDED: /version, /clearnpc, /clearmap, /who, /checkrep, /send, /summonall				** 			
**********************************************************************************************************************/
void CGame::ChatMsgHandler(int iClientH, char * pData, DWORD dwMsgSize)
{
 int i, iRet;
 WORD * wp;
 int  * ip;
 char * cp, * cp2;
 char   cBuffer[256], cTemp[256], cSendMode = NULL;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (dwMsgSize > 113) return;
	if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) return;
	if (memcmp((pData + 10), m_pClientList[iClientH]->m_cCharName, strlen(m_pClientList[iClientH]->m_cCharName)) != 0) return;
	if ((m_pClientList[iClientH]->m_bIsObserverMode == TRUE) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) return;
 
	cp = (char *)(pData + 21);
	m_pClientList[iClientH]->m_dwAFKCheckTime = timeGetTime();
	// Modification - chat logging
	switch (m_bLogChatOption) {
		// Chat Logs of only players
		case 1:
			if (m_pClientList[iClientH]->m_iAdminUserLevel == 0){
				ZeroMemory(cTemp,sizeof(cTemp));
				pData[dwMsgSize-1] = 0;
				wsprintf(cTemp,"Loc(%s) IP(%s) PC(%s):\"%s\"",m_pClientList[iClientH]->m_cMapName,m_pClientList[iClientH]->m_cIPaddress,m_pClientList[iClientH]->m_cCharName,cp);
				bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
			}
			break;
		// Chat Logs of only GM
		case 2:
			if (m_pClientList[iClientH]->m_iAdminUserLevel > 0){
				ZeroMemory(cTemp,sizeof(cTemp));
				pData[dwMsgSize-1] = 0;
				wsprintf(cTemp,"Loc(%s) IP(%s) GM(%s):\"%s\"",m_pClientList[iClientH]->m_cMapName,m_pClientList[iClientH]->m_cIPaddress,m_pClientList[iClientH]->m_cCharName,cp);
				bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
			}
			break;
		// Chat logs of all
		case 3:
			if (m_pClientList[iClientH]->m_iAdminUserLevel > 0){
				ZeroMemory(cTemp,sizeof(cTemp));
				pData[dwMsgSize-1] = 0;
				wsprintf(cTemp,"Loc(%s) IP(%s) GM(%s):\"%s\"",m_pClientList[iClientH]->m_cMapName,m_pClientList[iClientH]->m_cIPaddress,m_pClientList[iClientH]->m_cCharName,cp);
				bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
			}
			else{
				ZeroMemory(cTemp,sizeof(cTemp));
				pData[dwMsgSize-1] = 0;
				wsprintf(cTemp,"Loc(%s) IP(%s) PC(%s):\"%s\"",m_pClientList[iClientH]->m_cMapName,m_pClientList[iClientH]->m_cIPaddress,m_pClientList[iClientH]->m_cCharName,cp);
				bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
			}	
			break;
		// Chat logs of none
		case 4:		
			break;
	}

	switch (*cp) {
	case '@':
		*cp = 32;
		if ((strlen(cp) < 90) && (m_pClientList[iClientH]->m_iGuildRank == 0)) {
			ZeroMemory(cTemp, sizeof(cTemp));
			cp2 = (char *)cTemp;
			*cp2 = GSM_CHATMSG;
			cp2++;
			*cp2 = 1;
			cp2++;
			ip = (int *)cp2;
			*ip = m_pClientList[iClientH]->m_iGuildGUID;
			cp2 += 4;
			memcpy(cp2, m_pClientList[iClientH]->m_cCharName, 10);
			cp2 += 10;
			wp  = (WORD *)cp2;
			*wp = (WORD)strlen(cp);
			cp2 += 2;
			strcpy(cp2, cp);
			cp2 += strlen(cp);
			bStockMsgToGateServer(cTemp, strlen(cp) + 18);
		}
				
		if ( (m_pClientList[iClientH]->m_iTimeLeft_ShutUp == 0) && (m_pClientList[iClientH]->m_iLevel > 1) && 
			 (m_pClientList[iClientH]->m_iSP >= 3) ) {
			if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
				m_pClientList[iClientH]->m_iSP -= 3;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
			}
			cSendMode = 1;
		}
		else 
			if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
		break;

	case '$':
		*cp = 32;
		if ((m_pClientList[iClientH]->m_iTimeLeft_ShutUp == 0) && (m_pClientList[iClientH]->m_iSP >= 3)){
			if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
				m_pClientList[iClientH]->m_iSP -= 3;
				SendNotifyMsg(NULL,iClientH,DEF_NOTIFY_SP,NULL,NULL,NULL,NULL);
			}
			cSendMode = 4;
		}
		else
		
			if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
			
		break;

	case '^':
		*cp = 32;
		if ((strlen(cp) < 90) && (m_pClientList[iClientH]->m_iAdminUserLevel > 0)) {
			ZeroMemory(cTemp, sizeof(cTemp));
			cp2 = (char *)cTemp;
			*cp2 = GSM_CHATMSG;
			cp2++;
			*cp2 = 10;
			cp2++;
			ip = (int *)cp2;
			*ip = NULL;
			cp2 += 4;
			memcpy(cp2, m_pClientList[iClientH]->m_cCharName, 10);
			cp2 += 10;
			wp  = (WORD *)cp2;
			*wp = (WORD)strlen(cp);
			cp2 += 2;
			strcpy(cp2, cp);
			cp2 += strlen(cp);
			bStockMsgToGateServer(cTemp, strlen(cp) + 18);
		}
		if ((strlen(cp) < 90) && (m_pClientList[iClientH]->m_iGuildRank != -1)) {
			ZeroMemory(cTemp, sizeof(cTemp));
			cp2 = (char *)cTemp;
			*cp2 = GSM_CHATMSG;
			cp2++;
			*cp2 = 1;
			cp2++;
			ip = (int *)cp2;
			*ip = m_pClientList[iClientH]->m_iGuildGUID;
			cp2 += 4;
			memcpy(cp2, m_pClientList[iClientH]->m_cCharName, 10);
			cp2 += 10;
			wp  = (WORD *)cp2;
			*wp = (WORD)strlen(cp);
			cp2 += 2;
			strcpy(cp2, cp);
			cp2 += strlen(cp);
			bStockMsgToGateServer(cTemp, strlen(cp) + 18);
		}

		if ( (m_pClientList[iClientH]->m_iTimeLeft_ShutUp == 0) && (m_pClientList[iClientH]->m_iLevel > 10) && 
			(m_pClientList[iClientH]->m_iSP > 5) && m_pClientList[iClientH]->m_iGuildRank != -1) {
				if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
					m_pClientList[iClientH]->m_iSP -= 3;
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
				}
				cSendMode = 1;
			}
		else {
			if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
			if (m_pClientList[iClientH]->m_iHP <= 0) cSendMode = NULL;
		}
		if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) cSendMode = 10;
		break;

	case '!':
		*cp = 32;
		if ((strlen(cp) < 90) && (m_pClientList[iClientH]->m_iAdminUserLevel > 0)) {
			ZeroMemory(cTemp, sizeof(cTemp));
			cp2 = (char *)cTemp;
			*cp2 = GSM_CHATMSG;
			cp2++;
			*cp2 = 10;
			cp2++;
			ip = (int *)cp2;
			*ip = NULL;
			cp2 += 4;
			memcpy(cp2, m_pClientList[iClientH]->m_cCharName, 10);
			cp2 += 10;
			wp  = (WORD *)cp2;
			*wp = (WORD)strlen(cp);
			cp2 += 2;
			strcpy(cp2, cp);
			cp2 += strlen(cp);
			bStockMsgToGateServer(cTemp, strlen(cp) + 18);
		}
		if ( (m_pClientList[iClientH]->m_iTimeLeft_ShutUp == 0) && (m_pClientList[iClientH]->m_iLevel > 10) && 
			 (m_pClientList[iClientH]->m_iSP >= 5) ) {
			if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
				m_pClientList[iClientH]->m_iSP -= 5;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
			}
			cSendMode = 2;
		}
		else {
			if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
			if (m_pClientList[iClientH]->m_iHP <= 0) cSendMode = NULL;
		}
		if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) cSendMode = 10;
		break;

	case '~':
		*cp = 32;
		if ( (m_pClientList[iClientH]->m_iTimeLeft_ShutUp == 0) && (m_pClientList[iClientH]->m_iLevel > 1) && 
			 (m_pClientList[iClientH]->m_iSP >= 3) ) {
			if (m_pClientList[iClientH]->m_iTimeLeft_FirmStaminar == 0) {
				m_pClientList[iClientH]->m_iSP -= 3;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
			}
			cSendMode = 3;
		}
		else {
			if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
			if (m_pClientList[iClientH]->m_iHP <= 0) cSendMode = NULL;
		}
		break;

	case '/':
		ZeroMemory(cBuffer, sizeof(cBuffer));
		memcpy(cBuffer, cp, dwMsgSize - 21);
		cp = (char *)(cBuffer);

		if (memcmp(cp, "/fi ", 4) == 0) {
			CheckAndNotifyPlayerConnection(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/to", 3) == 0) {
			ToggleWhisperPlayer(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/setpf ", 7) == 0) {
			SetPlayerProfile(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/pf ", 4) == 0) {
			GetPlayerProfile(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/shutup ", 8) == 0) {
			ShutUpPlayer(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/rep+ ", 6) == 0) {
			SetPlayerReputation(iClientH, cp, 1, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/rep- ", 6) == 0) {
			SetPlayerReputation(iClientH, cp, 0, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/hold", 5) == 0) {
			SetSummonMobAction(iClientH, 1, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/tgt ", 5) == 0) {
			SetSummonMobAction(iClientH, 2, dwMsgSize - 21, cp);
			
		}

		else if (memcmp(cp, "/free", 5) == 0) {
			SetSummonMobAction(iClientH, 0, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/closeconn ", 11) == 0) {
			AdminOrder_CloseConn(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/ban", 4) == 0) {
			UserCommand_BanGuildsman(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/reservefightzone", 17) == 0) {
			AdminOrder_ReserveFightzone(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/attack ", 8) == 0) {
			AdminOrder_CallGuard(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/createfish ", 12) == 0) {
			AdminOrder_CreateFish(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/teleport ", 10) == 0 || memcmp(cp, "/tp ", 4) == 0) {
			AdminOrder_Teleport(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/goto ", 6) == 0) {
			AdminOrder_GoTo(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/summondemon ", 13) == 0) {
			AdminOrder_SummonDemon(iClientH);
			
		}

		else if (memcmp(cp, "/summonplayer ", 14) == 0) {
			AdminOrder_SummonPlayer(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/unsummonall ", 13) == 0) {
			AdminOrder_UnsummonAll(iClientH);
						
		}

		else if (memcmp(cp, "/unsummonboss", 13) == 0) {
			AdminOrder_UnsummonBoss(iClientH);
			
		}

		else if (memcmp(cp, "/checkip ", 9) == 0) {
			AdminOrder_CheckIP(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/polymorph ", 11) == 0) {
			AdminOrder_Polymorph(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/setinvi ", 9) == 0) {
			AdminOrder_SetInvi(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/gns ", 5) == 0) { // changed to 5...
			AdminOrder_GetNpcStatus(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/setattackmode ", 15) == 0) {
			AdminOrder_SetAttackMode(iClientH, cp, dwMsgSize - 21);
				
		}

		else if (memcmp(cp, "/setforcerecalltime ", 20) == 0) {
			AdminOrder_SetForceRecallTime(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/summon ", 8) == 0) {
			AdminOrder_Summon(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/disconnectall", 14) == 0) {
			AdminOrder_DisconnectAll(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/createitem ", 12) == 0) {
			AdminOrder_CreateItem(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/enableadmincommand ", 20) == 0) {
			AdminOrder_EnableAdminCommand(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/monstercount", 13) == 0) {
			AdminOrder_MonsterCount(iClientH,cp,dwMsgSize - 21);
			
		}


		else if (memcmp(cp, "/begincrusade", 13) == 0) {
			if (m_pClientList[iClientH]->m_iAdminUserLevel > 3) {
				GlobalStartCrusadeMode();
				wsprintf(cTemp, "(%s) GM Order(%s): begincrusadetotalwar", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
			}
			
		}

#ifdef TEXTOUT
		else if (memcmp(cp, "/textout", 8) == 0) {
			TextOut2();
			ShowClientMsg(iClientH, "Hello World");
			
		}
#endif
		
		else if (memcmp(cp, "/endcrusade", 11) == 0) {
			if (m_pClientList[iClientH]->m_iAdminUserLevel > 3) {
				ManualEndCrusadeMode(0);
				wsprintf(cTemp, "(%s) GM Order(%s): endcrusadetotalwar", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
			}
			
		}

		else if (memcmp(cp, "/createparty", 12) == 0) {
			RequestCreatePartyHandler(iClientH);
			
		}

		else if (memcmp(cp, "/joinparty ", 11) == 0) {
			RequestJoinPartyHandler(iClientH,cp,dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/dismissparty", 13) == 0) {
			RequestDismissPartyHandler(iClientH);
			
		}

		else if (memcmp(cp, "/getpartyinfo", 13) == 0) {
			GetPartyInfoHandler(iClientH);
			
		}

		else if (memcmp(cp, "/deleteparty", 12) == 0) {
			RequestDeletePartyHandler(iClientH);
			
		}

		else if ((memcmp(cp, "/shutdown", 9) == 0) && (m_pClientList[iClientH]->m_iAdminUserLevel >= m_iAdminLevelShutdown)) {
			m_cShutDownCode      = 2;
			m_bOnExitProcess     = TRUE;
			m_dwExitProcessTime  = timeGetTime();
			PutLogList("(!) GAME SERVER SHUTDOWN PROCESS BEGIN(by Admin-Command)!!!");
			bSendMsgToLS(MSGID_GAMESERVERSHUTDOWNED, NULL);
			
		}

		else if ((memcmp(cp, "/getticket", 10) == 0) && (m_pClientList[iClientH]->m_iAdminUserLevel >= 2)) {
			AdminOrder_GetFightzoneTicket(iClientH);
			
		}

		else if (memcmp(cp, "/beginapocalypse", 16) == 0) // SNOOPY reactivated these function
		{	if (   (m_pClientList[iClientH]->m_iAdminUserLevel >= 3)
				&& (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == TRUE)) 
			{	wsprintf(cTemp, "GM Order(%-10s): /beginapocalypse", m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
				GlobalStartApocalypseMode(iClientH, 0);
			}
		}
		else if (memcmp(cp, "/openapocalypsegate", 19) == 0)
		{	if (   (m_pClientList[iClientH]->m_iAdminUserLevel >= 3) 
				&& (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == TRUE)) 
			{	wsprintf(cTemp, "GM Order(%-10s): /openapocalypsegate", m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
				GlobalStartApocalypseMode(iClientH, 1);
			}
		}
		else if (memcmp(cp, "/closeapocalypsegate", 20) == 0)
		{	if (   (m_pClientList[iClientH]->m_iAdminUserLevel >= 3)
				&& (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == TRUE))  
			{	wsprintf(cTemp, "GM Order(%-10s): /closeapocalypsegate", m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
				GlobalStartApocalypseMode(iClientH, 2);
			}
		}
		else if (memcmp(cp, "/endapocalypse", 14) == 0)
		{	if (   (m_pClientList[iClientH]->m_iAdminUserLevel >= 3) 	
				&& (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == TRUE)) 
			{	wsprintf(cTemp, "GM Order(%-10s): /endapocalypse", m_pClientList[iClientH]->m_cCharName);
				bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
				GlobalEndApocalypseMode(iClientH);
			}
		}	

		else if (memcmp(cp, "/beginheldenian ", 16) == 0)	//m_iAdminLevelSpecialEvents
		{	wsprintf(cTemp, "GM Order(%-10s): /beginheldenian", m_pClientList[iClientH]->m_cCharName);
			bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
			ManualStartHeldenianMode(iClientH, cp, dwMsgSize - 21); 
			
		}		
		else if (memcmp(cp, "/endheldenian ", 14) == 0)		//m_iAdminLevelSpecialEvents
		{	wsprintf(cTemp, "GM Order(%-10s): /endheldenian", m_pClientList[iClientH]->m_cCharName);
			bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, cTemp);
			ManualEndHeldenianMode(iClientH, cp, dwMsgSize - 21);
			
		}

		// Modification 
		// New 19/05/2004
		else if (memcmp(cp, "/clearnpc", 9) == 0)
		{
			AdminOrder_ClearNpc(iClientH);
			
		}
		else if (memcmp(cp, "/clearmap", 9) == 0) 
		{
			AdminOrder_CleanMap(iClientH, cp, dwMsgSize);
			
		}

		else if (memcmp(cp, "/who", 4) == 0) 
		{
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_TOTALUSERS, NULL, NULL, NULL, NULL);
			
		}

		//50Cent - Capture The Flag
		else if (memcmp(cp, "/startctf", 9) == 0) {
			if (m_pClientList[iClientH]->m_iAdminUserLevel >= 3) StartCaptureTheFlag();
			
		}
		else if (memcmp(cp, "/endctf", 7) == 0) {
			if (m_pClientList[iClientH]->m_iAdminUserLevel >= 3) EndCaptureTheFlag(0);
			
		}
		
		else if (memcmp(cp, "/deathmatch", 11) == 0) {
            if (m_pClientList[iClientH]->m_iAdminUserLevel < 3) return;
			DeathmatchGame();
			
		}
		
		else if (memcmp(cp, "/onlines", 8) == 0) { // Centuu: muestra la cantidad total de Ares/Elv/Trav/GMs conectados.
			if (m_pClientList[iClientH]->m_iAdminUserLevel >= m_iAdminLevelWho) {
				char cMsg[120];
				int iAres = 0, iElv = 0, iTrav = 0, iGM = 0;
				for (int i = 1; i < DEF_MAXCLIENTS; i++) {
					if (m_pClientList[i] != NULL) {
						if (memcmp(m_pClientList[i]->m_cLocation, "are", 1) == 0 &&
							m_pClientList[i]->m_iAdminUserLevel == 0) iAres++;
						else if (memcmp(m_pClientList[i]->m_cLocation, "elv", 2) == 0 &&
							m_pClientList[i]->m_iAdminUserLevel == 0) iElv++;
						else if (memcmp(m_pClientList[i]->m_cLocation, "NONE", 3) == 0 &&
							m_pClientList[i]->m_iAdminUserLevel == 0) iTrav++;
						else if	(m_pClientList[i]->m_iAdminUserLevel > 0) iGM++;
					}
				}
				ZeroMemory(cMsg, sizeof(cMsg));
				wsprintf(cMsg, "Ares: %d | Elv: %d | Trav: %d | GM: %d", iAres, iElv, iTrav, iGM);
				SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, cMsg);
			}
			
		}

		else if (memcmp(cp, "/addmaster ", 11) == 0) {
            PlayerCommandAddMaster(iClientH, cp, dwMsgSize - 21);
            
        }
		else if (memcmp(cp, "/deletemaster ", 13) == 0) {
            PlayerOrder_DeleteGuildMaster(iClientH, cp, dwMsgSize - 21);
            
        }

		else if (memcmp(cp, "/save", 5) == 0) {
			if (bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATALOGOUT, iClientH) == FALSE) LocalSavePlayerData(iClientH);
			SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "Data saved!");
			
		}

		else if (memcmp(cp, "/banpj ", 7) == 0) { // MORLA - 2.12 Cagar pc del player
			AdminOrder_BanPj(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/banip ", 7) == 0) {
			AdminOrder_BanIP(iClientH, cp, dwMsgSize - 21);
			
		}

		
		else if (memcmp(cp, "/summonguild ", 13) == 0) {
			AdminOrder_SummonGuild(iClientH, cp, dwMsgSize - 21);
			
		}

		else if (memcmp(cp, "/checkrep ", 10) == 0) {
			AdminOrder_CheckRep(iClientH,cp, dwMsgSize - 21);
			
		}		

		else if (memcmp(cp, "/send ", 5) == 0) {
			AdminOrder_Pushplayer(iClientH, cp, dwMsgSize -21);
			
		}

		else if (memcmp(cp, "/summonall ", 11) == 0) {
			AdminOrder_SummonAll(iClientH, cp, dwMsgSize - 21);
			
		}

		//LifeX Auto Skills
		if (memcmp(cp, "/getskills", 10) == 0)
		{
			if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0)
			{
				SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You can't use this command as a Traveller!");
				return;
			}
			else
			AutoSkill(iClientH);
		}

		//LifeX Fix Revive 14/10/2019
		if (memcmp(cp, "/revive ", 8) == 0) {
			AdminOrder_Revive(iClientH, cp, dwMsgSize - 21);

		}

		return;
	}
	pData[dwMsgSize-1] = NULL;
	
	// SNOOPY: designed non corean confuse language		
	if ((m_pClientList[iClientH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_CONFUSE ] == 1)) {
		// Confuse Language
		cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 17);		
		while (*cp != NULL) {
			if ((cp[0] != NULL) && (cp[1] != NULL)) 
			{	switch (iDice(1,12)) {
				case 1:	memcpy(cp, "ma", 2); break;
				case 2:	memcpy(cp, "fo", 2); break;
				case 3:	memcpy(cp, "ru", 2); break;
				case 4:	memcpy(cp, "be", 2); break;
				case 5:	memcpy(cp, "xy", 2); break;
				case 6:	memcpy(cp, "ce", 2); break;
				case 7:	memcpy(cp, "li", 2); break;
				case 8:	memcpy(cp, "re", 2); break;
				case 9:	memcpy(cp, "su", 2); break;
				case 10:memcpy(cp, "to", 2); break;
				case 11:memcpy(cp, "ju", 2); break;
				case 12:memcpy(cp, "de", 2); break;
				}
				if (cp[1] != ' ')
				switch (iDice(1,12)) {
				case 1:	
				case 2:	
				case 3:	
				case 4:	
				case 5:	break;
				case 6:	memcpy(cp, "a ", 2); break;
				case 7:	
				case 8:	memcpy(cp, "e ", 2); break;
				case 9:	memcpy(cp, "i ", 2); break;
				case 10:memcpy(cp, "o ", 2); break;
				case 11:memcpy(cp, "u ", 2); break;
				case 12:memcpy(cp, "y ", 2); break;
				}	
				if (cp[0] != ' ')
				switch (iDice(1,12)) {
				case 1:	
				case 2:	
				case 3:	
				case 4:	
				case 5:	break;
				case 6:	memcpy(cp, " c", 2); break;
				case 7:	
				case 8:	memcpy(cp, " s", 2); break;
				case 9:	memcpy(cp, " t", 2); break;
				case 10:memcpy(cp, " l", 2); break;
				case 11:memcpy(cp, " r", 2); break;
				case 12:memcpy(cp, " n", 2); break;
				}				
				cp += 2;
			}
			else cp++; 
		}
	}
		
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 17);
	if ((cSendMode == NULL) && (m_pClientList[iClientH]->m_iWhisperPlayerIndex != -1)) {
		cSendMode = 20;
 		if (*cp == '#') cSendMode = NULL;
		if (m_pClientList[iClientH]->m_iTimeLeft_ShutUp > 0) cSendMode = NULL;
	}
	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	*wp = (WORD)iClientH;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 16);
	*cp = cSendMode;

	if (cSendMode != 20) {
		for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) {
			switch (cSendMode) {
			case NULL:
				if (m_pClientList[i]->m_bIsInitComplete == FALSE) break;
				if ((m_pClientList[i]->m_cMapIndex == m_pClientList[iClientH]->m_cMapIndex) &&
					 (m_pClientList[i]->m_sX > m_pClientList[iClientH]->m_sX - 13) && // 10
					 (m_pClientList[i]->m_sX < m_pClientList[iClientH]->m_sX + 13) && // 10
					 (m_pClientList[i]->m_sY > m_pClientList[iClientH]->m_sY - 10) && // 7
					 (m_pClientList[i]->m_sY < m_pClientList[iClientH]->m_sY + 10)) { // 7
					iRet = m_pClientList[i]->m_pXSock->iSendMsg(pData, dwMsgSize);
				}
				break;
					
			case 1:
				if (m_pClientList[i]->m_bIsInitComplete == FALSE) break;
				if ((memcmp(m_pClientList[i]->m_cGuildName, m_pClientList[iClientH]->m_cGuildName, 20) == 0) &&
					(memcmp(m_pClientList[i]->m_cGuildName, "NONE", 4) != 0)) {					
					iRet = m_pClientList[i]->m_pXSock->iSendMsg(pData, dwMsgSize);
				}
				break;
					
			case 2:
			case 10:
				iRet = m_pClientList[i]->m_pXSock->iSendMsg(pData, dwMsgSize);
				break;
					
			case 3:
				if (m_pClientList[i]->m_bIsInitComplete == FALSE) break;
				if ( (m_pClientList[i]->m_cSide == m_pClientList[iClientH]->m_cSide) ) 
					iRet = m_pClientList[i]->m_pXSock->iSendMsg(pData, dwMsgSize);
				break;

			case 4:
				if (m_pClientList[i]->m_bIsInitComplete == FALSE) break;
				if ((m_pClientList[i]->m_iPartyID != NULL) && (m_pClientList[i]->m_iPartyID == m_pClientList[iClientH]->m_iPartyID) ) 
					iRet = m_pClientList[i]->m_pXSock->iSendMsg(pData, dwMsgSize);
				break;
			}
		}
	}
	else {
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(pData, dwMsgSize);	
		if (m_pClientList[iClientH]->m_iWhisperPlayerIndex == 10000) {
			ZeroMemory(cBuffer, sizeof(cBuffer));
			cp = (char *)cBuffer;
			*cp = GSM_WHISFERMSG;
			cp++;
			memcpy(cp, m_pClientList[iClientH]->m_cWhisperPlayerName, 10);
			cp += 10;

			wp = (WORD *)cp;
			*wp = (WORD)dwMsgSize;
			cp += 2;
			memcpy(cp, pData, dwMsgSize);
			cp += dwMsgSize;
			bStockMsgToGateServer(cBuffer, dwMsgSize+13);
		}
		else{
			if (m_pClientList[ m_pClientList[iClientH]->m_iWhisperPlayerIndex ] != NULL && strcmp(m_pClientList[iClientH]->m_cWhisperPlayerName, m_pClientList[ m_pClientList[iClientH]->m_iWhisperPlayerIndex ]->m_cCharName) == 0){
				iRet = m_pClientList[m_pClientList[iClientH]->m_iWhisperPlayerIndex]->m_pXSock->iSendMsg(pData, dwMsgSize);	
				switch (m_bLogChatOption){
					case 1:
						if (m_pClientList[m_pClientList[iClientH]->m_iWhisperPlayerIndex]->m_iAdminUserLevel == 0){
							ZeroMemory(cTemp,sizeof(cTemp));
							wsprintf(cTemp,"GM Whisper   (%s):\"%s\"\tto Player(%s)",m_pClientList[iClientH]->m_cCharName, pData+21, m_pClientList[iClientH]->m_cWhisperPlayerName);
							bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
						}
						break;
					case 2:
						if (m_pClientList[m_pClientList[iClientH]->m_iWhisperPlayerIndex]->m_iAdminUserLevel > 0){
							ZeroMemory(cTemp,sizeof(cTemp));
							wsprintf(cTemp,"GM Whisper   (%s):\"%s\"\tto GM(%s)",m_pClientList[iClientH]->m_cCharName, pData+21, m_pClientList[iClientH]->m_cWhisperPlayerName);
							bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
						}
						break;
						case 3:
						if (m_pClientList[m_pClientList[iClientH]->m_iWhisperPlayerIndex]->m_iAdminUserLevel > 0){
							ZeroMemory(cTemp,sizeof(cTemp));
							wsprintf(cTemp,"GM Whisper   (%s):\"%s\"\tto GM(%s)",m_pClientList[iClientH]->m_cCharName, pData+21, m_pClientList[iClientH]->m_cWhisperPlayerName);
							bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
						}
						else{
							ZeroMemory(cTemp,sizeof(cTemp));
							wsprintf(cTemp,"Player Whisper   (%s):\"%s\"\tto Player(%s)",m_pClientList[iClientH]->m_cCharName, pData+21, m_pClientList[iClientH]->m_cWhisperPlayerName);
							bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH, FALSE,cTemp);
						}
						break;
					case 4:
						break;
				}
			}
		}
	}
}

/*********************************************************************************************************************
**  void CGame::ChatMsgHandlerGSM(int iMsgType, int iV1, char * pName, char * pData, DWORD dwMsgSize)				**
**  DESCRIPTION			:: manages Npc variables																	**
**  LAST_UPDATED		:: March 18, 2005; 6:30 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	- new Crop DeleteNpc after specific amount of time										**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
void CGame::ChatMsgHandlerGSM(int iMsgType, int iV1, char * pName, char * pData, DWORD dwMsgSize)
{
 int i, iRet;
 DWORD * dwp;
 WORD * wp;
 short * sp;
 char * cp, cTemp[256], cSendMode = NULL;

	ZeroMemory(cTemp, sizeof(cTemp));
	
	dwp = (DWORD *)cTemp;
	*dwp = MSGID_COMMAND_CHATMSG;
	
	wp  = (WORD *)(cTemp + DEF_INDEX2_MSGTYPE);
	*wp = NULL;

	cp  = (char *)(cTemp + DEF_INDEX2_MSGTYPE + 2);
	sp  = (short *)cp;
	*sp = NULL;
	cp += 2;

	sp  = (short *)cp;
	*sp = NULL;
	cp += 2;
	
	memcpy(cp, pName, 10);
	cp += 10;

	*cp = (char)iMsgType;
	cp++;

	memcpy(cp, pData, dwMsgSize);
	cp += dwMsgSize;

	switch (iMsgType) {
	case 1:
		for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) {
			if (m_pClientList[i]->m_bIsInitComplete == FALSE) break;
			if ( (m_pClientList[i]->m_iGuildGUID == iV1) && (m_pClientList[i]->m_iGuildGUID != 0)) {
				iRet = m_pClientList[i]->m_pXSock->iSendMsg(cTemp, dwMsgSize +22);
			}
		}
		break;

	case 2:
	case 10:
		for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) {
			iRet = m_pClientList[i]->m_pXSock->iSendMsg(cTemp, dwMsgSize +22);
		}
		break;
	}
}

/*********************************************************************************************************************
**  int CGame::iClientMotion_Attack_Handler(int iClientH, short sX, short sY, short dX, short dY, short wType,		**
**		char cDir, WORD wTargetObjectID, BOOL bResponse, BOOL bIsDash)												**
**  DESCRIPTION			:: controls player attack																	**
**  LAST_UPDATED		:: March 19, 2005; 1:21 PM; Hypnotoad														**
**	RETURN_VALUE		:: int																						**
**  NOTES				::	- added checks for Firebow and Directionbow to see if player is m_bIsInsideWarehouse,	**
**							m_bIsInsideWizardTower, m_bIsInCombatantOnlyZone										**
**							- added ability to attack moving object													**
**							- fixed attack unmoving object															**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
int CGame::iClientMotion_Attack_Handler(int iClientH, short sX, short sY, short dX, short dY, short wType, char cDir, WORD wTargetObjectID, BOOL bResponse, BOOL bIsDash)
{
 char cData[100];
 DWORD * dwp, dwTime;
 WORD  * wp;
 int     iRet, tdX = 0, tdY = 0, i;
 short   sOwner, sAbsX, sAbsY;
 char    cOwnerType;
 BOOL    bNearAttack = FALSE, var_AC = FALSE;
 short sItemIndex;
 int tX, tY, iErr;
 unsigned long iExp;

	if (m_pClientList[iClientH] == NULL) return 0;
	if ((cDir <= 0) || (cDir > 8))       return 0;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return 0;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return 0;
	dwTime = timeGetTime();
	m_pClientList[iClientH]->m_dwLastActionTime = dwTime;
	m_pClientList[iClientH]->m_iAttackMsgRecvCount++;
	if (m_pClientList[iClientH]->m_iAttackMsgRecvCount >= 7) {
		if (m_pClientList[iClientH]->m_dwAttackLAT != 0) {
			if ((dwTime - m_pClientList[iClientH]->m_dwAttackLAT) < (3500)) {		
				DeleteClient(iClientH, TRUE, TRUE, TRUE);
				return 0;
			}
		}
		m_pClientList[iClientH]->m_dwAttackLAT = dwTime;
		m_pClientList[iClientH]->m_iAttackMsgRecvCount = 0;
	}
	if ((wTargetObjectID != NULL) && (wType != 2)) {
		if (wTargetObjectID < DEF_MAXCLIENTS) {
			if (m_pClientList[wTargetObjectID] != NULL) {
				tdX = m_pClientList[wTargetObjectID]->m_sX;
				tdY = m_pClientList[wTargetObjectID]->m_sY;
			}
		}
		else if ((wTargetObjectID > 10000) && (wTargetObjectID < (10000 + DEF_MAXNPCS))) {
			if (m_pNpcList[wTargetObjectID - 10000] != NULL) {
				tdX = m_pNpcList[wTargetObjectID - 10000]->m_sX;
				tdY = m_pNpcList[wTargetObjectID - 10000]->m_sY;
			}
		}
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwner, &cOwnerType, dX, dY);
		if (sOwner == (wTargetObjectID - 10000)) {
			tdX = m_pNpcList[sOwner]->m_sX;
			dX = tdX;
			tdY = m_pNpcList[sOwner]->m_sY;
			dY = tdY;
			bNearAttack = FALSE;
			var_AC = TRUE;
		}
		if (var_AC != TRUE) {
			if ((tdX == dX) && (tdY == dY)) {
				bNearAttack = FALSE;	
			}
			else if ((abs(tdX - dX) <= 1) && (abs(tdY - dY) <= 1)) {
				dX = tdX;
				dY = tdY;
				bNearAttack = TRUE;
			}
		}
	}
	if ((dX < 0) || (dX >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeX) || (dY < 0) || (dY >= m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY)) return 0;
	if ((sX != m_pClientList[iClientH]->m_sX) || (sY != m_pClientList[iClientH]->m_sY)) return 2;
	

	sAbsX = abs(sX - dX);
	sAbsY = abs(sY - dY);
	if ((wType != 2) && (wType < 20)) {
		if (var_AC == FALSE) {
			sItemIndex = m_pClientList[iClientH]->m_sItemEquipmentStatus[ DEF_EQUIPPOS_TWOHAND ];
			if (sItemIndex != -1) {
				if (m_pClientList[iClientH]->m_pItemList[sItemIndex] == NULL) return 0;
				if (m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_sIDnum == 845) {
					if ((sAbsX > 4) || (sAbsY > 4)) wType = 0;
				}
				else{
					if ((sAbsX > 1) || (sAbsY > 1)) wType = 0;
				}
			}
			else{
				if ((sAbsX > 1) || (sAbsY > 1)) wType = 0;
			}
		}
		else{
			cDir = m_Misc.cGetNextMoveDir(sX, sY, dX, dY);
			if ((m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bCheckFlySpaceAvailable(sX, sY, cDir, sOwner)) != FALSE)
				wType = 0;
		}
	}
	ClearSkillUsingStatus(iClientH);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(0, iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);
	m_pClientList[iClientH]->m_cDir = cDir;
	iExp = 0;
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwner, &cOwnerType, dX, dY);
	if (sOwner != NULL) {
		if ((wType != 0) && ((dwTime - m_pClientList[iClientH]->m_dwRecentAttackTime) > 100)) { 
			if ((m_pClientList[iClientH]->m_pIsProcessingAllowed == FALSE) && (m_pClientList[iClientH]->m_bIsInsideWarehouse == FALSE) 
				&& (m_pClientList[iClientH]->m_bIsInsideWizardTower == FALSE) && (m_pClientList[iClientH]->m_bIsInsideEnemyBuilding == FALSE)) {
				// Magic Weapons - Add Special Effect for Weapon
				short sType, sManaCost;
				DWORD dwType1, dwType2, dwValue1, dwValue2;

				if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1) {
					sItemIndex = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
				}
				else if (m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1) {
					sItemIndex = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				}
				else sItemIndex = -1;

				if (sItemIndex != -1) {
					if ((m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) != NULL) {
						dwType1 = (m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) >> 20;
						dwValue1 = (m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x000F0000) >> 16;
						dwType2 = (m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x0000F000) >> 12;
						dwValue2 = (m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00000F00) >> 8;
					}
					if (dwType1 == 15) {
						sManaCost = dwValue2 * 2;
						if (m_pClientList[iClientH]->m_iMP >= sManaCost) {
							switch (dwValue1) {
								// Fire-Strike
							case 1:
								sType = 30;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Lightning
							case 2:
								sType = 43;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Chill-Wind
							case 3:
								sType = 45;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Ice-Strike
							case 4:
								sType = 57;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Energy-Strike
							case 5:
								sType = 60;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Mass-Fire-Strike
							case 6:
								sType = 61;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Mass-Chill-Wind
							case 7:
								sType = 63;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Earthworm-Strike
							case 8:
								sType = 64;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Bloody-Shock-Wave
							case 9:
								sType = 70;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Mass-Ice-Strike
							case 10:
								sType = 72;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Lightning-Strike
							case 11:
								sType = 74;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Ice-Whirlwind
							case 12:
								sType = 75;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Meteor-Strike
							case 13:
								sType = 81;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Mass-Magic-Missile
							case 14:
								sType = 82;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Blizzard
							case 15:
								sType = 91;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
								// Earth-Shock-Wave
							case 16:
								sType = 96;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, dX, dY, (sType + 100), m_pClientList[iClientH]->m_sType);
								break;
							}
							// Critical Attack - Mass-Magic-Missile Aura
							if (wType >= 20)
							{
								sType = 84;
								SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[iClientH]->m_cMapIndex, sX, sY, sX, sY, (sType + 100), m_pClientList[iClientH]->m_sType);
							}
						}
					}
				}
				// End of Magic Weapons
				sItemIndex = m_pClientList[iClientH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				if (sItemIndex != -1 && m_pClientList[iClientH]->m_pItemList[sItemIndex] != NULL) {
					// Directional Bow. Fixed by juan249
					if(m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_sIDnum == 874){ // Directional bow 
						iErr = 0; 
						for(i = 1; i < 6; i++){ 
							m_Misc.GetPoint2(sX, sY, dX, dY, &tX, &tY, &iErr, i); 
							m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwner, &cOwnerType, tX, tY); 
							iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, tX, tY, wType, bNearAttack, bIsDash, TRUE); // 1 
							if (((abs(tdX - dX) >= 1) && (abs(tdY - dY) >= 1)) || ((abs(tdX - dX) <= 1) && (abs(tdY - dY) <= 1))) { 
								m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwner, &cOwnerType, dX, dY); 
								iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, dX, dY, wType, bNearAttack, bIsDash, FALSE); // 0 
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								}
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								} 
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								} 
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								} 
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								} 
								while (((tdX - dX) >= 1) && ((tdY - dY) >= 1)) { 
									dX += 4; dY += 4; tY += 4; tX += 4; 
								} 
							} 
						} 
					}
					else if(m_pClientList[iClientH]->m_pItemList[sItemIndex]->m_sIDnum == 873){ // Firebow
						if ((m_pClientList[iClientH]->m_sAppr2 & 0xF000) != 0) {
							
							iAddDynamicObjectList(iClientH, DEF_OWNERTYPE_PLAYER_INDIRECT, DEF_DYNAMICOBJECT_FIRE3, m_pClientList[iClientH]->m_cMapIndex, dX, dY, (iDice(1,7)+3)*1000, 8);
							
							iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, dX, dY, wType, bNearAttack, bIsDash, FALSE); // 0
						}
					}
					else{
						iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, dX, dY, wType, bNearAttack, bIsDash, FALSE); // 0
					}
				}
				else{
					iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, dX, dY, wType, bNearAttack, bIsDash, FALSE); // 0
				}
			}
			else{
				iExp += iCalculateAttackEffect(sOwner, cOwnerType, iClientH, DEF_OWNERTYPE_PLAYER, dX, dY, wType, bNearAttack, bIsDash, FALSE); // 0
			}
			if (m_pClientList[iClientH] == NULL) return 0;
			m_pClientList[iClientH]->m_dwRecentAttackTime = dwTime;
		}
	}
	else _CheckMiningAction(iClientH, dX, dY);

	if (iExp != 0) {
		GetExp(iClientH, iExp, TRUE);
	}

	if (bResponse == TRUE) {
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_RESPONSE_MOTION;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_OBJECTMOTION_ATTACK_CONFIRM;
	
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
		switch (iRet) {
		case DEF_XSOCKEVENT_QUENEFULL:
		case DEF_XSOCKEVENT_SOCKETERROR:
		case DEF_XSOCKEVENT_CRITICALERROR:
		case DEF_XSOCKEVENT_SOCKETCLOSED:
			DeleteClient(iClientH, TRUE, TRUE, TRUE);
			return 0;
		}
	}

	return 1;
}

void CGame::MsgProcess()
{
 char   * pData, cFrom, cKey;
 DWORD    dwMsgSize, * dwpMsgID;
 WORD   * wpMsgType, * wp;
 int      i, iClientH;
 char   m_msgBuff[100];

 char *cp, cData[120];
DWORD dwTime = timeGetTime();
DWORD * dwp, dwTimeRcv;
	char cBuffer[256];
	int iRet;

	ZeroMemory(cBuffer, 256);
	
	if ((m_bF5pressed == TRUE) && (m_bF1pressed == TRUE)) {
		PutLogList("(XXX) RELOADING CONFIGS MANUALY...");
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
					bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA, i);
				}
				bInit();
		}

	if ((m_bF1pressed == TRUE) && (m_bF4pressed == TRUE) && (m_bOnExitProcess == FALSE)) {
		// 쨍챨쨉챌 횇짭쨋처��횑쩐챨횈짰��횉 쨉짜��횑횇횒쨍짝 ��첬��책횉횗 횊횆 횉횁쨌횓짹횞쨌짜��쨩 횁쩐쨌찼횉횠쩐횩 횉횗쨈횢. 
		m_cShutDownCode      = 2;
		m_bOnExitProcess     = TRUE;
		m_dwExitProcessTime  = timeGetTime();
		// 째횚��횙 쩌짯쨔철 쩌횏쨈횢쩔챤��횑 쩍횄��횤쨉횉쨍챕 쨈천��횑쨩처��횉 횇짭쨋처��횑쩐챨횈짰 횁짖쩌횙��횑 째횇쨘횓쨉횊쨈횢. 
		PutLogList("(!) GAME SERVER SHUTDOWN PROCESS BEGIN(by Local command)!!!");
		// 쨌횓짹횞 쩌짯쨔철쩔징째횚 횉철��챌 쩌짯쨔철째징 쩌횏쨈횢쩔챤 횁횩��횙��쨩 쩐횏쨍째쨈횢. 
		bSendMsgToLS(MSGID_GAMESERVERSHUTDOWNED, NULL);
		// OccupyFlag 쨉짜��횑횇횒 ��첬��책 

		
		return;
	}
	
	ZeroMemory(m_pMsgBuffer, DEF_MSGBUFFERSIZE+1);
	pData = (char *)m_pMsgBuffer;

	m_iCurMsgs = 0;
	while (bGetMsgQuene(&cFrom, pData, &dwMsgSize, &iClientH, &cKey) == TRUE) {
		
		m_iCurMsgs++;
		if (m_iCurMsgs > m_iMaxMsgs) m_iMaxMsgs = m_iCurMsgs;

		switch (cFrom) {

		case DEF_MSGFROM_GATESERVER:
			dwpMsgID   = (DWORD *)(pData + DEF_INDEX4_MSGID);
			wpMsgType  = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
			switch (*dwpMsgID) {
			case MSGID_PARTYOPERATION:
				PartyOperationResultHandler(pData);
				break;

			case MSGID_SERVERSTOCKMSG:
				ServerStockMsgHandler(pData);
				break;
									
			case MSGID_SENDSERVERSHUTDOWNMSG:
				wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
				switch (*wp) {
				case 1:
					PutLogList("(!) Send server shutdown announcement - 1.");
					for (i = 1; i < DEF_MAXCLIENTS; i++)
					if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_SERVERSHUTDOWN, 1, NULL, NULL, NULL);
					}
					break;
				case 2:
					PutLogList("(!) Send server shutdown announcement - 2.");
					for (i = 1; i < DEF_MAXCLIENTS; i++)
					if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_SERVERSHUTDOWN, 2, NULL, NULL, NULL);
					}
					break;
				}
				bSendMsgToLS(MSGID_SENDSERVERSHUTDOWNMSG, NULL, NULL); 
				break;
			
			case MSGID_GAMESERVERSHUTDOWNED:
				m_cShutDownCode      = 1;
				m_bOnExitProcess     = TRUE;
				m_dwExitProcessTime  = timeGetTime();
				PutLogList("(!) GAME SERVER SHUTDOWN PROCESS BEGIN(by Global command)!!!");
				bSendMsgToLS(MSGID_GAMESERVERSHUTDOWNED, NULL);
				
				break;
			
			case MSGID_TOTALGAMESERVERCLIENTS:
				wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE + 2);
				m_iTotalGameServerClients = (int)*wp;
				if (m_iTotalGameServerClients > m_iTotalGameServerMaxClients) 
					m_iTotalGameServerMaxClients = m_iTotalGameServerClients;
				break;
			
			case MSGID_RESPONSE_REGISTERGAMESERVER:
				switch (*wpMsgType) {
				case DEF_MSGTYPE_CONFIRM:
					PutLogList("(!) Game Server registration to Gate Server - Success!");
					m_bIsGateSockAvailable = TRUE;
					//50Cent - HG start process fix
                    bSendMsgToLS(MSGID_REQUEST_REGISTERGAMESERVER, NULL);
					break;

				case DEF_MSGTYPE_REJECT:
					PutLogList("(!) Game Server registration to Gate Server - Fail!");
					PutLogList(" ");
					PutLogList("(!!!) STOPPED!");
					break;
				}
				break;
			}
			break;

		case DEF_MSGFROM_LOGSERVER:
			dwpMsgID   = (DWORD *)(pData + DEF_INDEX4_MSGID);
			wpMsgType  = (WORD *)(pData + DEF_INDEX2_MSGTYPE);

			switch (*dwpMsgID) {
			case MSGID_REQUEST_CHECKACCOUNTPASSWORD:
				// 째챔횁짚��횉 횈횖쩍쨘쩔철쨉책쨍짝 쨘챰짹쨀 
				RequestCheckAccountPasswordHandler(pData, dwMsgSize);
				break;
			
			case MSGID_REQUEST_FORCEDISCONECTACCOUNT:
				// 째짯횁짝 째챔횁짚 횁짖쩌횙 횁쩐쨌찼. 쨉짜��횑횇횒쨍짝 ��첬��책횉횕째챠 횁짖쩌횙��쨩 횁쩐쨌찼쩍횄횇짼쨈횢. 
				wpMsgType  = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
				ForceDisconnectAccount((char *)(pData + DEF_INDEX2_MSGTYPE + 2), *wpMsgType);
				break;
			
			case MSGID_RESPONSE_SAVEPLAYERDATA_REPLY:
				// 횆쨀쨍짱횇횒��횉 쨉짜��횑횇횒째징 ��첬��책쨉횉쩐첬��쩍��쨩 쩐횏쨍짰쨈횂 쨍횧쩍횄횁철 
				ResponseSavePlayerDataReplyHandler(pData, dwMsgSize);
				break;
			
			case MSGID_GUILDNOTIFY:
				// 쨈횢쨍짜 째횚��횙쩌짯쨔철쩔징쩌짯 쨔횩쨩첵횉횗 짹챈쨉책 ��횑쨘짜횈짰쩔징 쨈챘횉횗 횇챘쨘쨍(짹챈쨉책쩔첩 째징��횚, 짹챈쨉책쩔첩 횇쨩횇챨, 짹챈쨉책 횉횠쨩챗 쨉챤)
				GuildNotifyHandler(pData, dwMsgSize);
				break;
			
			case MSGID_RESPONSE_DISBANDGUILD:
				// 짹챈쨉책 횉횠쨩챗쩔채짹쨍쩔징 쨈챘횉횗 ����쨈채 
				ResponseDisbandGuildHandler(pData, dwMsgSize);
				break;

			case MSGID_RESPONSE_CREATENEWGUILD:
				// 횆쨀쨍짱횇횒��횉 짹챈쨉책쨩첵쩌쨘 쩔채짹쨍쩔징 쨈챘횉횗 ����쨈채. 
				ResponseCreateNewGuildHandler(pData, dwMsgSize);
				break;
			
			case MSGID_RESPONSE_REGISTERGAMESERVER:
				switch (*wpMsgType) {
				case DEF_MSGTYPE_CONFIRM:
					PutLogList("(!) Game Server registration to Log Server - Success!");
					m_bIsLogSockAvailable = TRUE;
					break;

				case DEF_MSGTYPE_REJECT:
					PutLogList("(!) Game Server registration to Log Server - Fail!");
					break;
				}
		
				if (m_bIsBuildItemAvailable == FALSE) {
					// 쨍쨍쩐횪 쨘척쨉책쩐횈��횑횇횤 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! Build-Item configuration error.");
				}
								
				if (m_bIsItemAvailable == FALSE) {
					// 쨍쨍쩐횪 쩐횈��횑횇횤 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! Item configuration error.");
				}
				
				if (m_bIsNpcAvailable == FALSE) {
					// 쨍쨍쩐횪 쩐횈��횑횇횤 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! Npc configuration error.");
				}

				if (m_bIsMagicAvailable == FALSE) {
					// 쨍쨍쩐횪 MAGIC 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! MAGIC configuration error.");
				}

				if (m_bIsSkillAvailable == FALSE) {
					// 쨍쨍쩐횪 SKILL 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! SKILL configuration error.");
				}

				if (m_bIsQuestAvailable == FALSE) {
					// 쨍쨍쩐횪 SKILL 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! QUEST configuration error.");
				}

				if (m_bIsPotionAvailable == FALSE) {
					// 쨍쨍쩐횪 Potion 횁짚��횉 횊짯��횕쩔징쩌짯 쩔징쨌짱째징 ��횜쩐첬쨈횢쨍챕 째횚��횙쩌짯쨔철 쨉챤쨌횕쩔징 쨩처째체쩐첩��횑 쨉쩔��횤 쨘횘째징쨈횋.
					PutLogList(" ");
					PutLogList("(!!!) STOPPED! POTION configuration error.");
				}
				break;

			case MSGID_RESPONSE_PLAYERDATA:
				// 횉횄쨌쨔��횑쩐챤 쨉짜��횑횇횒째징 쨉쨉횂첩횉횩쨈횢. 
				ResponsePlayerDataHandler(pData, dwMsgSize);
				break;

			case MSGID_BUILDITEMCONFIGURATIONCONTENTS:
				// Build Item contents
				PutLogList("(!) BUILD-ITEM configuration contents received. Now decoding...");
				m_bIsBuildItemAvailable = _bDecodeBuildItemConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;
			
			case MSGID_ITEMCONFIGURATIONCONTENTS:
				// 쨌횓짹횞쩌짯쨔철쨌횓쨘횓횇횒 쩐횈��횑횇횤 횆횁횉횉짹횚쨌쨔��횑쩌횉 쨉짜��횑횇횒째징 쨉쨉횂첩횉횩쨈횢.
				PutLogList("(!) ITEM configuration contents received. Now decoding...");
				m_bIsItemAvailable = _bDecodeItemConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_NPCCONFIGURATIONCONTENTS:
				// NPC 횆횁횉횉짹횚쨌쨔��횑쩌횉 쨉짜��횑횇횒째징 쨉쨉횂첩횉횩쨈횢. 
				PutLogList("(!) NPC configuration contents received. Now decoding...");
				m_bIsNpcAvailable = _bDecodeNpcConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;
			
			case MSGID_MAGICCONFIGURATIONCONTENTS:
				PutLogList("(!) MAGIC configuration contents received. Now decoding...");
				m_bIsMagicAvailable = _bDecodeMagicConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_SKILLCONFIGURATIONCONTENTS:
				PutLogList("(!) SKILL configuration contents received. Now decoding...");
				m_bIsSkillAvailable = _bDecodeSkillConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_QUESTCONFIGURATIONCONTENTS:
				PutLogList("(!) QUEST configuration contents received. Now decoding...");
				m_bIsQuestAvailable = _bDecodeQuestConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_POTIONCONFIGURATIONCONTENTS:
				PutLogList("(!) POTION configuration contents received. Now decoding...");
				m_bIsPotionAvailable = _bDecodePotionConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_DUPITEMIDFILECONTENTS:
				PutLogList("(!) DupItemID file contents received. Now decoding...");
				_bDecodeDupItemIDFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			case MSGID_NOTICEMENTFILECONTENTS:
				PutLogList("(!) Noticement file contents received. Now decoding...");
				_bDecodeNoticementFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			// v2.17 2002-8-7 // 2002-09-06 #1
			case MSGID_NPCITEMCONFIGCONTENTS:
				PutLogList("(!) NpcItemConfig file contents received. Now decoding...");
				_bDecodeNpcItemConfigFileContents((char *)(pData + DEF_INDEX2_MSGTYPE + 2), dwMsgSize);
				break;

			}
			break;
		
		case DEF_MSGFROM_CLIENT:

			dwpMsgID = (DWORD *)(pData + DEF_INDEX4_MSGID);
			switch (*dwpMsgID) { // 84148741

			case MSGID_REQUEST_ONLINE:
				
				if (m_pClientList[iClientH])
					RequestOnlines(iClientH); //no necesitamos la data
				break;

			case MSGID_REQUEST_PING:
				
				//Change ping response

				if (m_pClientList[iClientH] == NULL) return;

				cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
				dwp = (DWORD *)cp;
				dwTimeRcv = *dwp;

				dwp = (DWORD *)(cBuffer + DEF_INDEX4_MSGID);
				*dwp = MSGID_RESPONSE_PING;
				wp  = (WORD *)(cBuffer + DEF_INDEX2_MSGTYPE);
				*wp = NULL;

				cp = (char *)(cBuffer + DEF_INDEX2_MSGTYPE + 2);
				dwp = (DWORD *)cp;
				*dwp = dwTimeRcv;
				cp += 4;

				iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cBuffer, 10);
				break;

			case DEF_REQUEST_ANGEL: // Angels by Snoopy...
				GetAngelHandler(iClientH, pData, dwMsgSize);
				break;
						
			case MSGID_REQUEST_INITPLAYER:
				RequestInitPlayerHandler(iClientH, pData, cKey);
				break;

			case MSGID_REQUEST_INITDATA:
#ifdef ANTI_HAX
				// Anti Bump 
                if (m_pClientList[iClientH]->m_bIsClientConnected == TRUE) {
                    if (m_pClientList[iClientH] == NULL) break;
                    wsprintf(G_cTxt, "(!!!) Client (%s) connection closed!. Sniffer suspect!.", m_pClientList[iClientH]->m_cCharName);
                    PutLogList(G_cTxt);
                    ZeroMemory(cData, sizeof(cData));
                    cp  = (char *)cData;
                    *cp = GSM_DISCONNECT;
                    cp++;
                    memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
                    cp += 10;
                    bStockMsgToGateServer(cData, 11);
                    m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(2, iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
                    bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, NULL);
                    bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATALOGOUT, iClientH, FALSE);
                    if ((dwTime - m_dwGameTime2) > 3000) { // 3 segs
                        m_pClientList[iClientH]->m_bIsClientConnected = FALSE;
                        m_iTotalClients--;
                        delete m_pClientList[iClientH];
                        m_pClientList[iClientH] = NULL;
                    }
                    break;
				}
                else {
                    m_pClientList[iClientH]->m_bIsClientConnected = TRUE;
                    RequestInitDataHandler(iClientH, pData, cKey, FALSE);
                }
#else
				RequestInitDataHandler(iClientH, pData, cKey, FALSE);
#endif
				break;

			case MSGID_COMMAND_CHECKCONNECTION:
				CheckConnectionHandler(iClientH, pData);
				break;

			case DEF_REQUEST_RESURRECTPLAYER_YES:
				RequestResurrectPlayer(iClientH, TRUE);
				break;

			case DEF_REQUEST_RESURRECTPLAYER_NO:
				RequestResurrectPlayer(iClientH, FALSE);
				break;

			case MSGID_REQUEST_SELLITEMLIST:
				RequestSellItemListHandler(iClientH, pData);
				break;
			
			case MSGID_REQUEST_RESTART:
				RequestRestartHandler(iClientH);
				break;

			case MSGID_REQUEST_PANNING:
				iRequestPanningMapDataRequest(iClientH, pData);
				break;

			case MSGID_REQUEST_NOTICEMENT:
				RequestNoticementHandler(iClientH, pData);
				break;
			
			case MSGID_BWM_COMMAND_SHUTUP:
				_BWM_Command_Shutup(pData);
				break;
			
			case MSGID_BWM_INIT:
				_BWM_Init(iClientH, pData);
				break;
			
			case MSGID_REQUEST_SETITEMPOS:
				_SetItemPos(iClientH, pData);
				break;
			
			case MSGID_ADMINUSER:
				break;
			
			case MSGID_REQUEST_FULLOBJECTDATA:
				RequestFullObjectData(iClientH, pData);
				break;
			
			case MSGID_REQUEST_RETRIEVEITEM:
				RequestRetrieveItemHandler(iClientH, pData);
				break;

			case MSGID_REQUEST_CIVILRIGHT:
				RequestCivilRightHandler(iClientH, pData);
				break;

			case MSGID_REQUEST_TELEPORT:
				RequestTeleportHandler(iClientH, pData);
				break;

			case MSGID_COMMAND_COMMON:
				ClientCommonHandler(iClientH, pData);
				break;

			case MSGID_COMMAND_MOTION:
				ClientMotionHandler(iClientH, pData);
				break;

			case MSGID_COMMAND_CHATMSG:
				ChatMsgHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_CREATENEWGUILD:
				RequestCreateNewGuildHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_DISBANDGUILD:
				RequestDisbandGuildHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_FIGHTZONE_RESERVE:
				FightzoneReserveHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_LEVELUPSETTINGS:
				LevelUpSettingsHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_STATECHANGEPOINT:
				StateChangeHandler(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_HELDENIAN_TP_LIST:	// 0x0EA03206
				
				RequestHeldenianTeleportList(iClientH, pData, dwMsgSize);
				break;
			case MSGID_REQUEST_HELDENIAN_TP:		// 0x0EA03208
				
				RequestHeldenianTeleportNow(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_HELDENIAN_SCROLL:
				
				RequestHeldenianScroll(iClientH, pData, dwMsgSize);
				break;

			case MSGID_REQUEST_TELEPORT_LIST:
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "aresden",7) == 0 ) {
					  RequestTeleportHandler(iClientH, "2   ", "dglv2", 263, 258);
				}
				else if (memcmp(m_pClientList[iClientH]->m_cLocation, "elvine",6) == 0 ) {
				  RequestTeleportHandler(iClientH, "2   ", "dglv2", 209, 258);
				}
				break;
				
			// Centuu: "Do you really wanna change city?"
			case DEF_REQUEST_CHANGECITY_YES:
				PlayerOrder_ChangeCity(iClientH, TRUE);
				break;
			

			default:
				if (m_pClientList[iClientH] != NULL) {
					wsprintf(m_msgBuff, "Unknown message received from %d! (0x%.8X) Delete Client", iClientH ,*dwpMsgID);
					PutLogList(m_msgBuff);
					DeleteClient(iClientH, TRUE, TRUE); // v1.4
				}
				else
				{
					wsprintf(m_msgBuff, "Unknown message received! (0x%.8X)", *dwpMsgID);
					PutLogList(m_msgBuff);
				}
				break;
			}	
			break;

		
		}
	}

}


BOOL CGame::bPutMsgQuene(char cFrom, char * pData, DWORD dwMsgSize, int iIndex, char cKey)
{
	
	// 쨍횧쩍횄횁철 횇짜째징 쨈횢 횄징쨈횢쨍챕 쩔징쨌짱 
	if (m_pMsgQuene[m_iQueneTail] != NULL) return FALSE;

	// 쨍횧쨍챨쨍짰 횉횘쨈챌��횑 ��횩쨍첩쨉횉쩐챤쨉쨉 쩔징쨌짱 
	m_pMsgQuene[m_iQueneTail] = new class CMsg;
	if (m_pMsgQuene[m_iQueneTail] == NULL) return FALSE;

	if (m_pMsgQuene[m_iQueneTail]->bPut(cFrom, pData, dwMsgSize, iIndex, cKey) == FALSE) return FALSE;

	m_iQueneTail++;
	if (m_iQueneTail >= DEF_MSGQUENESIZE) m_iQueneTail = 0;

	

	return TRUE;
}


BOOL CGame::bGetMsgQuene(char * pFrom, char * pData, DWORD * pMsgSize, int * pIndex, char * pKey)
{
	
	// 째징횁짰째짜 쨍횧쩍횄횁철째징 쩐첩��쨍쨍챕 쩔징쨌짱  
	if (m_pMsgQuene[m_iQueneHead] == NULL) return FALSE;

	m_pMsgQuene[m_iQueneHead]->Get(pFrom, pData, pMsgSize, pIndex, pKey);

	delete m_pMsgQuene[m_iQueneHead];
	m_pMsgQuene[m_iQueneHead] = NULL;

	m_iQueneHead++;
	if (m_iQueneHead >= DEF_MSGQUENESIZE) m_iQueneHead = 0;


	return TRUE;
}


void CGame::ClientCommonHandler(int iClientH, char * pData)
{
 WORD * wp, wCommand;
 short * sp, sX, sY; 
 int   * ip, iV1, iV2, iV3, iV4;
 char  * cp, cDir, * pString;
	
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;

	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wCommand = *wp;

	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp = (short *)cp;
	sX = *sp;
	cp += 2;

	sp = (short *)cp;
	sY = *sp;
	cp += 2;

	cDir = *cp;
	cp++;
 
	ip = (int *)cp;
	iV1 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV2 = *ip;
	cp += 4;

	ip = (int *)cp;
	iV3 = *ip;
	cp += 4;

	pString = cp;
	cp += 30;
	
	ip = (int *)cp;
	iV4 = *ip;
	cp += 4;
	
	switch (wCommand) {

	//ZeroEoyPnk - NewMessage
	case DEF_RESQUEST_PARTYHP:
		RefreshPartyStatus(iClientH);
		RefreshPartyCoords(iClientH);
		break;

	// Crafting
	case DEF_COMMONTYPE_CRAFTITEM:
		ReqCreateCraftingHandler(iClientH, pData);
		break;

	case DEF_COMMONTYPE_REQDKSET: // MORLA 2.5 - DK Set
		GetDkSet(iClientH);
		break;

	// New 15/05/2004
	case DEF_COMMONTYPE_REQ_CREATESLATE:
		ReqCreateSlateHandler(iClientH, pData);
		break;

// 2.06 - by KLKS
	case DEF_COMMONTYPE_REQ_CHANGEPLAYMODE:
		RequestChangePlayMode(iClientH);
		break;
//

	case DEF_COMMONTYPE_SETGUILDTELEPORTLOC:
		RequestSetGuildTeleportLocHandler(iClientH, iV1, iV2, m_pClientList[iClientH]->m_iGuildGUID, "middleland");
		break;

	case DEF_COMMONTYPE_SETGUILDCONSTRUCTLOC:
		RequestSetGuildConstructLocHandler(iClientH, iV1, iV2, m_pClientList[iClientH]->m_iGuildGUID, pString);
		break;
	
	case DEF_COMMONTYPE_GUILDTELEPORT:
		RequestGuildTeleportHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_SUMMONWARUNIT:
		RequestSummonWarUnitHandler(iClientH, sX, sY, iV1, iV2, iV3);
		break;
	
	case DEF_COMMONTYPE_REQUEST_HELP:
		RequestHelpHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_REQUEST_MAPSTATUS:
		MapStatusHandler(iClientH, iV1, pString);
		break;

	case DEF_COMMONTYPE_REQUEST_SELECTCRUSADEDUTY:
		SelectCrusadeDutyHandler(iClientH, iV1);
		break;
	
	case DEF_COMMONTYPE_REQUEST_CANCELQUEST:
		CancelQuestHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_REQUEST_ACTIVATESPECABLTY:
		ActivateSpecialAbilityHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_REQUEST_JOINPARTY:
		JoinPartyHandler(iClientH, iV1, pString);
		break;
	
	case DEF_COMMONTYPE_GETMAGICABILITY:
		GetMagicAbilityHandler(iClientH);
		break;

	case DEF_COMMONTYPE_BUILDITEM:
		BuildItemHandler(iClientH, pData);
		break;
	
	case DEF_COMMONTYPE_QUESTACCEPTED:
		QuestAcceptedHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_CANCELEXCHANGEITEM:
		CancelExchangeItem(iClientH);
		break;
	
	case DEF_COMMONTYPE_CONFIRMEXCHANGEITEM:
		ConfirmExchangeItem(iClientH);
		break;
	
	case DEF_COMMONTYPE_SETEXCHANGEITEM:
		SetExchangeItem(iClientH, iV1, iV2);
		break;
	
	case DEF_COMMONTYPE_REQ_GETHEROMANTLE:
		GetHeroMantleHandler(iClientH, iV1, pString);
		break;
	
	case DEF_COMMONTYPE_REQ_GETOCCUPYFLAG:
		GetOccupyFlagHandler(iClientH);
		break;

	case DEF_COMMONTYPE_REQ_SETDOWNSKILLINDEX:
		SetDownSkillIndexHandler(iClientH, iV1);
		break;

	case DEF_COMMONTYPE_TALKTONPC:
		NpcTalkHandler(iClientH, iV1);
		break;
	
	case DEF_COMMONTYPE_REQ_CREATEPOTION:
		ReqCreatePotionHandler(iClientH, pData);
		break;
	
	case DEF_COMMONTYPE_REQ_GETFISHTHISTIME:
		ReqGetFishThisTimeHandler(iClientH);
		break;
	
	case DEF_COMMONTYPE_REQ_REPAIRITEMCONFIRM:
		ReqRepairItemCofirmHandler(iClientH, iV1, pString);
		break;

	//50Cent - Repair All
    case DEF_COMMONTYPE_REQ_REPAIRALL:
        RequestRepairAllItemsHandler(iClientH);
        break;
    case DEF_COMMONTYPE_REQ_REPAIRALLDELETE:
        RequestRepairAllItemsDeleteHandler(iClientH, iV1);
        break;
    case DEF_COMMONTYPE_REQ_REPAIRALLCONFIRM:
        RequestRepairAllItemsConfirmHandler(iClientH);
        break;
	
	case DEF_COMMONTYPE_REQ_REPAIRITEM:
		ReqRepairItemHandler(iClientH, iV1, iV2, pString);
		break;
	
	case DEF_COMMONTYPE_REQ_SELLITEMCONFIRM:
		ReqSellItemConfirmHandler(iClientH, iV1, iV2, pString);
		break;
	
	case DEF_COMMONTYPE_REQ_SELLITEM:
		ReqSellItemHandler(iClientH, iV1, iV2, iV3, pString);
		break;
	
	case DEF_COMMONTYPE_REQ_USESKILL:
		UseSkillHandler(iClientH, iV1, iV2, iV3);
		break;
	
	case DEF_COMMONTYPE_REQ_USEITEM:
		UseItemHandler(iClientH, iV1, iV2, iV3, iV4);
		break;
	
	case DEF_COMMONTYPE_REQ_GETREWARDMONEY:
		GetRewardMoneyHandler(iClientH);
		break;

	case DEF_COMMONTYPE_ITEMDROP:
		DropItemHandler(iClientH, iV1, iV2, pString, TRUE);
		break;
	
	case DEF_COMMONTYPE_EQUIPITEM:
		// 쩔짤짹창쩌짯쨈횂 횈짱쩌쨘횆징 쨘짱횊짯쨍쨍��쨩 쨈횢쨌챕쨈횢.
		bEquipItemHandler(iClientH, iV1);
		// 쨔횢짼챦 쩔횥횉체쩔징 쨈챘횉횗 횁짚쨘쨍쨍짝 쩔짤짹창쩌짯 ��체쩌횤횉횗쨈횢.
		// .....
		break;

	case DEF_COMMONTYPE_REQ_PURCHASEITEM:
		// 쩐횈��횑횇횤 짹쨍��횚 쩔채짹쨍. 쨩챌쩍횉 쩐횈��횑횇횤��쨘 ��책쩌횘쩔징 쨩처째체쩐첩��횑 쩐챤쨉챨쩌짯쨋처쨉쨉 짹쨍��횚횉횘 쩌철 ��횜쨈횢.
		RequestPurchaseItemHandler(iClientH, pString, iV1);
		break;

	case DEF_COMMONTYPE_REQ_PURCHASEITEM2:
		RequestPurchaseItemHandler2(iClientH, pString, iV1);
		break;

	case DEF_COMMONTYPE_REQ_STUDYMAGIC:
		RequestStudyMagicHandler(iClientH, pString);
		break;

	case DEF_COMMONTYPE_REQ_TRAINSKILL:
		break;

	case DEF_COMMONTYPE_GIVEITEMTOCHAR:
		GiveItemHandler(iClientH, cDir, iV1, iV2, iV3, iV4, pString);
		break;

	case DEF_COMMONTYPE_EXCHANGEITEMTOCHAR:
		ExchangeItemHandler(iClientH, cDir, iV1, iV2, iV3, iV4, pString);
		break;

	case DEF_COMMONTYPE_JOINGUILDAPPROVE:
		JoinGuildApproveHandler(iClientH, pString);
		break;
	
	case DEF_COMMONTYPE_JOINGUILDREJECT:
		JoinGuildRejectHandler(iClientH, pString);
		break;

	case DEF_COMMONTYPE_DISMISSGUILDAPPROVE:
		DismissGuildApproveHandler(iClientH, pString);
		break;

	case DEF_COMMONTYPE_DISMISSGUILDREJECT:
		DismissGuildRejectHandler(iClientH, pString);
		break;

	case DEF_COMMONTYPE_RELEASEITEM:
		// 횇짭쨋처��횑쩐챨횈짰째징 ��책횂첩쨉횊 쩐횈��횑횇횤��쨩 횉횠횁짝횉횩쨈횢.
		ReleaseItemHandler(iClientH, iV1, TRUE);
		break;

	case DEF_COMMONTYPE_TOGGLECOMBATMODE:
		ToggleCombatModeHandler(iClientH);
		break;

	case DEF_COMMONTYPE_MAGIC:
		PlayerMagicHandler(iClientH, iV1, iV2, (iV3 - 100));
		break;

	case DEF_COMMONTYPE_TOGGLESAFEATTACKMODE:
		ToggleSafeAttackModeHandler(iClientH);
		break;

	// v1.4311-3 횄횩째징 ��횚��책짹횉 쨔횧짹창  
	case DEF_COMMONTYPE_REQ_GETOCCUPYFIGHTZONETICKET:
		GetFightzoneTicketHandler(iClientH);
		break;

	// Upgrade Item
	case DEF_COMMONTYPE_UPGRADEITEM:
		RequestItemUpgradeHandler(iClientH,iV1);
		break;

	case DEF_COMMONTYPE_REQGUILDNAME:
		RequestGuildNameHandler(iClientH, iV1, iV2);
		break;

	case DEF_COMMONTYPE_REQRANGO:
		RequestRango(iClientH, iV1);
		break;


	case DEF_COMMONTYPE_REQTPDG: // MORLA 2.3 - TP Deathmach Game
		if (m_pClientList[iClientH]->m_iLevel >= 100) 
		{
			if (bDeathmatch) 
			{
				RequestTeleportHandler(iClientH, "2   ", "fightzone1", 51, 56);
			}
			else SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "Deathmatch event is offline.");
		}
		else SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You need to be level 100 or higher.");
		break;

	//50Cent - HP Bar
	case DEF_COMMONTYPE_REQ_GETNPCHP:
		if ((iV1 - 10000 <= 0) || (iV1 - 10000 >= DEF_MAXNPCS)) return;
        if (m_pNpcList[iV1 - 10000] == NULL) return;
		if(m_pNpcList[iV1 - 10000]->m_iHP > m_pNpcList[iV1 - 10000]->m_iMaxHP) m_pNpcList[iV1 - 10000]->m_iMaxHP = m_pNpcList[iV1 - 10000]->m_iHP;
		SendNotifyMsg(NULL, iClientH, DEF_SEND_NPCHP, m_pNpcList[iV1 - 10000]->m_iHP, m_pNpcList[iV1 - 10000]->m_iMaxHP, NULL, NULL);
		break;

	case DEF_COMMONTYPE_REQUEST_ACCEPTJOINPARTY:
		RequestAcceptJoinPartyHandler(iClientH, iV1);
		break;

	default:
		wsprintf(G_cTxt,"Unknown message received! (0x%.8X)",wCommand);
		PutLogList(G_cTxt);
		break;
	}
}

void CGame::RefreshDeathmatch(int iClientH) // MORLA 2.3 - Actualiza los pjs del Deathmach
{
	if (m_pClientList[iClientH] != NULL && iClientH != 0) 
	{
		if (iClientH == iDGtop1) { iDGtop1 = iDGtop2; }
		if (iClientH == iDGtop2) { iDGtop2 = iDGtop3; }
		if (iClientH == iDGtop3) { iDGtop3 = iDGtop4; }
		if (iClientH == iDGtop4) { iDGtop4 = iDGtop5; }
		if (iClientH == iDGtop5) { iDGtop5 = iDGtop6; }
		if (iClientH == iDGtop6) { iDGtop6 = iDGtop7; }
		if (iClientH == iDGtop7) { iDGtop7 = iDGtop8; }
		if (iClientH == iDGtop8) { iDGtop8 = iDGtop9; }
		if (iClientH == iDGtop9) { iDGtop9 = iDGtop10; }
		if (iClientH == iDGtop10) { iDGtop10 = 0; }
	
		if (iDGtop1 == iDGtop2)
		{iDGtop2 = iDGtop3; iDGtop3 = iDGtop4; iDGtop4 = iDGtop5; iDGtop5 = iDGtop6; iDGtop6 = iDGtop7; iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop2 == iDGtop3)
		{iDGtop3 = iDGtop4; iDGtop4 = iDGtop5; iDGtop5 = iDGtop6; iDGtop6 = iDGtop7; iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop3 == iDGtop4)
		{iDGtop4 = iDGtop5; iDGtop5 = iDGtop6; iDGtop6 = iDGtop7; iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop4 == iDGtop5)
		{iDGtop5 = iDGtop6; iDGtop6 = iDGtop7; iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop5 == iDGtop6)
		{iDGtop6 = iDGtop7; iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop6 == iDGtop7)
		{iDGtop7 = iDGtop8; iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop7 == iDGtop8)
		{iDGtop8 = iDGtop9; iDGtop9 = iDGtop10; iDGtop10 = 0;}
		if (iDGtop8 == iDGtop9)
		{iDGtop9 = iDGtop10; iDGtop10 = 0;
		}
	}

	for (int i = 1; i < DEF_MAXCLIENTS; i++) // Check all clients
	{
		if (m_pClientList[i] != NULL) 
		{
			if (m_pClientList[iDGtop1]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 1, m_pClientList[iDGtop1]->m_iDGKills, m_pClientList[iDGtop1]->m_iDGDeaths, m_pClientList[iDGtop1]->m_cCharName);
			if (m_pClientList[iDGtop2]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 2, m_pClientList[iDGtop2]->m_iDGKills, m_pClientList[iDGtop2]->m_iDGDeaths, m_pClientList[iDGtop2]->m_cCharName);
			if (m_pClientList[iDGtop3]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 3, m_pClientList[iDGtop3]->m_iDGKills, m_pClientList[iDGtop3]->m_iDGDeaths, m_pClientList[iDGtop3]->m_cCharName);
			if (m_pClientList[iDGtop4]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 4, m_pClientList[iDGtop4]->m_iDGKills, m_pClientList[iDGtop4]->m_iDGDeaths, m_pClientList[iDGtop4]->m_cCharName);
			if (m_pClientList[iDGtop5]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 5, m_pClientList[iDGtop5]->m_iDGKills, m_pClientList[iDGtop5]->m_iDGDeaths, m_pClientList[iDGtop5]->m_cCharName);
			if (m_pClientList[iDGtop6]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 6, m_pClientList[iDGtop6]->m_iDGKills, m_pClientList[iDGtop6]->m_iDGDeaths, m_pClientList[iDGtop6]->m_cCharName);
			if (m_pClientList[iDGtop7]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 7, m_pClientList[iDGtop7]->m_iDGKills, m_pClientList[iDGtop7]->m_iDGDeaths, m_pClientList[iDGtop7]->m_cCharName);
			if (m_pClientList[iDGtop8]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 8, m_pClientList[iDGtop8]->m_iDGKills, m_pClientList[iDGtop8]->m_iDGDeaths, m_pClientList[iDGtop8]->m_cCharName);
			if (m_pClientList[iDGtop9]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 9, m_pClientList[iDGtop9]->m_iDGKills, m_pClientList[iDGtop9]->m_iDGDeaths, m_pClientList[iDGtop9]->m_cCharName);
			if (m_pClientList[iDGtop10]!=NULL)SendNotifyMsg(NULL, i, DEF_NOTIFY_DGKILL, 10, m_pClientList[iDGtop10]->m_iDGKills, m_pClientList[iDGtop10]->m_iDGDeaths, m_pClientList[iDGtop10]->m_cCharName);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//  int CGame::iClientMotion_Stop_Handler(int iClientH, short sX, short sY, char cDir)
//  description			:: checks if player is stopped
//  last updated		:: October 29, 2004; 6:46 PM; Hypnotoad
//	return value		:: int
/////////////////////////////////////////////////////////////////////////////////////
int CGame::iClientMotion_Stop_Handler(int iClientH, short sX, short sY, char cDir)
{
 char cData[100];
 DWORD * dwp;
 WORD  * wp;
 int     iRet;
 short   sOwnerH;
 char    cOwnerType;
	
	if (m_pClientList[iClientH] == NULL) return 0;
	if ((cDir <= 0) || (cDir > 8))       return 0;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return 0;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return 0;
	
	if ((sX != m_pClientList[iClientH]->m_sX) || (sY != m_pClientList[iClientH]->m_sY)) return 2;

	if (m_pClientList[iClientH]->m_bSkillUsingStatus[19] == TRUE) {
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, sX, sY);		
		if (sOwnerH != NULL) {
			DeleteClient(iClientH, TRUE, TRUE);
			return 0;
		}
	}

	ClearSkillUsingStatus(iClientH);

	

	m_pClientList[iClientH]->m_cDir = cDir;
	
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(0, iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, sX, sY);

	dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_MOTION;
	wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_OBJECTMOTION_CONFIRM;

	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, TRUE, TRUE);
		return 0;
	}

	return 1;
}

void CGame::ClientKilledHandler(int iClientH, int iAttackerH, char cAttackerType, short sDamage)
{
 char  * cp, cAttackerName[21], cData[120];
 short sAttackerWeapon;
 int   * ip, i, iExH;
 BOOL  bIsSAattacked = FALSE;
 char KilledMessage1[45], KilledMessage2[45], KilledMessage3[45], KilledMessage4[45], KilledMessage5[45], KilledMessage6[45];
 int Killedi, KMRand;
	
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
 	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;

	// 사투장인 경우 시간을 입력한다.
	// 2002-7-4 사투장의 갯수를 늘릴 수 있도록 

	m_pClientList[iClientH]->m_bIsKilled = TRUE;
	// HP는 0이다.
	m_pClientList[iClientH]->m_iHP = 0;

	if (m_pClientList[iClientH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0)
	{
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[iClientH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
		m_pClientList[iClientH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
		bRemoveFromDelayEventList(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
	}

	if ( m_pClientList[iClientH]->m_bIsPoisoned ) 
	{
		m_pClientList[iClientH]->m_bIsPoisoned = FALSE;
		SetPoisonFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_POISON, NULL, NULL, NULL);
	}

	// Snoopy: Remove all magic effects and flags
	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++)
		m_pClientList[iClientH]->m_cMagicEffectStatus[i] = 0;

	SetDefenseShieldFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetMagicProtectionFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetProtectionFromArrowFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetIllusionMovementFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetIllusionFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetInhibitionCastingFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetPoisonFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetIceFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetBerserkFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	SetSlateFlag(iClientH, DEF_NOTIFY_SLATECLEAR, FALSE);

	if (m_pClientList[iClientH]->m_cExchangeMode != 0) {
		iExH = m_pClientList[iClientH]->m_iExchangeH;
		_ClearExchangeStatus(iExH);
		_ClearExchangeStatus(iClientH);
	}
	// 현재 이 NPC를 공격대상으로 삼고있는 객체들을 해제한다.
	RemoveFromTarget(iClientH, DEF_OWNERTYPE_PLAYER, NULL, iAttackerH, cAttackerType);
	
	ZeroMemory(cAttackerName, sizeof(cAttackerName));
	switch (cAttackerType) {
	case DEF_OWNERTYPE_PLAYER_INDIRECT:
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[iAttackerH] != NULL)
			memcpy(cAttackerName, m_pClientList[iAttackerH]->m_cCharName, 10);
		break;
	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[iAttackerH] != NULL)
#ifdef DEF_LOCALNPCNAME     // v2.14 NPC 이름 중문화를 위한 선언 
			wsprintf(cAttackerName,"NPCNPCNPC@%d",m_pNpcList[iAttackerH]->m_sType);
#else 
			memcpy(cAttackerName, m_pNpcList[iAttackerH]->m_cNpcName, 20);
#endif
		break ;
	default:
		break;
	}
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_KILLED, NULL, NULL, NULL, cAttackerName);
	// 다른 클라이언트에게 죽는 동작 전송.
	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		sAttackerWeapon = ((m_pClientList[iAttackerH]->m_sAppr2 & 0x0FF0) >> 4);	
	}
	else sAttackerWeapon = 1;
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDYING, sDamage, sAttackerWeapon, NULL);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(12, iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetDeadOwner(iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cType == DEF_MAPTYPE_NOPENALTY_NOREWARD) return;
	if (   (m_bHeldenianWarInitiated == TRUE) 
		&& (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsHeldenianMap == TRUE)) 
	{	if (m_pClientList[iClientH]->m_cSide == 1) 
		{	m_iHeldenianAresdenDead++;
		}else if (m_pClientList[iClientH]->m_cSide == 2) 
		{	m_iHeldenianElvineDead++;
		}
		UpdateHeldenianStatus(-1);
	}

	//50Cent - Capture The Flag
	if (bCheckIfIsFlagCarrier(iClientH))
	{
		SetIceFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
		SetFlagCarrierFlag(iClientH, false);
	}

	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		// v1.432
		// 특수 능력이 있는 무기로 공격을 당했다.
		switch (m_pClientList[iAttackerH]->m_iSpecialAbilityType) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			bIsSAattacked = TRUE;
			break;
		}
		
		if (iAttackerH == iClientH) return; // 자폭이다.
		// 플레이어가 플레이어를 죽였다면 PK인지 전투중 승리인지를 판별하여 경험치를 올린다. 
		if (memcmp(m_pClientList[iAttackerH]->m_cMapName, "fightzone1", 10) == 0 && bDeathmatch) 
		{ 	
			char cScanMessage[50];
									
			//MORLA 2.2 - Deathmach Game completo:
			m_pClientList[iAttackerH]->m_iDGKills++;
			m_pClientList[iClientH]->m_iDGDeaths++;
			
			m_pClientList[iAttackerH]->m_iTotalDGKills++;
			m_pClientList[iClientH]->m_iTotalDGDeaths++;									

			DWORD dwTimeThisKill = timeGetTime();
			if (iLastKill == iAttackerH)
			{
				if (dwTimeLastKill > dwTimeThisKill) 
				{
					iTotalKills++;
					for (i = 1; i < DEF_MAXCLIENTS; i++) // Check all clients
					{
						if ((m_pClientList[i] != NULL)) 
						{
							if ((iTotalKills == 1) && (memcmp(m_pClientList[i]->m_cMapName, "fightzone1", 10) == 0))
								SendNotifyMsg(NULL, i, DEF_NOTIFY_DOUBLEKILL, NULL, NULL, NULL, NULL);
							else if ((iTotalKills == 2) && (memcmp(m_pClientList[i]->m_cMapName, "fightzone1", 10) == 0))
								SendNotifyMsg(NULL, i, DEF_NOTIFY_KILLSPRING, NULL, NULL, NULL, NULL);
							else if ((iTotalKills == 3) && (memcmp(m_pClientList[i]->m_cMapName, "fightzone1", 10) == 0))
								SendNotifyMsg(NULL, i, DEF_NOTIFY_MONSTERKILL, NULL, NULL, NULL, NULL);
							else if ((iTotalKills >= 4) && (memcmp(m_pClientList[i]->m_cMapName, "fightzone1", 10) == 0))
								SendNotifyMsg(NULL, i, DEF_NOTIFY_HOLYSHIT, NULL, NULL, NULL, NULL); 
						}
						dwTimeLastKill = (timeGetTime()+ 30*1000);
					}
				}
				else {
					iTotalKills = 0;
					iLastKill = iAttackerH;
					dwTimeLastKill = (timeGetTime()+ 30*1000);
				}
			}
			else {
				iTotalKills = 0;
				iLastKill = iAttackerH;
				dwTimeLastKill = (timeGetTime()+ 30*1000);
			}
			for (i = 25; i < 5000; i += 25) 
			{
				if (m_pClientList[iAttackerH]->m_iDGKills == i) 
				{
					m_pClientList[iAttackerH]->m_iDGPoints++;
					ZeroMemory(cScanMessage, sizeof(cScanMessage));
					wsprintf(cScanMessage, " 좬et a Deathmatch Point! Total: %d", m_pClientList[iAttackerH]->m_iDGPoints);
					SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, cScanMessage);
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_REPDGDEATHS, m_pClientList[iAttackerH]->m_iDGPoints, m_pClientList[iAttackerH]->m_iDeaths, m_pClientList[iAttackerH]->m_iRating, NULL);
					bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA, iAttackerH);
				}
			}
			if (m_pClientList[iDGtop1] != NULL) 
			{	
				if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop1]->m_iDGKills)
				{
					if(iDGtop1!=iAttackerH){
						iDGtop2 = iDGtop1;	
						iDGtop1 = iAttackerH;
					}
				}
				else
				{	
					if (m_pClientList[iDGtop2] != NULL)
					{ 
						if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop2]->m_iDGKills)
						{ 
							if(iDGtop2!=iAttackerH){
								iDGtop3 = iDGtop2;	
								iDGtop2 = iAttackerH;
							}
						}
						else
						{	
							if (m_pClientList[iDGtop3] != NULL)
							{
								if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop3]->m_iDGKills)
								{
									if(iDGtop3!=iAttackerH){
										iDGtop4 = iDGtop3;	
										iDGtop3 = iAttackerH;
									}
								}
								else
								{	
									if (m_pClientList[iDGtop4] != NULL)
									{
										if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop4]->m_iDGKills)
										{
											if(iDGtop4!=iAttackerH){
												iDGtop5 = iDGtop4;	
												iDGtop4 = iAttackerH;
											}
										}
										else
										{	
											if (m_pClientList[iDGtop5] != NULL)
											{
												if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop5]->m_iDGKills)
												{
													if(iDGtop5!=iAttackerH){
														iDGtop6 = iDGtop5;	
														iDGtop5 = iAttackerH;
													}
												} 
												else
												{	
													if (m_pClientList[iDGtop6] != NULL)
													{
														if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop6]->m_iDGKills)
														{
															if(iDGtop6!=iAttackerH){
																iDGtop7 = iDGtop6;	
																iDGtop6 = iAttackerH;
															}
														}
														else
														{	
															if (m_pClientList[iDGtop7] != NULL)
															{
																if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop7]->m_iDGKills)
																{
																	if(iDGtop7!=iAttackerH){
																		iDGtop8 = iDGtop7;	
																		iDGtop7 = iAttackerH;
																	}
																}
																else
																{	
																	if (m_pClientList[iDGtop8] != NULL)
																	{
																		if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop8]->m_iDGKills)
																		{
																			if(iDGtop8!=iAttackerH){
																				iDGtop9 = iDGtop8;	
																				iDGtop8 = iAttackerH;
																			}
																		}
																		else
																		{	
																			if (m_pClientList[iDGtop9] != NULL)
																			{
																				if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop9]->m_iDGKills)
																				{
																					if(iDGtop9!=iAttackerH){
																						iDGtop10 = iDGtop9;	
																						iDGtop9 = iAttackerH;
																					}
																				}
																				else
																				{	
																					if (m_pClientList[iDGtop10] != NULL)
																					{
																						if (m_pClientList[iAttackerH]->m_iDGKills >= m_pClientList[iDGtop10]->m_iDGKills)
																						{	
																							iDGtop10 = iAttackerH;
																						}
																					}
																					else {
																						iDGtop10 = iAttackerH;
																					}	
																				}
																			} 
																			else {
																				iDGtop9 = iAttackerH;
																			} 
																		}
																	} 
																	else {
																		iDGtop8 = iAttackerH;
																	} 
																}
															} 
															else {
																iDGtop7 = iAttackerH;
															} 
														}
													} 
													else {
														iDGtop6 = iAttackerH;
													} 
												}
											} 
											else {
												iDGtop5 = iAttackerH;
											}
										}
									} 
									else {
										iDGtop4 = iAttackerH;
									} 
								}
							} 
							else {
								iDGtop3 = iAttackerH;
							} 
						}
					} 
					else {
						iDGtop2 = iAttackerH;
					} 
				}
			} 
			else {
				iDGtop1 = iAttackerH;
			}
			RefreshDeathmatch(0);				
		}
		else 
		{
			if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) {
				// 희생자가 여행자이다. 
				if (m_pClientList[iClientH]->m_iPKCount == 0) {

					// 무고한 여행자였다. 공격자는 PK 불이익을 받는다.
					ApplyPKpenalty(iAttackerH, iClientH);
				}
				else {

					// 범죄를 저지른 여행자였다. 공격자는 PK를 잡은것에 대한 포상을 받는다. 
					PK_KillRewardHandler(iAttackerH, iClientH);
				}
			} 
			else {
				// 희생자가 여행자가 아니라 한 마을 소속이다. 
				if (m_pClientList[iClientH]->m_iGuildRank == -1) {
					// 희생자는 시민이다.
					// 공격자가 여행자, 같은 마을 시민, 같은 마을 길드원 -> PK가 됨. 다른 마을 시민, 길드원 -> 정당한 공격
					if (memcmp(m_pClientList[iAttackerH]->m_cLocation, "NONE", 4) == 0) {
						// 공격자가 여행자이다. 				
						if (m_pClientList[iClientH]->m_iPKCount == 0) {
							// 무고한 시민을 여행자가 죽였다. 여행자는 PK가 된다.
							ApplyPKpenalty(iAttackerH, iClientH);
						}
						else {
							// 여행자는 PK를 잡아도 보상을 받지 못한다.
							PK_KillRewardHandler(iAttackerH, iClientH);
						}
					}
					else {
						// 공격자가 시민, 혹은 길드원 -> 마을이 같으면 PK, 다른 마을이라면 정당한 공격 
						if (memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iAttackerH]->m_cLocation, 10) == 0) {
							// 같은 마을 시민을 같은마을 시민 혹은 길드원이 공격한 것이다.  
							if (m_pClientList[iClientH]->m_iPKCount == 0) {
								// 희생자가 무고한 상태. PK이다.
								ApplyPKpenalty(iAttackerH, iClientH);
							}
							else {
								// 범죄자를 잡았다. 
								PK_KillRewardHandler(iAttackerH, iClientH);
							}
						}
						else {
							// 공격자가 다른 마을 소속. 정당한 공격행위
							EnemyKillRewardHandler(iAttackerH, iClientH);
						}
					}
				}
				else {
					// 희생자는 길드원이다. 
					// 공격한 자가 여행자, 시민, 전쟁상태가 아닌 길드원-> PK / 전생상태중인 길드원 -> 정당한 전투행위
					if (memcmp(m_pClientList[iAttackerH]->m_cLocation, "NONE", 4) == 0) {
						// 공격자가 여행자이다.
						if (m_pClientList[iClientH]->m_iPKCount == 0) {
							// 무고한 길드원을 여행자가 죽였다. 여행자는 PK가 된다.
							ApplyPKpenalty(iAttackerH, iClientH);
						}
						else {
							// 여행자는 PK를 잡아도 보상을 받지 못한다.
							PK_KillRewardHandler(iAttackerH, iClientH);
						}
					}
					else {
						// 공격자는 시민 혹은 길드원 -> 마을이 같으면 PK, 다른 마을이라면 정당한 공격 
						if (memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iAttackerH]->m_cLocation, 10) == 0) {
							// 같은 마을 길드원을 같은마을 시민 혹은 길드원이 공격한 것이다.  
							if (m_pClientList[iClientH]->m_iPKCount == 0) {
								// 희생자가 무고한 상태. PK이다.
								ApplyPKpenalty(iAttackerH, iClientH);
							}
							else {
								// 범죄자를 잡았다. 
								PK_KillRewardHandler(iAttackerH, iClientH);
							}
						}
						else {
							// 공격자가 다른 마을 소속. 정당한 공격행위
							EnemyKillRewardHandler(iAttackerH, iClientH);
						}
					}
				}
			}

			// 희생당한 플레이어의 등급에 맞는 페널티를 취한다. 
			if (m_pClientList[iClientH]->m_iPKCount > 0) 
				ApplyCombatKilledPenalty(iClientH, m_pClientList[iClientH]->m_iPKCount, bIsSAattacked);
		}

		memcpy(KilledMessage1, cAttackerName, strlen(cAttackerName));
		strcat(KilledMessage1, " whooped ");
		strcat(KilledMessage1, m_pClientList[iClientH]->m_cCharName);
		strcat(KilledMessage1, "'s ass!");

		memcpy(KilledMessage2, cAttackerName, strlen(cAttackerName));
		strcat(KilledMessage2, " smashed ");
		strcat(KilledMessage2, m_pClientList[iClientH]->m_cCharName);
		strcat(KilledMessage2, "'s face into the ground!");

		memcpy(KilledMessage3, m_pClientList[iClientH]->m_cCharName, strlen(m_pClientList[iClientH]->m_cCharName));
		strcat(KilledMessage3, " was sliced to pieces by ");
		strcat(KilledMessage3, cAttackerName);

		memcpy(KilledMessage4, m_pClientList[iClientH]->m_cCharName, strlen(m_pClientList[iClientH]->m_cCharName));
		strcat(KilledMessage4, " says LAG LAG!! but gets PWNED by ");
		strcat(KilledMessage4, cAttackerName);

		memcpy(KilledMessage5, cAttackerName, strlen(cAttackerName));
		strcat(KilledMessage5, " sent ");
		strcat(KilledMessage5, m_pClientList[iClientH]->m_cCharName);
		strcat(KilledMessage5, " off too pie heaven! ");

		memcpy(KilledMessage6, m_pClientList[iClientH]->m_cCharName, strlen(m_pClientList[iClientH]->m_cCharName));
		strcat(KilledMessage6, " got beat by ");
		strcat(KilledMessage6, cAttackerName);
		strcat(KilledMessage6, "'s ugly stick!");

		for (Killedi = 1; Killedi < DEF_MAXCLIENTS; Killedi++){
			if ((m_pClientList[Killedi] != NULL)) {
				KMRand = rand()%6;
				if (KMRand == 0)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage1);
				}
				else if (KMRand == 1)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage2);
				}
				else if (KMRand == 2)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage3);
				}
				else if (KMRand == 3)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage4);
				}
				else if (KMRand == 4)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage5);
				}
				else if (KMRand == 5)
				{
					SendNotifyMsg(NULL, Killedi, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, KilledMessage6);
				}
				wsprintf(G_cTxt, "%s killed %s", cAttackerName, m_pClientList[iClientH]->m_cCharName);
				PutLogFileList(G_cTxt);
			}
		}
	}
	else if (cAttackerType == DEF_OWNERTYPE_NPC) {

		_bPKLog(DEF_PKLOG_BYNPC,iClientH,NULL,cAttackerName) ;

		// 플레이어가 몹에게 죽었다. 희생당한 플레이어의 등급에 맞는 페널티를 취한다.
		if (m_pClientList[iClientH]->m_iPKCount > 0)
			ApplyCombatKilledPenalty(iClientH, m_pClientList[iClientH]->m_iPKCount, bIsSAattacked);
		
		// 만약 공격한 NPC가 전쟁용 유니트라면 지휘관에게 건설 포인트 부가
		if (m_pNpcList[iAttackerH]->m_iGuildGUID != NULL) {
						
			if (m_pNpcList[iAttackerH]->m_cSide != m_pClientList[iClientH]->m_cSide) {
				// 전쟁용 구조물 혹은 유니트가 적 플레이어를 죽였다. 바로 통보한다.
				// 현재 서버에 지휘관이 있다면 곧바로 통보. 없으면 다른 서버로 알려줌.
				for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_iGuildGUID == m_pNpcList[iAttackerH]->m_iGuildGUID) &&
					(m_pClientList[i]->m_iCrusadeDuty == 3)) {
					m_pClientList[i]->m_iConstructionPoint += ((m_pClientList[iClientH]->m_iLevel+ m_pClientList[iClientH]->m_iMajesticLevel) / 2);

					// 지휘관에게 바로 통보.
					SendNotifyMsg(NULL, i, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[i]->m_iConstructionPoint, m_pClientList[i]->m_iWarContribution, NULL, NULL);
					return;
				}
				
				// 현재 서버에 없다. 다른 서버의 지휘관에게 알려야 한다.
				ZeroMemory(cData, sizeof(cData));
				cp = (char *)cData;
				*cp = GSM_CONSTRUCTIONPOINT;
				cp++;
				ip = (int*)cp;
				*ip = m_pNpcList[iAttackerH]->m_iGuildGUID;
				cp += 4;
				ip = (int*)cp;
				*ip = ((m_pClientList[iClientH]->m_iLevel+ m_pClientList[iClientH]->m_iMajesticLevel) / 2);
				cp += 4;
				bStockMsgToGateServer(cData, 9);
			}
		}
	}
	else if (cAttackerType == DEF_OWNERTYPE_PLAYER_INDIRECT) {
		_bPKLog(DEF_PKLOG_BYOTHER,iClientH,NULL,NULL) ;
		// 플레이어가 죽었지만 공격자가 간접적이다. 아무런 영향이 없다.
		m_pClientList[iClientH]->m_iExp -= iDice(1, 120000000);
		if (m_pClientList[iClientH]->m_iExp < 0) m_pClientList[iClientH]->m_iExp = 0;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);
	}
	else if (cAttackerType == DEF_MAGICTYPE_CREATE_DYNAMIC) {
		EnemyKillRewardHandler(iAttackerH, iClientH);
	}
}

/*********************************************************************************************************************
**  int CGame::iDice(int iThrow, int iRange)																		**
**  description			:: produces a random number between the throw and range										**
**  last updated		:: November 20, 2004; 10:24 PM; Hypnotoad													**
**	return value		:: int																						**
**********************************************************************************************************************/
int CGame::iDice(int iThrow, int iRange)
{
 int i, iRet;

	if (iRange <= 0) return 0;
	iRet = 0;
	for (i = 1; i <= iThrow; i++) {
		iRet += (rand() % iRange) + 1;
	}
	return iRet;
}

void CGame::TimeManaPointsUp(int iClientH)
{
 int iMaxMP, iTotal;
 double dV1, dV2, dV3;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_iHungerStatus <= 0) return;
	if (m_pClientList[iClientH]->m_bSkillUsingStatus[19] == TRUE) return;

	iMaxMP = iGetMaxMP(iClientH);// v1.4
	if (m_pClientList[iClientH]->m_iMP < iMaxMP) {
		iTotal = iDice(1, (m_pClientList[iClientH]->m_iMag+m_pClientList[iClientH]->m_iAngelicMag));
		if (m_pClientList[iClientH]->m_iAddMP != 0) {
			dV2 = (double)iTotal;
			dV3 = (double)m_pClientList[iClientH]->m_iAddMP;
			dV1 = (dV3 / 100.0f)*dV2;
			iTotal += (int)dV1;
		}

		m_pClientList[iClientH]->m_iMP += iTotal;
		
		if (m_pClientList[iClientH]->m_iMP > iMaxMP) 
			m_pClientList[iClientH]->m_iMP = iMaxMP;

		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MP, NULL, NULL, NULL, NULL);
	}
}

// 05/29/2004 - Hypnotoad - fixed infinite sp bug
void CGame::TimeStaminarPointsUp(int iClientH)
{
 int iMaxSP, iTotal=0;
	double dV1, dV2, dV3;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_iHungerStatus <= 0) return;
	if (m_pClientList[iClientH]->m_bSkillUsingStatus[19] == TRUE) return; // v1.4 횄혖횄��붌꺿궗횂쨘횄�뮼궰늘꺿�≥꺜뤓궰궁꺜� 횂짹횄짖횂쩌횄쨘 횂쨩횄짠횂쩔횄짬횄혖횄타횂쩔횂징횂쨈횄��� 횂쩍횂쨘횄��┚꺿�붌궰뮨꺟뮼궰냉꺟� 횂쩔횄�궗횂쨍횂짙횄혖횄쨋 횂쩐횄힋횄�궗횂쩍.
	
	iMaxSP = iGetMaxSP(iClientH);
	if (m_pClientList[iClientH]->m_iSP < iMaxSP) {

		iTotal = iDice(1, (m_pClientList[iClientH]->m_iVit/3)); // Staminar Point쨈횂 10횄횎쨍쨋쨈횢 1D(Vit/3)쩐쩔 쩔횄쨋처째짙쨈횢.
		if (m_pClientList[iClientH]->m_iAddSP != 0) {
			dV2 = (double)iTotal;
			dV3 = (double)m_pClientList[iClientH]->m_iAddSP;
			dV1 = (dV3 / 100.0f)*dV2;
			iTotal += (int)dV1;
		}
	
		// v2.03 쨌쨔쨘짠 60 ��횑횉횕쨈횂 횁짚짹창��청��쨍쨌횓 쩍쨘횇횞쨔횑쨀짧째징 쨍쨔��횑 횂첫쨈횢.
		if (m_pClientList[iClientH]->m_iLevel <= 20) {
			iTotal += 15;
		} else if ( m_pClientList[iClientH]->m_iLevel <= 40) {
			iTotal += 10;
		}  else if ( m_pClientList[iClientH]->m_iLevel <= 60) { 
			iTotal += 5;
		}

		m_pClientList[iClientH]->m_iSP += iTotal;
		if (m_pClientList[iClientH]->m_iSP > iMaxSP) 
			m_pClientList[iClientH]->m_iSP = iMaxSP;

		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
	}
}

void CGame::ToggleCombatModeHandler(int iClientH)
{
	short sAppr2;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;
	// 횁횞��쨘횄쨈횉횕짹창쨀짧 횁횞��쨘 쨩처횇횂쩔징쩌짯쨈횂 쨘짱횊짱횉횘 쩌철 쩐첩쨈횢.
	if (m_pClientList[iClientH]->m_bSkillUsingStatus[19] == TRUE) return;

	sAppr2 = (short)((m_pClientList[iClientH]->m_sAppr2 & 0xF000) >> 12);

	m_pClientList[iClientH]->m_bIsAttackModeChange = TRUE; // v2.172


	if (sAppr2 == 0 && m_pClientList[iClientH]->m_bIsPolymorph == FALSE) {
		// 쨘챰��체횇천 쨍챨쨉책쩔쨈쨈횢. ��체횇천쨍챨쨉책쨌횓 쨔횢짼횤쨈횢.
		m_pClientList[iClientH]->m_sAppr2 = (0xF000 | m_pClientList[iClientH]->m_sAppr2);
	}
	else {
		// ��체횇천 쨍챨쨉책쩔쨈쨈횢. 쨘챰��체횇천쨍챨쨉책쨌횓 쨔횢짼횤쨈횢.
		m_pClientList[iClientH]->m_sAppr2 = (0x0FFF & m_pClientList[iClientH]->m_sAppr2);
	}

	// 횆쨀쨍짱횇횒��횉 쩔횥횉체��횑 쨔횢짼챤쩐첬��쨍쨔횉쨌횓 ��횑쨘짜횈짰쨍짝 ��체쨈횧횉횗쨈횢.
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);

}

void CGame::OnGateSocketEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
 int   iRet;
	
	if (m_pGateSock == NULL) return;

	iRet = m_pGateSock->iOnSocketEvent(wParam, lParam);

	switch (iRet) {
	case DEF_XSOCKEVENT_UNSENTDATASENDCOMPLETE:
		PutLogList("(!!!) Gate-socket connected!");
		SendMsgToGateServer(MSGID_REQUEST_REGISTERGAMESERVER, NULL);
		m_iGateSockConnRetryTimes = 0; // centuu
		break;

	case DEF_XSOCKEVENT_CONNECTIONESTABLISH:
		// 째횚��횑횈짰쩌짯쨔철쨌횓��횉 쩔짭째찼��횑 ��횑쨌챌쩐챤 횁쨀��쨍쨔횉쨌횓 째횚��횙쩌짯쨔철 쨉챤쨌횕 쨍횧쩍횄횁철쨍짝 ��체쩌횤횉횗쨈횢.
		// v1.41 gate-socket��쨩 ��챌쩔짭째찼횉횘 쨋짠 횆짬쩔챤횈횄 횉횕쨈횂 쨘짱쩌철. 쩌짯쨔철 ��횤쨉쩔 쨉쨉횁횩 gate-socket��횑 쩌횘횆횕쩔징쨌짱쨌횓 짼첨짹창쨍챕 째챨쨔횢쨌횓 ��챌횁짖쩌횙��쨩 
		// 쩍횄쨉쨉횉횕쨍챌 ��횑 째짧��횑 ��횕횁짚횆징 ��횑쨩처��횑 쨉횉쨍챕 쩔짭째찼 쩍횉횈횖쨌횓 째짙횁횜쨉횉쩐챤 ��횣쨉쩔 쩌짯쨔철 쩌횏쨈횢쩔챤 쨍챨쨉책(4)쨌횓 쨉챕쩐챤째짙쨈횢. 
		m_iGateSockConnRetryTimes = 0;
		break;
	
	case DEF_XSOCKEVENT_READCOMPLETE:
		// 쨍횧쩍횄횁철째징 쩌철쩍횇쨉횉쩐첬쨈횢.
		OnGateRead();
		break;
	
	case DEF_XSOCKEVENT_BLOCK:
		break;
	
	case DEF_XSOCKEVENT_CONFIRMCODENOTMATCH:
		// 횊짰��횓횆횣쨉책째징 ��횕횆징횉횕횁철 쩐횎쨈횂쨈횢.
	case DEF_XSOCKEVENT_MSGSIZETOOLARGE:
		// 쩌철쩍횇횉횠쩐횩 횉횘 쨍횧쩍횄횁철 횇짤짹창째징 쨔철횈횤쨘쨍쨈횢 횇짤쨈횢.	횁쩐쨌찼횉횠쩐횩쨍쨍 횉횗쨈횢.
	case DEF_XSOCKEVENT_SOCKETERROR:
		// 쩌횘횆횕쩔징 쩔징쨌짱째징 쨀쨉쨈횢.
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 쩌횘횆횕��횑 쨈횦횉청쨈횢.
		delete m_pGateSock;
		m_pGateSock = NULL;
		PutLogList("(!!!) Gate-socket connection lost!");
		m_bIsGateSockAvailable = FALSE;

		// v1.41 Gate Server쨌횓��횉 ��챌쩔짭째찼 쩍횄쨉쨉 
		m_pGateSock = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
		m_pGateSock->bConnect(m_cGateServerAddr, m_iGateServerPort, WM_ONGATESOCKETEVENT);
		m_pGateSock->bInitBufferSize(DEF_MSGBUFFERSIZE);
		// v1.41 쩔짭째찼 쩍횄째짙 횄쩌횇짤쩔챘 
		m_iGateSockConnRetryTimes = 1;

		wsprintf(G_cTxt, "(!!!) Try to reconnect gate-socket... Addr:%s  Port:%d", m_cGateServerAddr, m_iGateServerPort);
		PutLogList(G_cTxt);

		
		break;
	}
}

void CGame::OnGateRead()
{
 DWORD dwMsgSize;
 char * pData, cKey;

	pData = m_pGateSock->pGetRcvDataPointer(&dwMsgSize, &cKey);

	if (bPutMsgQuene(DEF_MSGFROM_GATESERVER, pData, dwMsgSize, NULL, cKey) == FALSE) {
		// 쨍횧쩍횄횁철 횇짜쩔징 ��횑쨩처��횑 쨩첵째책쨈횢. 횆징쨍챠��청��횓 쩔징쨌짱.
		PutLogList("@@@@@@ CRITICAL ERROR in MsgQuene!!! (OnGateRead) @@@@@@");
	}	
}

void CGame::SendMsgToGateServer(DWORD dwMsg, int iClientH, char * pData)
{
 DWORD * dwp;
 WORD  * wp;
 int     iRet, i;
 char    cData[1000], cCharName[11], cAccountName[11], cAccountPassword[11], cAddress[16], cGuildName[21], cTxt[120], * cp;

	if (m_pGateSock == NULL) {
		PutLogList("(!) SendMsgToGateServer fail - Socket to Gate-Server not available.");
		return;
	}

	ZeroMemory(cData, sizeof(cData));
	ZeroMemory(cCharName, sizeof(cCharName));
	ZeroMemory(cAccountName, sizeof(cAccountName));
	ZeroMemory(cAccountPassword, sizeof(cAccountPassword));
	ZeroMemory(cAddress,  sizeof(cAddress));
	ZeroMemory(cGuildName, sizeof(cGuildName));

	switch (dwMsg) {
	// New 07/05/2004
	case MSGID_PARTYOPERATION:
		iRet = m_pGateSock->iSendMsg(pData, 50);
		break;

	case MSGID_SERVERSTOCKMSG:
		iRet = m_pGateSock->iSendMsg(pData, m_iIndexGSS+1);
		break;
	
	case MSGID_ITEMLOG:
		// 쩐횈��횑횇횤 ��체쨈횧 쨌횓짹횞쨈횢. 쨩챌쩔챘횉횕횁철 쩐횎��쩍.
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_ITEMLOG;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		
		cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);
		memcpy(cp, pData, 47);
		cp += 47;

		iRet = m_pGateSock->iSendMsg(cData, 53);
		break;
	
	case MSGID_REQUEST_REGISTERGAMESERVER:
		// 째횚��횑횈짰 쩌짯쨔철쩔징째횚 째횚��횙쩌짯쨔철 쨉챤쨌횕��쨩 쩔채횄쨩횉횗쨈횢.
		wsprintf(cTxt, "(!) Try to register game server(%s) - GateServer", m_cServerName);
		PutLogList(cTxt);
		
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_REQUEST_REGISTERGAMESERVER;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		
		cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);

		memcpy(cAccountName, m_cServerName, 10);
		if (m_iGameServerMode == 1)
		{
			memcpy(cAddress, m_cGameServerAddrInternal, strlen(m_cGameServerAddrInternal));
		}
		if (m_iGameServerMode == 2)
		{
			memcpy(cAddress, m_cGameServerAddr, strlen(m_cGameServerAddr));
		}

		memcpy(cp, cAccountName, 10);
		cp += 10;

		memcpy(cp, cAddress, 16);
		cp += 16;

		wp  = (WORD *)cp;
		*wp = m_iGameServerPort;
		cp += 2;

		*cp = m_iTotalMaps;
		cp++;

		for (i = 0; i < m_iTotalMaps; i++) {
			memcpy(cp, m_pMapList[i]->m_cName, 11);
			cp += 11;
		}
		
		dwp = (DWORD *)cp;
		*dwp = (DWORD)GetCurrentProcessId();	 // 횉횁쨌횓쩌쩌쩍쨘 횉횣쨉챕��쨩 짹창쨌횕횉횗쨈횢.
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = 1126;
		cp += 2;

		iRet = m_pGateSock->iSendMsg(cData, 43 + m_iTotalMaps*11);
		break;

	case MSGID_GAMESERVERALIVE:
		// 횁짚짹창��청��쨍쨌횓 째횚��횙 쩌짯쨔철��횉 횁짚쨘쨍쨍짝 ��체쩌횤 
		// 쨍쨍쩐횪 쨌횓짹횞 쩌짯쨔철쩔횒��횉 쩌횘횆횕 쩔짭째찼��횑 짼첨쩐챤횁쨀쨈횢쨍챕 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쨩횁철 쩐횎쩐횈 쩌짯쨔철쩔징 ��횑쨩처��횑 쨩첵째책��쩍��쨩 쩐횏쨍짰째횚 ��짱쨉쨉횉횗쨈횢.
		if (m_bIsLogSockAvailable == FALSE) return;
		
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_GAMESERVERALIVE;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;

		cp  = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);
		wp  = (WORD *)cp;
		*wp = m_iTotalClients;
		cp += 2;
		
		iRet = m_pGateSock->iSendMsg(cData, 8);
		break;
	}

	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 째횚��횑횈짰 쩌짯쨔철쨌횓 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩐쨋짠 쩔징쨌짱째징 쨔횩쨩첵횉횩쨈횢.
		PutLogList("(***) Socket to Gate-Server crashed! Critical error!");
		delete m_pGateSock;
		m_pGateSock = NULL;
		m_bIsGateSockAvailable = FALSE;

		// v1.41 Gate Server쨌횓��횉 ��챌쩔짭째찼 쩍횄쨉쨉: 쩌짯쨔철쨍짝 쩌횏쨈횢쩔챤 횉횕쨈횂 째횒��횑 쩐횈쨈횕쨈횢. 
		m_pGateSock = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
		m_pGateSock->bConnect(m_cGateServerAddr, m_iGateServerPort, WM_ONGATESOCKETEVENT);
		m_pGateSock->bInitBufferSize(DEF_MSGBUFFERSIZE);
		// v1.41 쩔짭째찼 쩍횄째짙 횄쩌횇짤쩔챘 
		m_iGateSockConnRetryTimes = 1;	

		wsprintf(G_cTxt, "(!) Try to reconnect gate-socket... Addr:%s  Port:%d", m_cGateServerAddr, m_iGateServerPort);
		PutLogList(G_cTxt);

		
		break;
	}
}

void CGame::Quit()
{
 int i;	

	// 쩐짼쨌쨔쨉책쨍짝 횁횞��횓쨈횢.
	G_bIsThread = FALSE;
	Sleep(300);
		
	if (m_pMainLogSock != NULL) delete m_pMainLogSock;
	if (m_pGateSock != NULL) delete m_pGateSock;

	for (i = 0; i < DEF_MAXSUBLOGSOCK; i++)
		if (m_pSubLogSock[i] != NULL) delete m_pSubLogSock[i];

	for (i = 0; i < DEF_MAXCLIENTS; i++)
	if (m_pClientList[i] != NULL) delete m_pClientList[i];

	for (i = 0; i < DEF_MAXNPCS; i++)
	if (m_pNpcList[i] != NULL) delete m_pNpcList[i];

	for (i = 0; i < DEF_MAXMAPS; i++)
	if (m_pMapList[i] != NULL) delete m_pMapList[i];

	for (i = 0; i < DEF_MAXITEMTYPES; i++)
	if (m_pItemConfigList[i] != NULL) delete m_pItemConfigList[i];

	for (i = 0; i < DEF_MAXNPCTYPES; i++)
	if (m_pNpcConfigList[i] != NULL) delete m_pNpcConfigList[i];

	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
	if (m_pMagicConfigList[i] != NULL) delete m_pMagicConfigList[i];

	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
	if (m_pSkillConfigList[i] != NULL) delete m_pSkillConfigList[i];

	for (i = 0; i < DEF_MAXQUESTTYPE; i++)
	if (m_pQuestConfigList[i] != NULL) delete m_pQuestConfigList[i];

	for (i = 0; i < DEF_MAXDYNAMICOBJECTS; i++)
	if (m_pDynamicObjectList[i] != NULL) delete m_pDynamicObjectList[i];

	for (i = 0; i < DEF_MAXDELAYEVENTS; i++)
	if (m_pDelayEventList[i] != NULL) delete m_pDelayEventList[i];

	for (i = 0; i < DEF_MAXNOTIFYMSGS; i++)
	if (m_pNoticeMsgList[i] != NULL) delete m_pNoticeMsgList[i];

	for (i = 0; i < DEF_MAXFISHS; i++)
	if (m_pFish[i] != NULL) delete m_pFish[i];

	for (i = 0; i < DEF_MAXMINERALS; i++)
	if (m_pMineral[i] != NULL) delete m_pMineral[i];

	for (i = 0; i < DEF_MAXPOTIONTYPES; i++) {
		if (m_pPotionConfigList[i] != NULL) delete m_pPotionConfigList[i];
		if (m_pCraftingConfigList[i] != NULL) delete m_pCraftingConfigList[i];	// Crafting
	}

	for (i = 0; i < DEF_MAXBUILDITEMS; i++) 
	if (m_pBuildItemList[i] != NULL) delete m_pBuildItemList[i];

	for (i = 0; i < DEF_MAXDUPITEMID; i++)
	if (m_pDupItemIDList[i] != NULL) delete m_pDupItemIDList[i];

	if (m_pNoticementData != NULL) delete[] m_pNoticementData;

}

long CGame::iGetLevelExp(int iLevel)
{
 unsigned long iRet;
	
	if (iLevel == 0) return 0;
	
	iRet = iGetLevelExp(iLevel - 1) + iLevel * ( 50 + (iLevel * (iLevel / 17) * (iLevel / 17) ) );

	return iRet;
}

// 2003-04-14 횁철횁쨍 횈첨��횓횈짰쨍짝 쨌쨔쨘짠 쩌철횁짚쩔징 쩐쨉쩌철 ��횜쨈횢...
/////////////////////////////////////////////////////////////////////////////////////
//  StateChangeHandler(int iClientH, char * pData, DWORD dwMsgSize)
//  desc		 :: 횁철횁쨍횈첨��횓횈짰쨍짝 쨌쨔쨘짠쩐첨 횈첨��횓횈짰쨌횓 쨉쨔쨍째쨈횢...
//	return value :: void
//  date		 :: [2003-04-14]    stupid koreans
/////////////////////////////////////////////////////////////////////////////////////
void CGame::StateChangeHandler(int iClientH, char * pData, DWORD dwMsgSize)
{char * cp, cStateChange1, cStateChange2, cStateChange3;
 char cStr, cVit, cDex, cInt, cMag, cChar;
 int iOldStr, iOldVit, iOldDex, iOldInt, iOldMag, iOldChar;	
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_iGizonItemUpgradeLeft <= 0) return;
	cStr = cVit = cDex = cInt = cMag = cChar = 0;
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	cStateChange1 = *cp;
	cp++;
	cStateChange2 = *cp;
	cp++;
	cStateChange3 = *cp;
	cp++;
	iOldStr	= m_pClientList[iClientH]->m_iStr;
	iOldVit	= m_pClientList[iClientH]->m_iVit;
	iOldDex = m_pClientList[iClientH]->m_iDex;
	iOldInt = m_pClientList[iClientH]->m_iInt;
	iOldMag = m_pClientList[iClientH]->m_iMag;
	iOldChar = m_pClientList[iClientH]->m_iCharisma;	
		
	if(!bChangeState(cStateChange1,&cStr,&cVit,&cDex,&cInt,&cMag,&cChar))
	{	// SNOOPY: Stats order was wrong here !
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if(!bChangeState(cStateChange2,&cStr,&cVit,&cDex,&cInt,&cMag,&cChar))
	{	// SNOOPY: Stats order was wrong here !
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if(!bChangeState(cStateChange3,&cStr,&cVit,&cDex,&cInt,&cMag,&cChar))
	{	// SNOOPY: Stats order was wrong here !
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if(m_pClientList[iClientH]->m_iGuildRank == 0 )
	{	if(m_pClientList[iClientH]->m_iCharisma - cChar < 20)
		{	// gm cn't drop charisma below 20
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
			return;
	}	}
	if(iOldStr +iOldVit	+iOldDex +iOldInt +iOldMag +iOldChar != ((m_iPlayerMaxLevel-1)*3 + 70))
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if(cStr < 0 || cVit < 0 || cDex < 0 || cInt < 0 || cMag < 0 || cChar < 0
		|| cStr + cVit + cDex + cInt + cMag + cChar != 3)
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iStr - cStr > m_sCharStatLimit - 11) 
		 || (m_pClientList[iClientH]->m_iStr - cStr < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iVit - cVit > m_sCharStatLimit - 11)
		 || (m_pClientList[iClientH]->m_iVit - cVit < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iDex - cDex > m_sCharStatLimit - 11)
		 || (m_pClientList[iClientH]->m_iDex - cDex < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iInt - cInt > m_sCharStatLimit - 11)
		 || (m_pClientList[iClientH]->m_iInt - cInt < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iMag - cMag > m_sCharStatLimit - 11)
		 || (m_pClientList[iClientH]->m_iMag - cMag < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	if ((m_pClientList[iClientH]->m_iCharisma - cChar > m_sCharStatLimit - 11)
		 || (m_pClientList[iClientH]->m_iCharisma - cChar < 10)) 
	{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_FAILED, NULL, NULL, NULL, NULL);
		return;
	}
	m_pClientList[iClientH]->m_iLU_Pool += 3;
	m_pClientList[iClientH]->m_iGizonItemUpgradeLeft--;
	m_pClientList[iClientH]->m_iStr  -= cStr;
	m_pClientList[iClientH]->m_iVit  -= cVit;
	m_pClientList[iClientH]->m_iDex  -= cDex;
	m_pClientList[iClientH]->m_iInt  -= cInt;
	m_pClientList[iClientH]->m_iMag  -= cMag;
	m_pClientList[iClientH]->m_iCharisma -= cChar;
	if (cInt > 0) bCheckMagicInt(iClientH);
	// Snoopy: Check max values here or character will be considered as hacker if reducing mana or vit
	if (m_pClientList[iClientH]->m_iHP > iGetMaxHP(iClientH)) m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH, FALSE);
	if (m_pClientList[iClientH]->m_iMP > iGetMaxMP(iClientH)) m_pClientList[iClientH]->m_iMP = iGetMaxMP(iClientH);
	if (m_pClientList[iClientH]->m_iSP > iGetMaxSP(iClientH)) m_pClientList[iClientH]->m_iSP = iGetMaxSP(iClientH);
	
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_STATECHANGE_SUCCESS, NULL, NULL, NULL, NULL);
}

// 2003-04-14 횁철횁쨍 횈첨��횓횈짰쨍짝 쨌쨔쨘짠 쩌철횁짚쩔징 쩐쨉쩌철 ��횜쨈횢...
/////////////////////////////////////////////////////////////////////////////////////
//  bChangeState(char cStateChange 
//  		  ,char* cStr, char *cVit,char *cDex,char *cInt,char *cMag,char *cChar)
//  desc		 :: 횁철횁쨍 횈첨��횓횈짰쨌횓 횈짱쩌쨘째짧 쨔횢짼횥�믠�씳�쨩 쨈천횉횠 횁횠쨈횢...
//	return value :: BOOL횉체 0(FASLE) 쩔징쨌짱 쨌쨔쨘짠 쩌철횁짚 쨘횘째징...
//  date		 :: [2003-04-14] 
/////////////////////////////////////////////////////////////////////////////////////
BOOL CGame::bChangeState(char cStateChange, char* cStr, char *cVit,char *cDex,char *cInt,char *cMag,char *cChar)
{	// centu - fixed
	if(cStateChange == DEF_STR)
	{	++*cStr; 
	}else if(cStateChange == DEF_VIT)
	{	++*cVit; 
	}else if(cStateChange == DEF_DEX)
	{	++*cDex; 
	}else if(cStateChange == DEF_INT)
	{	++*cInt; 
	}else if(cStateChange == DEF_MAG)
	{	++*cMag; 
	}else if(cStateChange == DEF_CHR)
	{	++*cChar; 
	}else
	{	return 0;
	}
	return cStateChange;
}

void CGame::LevelUpSettingsHandler(int iClientH, char * pData, DWORD dwMsgSize)
{
	char* cp;
	// sleeq - fix for negative level up points
	short* sp;
	short cStr, cVit, cDex, cInt, cMag, cChar;
	int iTotalSetting = 0;


	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_iLU_Pool <= 0) 
	{
		//횉횠횆쩔��횓째징??
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SETTING_FAILED, NULL, NULL, NULL, NULL);
		return ;
	}
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);

	sp = (short*)cp;
	cStr = *sp;
	cp += 2;

	sp = (short*)cp;
	cVit = *sp;
	cp += 2;

	sp = (short*)cp;
	cDex = *sp;
	cp += 2;

	sp = (short*)cp;
	cInt = *sp;
	cp += 2;

	sp = (short*)cp;
	cMag = *sp;
	cp += 2;

	sp = (short*)cp;
	cChar = *sp;
	cp += 2;


	if ( (cStr + cVit + cDex + cInt + cMag + cChar) > m_pClientList[iClientH]->m_iLU_Pool) { // -3
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SETTING_FAILED, NULL, NULL, NULL, NULL);
			return;
	}

	// Level-Up Setting째짧쩔징 쩔��쨌첫째징 ��횜쨈횂횁철 째횏쨩챌횉횗쨈횢.
	if ((m_pClientList[iClientH]->m_iStr + cStr > m_sCharStatLimit - 11) || (cStr < 0))
		return;

	if ((m_pClientList[iClientH]->m_iDex + cDex > m_sCharStatLimit - 11) || (cDex < 0))
		return;

	if ((m_pClientList[iClientH]->m_iInt + cInt > m_sCharStatLimit - 11) || (cInt < 0))
		return;

	if ((m_pClientList[iClientH]->m_iVit + cVit > m_sCharStatLimit - 11) || (cVit < 0))
		return;

	if ((m_pClientList[iClientH]->m_iMag + cMag > m_sCharStatLimit - 11) || (cMag < 0))
		return;

	if ((m_pClientList[iClientH]->m_iCharisma + cChar > m_sCharStatLimit - 11) || (cChar < 0))
		return;

	iTotalSetting = m_pClientList[iClientH]->m_iStr + m_pClientList[iClientH]->m_iDex + m_pClientList[iClientH]->m_iVit + 
		m_pClientList[iClientH]->m_iInt + m_pClientList[iClientH]->m_iMag + m_pClientList[iClientH]->m_iCharisma;

	//(쨌쨔쨘짠 횈짱쩌쨘째짧 + 쨌쨔쨘짠쩐첨 횈첨��횓횈짰 > 쨌쨔쨘짠쩐첨 횈짱쩌쨘째짧 횁짚쨩처횆징)쨍챕 쨘챰횁짚쨩처��횑쨈횢.. 횄쨀쨍짰 쨘횘째징.. 쨌쨔쨘짠쩐첨 횈첨��횓횈짰쨍짝 횁짚쨩처횆징쨌횓 쨍쨋횄횩째챠 횄쨀쨍짰 쨘횘째징..
	if (iTotalSetting + m_pClientList[iClientH]->m_iLU_Pool -3 > ((m_pClientList[iClientH]->m_iLevel-1)*3 + 70))
	{
		
		m_pClientList[iClientH]->m_iLU_Pool = 3 + (m_pClientList[iClientH]->m_iLevel-1)*3 + 70 - iTotalSetting;

		//iTotalSetting째짧��횑 ��횩쨍첩쨉횊 째챈쩔챙쨈횢...
		if(m_pClientList[iClientH]->m_iLU_Pool < 3)
			m_pClientList[iClientH]->m_iLU_Pool = 3;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SETTING_FAILED, NULL, NULL, NULL, NULL);
		return ;
	}

	//(쨌쨔쨘짠 횈짱쩌쨘째짧 + 쨌쨔쨘짠쩐첨 쩍횄횇쨀 횈첨��횓횈짰 횁D > 쨌쨔쨘짠쩐첨 횈짱쩌쨘째짧 횁짚쨩처횆징)��횑쨍챕 횄쨀쨍짰 쨘횘째징..
	if (iTotalSetting + (cStr + cVit + cDex + cInt + cMag + cChar) >	((m_pClientList[iClientH]->m_iLevel-1)*3 + 70)) 
	{
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SETTING_FAILED, NULL, NULL, NULL, NULL);
		return;
	}

	m_pClientList[iClientH]->m_iLU_Pool -= (cStr + cVit + cDex + cInt + cMag + cChar);

	// 쩔��쨌첫째징 쩐첩��쨍쨍챕 째짧��쨩 횉횘쨈챌횉횗쨈횢.
	m_pClientList[iClientH]->m_iStr  += cStr;
	m_pClientList[iClientH]->m_iVit  += cVit;
	m_pClientList[iClientH]->m_iDex  += cDex;
	m_pClientList[iClientH]->m_iInt  += cInt;
	m_pClientList[iClientH]->m_iMag  += cMag;
	m_pClientList[iClientH]->m_iCharisma += cChar;

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SETTING_SUCCESS, NULL, NULL, NULL, NULL);

}

// v1.4311-3 횄횩째징 쨩챌횇천��책 쩔쨔쩐횪 횉횚쩌철 FightzoneReserveHandler
void CGame::FightzoneReserveHandler(int iClientH, char * pData, DWORD dwMsgSize)
{
 char cData[100];
 int iFightzoneNum ,* ip ,  iEnableReserveTime ;
 DWORD * dwp, dwGoldCount ;
 WORD  * wp, wResult;
 int     iRet, iResult=1, iCannotReserveDay;
 SYSTEMTIME SysTime;
 
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
 
	GetLocalTime(&SysTime);
	
	// 쩔쨔쩐횪 째징쨈횋횉횗 쩍횄째짙 : 쨉횓쩍횄째짙 째짙째횦��쨍쨌횓 쩔쨔쩐횪��횑 째징쨈횋횉횕쨍챌 쨩챌쩔챘쩔횕쨌찼 5쨘횖��체쩔징쨈횂 쩔쨔쩐횪��횑 쨘횘째징쨈횋횉횕쨈횢.
	iEnableReserveTime  = 2*20*60 - ((SysTime.wHour%2)*20*60 + SysTime.wMinute*20) - 5*20;
	
	dwGoldCount = dwGetItemCount(iClientH, "Gold");
		
	ip = (int *)(pData + DEF_INDEX2_MSGTYPE + 2);
	// 쩔쨔쩐횪��쨩 쩔첩횉횕쨈횂 쨩챌횇천��책 쨔첩횊짙쨍짝 쨔횧쨈횂쨈횢.
	iFightzoneNum = *ip;

	// ��횩쨍첩쨉횊 fightzone 쨔첩횊짙쨍짝 째횋쨌짱쨀쩍쨈횢.
	if ((iFightzoneNum < 1) || (iFightzoneNum > DEF_MAXFIGHTZONE)) return;

	iCannotReserveDay = (SysTime.wDay + m_pClientList[iClientH]->m_cSide + iFightzoneNum ) % 2 ;
	if (iEnableReserveTime <= 0 ){
		wResult = DEF_MSGTYPE_REJECT;
		iResult = 0 ;
	} else if (m_iFightZoneReserve[iFightzoneNum-1] != 0){
		wResult = DEF_MSGTYPE_REJECT;
		iResult = -1 ;
	} else if ( dwGoldCount < 1500 ) {
		wResult = DEF_MSGTYPE_REJECT;
		iResult = -2 ;	           // 쨉쨌��횑 ��청��쨍쨍챕 -2 째짧��쨩 횇짭쨋처��횑쩐챨횈짰쩔징째횚 쨘쨍쨀쩍쨈횢.
	} else if( iCannotReserveDay ) {
		wResult = DEF_MSGTYPE_REJECT;
		iResult = -3 ;
	} else if( m_pClientList[iClientH]-> m_iFightzoneNumber != 0 ) {
		wResult = DEF_MSGTYPE_REJECT;
		iResult = -4 ;
	} else {
		wResult = DEF_MSGTYPE_CONFIRM;

		SetItemCount(iClientH, "Gold", dwGoldCount - 1500);
		iCalcTotalWeight(iClientH);
		
		m_iFightZoneReserve[iFightzoneNum-1] = iClientH;
		
		m_pClientList[iClientH]->m_iFightzoneNumber  = iFightzoneNum ;
		m_pClientList[iClientH]->m_iReserveTime	 =  SysTime.wMonth*10000 + SysTime.wDay*100 + SysTime.wHour ;  

		if (SysTime.wHour%2 )	m_pClientList[iClientH]->m_iReserveTime  ++  ;	// 횊짝쩌철 쩍횄째짙쨈챘��횑쨍챕 횉횗쩍횄째짙 횊횆짹챤횁철 쩔쨔쩐횪쨉횊쨈횢.
		else					m_pClientList[iClientH]->m_iReserveTime  += 2  ;    // 횂짝쩌철 쩍횄째짙쨈챘��횑쨍챕 쨉횓 쩍횄째짙 횊횆짹챤횁철 쩔쨔쩐횪쨉횊쨈횢.
		wsprintf(G_cTxt, "(*) Reserve FIGHTZONETICKET : Char(%s) TICKENUMBER (%d)", m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iReserveTime);		
		PutLogFileList(G_cTxt);
		PutLogList(G_cTxt);

		m_pClientList[iClientH]->m_iFightZoneTicketNumber  = 50 ;  
		iResult = 1 ;
	}  

	ZeroMemory(cData, sizeof(cData));

	dwp = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_FIGHTZONE_RESERVE;

	wp = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp =  wResult ;

	ip  = (int *)(cData + DEF_INDEX2_MSGTYPE+2) ; 
	*ip =  iResult ;
	ip+= 4;
	
	// 쨩챌횇천��책 쩔쨔쩐횪 ����쨈채 쨍횧쩌쩌횁철  횇짭쨋처��횑쩐챨횈짰쩔징째횚 ��체쩌횤
		
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 10);
 
	switch (iRet) {
		case DEF_XSOCKEVENT_QUENEFULL:
		case DEF_XSOCKEVENT_SOCKETERROR:
		case DEF_XSOCKEVENT_CRITICALERROR:
		case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩐쨋짠 쩔징쨌짱째징 쨔횩쨩첵횉횩쨈횢쨍챕 횁짝째횇횉횗쨈횢.
		DeleteClient(iClientH, TRUE, TRUE);
		break;
	}
}

BOOL CGame::bCheckLimitedUser(int iClientH)
{
	if (m_pClientList[iClientH] == NULL) return FALSE;
	
	if ( (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) && 
		 (m_pClientList[iClientH]->m_iExp >= m_iLevelExp20 ) ) {
		// 쩔짤횉횪��횣째징 쨌쨔쨘짠 20 째챈횉챔횆징쨍짝 쩐챵쩐첬쨈횢쨍챕 19쩌철횁횠��쨍쨌횓 횊짱쩔첩. 

		m_pClientList[iClientH]->m_iExp = m_iLevelExp20 - 1;	
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_TRAVELERLIMITEDLEVEL, NULL, NULL, NULL, NULL);
		return TRUE;
	}


	return FALSE;
}

void CGame::RequestCivilRightHandler(int iClientH, char *pData)
{
 char * cp, cData[100];
 DWORD * dwp;
 WORD * wp, wResult;
 int  iRet;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if ((m_bAdminSecurity == TRUE) && (m_pClientList[iClientH]->m_iAdminUserLevel > 0)) return;

	// ?�쉻夷뷀쉻 �쉲�슅 夷띿쮮?夷�?�쉲 姨뚰슆姨뚰슇?�쉻 ?�슌夷덊슓夷띿콝 姨랁쉪夷뷀슀吏뱁쉲?夷� 吏몄쭠�쉧泥� 姨뚯쿋 姨먯꺽夷덊슓. 
	if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) != 0) wResult = 0;
	else wResult = 1;

	// 夷뚯쮷夷섏쭬?�쉻 5 ?�쉻�쉲�슃夷뗭쿂夷됱쮬 姨랁쉪夷뷀슀吏뱁쉲?夷� 姨먯굘?夷� 姨뚯쿋 姨먯꺽夷덊슓. 
	if (m_pClientList[iClientH]->m_iLevel < 5) wResult = 0;
	
	if (wResult == 1) {
		// �쉲泥�?梨� 夷랁쉸?�쉲 ?�쉻夷띿쭬?夷� �쉲�슆夷덉콐�쉲�슅夷덊슓.
		ZeroMemory(m_pClientList[iClientH]->m_cLocation, sizeof(m_pClientList[iClientH]->m_cLocation));
		strcpy(m_pClientList[iClientH]->m_cLocation, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName);
	}

	// Side �쉲�슆夷덉콐
	if (memcmp(m_pClientList[iClientH]->m_cLocation, "are", 3) == 0) 
		m_pClientList[iClientH]->m_cSide = 1;

	else if (memcmp(m_pClientList[iClientH]->m_cLocation, "elv", 3) == 0) 
		m_pClientList[iClientH]->m_cSide = 2;

	dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_CIVILRIGHT;
	wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp  = wResult;

	// v1.41 夷랁쉸 ?�쉻夷띿쭬 姨먰쉹夷뚰쉧�쉧�슖 
	cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cp, m_pClientList[iClientH]->m_cLocation, 10);
	cp += 10;

	// ??夷덉콈 夷랁슙姨랁쉪�쉧泥좎쮰吏� �쉯吏�夷뗭쿂?�쉻姨먯괩�쉱吏곗찓吏뺤㎏�슊 ?泥댁찈�슕
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 16);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 夷랁슙姨랁쉪�쉧泥좎쮰吏� 夷섏쮰夷�姨먯쮮吏� 姨붿쭠夷뚯㎟吏몄쭠 夷뷀슜夷⑹껨�쉲�슜夷덊슓夷띿콝 �쉧吏앹㎏�쉯�쉲�슅夷덊슓.
		DeleteClient(iClientH, TRUE, TRUE);
		return;
	}
	// �쉱吏깆찈夷�?�쉻 夷뷀슓吏쇱광夷뷀쉲夷뚰슀 姨뷀슖姨먯콐?夷� 夷⑹쿇夷뚰슀 夷섏쮰夷�姨띿쮫�슓. 
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
	// new
	if (m_pClientList[iClientH]->m_iPartyID != NULL) {
		RequestDeletePartyHandler(iClientH);
	}
	RequestChangePlayMode(iClientH); // new
}

// 05/21/2004 - Hypnotoad - send player to jail
void CGame::ApplyPKpenalty(short sAttackerH, short sVictumH)
{
	int iV1, iV2;

	if (m_pClientList[sAttackerH] == NULL) return;
	if (m_pClientList[sVictumH] == NULL) return;
	// 쩐횊��체 째첩째횦 쨍챨쨉책째징 횆횗횁첩 쨩처횇횂쩔징쩌짯 째첩째횦��쨍쨌횓 ��횓횉횠 째째��쨘 횈챠��횑 횁횞��쨩쩌철쨈횂 쩐첩횁철쨍쨍 쨍쨍쩐횪 ��횜��쨩째챈쩔챙 쨔짬쩍횄 
	// 쨈횥 째첩째횦��횣째징 쨔체횁횏��횣째징 쩐횈쨈횕쩐챤쩐횩쨍쨍 횉횠쨈챌쨉횊쨈횢.
	if ((m_pClientList[sAttackerH]->m_bIsSafeAttackMode == TRUE) && (m_pClientList[sAttackerH]->m_iPKCount == 0)) return; 

	// PK Count 횁천째징  
	m_pClientList[sAttackerH]->m_iPKCount++;

	_bPKLog(DEF_PKLOG_BYPK,sAttackerH,sVictumH,NULL) ;

	// 째챈횉챔횆징 째짢쩌횘 
	iV1 = iDice(((m_pClientList[sVictumH]->m_iLevel+ m_pClientList[sVictumH]->m_iMajesticLevel )/2)+1, 50);
	iV2 = iDice(((m_pClientList[sAttackerH]->m_iLevel+ m_pClientList[sAttackerH]->m_iMajesticLevel)/2)+1, 50);

	m_pClientList[sAttackerH]->m_iExp -= iV1; 
	m_pClientList[sAttackerH]->m_iExp -= iV2;
	if (m_pClientList[sAttackerH]->m_iExp < 0) m_pClientList[sAttackerH]->m_iExp = 0;

	// 횈채쨀횓횈쩌쨍짝 쨍횚쩐첬��쩍��쨩 쩐횏쨌횁횁횠쨈횢.
	SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_PKPENALTY, NULL, NULL, NULL, NULL);	

	// 횈짱쩌쨘��횑 쨔횢짼챤쨔횉쨌횓 쩔횥쩐챌��쨩 쨩천쨌횓 쨘쨍쨀쩍쨈횢. 
	SendEventToNearClient_TypeA(sAttackerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);

	// v1.41 Rating 횉횕쨋척 
	m_pClientList[sAttackerH]->m_iRating -= 10;
	
	// MORLA 2.4 - Actualizo la REP
	SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_REPDGDEATHS, m_pClientList[sAttackerH]->m_iDGPoints, m_pClientList[sAttackerH]->m_iDeaths, m_pClientList[sAttackerH]->m_iRating, NULL);

	if (strcmp(m_pClientList[sAttackerH]->m_cLocation, "aresden") == 0) {
		if ( (strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "arebrk11") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "arebrk12") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "arebrk21") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "arebrk22") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "aresden") == 0)   ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "huntzone2") == 0) ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "areuni") == 0)    ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "arefarm") == 0)) {

				// 쩐횈쨌쨔쩍쨘쨉짠 짹횢짹쨀쩔징쩌짯 PK쨍짝 횉횩쨈횢. 쨘챠쨍짰쨉첫 횇횣쨌쨔횈첨횈짰 5쨘횖
				// v2.16 쩌쨘횊횆쨈횕 쩌철횁짚
				ZeroMemory(m_pClientList[sAttackerH]->m_cLockedMapName, sizeof(m_pClientList[sAttackerH]->m_cLockedMapName));
				strcpy(m_pClientList[sAttackerH]->m_cLockedMapName, "arejail");
				m_pClientList[sAttackerH]->m_iLockedMapTime = 60*3;
				RequestTeleportHandler(sAttackerH, "2   ", "arejail", -1, -1);
						
			}
	}

	else if (strcmp(m_pClientList[sAttackerH]->m_cLocation, "elvine") == 0) {
		if ( (strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvbrk11") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvbrk12") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvbrk21") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvbrk22") == 0)  ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvine") == 0)    ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "huntzone1") == 0) ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvuni") == 0)    ||
			(strcmp(m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cName, "elvfarm") == 0)) {

				// 쩔짚쨔횢��횓 짹횢짹쨀쩔징쩌짯 PK쨍짝 횉횩쨈횢. 쨘챠쨍짰쨉첫 횇횣쨌쨔횈첨횈짰 5쨘횖
				ZeroMemory(m_pClientList[sAttackerH]->m_cLockedMapName, sizeof(m_pClientList[sAttackerH]->m_cLockedMapName));
				strcpy(m_pClientList[sAttackerH]->m_cLockedMapName, "elvjail");
				m_pClientList[sAttackerH]->m_iLockedMapTime = 60*3;
				RequestTeleportHandler(sAttackerH, "2   ", "elvjail", -1, -1);
					
			}
	}
}


// 05/17/2004 - Hypnotoad - register pk log
void CGame::PK_KillRewardHandler(short sAttackerH, short sVictumH)
{
	if (m_pClientList[sAttackerH] == NULL) return;
	if (m_pClientList[sVictumH] == NULL)   return;

	_bPKLog(DEF_PKLOG_BYPLAYER,sAttackerH,sVictumH,NULL) ;

	if (m_pClientList[sAttackerH]->m_iPKCount == 0) {
		// PK쨍짝 ��창��쨘 쨩챌쨋첨��횑 PK쨍챕 쩐횈쨔짬쨌짹 쨉챈��횑 쩐첩쨈횢.

		// 횈첨쨩처짹횦쨍쨍 쨈짤��청. 째챈횉챔횆징쨈횂 쩔��쨍짙횁철 쩐횎쨈횂쨈횢. 
		m_pClientList[sAttackerH]->m_iRewardGold += iGetExpLevel(m_pClientList[sVictumH]->m_iExp) * 3;
		
		if (m_pClientList[sAttackerH]->m_iRewardGold < 0) 
			m_pClientList[sAttackerH]->m_iRewardGold = 0;

		SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_PKCAPTURED, m_pClientList[sVictumH]->m_iPKCount, m_pClientList[sVictumH]->m_iLevel, NULL, m_pClientList[sVictumH]->m_cCharName);
	}
}

void CGame::EnemyKillRewardHandler(int iAttackerH, int iClientH)
{
	// enemy-kill-mode = 1 | 0
	// if m_bEnemyKillMode is true than death match mode

	// DEATHMATCH MODE:
	// Aresden kills Elvine in Aresden and gets EK
	// Elvine kills Aresden in Aresden and gets an EK 
	// Elvine kills Aresden in Elvine and gets an EK
	// Aresden kills Elvine in Elvine and gets an EK

	// CLASSIC MODE:
	// Aresden kills Elvine in Aresden and gets EK
	// Elvine kills Aresden in Aresden and doesnt get an EK 
	// Elvine kills Aresden in Elvine and gets an EK
	// Aresden kills Elvine in Elvine and doesnt get an EK
	
	unsigned long iRewardExp;

	int iRangoAttacker = 1;
	
	// if the attacker doesnt exist no result
	if (m_pClientList[iAttackerH] == NULL) return;
	// if the target doesnt exist no result
	if (m_pClientList[iClientH] == NULL)   return;

	// anti lammer
	if ((strcmp(m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iAttackerH]->m_cIP2) == 0) || (strcmp(m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iAttackerH]->m_cIPaddress) == 0)) return; 
	strcpy(m_pClientList[iAttackerH]->m_cIP2, m_pClientList[iClientH]->m_cIPaddress);

	// Log the EK (killed by enemy)
	_bPKLog(DEF_PKLOG_BYENERMY,iAttackerH,iClientH,NULL) ;

	// MORLA2.2 - EK y REP segun Rango
	
		if(((m_pClientList[iClientH]->m_iMaxEK >= 200) && (m_pClientList[iClientH]->m_iRating < 40 )) || ((m_pClientList[iClientH]->m_iMaxEK < 300) && (m_pClientList[iClientH]->m_iRating >= 30 )))
		{	iRangoAttacker = 2;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 300) && (m_pClientList[iClientH]->m_iRating < 50 )) || ((m_pClientList[iClientH]->m_iMaxEK < 400) && (m_pClientList[iClientH]->m_iRating >= 40 )))
		{	iRangoAttacker = 3;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 400) && (m_pClientList[iClientH]->m_iRating < 60 )) || ((m_pClientList[iClientH]->m_iMaxEK < 500) && (m_pClientList[iClientH]->m_iRating >= 50 )))
		{	iRangoAttacker = 4;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 500) && (m_pClientList[iClientH]->m_iRating < 70 )) || ((m_pClientList[iClientH]->m_iMaxEK < 600) && (m_pClientList[iClientH]->m_iRating >= 60 )))
		{	iRangoAttacker = 5;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 600) && (m_pClientList[iClientH]->m_iRating < 80 )) || ((m_pClientList[iClientH]->m_iMaxEK < 700) && (m_pClientList[iClientH]->m_iRating >= 70 )))
		{	iRangoAttacker = 6;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 700) && (m_pClientList[iClientH]->m_iRating < 90 )) || ((m_pClientList[iClientH]->m_iMaxEK < 800) && (m_pClientList[iClientH]->m_iRating >= 80 )))
		{	iRangoAttacker = 7;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 800) && (m_pClientList[iClientH]->m_iRating < 100 )) || ((m_pClientList[iClientH]->m_iMaxEK < 900) && (m_pClientList[iClientH]->m_iRating >= 90 )))
		{	iRangoAttacker = 8;
		}
		else if(((m_pClientList[iClientH]->m_iMaxEK >= 900) && (m_pClientList[iClientH]->m_iRating < 200 )) || ((m_pClientList[iClientH]->m_iMaxEK < 1000) && (m_pClientList[iClientH]->m_iRating >= 100 )))
		{	iRangoAttacker = 9;
		}
		else if( (m_pClientList[iClientH]->m_iMaxEK >= 1000) &&  (m_pClientList[iClientH]->m_iRating >= 200 ))
		{	iRangoAttacker = 10;
		}
	

	if (m_pClientList[iAttackerH]->m_iPKCount == 0) {
		// ��청��쨩 ��창��쨘 쨩챌쨋첨��횑 PK쨍챕 쩐횈쨔짬쨌짹 쨉챈��횑 쩐첩쨈횢.
	
		// 횊챰쨩첵��횣��횉 쩍횄쨔횓, 짹챈쨉책쩔첩 쩔짤쨘횓쩔징 쨉청쨋처 횈첨쨩처��횑 쨈횧쨋처횁첩쨈횢. 
		
		// 짹챈쨉책쩔첩��횑 쩐횈쨈횕쨔횉쨌횓 쩍횄쨔횓. (쩔짤횉횪��횣��횉 째챈쩔챙쩔징쨈횂 ��횑 횉횚쩌철째징 횊짙횄창쨉횉횁철 쩐횎��쨍쨔횉쨌횓)
		// v2.15 ��청��쨩 횁횞쩔쨈��쨩쨋짠 횈챵짹횛째챈횉챔횆징쨍짝 쩐챵짹창��짠횉횠 
		iRewardExp = (iDice(3, (3*iGetExpLevel(m_pClientList[iClientH]->m_iExp))) + iGetExpLevel(m_pClientList[iClientH]->m_iExp))/ 3 ;

		if (m_bIsCrusadeMode == TRUE || m_bIsHeldenianMode == TRUE) {
			// 횇짤쨌챌쩌쩌��횑쨉책 쨍챨쨉책쨋처쨍챕 째챈횉챔횆징��횉 (1/3)*3��쨩 쨍횛��첬 횁횜째챠 쨀짧쨍횙횁철쨈횂 6쨔챔쨌횓 ��체��챦 째첩횉책쨉쨉쩔징 쨈짤��청 
			m_pClientList[iAttackerH]->m_iExp += (iRewardExp/3)*4;
			m_pClientList[iAttackerH]->m_iWarContribution += (iRewardExp - (iRewardExp/3))*12;

			m_pClientList[iAttackerH]->m_iConstructionPoint += (m_pClientList[iClientH]->m_iLevel+ m_pClientList[iClientH]->m_iMajesticLevel) / 2;

			// 쩐횏쨌횁횁횠쨈횢.
			SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iAttackerH]->m_iConstructionPoint, m_pClientList[iAttackerH]->m_iWarContribution, NULL, NULL);

		}
		else {
			// ��횕쨔횦 쨍챨쨉책.
			m_pClientList[iAttackerH]->m_iExp += iRewardExp;
		}

		// 횊챰쨩첵��횣��횉 쨌쨔쨘짠��횑 80��횑쨩처��횑째챠
		if (memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iClientH]->m_cMapName, 10) != 0) {
			// 횊챰쨩첵��횣째징 횁횞��쨘 째첨��횑 ��횣쩍횇��횉 쨍쨋��쨩��횑 쩐횈쨈횕쨋처쨍챕 EK쨌횓 ��횓횁짚 
			m_pClientList[iAttackerH]->m_iEnemyKillCount += m_iEnemyKillAdjust * iRangoAttacker;

			m_pClientList[iAttackerH]->m_iDeaths++; // MORLA 2.2 - Le suma una muerte al pj

			// Wanted System
			switch (m_pClientList[iAttackerH]->m_iWantedLevel) {
			case 0:
				if (m_pClientList[iAttackerH]->m_iDeaths == 5) {
					m_pClientList[iAttackerH]->m_iWantedLevel++;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are now Wanted! (Level 1).");
					SetWantedFlag(iAttackerH, DEF_OWNERTYPE_PLAYER, 1);
				}
				break;
			case 1:
				if (m_pClientList[iAttackerH]->m_iDeaths == 10) {
					m_pClientList[iAttackerH]->m_iWantedLevel++;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are now Wanted! (Level 2).");
				}
				break;
			case 2:
				if (m_pClientList[iAttackerH]->m_iDeaths == 15) {
					m_pClientList[iAttackerH]->m_iWantedLevel++;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are now Wanted! (Level 3).");
				}
				break;
			case 3:
				if (m_pClientList[iAttackerH]->m_iDeaths == 20) {
					m_pClientList[iAttackerH]->m_iWantedLevel++;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are now Wanted! (Level 4).");
				}
				break;
			case 4:
				if (m_pClientList[iAttackerH]->m_iDeaths == 25) {
					m_pClientList[iAttackerH]->m_iWantedLevel++;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are now Wanted! (Level 5).");
				}
				break;
			}
			class CItem* pItem;
			int iItemID = -1, iEraseReq;
			char cData[256], *cp;
			DWORD* dwp;
			short* sp;
			WORD* wp;
			if (m_pClientList[iClientH]->m_iWantedLevel > 0) {
				switch (m_pClientList[iClientH]->m_iWantedLevel) {
				case 1:
					m_pClientList[iAttackerH]->m_iEnemyKillCount += 2;
					SetItemCount(iAttackerH, "Gold", dwGetItemCount(iAttackerH, "Gold") + 1000);
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You received (2) EKs and 1000g for killing a Wanted Lv. 1.");
					break;
				case 2:
					m_pClientList[iAttackerH]->m_iEnemyKillCount += 4;
					SetItemCount(iAttackerH, "Gold", dwGetItemCount(iAttackerH, "Gold") + 2500);
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You received (4) EKs and 2500g for killing a Wanted Lv. 2.");
					break;
				case 3:
					m_pClientList[iAttackerH]->m_iEnemyKillCount += 6;
					SetItemCount(iAttackerH, "Gold", dwGetItemCount(iAttackerH, "Gold") + 5000);
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You received (6) EKs and 5000g for killing a Wanted Lv. 3.");
					break;
				case 4:
					m_pClientList[iAttackerH]->m_iEnemyKillCount += 8;
					SetItemCount(iAttackerH, "Gold", dwGetItemCount(iAttackerH, "Gold") + 7500);
					iItemID = 650;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You received (8) EKs, 1 Zem and 7500g for killing a Wanted Lv. 4.");
					break;
				case 5:
					m_pClientList[iAttackerH]->m_iEnemyKillCount += 10;
					SetItemCount(iAttackerH, "Gold", dwGetItemCount(iAttackerH, "Gold") + 10000);
					iItemID = 650;
					SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You received (10) EKs, 1 Zem and 10000g for killing a Wanted Lv. 5.");
					break;
				}
				SetWantedFlag(iClientH, DEF_OWNERTYPE_PLAYER, 0);
				m_pClientList[iClientH]->m_iDeaths = 0;
				m_pClientList[iClientH]->m_iWantedLevel = 0;
				m_pClientList[iClientH]->m_iEnemyKillCount -= 15;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You are no longer Wanted and were punished with -15 EK.");
				if (iItemID != -1) {
					pItem = new class CItem;
					if (_bInitItemAttr(pItem, iItemID) == FALSE) {
						delete pItem;
						return;
					}
					ZeroMemory(cData, sizeof(cData));
					if (_bAddClientItemList(iAttackerH, pItem, &iEraseReq) == TRUE) {
						dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
						*dwp = MSGID_NOTIFY;
						wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
						*wp = DEF_NOTIFY_ITEMOBTAINED;
						cp = (char*)(cData + DEF_INDEX2_MSGTYPE + 2);
						*cp = 1;
						cp++;
						memcpy(cp, pItem->m_cName, 20);
						cp += 20;
						dwp = (DWORD*)cp;
						*dwp = pItem->m_dwCount;
						cp += 4;
						*cp = pItem->m_cItemType;
						cp++;
						*cp = pItem->m_cEquipPos;
						cp++;
						*cp = (char)0;
						cp++;
						sp = (short*)cp;
						*sp = pItem->m_sLevelLimit;
						cp += 2;
						*cp = pItem->m_cGenderLimit;
						cp++;
						wp = (WORD*)cp;
						*wp = pItem->m_wCurLifeSpan;
						cp += 2;
						wp = (WORD*)cp;
						*wp = pItem->m_wWeight;
						cp += 2;
						sp = (short*)cp;
						*sp = pItem->m_sSprite;
						cp += 2;
						sp = (short*)cp;
						*sp = pItem->m_sSpriteFrame;
						cp += 2;
						*cp = pItem->m_cItemColor;
						cp++;
						*cp = (char)pItem->m_sItemSpecEffectValue2;
						cp++;
						dwp = (DWORD*)cp;
						*dwp = pItem->m_dwAttribute;
						cp += 4;
						*cp = (char)pItem->m_sItemSpecEffectValue3;
						cp++;
						iCalcTotalWeight(iAttackerH);
						if (iEraseReq == 1) {
							delete pItem;
							pItem = NULL;
						}
						m_pClientList[iAttackerH]->m_pXSock->iSendMsg(cData, 54);
					}
					else delete pItem;
				}
			}
			SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_ENEMYKILLS, m_pClientList[iAttackerH]->m_iEnemyKillCount, NULL, NULL, NULL);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ENEMYKILLS, m_pClientList[iClientH]->m_iEnemyKillCount, NULL, NULL, NULL);

			if (m_pClientList[iAttackerH]->m_iEnemyKillCount > m_pClientList[iAttackerH]->m_iMaxEK)
			{
				m_pClientList[iAttackerH]->m_iMaxEK = m_pClientList[iAttackerH]->m_iEnemyKillCount;
			}
		}

		// 횈첨쨩처짹횦 쨈짤��청 
		m_pClientList[iAttackerH]->m_iRewardGold += iDice(1, (iGetExpLevel(m_pClientList[iClientH]->m_iExp)));

		if (m_pClientList[iAttackerH]->m_iRewardGold < 0)
			m_pClientList[iAttackerH]->m_iRewardGold = 0;		

		// ��청��쨩 ��창쩐횘쨈횢쨈횂 쨍횧쩍횄횁철 쨘쨍쨀쩔 
		SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_ENEMYKILLREWARD, iClientH, NULL, NULL, NULL);

		if (bCheckLimitedUser(iAttackerH) == FALSE) {
			// 횄쩌횉챔횈횉 쨩챌쩔챘��횣 횁짝횉횗쩔징 횉횠쨈챌쨉횉횁철 쩐횎��쨍쨍챕 째챈횉챔횆징째징 쩔횄쨋첬쨈횢쨈횂 횇챘쨘쨍쨍짝 횉횗쨈횢.
			SendNotifyMsg(NULL, iAttackerH, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);
		}
		// 쨌쨔쨘짠��횑 쩔횄쨋첬쨈횂횁철쨍짝 째횏쨩챌횉횗쨈횢.
		bCheckLevelUp(iAttackerH);

	}
}

// 05/22/2004 - Hypnotoad - register in pk log
void CGame::ApplyCombatKilledPenalty(int iClientH, int cPenaltyLevel, BOOL bIsSAattacked)
{  
	unsigned long iExp;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;

	// Crusade
	if (m_bIsCrusadeMode == TRUE || m_bIsHeldenianMode == TRUE) {
		// 횇짤쨌챌쩌쩌��횑쨉책 쨍챨쨉책��횓 째챈쩔챙 ��체��챦횁횩쩔징 횁횞쩐챤쨉쨉 쩐횈쨔짬쨌짹 횈채쨀횓횈쩌째징 쩐첩쨈횢.
		// PKcount쨍쨍 째짢쩌횘 
		if (m_pClientList[iClientH]->m_iPKCount > 0) {
			m_pClientList[iClientH]->m_iPKCount--;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PKPENALTY, NULL, NULL, NULL, NULL);	
			// v2.15 
			_bPKLog(DEF_PKLOG_REDUCECRIMINAL,NULL,iClientH,NULL) ;

		}
		
	}
	else {
		// PKcount 째짢쩌횘 
		if (m_pClientList[iClientH]->m_iPKCount > 0) {
			m_pClientList[iClientH]->m_iPKCount--;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PKPENALTY, NULL, NULL, NULL, NULL);	
			// v2.15
			_bPKLog(DEF_PKLOG_REDUCECRIMINAL,NULL,iClientH,NULL) ;
		}

		// 횉횄쨌쨔��횑쩐챤쨌횓쨘횓횇횒��횉 째첩째횦��쨩 쨔횧째챠 ��체��챦횁횩 쨩챌쨍횁횉횩쨈횢.
		iExp = iDice(1, (5*cPenaltyLevel*(m_pClientList[iClientH]->m_iLevel+ m_pClientList[iClientH]->m_iMajesticLevel)));

		// 횁횩쨍쨀��횓 째챈쩔챙 횁횞쩐첬��쨩 쨋짠 쨋쨀쩐챤횁철쨈횂 째챈횉챔횆징쨈횂 1/3
		if (m_pClientList[iClientH]->m_bIsNeutral == TRUE) iExp = iExp / 3;

		m_pClientList[iClientH]->m_iExp -= iExp;
		if (m_pClientList[iClientH]->m_iExp < 0) m_pClientList[iClientH]->m_iExp = 0;

		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);

		// v1.41 횁횩쨍쨀��쨘 쩐횈��횑횇횤��횑 쨋쨀쩐챤횁철횁철 쩐횎쨈횂쨈횢.
		if (m_pClientList[iClientH]->m_bIsNeutral != TRUE) {
			_PenaltyItemDrop(iClientH, cPenaltyLevel, bIsSAattacked);
		}
	}
}

int CGame::iAddDynamicObjectList(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, DWORD dwLastTime, int iV1)
{
 int i;
 short sPreType;
 DWORD dwTime, dwRegisterTime;

	m_pMapList[cMapIndex]->bGetDynamicObject(sX, sY, &sPreType, &dwRegisterTime);
	if (sPreType != NULL) return NULL;

	switch (sType) {	
	case DEF_DYNAMICOBJECT_FIRE3:
	case DEF_DYNAMICOBJECT_FIRE:
		if (m_pMapList[cMapIndex]->bGetIsMoveAllowedTile(sX, sY) == FALSE)
			return NULL;
		if (dwLastTime != NULL)  {
			switch (m_pMapList[cMapIndex]->m_cWhetherStatus) {
			case 1:	dwLastTime = dwLastTime - (dwLastTime / 2);       break;
			case 2:	dwLastTime = (dwLastTime / 2) - (dwLastTime / 3); break;
			case 3:	dwLastTime = (dwLastTime / 3) - (dwLastTime / 4); break;
			// SNOOPY: Added reduced duration if snow whether
			case 4:	dwLastTime = dwLastTime - (dwLastTime / 6);       break;
			case 5:	dwLastTime = dwLastTime - (dwLastTime / 4);		  break;
			case 6:	dwLastTime = dwLastTime - (dwLastTime / 2);		  break;
			default:break;
			}
			if (dwLastTime == NULL) dwLastTime = 1000;
		}
		break;

	// SNOOPY: Increased duration if snow whether
	case DEF_DYNAMICOBJECT_ICESTORM:
		if (dwLastTime != NULL)  {
			switch (m_pMapList[cMapIndex]->m_cWhetherStatus) {
			case 1:	break;
			// Reduced duration if heavy rain
			case 2:	dwLastTime = dwLastTime  - (dwLastTime / 8); break;
			case 3:	dwLastTime = dwLastTime  - (dwLastTime / 4); break;
			// Increased duration if snow whether
			case 4:	dwLastTime = dwLastTime + (dwLastTime / 2);       break;
			case 5:	dwLastTime = dwLastTime *2;		  break;
			case 6:	dwLastTime = dwLastTime *4;		  break;
			default:break;
			}
			if (dwLastTime == NULL) dwLastTime = 1000;
		}
		break;
	
	case DEF_DYNAMICOBJECT_FISHOBJECT:
	case DEF_DYNAMICOBJECT_FISH:
		if (m_pMapList[cMapIndex]->bGetIsWater(sX, sY) == FALSE)
			return NULL;
		break;

	case DEF_DYNAMICOBJECT_ARESDENFLAG1:
	case DEF_DYNAMICOBJECT_ELVINEFLAG1:
	case DEF_DYNAMICOBJECT_MINERAL1:
	case DEF_DYNAMICOBJECT_MINERAL2:
		if (m_pMapList[cMapIndex]->bGetMoveable(sX, sY) == FALSE)
			return NULL;
		m_pMapList[cMapIndex]->SetTempMoveAllowedFlag(sX, sY, FALSE);
		break;

	case DEF_DYNAMICOBJECT_FIRE2: // centu - burning crusade structures
		if (dwLastTime != NULL) {
			switch (m_pMapList[cMapIndex]->m_cWhetherStatus) {
			case 1:	dwLastTime = dwLastTime - (dwLastTime / 2);       break;
			case 2:	dwLastTime = (dwLastTime / 2) - (dwLastTime / 3); break;
			case 3:	dwLastTime = (dwLastTime / 3) - (dwLastTime / 4); break;
				// SNOOPY: Added reduced duration if snow whether
			case 4:	dwLastTime = dwLastTime - (dwLastTime / 6);       break;
			case 5:	dwLastTime = dwLastTime - (dwLastTime / 4);		  break;
			case 6:	dwLastTime = dwLastTime - (dwLastTime / 2);		  break;
			default:break;
			}
			if (dwLastTime == NULL) dwLastTime = 1000;
		}
		break;

	}
   	
	for (i = 1; i < DEF_MAXDYNAMICOBJECTS; i++) 
	if (m_pDynamicObjectList[i] == NULL) {
		dwTime = timeGetTime();
		
		if (dwLastTime != NULL) 
			dwLastTime += (iDice(1,4)*1000);

		m_pDynamicObjectList[i] = new class CDynamicObject(sOwner, cOwnerType, sType, cMapIndex, sX, sY, dwTime, dwLastTime, iV1);
		m_pMapList[cMapIndex]->SetDynamicObject(i, sType, sX, sY, dwTime);
		SendEventToNearClient_TypeB(MSGID_DYNAMICOBJECT, DEF_MSGTYPE_CONFIRM, cMapIndex, sX, sY, sType, i, NULL);

		return i;
	}
	return NULL;
}

void CGame::CheckDynamicObjectList()
{
 int i;
 DWORD dwTime = timeGetTime(), dwRegisterTime;
 short sType;

	// 쨀짱쩐쩐 횊쩔째첬쩔징 쨉청쨍짜 쨉쩔��청 째쨈횄쩌��횉 횁철쩌횙쩍횄째짙 쨈횥횄횪��쨩 째챔쨩챗횉횗쨈횢. 
	for (i = 1; i < DEF_MAXDYNAMICOBJECTS; i++)  
	{	if ( (m_pDynamicObjectList[i] != NULL) && (m_pDynamicObjectList[i]->m_dwLastTime != NULL) ) 
		{	switch (m_pDynamicObjectList[i]->m_sType) {
			case DEF_DYNAMICOBJECT_FIRE3:
			case DEF_DYNAMICOBJECT_FIRE2: // centu - burning crusade structures
			case DEF_DYNAMICOBJECT_FIRE:
				switch (m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus) {
				case 0: 
					break;
				case 1: 
				case 2:
				case 3:
					m_pDynamicObjectList[i]->m_dwLastTime = m_pDynamicObjectList[i]->m_dwLastTime - (m_pDynamicObjectList[i]->m_dwLastTime/10) * m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus;
					break;
				case 4: 	// SNOOPY: Added snow whether
				case 5:
				case 6:
					m_pDynamicObjectList[i]->m_dwLastTime = m_pDynamicObjectList[i]->m_dwLastTime - (m_pDynamicObjectList[i]->m_dwLastTime/20) * m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus;
					break;
				}
				break;
	}	}	}

	// 쩍횄째짙��횑 쨍쨍쨌찼쨉횊 째쨈횄쩌쨍짝 횁쩐쨌찼쩍횄횇짼쨈횢. 횁철쩌횙쩍횄째짙��횑 NULL��횑쨍챕 쩔쨉쩔첩횊첨 쨀짼쩐횈��횜쨈횂 쨉쩔��청 째쨈횄쩌��횑쨈횢.
	for (i = 1; i < DEF_MAXDYNAMICOBJECTS; i++) { 
		if ( (m_pDynamicObjectList[i] != NULL) && (m_pDynamicObjectList[i]->m_dwLastTime != NULL) && 
			 ((dwTime - m_pDynamicObjectList[i]->m_dwRegisterTime) >= m_pDynamicObjectList[i]->m_dwLastTime) ) {
		
			// 횁철쩌횙쩍횄째짙��횑 째챈째첬횉횗 쨉쩔��청 째쨈횄쩌쨍짝 횄짙쩐횘쨈횢.
			m_pMapList[ m_pDynamicObjectList[i]->m_cMapIndex ]->bGetDynamicObject( m_pDynamicObjectList[i]->m_sX, m_pDynamicObjectList[i]->m_sY, &sType, &dwRegisterTime );
			// 쨉챤쨌횕쩍횄째짙��횑 ��횕횆징횉횗쨈횢쨍챕 째쨈횄쩌째징 쨩챌쨋처횁첩쨈횢쨈횂 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쨩횁횪쩐횩 횉횗쨈횢.
			
			if (dwRegisterTime == m_pDynamicObjectList[i]->m_dwRegisterTime) {
				SendEventToNearClient_TypeB(MSGID_DYNAMICOBJECT, DEF_MSGTYPE_REJECT, m_pDynamicObjectList[i]->m_cMapIndex, m_pDynamicObjectList[i]->m_sX, m_pDynamicObjectList[i]->m_sY, m_pDynamicObjectList[i]->m_sType, i, NULL);
				// 쨍횎쩔징쩌짯 쨩챔횁짝횉횗쨈횢.
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->SetDynamicObject(NULL, NULL, m_pDynamicObjectList[i]->m_sX, m_pDynamicObjectList[i]->m_sY, dwTime);
			}

			switch (sType) {
			case DEF_DYNAMICOBJECT_FISHOBJECT:
			case DEF_DYNAMICOBJECT_FISH:
				// 쨔째째챠짹창 쩔��쨘챗횁짠횈짰째징 쨩챌쨋처횁쨀��쨍쨔횉쨌횓 횄쨀쨍짰횉횗쨈횢.
				bDeleteFish(m_pDynamicObjectList[i]->m_sOwner, 2); // 쩍횄째짙��횑 횁철쨀짧쩌짯 쨔째째챠짹창째징 쨩챌쨋처횁첩쨈횢.
				break;
			}
	
			// 쨍짰쩍쨘횈짰쨍짝 쨩챔횁짝횉횗쨈횢.
			delete m_pDynamicObjectList[i];
			m_pDynamicObjectList[i] = NULL;
		}
	}
}

void CGame::RequestFullObjectData(int iClientH, char *pData)
{
 DWORD * dwp;
 WORD  * wp, wObjectID;
 char  * cp, cData[100];
 short * sp, sX, sY;
 int     sTemp, sTemp2;
 int   * ip, iRet;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;

	wp = (WORD *)(pData + DEF_INDEX2_MSGTYPE);
	wObjectID = *wp;
	
	ZeroMemory(cData, sizeof(cData));
	dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_EVENT_MOTION;
	wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_OBJECTSTOP;
	
	cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);

	if (wObjectID < 10000) {
		// 횆쨀쨍짱횇횒��횉 횁짚쨘쨍쨍짝 쩔첩횉횗쨈횢. 
		// ��횩쨍첩쨉횊 ��횓쨉짝쩍쨘째짧��횑째횇쨀짧 횁쨍��챌횉횕횁철 쩐횎쨈횂 횉횄쨌쨔��횑쩐챤쨋처쨍챕 쨔짬쩍횄.
		if ( (wObjectID == 0) || (wObjectID >= DEF_MAXCLIENTS) ) return;
		if (m_pClientList[wObjectID] == NULL) return;
		
		wp  = (WORD *)cp;
		*wp = wObjectID;			// ObjectID
		cp += 2;
		sp  = (short *)cp;
		sX  = m_pClientList[wObjectID]->m_sX;
		*sp = sX;
		cp += 2;
		sp  = (short *)cp;
		sY  = m_pClientList[wObjectID]->m_sY;
		*sp = sY;
		cp += 2;
		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sType;
		cp += 2;
		*cp = m_pClientList[wObjectID]->m_cDir;
		cp++;
		memcpy(cp, m_pClientList[wObjectID]->m_cCharName, 10);
		cp += 10;
		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr1;
		cp += 2;
		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr2;
		cp += 2;
		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr3;
		cp += 2;
		sp  = (short *)cp;
		*sp = m_pClientList[wObjectID]->m_sAppr4;
		cp += 2;
		//v1.4 ApprColor
		ip = (int *)cp;
		*ip = m_pClientList[wObjectID]->m_iApprColor;
		cp += 4;
		
		ip  = (int *)cp;
		
		// sStatus��횉 쨩처��짠 4쨘챰횈짰째징 FOE 째체째챔쨍짝 쨀짧횇쨍쨀쩍쨈횢. 
		sTemp = m_pClientList[wObjectID]->m_iStatus;
		sTemp = 0x0FFFFFFF & sTemp;// 쨩처��짠 4쨘챰횈짰 횇짭쨍짰쩐챤
		sTemp2 = iGetPlayerABSStatus(wObjectID, iClientH); 
		sTemp  = (sTemp | (sTemp2 << 28));//Original : 12
		
		*ip = sTemp;
		
		cp += 4;//Original 2
		
		if (m_pClientList[wObjectID]->m_bIsKilled == TRUE) // v1.4
			 *cp = 1;
		else *cp = 0;
		cp++;

		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 41); // v1.4
	}
	else {
		// NPC��횉 횁짚쨘쨍쨍짝 쩔첩횉횗쨈횢.
		// ��횩쨍첩쨉횊 ��횓쨉짝쩍쨘 째짧��횑째횇쨀짧 쨩첵쩌쨘쨉횉횁철 쩐횎��쨘 NPC쨋처쨍챕 쨔짬쩍횄 
		if ( ((wObjectID - 10000) == 0) || ((wObjectID - 10000) >= DEF_MAXNPCS) ) return;
		if (m_pNpcList[wObjectID - 10000] == NULL) return;
		
		wp  = (WORD *)cp;
		*wp = wObjectID;			
		cp += 2;

		wObjectID -= 10000;

		sp  = (short *)cp;
		sX  = m_pNpcList[wObjectID]->m_sX;
		*sp = sX;
		cp += 2;
		sp  = (short *)cp;
		sY  = m_pNpcList[wObjectID]->m_sY;
		*sp = sY;
		cp += 2;
		sp  = (short *)cp;
		*sp = m_pNpcList[wObjectID]->m_sType;
		cp += 2;
		*cp = m_pNpcList[wObjectID]->m_cDir;
		cp++;
		memcpy(cp, m_pNpcList[wObjectID]->m_cName, 5);
		cp += 5;
		sp  = (short *)cp;
		*sp = m_pNpcList[wObjectID]->m_sAppr2;
		cp += 2;
		
		ip  = (int *)cp;
	
		sTemp = m_pNpcList[wObjectID]->m_iStatus;
		sTemp = 0x0FFFFFFF & sTemp;// 쨩처��짠 4쨘챰횈짰 횇짭쨍짰쩐챤
		
		sTemp2 = iGetNpcRelationship(wObjectID, iClientH);
		sTemp  = (sTemp | (sTemp2 << 28));//Original : 12	
		*ip = sTemp;
		
		cp += 4;//Original 2

		if (m_pNpcList[wObjectID]->m_bIsKilled == TRUE) // v1.4
			 *cp = 1;
		else *cp = 0;
		cp++;

		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 27); // v1.4 //Original : 25
	}

	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩐쨋짠 쩔징쨌짱째징 쨔횩쨩첵횉횩쨈횢쨍챕 횁짝째횇횉횗쨈횢.
		DeleteClient(iClientH, TRUE, TRUE);
		break;
	}
}

void CGame::Effect_Damage_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3, BOOL bExp, int iAttr)
{
 int iPartyID, iDamage, iSideCondition, iIndex, iRemainLife, iTemp, iMaxSuperAttack, iRepDamage;
 char cAttackerSide, cDamageMoveDir;
 DWORD dwTime;
 register double dTmp1, dTmp2, dTmp3;
 short sAtkX, sAtkY, sTgtX, sTgtY, dX, dY, sItemIndex;
 unsigned long iExp;

 	if (cAttackerType == DEF_OWNERTYPE_PLAYER)
		if (m_pClientList[sAttackerH] == NULL) return;

	if (cAttackerType == DEF_OWNERTYPE_NPC)
		if (m_pNpcList[sAttackerH] == NULL) return;

	if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) 
		&& (m_bIsHeldenianMode == TRUE)				// No spell work before war has begun
		&& (m_bHeldenianWarInitiated == FALSE)
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex] != 0) 
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsHeldenianMap == 1)) return; 
	
	dwTime = timeGetTime();
	iDamage = (iDice(sV1, sV2) + sV3);
	if (iDamage <= 0) iDamage = 0;

	switch (cAttackerType) {
	case DEF_OWNERTYPE_PLAYER:	
		//LifeX Fix Admin Hit NPC
		if ((m_pClientList[sAttackerH]->m_iAdminUserLevel == 2) || (m_pClientList[sAttackerH]->m_iAdminUserLevel == 3))
		{
			SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_IPACCOUNTINFO, NULL, NULL, NULL, "You cannot do any damage as a GM.");
			return;
		}

		if (m_pClientList[sAttackerH]->m_cHeroArmourBonus == 2) iDamage += 4;
		if ((m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND] == -1) || (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] == -1)) {
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
			if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 861 || m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 862) {
					float damageTemp = (float)iDamage;
					damageTemp *= 1.5f; // O el valor con punto flotante que ustedes dispongan... JustThink
					iDamage = (int)damageTemp;
				}
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 863 || m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 864) {
					if (m_pClientList[sAttackerH]->m_iRating > 0) {
						iRepDamage = m_pClientList[sAttackerH]->m_iRating/10;
						iDamage += iRepDamage;
					}
					if (cTargetType == DEF_OWNERTYPE_PLAYER) {
						if (m_pClientList[sTargetH] != NULL) {
							if (m_pClientList[sTargetH]->m_iRating <= 0) {
								iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/10);
								iDamage += iRepDamage;
							}
						}
					}
				}
			}
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
			if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 859) { // NecklaceOfKloness  
					if (cTargetType == DEF_OWNERTYPE_PLAYER) {
						if (m_pClientList[sTargetH] != NULL) {
							iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/20);
							iDamage += iRepDamage;
						}
					}
				}
			}
		}

		if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[sAttackerH]->m_bIsPlayerCivil == TRUE) && (cTargetType == DEF_OWNERTYPE_PLAYER)) return;

		dTmp1 = (double)iDamage;
		if ((m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag) <= 0)
			 dTmp2 = 1.0f;
		else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag);	
		dTmp2 = dTmp2 / 3.3f;
		dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
		iDamage = (int)(dTmp3 +0.5f);

		iDamage += m_pClientList[sAttackerH]->m_iAddMagicalDamage;
		if (iDamage <= 0) iDamage = 0;

		if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) 
			iDamage += iDamage/3;

		if (bCheckHeldenianMap(sAttackerH, DEF_OWNERTYPE_PLAYER) == 1) {
			iDamage += iDamage/3;
		}

		if ((cTargetType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == TRUE) && (m_pClientList[sAttackerH]->m_iCrusadeDuty == 1)) {
			if (m_pClientList[sAttackerH]->m_iLevel <= 80) {
				iDamage += (iDamage * 7) / 10;
			}
			else if (m_pClientList[sAttackerH]->m_iLevel > 80 && m_pClientList[sAttackerH]->m_iLevel <= 100) {
				iDamage += iDamage / 2;
			}
			else if (m_pClientList[sAttackerH]->m_iLevel > 100) {
				iDamage += iDamage / 3;
			}
		}
		
		cAttackerSide = m_pClientList[sAttackerH]->m_cSide;
		sAtkX = m_pClientList[sAttackerH]->m_sX;
		sAtkY = m_pClientList[sAttackerH]->m_sY;
		iPartyID = m_pClientList[sAttackerH]->m_iPartyID;
		break;

	case DEF_OWNERTYPE_NPC:
		cAttackerSide = m_pNpcList[sAttackerH]->m_cSide;
		sAtkX = m_pNpcList[sAttackerH]->m_sX;
		sAtkY = m_pNpcList[sAttackerH]->m_sY;
		break;
	}

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:

		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsInitComplete == FALSE) return;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;

		if ((m_pClientList[sTargetH]->m_iStatus & 0x400000) != 0) return;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == FALSE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsPlayerCivil == TRUE)) return;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsNeutral == TRUE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsOwnLocation == TRUE)) return;
		
		if ((dwTime - m_pClientList[sTargetH]->m_dwTime) > DEF_RAGPROTECTIONTIME) return;
		if ((m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->m_bIsAttackEnabled == FALSE) && (m_pClientList[sTargetH]->m_iAdminUserLevel == 0)) return;
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH]->m_bIsNeutral == TRUE) && (m_pClientList[sTargetH]->m_iPKCount == 0)) return;
		if ((m_pClientList[sTargetH]->m_iPartyID != NULL) && (iPartyID == m_pClientList[sTargetH]->m_iPartyID)) return;
		m_pClientList[sTargetH]->m_dwLogoutHackCheck = dwTime;

		if (cAttackerType == DEF_OWNERTYPE_PLAYER) { 
			if (m_pClientList[sAttackerH]->m_bIsSafeAttackMode == TRUE) {
				iSideCondition = iGetPlayerRelationship(sAttackerH, sTargetH);
				if ((iSideCondition != 7) && (iSideCondition != 2) && (iSideCondition != 6)) {
					if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
						if (m_pClientList[sAttackerH]->m_iGuildGUID == m_pClientList[sTargetH]->m_iGuildGUID) {
							return;
						}
					}
					return;
				}
			}
			if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->iGetAttribute(m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY, 0x00000005) != 0) return;
		}

		ClearSkillUsingStatus(sTargetH);
		
		switch (iAttr) {
		case 1:
			if (m_pClientList[sTargetH]->m_iAddAbsEarth != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsEarth;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 2:
			if (m_pClientList[sTargetH]->m_iAddAbsAir != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsAir;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 3:
			if (m_pClientList[sTargetH]->m_iAddAbsFire != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsFire;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 4:
			if (m_pClientList[sTargetH]->m_iAddAbsWater != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsWater;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		default: break;
		}

		iIndex = m_pClientList[sTargetH]->m_iMagicDamageSaveItemIndex;
		if ((iIndex != -1) && (iIndex >= 0) && (iIndex < DEF_MAXITEMS)) {
			
			switch (m_pClientList[sTargetH]->m_pItemList[iIndex]->m_sIDnum) {
			case 335:
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.2f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
						
			case 337:
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.1f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
			}
			if (iDamage <= 0) iDamage = 0;
			
			iRemainLife = m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan;			
			if (iRemainLife <= iDamage) {
				ItemDepleteHandler(sTargetH, iIndex, TRUE, TRUE);
			}
			else {
				m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan -= iDamage;
			}
		}

		if (m_pClientList[sTargetH]->m_iAddAbsMD != 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsMD;
			dTmp3 = (dTmp2/100.0f)*dTmp1;
			iDamage = iDamage - (int)dTmp3;
		}

		if (cTargetType == DEF_OWNERTYPE_PLAYER) {
			iDamage -= (iDice(1, m_pClientList[sTargetH]->m_iVit/10) - 1);
			if (iDamage <= 0) iDamage = 0;
		}
	
		if ((m_pClientList[sTargetH]->m_bIsLuckyEffect == TRUE) && 
			(iDice(1,10) == 5) && (m_pClientList[sTargetH]->m_iHP <= iDamage)) {
			iDamage = m_pClientList[sTargetH]->m_iHP - 1;
		}

		if (m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2)
			iDamage = iDamage / 2;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsSpecialAbilityEnabled == TRUE)) {
			switch (m_pClientList[sTargetH]->m_iSpecialAbilityType) {
			case 51:
			case 52:
				return;
			}
		}
		
		m_pClientList[sTargetH]->m_iHP -= iDamage;
		if (m_pClientList[sTargetH]->m_iHP <= 0) {
			ClientKilledHandler(sTargetH, sAttackerH, cAttackerType, iDamage);	
		}
		else {
			if (iDamage > 0) {
				if (m_pClientList[sTargetH]->m_iAddTransMana > 0) {
					dTmp1 = (double)m_pClientList[sTargetH]->m_iAddTransMana;
					dTmp2 = (double)iDamage;
					dTmp3 = (dTmp1/100.0f)*dTmp2 +1.0f;

					iTemp = iGetMaxMP(sTargetH);
					m_pClientList[sTargetH]->m_iMP += (int)dTmp3;
					if (m_pClientList[sTargetH]->m_iMP > iTemp) m_pClientList[sTargetH]->m_iMP = iTemp;
				}

				if (m_pClientList[sTargetH]->m_iAddChargeCritical > 0) {
					if (iDice(1,100) <= (m_pClientList[sTargetH]->m_iAddChargeCritical)) {
						iMaxSuperAttack = ((m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel) / 10);
						if (m_pClientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[sTargetH]->m_iSuperAttackLeft++;
						SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
					}
				}

				m_pClientList[sTargetH]->m_dwRecentAttackTime = dwTime;
				
				SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
				SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);

				if (m_pClientList[sTargetH]->m_bSkillUsingStatus[19] != TRUE) {
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->ClearOwner(0, sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
				}
			
				if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);							
					m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
				}
			}
		}

		sTgtX = m_pClientList[sTargetH]->m_sX;
		sTgtY = m_pClientList[sTargetH]->m_sY;
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == NULL) return;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) return;
		if ((m_bIsCrusadeMode == TRUE) && (cAttackerSide == m_pNpcList[sTargetH]->m_cSide)) return;
		
		sTgtX = m_pNpcList[sTargetH]->m_sX;
		sTgtY = m_pNpcList[sTargetH]->m_sY;

		switch (m_pNpcList[sTargetH]->m_cActionLimit) {
		case 1:
		case 2:
			return;

		case 4:
			if (sTgtX == sAtkX) {
				if (sTgtY == sAtkY) return;
				else if (sTgtY > sAtkY) cDamageMoveDir = 5;
				else if (sTgtY < sAtkY) cDamageMoveDir = 1;
			}
			else if (sTgtX > sAtkX) {
				if (sTgtY == sAtkY)     cDamageMoveDir = 3;
				else if (sTgtY > sAtkY) cDamageMoveDir = 4;
				else if (sTgtY < sAtkY) cDamageMoveDir = 2;
			}
			else if (sTgtX < sAtkX) {
				if (sTgtY == sAtkY)     cDamageMoveDir = 7;
				else if (sTgtY > sAtkY) cDamageMoveDir = 6;
				else if (sTgtY < sAtkY) cDamageMoveDir = 8;							
			}

			dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
			dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

			if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {
				cDamageMoveDir = iDice(1,8);
				dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
				dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];			
				if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) return;
			}
						
			m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->ClearOwner(5, sTargetH, DEF_OWNERTYPE_NPC, m_pNpcList[sTargetH]->m_sX, m_pNpcList[sTargetH]->m_sY);
			m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_NPC, dX, dY);
			m_pNpcList[sTargetH]->m_sX   = dX;
			m_pNpcList[sTargetH]->m_sY   = dY;
			m_pNpcList[sTargetH]->m_cDir = cDamageMoveDir;
					
			SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
				
			dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
			dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];
					
			if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {
				cDamageMoveDir = iDice(1,8);
				dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
				dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];
						
				if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) return;
			}
						
			m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->ClearOwner(5, sTargetH, DEF_OWNERTYPE_NPC, m_pNpcList[sTargetH]->m_sX, m_pNpcList[sTargetH]->m_sY);
			m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_NPC, dX, dY);
			m_pNpcList[sTargetH]->m_sX   = dX;
			m_pNpcList[sTargetH]->m_sY   = dY;
			m_pNpcList[sTargetH]->m_cDir = cDamageMoveDir;
					
			SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);

			return;
		}

		if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
			switch (m_pNpcList[sTargetH]->m_sType) {
			case 40:
			case 41:
				if ((m_pClientList[sAttackerH]->m_cSide == 0) || (m_pNpcList[sTargetH]->m_cSide == m_pClientList[sAttackerH]->m_cSide)) return;
				break;
			}
		}

		switch (m_pNpcList[sTargetH]->m_sType) {
				case 67: // McGaffin
				case 68: // Perry
				case 69: // Devlin
				return;
		}
		
		if (m_pNpcList[sTargetH]->m_iAbsDamage > 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)(m_pNpcList[sTargetH]->m_iAbsDamage)/100.0f;
			dTmp3 = dTmp1 * dTmp2;
			dTmp2 = dTmp1 - dTmp3;
			iDamage = (int)dTmp2;
			if (iDamage < 0) iDamage = 1;
		}

		if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2)
			iDamage = iDamage / 2;
		
		m_pNpcList[sTargetH]->m_iHP -= iDamage;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) {
			NpcKilledHandler(sAttackerH, cAttackerType, sTargetH, iDamage);
		}
		else {
			switch (cAttackerType) {
			case DEF_OWNERTYPE_PLAYER:
				if ((m_pNpcList[sTargetH]->m_sType != 21) && (m_pNpcList[sTargetH]->m_sType != 55) && (m_pNpcList[sTargetH]->m_sType != 56)
					&& (m_pNpcList[sTargetH]->m_cSide == cAttackerSide)) return ;
				break;

			case DEF_OWNERTYPE_NPC:
				if (m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide) return;
				break;
			}
			
			SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);
						
			if ((iDice(1,3) == 2) && (m_pNpcList[sTargetH]->m_cActionLimit == 0)) {
				if ((cAttackerType == DEF_OWNERTYPE_NPC) && 
					(m_pNpcList[sAttackerH]->m_sType == m_pNpcList[sTargetH]->m_sType) &&
					(m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide)) return;

				m_pNpcList[sTargetH]->m_cBehavior          = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[sTargetH]->m_sBehaviorTurnCount = 0;		
				m_pNpcList[sTargetH]->m_iTargetIndex = sAttackerH;
				m_pNpcList[sTargetH]->m_cTargetType  = cAttackerType;

				m_pNpcList[sTargetH]->m_dwTime = dwTime;

				if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_HOLDOBJECT);
				}

				if ( (m_pNpcList[sTargetH]->m_iNoDieRemainExp > 0) && (m_pNpcList[sTargetH]->m_bIsSummoned != TRUE) && 
					 (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) ) {
					if (m_pNpcList[sTargetH]->m_iNoDieRemainExp > iDamage) {
						iExp = iDamage;

						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0;
								break;
							default: break;
							}
						}
											
						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp, TRUE);
						else GetExp(sAttackerH, (iExp/2), TRUE);
						m_pNpcList[sTargetH]->m_iNoDieRemainExp -= iDamage;
					}
					else {
						iExp = m_pNpcList[sTargetH]->m_iNoDieRemainExp;

						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0;
								break;
							default: break;
							}
						}
						
						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp, TRUE);
						else GetExp(sAttackerH, (iExp/2), TRUE);
						m_pNpcList[sTargetH]->m_iNoDieRemainExp = 0;
					}
				}
			}
		}
		break;
	}
}

void CGame::Effect_Damage_Spot_Type2(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, BOOL bExp, int iAttr)
{
 int iPartyID, iDamage, iSideCondition, iIndex, iRemainLife, iTemp, iMaxSuperAttack, iRepDamage;
 char cAttackerSide, cDamageMoveDir, cDamageMinimum;
 DWORD dwTime;
 register double dTmp1, dTmp2, dTmp3;
 short sTgtX, sTgtY, sItemIndex;
 unsigned long iExp;

	if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] == NULL)) return;
	if ((cAttackerType == DEF_OWNERTYPE_NPC) && (m_pNpcList[sAttackerH] == NULL)) return;
	
	if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) 
		&& (m_bIsHeldenianMode == TRUE)				// No spell work before war has begun
		&& (m_bHeldenianWarInitiated == FALSE)
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex] != 0) 
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsHeldenianMap == 1)) return; 
	
	dwTime = timeGetTime();
	sTgtX = 0;
	sTgtY = 0;
	iDamage = (iDice(sV1, sV2) + sV3);
	if (iDamage <= 0) iDamage = 0;

	switch (cAttackerType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sAttackerH]->m_cHeroArmourBonus == 2) iDamage += 4;
		if ((m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND] == -1) || (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] == -1)) {
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
			if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 861 || m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 862) {
					float damageTemp = (float)iDamage;
					damageTemp *= 1.5f; // O el valor con punto flotante que ustedes dispongan... JustThink
					iDamage = (int)damageTemp;
				}
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 863 || m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 864) {
					if (m_pClientList[sAttackerH]->m_iRating > 0) {
						iRepDamage = m_pClientList[sAttackerH]->m_iRating/10;
						iDamage += iRepDamage;
					}
					if (cTargetType == DEF_OWNERTYPE_PLAYER) {
						if (m_pClientList[sTargetH] != NULL) {
							if (m_pClientList[sTargetH]->m_iRating <= 0) {
								iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/10);
								iDamage += iRepDamage;
							}
						}
					}
				}
			}
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
			if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
				if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 859) { // NecklaceOfKloness  
					if (cTargetType == DEF_OWNERTYPE_PLAYER) {
						if (m_pClientList[sTargetH] != NULL) {
							iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/20);
							iDamage += iRepDamage;
						}
					}
				}
			}
		}

		if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[sAttackerH]->m_bIsPlayerCivil == TRUE) && (cTargetType == DEF_OWNERTYPE_PLAYER)) return;

		dTmp1 = (double)iDamage;
		if ((m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag) <= 0)
			 dTmp2 = 1.0f;
		else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag);	
		dTmp2 = dTmp2 / 3.3f;
		dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
		iDamage = (int)(dTmp3 +0.5f);
		if (iDamage <= 0) iDamage = 0;
		// order switched with above
		iDamage += m_pClientList[sAttackerH]->m_iAddMagicalDamage;

		if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) 
			iDamage += iDamage/3;

		if (bCheckHeldenianMap(sAttackerH, DEF_OWNERTYPE_PLAYER) == 1) {
			iDamage += iDamage/3;
		}

		if ((cTargetType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == TRUE) && (m_pClientList[sAttackerH]->m_iCrusadeDuty == 1)) {
			if (m_pClientList[sAttackerH]->m_iLevel <= 80) {
				iDamage += (iDamage * 7) / 10;
			}
			else if (m_pClientList[sAttackerH]->m_iLevel > 80 && m_pClientList[sAttackerH]->m_iLevel <= 100) {
				iDamage += iDamage / 2;
			}
			else if (m_pClientList[sAttackerH]->m_iLevel > 100) {
				iDamage += iDamage / 3;
			}
		}
		
		cAttackerSide = m_pClientList[sAttackerH]->m_cSide;
		iPartyID = m_pClientList[sAttackerH]->m_iPartyID;
		break;

	case DEF_OWNERTYPE_NPC:
		cAttackerSide = m_pNpcList[sAttackerH]->m_cSide;
		break;
	}

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:

		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsInitComplete == FALSE) return;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;
		if ((dwTime - m_pClientList[sTargetH]->m_dwTime) > DEF_RAGPROTECTIONTIME) return;
		if (m_pClientList[sTargetH]->m_cMapIndex == -1) return;
		if ((m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->m_bIsAttackEnabled == FALSE) && (m_pClientList[sTargetH]->m_iAdminUserLevel == 0)) return;
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsNeutral == TRUE) && (m_pClientList[sTargetH]->m_iPKCount == 0)) return;

		if ((m_pClientList[sTargetH]->m_iStatus & 0x400000) != 0) return;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == FALSE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsPlayerCivil == TRUE)) return;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsNeutral == TRUE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsOwnLocation == TRUE)) return;
		
		if ((m_pClientList[sTargetH]->m_iPartyID != NULL) && (iPartyID == m_pClientList[sTargetH]->m_iPartyID)) return;
		m_pClientList[sTargetH]->m_dwLogoutHackCheck = dwTime;

		if (cAttackerType == DEF_OWNERTYPE_PLAYER) { 
			if (m_pClientList[sAttackerH]->m_bIsSafeAttackMode == TRUE) {
				iSideCondition = iGetPlayerRelationship(sAttackerH, sTargetH);
				if ((iSideCondition != 7) && (iSideCondition != 2) && (iSideCondition != 6)) {
					if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
						if (m_pClientList[sAttackerH]->m_iGuildGUID == m_pClientList[sTargetH]->m_iGuildGUID) {
							return;
						}
					}
					return;
				}
			}
			if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->iGetAttribute(m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY, 0x00000005) != 0) return;
		}

		ClearSkillUsingStatus(sTargetH);
		
		switch (iAttr) {
		case 1:
			if (m_pClientList[sTargetH]->m_iAddAbsEarth != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsEarth;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 2:
			if (m_pClientList[sTargetH]->m_iAddAbsAir != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsAir;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 3:
			if (m_pClientList[sTargetH]->m_iAddAbsFire != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsFire;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 4:
			if (m_pClientList[sTargetH]->m_iAddAbsWater != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsWater;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		default: break;
		}

		iIndex = m_pClientList[sTargetH]->m_iMagicDamageSaveItemIndex;
		if ((iIndex != -1) && (iIndex >= 0) && (iIndex < DEF_MAXITEMS)) {
			
			switch (m_pClientList[sTargetH]->m_pItemList[iIndex]->m_sIDnum) {
			case 335:
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.2f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
						
			case 337:
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.1f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
			}
			if (iDamage <= 0) iDamage = 0;
			
			iRemainLife = m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan;			
			if (iRemainLife <= iDamage) {
				ItemDepleteHandler(sTargetH, iIndex, TRUE, TRUE);
			}
			else {
				m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan -= iDamage;
			}
		}

		if (m_pClientList[sTargetH]->m_iAddAbsMD != 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsMD;
			dTmp3 = (dTmp2/100.0f)*dTmp1;
			iDamage = iDamage - (int)dTmp3;
		}

		if (cTargetType == DEF_OWNERTYPE_PLAYER) {
			iDamage -= (iDice(1, m_pClientList[sTargetH]->m_iVit/10) - 1);
			if (iDamage <= 0) iDamage = 0;
		}
	
		if (m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2)
			iDamage = iDamage / 2;
		
		if (m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 5) break;

		if ((m_pClientList[sTargetH]->m_bIsLuckyEffect == TRUE) && 
			(iDice(1,10) == 5) && (m_pClientList[sTargetH]->m_iHP <= iDamage)) {
			iDamage = m_pClientList[sTargetH]->m_iHP - 1;
		}

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsSpecialAbilityEnabled == TRUE)) {
			switch (m_pClientList[sTargetH]->m_iSpecialAbilityType) {
			case 51:
			case 52:
				return;
			}
		}
		
		m_pClientList[sTargetH]->m_iHP -= iDamage;
		if (m_pClientList[sTargetH]->m_iHP <= 0) {
			ClientKilledHandler(sTargetH, sAttackerH, cAttackerType, iDamage);	
		}
		else {
			if (iDamage > 0) {
				if (m_pClientList[sTargetH]->m_iAddTransMana > 0) {
					dTmp1 = (double)m_pClientList[sTargetH]->m_iAddTransMana;
					dTmp2 = (double)iDamage;
					dTmp3 = (dTmp1/100.0f)*dTmp2 +1.0f;

					iTemp = iGetMaxMP(sTargetH);
					m_pClientList[sTargetH]->m_iMP += (int)dTmp3;
					if (m_pClientList[sTargetH]->m_iMP > iTemp) m_pClientList[sTargetH]->m_iMP = iTemp;
				}

				if (m_pClientList[sTargetH]->m_iAddChargeCritical > 0) {
					if (iDice(1,100) <= (m_pClientList[sTargetH]->m_iAddChargeCritical)) {
						iMaxSuperAttack = ((m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel) / 10);
						if (m_pClientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[sTargetH]->m_iSuperAttackLeft++;
						SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
					}
				}
				
				if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE)) {
					cDamageMinimum = 80;
				}
				else {
					cDamageMinimum = 50;
				}

				if (iDamage >= cDamageMinimum) {
					sTgtX = m_pClientList[sTargetH]->m_sX;
					sTgtY = m_pClientList[sTargetH]->m_sY;
					if (sTgtX == sAtkX) {
						if (sTgtY == sAtkY) return;
							else if (sTgtY > sAtkY) cDamageMoveDir = 5;
							else if (sTgtY < sAtkY) cDamageMoveDir = 1;
						}
						else if (sTgtX > sAtkX) {
							if (sTgtY == sAtkY)     cDamageMoveDir = 3;
							else if (sTgtY > sAtkY) cDamageMoveDir = 4;
							else if (sTgtY < sAtkY) cDamageMoveDir = 2;
						}
					else if (sTgtX < sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 7;
						else if (sTgtY > sAtkY) cDamageMoveDir = 6;
						else if (sTgtY < sAtkY) cDamageMoveDir = 8;							
					}
					m_pClientList[sTargetH]->m_iLastDamage = iDamage;
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_DAMAGEMOVE, cDamageMoveDir, iDamage, NULL, NULL);
				}

				SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
				SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);

				if (m_pClientList[sTargetH]->m_bSkillUsingStatus[19] != TRUE) {
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->ClearOwner(0, sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
				}
			
				if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);							
					m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
				}
			}
		}
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == NULL) return;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) return;
		if ((m_bIsCrusadeMode == TRUE) && (cAttackerSide == m_pNpcList[sTargetH]->m_cSide)) return;
		
		switch (m_pNpcList[sTargetH]->m_cActionLimit) {
		case 1:
		case 2:
		case 4:
		case 6:
			return;

		case 3:
		case 5:
			if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
				switch (m_pNpcList[sTargetH]->m_sType) {
				case 40:
				case 41:
					if ((m_pClientList[sAttackerH]->m_cSide == 0) || (m_pNpcList[sTargetH]->m_cSide == m_pClientList[sAttackerH]->m_cSide)) return;
					break;
				}
			}
		}
	
		if (m_pNpcList[sTargetH]->m_iAbsDamage > 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)(m_pNpcList[sTargetH]->m_iAbsDamage)/100.0f;
			dTmp3 = dTmp1 * dTmp2;
			dTmp2 = dTmp1 - dTmp3;
			iDamage = (int)dTmp2;
			if (iDamage < 0) iDamage = 1;
		}

		if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2)
			iDamage = iDamage / 2;
		
		m_pNpcList[sTargetH]->m_iHP -= iDamage;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) {
			NpcKilledHandler(sAttackerH, cAttackerType, sTargetH, iDamage);
		}
		else {
			switch (cAttackerType) {
			case DEF_OWNERTYPE_PLAYER:
				if ((m_pNpcList[sTargetH]->m_sType != 21) && (m_pNpcList[sTargetH]->m_sType != 55) && (m_pNpcList[sTargetH]->m_sType != 56)
					&& (m_pNpcList[sTargetH]->m_cSide == cAttackerSide)) return ;
				break;

			case DEF_OWNERTYPE_NPC:
				if (m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide) return;
				break;
			}
			
			SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);		
			if ((iDice(1,3) == 2) && (m_pNpcList[sTargetH]->m_cActionLimit == 0)) {
				if ((cAttackerType == DEF_OWNERTYPE_NPC) && 
					(m_pNpcList[sAttackerH]->m_sType == m_pNpcList[sTargetH]->m_sType) &&
					(m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide)) return;

				m_pNpcList[sTargetH]->m_cBehavior          = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[sTargetH]->m_sBehaviorTurnCount = 0;		
				m_pNpcList[sTargetH]->m_iTargetIndex = sAttackerH;
				m_pNpcList[sTargetH]->m_cTargetType  = cAttackerType;
				m_pNpcList[sTargetH]->m_dwTime = dwTime;

				if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_HOLDOBJECT);
				}

				if ((m_pNpcList[sTargetH]->m_iNoDieRemainExp > 0) && (m_pNpcList[sTargetH]->m_bIsSummoned != TRUE) && (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL)) {
					if (m_pNpcList[sTargetH]->m_iNoDieRemainExp > iDamage) {
						iExp = iDamage;

						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0;
								break;
							default: break;
							}
						}
											
						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp, TRUE);
						else GetExp(sAttackerH, (iExp/2), TRUE);
						m_pNpcList[sTargetH]->m_iNoDieRemainExp -= iDamage;
					}
					else {
						iExp = m_pNpcList[sTargetH]->m_iNoDieRemainExp;

						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0;
								break;
							default: break;
							}
						}
						
						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp, TRUE);
						else GetExp(sAttackerH, (iExp/2), TRUE);
						m_pNpcList[sTargetH]->m_iNoDieRemainExp = 0;
					}
				}
			}
		}
		break;
	}
}

void CGame::Effect_Damage_Spot_DamageMove(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, BOOL bExp, int iAttr)
{
 int iDamage, iSideCondition, iIndex, iRemainLife, iTemp, iMaxSuperAttack;
 DWORD dwTime, wWeaponType;
 char cAttackerSide, cDamageMoveDir;
 register double dTmp1, dTmp2, dTmp3;
 int iPartyID, iMoveDamage;
 short sTgtX, sTgtY;

	if (cAttackerType == DEF_OWNERTYPE_PLAYER)
		if (m_pClientList[sAttackerH] == NULL) return;

	if (cAttackerType == DEF_OWNERTYPE_NPC)
		if (m_pNpcList[sAttackerH] == NULL) return;

	if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) 
		&& (m_bIsHeldenianMode == TRUE)				// No spell work before war has begun
		&& (m_bHeldenianWarInitiated == FALSE)
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex] != 0) 
		&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsHeldenianMap == 1)) return; 

	dwTime = timeGetTime();
	sTgtX = 0;
	sTgtY = 0;
	
	// 해당 타켓에게 대미지를 먹인다. 
	iDamage = (iDice(sV1, sV2) + sV3) ;
	if (iDamage <= 0) iDamage = 0;

	iPartyID = 0;

	// 공격자가 플레이어라면 Mag에 따른 보너스 대미지를 가산 
	switch (cAttackerType) {
	case DEF_OWNERTYPE_PLAYER:

		dTmp1 = (double)iDamage;
		if ((m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag) <= 0)
			 dTmp2 = 1.0f;
		else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag);
			
		dTmp2 = dTmp2 / 3.3f;
		dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
		iDamage = (int)(dTmp3 +0.5f);
		if (iDamage <= 0) iDamage = 0;

		// v1.432 2001 4 7 13 7
		iDamage += m_pClientList[sAttackerH]->m_iAddMagicalDamage;

		// v1.44 사투장이면 대미지 1.33배 
		if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) 
			iDamage += iDamage/3;

		// Crusade : 전면전 모드일때 대인 공격력 1.33배 
		if ((cTargetType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == TRUE) && (m_pClientList[sAttackerH]->m_iCrusadeDuty == 1))
		{
			// v2.15 저랩의 경우는 데미지가 증가한다. 1.7 배 
			if (m_pClientList[sAttackerH]->m_iLevel <= 80)
			{
				iDamage += (iDamage * 7) / 10;
			} // v2.15 저랩의 경우는 데미지가 증가한다. 1.5 배 
			else if (m_pClientList[sAttackerH]->m_iLevel > 80 && m_pClientList[sAttackerH]->m_iLevel <= 100)
			{
				iDamage += iDamage / 2;
			}
			else if (m_pClientList[sAttackerH]->m_iLevel > 100)
			{
				iDamage += iDamage / 3;
			}
		}

		if (m_pClientList[sAttackerH]->m_cHeroArmourBonus == 2) {
			iDamage += 4;
		}

		wWeaponType = ((m_pClientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
		if (wWeaponType == 34) {
			iDamage += iDamage/3;
		}

		if (bCheckHeldenianMap(sAttackerH, DEF_OWNERTYPE_PLAYER) == 1) {
			iDamage += iDamage/3;
		}

		cAttackerSide = m_pClientList[sAttackerH]->m_cSide;
		
		iPartyID = m_pClientList[sAttackerH]->m_iPartyID;
		break;

	case DEF_OWNERTYPE_NPC:
		cAttackerSide = m_pNpcList[sAttackerH]->m_cSide;
		break;
	}

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		// 공격 대상이 존재하지 않으면 리턴 
		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsInitComplete == FALSE) return;
		// 이미 죽어 있다면 처리 안함.
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;
		// 랙으로 인해 보호를 받아야 한다면 
		if ((dwTime - m_pClientList[sTargetH]->m_dwTime) > DEF_RAGPROTECTIONTIME) return;
		// 공격자가 위치한 맵이 공격 불가능 맵이라면 
		// v2.03 서버 다운되어서 고침 
		if (m_pClientList[sTargetH]->m_cMapIndex == -1) return;
		if ((m_pMapList[ m_pClientList[sTargetH]->m_cMapIndex ]->m_bIsAttackEnabled == FALSE) && (m_pClientList[sTargetH]->m_iAdminUserLevel == 0)) return;
		// v1.41 공격자가 중립이면 대인 공격이 불가능하다. 
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH]->m_bIsNeutral == TRUE) && (m_pClientList[sTargetH]->m_iPKCount == 0)) return;

		// v2.172 같은편끼리는 마을에서 공격당하지 않는다. 범죄자와 NPC는 예외 중립도 공격 않되게 
		if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[sTargetH]->m_iPKCount == 0) && (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsPlayerCivil == TRUE)) return ;
		if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[sTargetH]->m_iPKCount == 0) && (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH]->m_bIsPlayerCivil == TRUE)) return ;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsNeutral == TRUE) && (m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsPlayerCivil == TRUE)) return;

		// 01-12-17 같은 파티원이면 공격 불가 
		if ((m_pClientList[sTargetH]->m_iPartyID != NULL) && (iPartyID == m_pClientList[sTargetH]->m_iPartyID)) return;
		m_pClientList[sTargetH]->m_dwLogoutHackCheck = dwTime;

		// 만약 공격자가 플레이어이고 공격자가 안전 공격 모드라면 공격의 의미가 없다. 
		if (cAttackerType == DEF_OWNERTYPE_PLAYER) { 
			
			if (m_pClientList[sAttackerH]->m_bIsSafeAttackMode == TRUE) {
				iSideCondition = iGetPlayerRelationship(sAttackerH, sTargetH);
				if ((iSideCondition != 7) && (iSideCondition != 2) && (iSideCondition != 6)) {
					// 아무 효과 없음. 마나 소비량이 줄었으므로 
				
					// 같은 편이지만 만약 사투장 내에서 편이 같다면 공격 처리를 해야한다.
					if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
						if (m_pClientList[sAttackerH]->m_iGuildGUID == m_pClientList[sTargetH]->m_iGuildGUID) {
							// 사투장 내에서 다른 길드다. 공격이 가능하다. 
							return;
						}
					}
					return;
				}
			}

			// 마법 보호 혹은 안전 영역이라면 공격 성공 못함 
			if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->iGetAttribute(m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY, 0x00000005) != 0) return;
		}
		
		// 스킬의 사용상태를 모두 무효화 한다.
		ClearSkillUsingStatus(sTargetH);

		// v1.432 속성별 대미지 감소 
		switch (iAttr) {
		case 1:
			if (m_pClientList[sTargetH]->m_iAddAbsEarth != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsEarth;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 2:
			if (m_pClientList[sTargetH]->m_iAddAbsAir != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsAir;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 3:
			if (m_pClientList[sTargetH]->m_iAddAbsFire != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsFire;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		case 4:
			if (m_pClientList[sTargetH]->m_iAddAbsWater != 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsWater;
				dTmp3 = (dTmp2/100.0f)*dTmp1;
				iDamage = iDamage - (int)(dTmp3);
				if (iDamage < 0) iDamage = 0;
			}
			break;

		default: break;
		}
		
		iIndex = m_pClientList[sTargetH]->m_iMagicDamageSaveItemIndex;
		if ((iIndex != -1) && (iIndex >= 0) && (iIndex < DEF_MAXITEMS)) {
			// 마법 대미지 절감 효과를 가진 아이템이다.
			
			// 아이템의 종류에 따라 대미지를 줄인다. 
			switch (m_pClientList[sTargetH]->m_pItemList[iIndex]->m_sIDnum) {
			case 335: // 에머랄드 반지 20%
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.2f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
						
			case 337: // 루비 반지 10%
				dTmp1 = (double)iDamage;
				dTmp2 = dTmp1 * 0.1f;
				dTmp3 = dTmp1 - dTmp2;
				iDamage = (int)(dTmp3 +0.5f);
				break;
			}
			if (iDamage <= 0) iDamage = 0;
			
			iRemainLife = m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan;			
			if (iRemainLife <= iDamage) {
				// 마법 데미지 절감 아이템이 부서진다. 
				ItemDepleteHandler(sTargetH, iIndex, TRUE, TRUE);
			}
			else {
				// 마법 데미지 절감 아이템의 수명만 줄인다. 
				m_pClientList[sTargetH]->m_pItemList[iIndex]->m_wCurLifeSpan -= iDamage;
			}
		}

		// v1.42 추가된 고정 마법 대미지 절감
		if (m_pClientList[sTargetH]->m_iAddAbsMD != 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)m_pClientList[sTargetH]->m_iAddAbsMD;
			dTmp3 = (dTmp2/100.0f)*dTmp1;
			iDamage = iDamage - (int)dTmp3;
		}

		// v1.4 VIT에 따른 대미지 감소 
		if (cTargetType == DEF_OWNERTYPE_PLAYER) {
			iDamage -= (iDice(1, m_pClientList[sTargetH]->m_iVit/10) - 1);
			if (iDamage <= 0) iDamage = 0;
		}

		// 만약 마법 보호중이라면 대미지는 1/2 
		if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_PROTECT ] == 2)
			iDamage = iDamage / 2;
	
		if ((m_pClientList[sTargetH]->m_bIsLuckyEffect == TRUE) && 
			(iDice(1,10) == 5) && (m_pClientList[sTargetH]->m_iHP <= iDamage)) {
			// 행운효과로 죽음을 모면한다.
			iDamage = m_pClientList[sTargetH]->m_iHP - 1;
		}

		// v1.432 특수 능력 중 모든 대미지를 막는 효과가 활성화 된 경우 대미지를 입지 않는다.
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsSpecialAbilityEnabled == TRUE)) {
			switch (m_pClientList[sTargetH]->m_iSpecialAbilityType) {
			case 51:
			case 52:
				// 
				return;
			}
		}

		m_pClientList[sTargetH]->m_iHP -= iDamage;
		if (m_pClientList[sTargetH]->m_iHP <= 0) {
			// 플레이어가 사망했다.
			ClientKilledHandler(sTargetH, sAttackerH, cAttackerType, iDamage);	
		}
		else {
			if (iDamage > 0) {
				// v2.04 타격을 받았는데 마나 변환 특성치가 있었다면 
				if (m_pClientList[sTargetH]->m_iAddTransMana > 0) {
					dTmp1 = (double)m_pClientList[sTargetH]->m_iAddTransMana;
					dTmp2 = (double)iDamage;
					dTmp3 = (dTmp1/100.0f)*dTmp2 +1.0f;

					// 최대 마나치 
					iTemp = iGetMaxMP(sTargetH);
					m_pClientList[sTargetH]->m_iMP += (int)dTmp3;
					if (m_pClientList[sTargetH]->m_iMP > iTemp) m_pClientList[sTargetH]->m_iMP = iTemp;
				}

				// v2.04 타격을 받았는데 필살 충전의 특성치가 있었다면 
				if (m_pClientList[sTargetH]->m_iAddChargeCritical > 0) {
					// 확률 계산에 따라서 필살기가 충전된다.
					if (iDice(1,100) <= (m_pClientList[sTargetH]->m_iAddChargeCritical)) {
						iMaxSuperAttack = ((m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel) / 10);
						if (m_pClientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[sTargetH]->m_iSuperAttackLeft++;
						// v1.12 서버와 클라이언트 간에 카운트가 일치하지 않는 경우가 있을 수 있으므로 가감에 상관없이 보낸다.
						SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
					}
				}

				// v1.44 사투장이면 대미지 80이상일때 밀린다.
				if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE)) 
					 iMoveDamage = 80;
				else iMoveDamage = 50;

				if (iDamage >= iMoveDamage) {
					// 대미지가 50이상이면 튕긴다.
			
					sTgtX = m_pClientList[sTargetH]->m_sX;
					sTgtY = m_pClientList[sTargetH]->m_sY;

					if (sTgtX == sAtkX) {
						if (sTgtY == sAtkY)     goto EDSD_SKIPDAMAGEMOVE;
						else if (sTgtY > sAtkY) cDamageMoveDir = 5;
						else if (sTgtY < sAtkY) cDamageMoveDir = 1;
					}
					else if (sTgtX > sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 3;
						else if (sTgtY > sAtkY) cDamageMoveDir = 4;
						else if (sTgtY < sAtkY) cDamageMoveDir = 2;
					}
					else if (sTgtX < sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 7;
						else if (sTgtY > sAtkY) cDamageMoveDir = 6;
						else if (sTgtY < sAtkY) cDamageMoveDir = 8;							
					}

					// v1.44 밀려날때 대미지를 입력한다.
					m_pClientList[sTargetH]->m_iLastDamage = iDamage;
					// 받은 대미지를 통보한다. <- HP를 그대로 알린다.
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
					// 튕겨 나가라는 메시지 입력 	
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_DAMAGEMOVE, cDamageMoveDir, iDamage, NULL, NULL);
				}
				else {
EDSD_SKIPDAMAGEMOVE:;
					// 받은 대미지를 통보한다. <- HP를 그대로 알린다.
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
					// 충격을 받았다면 충격동작 전송 
					SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);
				}

				// v1.4 죽은척하고 있는 경우는 Owner 위치를 옮긴다. 
				if (m_pClientList[sTargetH]->m_bSkillUsingStatus[19] != TRUE) {
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->ClearOwner(0, sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
					m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_PLAYER, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
				}
			
				if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					// Hold-Person 되어 있었던 상태라면 풀린다. 마법공격 패럴라이즈 된 것도 풀린다.
					// 1: Hold-Person 
					// 2: Paralize
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
							
					m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
				}
			}
		}
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == NULL) return;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) return;
		if ((m_bIsCrusadeMode == TRUE) && (cAttackerSide == m_pNpcList[sTargetH]->m_cSide)) return;
		
		switch (m_pNpcList[sTargetH]->m_cActionLimit) {
		case 1:
		case 2:
		case 4:
			return;
		}
		
		// 전쟁용 구조물중 그랜드 매직 제네레이터, 에너지 실드 제네레이터는 아군이나 중립의 공격에 대미지를 입지 않는다.
		if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
			switch (m_pNpcList[sTargetH]->m_sType) {
			case 40:
			case 41:
				if ((m_pClientList[sAttackerH]->m_cSide == 0) || (m_pNpcList[sTargetH]->m_cSide == m_pClientList[sAttackerH]->m_cSide)) return;
				break;
			}
		}

		switch (m_pNpcList[sTargetH]->m_sType) {
			case 67: // McGaffin
			case 68: // Perry
			case 69: // Devlin
				iDamage = 0;
			break;
		}
		
		// 몬스터가 마법 대미지 흡수률이 있다면(AbsDamage가 0보다 크다) 원래 마법 대미지를 감소시킨다.
		if (m_pNpcList[sTargetH]->m_iAbsDamage > 0) {
			dTmp1 = (double)iDamage;
			dTmp2 = (double)(m_pNpcList[sTargetH]->m_iAbsDamage)/100.0f;
			dTmp3 = dTmp1 * dTmp2;
			dTmp2 = dTmp1 - dTmp3;
			iDamage = (int)dTmp2;
			if (iDamage < 0) iDamage = 1;
		}

		// 만약 마법 보호중이라면 대미지는 1/2 
		if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_PROTECT ] == 2)
			iDamage = iDamage / 2;
		
		m_pNpcList[sTargetH]->m_iHP -= iDamage;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) {
			// NPC가 사망했다.
			NpcKilledHandler(sAttackerH, cAttackerType, sTargetH, iDamage);
		}
		else {
			// 공격당했지만 살아있다. 반격한다.

			// 편이 같으면 반격하지 않는다.
			switch (cAttackerType) {
			case DEF_OWNERTYPE_PLAYER:
				// v2.15 경비는 같은 편도 반격한다.			
				if ((m_pNpcList[sTargetH]->m_sType != 21) && (m_pNpcList[sTargetH]->m_sType != 55) && (m_pNpcList[sTargetH]->m_sType != 56)
					&& (m_pNpcList[sTargetH]->m_cSide == cAttackerSide)) return;
				break;

			case DEF_OWNERTYPE_NPC:
				if (m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide) return;
				break;
			}
			
			// 충격을 받았다면 충격동작 전송
			SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);
			
			if ((iDice(1,3) == 2) && (m_pNpcList[sTargetH]->m_cActionLimit == 0)) {

				// 동족이고 편이 같으면 반격하지 않는다.
				if ((cAttackerType == DEF_OWNERTYPE_NPC) && 
					(m_pNpcList[sAttackerH]->m_sType == m_pNpcList[sTargetH]->m_sType) &&
					(m_pNpcList[sAttackerH]->m_cSide == m_pNpcList[sTargetH]->m_cSide)) return;

				// ActionLimit가 1이면 반격을 하지 않는다. 오직 움직일수만 있으니.
				m_pNpcList[sTargetH]->m_cBehavior          = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[sTargetH]->m_sBehaviorTurnCount = 0;		
				m_pNpcList[sTargetH]->m_iTargetIndex = sAttackerH;
				m_pNpcList[sTargetH]->m_cTargetType  = cAttackerType;
				
				// 여기서 표효 동작같은것을 위한 메시지 발송.

				// Damage를 입은 충격으로 인한 지연효과.
				m_pNpcList[sTargetH]->m_dwTime = dwTime;

				if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
					// Hold 되어 있었던 상태라면 풀린다. 	
					m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_HOLDOBJECT);
				}

				//Crusade
				unsigned long iExp;

				// NPC에 대한 공격이 성공했으므로 공격자가 플레이어라면 입힌 대미지 만큼의 경험치를 공격자에게 준다. 
				if ( (m_pNpcList[sTargetH]->m_iNoDieRemainExp > 0) && (m_pNpcList[sTargetH]->m_bIsSummoned != TRUE) && 
					 (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) ) {
					// ExpStock을 올린다. 단 소환몹인 경우 경험치를 올리지 않는다.
					if (m_pNpcList[sTargetH]->m_iNoDieRemainExp > iDamage) {
						// Crusade
						iExp = iDamage;

						//v2.03 918 경험치 증가 
						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}
						
						// v2.17 2002-8-6 공격자의 레벨이 100 이상이면 토끼나 고양이를 잡을때 경험치가 올라가지 않는다.
						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0 ;
							break ;
							default: break;
							}
						}

						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp); 
						else GetExp(sAttackerH, (iExp/2)); 
						m_pNpcList[sTargetH]->m_iNoDieRemainExp -= iDamage;
					}
					else {
						// Crusade
						iExp = m_pNpcList[sTargetH]->m_iNoDieRemainExp;

						//v2.03 918 경험치 증가 
						if (m_pClientList[sAttackerH]->m_iAddExp > 0) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						// v2.17 2002-8-6 공격자의 레벨이 100 이상이면 토끼나 고양이를 잡을때 경험치가 올라가지 않는다.
						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0 ;
							break ;
							default: break;
							}
						}


						if (bExp == TRUE) 
							 GetExp(sAttackerH, iExp); 
						else GetExp(sAttackerH, (iExp/2)); 
						m_pNpcList[sTargetH]->m_iNoDieRemainExp = 0;
					}
				}
			}
		}
		break;
	}
}

void CGame::Effect_HpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3)
{
 int iHP, iMaxHP;
 DWORD dwTime = timeGetTime();

	if (cAttackerType == DEF_OWNERTYPE_PLAYER)
		if (m_pClientList[sAttackerH] == NULL) return;

	iHP = iDice(sV1, sV2) + sV3;

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;
		iMaxHP = iGetMaxHP(sTargetH);
		if (m_pClientList[sTargetH]->m_iSideEffect_MaxHPdown != 0) 
			iMaxHP = iMaxHP - (iMaxHP/m_pClientList[sTargetH]->m_iSideEffect_MaxHPdown);
		if (m_pClientList[sTargetH]->m_iHP < iMaxHP) {
			m_pClientList[sTargetH]->m_iHP += iHP;
			if (m_pClientList[sTargetH]->m_iHP > iMaxHP) m_pClientList[sTargetH]->m_iHP = iMaxHP;
			if (m_pClientList[sTargetH]->m_iHP <= 0)     m_pClientList[sTargetH]->m_iHP = 1;
			SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
		}
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[sTargetH] == NULL) return;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) return;
		if (m_pNpcList[sTargetH]->m_bIsKilled == TRUE) return;
		iMaxHP = m_pNpcList[sTargetH]->m_iHitDice*4;
		if (m_pNpcList[sTargetH]->m_iHP < iMaxHP) {
			m_pNpcList[sTargetH]->m_iHP += iHP;
			if (m_pNpcList[sTargetH]->m_iHP > iMaxHP) m_pNpcList[sTargetH]->m_iHP = iMaxHP;
			if (m_pNpcList[sTargetH]->m_iHP <= 0)     m_pNpcList[sTargetH]->m_iHP = 1;
		}
		break;
	}
}

void CGame::Effect_SpDown_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3)
{
 int iSP, iMaxSP;
 DWORD dwTime = timeGetTime();

	if (cAttackerType == DEF_OWNERTYPE_PLAYER)
		if (m_pClientList[sAttackerH] == NULL) return;

	// 횉횠쨈챌 횇쨍횆횕��횉 Sp쨍짝 쨀쨩쨍째쨈횢.
	iSP = iDice(sV1, sV2) + sV3;
	
	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;
	
		// New 19/05/2004
		// Is the user having an invincibility slate
		if ((m_pClientList[sTargetH]->m_iStatus & 0x400000) != 0) return;

		iMaxSP = iGetMaxSP(sTargetH);
		if (m_pClientList[sTargetH]->m_iSP > 0) {
			
			//v1.42 
			if (m_pClientList[sTargetH]->m_iTimeLeft_FirmStaminar == 0) {
				m_pClientList[sTargetH]->m_iSP -= iSP;
				if (m_pClientList[sTargetH]->m_iSP < 0) m_pClientList[sTargetH]->m_iSP = 0;
				SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
			}
		}
		break;

	case DEF_OWNERTYPE_NPC:
		// NPC쨈횂 쩍쨘횇횂쨔횑쨀횎 째쨀쨀채��횑 쩐첩쨈횢.
		break;
	}
}


void CGame::Effect_SpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3)
{
 int iSP, iMaxSP;
 DWORD dwTime = timeGetTime();

	if (cAttackerType == DEF_OWNERTYPE_PLAYER)
		if (m_pClientList[sAttackerH] == NULL) return;

	// 횉횠쨈챌 횇쨍횆횕��횉 Sp쨍짝 쩔횄쨍째쨈횢.
	iSP = iDice(sV1, sV2) + sV3;
	
	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[sTargetH] == NULL) return;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return;
	
		iMaxSP = iGetMaxSP(sTargetH);
		if (m_pClientList[sTargetH]->m_iSP < iMaxSP) {
			m_pClientList[sTargetH]->m_iSP += iSP;
			
			if (m_pClientList[sTargetH]->m_iSP > iMaxSP) 
				m_pClientList[sTargetH]->m_iSP = iMaxSP;

			SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL);
		}
		break;

	case DEF_OWNERTYPE_NPC:
		// NPC쨈횂 쩍쨘횇횂쨔횑쨀횎 째쨀쨀채��횑 쩐첩쨈횢.
		break;
	}
}

void CGame::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case VK_F1:
		m_bF1pressed = TRUE;
		break;
	case VK_F4:
		m_bF4pressed = TRUE;
		break;
	case VK_F5:
		m_bF5pressed = TRUE;
		break;
	case VK_F12:
		m_bF12pressed = TRUE;
		break;
	}
}

void CGame::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
 int i;
 
	switch (wParam) {
	case VK_F2:
				
		break;
	
	case VK_F1:
		m_bF1pressed = FALSE;
		break;
	case VK_F4:
		m_bF4pressed = FALSE;
		break;
	case VK_F5:
		m_bF5pressed = FALSE;
		break;
	case VK_F12:
		m_bF12pressed = FALSE;
		break;
	
	case VK_F6:
		if (m_bF1pressed == TRUE) {
			PutLogList("(!) Send server shutdown announcement1...");
			for (i = 1; i < DEF_MAXCLIENTS; i++)
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
				SendNotifyMsg(NULL, i, DEF_NOTIFY_SERVERSHUTDOWN, 1, NULL, NULL, NULL);
			}
		}
		break;

	case VK_F7:
		if (m_bF1pressed == TRUE) {
			PutLogList("(!) Send server shutdown announcement2...");
			for (i = 1; i < DEF_MAXCLIENTS; i++)
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
				SendNotifyMsg(NULL, i, DEF_NOTIFY_SERVERSHUTDOWN, 2, NULL, NULL, NULL);
			}
		}
		break;

	case VK_F9:
		if ((m_bF1pressed == TRUE)) {
			PutLogList("(!!!) Resume Crusade Mode...");
			LocalStartCrusadeMode(NULL);
		}
		break;

	case VK_F11:
		if ((m_bF1pressed == TRUE)) {
			PutLogList("(!!!) ManualEndCrusadeMode: side 0");
			ManualEndCrusadeMode(0);
		}
		break;

	
	case VK_1:
	case VK_4:
		if ((m_bF1pressed == TRUE)) {
			GlobalUpdateConfigs(1);
		}
		break;


	case VK_2:
		if ((m_bF1pressed == TRUE)) {
			GlobalUpdateConfigs(2);
		}
		break;

	case VK_3:
		if ((m_bF1pressed == TRUE)) {
			GlobalUpdateConfigs(3);
		}
		break;


		//Crusade Testcode
	case VK_HOME:
		if ((m_bF1pressed == TRUE)) {
			GlobalStartCrusadeMode();
		}
		break;

	case VK_INSERT:
		_GrandMagicLaunchMsgSend(1, 1);
		MeteorStrikeMsgHandler(1);
		break;

	case VK_DELETE:
		_GrandMagicLaunchMsgSend(1, 2);
		MeteorStrikeMsgHandler(2);
		break;
	}
}

/*********************************************************************************************************************
**  BOOL CGame::bRegisterDelayEvent(int iDelayType, int iEffectType, DWORD dwLastTime, int iTargetH,				**
**									   char cTargetType, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3) **
**  description			:: initiates the delayed event process														**
**  last updated		:: November 20, 2004; 9:30 PM; Hypnotoad													**
**	return value		:: BOOL																						**
**********************************************************************************************************************/
BOOL CGame::bRegisterDelayEvent(int iDelayType, int iEffectType, DWORD dwLastTime, int iTargetH, char cTargetType, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3)
{
 int i;

	for (i = 0; i < DEF_MAXDELAYEVENTS; i++) 
	if (m_pDelayEventList[i] == NULL) {
		m_pDelayEventList[i] = new class CDelayEvent;
		m_pDelayEventList[i]->m_iDelayType	= iDelayType;
		m_pDelayEventList[i]->m_iEffectType = iEffectType;
		m_pDelayEventList[i]->m_cMapIndex	= cMapIndex;
		m_pDelayEventList[i]->m_dX			= dX;
		m_pDelayEventList[i]->m_dY			= dY;
		m_pDelayEventList[i]->m_iTargetH    = iTargetH;
		m_pDelayEventList[i]->m_cTargetType = cTargetType;
		m_pDelayEventList[i]->m_iV1         = iV1;
		m_pDelayEventList[i]->m_iV2         = iV2;
		m_pDelayEventList[i]->m_iV3         = iV3; 
		m_pDelayEventList[i]->m_dwTriggerTime = dwLastTime;
		return TRUE;
	}
	return FALSE;
}

void CGame::DelayEventProcessor()
{
 int i, iSkillNum, iResult;
 DWORD dwTime = timeGetTime();
 int iTemp;

	for (i = 0; i < DEF_MAXDELAYEVENTS; i++) 
	if ((m_pDelayEventList[i] != NULL) && (m_pDelayEventList[i]->m_dwTriggerTime < dwTime)) {

		// ��횑쨘짜횈짰째징 쨉쩔��횤횉횘 쩍횄째짙��횑 쨉횈쨈횢. 쨉쩔��횤횊횆 쨩챔횁짝쨉횊쨈횢.
		switch (m_pDelayEventList[i]->m_iDelayType) {

		case DEF_DELAYEVENTTYPE_TAMING_SKILL: // Taming
			switch (m_pDelayEventList[i]->m_cTargetType) {
			case DEF_OWNERTYPE_PLAYER:				
				if (m_pClientList[m_pDelayEventList[i]->m_iTargetH] == NULL) break;
				// If not the right Taming usage exit
				if (m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bSkillUsingStatus[22] == FALSE) break;
				if (m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iSkillUsingTimeID[22] != m_pDelayEventList[i]->m_iV2) break;
				_TamingHandler(m_pDelayEventList[i]->m_iTargetH
								, 22
								, m_pDelayEventList[i]->m_cMapIndex
								, m_pDelayEventList[i]->m_dX
								, m_pDelayEventList[i]->m_dY);
				m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bSkillUsingStatus[22] = FALSE;
				m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iSkillUsingTimeID[22] = NULL;
				break;
			}
			break;

		case DEF_DELAYEVENTTYPE_ANCIENT_TABLET:
			if ((m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iStatus & 0x400000) != 0) {
				iTemp = 1;
			}
			else if ((m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iStatus & 0x800000) != 0) {
				iTemp = 3;
			}
			else if ((m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iStatus & 0x10000) != 0) {
				iTemp = 4;
			}

			SendNotifyMsg(NULL, m_pDelayEventList[i]->m_iTargetH, DEF_NOTIFY_SLATE_STATUS, iTemp, NULL, NULL, NULL);
			SetSlateFlag(m_pDelayEventList[i]->m_iTargetH, iTemp, FALSE);
			break;

		case DEF_DELAYEVENTTYPE_CALCMETEORSTRIKEEFFECT:
			CalcMeteorStrikeEffectHandler(m_pDelayEventList[i]->m_cMapIndex);
			break;

		case DEF_DELAYEVENTTYPE_DOMETEORSTRIKEDAMAGE:
			DoMeteorStrikeDamageHandler(m_pDelayEventList[i]->m_cMapIndex);
			break;
		
		case DEF_DELAYEVENTTYPE_METEORSTRIKE:
			MeteorStrikeHandler(m_pDelayEventList[i]->m_cMapIndex);
			break;
		
		case DEF_DELAYEVENTTYPE_USEITEM_SKILL:
			// 쩐횈��횑횇횤 쨩챌쩔챘쩔징 쨉청쨍짜 째찼째첬 째챔쨩챗, 횇챘쨘쨍 
			switch (m_pDelayEventList[i]->m_cTargetType) {
			case DEF_OWNERTYPE_PLAYER:
				iSkillNum = m_pDelayEventList[i]->m_iEffectType;
				
				if ( m_pClientList[m_pDelayEventList[i]->m_iTargetH] == NULL ) break;
				// 짹창쩌첬 쨩챌쩔챘��횑 쨔짬횊쩔횊짯 쨉횉쩐첬쨈횢쨍챕 쨔짬쩍횄. 
				if ( m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bSkillUsingStatus[iSkillNum] == FALSE ) break;
				// 짹창쩌첬 쨩챌쩔챘 쩍횄째짙 ID째징 쨈횧쨋처쨉쨉 쨔짬쩍횄 v1.12
				if ( m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iSkillUsingTimeID[iSkillNum] != m_pDelayEventList[i]->m_iV2) break;
				
				// 짹창쩌첬 쨩챌쩔챘 쨩처횇횂 횉횠횁짝 
				m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bSkillUsingStatus[iSkillNum] = FALSE;
				m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_iSkillUsingTimeID[iSkillNum] = NULL;
				
				// ��횑횁짝 Skill��횉 횊쩔째첬쩔징 쨉청쨍짜 째챔쨩챗��쨩 횉횗쨈횢. 
				iResult = iCalculateUseSkillItemEffect(m_pDelayEventList[i]->m_iTargetH, m_pDelayEventList[i]->m_cTargetType,
				 	                                   m_pDelayEventList[i]->m_iV1, iSkillNum, m_pDelayEventList[i]->m_cMapIndex, m_pDelayEventList[i]->m_dX, m_pDelayEventList[i]->m_dY);

				// 짹창쩌첬 쨩챌쩔챘��횑 횁횩횁철 쨉횉쩐첬��쩍��쨩 쩐횏쨍째쨈횢.
				SendNotifyMsg(NULL, m_pDelayEventList[i]->m_iTargetH, DEF_NOTIFY_SKILLUSINGEND, iResult, NULL, NULL, NULL);
				break;
			}
			break;
		
		case DEF_DELAYEVENTTYPE_DAMAGEOBJECT:
			break;

		case DEF_DELAYEVENTTYPE_KILL_ABADDON:
			NpcKilledHandler(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, m_pDelayEventList[i]->m_iTargetH, 0);
			break;

		case DEF_DELAYEVENTTYPE_END_APOCALYPSE:
			GlobalEndApocalypseMode(0);	
			break;

		case DEF_DELAYEVENTTYPE_MAGICRELEASE: 
			// Removes the aura after time
			switch (m_pDelayEventList[i]->m_cTargetType) {
			case DEF_OWNERTYPE_PLAYER:
				if (m_pClientList[ m_pDelayEventList[i]->m_iTargetH ] == NULL) break;
				
				SendNotifyMsg(NULL, m_pDelayEventList[i]->m_iTargetH, DEF_NOTIFY_MAGICEFFECTOFF, 
					          m_pDelayEventList[i]->m_iEffectType, m_pClientList[ m_pDelayEventList[i]->m_iTargetH ]->m_cMagicEffectStatus[ m_pDelayEventList[i]->m_iEffectType ], NULL, NULL);
				
				m_pClientList[ m_pDelayEventList[i]->m_iTargetH ]->m_cMagicEffectStatus[ m_pDelayEventList[i]->m_iEffectType ] = NULL;
				
				// Inbitition casting 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_INHIBITION)
					m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bInhibition = FALSE;

				// Invisibility 효과 해제 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_INVISIBILITY)
					SetInvisibilityFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);

				// Berserk 효과 해제
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_BERSERK)
					SetBerserkFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);

				// Confusion
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_CONFUSE)
					switch(m_pDelayEventList[i]->m_iV1){
						case 3: SetIllusionFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE); break;
						case 4: SetIllusionMovementFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE); break;
					}	

				// Protection Magic
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_PROTECT) {
					switch(m_pDelayEventList[i]->m_iV1){
						case 1:
							SetProtectionFromArrowFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
							break;
						case 2:
						case 5:
							SetMagicProtectionFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
							break;
						case 3:
						case 4:
							SetDefenseShieldFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
							break;
					}
				}

				
				// polymorph 효과 해제 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_POLYMORPH) {
					m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_sType = m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_sOriginalType;
					m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bIsPolymorph = FALSE;
					SendEventToNearClient_TypeA(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
				}

				// Ice 효과 해제 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_ICE)
					SetIceFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
				break;
			
			case DEF_OWNERTYPE_NPC:
				if (m_pNpcList[ m_pDelayEventList[i]->m_iTargetH ] == NULL) break;
				
				m_pNpcList[ m_pDelayEventList[i]->m_iTargetH ]->m_cMagicEffectStatus[ m_pDelayEventList[i]->m_iEffectType ] = NULL;
				
				// Invisibility 횊쩔째첬 횉횠횁짝 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_INVISIBILITY)
					SetInvisibilityFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);

				// Berserk 횊쩔째첬 횉횠횁짝
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_BERSERK)
					SetBerserkFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);

				// polymorph 횊쩔째첬 횉횠횁짝 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_POLYMORPH) {
					m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_sType = m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_sOriginalType;
					m_pClientList[m_pDelayEventList[i]->m_iTargetH]->m_bIsPolymorph = FALSE;
					SendEventToNearClient_TypeA(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
				}

				// Ice 횊쩔째첬 횉횠횁짝 
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_ICE)
					SetIceFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);
				
				// Illusion
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_CONFUSE)
					SetIllusionFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);

				// Protection Magic
				if (m_pDelayEventList[i]->m_iEffectType == DEF_MAGICTYPE_PROTECT) {
					switch(m_pDelayEventList[i]->m_iV1){
						case 1:
							SetProtectionFromArrowFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);
							break;
						case 2:
						case 5:
							SetMagicProtectionFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);
							break;
						case 3:
						case 4:
							SetDefenseShieldFlag(m_pDelayEventList[i]->m_iTargetH, DEF_OWNERTYPE_NPC, FALSE);
							break;
					}
				}
				break;
			}
			break;
		}
		
		delete m_pDelayEventList[i];
		m_pDelayEventList[i] = NULL;
	}
}
BOOL CGame::bRemoveFromDelayEventList(int iH, char cType, int iEffectType)
{
 int i;

	for (i = 0; i < DEF_MAXDELAYEVENTS; i++) 
	if (m_pDelayEventList[i] != NULL) {
		
		if (iEffectType == NULL) {
			// Effect 횁쩐쨌첫쩔징 쨩처째체쩐첩��횑 쨍챨쨉횓 쨩챔횁짝 	
			if ( (m_pDelayEventList[i]->m_iTargetH == iH) && (m_pDelayEventList[i]->m_cTargetType == cType) ) {
				delete m_pDelayEventList[i];
				m_pDelayEventList[i] = NULL;
			}
		}
		else {
			// 횉횠쨈챌 Effect쨍쨍 쨩챔횁짝.
			if ( (m_pDelayEventList[i]->m_iTargetH == iH) && (m_pDelayEventList[i]->m_cTargetType == cType) &&
				 (m_pDelayEventList[i]->m_iEffectType == iEffectType) ) {
				delete m_pDelayEventList[i];
				m_pDelayEventList[i] = NULL;
			}
		}
	}
	
	return TRUE;
}

void CGame::SendObjectMotionRejectMsg(int iClientH)
{
 char  * cp, cData[30];
 DWORD * dwp;
 WORD  * wp;
 short * sp;
 int     iRet;

	if (m_pClientList[iClientH] == NULL) return; // add by SNOOPY

	m_pClientList[iClientH]->m_bIsMoveBlocked = TRUE; // v2.171
	
	// ��횑쨉쩔��횑 쨘횘째징쨈횋횉횕쨈횢. 
	dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
 	*dwp = MSGID_RESPONSE_MOTION;
	wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_OBJECTMOTION_REJECT;
	
	cp   = (char *)(cData + DEF_INDEX2_MSGTYPE + 2); 
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sX; 
	cp += 2;
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sY; 
	cp += 2;
	
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 10);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩐쨋짠 쩔징쨌짱째징 쨔횩쨩첵횉횩쨈횢쨍챕 횁짝째횇횉횗쨈횢.
		DeleteClient(iClientH, TRUE, TRUE);
		break;
	}
}

int CGame::_iGetTotalClients()
{
 int i, iTotal;

	iTotal = 0;
	for (i = 1; i < DEF_MAXCLIENTS; i++) 
	if (m_pClientList[i] != NULL) iTotal++;

	return iTotal;
}

void CGame::DynamicObjectEffectProcessor()
{
 int i, ix, iy, iIndex;
 short sOwnerH, iDamage, sType, sAttacker;
 char  cOwnerType, cAttackerOwnerType;
 DWORD dwTime = timeGetTime(), dwRegisterTime;
	
	// 
	for (i = 0; i < DEF_MAXDYNAMICOBJECTS; i++) 
	if (m_pDynamicObjectList[i] != NULL) {

		cAttackerOwnerType = m_pDynamicObjectList[i]->m_cOwnerType;
		if (cAttackerOwnerType == DEF_OWNERTYPE_PLAYER_INDIRECT)
		{
			sAttacker = m_pDynamicObjectList[i]->m_sOwner;
			if (m_pClientList[sAttacker] == NULL)
			{
				sAttacker = 0;
				cAttackerOwnerType = NULL;
			}
			else if (strcmp(m_pClientList[sAttacker]->m_cCharName, m_pDynamicObjectList[i]->cOwnerName) != 0)
			{
				sAttacker = 0;
				cAttackerOwnerType = NULL;
			}
		}
		switch (m_pDynamicObjectList[i]->m_sType) {

		case DEF_DYNAMICOBJECT_PCLOUD_BEGIN:
			// 횈첨��횑횁챨 횇짭쨋처쩔챙쨉책
			for (ix = m_pDynamicObjectList[i]->m_sX -1; ix <= m_pDynamicObjectList[i]->m_sX+1; ix++)
			for (iy = m_pDynamicObjectList[i]->m_sY -1; iy <= m_pDynamicObjectList[i]->m_sY+1; iy++) {
				
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
				if (sOwnerH != NULL) {
					// Poison Damage쨍짝 ��횚쨈횂쨈횢.
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == NULL) break;
						if (m_pClientList[sOwnerH]->m_bIsKilled == TRUE) break;
						// v1.41 횁횩쨍쨀��횑째챠 ��체횇천쨍챨쨉책째징 쩐횈쨈횕쨍챕 횉횉횉횠쨍짝 ��횚횁철 쩐횎쨈횂쨈횢.
						// ��횑쨌짹 쩍횆��쨍쨌횓 쨈챘쨔횑횁철��횉 횇짤짹창쨍짝 째찼횁짚
						// Snoopy: Increazed a bit ..because rain/snow will reduce it.
						if (m_pDynamicObjectList[i]->m_iV1 <= 20) // Was 20 or 40 in spells definition ....
							 iDamage = iDice(2,8); // 1..8 >> 2..8
						else iDamage = iDice(2,10); // 1..8 >> 2..10	

						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(46, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);

						// New 17/05/2004 Changed
						if (m_pClientList[sOwnerH]->m_iAdminUserLevel == 0)
							m_pClientList[sOwnerH]->m_iHP -= iDamage;
						
						if (m_pClientList[sOwnerH]->m_iHP <= 0) {
							// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
							ClientKilledHandler(sOwnerH, sOwnerH, cOwnerType, iDamage);	
	  					}
						else {
							if (iDamage > 0) {
								// 쨔횧��쨘 쨈챘쨔횑횁철쨍짝 횇챘쨘쨍횉횗쨈횢. <- HP쨍짝 짹횞쨈챘쨌횓 쩐횏쨍째쨈횢.
								SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);

								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
									// 쨍쨋쨘챰 쨩처횇횂째징 횉짰쨍째쨈횢.	
									// 1: Hold-Person 
									// 2: Paralize
									SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
							
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
									bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
								}
						 	}

							// v1.42 Poison 횊쩔째첬
							if ( (bCheckResistingMagicSuccess(1, sOwnerH, DEF_OWNERTYPE_PLAYER, 100) == FALSE) &&
								 (m_pClientList[sOwnerH]->m_bIsPoisoned == FALSE) ) {
								
								m_pClientList[sOwnerH]->m_bIsPoisoned  = TRUE;
								m_pClientList[sOwnerH]->m_iPoisonLevel = m_pDynamicObjectList[i]->m_iV1;
								m_pClientList[sOwnerH]->m_dwPoisonTime = dwTime;
								// 횁횩쨉쨋쨉횉쩐첬��쩍��쨩 쩐횏쨍째쨈횢. 
								SetPoisonFlag(sOwnerH, cOwnerType, TRUE);// poison aura appears from dynamic objects
								SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POISON, m_pClientList[sOwnerH]->m_iPoisonLevel, NULL, NULL);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						// 쨍처쩍쨘횇횒��횉 횁횩쨉쨋횊쩔째첬쨈횂 쩐횈횁첨 짹쨍횉철 쩐횊쨉횎
						if (m_pNpcList[sOwnerH] == NULL) break;

						// ��횑쨌짹 쩍횆��쨍쨌횓 쨈챘쨔횑횁철��횉 횇짤짹창쨍짝 째찼횁짚
						if (m_pDynamicObjectList[i]->m_iV1 <= 20)
							 iDamage = iDice(2,8);
						else iDamage = iDice(2,10);	
						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(46, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);

						if (iDamage < 1 ) iDamage = 1;				
						// HP

						// ��체��챦쩔챘 짹쨍횁쨋쨔째횁횩 짹횞쨌짙쨉책 쨍횇횁첨 횁짝쨀횞쨌쨔��횑횇횒, 쩔징쨀횎횁철 쩍횉쨉책 횁짝쨀횞쨌쨔��횑횇횒쨈횂 횉횎쨉책쨌첫 쨍쨋쨔첵쩔징 쨈챘쨔횑횁철쨍짝 ��횚횁철 쩐횎쨈횂쨈횢.
						switch (m_pNpcList[sOwnerH]->m_cActionLimit) {
						case 0: // normal monster
						case 1: // never runner monster
							m_pNpcList[sOwnerH]->m_iHP -= iDamage;
							// SNOOPY: Poison cloud can poison npc
							if ((bCheckResistingMagicSuccess(0, sOwnerH, DEF_OWNERTYPE_NPC, 100) == FALSE)
								&& (bCheckResistingPoisonSuccess(sOwnerH, DEF_OWNERTYPE_NPC) == FALSE))
							{
								if (m_pNpcList[sOwnerH]->m_iPoisonLevel < m_pDynamicObjectList[i]->m_iV1)
									m_pNpcList[sOwnerH]->m_iPoisonLevel = m_pDynamicObjectList[i]->m_iV1;
								SetPoisonFlag(sOwnerH, cOwnerType, TRUE);// poison aura appears from dynamic objects
							}
							if (m_pNpcList[sOwnerH]->m_iHP <= 0)
							{
								NpcKilledHandler(sAttacker, cAttackerOwnerType, sOwnerH, 0);
							}
							else
							{
								if (iDice(1, 3) == 2)
									m_pNpcList[sOwnerH]->m_dwTime = dwTime;

								if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) {
									// Hold 	
									m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = NULL;
								}

								// NPC
								SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, 0, NULL);
							}
							break;
						default:
							iDamage = 0;
							break;
						}
						break;
					}
				}
			}
			break;
						
		case DEF_DYNAMICOBJECT_ICESTORM:
			for (ix = m_pDynamicObjectList[i]->m_sX -2; ix <= m_pDynamicObjectList[i]->m_sX+2; ix++)
			for (iy = m_pDynamicObjectList[i]->m_sY -2; iy <= m_pDynamicObjectList[i]->m_sY+2; iy++) {
				
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
				if (sOwnerH != NULL) {
					switch (cOwnerType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == NULL) break;
						if (m_pClientList[sOwnerH]->m_bIsKilled == TRUE) break;

						// Increased damages a bit
						iDamage = iDice(3,4) + 5;

						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(55, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);

						if (m_pClientList[sOwnerH]->m_iAdminUserLevel == 0)
						m_pClientList[sOwnerH]->m_iHP -= iDamage;
						
						if (m_pClientList[sOwnerH]->m_iHP <= 0) {
							// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
							ClientKilledHandler(sOwnerH, sOwnerH, cOwnerType, iDamage);	
	  					}
						else {
							if (iDamage > 0) {

									SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);

								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] == 1) {

									SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
							
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
									bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
								}
						 	}

							if ( (bCheckResistingIceSuccess(1, sOwnerH, DEF_OWNERTYPE_PLAYER, m_pDynamicObjectList[i]->m_iV1) == FALSE) &&
								 (m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] == 0) ) {
								
								m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] = 1;
								SetIceFlag(sOwnerH, cOwnerType, TRUE);
								// 횊쩔째첬째징 횉횠횁짝쨉횋 쨋짠 쨔횩쨩첵횉횘 쨉척쨌쨔��횑 ��횑쨘짜횈짰쨍짝 쨉챤쨌횕횉횗쨈횢.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (20*1000), 
									                sOwnerH, cOwnerType, NULL, NULL, NULL, 1, NULL, NULL);

								SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, NULL, NULL);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == NULL) break;
						
						iDamage = iDice(3,4) + 5;
						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(55, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);

						switch (m_pNpcList[sOwnerH]->m_sType) {
						case 40: // ESG
						case 41: // GMG
						case 67: // McGaffin
						case 68: // Perry
						case 69: // Devlin
							iDamage = 0;
							break;
						}
						
						switch (m_pNpcList[sOwnerH]->m_cActionLimit) {
						case 0:
						case 3:
						case 5:
							m_pNpcList[sOwnerH]->m_iHP -= iDamage;
							break;
						case 8: // Heldenian gate.
							iDamage = iDamage/2;
							break;
						}

						if (m_pNpcList[sOwnerH]->m_iHP <= 0) {
							// NPC째징 쨩챌쨍횁횉횩쨈횢.
							NpcKilledHandler(sOwnerH, cOwnerType, sOwnerH, 0); //v1.2 횇쨍쩌짯 횁횞��쨍쨍챕 쨍쨋횁철쨍쨌 쨈챘쨔횑횁철째징 0. 쩐횈��횑횇횤��쨩 쩍짹째횚 짹쨍횉횕횁철 쨍첩횉횕째횚 횉횕짹창 ��짠횉횚.
						}
						else {
							// Damage쨍짝 ��횚��쨘 횄챈째횦��쨍쨌횓 ��횓횉횗 횁철쩔짭횊쩔째첬.
							if (iDice(1,3) == 2)
								m_pNpcList[sOwnerH]->m_dwTime = dwTime;
							
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
								// Hold 쨉횉쩐챤 ��횜쩐첬쨈첩 쨩처횇횂쨋처쨍챕 횉짰쨍째쨈횢. 	
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
							}
						
							// NPC쨍짝 쨉쨉쨍횁째징쨈횂 쨍챨쨉책쨌횓 ��체횊짱쩍횄횇짼쨈횢.
					 		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, 0, NULL);

							// v1.42 Ice 횊쩔째첬
							if ( (bCheckResistingIceSuccess(1, sOwnerH, DEF_OWNERTYPE_NPC, m_pDynamicObjectList[i]->m_iV1) == FALSE) &&
								 (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] == 0) ) {
																
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] = 1;
								SetIceFlag(sOwnerH, cOwnerType, TRUE);
								// 횊쩔째첬째징 횉횠횁짝쨉횋 쨋짠 쨔횩쨩첵횉횘 쨉척쨌쨔��횑 ��횑쨘짜횈짰쨍짝 쨉챤쨌횕횉횗쨈횢.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (20*1000), 
								                    sOwnerH, cOwnerType, NULL, NULL, NULL, 1, NULL, NULL);
							}
						}
					   	break;
					}
				}

				// 횁횞��쨘횄쨈횉횕째챠 ��횜쨈횂 횆쨀쨍짱��횑 ��횜쨈횢쨍챕
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
				if ( (cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != NULL) &&
			 	     (m_pClientList[sOwnerH]->m_iHP > 0) ) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					iDamage = iDice(6,4) + 10; // Increased serioully.
					m_pClientList[sOwnerH]->m_iHP -= iDamage;
						
					if (m_pClientList[sOwnerH]->m_iHP <= 0) {
						// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
						ClientKilledHandler(sOwnerH, sOwnerH, cOwnerType, iDamage);	
	  				}
					else {
						if (iDamage > 0) {
							m_pClientList[sOwnerH]->m_dwRecentAttackTime = dwTime;
							// 쨔횧��쨘 쨈챘쨔횑횁철쨍짝 횇챘쨘쨍횉횗쨈횢. <- HP쨍짝 짹횞쨈챘쨌횓 쩐횏쨍째쨈횢.
							SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
						}
					}
				}

				// 짹횢횄쨀쩔징 Fire Object째징 ��횜쨈횢쨍챕 쩌철쨍챠��쨩 횁횢��횓쨈횢.
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->bGetDynamicObject(ix, iy, &sType, &dwRegisterTime, &iIndex);
				if (((sType == DEF_DYNAMICOBJECT_FIRE) || (sType == DEF_DYNAMICOBJECT_FIRE3)) && (m_pDynamicObjectList[iIndex] != NULL)) 
					m_pDynamicObjectList[iIndex]->m_dwLastTime = m_pDynamicObjectList[iIndex]->m_dwLastTime - (m_pDynamicObjectList[iIndex]->m_dwLastTime/10);
			}
			break;
		
		case DEF_DYNAMICOBJECT_FIRE3:
		case DEF_DYNAMICOBJECT_FIRE2:
		case DEF_DYNAMICOBJECT_FIRE:
			// Fire-Wall쨌첫��횉 횇쨍쨈횂 쨘횘짼횋
			if (m_pDynamicObjectList[i]->m_iCount == 1) {
				// 짹횢횄쨀쩔징 횇쨍쨈횂 쨔째째횉��횑 ��횜쨈횢쨍챕 쨔첩횁첩쨈횢. 
				CheckFireBluring(m_pDynamicObjectList[i]->m_cMapIndex, m_pDynamicObjectList[i]->m_sX, m_pDynamicObjectList[i]->m_sY);
			}
			m_pDynamicObjectList[i]->m_iCount++;
			if (m_pDynamicObjectList[i]->m_iCount > 10) m_pDynamicObjectList[i]->m_iCount = 10; 

				for (ix = m_pDynamicObjectList[i]->m_sX;    ix <= m_pDynamicObjectList[i]->m_sX;   ix++)
				for (iy = m_pDynamicObjectList[i]->m_sY;    iy <= m_pDynamicObjectList[i]->m_sY;   iy++) {
				
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
				if (sOwnerH != NULL) {
					// Fire Damage쨍짝 ��횚쨈횂쨈횢.
					switch (cOwnerType) {
					
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[sOwnerH] == NULL) break;
						if (m_pClientList[sOwnerH]->m_bIsKilled == TRUE) break;
						// v1.41 횁횩쨍쨀��횑째챠 ��체횇천쨍챨쨉책째징 쩐횈쨈횕쨍챕 횉횉횉횠쨍짝 ��횚횁철 쩐횎쨈횂쨈횢.
						// Snoopy: Increazed a bit ..because rain/snow will reduce it.	.
						iDamage = iDice(2,4);			
						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(40, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);
						// New 17/05/2004
						if (m_pClientList[sOwnerH]->m_iAdminUserLevel == 0)
							m_pClientList[sOwnerH]->m_iHP -= iDamage;
						
						if (m_pClientList[sOwnerH]->m_iHP <= 0) {
							// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
							ClientKilledHandler(sOwnerH, sOwnerH, cOwnerType, iDamage);	
	  					}
						else {
							if (iDamage > 0) {
								// 쨔횧��쨘 쨈챘쨔횑횁철쨍짝 횇챘쨘쨍횉횗쨈횢. <- HP쨍짝 짹횞쨈챘쨌횓 쩐횏쨍째쨈횢.
								SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);

								if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
									// Hold-Person 쨉횉쩐챤 ��횜쩐첬쨈첩 쨩처횇횂쨋처쨍챕 횉짰쨍째쨈횢. Fire Field쨌횓쨈횂 횈횖쨌짼쨋처��횑횁챤 쨉횊째횒쨉쨉 횉짰쨍째쨈횢. 	
									// 1: Hold-Person 
									// 2: Paralize	
									SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
							
									m_pClientList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
									bRemoveFromDelayEventList(sOwnerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
								}
						 	}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[sOwnerH] == NULL) break;
						
						iDamage = iDice(2,4);	
						// SNOOPY: Whether Bouns
						iDamage += iGetWhetherMagicBonusEffect(40, m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->m_cWhetherStatus);
						if (iDamage < 1 ) iDamage=1;

						// ��체��챦쩔챘 짹쨍횁쨋쨔째횁횩 짹횞쨌짙쨉책 쨍횇횁첨 횁짝쨀횞쨌쨔��횑횇횒, 쩔징쨀횎횁철 쩍횉쨉책 횁짝쨀횞쨌쨔��횑횇횒쨈횂 횉횎쨉책쨌첫 쨍쨋쨔첵쩔징 쨈챘쨔횑횁철쨍짝 ��횚횁철 쩐횎쨈횂쨈횢.
						switch (m_pNpcList[sOwnerH]->m_sType) {
						case 40: // ESG
						case 41: // GMG
						case 67: // McGaffin
						case 68: // Perry
						case 69: // Devlin
							iDamage = 0;
							break;
						}
												
						// HP쩔징쩌짯 쨩짬쨈횢. Action Limit쩔징 쨉청쨋처 횄쨀쨍짰횉횗쨈횢.
						switch (m_pNpcList[sOwnerH]->m_cActionLimit) {
						case 0: // ��횕쨔횦
						case 3: // 쨈천쨔횑쨌첫
						case 5: // 째횉횄횪쨔째 
						case 8: // Heldenian gate.
							m_pNpcList[sOwnerH]->m_iHP -= iDamage;
							break;
						}
						if (m_pNpcList[sOwnerH]->m_iHP <= 0) {
							// NPC째징 쨩챌쨍횁횉횩쨈횢.
							NpcKilledHandler(sOwnerH, cOwnerType, sOwnerH, 0); //v1.2 횇쨍쩌짯 횁횞��쨍쨍챕 쨍쨋횁철쨍쨌 쨈챘쨔횑횁철째징 0. 쩐횈��횑횇횤��쨩 쩍짹째횚 짹쨍횉횕횁철 쨍첩횉횕째횚 횉횕짹창 ��짠횉횚.
						}
						else {
							// Damage쨍짝 ��횚��쨘 횄챈째횦��쨍쨌횓 ��횓횉횗 횁철쩔짭횊쩔째첬.
							if (iDice(1,3) == 2)
								m_pNpcList[sOwnerH]->m_dwTime = dwTime;
							
							if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] != 0) {
								// Hold 쨉횉쩐챤 ��횜쩐첬쨈첩 쨩처횇횂쨋처쨍챕 횉짰쨍째쨈횢. 	
								m_pNpcList[sOwnerH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
							}
						
							// NPC쨍짝 쨉쨉쨍횁째징쨈횂 쨍챨쨉책쨌횓 ��체횊짱쩍횄횇짼쨈횢.
					 		SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, 0, NULL);
						}
					   	break;
					}
				}

				// 횁횞��쨘횄쨈횉횕째챠 ��횜쨈횂 횆쨀쨍짱��횑 ��횜쨈횢쨍챕
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->GetDeadOwner(&sOwnerH, &cOwnerType, ix, iy);
				if ( (cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != NULL) &&
			 	     (m_pClientList[sOwnerH]->m_iHP > 0) ) {
					// 횁횞��쨘 횄쨈횉횕째챠 ��횜쨈횂 횉횄쨌쨔��횑쩐챤쨈횢.
					iDamage = iDice(1,6);
					m_pClientList[sOwnerH]->m_iHP -= iDamage;
						
					if (m_pClientList[sOwnerH]->m_iHP <= 0) {
						// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
						ClientKilledHandler(sOwnerH, sOwnerH, cOwnerType, iDamage);	
	  				}
					else {
						if (iDamage > 0) {
							m_pClientList[sOwnerH]->m_dwRecentAttackTime = dwTime;
							// 쨔횧��쨘 쨈챘쨔횑횁철쨍짝 횇챘쨘쨍횉횗쨈횢. <- HP쨍짝 짹횞쨈챘쨌횓 쩐횏쨍째쨈횢.
							SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
						}
					}
				}

				// 짹횢횄쨀쩔징 Ice Object째징 ��횜쨈횢쨍챕 쩌철쨍챠��쨩 횁횢��횓쨈횢.
				m_pMapList[m_pDynamicObjectList[i]->m_cMapIndex]->bGetDynamicObject(ix, iy, &sType, &dwRegisterTime, &iIndex);
				if ((sType == DEF_DYNAMICOBJECT_ICESTORM) && (m_pDynamicObjectList[iIndex] != NULL)) 
					m_pDynamicObjectList[iIndex]->m_dwLastTime = m_pDynamicObjectList[iIndex]->m_dwLastTime - (m_pDynamicObjectList[iIndex]->m_dwLastTime/10);
			}
			break;
		}
	}
} 

void CGame::CheckAndNotifyPlayerConnection(int iClientH, char * pMsg, DWORD dwSize)
{
 char   seps[] = "= \t\n";
 char   * token, * cp, cName[11], cBuff[256], cPlayerLocation[120];
 class  CStrTok * pStrTok;
 int i;
 WORD * wp;

	if (m_pClientList[iClientH] == NULL) return;
	if (dwSize <= 0) return;

	ZeroMemory(cPlayerLocation,sizeof(cPlayerLocation));
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pMsg, dwSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token == NULL) {
		delete pStrTok;
		return;
	}

	if (strlen(token) > 10) 
		 memcpy(cName, token, 10);	
	else memcpy(cName, token, strlen(token));

	// cName��횉 ��횑쨍짠��쨩 째징횁첩 횉횄쨌쨔��횑쩐챤째징 횁짖쩌횙횁횩��횓횁철 횄짙쨈횂쨈횢. 
	for (i = 1; i < DEF_MAXCLIENTS; i++) 
	if ((m_pClientList[i] != NULL) && (memcmp(cName, m_pClientList[i]->m_cCharName, 10) == 0)) {
		// 째째��쨘 ��횑쨍짠��쨩 째징횁첩 횆쨀쨍짱횇횒쨍짝 횄짙쩐횘쨈횢. 
		if(m_pClientList[iClientH]->m_iAdminUserLevel > 0){ // GM's get more info
			cp = (char *)cPlayerLocation;

			memcpy(cp,m_pClientList[i]->m_cMapName,10);
			cp += 10;

			wp = (WORD *)cp;
			*wp = m_pClientList[i]->m_sX;
			cp += 2;

			wp = (WORD *)cp;
			*wp = m_pClientList[i]->m_sY;
			cp += 2;
		}
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERONGAME, NULL, NULL, NULL, m_pClientList[i]->m_cCharName,NULL,NULL,NULL,NULL,NULL,NULL,cPlayerLocation);

		delete pStrTok;
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	cp = (char *)cBuff;
	*cp = GSM_REQUEST_FINDCHARACTER;
	cp++;

	wp = (WORD *)cp;
	*wp = m_wServerID_GSS;
	cp += 2;

	wp = (WORD *)cp;
	*wp = iClientH;
	cp += 2;

	memcpy(cp, cName, 10);
	cp += 10;

	memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
	cp += 10;

	bStockMsgToGateServer(cBuff, 25);

	delete pStrTok;
}



void CGame::ToggleWhisperPlayer(int iClientH, char * pMsg, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cName[11], cBuff[256];
 class  CStrTok * pStrTok;
 int i;
 char *cp;
 WORD *wp;

	if (m_pClientList[iClientH] == NULL) return;
	if (dwMsgSize <= 0) return;

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pMsg, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   
	if (token == NULL) {
		m_pClientList[iClientH]->m_iWhisperPlayerIndex = -1;
		ZeroMemory(m_pClientList[iClientH]->m_cWhisperPlayerName, sizeof(m_pClientList[iClientH]->m_cWhisperPlayerName));
		m_pClientList[iClientH]->m_bIsCheckingWhisperPlayer = FALSE;
		// Whisper mode enabled
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_WHISPERMODEOFF, NULL, NULL, NULL, cName);
	}
	else {
		if (strlen(token) > 10) 
			 memcpy(cName, token, 10);
		else memcpy(cName, token, strlen(token));

		m_pClientList[iClientH]->m_iWhisperPlayerIndex = -1;

		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0)) {
			if (i == iClientH) {
				delete pStrTok;
				// Whisper self XenX
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You shouldnt talk to yourself!");
				return;
			}
			m_pClientList[iClientH]->m_iWhisperPlayerIndex = i;
			ZeroMemory(m_pClientList[iClientH]->m_cWhisperPlayerName, sizeof(m_pClientList[iClientH]->m_cWhisperPlayerName));
			strcpy(m_pClientList[iClientH]->m_cWhisperPlayerName, cName);
			break;
		}

		if (m_pClientList[iClientH]->m_iWhisperPlayerIndex == -1) {
			ZeroMemory(cBuff, sizeof(cBuff));
			cp = (char *)cBuff;
			*cp = GSM_REQUEST_FINDCHARACTER;
			cp++;

			wp = (WORD *)cp;
			*wp = m_wServerID_GSS;
			cp += 2;

			wp = (WORD *)cp;
			*wp = iClientH;
			cp += 2;

			memcpy(cp, cName, 10);
			cp += 10;

			memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
			cp += 10;

			bStockMsgToGateServer(cBuff, 25);

			ZeroMemory(m_pClientList[iClientH]->m_cWhisperPlayerName, sizeof(m_pClientList[iClientH]->m_cWhisperPlayerName));
			strcpy(m_pClientList[iClientH]->m_cWhisperPlayerName, cName);
			m_pClientList[iClientH]->m_bIsCheckingWhisperPlayer = TRUE;
		}
		else{
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_WHISPERMODEON, NULL, NULL, NULL, m_pClientList[iClientH]->m_cWhisperPlayerName);
			return;
		}
		//player not online XenX
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "This player is not online!");
	}
	delete pStrTok;
}


void CGame::SetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize)
{
 char cTemp[256];
 int i;


	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize - 7) <= 0) return;

	ZeroMemory(cTemp, sizeof(cTemp));
	memcpy(cTemp, (pMsg + 7), dwMsgSize - 7);
	
	// 째첩쨔챕쨋천��쨩 쩐챨쨈천쨔횢쨌횓 쨔횢짼횤쨈횢. 
	for (i = 0; i < 256; i++)
		if (cTemp[i] == ' ') cTemp[i] = '_';

	// 쩔징쨌짱 쨔챈횁철 횆횣쨉책 
	cTemp[255] = NULL;

	ZeroMemory(m_pClientList[iClientH]->m_cProfile, sizeof(m_pClientList[iClientH]->m_cProfile));
	strcpy(m_pClientList[iClientH]->m_cProfile, cTemp);
}

void CGame::GetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cName[11], cBuff[256], cBuff2[500];
 class  CStrTok * pStrTok;
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pMsg, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   	
	if (token != NULL) {
		// token��횑 째챨 횉횁쨌횓횉횎��쨩 쩐챵째챠��횣 횉횕쨈횂 쨩챌쩔챘��횣 ��횑쨍짠 
		if (strlen(token) > 10) 
			 memcpy(cName, token, 10);
		else memcpy(cName, token, strlen(token));
		
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0)) {
		
			ZeroMemory(cBuff2, sizeof(cBuff2));
			wsprintf(cBuff2, "%s Profile: %s", cName, m_pClientList[i]->m_cProfile);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERPROFILE, NULL, NULL, NULL, cBuff2);

			delete pStrTok;
			return;
		}
		// 횉철��챌 횁짖쩌횙횁횩��횑 쩐횈쨈횕쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERNOTONGAME, NULL, NULL, NULL, cName);
	}

	delete pStrTok;
	return;
}

/*********************************************************************************************************************
** BOOL CGame::SetAngelFlag(short sOwnerH, char cOwnerType, int iStatus, iTemp)  Snoopy								** 
** description   :: Sets the staus to send or not Angels to every client											**
*********************************************************************************************************************/
void CGame::SetAngelFlag(short sOwnerH, char cOwnerType, int iStatus, int iTemp) 
{	if (cOwnerType != DEF_OWNERTYPE_PLAYER) return;
	if (m_pClientList[sOwnerH] == NULL) return;
	switch (iStatus) {
	case 1: // STR Angel
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00001000;  
		break;
	case 2: // DEX Angel
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00002000;
		break;
	case 3: // INT Angel
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00004000;
		break;
	case 4: // MAG Angel
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | 0x00008000;
		break;
	default:// Remove all Angels
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus & 0xFFFF00FF;
		break;
	}
	if (iTemp > 9)
	{
		int iAngelicStars = (iTemp / 3) * (iTemp / 5);
		m_pClientList[sOwnerH]->m_iStatus = m_pClientList[sOwnerH]->m_iStatus | (iAngelicStars << 8);
	}
	SendEventToNearClient_TypeA(sOwnerH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
}

int CGame::_iGetPlayerNumberOnSpot(short dX, short dY, char cMapIndex, char cRange)
{
 int ix, iy, iSum = 0;
 short sOwnerH;
 char  cOwnerType;

	for (ix = dX - cRange; ix <= dX + cRange; ix++)
	for (iy = dY - cRange; iy <= dY + cRange; iy++) {
		m_pMapList[cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
		if ((sOwnerH != NULL) && (cOwnerType == DEF_OWNERTYPE_PLAYER))
			iSum++;
	}

	return iSum;
}

BOOL CGame::bAnalyzeCriminalAction(int iClientH, short dX, short dY, BOOL bIsCheck)
{
 int   iNamingValue, tX, tY;
 short sOwnerH;
 char  cOwnerType, cName[11], cNpcName[21];
 char  cNpcWaypoint[11];

	if (m_pClientList[iClientH] == NULL) return FALSE;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return FALSE;
	if (m_bIsCrusadeMode == TRUE) return FALSE;

	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

	if ((cOwnerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sOwnerH] != NULL)) {
		if (_bGetIsPlayerHostile(iClientH, sOwnerH) != TRUE) {
			if (bIsCheck == TRUE) return TRUE;

			ZeroMemory(cNpcName, sizeof(cNpcName));
			if (strcmp(m_pClientList[iClientH]->m_cMapName, "aresden") == 0) 
				strcpy(cNpcName, "Guard-Aresden");			
			else if (strcmp(m_pClientList[iClientH]->m_cMapName, "elvine") == 0) 
				strcpy(cNpcName, "Guard-Elvine");
			else  if (strcmp(m_pClientList[iClientH]->m_cMapName, "default") == 0) 
				strcpy(cNpcName, "Guard-Neutral");

			iNamingValue = m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->iGetEmptyNamingValue();
			if (iNamingValue != -1) {

				ZeroMemory(cNpcWaypoint, sizeof(cNpcWaypoint));
				ZeroMemory(cName, sizeof(cName));
			   	wsprintf(cName, "XX%d", iNamingValue);
				cName[0] = '_';
				cName[1] = m_pClientList[iClientH]->m_cMapIndex+65;
				
				tX = (int)m_pClientList[iClientH]->m_sX;
				tY = (int)m_pClientList[iClientH]->m_sY;
				if (bCreateNewNpc(cNpcName, cName, m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_cName, 0, 0, DEF_MOVETYPE_RANDOM, 
					              &tX, &tY, cNpcWaypoint, NULL, NULL, -1, FALSE, TRUE) == FALSE) {
					m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->SetNamingValueEmpty(iNamingValue);
				} 
				else {
					bSetNpcAttackMode(cName, iClientH, DEF_OWNERTYPE_PLAYER, TRUE);
				}
			}
		}
	}
	return FALSE;
}

BOOL CGame::_bGetIsPlayerHostile(int iClientH, int sOwnerH)
{
	if (m_pClientList[iClientH] == NULL) return FALSE;
	if (m_pClientList[sOwnerH]  == NULL) return FALSE;

	// ��횣짹창 ��횣쩍횇쩔징 쨈챘횉횗 째첩째횦��쨘 쨔체횁횏쨋처 쨘쩌 쩌철 쩐첩쨈횢. 
	if (iClientH == sOwnerH) return TRUE;

	if (m_pClientList[iClientH]->m_cSide == 0) {
		// 째첩째횦��횣쨈횂 쩔짤횉횪��횣��횑쨈횢.
		// 쨩처쨈챘쨔챈��횑 쨔체횁횏��횣��횑쨍챕 ��청쩌쨘��횑쨍챌 짹횞 ��횑쩔횥쩔징쨈횂 쩐횈쨈횕쨈횢. 
		if (m_pClientList[sOwnerH]->m_iPKCount != 0) 
			 return TRUE;
		else return FALSE;
	}
	else {
		// 째첩째횦��횣쨈횂 쩌횘쩌횙 쨍쨋��쨩��쨩 째짰째챠 ��횜쨈횢. 
		if (m_pClientList[iClientH]->m_cSide != m_pClientList[sOwnerH]->m_cSide) {
			// 쩌짯쨌횓 쨩챌��횑쨉책째징 쨈횢쨍짙쨈횢. 
			if (m_pClientList[sOwnerH]->m_cSide == 0) {
				if (m_pClientList[sOwnerH]->m_iPKCount != 0) 
				 	 return TRUE;
				else return FALSE;
			}
			else return TRUE;
		}
		else {
			if (m_pClientList[sOwnerH]->m_iPKCount != 0) 
			 	 return TRUE;
			else return FALSE;
		}
	}

	return FALSE;
}

void CGame::CheckDayOrNightMode()
{
 SYSTEMTIME SysTime;	
 int cPrevMode;
 int  i;

	// 횉철��챌 쩍횄째짙쩔징 쨉청쨋처 쨀쨌 횊짚��쨘 쨔찾��쨩 째찼횁짚횉횗쨈횢. 
	// 횁횜, 쩐횩째짙 쨍챨쨉책 쩌쨀횁짚 
	cPrevMode = m_cDayOrNight;
 
	GetLocalTime(&SysTime);
	if (SysTime.wHour >= 19 || SysTime.wHour <= 6)
		 m_cDayOrNight = 2;
	else m_cDayOrNight = 1;

	if (cPrevMode != m_cDayOrNight) {
		// 횁횜, 쩐횩째짙 쨍챨쨉책째징 쨘짱째챈쨉횉쩐첬쨈횢. 횁횜, 쩐횩째짙 쨍챨쨉책��횉 쩔쨉횉창��쨩 쨔횧쨈횂 쨍횎쩔징 횁쨍��챌횉횕쨈횂 횇짭쨋처��횑쩐챨횈짰쨉챕쩔징째횚 쩐횏쨍째쨈횢. 
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
			if ((m_pClientList[i]->m_cMapIndex >= 0) && 
				(m_pMapList[m_pClientList[i]->m_cMapIndex] != NULL) &&
				(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_bIsFixedDayMode == FALSE))
				SendNotifyMsg(NULL, i, DEF_NOTIFY_TIMECHANGE, m_cDayOrNight, NULL, NULL, NULL);	
		}
	}
}


void CGame::ShutUpPlayer(int iClientH, char * pMsg, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cName[11], cBuff[256];
 class  CStrTok * pStrTok;
 int i, iTime;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelShutup) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pMsg, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   	
	if (token != NULL) {
		// token��횑 째챨 횄짚횈횄��쨩 쨘횘째징쨈횋횉횕째횚 쨍쨍쨉챕 쨩챌쩔챘��횣 ��횑쨍짠 
		if (strlen(token) > 10) 
			 memcpy(cName, token, 10);
		else memcpy(cName, token, strlen(token));
		
		// 쨈횢��쩍 횇채횇짬��쨘 횁짚횁철 쩍횄횇쨀 쩍횄째짙. 
		token = pStrTok->pGet();
		if (token == NULL) 
			 iTime = 0;
		else iTime = atoi(token);
	
		if (iTime < 0) iTime = 0;
	 		
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0)) {
			
			m_pClientList[i]->m_iTimeLeft_ShutUp = iTime * 20; // 1��횑 3횄횎쨈횢. 20��횑쨍챕 1쨘횖 
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERSHUTUP, iTime, NULL, NULL, cName);
			SendNotifyMsg(NULL, i, DEF_NOTIFY_PLAYERSHUTUP, iTime, NULL, NULL, cName);

			// Admin Log
			wsprintf(G_cTxt, "GM Order(%s): Shutup PC(%s) (%d)Min", m_pClientList[iClientH]->m_cCharName, 
				     m_pClientList[i]->m_cCharName, iTime);
			PutAdminLogFileList(G_cTxt);

			delete pStrTok;
			return;
		}
		// 횉철��챌 횁짖쩌횙횁횩��횑 쩐횈쨈횕쨈횢.
		ZeroMemory(cBuff, sizeof(cBuff));

		char *cp;
		WORD *wp;

		cp = (char *)cBuff;

		*cp = GSM_REQUEST_SHUTUPPLAYER;
		cp++;

		wp = (WORD *)cp;
		*wp = m_wServerID_GSS;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)iClientH;
		cp += 2;

		memcpy(cp, cName, 10);
		cp += 10;

		wp = (WORD *)cp;
		*wp = iTime;
		cp += 2;

		memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
		cp += 10;

		bStockMsgToGateServer(cBuff, 27);
	}

	delete pStrTok;
}


void CGame::SetPlayerReputation(int iClientH, char * pMsg, char cValue, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cName[11], cBuff[256];
 class  CStrTok * pStrTok;
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;
	if (m_pClientList[iClientH]->m_iLevel < 40) return;

	if ((m_pClientList[iClientH]->m_iTimeLeft_Rating != 0) || (m_pClientList[iClientH]->m_iPKCount != 0)) {
		// 평가를 내릴 시간이 되지 않았거나 범죄자는 평가를 내릴 수 없다. 기능을 사용할 수 없다.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTRATING, m_pClientList[iClientH]->m_iTimeLeft_Rating, NULL, NULL, NULL);
		return;
	}
	else if (memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) == 0) {
		// 소속 마을이 없는 사람은 평판을 내릴 수 없다.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTRATING, 0, NULL, NULL, NULL);
		return;	
	}

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pMsg, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   	
	if (token != NULL) {
		// token이 곧 평판을 평가할 사용자 이름 
		if (strlen(token) > 10) 
			 memcpy(cName, token, 10);
		else memcpy(cName, token, strlen(token));
		
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0)) {
			
			if (i != iClientH) {
				if(memcmp(m_pClientList[iClientH]->m_cIPaddress,  m_pClientList[i]->m_cIPaddress,  strlen(m_pClientList[iClientH]->m_cIPaddress)) == 0)
                {
                    SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You can't send rep to a player with your same IP.");
                }
                else
                {
					// 자기 자신을 평가할 수는 없다.
					if (cValue == 0) 
						m_pClientList[i]->m_iRating -= m_iRatingAdjust;
					else if (cValue == 1)
						m_pClientList[i]->m_iRating += m_iRatingAdjust;
					
					// 평가를 내렸으므로 시간 간격을 재 할당. 
					m_pClientList[iClientH]->m_iTimeLeft_Rating = 20*60;

					SendNotifyMsg(NULL, i, DEF_NOTIFY_RATINGPLAYER, cValue, NULL, NULL, cName);
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_RATINGPLAYER, cValue, NULL, NULL, cName);

					SendNotifyMsg(NULL, i, DEF_NOTIFY_REPDGDEATHS, m_pClientList[i]->m_iDGPoints, m_pClientList[i]->m_iDeaths, m_pClientList[i]->m_iRating, NULL); // MORLA 2.4 - Actualiza la REP
					
					delete pStrTok;
					return;
				}
			}
		}
		// 현재 접속중이 아니다.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERNOTONGAME, NULL, NULL, NULL, cName);
	}
	
	delete pStrTok;
}

BOOL CGame::bReadNotifyMsgListFile(char * cFn)
{
 FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadMode;
 char seps[] = "=\t\n;";
 class CStrTok * pStrTok;
 int   i;

	cReadMode = 0;
	m_iTotalNoticeMsg = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile == NULL) {
		PutLogList("(!) Notify Message list file not found!...");
		return FALSE;
	}
	else {
		PutLogList("(!) Reading Notify Message list file...");
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();
		while( token != NULL )   {
			
			if (cReadMode != 0) {
				switch (cReadMode) {
				case 1:
					for (i = 0; i < DEF_MAXNOTIFYMSGS; i++) 
					if (m_pNoticeMsgList[i] == NULL) {
						m_pNoticeMsgList[i] = new class CMsg;	
						m_pNoticeMsgList[i]->bPut(NULL, token, strlen(token), NULL, NULL);
						m_iTotalNoticeMsg++;
						break;
					}			
					cReadMode = 0;
					break;
				}
			}
			else {
				if (memcmp(token, "notify_msg", 10) == 0) cReadMode = 1;
			}
			
			token = pStrTok->pGet();
			
		}

		delete pStrTok;
		delete[] cp;

		fclose(pFile);
	}

	return TRUE;
}
void CGame::NoticeHandler()
{
 char  cTemp, cBuffer[1000], cKey;
 DWORD dwSize, dwTime = timeGetTime();
 int i, iMsgIndex, iTemp;

	// 째첩횁철쨩챌횉횞��횑 1째쨀 ��횑횉횕쨋처쨍챕 쨘쨍쨀쩐 횉횎쩔채째징 쩐첩쨈횢.
	if (m_iTotalNoticeMsg <= 1) return;

	if ((dwTime - m_dwNoticeTime) > DEF_NOTICETIME) {
		// 째첩횁철쨩챌횉횞��쨩 ��체쩌횤횉횘 쩍횄째짙��횑 쨉횉쩐첬쨈횢. 
		m_dwNoticeTime = dwTime;	
		do {
			iMsgIndex = iDice(1, m_iTotalNoticeMsg) - 1;
		} while (iMsgIndex == m_iPrevSendNoticeMsg);

		m_iPrevSendNoticeMsg = iMsgIndex;
		
		ZeroMemory(cBuffer, sizeof(cBuffer));
		if (m_pNoticeMsgList[iMsgIndex] != NULL) {
			m_pNoticeMsgList[iMsgIndex]->Get(&cTemp, cBuffer, &dwSize, &iTemp, &cKey);
		}
		
		for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) {
			SendNotifyMsg(NULL, i, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, cBuffer);
		}
	}
}


void CGame::ResponseSavePlayerDataReplyHandler(char * pData, DWORD dwMsgSize)
{
 char * cp, cCharName[11];
 int i;

	ZeroMemory(cCharName, sizeof(cCharName));
	
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	memcpy(cCharName, cp, 10);

	// ��횑횁짝 ��횑 ��횑쨍짠��쨩 째짰쨈횂 횇짭쨋처��횑쩐챨횈짰쨍짝 횄짙쩐횈 횁짖쩌횙��쨩 짼첨쩐챤쨉쨉 횁횁쨈횢쨈횂 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩍쨈횢. 
	for (i = 0; i < DEF_MAXCLIENTS; i++) 
	if (m_pClientList[i] != NULL) {
		if (memcmp(m_pClientList[i]->m_cCharName, cCharName, 10) == 0) {
			// 째째��쨘 ��횑쨍짠��쨩 째징횁첩 횆쨀쨍짱횇횒쨍짝 횄짙쩐횘쨈횢. 횁짖쩌횙��쨩 횁쩐쨌찼횉횕쨋처쨈횂 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩍쨈횢.
			SendNotifyMsg(NULL, i, DEF_NOTIFY_SERVERCHANGE, NULL, NULL, NULL, NULL);
		}
	}
}

long CGame::iGetExpLevel(unsigned long iExp)
{
 int i;

	for (i = 1; i < DEF_MAXEXPTABLE; i++)
	if ((m_iLevelExpTable[i] <= iExp) && (m_iLevelExpTable[i+1] > iExp)) return i;

	return 0;
}

void CGame::AdminOrder_CallGuard(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cName[11], cTargetName[11], cBuff[256], cNpcName[21], cNpcWaypoint[11];
 class  CStrTok * pStrTok;
 int i, iNamingValue, tX, tY;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelCallGaurd) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cNpcWaypoint, sizeof(cNpcWaypoint));
	ZeroMemory(cTargetName, sizeof(cTargetName));
	ZeroMemory(cNpcName, sizeof(cNpcName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   	
	if (token != NULL) {
		// token��횑 째챨 횄짚횈횄��쨩 쨘횘째징쨈횋횉횕째횚 쨍쨍쨉챕 쨩챌쩔챘��횣 ��횑쨍짠 
		if (strlen(token) > 10) 
			 memcpy(cTargetName, token, 10);
		else memcpy(cTargetName, token, strlen(token));
	 		
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cTargetName, 10) == 0)) {
			// 쨍챰횉짜 횆쨀쨍짱횇횒쨍짝 횄짙쩐횘쨈횢. 	
			
			if (memcmp(m_pClientList[i]->m_cMapName, "aresden", 7) == 0) 
				strcpy(cNpcName, "Guard-Aresden");			
			else if (memcmp(m_pClientList[i]->m_cMapName, "elvine", 6) == 0) 
				strcpy(cNpcName, "Guard-Elvine");
			else strcpy(cNpcName, "Guard-Neutral");  // <- ��횑째횒��쨘 쨍쨋��쨩��횑 쩐횈쨈횕쨔횉쨌횓 횁횩쨍쨀 째징쨉책쨍짝 쨩첵쩌쨘쩍횄횇짼쨈횢.
			
			iNamingValue = m_pMapList[ m_pClientList[i]->m_cMapIndex ]->iGetEmptyNamingValue();
			if (iNamingValue != -1) {
				// 쨈천��횑쨩처 ��횑 쨍횎쩔징 NPC쨍짝 쨍쨍쨉챕쩌철 쩐첩쨈횢. ��횑쨍짠��쨩 횉횘쨈챌횉횘 쩌철 쩐첩짹창 쨋짠쨔짰.
			
				// NPC쨍짝 쨩첵쩌쨘횉횗쨈횢.
				wsprintf(cName, "XX%d", iNamingValue);
				cName[0] = '_';
				cName[1] = m_pClientList[i]->m_cMapIndex+65;
				
				tX = (int)m_pClientList[i]->m_sX;
				tY = (int)m_pClientList[i]->m_sY;
				if (bCreateNewNpc(cNpcName, cName, m_pMapList[ m_pClientList[i]->m_cMapIndex ]->m_cName, 0, 0, DEF_MOVETYPE_RANDOM, 
					              &tX, &tY, cNpcWaypoint, NULL, NULL, -1, FALSE, TRUE) == FALSE) {
					// 쩍횉횈횖횉횩��쨍쨔횉쨌횓 쩔쨔쩐횪쨉횊 NameValue쨍짝 횉횠횁짝쩍횄횇짼쨈횢.
					m_pMapList[ m_pClientList[i]->m_cMapIndex ]->SetNamingValueEmpty(iNamingValue);
				} 
				else {
					// 째징쨉책쨍짝 쨩첵쩌쨘쩍횄횆횞쨈횢. 째첩째횦 쨍챰횉짜쨍짝 횉횘쨈챌횉횗쨈횢.
					bSetNpcAttackMode(cName, i, DEF_OWNERTYPE_PLAYER, TRUE);
				}
			}

			delete pStrTok;
			return;
		}

		// 횉철��챌 횁짖쩌횙횁횩��횑 쩐횈쨈횕쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERNOTONGAME, NULL, NULL, NULL, cTargetName);
	}

	delete pStrTok;
}

void CGame::AdminOrder_SummonDemon(int iClientH)
{
 char cName[21], cNpcName[21], cNpcWaypoint[11];	
 int iNamingValue, tX, tY;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == FALSE) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSummonDemon) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	iNamingValue = m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->iGetEmptyNamingValue();
	if (iNamingValue != -1) {
		// 쨈천��횑쨩처 ��횑 쨍횎쩔징 NPC쨍짝 쨍쨍쨉챕쩌철 쩐첩쨈횢. ��횑쨍짠��쨩 횉횘쨈챌횉횘 쩌철 쩐첩짹창 쨋짠쨔짰.

		// NPC쨍짝 쨩첵쩌쨘횉횗쨈횢.
		ZeroMemory(cNpcName, sizeof(cNpcName));
		strcpy(cNpcName, "Demon");	
		
		ZeroMemory(cName, sizeof(cName));
		wsprintf(cName, "XX%d", iNamingValue);
		cName[0] = '_';
		cName[1] = m_pClientList[iClientH]->m_cMapIndex+65;
		
		ZeroMemory(cNpcWaypoint, sizeof(cNpcWaypoint));

		tX = (int)m_pClientList[iClientH]->m_sX;
		tY = (int)m_pClientList[iClientH]->m_sY;
		if (bCreateNewNpc(cNpcName, cName, m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_cName, 0, (rand() % 9), 
			              DEF_MOVETYPE_RANDOM, &tX, &tY, cNpcWaypoint, NULL, NULL, -1, FALSE, FALSE) == FALSE) {
			// 쩍횉횈횖횉횩��쨍쨔횉쨌횓 쩔쨔쩐횪쨉횊 NameValue쨍짝 횉횠횁짝쩍횄횇짼쨈횢.
			m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->SetNamingValueEmpty(iNamingValue);
		} 
		else {
			// Admin Log
			wsprintf(G_cTxt, "Admin Order(%s): Summon Demon", m_pClientList[iClientH]->m_cCharName);
			PutAdminLogFileList(G_cTxt);
		}
	}

}

// v1.4311-3 횄횩째징 쩔챤쩔쨉��횣째징 쨩챌횇천��책��쨩 쩔쨔쩐횪횉횗쨈횢.
void CGame::AdminOrder_ReserveFightzone(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256];
 class  CStrTok * pStrTok;
 int iNum ;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;


	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelReserveFightzone) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	
	if( m_iFightzoneNoForceRecall == 0 ) {
		m_iFightzoneNoForceRecall = 1 ; 
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FIGHTZONERESERVE, -5, NULL, NULL, NULL);
	} else {
		m_iFightzoneNoForceRecall = 0 ; 
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FIGHTZONERESERVE, -4, NULL, NULL, NULL);
	}

	if (token == NULL) {
		delete pStrTok;
		return;
	}

	iNum = atoi(token) - 1;
			
	if ( m_iFightZoneReserve[iNum] != -1) {
		// Admin Log
		wsprintf(G_cTxt, "Admin Order(%s):  %d FightzoneReserved", m_pClientList[iClientH]->m_cCharName, iNum );
		PutAdminLogFileList(G_cTxt);
		
		m_iFightZoneReserve[iNum] = - 1 ;        // 쩔챤쩔쨉��횣째징 쩔쨔쩐횪횉횗 쨩챌횇천��책��쨘 -1 째짧��횑 쨉챕쩐챤째짙쨈횢.
												 // ��횑횁짝쨘횓횇횒 째챔쩌횙 쨈횢쨍짜 ��짱��첬쨈횂 쩔쨔쩐횪��횑 쨘횘째징쨈횋횉횕쨈횢.
		// 쩔챤쩔쨉��횣째징 쨩챌횇천��책 쩔쨔쩐횪쩔징 쩌쨘째첩횉횕쨈횂 째챈쩔챙 
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FIGHTZONERESERVE, iNum+1, NULL, NULL, NULL);
		
	}  else {	// 쩔챤쩔쨉��횣째징 쩔쨔쩐횪횉횗 쨩챌횇천��책��쨩 쨈횢쩍횄 쩔쨔쩐횪횉횕쨍챕 쩔쨔쩐횪��횑 횄챘쩌횘쨉횊쨈횢.
		wsprintf(G_cTxt, "Admin Order(%s):  %d Cancel FightzoneReserved", m_pClientList[iClientH]->m_cCharName, iNum );
		PutAdminLogFileList(G_cTxt);

		m_iFightZoneReserve[iNum] = 0 ;       
		// 쩔챤쩔쨉��횣째징 쨩챌횇천��책 쩔쨔쩐횪��쨩 횄챘쩌횘횉횕쨈횂 째챈쩔챙       -3 째짧��쨩 쨀횗째횥횁횠쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FIGHTZONERESERVE, -3, NULL, NULL, NULL);

	}
		
}


void CGame::AdminOrder_CloseConn(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cTargetName[11], cBuff[256];
 class  CStrTok * pStrTok;
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelGMCloseconn) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cTargetName, sizeof(cTargetName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	if (token != NULL) {
		// token��횑 째챨 횄짚횈횄��쨩 쨘횘째징쨈횋횉횕째횚 쨍쨍쨉챕 쨩챌쩔챘��횣 ��횑쨍짠 
		if (strlen(token) > 10) 
			 memcpy(cTargetName, token, 10);
		else memcpy(cTargetName, token, strlen(token));
		
		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cTargetName, 10) == 0)) {
			// 쨍챰횉짜 횆쨀쨍짱횇횒쨍짝 횄짙쩐횘쨈횢. 째짯횁짝쨌횓 횁짖쩌횙��쨩 짼첨쨈횂쨈횢.	
			if (m_pClientList[i]->m_bIsInitComplete == TRUE) {
				// v1.22 째짯횁짝 횁짖쩌횙 횁쩐쨌찼쨉횊 횇짭쨋처��횑쩐챨횈짰쨈횂 쨘챠쨍짰쨉첫 쩐횈��횕쨌짙쨉책쨌횓 횇횣쨌쨔횈첨횈짰쨉횊쨈횢.
				DeleteClient(i, TRUE, TRUE, TRUE, TRUE);
			}

			// Admin Log
			wsprintf(G_cTxt, "Admin Order(%s): Close Conn", m_pClientList[iClientH]->m_cCharName);
			PutAdminLogFileList(G_cTxt);

			delete pStrTok;
			return;
		}
		// 횉철��챌 횁짖쩌횙횁횩��횑 쩐횈쨈횕쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERNOTONGAME, NULL, NULL, NULL, cTargetName);
	}

	delete pStrTok;
}

void CGame::AdminOrder_CreateFish(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cItemName[21];
 class  CStrTok * pStrTok;
 class  CItem   * pItem;
 int tX, tY, iType;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelCreateFish) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	tX = tY = iType = 0;

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	
	token = pStrTok->pGet();
	if (token != NULL) {
		tX = atoi(token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		tY = atoi(token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		iType = atoi(token);
	}

	if ((tX != 0) && (tY != 0) && (iType != 0)) {
		// ��횑 횁횂횉짜쩔징 쨔째째챠짹창쨍짝 쨍쨍쨉챌쨈횢.
		pItem = new class CItem;
		if (pItem == NULL) {
			delete pStrTok;
			return;
		}
		ZeroMemory(cItemName, sizeof(cItemName));
		strcpy(cItemName, "Fish");
		if (_bInitItemAttr(pItem, cItemName) == TRUE) {
   			iCreateFish(m_pClientList[iClientH]->m_cMapIndex, tX, tY, iType, pItem, 1, 60000*20);
		}
		else delete pItem;
   	}

	delete pStrTok;
}

void CGame::AdminOrder_Teleport(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cMapName[256];
 class  CStrTok * pStrTok;
 int dX, dY;
 BOOL   bFlag;

	dX = dY = -1;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelTeleport) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	
	token = pStrTok->pGet();
	if (token != NULL) {
		ZeroMemory(cMapName, sizeof(cMapName));
		strcpy(cMapName, token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		dX = atoi(token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		dY = atoi(token);
	}

	bFlag = FALSE;
	if (strcmp("2ndmiddle", cMapName) == 0) bFlag = TRUE;
	if (strcmp("abaddon", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("arebrk11", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arebrk12", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arebrk21", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arebrk22", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arefarm", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arejail", cMapName) == 0) bFlag = TRUE;
	if (strcmp("aremidl", cMapName) == 0) bFlag = TRUE;
	if (strcmp("aremidr", cMapName) == 0) bFlag = TRUE;
	if (strcmp("aresden", cMapName) == 0) bFlag = TRUE;
	if (strcmp("aresdend1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("areuni", cMapName) == 0) bFlag = TRUE;
	if (strcmp("arewrhus", cMapName) == 0) bFlag = TRUE;
	if (strcmp("bisle", cMapName) == 0)   bFlag = TRUE;
	if (strcmp("bsmith_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("bsmith_1f", cMapName) == 0) bFlag = TRUE;
	if (strcmp("bsmith_2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("bsmith_2f", cMapName) == 0) bFlag = TRUE;
	if (strcmp("BtField", cMapName) == 0) bFlag = TRUE;
	if (strcmp("cath_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("cath_2", cMapName) == 0)      bFlag = TRUE;
	if (strcmp("cityhall_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("cityhall_2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("CmdHall_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("CmdHall_2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("default", cMapName) == 0) bFlag = TRUE;
	if (strcmp("dglv2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("dglv3", cMapName) == 0) bFlag = TRUE;
	if (strcmp("dglv4", cMapName) == 0) bFlag = TRUE;
	if (strcmp("druncncity", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("elvbrk11", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvbrk12", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvbrk21", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvbrk22", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvfarm", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvine", cMapName) == 0)  bFlag = TRUE;
	if (strcmp("elvined1", cMapName) == 0)    bFlag = TRUE;
	if (strcmp("elvjail", cMapName) == 0)    bFlag = TRUE;
	if (strcmp("elvmidl", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvmidr", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvuni", cMapName) == 0) bFlag = TRUE;
	if (strcmp("elvwrhus", cMapName) == 0) bFlag = TRUE;
	if (strcmp("fightzone1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("gldhall_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("gldhall_2", cMapName) == 0)   bFlag = TRUE;
	if (strcmp("GodH", cMapName) == 0)   bFlag = TRUE;
	if (strcmp("gshop_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("gshop_1f", cMapName) == 0) bFlag = TRUE;
	if (strcmp("gshop_2", cMapName) == 0)     bFlag = TRUE;
	if (strcmp("gshop_2f", cMapName) == 0)     bFlag = TRUE;
	if (strcmp("HRampart", cMapName) == 0)     bFlag = TRUE;
	if (strcmp("huntzone1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("huntzone2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("huntzone3", cMapName) == 0) bFlag = TRUE;
	if (strcmp("huntzone4", cMapName) == 0) bFlag = TRUE;
	if (strcmp("icebound", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("inferniaA", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("inferniaB", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("maze", cMapName) == 0) bFlag = TRUE; 
	if (strcmp("middled1n", cMapName) == 0) bFlag = TRUE;
	if (strcmp("middled1x", cMapName) == 0) bFlag = TRUE;
	if (strcmp("middleland", cMapName) == 0) bFlag = TRUE;
	if (strcmp("procella", cMapName) == 0) bFlag = TRUE;
	if (strcmp("resurr1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("resurr2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("toh1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("toh2", cMapName) == 0) bFlag = TRUE;
	if (strcmp("toh3", cMapName) == 0) bFlag = TRUE;
	if (strcmp("wrhus_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("wrhus_1f", cMapName) == 0) bFlag = TRUE;
	if (strcmp("wrhus_2", cMapName) == 0)     bFlag = TRUE;
	if (strcmp("wrhus_2f", cMapName) == 0)     bFlag = TRUE;
	if (strcmp("wzdtwr_1", cMapName) == 0) bFlag = TRUE;
	if (strcmp("wzdtwr_2", cMapName) == 0) bFlag = TRUE;

	if (bFlag == TRUE)
		RequestTeleportHandler(iClientH, "2   ", cMapName, dX, dY);
   	
	delete pStrTok;
}

int CGame::_iCalcPlayerNum(char cMapIndex, short dX, short dY, char cRadius)
{
 int ix, iy, iRet;
 class CTile * pTile;	

	// 횄쨀쨍짰 쩌횙쨉쨉쨍짝 쨀척��횑짹창 ��짠횉횠 횉횚쩌철쨍짝 횆횦횉횕횁철 쩐횎쨈횂쨈횢.
	if ((cMapIndex < 0)	|| (cMapIndex > DEF_MAXMAPS)) return 0;
	if (m_pMapList[cMapIndex] == NULL) return 0;

	iRet = 0;
	for (ix = dX - cRadius; ix <= dX + cRadius; ix++)
	for (iy = dY - cRadius; iy <= dY + cRadius; iy++) {
		if ( (ix < 0) || (ix >= m_pMapList[cMapIndex]->m_sSizeX) || 
			 (iy < 0) || (iy >= m_pMapList[cMapIndex]->m_sSizeY) ) {
			// 횁횂횉짜쨍짝 쨔첸쩐챤쨀짧쨔횉쨌횓 횄쨀쨍짰횉횕횁철 쩐횎쨈횂쨈횢.	
		}
		else {
			pTile = (class CTile *)(m_pMapList[cMapIndex]->m_pTile + ix + iy*m_pMapList[cMapIndex]->m_sSizeY);
			if ((pTile->m_sOwner != NULL) && (pTile->m_cOwnerClass == DEF_OWNERTYPE_PLAYER))
				iRet++;
		}
	}

	return iRet;
}


void CGame::WeatherProcessor()
{
char cPrevMode;
int i, j;
DWORD dwTime;
	dwTime = timeGetTime();
// SNOOPY for snow in winter / acomodado a estaciones de Argentina CENTU
SYSTEMTIME SysTime;

	for (i = 0; i < DEF_MAXMAPS; i++) 
	{
		if ((m_pMapList[i] != NULL) && (m_pMapList[i]->m_bIsFixedDayMode == FALSE)) 
		{	cPrevMode = m_pMapList[i]->m_cWhetherStatus;
			if (m_pMapList[i]->m_cWhetherStatus != NULL) 
			{	if ((dwTime - m_pMapList[i]->m_dwWhetherStartTime) > m_pMapList[i]->m_dwWhetherLastTime) 
					m_pMapList[i]->m_cWhetherStatus = NULL;
			}else 
			{	GetLocalTime(&SysTime);
				switch((short)SysTime.wMonth) {
				case 6: 
				case 7:
				case 8: // Winter
					if (iDice(1,100) == 13) 
					{	m_pMapList[i]->m_cWhetherStatus = iDice(3,2);
						m_pMapList[i]->m_dwWhetherStartTime = dwTime;
						m_pMapList[i]->m_dwWhetherLastTime  = 60000*3 + 60000*iDice(2,7);					
					}
					break;
				case 12:
				case 1: 
				case 2:  // Summer weather: rare thunderstorms heavy rain
					// Chrismas
					if (((short)SysTime.wMonth == 12) && ((short)SysTime.wDay >= 8)) 						
					{	m_pMapList[i]->m_cWhetherStatus = iDice(1,2)+4;
						m_pMapList[i]->m_dwWhetherStartTime = dwTime;
						m_pMapList[i]->m_dwWhetherLastTime  = 60000*3 + 60000*iDice(2,7);					
					}
					else
					{
						if (iDice(1,800) == 13) 
						{	m_pMapList[i]->m_cWhetherStatus = 3;
							m_pMapList[i]->m_dwWhetherStartTime = dwTime;
							m_pMapList[i]->m_dwWhetherLastTime  = 60000 + 60000*iDice(1,3);
						}
					}
					break;								
				default:   // Standard Weather
					if (iDice(1,300) == 13) 
					{	m_pMapList[i]->m_cWhetherStatus = iDice(1,3); 
						m_pMapList[i]->m_dwWhetherStartTime = dwTime;
						m_pMapList[i]->m_dwWhetherLastTime  = 60000*3 + 60000*iDice(1,7);
					}
					break;
				}
			}
			if (m_pMapList[i]->m_bIsSnowEnabled == TRUE) 
			{	m_pMapList[i]->m_cWhetherStatus = iDice(1,3)+3;
				m_pMapList[i]->m_dwWhetherStartTime = dwTime;
				m_pMapList[i]->m_dwWhetherLastTime  = 60000*3 + 60000*iDice(1,7);
			}

			if (cPrevMode != m_pMapList[i]->m_cWhetherStatus) 
			{	m_pMapList[i]->m_cThunder = 0;
				for (j = 1; j < DEF_MAXCLIENTS; j++) 
				if ((m_pClientList[j] != NULL) && (m_pClientList[j]->m_bIsInitComplete == TRUE) && (m_pClientList[j]->m_cMapIndex == i)) 
					SendNotifyMsg(NULL, j, DEF_NOTIFY_WHETHERCHANGE, m_pMapList[i]->m_cWhetherStatus, NULL, NULL, NULL);
			}else
			{	if (m_pMapList[i]->m_cThunder == 2) DoAbaddonThunderDamageHandler(i);
			}
		} //If
	} //for Loop
}

int CGame::iGetPlayerRelationship(int iClientH, int iOpponentH)
{
 int iRet;
	
	if (m_pClientList[iClientH] == NULL) return 0;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return 0;

	if (m_pClientList[iOpponentH] == NULL) return 0;
	if (m_pClientList[iOpponentH]->m_bIsInitComplete == FALSE) return 0;

	iRet = 0;

	if (m_pClientList[iClientH]->m_iPKCount != 0) {
		// 쨘쨩��횓��횑 쨔체횁횏��횣��횑횉횕쨍챕 쨩처쨈챘쨔챈��횑 쨍쨋��쨩��횑 째째��쨘 째챈쩔챙 ��짠횉첫. 쨈횢쨍짙쨍챕 ��청 
		if ((memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iOpponentH]->m_cLocation, 10) == 0) &&
			(memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) != 0) && (memcmp(m_pClientList[iOpponentH]->m_cLocation, "NONE", 4) != 0)) {
			 iRet = 7; // ��짠횉첫 
		}
		else iRet = 2; // ��청   
	}
	else if (m_pClientList[iOpponentH]->m_iPKCount != 0) {
		// 쨩처쨈챘쨔챈��횑 쨔체횁횏��횣��횑횉횕쨍챕
		if ((memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iOpponentH]->m_cLocation, 10) == 0) &&
			(memcmp(m_pClientList[iClientH]->m_cLocation, "NONE", 4) != 0)) 
			 iRet = 6; // 쨍쨋��쨩��횑 째째��쨍쨍챕 PK
		else iRet = 2; // 쨈횢쨍짙쨍챕 짹횞쨀횋 ��청 
	}
	else {
		if (m_pClientList[iClientH]->m_cSide != m_pClientList[iOpponentH]->m_cSide) {
			if ((m_pClientList[iClientH]->m_cSide != 0) && (m_pClientList[iOpponentH]->m_cSide != 0)) {
				// 쨉횗 쨈횢 0(Traveler)��횑 쩐횈쨈횕쨍챕 ��청��횑쨈횢.
				iRet = 2;
			}
			else {
				iRet = 0;
			}
		}	
		else {
			// 쩐횈짹쨘��횑쨈횢. 짹챈쨉책쩔첩쩔짤쨘횓쨍짝 횈횉쨈횥.
			if ((memcmp(m_pClientList[iClientH]->m_cGuildName, m_pClientList[iOpponentH]->m_cGuildName, 20) == 0) &&
				(memcmp(m_pClientList[iClientH]->m_cGuildName, "NONE", 4) != 0) ) {
				// 짹챈쨉책 ��횑쨍짠��횑 째째쨈횢. 
				if (m_pClientList[iOpponentH]->m_iGuildRank == 0)
					 iRet = 5;	// 짹챈쨉책 쨌짤횇짤째징 0. 짹챈쨉책쨍쨋쩍쨘횇횒��횑쨈횢.
				else iRet = 3;	// 째째��쨘 짹챈쨉책쩔첩
			}
			else 
			if ((memcmp(m_pClientList[iClientH]->m_cLocation, m_pClientList[iOpponentH]->m_cLocation, 10) == 0) &&
				(memcmp(m_pClientList[iClientH]->m_cGuildName, "NONE", 4) != 0) &&
				(memcmp(m_pClientList[iOpponentH]->m_cGuildName, "NONE", 4) != 0) &&
				(memcmp(m_pClientList[iClientH]->m_cGuildName, m_pClientList[iOpponentH]->m_cGuildName, 20) != 0)) {
				// 짹챈쨉책 ��짠횆징쨈횂 째째째챠 짹챈쨉책 ��횑쨍짠��횑 쨈횢쨍짙쨈횢.
				iRet = 4; // 쨈횢쨍짜 짹챈쨉책쩔첩 
			}
			else iRet = 1; // 짹횞쨀횋 째째��쨘횈챠 
		}
	}

	return iRet;
}

int CGame::iGetPlayerABSStatus(int iWhatH, int iRecvH)
{
	int iRet;

	if (m_pClientList[iWhatH] == NULL) return 0;
	if (m_pClientList[iRecvH] == NULL) return 0;

	iRet = 0;


		if (m_pClientList[iWhatH]->m_iPKCount != 0) {
			iRet = 8;
		}

		if (m_pClientList[iWhatH]->m_cSide != 0) {
			iRet = iRet | 4;
		}

		if (m_pClientList[iWhatH]->m_cSide == 1) {
			iRet = iRet | 2;
		}

		if (m_pClientList[iWhatH]->m_bIsPlayerCivil == TRUE)
			iRet = iRet | 1;

		return iRet;
}

int CGame::_iForcePlayerDisconect(int iNum)
{
 int i, iCnt;

	iCnt = 0;
	for (i = 1; i < DEF_MAXCLIENTS; i++)
	if (m_pClientList[i] != NULL) {
		if (m_pClientList[i]->m_bIsInitComplete == TRUE)
			 DeleteClient(i, TRUE, TRUE);
		else DeleteClient(i, FALSE, FALSE);
		iCnt++;
		if (iCnt >= iNum) break;
	}

	return iCnt;
}

void CGame::SpecialEventHandler()
{
 DWORD dwTime;
 
	// 횈짱쨘째횉횗 ��횑쨘짜횈짰쨍짝 쨩첵쩌쨘횉횗쨈횢. 
	dwTime = timeGetTime();

	if ((dwTime - m_dwSpecialEventTime) < DEF_SPECIALEVENTTIME) return; // DEF_SPECIALEVENTTIME
	m_dwSpecialEventTime  = dwTime;
	m_bIsSpecialEventTime = TRUE;
	
	switch (iDice(1,180)) {
	case 98: m_cSpecialEventType = 2; break; // 쨉짜쨍처 횊짚��쨘 ��짱쨈횕횆횥��횑 쨀짧쩔횄 째징쨈횋쩌쨘��쨘 30쨘횖쩔징 1쨔첩 1/30
	default: m_cSpecialEventType = 1; break;
	}
}

void CGame::AdminOrder_CheckIP(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cIP[21], cInfoString[500];
 class  CStrTok * pStrTok;
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelCheckIP) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	
	if (token != NULL) {
		// token��횑 IP address��횑쨈횢. 
		ZeroMemory(cIP, sizeof(cIP));
		strcpy(cIP, token);

		for (i = 1; i < DEF_MAXCLIENTS; i++) 
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cIPaddress, cIP, strlen(cIP)) == 0)) {
			// 쩔채짹쨍횉횗 횁횜쩌횘쩔횒 ��횕횆징횉횕쨈횂 횇짭쨋처��횑쩐챨횈짰 쨔횩째횩. 
			ZeroMemory(cInfoString, sizeof(cInfoString));
			wsprintf(cInfoString, "Name(%s/%s) Loc(%s: %d %d) Level(%d:%d) Init(%d) IP(%s)", 
				     m_pClientList[i]->m_cAccountName, m_pClientList[i]->m_cCharName, m_pClientList[i]->m_cMapName, 
					 m_pClientList[i]->m_sX, m_pClientList[i]->m_sY, 
					 m_pClientList[i]->m_iLevel, NULL,
					 m_pClientList[i]->m_bIsInitComplete, m_pClientList[i]->m_cIPaddress);

			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_IPACCOUNTINFO, NULL, NULL, NULL, cInfoString);
		}
	}

	
	delete pStrTok;
}

void CGame::ToggleSafeAttackModeHandler(int iClientH) //v1.1
{
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;

	// 쩐횊��체 째첩째횦 쨍챨쨉책쨍짝 횇채짹횤횉횗쨈횢. 
	if (m_pClientList[iClientH]->m_bIsSafeAttackMode == TRUE) 
		 m_pClientList[iClientH]->m_bIsSafeAttackMode = FALSE;
	else m_pClientList[iClientH]->m_bIsSafeAttackMode = TRUE;

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SAFEATTACKMODE, NULL, NULL, NULL, NULL);
}

void CGame::ForceDisconnectAccount(char *pAccountName, WORD wCount)
{
 int i;

	// 횁횩쨘쨔쨉횊 째챔횁짚��쨩 째짰째챠��횜쨈횂 횆쨀쨍짱횇횒쨍짝 쨩챔횁짝횉횗쨈횢. 
	for (i = 1; i < DEF_MAXCLIENTS; i++)
	if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cAccountName, pAccountName, 10) == 0)) {
		wsprintf(G_cTxt, "<%d> Force disconnect account: CharName(%s) AccntName(%s) Count(%d)", i, m_pClientList[i]->m_cCharName, m_pClientList[i]->m_cAccountName, wCount);
		PutLogList(G_cTxt);
		
		//v1.4312
		SendNotifyMsg(NULL, i, DEF_NOTIFY_FORCEDISCONN, wCount, NULL, NULL, NULL);
	}
}

void CGame::AdminOrder_Polymorph(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256]; 
 class  CStrTok * pStrTok;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelPolymorph) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token != NULL) {
		if (memcmp(token, "off", 3) == 0 || memcmp(token, "0", 1) == 0)
			m_pClientList[iClientH]->m_sType = m_pClientList[iClientH]->m_sOriginalType;

		else if (memcmp(token, "Slime", 5) == 0)
			m_pClientList[iClientH]->m_sType = 10;

		else if (memcmp(token, "Skeleton", 8) == 0)
			m_pClientList[iClientH]->m_sType = 11;

		else if (memcmp(token, "Stone-Golem", 11) == 0)
			m_pClientList[iClientH]->m_sType = 12;

		else if (memcmp(token, "Cyclops", 7) == 0)
			m_pClientList[iClientH]->m_sType = 13;

		else if (memcmp(token, "Orc", 3) == 0)
			m_pClientList[iClientH]->m_sType = 14;

		else if (memcmp(token, "Giant-Ant", 9) == 0)
			m_pClientList[iClientH]->m_sType = 16;

		else if (memcmp(token, "Scorpion", 8) == 0)
			m_pClientList[iClientH]->m_sType = 17;

		else if (memcmp(token, "Zombie", 6) == 0)
			m_pClientList[iClientH]->m_sType = 18;

		else if (memcmp(token, "Amphis", 6) == 0)
			m_pClientList[iClientH]->m_sType = 22;

		else if (memcmp(token, "Clay-Golem", 10) == 0)
			m_pClientList[iClientH]->m_sType = 23;

		else if (memcmp(token, "Hellbound", 9) == 0)
			m_pClientList[iClientH]->m_sType = 27;

		else if (memcmp(token, "Troll", 5) == 0)
			m_pClientList[iClientH]->m_sType = 28;

		else if (memcmp(token, "Ogre", 4) == 0)
			m_pClientList[iClientH]->m_sType = 29;

		else if (memcmp(token, "Liche", 5) == 0)
			m_pClientList[iClientH]->m_sType = 30;

		else if (memcmp(token, "Demon", 5) == 0)
			m_pClientList[iClientH]->m_sType = 31;

		else if (memcmp(token, "Unicorn", 7) == 0)
			m_pClientList[iClientH]->m_sType = 32;

		else if (memcmp(token, "WereWolf", 8) == 0)
			m_pClientList[iClientH]->m_sType = 33;

		else if (memcmp(token, "Stalker", 7) == 0)
			m_pClientList[iClientH]->m_sType = 48;

		else if (memcmp(token, "Hellclaw", 8) == 0)
			m_pClientList[iClientH]->m_sType = 49;

		else if (memcmp(token, "Tigerworm", 8) == 0)
			m_pClientList[iClientH]->m_sType = 50;

		else if (memcmp(token, "Gagoyle", 7) == 0)
			m_pClientList[iClientH]->m_sType = 52;

		else if (memcmp(token, "Beholder", 8) == 0)
			m_pClientList[iClientH]->m_sType = 53;

		else if (memcmp(token, "Dark-Elf", 8) == 0)
			m_pClientList[iClientH]->m_sType = 54;

		else if (memcmp(token, "Rabbit", 6) == 0)
			m_pClientList[iClientH]->m_sType = 55;

		else if (memcmp(token, "Cat", 3) == 0)
			m_pClientList[iClientH]->m_sType = 56;

		else if (memcmp(token, "Giant-Frog", 10) == 0)
			m_pClientList[iClientH]->m_sType = 57;

		else if (memcmp(token, "Mountain-Giant", 14) == 0)
			m_pClientList[iClientH]->m_sType = 58;

		else if (memcmp(token, "Ettin", 5) == 0)
			m_pClientList[iClientH]->m_sType = 59;

		else if (memcmp(token, "Cannibal-Plant", 13) == 0)
			m_pClientList[iClientH]->m_sType = 60;

		else if (memcmp(token, "Rudolph", 7) == 0)
			m_pClientList[iClientH]->m_sType = 61;

		else if (memcmp(token, "DireBoar", 8) == 0)
			m_pClientList[iClientH]->m_sType = 62;

		else if (memcmp(token, "Frost", 5) == 0)
			m_pClientList[iClientH]->m_sType = 63;

		else if (memcmp(token, "Crops", 5) == 0)
			m_pClientList[iClientH]->m_sType = 64;

		else if (memcmp(token, "Ice-Golem", 9) == 0)
			m_pClientList[iClientH]->m_sType = 65;

		else if (memcmp(token, "Barlog", 6) == 0)
			m_pClientList[iClientH]->m_sType = 70;

		else if (memcmp(token, "Centaurus", 9) == 0)
			m_pClientList[iClientH]->m_sType = 71;

		else if (memcmp(token, "Claw-Turtle", 11) == 0)
			m_pClientList[iClientH]->m_sType = 72;

		else if (memcmp(token, "Giant-Crayfish", 14) == 0)
			m_pClientList[iClientH]->m_sType = 74;

		else if (memcmp(token, "Giant-Lizard", 12) == 0)
			m_pClientList[iClientH]->m_sType = 75;

		else if (memcmp(token, "Giant-Plant", 11) == 0)
			m_pClientList[iClientH]->m_sType = 76;

		else if (memcmp(token, "MasterMage-Orc", 14) == 0)
			m_pClientList[iClientH]->m_sType = 77;

		else if (memcmp(token, "Minotaurs", 9) == 0)
			m_pClientList[iClientH]->m_sType = 78;

		else if (memcmp(token, "Nizie", 5) == 0)
			m_pClientList[iClientH]->m_sType = 79;

		else if (memcmp(token, "Tentocle", 8) == 0)
			m_pClientList[iClientH]->m_sType = 80;
	}
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
	delete pStrTok;
}

void CGame::AdminOrder_SetInvi(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256]; 
 class  CStrTok * pStrTok;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSetInvis) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token != NULL) {
		// ��횑 째짧��횑 쨔짰��횣 '1'��횑쨍챕 횇천쨍챠��쨍쨌횓 쩌쩌횈짰. '0'��횑쨍챕 횉횠횁짝 
		if (token[0] == '1') SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, TRUE);
		else if (token[0] == '0') SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, FALSE);
	}

	delete pStrTok;
}

BOOL CGame::bOnClose()
{
	if (m_bIsServerShutdowned == FALSE) 
		if (MessageBox(NULL, "Player data not saved! Shutdown server now?", m_cServerName, MB_ICONEXCLAMATION | MB_YESNO) == IDYES) return TRUE;
		else return FALSE;
	else return TRUE;
}

void CGame::LocalSavePlayerData(int iClientH)
{
 char * pData, * cp, cFn[256], cDir[256], cTxt[256], cCharDir[256];
 int    iSize;
 FILE * pFile;
 SYSTEMTIME SysTime;

	// 쨌횓짹횞 쩌짯쨔철쨌횓��횉 쩔짭째찼��횑 횁쩐쨌찼쨉횉쩐챤 ��횙쩍횄쨌횓 째횚��횙쩌짯쨔철 쨀쨩��횉 횈첬쨈천쩔징 ��첬��책횉횗쨈횢. 
	if (m_pClientList[iClientH] == NULL) return;
 
	pData = new char[30000];
	if (pData == NULL) return;
	ZeroMemory(pData, 30000);

	cp = (char *)(pData);
	iSize = _iComposePlayerDataFileContents(iClientH, cp);

	GetLocalTime(&SysTime);
	ZeroMemory(cCharDir, sizeof(cDir));
	wsprintf(cCharDir, "Character_%d_%d_%d_%d", SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);

	ZeroMemory(cDir, sizeof(cDir));
	ZeroMemory(cFn, sizeof(cFn));
	strcat(cFn,cCharDir);
	strcat(cFn,"\\");
	strcat(cFn,"\\");					  
	wsprintf(cTxt, "AscII%d", (unsigned char)m_pClientList[iClientH]->m_cCharName[0]);
	strcat(cFn, cTxt);
	strcpy(cDir, cFn);
	strcat(cFn,"\\");
	strcat(cFn,"\\");					  
	strcat(cFn, m_pClientList[iClientH]->m_cCharName);
	strcat(cFn, ".txt");

	// 쨉챨쨌쨘횇채쨍짰쨍짝 쨍쨍쨉챌쨈횢.
	_mkdir(cCharDir);
	_mkdir(cDir);

	if (iSize == 0) {
		PutLogList("(!) Character data body empty: Cannot create & save temporal player data file.");
		delete[] pData;
		return;
	}

	pFile = fopen(cFn, "wt");
	if (pFile == NULL) {
		wsprintf(cTxt, "(!) Cannot create temporal player data file : Name(%s)", cFn);
		PutLogList(cTxt);
	}
	else {
		wsprintf(cTxt, "(!) temporal player data file saved : Name(%s)", cFn);
		PutLogList(cTxt);
		fwrite(cp, iSize, 1, pFile);
		fclose(pFile);
	}
	
	delete[] pData;
}

void CGame::CheckFireBluring(char cMapIndex, int sX, int sY)
{
 int ix, iy, iItemNum;
  short sSpr, sSprFrame;
 char  cItemColor;
 class CItem * pItem;

	for (ix = sX -1; ix <= sX +1; ix++)
	for (iy = sY -1; iy <= sY +1; iy++) {
		// 쨍쨍쩐횪 ��횑 ��짠횆징쩔징 쨔횩횊짯쩌쨘 쩐횈��횑횇횤��횑 ��횜쨈횢쨍챕 횁철쩔챙째챠 쨘횘 쩔��쨘챗횁짠횈짰쨍짝 쨀천쨈횂쨈횢.	
		iItemNum = m_pMapList[cMapIndex]->iCheckItem(ix, iy);
				
		switch (iItemNum) {
		case 355: 
			// 쩌짰횇쨘��횑쨈횢. 쩐횈��횑횇횤��쨩 횁철쩔챙째챠 쨘횘��쨩 쨍쨍쨉챌쨈횢.
			pItem = m_pMapList[cMapIndex]->pGetItem(ix, iy, &sSpr, &sSprFrame, &cItemColor);
			if (pItem != NULL) delete pItem;
			iAddDynamicObjectList(NULL, NULL, DEF_DYNAMICOBJECT_FIRE, cMapIndex, ix, iy, 6000);	

			SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_SETITEM, cMapIndex,
				                        ix, iy, sSpr, sSprFrame, cItemColor);
			break;
		}
	}
}

void CGame::AdminOrder_GetNpcStatus(int iClientH, char * pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cNpcName[256];
 class  CStrTok * pStrTok;
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelGetNpcStatus) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	if (token != NULL) {
		ZeroMemory(cNpcName, sizeof(cNpcName));
		strcpy(cNpcName, token);
	}

	for (i = 0; i < DEF_MAXNPCS; i++) 
	if (m_pNpcList[i] != NULL) {
		if (memcmp(m_pNpcList[i]->m_cName, cNpcName, 5) == 0) {
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINIFO, 1, i, NULL, NULL);	
		}
	}

	delete pStrTok;
}

static int ___iCAB5[]  = {0,0, 0,1,2};
static int ___iCAB6[]  = {0,0, 0,0,0};
static int ___iCAB7[]  = {0,0, 1,2,3};
static int ___iCAB8[]  = {0,0, 1,3,5};
static int ___iCAB9[]  = {0,0, 2,4,8};
static int ___iCAB10[] = {0,0, 1,2,3};

int CGame::iGetComboAttackBonus(int iSkill, int iComboCount)
{
	if (iComboCount <= 1) return 0;
	if (iComboCount > 6) return 0;
	switch (iSkill) {
	case 5:
		return ___iCAB5[iComboCount];
	case 6:
		return ___iCAB6[iComboCount];
	case 7:
		return ___iCAB7[iComboCount];
	case 8:
		return ___iCAB8[iComboCount];
	case 9:
		return ___iCAB9[iComboCount];
	case 10:
		return ___iCAB10[iComboCount];
	case 14:
		return ___iCAB6[iComboCount];
	case 21:
		return ___iCAB10[iComboCount];
	}

	return 0;
}

void CGame::_BWM_Init(int iClientH, char *pData)
{
	if (m_pClientList[iClientH] == NULL) return;

	m_pClientList[iClientH]->m_bIsBWMonitor = TRUE;
	wsprintf(G_cTxt, "(*) BWMonitor(%d) registered.", iClientH);
	PutLogList(G_cTxt);
}

void CGame::_BWM_Command_Shutup(char *pData)
{
 char * cp, cName[11];
 int i;

	cp = (char *)(pData + 16);

	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);

	for (i = 1; i < DEF_MAXCLIENTS; i++) 
	if (m_pClientList[i] != NULL) {
		if (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0) {
			m_pClientList[i]->m_iTimeLeft_ShutUp = 20*3*10; // 1��횑 3횄횎쨈횢. 20��횑쨍챕 1쨘횖 쩔책��쨩 횉횕쨍챕 쨔짬횁쨋째횉 횈채쨀횓횈쩌 10쨘횖  
			SendNotifyMsg(NULL, i, DEF_NOTIFY_PLAYERSHUTUP, 20*3*10, NULL, NULL, cName);
			
			// Admin Log
			wsprintf(G_cTxt, "BWordMonitor shutup(%s %d)", cName, 20*3*10);
			PutAdminLogFileList(G_cTxt);

			break;
		}
	}
}

// centu - added majestic level to calculate max hp/sp/mp
int CGame::iGetMaxHP(int iClientH, BOOL bBloodEffect)
{
	int iRet;
	if (m_pClientList[iClientH] == NULL) return 0;
	// Changed to this due to patch in client that in case of odd level and Str gives 1 more HP.
	iRet = (3*m_pClientList[iClientH]->m_iVit) + (2 * (m_pClientList[iClientH]->m_iLevel + m_pClientList[iClientH]->m_iMajesticLevel)) + ((m_pClientList[iClientH]->m_iStr+m_pClientList[iClientH]->m_iAngelicStr)/2);

	if ((bBloodEffect == TRUE) && (m_pClientList[iClientH]->m_iSideEffect_MaxHPdown != 0))
		iRet -= (iRet/m_pClientList[iClientH]->m_iSideEffect_MaxHPdown);

	return iRet;
}

int CGame::iGetMaxMP(int iClientH)
{

	if (m_pClientList[iClientH] == NULL) return 0;

	return (2*(m_pClientList[iClientH]->m_iMag+m_pClientList[iClientH]->m_iAngelicMag)) + (2 * (m_pClientList[iClientH]->m_iLevel + m_pClientList[iClientH]->m_iMajesticLevel)) + ((m_pClientList[iClientH]->m_iInt+m_pClientList[iClientH]->m_iAngelicInt)/2);

}

int CGame::iGetMaxSP(int iClientH)
{

	if (m_pClientList[iClientH] == NULL) return 0;

	return (2*(m_pClientList[iClientH]->m_iStr+m_pClientList[iClientH]->m_iAngelicStr)) + (2*(m_pClientList[iClientH]->m_iLevel + m_pClientList[iClientH]->m_iMajesticLevel));
	
}

void CGame::OnSubLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
 UINT iTmp;
 int iLogSockH, iRet;

	iTmp = (WM_ONLOGSOCKETEVENT + 1);
	iLogSockH = message - iTmp;
	
	if (m_pSubLogSock[iLogSockH] == NULL) return;

	iRet = m_pSubLogSock[iLogSockH]->iOnSocketEvent(wParam, lParam);

	switch (iRet) {
	case DEF_XSOCKEVENT_UNSENTDATASENDCOMPLETE:
		wsprintf(G_cTxt, "(!!!) Log Socket Connection Established Log#(%d) Address:%s  Port:%d", iLogSockH, m_cLogServerAddr, m_iLogServerPort);
		PutLogList(G_cTxt);

		m_bIsSubLogSockAvailable[iLogSockH] = TRUE;
		m_iSubLogSockActiveCount++;
		break;

	case DEF_XSOCKEVENT_CONNECTIONESTABLISH:
		// 쨌횓짹횞쩌짯쨔철쨌횓��횉 쩔짭째찼��횑 ��횑쨌챌쩐챤 횁쨀쨈횢.
		wsprintf(G_cTxt, "(!!!) Sub-log-socket(%d) connected.", iLogSockH);
		PutLogList(G_cTxt);
		break;
	
	case DEF_XSOCKEVENT_READCOMPLETE:
		// 쨍횧쩍횄횁철째징 쩌철쩍횇쨉횉쩐첬쨈횢. 
		OnSubLogRead(iLogSockH);
		break;
	
	case DEF_XSOCKEVENT_BLOCK:
		wsprintf(G_cTxt, "(!!!) Sub-log-socket(%d) BLOCKED!", iLogSockH);
		PutLogList(G_cTxt);
		break;
	
	case DEF_XSOCKEVENT_CONFIRMCODENOTMATCH:
	case DEF_XSOCKEVENT_MSGSIZETOOLARGE:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		// 쩌횘횆횕��횑 쨈횦횉청쨈횢.
		delete m_pSubLogSock[iLogSockH];
		m_pSubLogSock[iLogSockH] = NULL;
		m_bIsSubLogSockAvailable[iLogSockH] = FALSE;
		
		m_iSubLogSockFailCount++;
		m_iSubLogSockActiveCount--;

		wsprintf(G_cTxt, "(!!!) Sub-log-socket(%d) connection lost!", iLogSockH);
		PutLogList(G_cTxt);
		PutLogFileList(G_cTxt);
		
		m_pSubLogSock[iLogSockH] = new class XSocket(m_hWnd, DEF_SERVERSOCKETBLOCKLIMIT);
		m_pSubLogSock[iLogSockH]->bConnect(m_cLogServerAddr, m_iLogServerPort, (WM_ONLOGSOCKETEVENT + iLogSockH + 1));
		m_pSubLogSock[iLogSockH]->bInitBufferSize(DEF_MSGBUFFERSIZE);

		wsprintf(G_cTxt, "(!!!) Try to reconnect sub-log-socket(%d)... Addr:%s  Port:%d", iLogSockH, m_cLogServerAddr, m_iLogServerPort);
		PutLogList(G_cTxt);
		
		break;
	}
}

void CGame::OnSubLogRead(int iIndex)
{
 DWORD dwMsgSize;
 char * pData, cKey;

	pData = m_pSubLogSock[iIndex]->pGetRcvDataPointer(&dwMsgSize, &cKey);

	if (bPutMsgQuene(DEF_MSGFROM_LOGSERVER, pData, dwMsgSize, NULL, cKey) == FALSE) {
		// 쨍횧쩍횄횁철 횇짜쩔징 ��횑쨩처��횑 쨩첵째책쨈횢. 횆징쨍챠��청��횓 쩔징쨌짱.
		PutLogList("@@@@@@ CRITICAL ERROR in MsgQuene!!! @@@@@@");
	}	
}

BOOL CGame::_bCheckSubLogSocketIndex()
{
 int  iCnt;
 BOOL bLoopFlag;

	// 쨍횧쩍횄횁철쨍짝 쨘쨍쨀쩐 Sub-log-socket ��횓쨉짝쩍쨘 ��체횁첩 
	m_iCurSubLogSockIndex++;
	if (m_iCurSubLogSockIndex >= DEF_MAXSUBLOGSOCK) m_iCurSubLogSockIndex = 0;

	iCnt = 0;
	bLoopFlag = FALSE;
	while (bLoopFlag == FALSE) {
		if ((m_pSubLogSock[m_iCurSubLogSockIndex] != NULL) && (m_bIsSubLogSockAvailable[m_iCurSubLogSockIndex] == TRUE)) 
			 bLoopFlag = TRUE;
		else m_iCurSubLogSockIndex++;

		iCnt++;
		if (iCnt >= DEF_MAXSUBLOGSOCK) {
			// 쨘쨍쨀쩐 쩌철 ��횜쨈횂 Sub-log-socket��횑 횉횕쨀짧쨉쨉 쩐첩쨈횢. 째짯횁짝 쩌횏쨈횢쩔챤 쨍챨쨉책쨌횓 ��체횊짱 
			if (m_bOnExitProcess == FALSE) {
				m_cShutDownCode      = 3;
				m_bOnExitProcess     = TRUE;
				m_dwExitProcessTime  = timeGetTime();
				// 째횚��횙 쩌짯쨔철 쩌횏쨈횢쩔챤��횑 쩍횄��횤쨉횉쨍챕 쨈천��횑쨩처��횉 횇짭쨋처��횑쩐챨횈짰 횁짖쩌횙��횑 째횇쨘횓쨉횊쨈횢. 
				PutLogList("(!) GAME SERVER SHUTDOWN PROCESS BEGIN(by Log-server connection Lost)!!!");
			}
			return FALSE;
		}
	}

	return TRUE;
}

void CGame::_CheckGateSockConnection()
{
	// ��횑쨔횑 쩌짯쨔철째징 쩌횏쨈횢쩔챤쨉횊 쨩처횇횂쨋처쨍챕 횆짬쩔챤횈횄 횉횘 횉횎쩔채째징 쩐첩쨈횢.
	if (m_bIsServerShutdowned == TRUE) return;

	if (m_iGateSockConnRetryTimes != 0) {
		wsprintf(G_cTxt, "(!!!) Gate-socket connection counting...%d", m_iGateSockConnRetryTimes); 
		PutLogList(G_cTxt);
		m_iGateSockConnRetryTimes++;
	}

	// 60횄횎째짙 Gate-socket��횑 쩔짭째찼쨉횉횁철 쩐횎쩐횘쨈횢쨍챕 ��횣쨉쩔 ��챌쨘횓횈횄 쨍챨쨉책쨌횓 쨉챕쩐챤째짙쨈횢.
	if (m_iGateSockConnRetryTimes > 20) {
		// 째횚��횑횈짰 쩌짯쨔철쩔횒��횉 쩔짭째찼��횑 짼첨째책��쨍쨔횉쨌횓 쨘쨔짹쨍횉횘 쩌철 쩐첩쨈횢. ��횣쨉쩔��쨍쨌횓 쩌짯쨔철쨍짝 쩌횏쨈횢쩔챤횉횗쨈횢.
		if (m_bOnExitProcess == FALSE) {
			m_iFinalShutdownCount = 1;
			m_bOnExitProcess     = TRUE;
			m_dwExitProcessTime  = timeGetTime();
			// 째횚��횙 쩌짯쨔철 쩌횏쨈횢쩔챤��횑 쩍횄��횤쨉횉쨍챕 쨈천��횑쨩처��횉 횇짭쨋처��횑쩐챨횈짰 횁짖쩌횙��횑 째횇쨘횓쨉횊쨈횢. 
			PutLogList("(!) GAME SERVER SHUTDOWN PROCESS BEGIN(by gate-server connection Lost)!!!");
		}
	}
}

void CGame::AdminOrder_SetAttackMode(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256]; 
 class  CStrTok * pStrTok;
 int    i;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;
	

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSetAttackMode) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	
	if (token != NULL) {
		// ��횑 째짧��횑 쨔짰��횣 '1'��횑쨍챕 째첩째횦 쨍챨쨉책 쩌쨀횁짚. 0��횑쨍챕 째첩째횦 쨍챨쨉책 횉횠횁짝  
		if (token[0] == '1') {
			m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_bIsAttackEnabled = TRUE;
			// 째짖 횇짭쨋처��횑쩐챨횈짰쨉챕쩔징째횚 째첩째횦쨍챨쨉책 ��짱횊쩔��횙��쨩 쩐횏쨍째쨈횢.
			for (i = 1; i < DEF_MAXCLIENTS; i++) 
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE) && (m_pClientList[i]->m_cMapIndex == m_pClientList[iClientH]->m_cMapIndex)) 
				SendNotifyMsg(NULL, i, DEF_NOTIFY_GLOBALATTACKMODE, (int)m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_bIsAttackEnabled, NULL, NULL, NULL);	
		}
		else if (token[0] == '0') {
			m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_bIsAttackEnabled = FALSE;
			
			// 째짖 횇짭쨋처��횑쩐챨횈짰쨉챕쩔징째횚 째첩째횦쨍챨쨉책 쨔짬횊쩔��횙��쨩 쩐횏쨍째쨈횢.
			for (i = 1; i < DEF_MAXCLIENTS; i++) 
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE) && (m_pClientList[i]->m_cMapIndex == m_pClientList[iClientH]->m_cMapIndex)) 
				SendNotifyMsg(NULL, i, DEF_NOTIFY_GLOBALATTACKMODE, (int)m_pMapList[ m_pClientList[iClientH]->m_cMapIndex ]->m_bIsAttackEnabled, NULL, NULL, NULL);	
		}
	}

	delete pStrTok;
}


void CGame::AdminOrder_UnsummonAll(int iClientH)
{
 int i;

	if (m_pClientList[iClientH] == NULL) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelUnsummonAll) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	// 쩌횘횊짱쨉횊 쨍챨쨉챌 쨍처쩍쨘횇횒쨍짝 횁횞��횓쨈횢. 
	for (i = 1; i < DEF_MAXNPCS; i++)
	if (m_pNpcList[i] != NULL) {
		if ((m_pNpcList[i]->m_bIsSummoned == TRUE) && (m_pNpcList[i]->m_bIsKilled == FALSE)) 
			NpcKilledHandler(iClientH, DEF_OWNERTYPE_PLAYER, i, 0);
	}
}

void CGame::AdminOrder_Summon(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cName_Master[10], cName_Slave[10], cNpcName[256], cWaypoint[11], cSA; 
 int    pX, pY, j, iNum, iNamingValue;
 class  CStrTok * pStrTok;
 BOOL   bMaster = FALSE;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSummon) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token == NULL) {
		delete pStrTok;
		return;
	}

	ZeroMemory(cNpcName, sizeof(cNpcName));
	strcpy(cNpcName, token);

	token = pStrTok->pGet();
	
	if (token != NULL) 
		 iNum = atoi(token);
	else iNum = 1;

	if (iNum <= 0)  iNum = 1;
	if (iNum >= 50)  iNum = 50;
		
	cSA = 0;
	pX = m_pClientList[iClientH]->m_sX;
	pY = m_pClientList[iClientH]->m_sY;

	wsprintf(G_cTxt, "(!) Admin Order: Summon(%s)-(%d)", cNpcName, iNum);
	PutLogList(G_cTxt);

	iNamingValue = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();

	if (iNamingValue != -1)
	{
		ZeroMemory(cName_Master, sizeof(cName_Master));
		wsprintf(cName_Master, "XX%d", iNamingValue);
		cName_Master[0] = '_';
		cName_Master[1] = m_pClientList[iClientH]->m_cMapIndex + 65;
			
		bMaster = bCreateNewNpc(cNpcName, cName_Master, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, (rand() % 3), cSA, DEF_MOVETYPE_RANDOM, &pX, &pY, cWaypoint, NULL, NULL, -1, FALSE, FALSE, FALSE, TRUE);

		if (!bMaster)
		{
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
		}
	}
	else
	{
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_IPACCOUNTINFO, NULL, NULL, NULL, "Maps too much mobs, Kindly check.");
	}

	for (j = 0; j < (iNum - 1); j++) 
	{
		iNamingValue = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();
		if (iNamingValue != -1)
		{
			ZeroMemory(cName_Slave, sizeof(cName_Slave));
			wsprintf(cName_Slave, "XX%d", iNamingValue);
			cName_Slave[0] = '_';
			cName_Slave[1] = m_pClientList[iClientH]->m_cMapIndex + 65;
			
			if (bCreateNewNpc(cNpcName, cName_Slave, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, (rand() % 3), cSA, DEF_MOVETYPE_RANDOM, &pX, &pY, cWaypoint, NULL, NULL, -1, FALSE, FALSE, FALSE) == FALSE) {
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
			}
			else {
				bSetNpcFollowMode(cName_Slave, cName_Master, DEF_OWNERTYPE_NPC);
			}
		}
	}

	delete pStrTok;
}

void CGame::AdminOrder_SummonAll(int iClientH, char *pData, DWORD dwMsgSize)
{

 char   seps[] = "= \t\n";
 char   * token, * cp, cBuff[256], cLocation[11], cMapName[11];
 WORD   *wp;
 int    pX, pY, i;
 class  CStrTok * pStrTok;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize) <= 0) return;
	if (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == FALSE) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSummonAll) {
		 // Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		 SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		 return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token == NULL) {
		 delete pStrTok;
		 return;
	}

	pX = m_pClientList[iClientH]->m_sX;
	pY = m_pClientList[iClientH]->m_sY;


	memcpy(cMapName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 11);

	if (strlen(token) > 10)
	memcpy(cLocation, token, 10);
	else memcpy(cLocation, token, strlen(token));

	for (i = 0; i < DEF_MAXCLIENTS; i++)
		 if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cLocation, token) == 0)) {
			  RequestTeleportHandler(i, "2   ", cMapName, pX, pY);
		 }

	wsprintf(G_cTxt,"GM Order(%s): PC(%s) Summoned to (%s)", m_pClientList[iClientH]->m_cLocation,
	   cLocation, cMapName);
	bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, G_cTxt);

	ZeroMemory(cBuff, sizeof(cBuff));
	cp = (char *)cBuff;
	*cp = GSM_REQUEST_SUMMONALL;
	cp++;

	memcpy(cp, cLocation, 10);
	cp += 10;

	memcpy(cp, cMapName, 10);
	cp += 10;

	wp = (WORD *)cp;
	*wp = m_pClientList[iClientH]->m_sX;
	cp += 2;

	wp = (WORD *)cp;
	*wp = m_pClientList[iClientH]->m_sY;
	cp += 2;

	bStockMsgToGateServer(cBuff, 25);

	delete pStrTok;
}

void CGame::AdminOrder_SummonPlayer(int iClientH, char *pData, DWORD dwMsgSize)
{
	char   seps[] = "= \t\n";
	char   * token, * cp, cBuff[256], cMapName[11], cName[11]; 
	WORD   *wp;
	int    pX, pY, i;
	class  CStrTok * pStrTok;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSummonPlayer) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	ZeroMemory(cName, sizeof(cName));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token == NULL) {
		delete pStrTok;
		return;
	}

	pX = m_pClientList[iClientH]->m_sX;
	pY = m_pClientList[iClientH]->m_sY;
	memcpy(cMapName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 11);

	if (strlen(token) > 10)
		memcpy(cName, token, 10);
	else memcpy(cName, token, strlen(token));

	for (i = 0; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cName, 10) == 0)) {
			if (i == iClientH) {
				delete pStrTok;
				return;
			}
			RequestTeleportHandler(i, "2   ", cMapName, pX, pY);
			delete pStrTok;
			return;
		}

	// find char on other hg's
	wsprintf(G_cTxt,"GM Order(%s): PC(%s) Summoned to (%s)", m_pClientList[iClientH]->m_cCharName,
				cName, cMapName);
	bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, G_cTxt);

	ZeroMemory(cBuff, sizeof(cBuff));
	cp = (char *)cBuff;
	*cp = GSM_REQUEST_SUMMONPLAYER;
	cp++;

	memcpy(cp, cName, 10);
	cp += 10;

	memcpy(cp, cMapName, 10);
	cp += 10;

	wp = (WORD *)cp;
	*wp = m_pClientList[iClientH]->m_sX;
	cp += 2;

	wp = (WORD *)cp;
	*wp = m_pClientList[iClientH]->m_sY;
	cp += 2;

	bStockMsgToGateServer(cBuff, 25);

	delete pStrTok;
}

void CGame::AdminOrder_DisconnectAll(int iClientH, char *pData, DWORD dwMsgSize)
{

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;
	if (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == FALSE) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelDisconnectAll) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	_iForcePlayerDisconect(DEF_MAXCLIENTS);
}

void CGame::RequestNoticementHandler(int iClientH, char * pData)
{
 char * cp, cData[120];
 int  * ip, iRet, iClientSize;
 DWORD * dwp;
 WORD  * wp;
 
	if (m_pClientList[iClientH] == NULL) return;
	if (m_dwNoticementDataSize < 10) return;

	ip = (int *)(pData + DEF_INDEX2_MSGTYPE + 2);
	iClientSize = *ip;

	if (iClientSize != m_dwNoticementDataSize) {
		// 횇짭쨋처��횑쩐챨횈짰째징 째짰째챠 ��횜쨈횂 횈횆��횕 쨩챌��횑횁챤쩔횒 쨈횢쨍짙쨍챕 쨀쨩쩔챘��쨩 쨍챨쨉횓 쨘쨍쨀쩍쨈횢.
		cp = new char[m_dwNoticementDataSize + 2 + DEF_INDEX2_MSGTYPE + 2];
		ZeroMemory(cp, m_dwNoticementDataSize + 2 + DEF_INDEX2_MSGTYPE + 2);
		memcpy((cp + DEF_INDEX2_MSGTYPE + 2), m_pNoticementData, m_dwNoticementDataSize);
		
		dwp  = (DWORD *)(cp + DEF_INDEX4_MSGID);
		*dwp = MSGID_RESPONSE_NOTICEMENT;
		wp   = (WORD *)(cp + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_REJECT;
		
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cp, m_dwNoticementDataSize + 2 + DEF_INDEX2_MSGTYPE + 2);
	
		delete[] cp;
	}
	else {
		ZeroMemory(cData, sizeof(cData));
		
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_RESPONSE_NOTICEMENT;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_MSGTYPE_CONFIRM;
		
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
	}
	// 쩔징쨌짱 쨔횩쨩첵횉횠쨉쨉 짼첨횁철 쩐횎쨈횂쨈횢.	
}

void CGame::_bDecodeNoticementFileContents(char *pData, DWORD dwMsgSize)
{
 char * cp;	
	
	cp = (pData);
	
	if (m_pNoticementData != NULL) {
		delete[] m_pNoticementData;
		m_pNoticementData = NULL;
	}

	m_pNoticementData = new char[strlen(cp) + 2];
	ZeroMemory(m_pNoticementData, strlen(cp) + 2);

	memcpy(m_pNoticementData, cp, strlen(cp));
	m_dwNoticementDataSize = strlen(cp);

	wsprintf(G_cTxt, "(!) Noticement Data Size: %d", m_dwNoticementDataSize);
	PutLogList(G_cTxt);
}

void CGame::RequestCheckAccountPasswordHandler(char *pData, DWORD dwMsgSize)
{
 int * ip, i, iLevel;
 char * cp, cAccountName[11], cAccountPassword[11];

	cp = (char *)(pData + 6);

	ZeroMemory(cAccountName, sizeof(cAccountName));
	ZeroMemory(cAccountPassword, sizeof(cAccountPassword));

	memcpy(cAccountName, cp, 10);
	cp += 10;

	memcpy(cAccountPassword, cp, 10);
	cp += 10;

	ip = (int *)cp;
	iLevel = *ip;
	cp += 4;

	for (i = 0; i < DEF_MAXCLIENTS; i++)
	if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cAccountName, cAccountName) == 0)) {
		// 째째��쨘 째챔횁짚��쨩 횄짙쩐횘쨈횢. 쨍쨍쩐횪 횈횖쩍쨘쩔철쨉책쨀짧 쨌쨔쨘짠��횑 쨈횢쨍짙쨍챕 쨉짜��횑횇횒 ��첬��책��쨩 횉횕횁철 쩐횎째챠 횁짖쩌횙��쨩 짼첨쨈횂쨈횢. 
		if ((strcmp(m_pClientList[i]->m_cAccountPassword, cAccountPassword) != 0) || (m_pClientList[i]->m_iLevel != iLevel)) {
			wsprintf(G_cTxt, "(TestLog) Error! Account(%s)-Level(%d) password(or level) mismatch! Disconnect.", cAccountName, iLevel);
			PutLogList(G_cTxt);
			// 쨉짜��횑횇횒 ��첬��책��쨩 횉횕횁철 쩐횎째챠 짼첨쨈횂쨈횢.
			DeleteClient(i, FALSE, TRUE);
			return;
		}
	}
}

void CGame::AdminOrder_EnableAdminCommand(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   * token, cBuff[256], len;
 char   seps[] = "= \t\n";
 class  CStrTok * pStrTok;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);
	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token != NULL) {
		len = strlen(token);
		if(len > 10) len = 10;
		if (memcmp(token, m_cSecurityNumber, len) == 0) {
			m_pClientList[iClientH]->m_bIsAdminCommandEnabled = TRUE;
		}
		else {
			wsprintf(G_cTxt, "(%s) Player(%s) attempts to access /enableadmincommand with %s", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, token);
			PutHackLogFileList(G_cTxt);
		}
	}
}

void CGame::AdminOrder_CreateItem(int iClientH, char *pData, DWORD dwMsgSize)
{
 char   seps[] = "= \t\n";
 char   * cp, * token, cBuff[256], cItemName[256], cData[256], cTemp[256], cAttribute[256], cValue[256];
 SYSTEMTIME SysTime;
 class  CStrTok * pStrTok;
 class  CItem * pItem;
 short  * sp;
 int    iRet, iTemp, iEraseReq, iValue;
 DWORD * dwp;
 WORD  * wp, wTemp;
 double dV1, dV2, dV3;
 
	// if the client doesnt exist than no effect.
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == FALSE) return;

	// if the command is just "/createitem " than no effect.
	if ((dwMsgSize)	<= 0) return;

	// if client's admin level is less than 4 no effect.
	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelCreateItem) {
		// if the admin user level is not 0 and less than 4 send message 
		if (m_pClientList[iClientH]->m_iAdminUserLevel !=  0)	
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	} // close if 

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);
	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	// if the token is something it is an item name
	if (token != NULL) {
		ZeroMemory(cItemName, sizeof(cItemName));
		strcpy(cItemName, token);
	} // close if 

	// if the 2nd token is true it is the item attribute
	ZeroMemory(cAttribute, sizeof(cAttribute));
	token = pStrTok->pGet();
	if (token != NULL) {
		ZeroMemory(cAttribute, sizeof(cAttribute));
		strcpy(cAttribute, token);
	} // close if 

	// if the 3rd token is true it is the item value
	ZeroMemory(cValue, sizeof(cValue));
	iValue = 0;
	token = pStrTok->pGet();
	if (token != NULL) {
		ZeroMemory(cValue, sizeof(cValue));
		strcpy(cValue, token);
		iValue = atoi(cValue);
	} // close if 

	pItem = new class CItem;
	// if the given itemname doesnt exist delete item
	if (_bInitItemAttr(pItem, cItemName) == FALSE) {
		delete pItem;
		return;	
	} //close if 

	if (strlen(cAttribute) != 0) {
		pItem->m_dwAttribute = atoi(cAttribute);
		if (pItem->m_dwAttribute == 1) {
			if ((iValue >= 1) && (iValue <= 200)) {
				pItem->m_cItemColor = 2;
				pItem->m_sItemSpecEffectValue2 = iValue - 100;
								
				dV2 = (double)pItem->m_sItemSpecEffectValue2;
				dV3 = (double)pItem->m_wMaxLifeSpan;
				dV1 = (dV2/100.0f)*dV3;

				iTemp  = (int)pItem->m_wMaxLifeSpan;
				iTemp += (int)dV1;

				if (iTemp <= 0) 
					 wTemp = 1;
				else wTemp = (WORD)iTemp;

				if (wTemp <= pItem->m_wMaxLifeSpan*2) {
					pItem->m_wMaxLifeSpan = wTemp;
					pItem->m_sItemSpecEffectValue1 = (short)wTemp;
					pItem->m_wCurLifeSpan = pItem->m_wMaxLifeSpan;
				} // close if 
				else pItem->m_sItemSpecEffectValue1 = (short)pItem->m_wMaxLifeSpan;
			} // close if
			else pItem->m_dwAttribute = NULL;
		} // close if
		else {
			if (pItem->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ATTACK) {
				switch ((pItem->m_dwAttribute & 0xF00000) >> 20) {
				case 6:	pItem->m_cItemColor = 2; break;
				case 8: pItem->m_cItemColor = 3; break;
				case 1:	pItem->m_cItemColor = 5; break;
				case 5:	pItem->m_cItemColor = 1; break;
				case 3:	pItem->m_cItemColor = 7; break;
				case 2:	pItem->m_cItemColor = 4; break;
				case 7:	pItem->m_cItemColor = 6; break;
				case 9:	pItem->m_cItemColor = 8; break;
				} // close switch
			} // close if 
			else if (pItem->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ATTACK_MANASAVE) {
				switch ((pItem->m_dwAttribute & 0xF00000) >> 20) {
				case 10: pItem->m_cItemColor = 5; break;
				} // close switch 
			} // close else if
		} // close else 
	} // close if 

	// if the item id is
	switch (pItem->m_sIDnum) {
	case 511: // ArenaTicket
	case 513: // ArenaTicket(2)
	case 515: // ArenaTicket(3)
	case 517: // ArenaTicket(4)
	case 530: // ArenaTicket(5)
	case 531: // ArenaTicket(6)
	case 532: // ArenaTicket(7)
	case 533: // ArenaTicket(8)
	case 534: // ArenaTicket(9)
		GetLocalTime(&SysTime);
		pItem->m_sTouchEffectType   = DEF_ITET_DATE;
		// v1.4311-3 변경 운영자가 발급한 입장권은 그날은 항상 입장 가능 ..
		pItem->m_sTouchEffectValue1 = (short)SysTime.wMonth;
		pItem->m_sTouchEffectValue2 = (short)SysTime.wDay;
		pItem->m_sTouchEffectValue3 = 24 ;
		break;

	default:
		GetLocalTime(&SysTime);
		pItem->m_sTouchEffectType   = DEF_ITET_ID;
		pItem->m_sTouchEffectValue1 = iDice(1,100000);
		pItem->m_sTouchEffectValue2 = iDice(1,100000);
		// 마지막 숫자는 아이템 생성 월, 일	
		ZeroMemory(cTemp, sizeof(cTemp));
		wsprintf(cTemp, "%d%2d",  (short)SysTime.wMonth, (short)SysTime.wDay);
		pItem->m_sTouchEffectValue3 = atoi(cTemp);
		break;
	}
	
	ZeroMemory(cData, sizeof(cData));
	if (_bAddClientItemList(iClientH, pItem, &iEraseReq) == TRUE) {
		// 아이템을 획득했다.
		dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
		*dwp = MSGID_NOTIFY;
		wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
		*wp  = DEF_NOTIFY_ITEMOBTAINED;
		
		cp = (char *)(cData + DEF_INDEX2_MSGTYPE + 2);
		
		// 1개 획득했다. Amount가 아니다!
		*cp = 1;
		cp++;
		
		memcpy(cp, pItem->m_cName, 20);
		cp += 20;
		
		dwp  = (DWORD *)cp;
		*dwp = pItem->m_dwCount;	// 수량을 입력 
		cp += 4;
		
		*cp = pItem->m_cItemType;
		cp++;
		
		*cp = pItem->m_cEquipPos;
		cp++;
		
		*cp = (char)0; // 얻은 아이템이므로 장착되지 않았다.
		cp++;
		
		sp  = (short *)cp;
		*sp = pItem->m_sLevelLimit;
		cp += 2;
		
		*cp = pItem->m_cGenderLimit;
		cp++;
		
		wp = (WORD *)cp;
		*wp = pItem->m_wCurLifeSpan;
		cp += 2;
		
		wp = (WORD *)cp;
		*wp = pItem->m_wWeight;
		cp += 2;
		
		sp  = (short *)cp;
		*sp = pItem->m_sSprite;
		cp += 2;
		
		sp  = (short *)cp;
		*sp = pItem->m_sSpriteFrame;
		cp += 2;
		
		*cp = pItem->m_cItemColor;
		cp++;

		*cp = (char)pItem->m_sItemSpecEffectValue2; // v1.41 
		cp++;
		
		dwp = (DWORD *)cp;
		*dwp = pItem->m_dwAttribute;
		cp += 4;

		// v2.15 로그 관련 수정
		if (iEraseReq == 1) {
			delete pItem;
			pItem = NULL ;
		}
		
		// 아이템 정보 전송 
		iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 53);
		

		// v2.14 Admin Log
		wsprintf(G_cTxt, "(%s) GM Order(%s): Create ItemName(%s)",m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, cItemName);
		bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, NULL,G_cTxt);

		
	}
	else {
		// 아이템을 소지할 수 없는 상황이다.		
		delete pItem;
		
	}
}

void CGame::ActivateSpecialAbilityHandler(int iClientH)
{
 DWORD dwTime = timeGetTime();
 short sTemp;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_iSpecialAbilityTime != 0) return;
	if (m_pClientList[iClientH]->m_iSpecialAbilityType == 0) return;
	if (m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled == TRUE) return;

	m_pClientList[iClientH]->m_bIsSpecialAbilityEnabled  = TRUE;
	m_pClientList[iClientH]->m_dwSpecialAbilityStartTime = dwTime;

	m_pClientList[iClientH]->m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC;

	sTemp = m_pClientList[iClientH]->m_sAppr4;
	sTemp = sTemp & 0xFF0F;
	switch (m_pClientList[iClientH]->m_iSpecialAbilityType) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		sTemp = sTemp | 0x0010;
		break;
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
		sTemp = sTemp | 0x0020;
		break;
	}
	m_pClientList[iClientH]->m_sAppr4 = sTemp;

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SPECIALABILITYSTATUS, 1, m_pClientList[iClientH]->m_iSpecialAbilityType, m_pClientList[iClientH]->m_iSpecialAbilityLastSec, NULL);
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
}

void CGame::CheckConnectionHandler(int iClientH, char *pData)
{
 char * cp;
 DWORD * dwp, dwTimeRcv, dwTime, dwTimeGapClient, dwTimeGapServer;
	
	dwTime = timeGetTime();
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	dwp = (DWORD *)cp;
	dwTimeRcv = *dwp;

	if (m_pClientList[iClientH] == NULL) return;

#ifdef ANTI_HAX
	CheckDenialServiceAttack(iClientH, dwTimeRcv);
#endif
	
	if (m_pClientList[iClientH]->m_dwInitCCTimeRcv == NULL) {
		m_pClientList[iClientH]->m_dwInitCCTimeRcv = dwTimeRcv;
		m_pClientList[iClientH]->m_dwInitCCTime = dwTime;
	}
	else {
		dwTimeGapClient = (dwTimeRcv - m_pClientList[iClientH]->m_dwInitCCTimeRcv);
		dwTimeGapServer = (dwTime - m_pClientList[iClientH]->m_dwInitCCTime);
		
		if (dwTimeGapClient < dwTimeGapServer) return;
		if ((abs(int(dwTimeGapClient - dwTimeGapServer))) >= (DEF_CLIENTTIMEOUT)) {
			DeleteClient(iClientH, TRUE, TRUE);
		}
	}
}

BOOL CGame::bStockMsgToGateServer(char *pData, DWORD dwSize)
{
 char * cp;

	if ((m_iIndexGSS + dwSize) >= DEF_MAXGATESERVERSTOCKMSGSIZE-10) return FALSE;

	cp = (char *)(m_cGateServerStockMsg + m_iIndexGSS);	
	memcpy(cp, pData, dwSize);

	m_iIndexGSS += dwSize;

	return TRUE;
}


void CGame::SendStockMsgToGateServer()
{
 DWORD * dwp;
 WORD * wp;
 char * cp;

	// 짹횞쨉쩔쩐횊 쨍챨쩐횈쨀천쩐횘쨈첩 쨍횧쩍횄횁철쨍짝 째횚��횑횈짰 쩌짯쨔철쨌횓 ��체쩌횤.
	if (m_iIndexGSS > 6) {
		SendMsgToGateServer(MSGID_SERVERSTOCKMSG, NULL, m_cGateServerStockMsg);
	
		// 쨔철횈횤 횇짭쨍짰쩐챤
		ZeroMemory(m_cGateServerStockMsg, sizeof(m_cGateServerStockMsg));
		// 쨍횉 쩐횛쨘횓쨘횖쩔징 쨍횧쩍횄횁철 쨩챨��횚
		cp = (char *)m_cGateServerStockMsg;
		dwp = (DWORD *)cp;
		*dwp = MSGID_SERVERSTOCKMSG;
		cp += 4;
		wp = (WORD *)cp;
		*wp = DEF_MSGTYPE_CONFIRM;
		cp += 2;

		m_iIndexGSS = 6;
	}
}

void CGame::ServerStockMsgHandler(char *pData)
{
 char * cp, * cp2, cTemp[120], cLocation[10], cGuildName[20], cName[11], cTemp2[120], cTemp3[120], cMapName[11], cBuffer[256]; short * sp;
 WORD * wp, wServerID, wClientH, wV1, wV2, wV3, wV4, wV5;
 DWORD * dwp;
 BOOL bFlag = FALSE;
 int * ip, i, iTotal, iV1, iV2, iV3, iRet;
 short sX, sY;

	iTotal = 0;
	cp = (char *)(pData + 6);
	while (bFlag == FALSE) {
		iTotal++;
		switch (*cp) {
		
		case GSM_REQUEST_SUMMONGUILD:
			cp++;

			ZeroMemory(cGuildName, sizeof(cGuildName));
			memcpy(cGuildName, cp, 20);
			cp += 20;

			ZeroMemory(cTemp, sizeof(cMapName));
			memcpy(cMapName, cp, 10);
			cp += 10;

			cp2 = (char *) cTemp + 10;
			wp = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp = (WORD *)cp;
			wV2 = *wp;
			cp += 2;

			for (i = 0; i < DEF_MAXCLIENTS; i++)
			if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cGuildName, cGuildName) == 0))
			{	wsprintf(G_cTxt,"PC(%s) summoned by Guild(%s) to %s.", m_pClientList[i]->m_cCharName, cGuildName, cMapName);
				PutLogList(G_cTxt);
				RequestTeleportHandler(i, "2   ", cMapName, wV1, wV2);
			}

			break;

		// v2.14 쩌쨘횊횆쨈횕 횄횩째징 ��짱��첬 쩌횘횊짱 
		case GSM_REQUEST_SUMMONPLAYER:
			cp++;
			ZeroMemory(cName, sizeof(cName));
			memcpy(cName, cp, 10);
			cp += 10;

			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			cp2 = (char *) cTemp + 10 ;
			
			wp = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp = (WORD *)cp;
			wV2 = *wp;
			cp += 2;
			
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cCharName, cName) == 0)) {
					RequestTeleportHandler(i, "2   ", cTemp ,wV1, wV2);
					break;
				}
			break;
		
		case GSM_REQUEST_SUMMONALL:
			cp++;
			ZeroMemory(cLocation, sizeof(cLocation));
			memcpy(cLocation, cp, 10);
			cp += 10;

			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			cp2 = (char *) cTemp + 10;
			
			wp = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp = (WORD *)cp;
			wV2 = *wp;
			cp += 2;
			
			for (i = 0; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cLocation, cLocation) == 0)) {
					RequestTeleportHandler(i, "2   ", cTemp, wV1, wV2);
					break;
				}
			break;

		case GSM_CHATMSG:
			cp++;
			ZeroMemory(cTemp, sizeof(cTemp));
			ZeroMemory(cName, sizeof(cName));
			iV1 = *cp;
			cp++;
			ip = (int *)cp;
			iV2 = *ip;
			cp += 4;
			memcpy(cName, cp, 10);
			cp += 10;;
			sp = (short *)cp;
			wV1 = (WORD)*sp;
			cp += 2;
			ChatMsgHandlerGSM(iV1, iV2, cName, cp, wV1);
			cp += wV1;
			break;
		
		case GSM_CONSTRUCTIONPOINT:
			cp++;
			ip = (int *)cp;
			iV1 = *ip;
			cp += 4;
			ip = (int *)cp;
			iV2 = *ip;
			cp += 4;
			GSM_ConstructionPoint(iV1, iV2);
			break;

		case GSM_SETGUILDTELEPORTLOC:
			cp++;
			ip = (int *)cp;
			iV1 = *ip;
			cp += 4;
			ip = (int *)cp;
			iV2 = *ip;
			cp += 4;
			ip = (int *)cp;
			iV3 = *ip;
			cp += 4;
			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;
			GSM_SetGuildTeleportLoc(iV1, iV2, iV3, cTemp);
			break;

		case GSM_SETGUILDCONSTRUCTLOC:
			cp++;
			ip = (int *)cp;
			iV1 = *ip;
			cp += 4;
			ip = (int *)cp;
			iV2 = *ip;
			cp += 4;
			ip = (int *)cp;
			iV3 = *ip;
			cp += 4;
			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;
			GSM_SetGuildConstructLoc(iV1, iV2, iV3, cTemp);
			break;

		case GSM_REQUEST_SETFORCERECALLTIME:
			cp++;
			wp = (WORD *)cp;
			m_sForceRecallTime = *wp;
			cp += 2;

			wsprintf(G_cTxt,"(!) Game Server Force Recall Time (%d)min",m_sForceRecallTime) ;
			PutLogList(G_cTxt) ;
			break;

		case GSM_MIDDLEMAPSTATUS:
			cp++;
			// 짹쨍횁쨋횄쩌 횇짭쨍짰쩐챤
			for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
				m_stMiddleCrusadeStructureInfo[i].cType = NULL;
				m_stMiddleCrusadeStructureInfo[i].cSide = NULL;
				m_stMiddleCrusadeStructureInfo[i].sX    = NULL;
				m_stMiddleCrusadeStructureInfo[i].sY    = NULL;
			}
			sp = (short *)cp;
			m_iTotalMiddleCrusadeStructures = *sp;
			cp += 2;
			// 횁짚쨘쨍 ��횖쩐챤쨉챕��횓쨈횢.
			for (i = 0; i < m_iTotalMiddleCrusadeStructures; i++) {
				m_stMiddleCrusadeStructureInfo[i].cType = *cp;
				cp++;
				m_stMiddleCrusadeStructureInfo[i].cSide = *cp;
				cp++;
				sp = (short *)cp;
				m_stMiddleCrusadeStructureInfo[i].sX = *sp;
				cp += 2;
				sp = (short *)cp;
				m_stMiddleCrusadeStructureInfo[i].sY = *sp;
				cp += 2;	
			}
			break;
		
		case GSM_BEGINCRUSADE:
			cp++;
			dwp = (DWORD *)cp;
			cp += 4;
			LocalStartCrusadeMode(*dwp);
			break;

		case GSM_BEGINAPOCALYPSE:
			cp++;
			dwp = (DWORD *)cp;
			cp += 4;
			LocalStartApocalypse(*dwp);
			break;

		case GSM_ENDAPOCALYPSE:
			cp++;
			LocalEndApocalypse();
			break;

		case GSM_STARTHELDENIAN:
			cp++;
			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;
			wp  = (WORD *)cp;
			wV2 = *wp;
			cp += 2;
			dwp = (DWORD *)cp;
			cp += 4;
			LocalStartHeldenianMode(wV1, wV2, *dwp);
			break;

		case GSM_ENDHELDENIAN:
			cp++;
			dwp = (DWORD *)cp;
			cp += 4;
			ip = (int *)cp;
			iV1 = *ip;
			cp += 4;
			LocalEndHeldenianMode(*dwp ,iV1);
			break;
			
		case GSM_UPDATECONFIGS:
			cp++;
			LocalUpdateConfigs(*cp);
			cp += 16;
			break;

		case GSM_ENDCRUSADE:
			cp++;
			LocalEndCrusadeMode(*cp);
			cp += 16;
			break;

		case GSM_COLLECTEDMANA:
			cp++;
			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV2 = *wp;
			cp += 2;
			CollectedManaHandler(wV1, wV2);
			break;

		case GSM_GRANDMAGICLAUNCH:
			cp++;
			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV2 = *wp;
			cp += 2;

			switch (wV1) {
			case 1: // 쨍횧횇횞쩔�� 쩍쨘횈짰쨋처��횑횇짤 
				MeteorStrikeMsgHandler((char)wV2);
				break;
			}
			break;
		
		case  GSM_GRANDMAGICRESULT:
			cp++;
			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV2 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV3 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV4 = *wp;
			cp += 2;

			wp  = (WORD *)cp;
			wV5 = *wp;

			GrandMagicResultHandler(cTemp, wV1, wV2, wV3, wV4, wV5, cp);
			break;
		
			// v2.15 2002-5-21
		case GSM_REQUEST_SHUTUPPLAYER:
			cp++;
			wp = (WORD *)cp;
			wServerID = *wp;
			cp += 2;
			wp = (WORD *)cp;
			wClientH = *wp;
			cp += 2;

			ZeroMemory(cName, sizeof(cName));
			memcpy(cName, cp, 10);
			cp += 10;

			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			GSM_RequestShutupPlayer(cTemp,wServerID,wClientH, wV1, cName);
			break ;

		case GSM_RESPONSE_SHUTUPPLAYER:
			cp++;
			wp = (WORD *)cp;
			wServerID = *wp;
			cp += 2;
			wp = (WORD *)cp;
			wClientH = *wp;
			cp += 2;

			ZeroMemory(cName, sizeof(cName));
			memcpy(cName, cp, 10);
			cp += 10;

			wp  = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;


			if (wServerID == m_wServerID_GSS) {
				if ((m_pClientList[wClientH] != NULL)&& (strcmp(m_pClientList[wClientH]->m_cCharName, cName) == 0)&&(m_pClientList[wClientH]->m_iAdminUserLevel > 0)) {
					SendNotifyMsg(NULL, wClientH, DEF_NOTIFY_PLAYERSHUTUP, wV1, NULL, NULL, cTemp);

				}
			}
			break;

		// New 16/05/2004
		case GSM_WHISFERMSG:
			ZeroMemory(cName, sizeof(cName));
			ZeroMemory(cBuffer, sizeof(cBuffer));
			cp++;
			memcpy(cName, cp, 10);
			cp += 10;
			wp = (WORD *)cp;
			wV1 = *wp;
			cp += 2;

			memcpy(cBuffer, cp, wV1);
			cp += wV1;

			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cCharName, cName) == 0)) {
					iRet = m_pClientList[i]->m_pXSock->iSendMsg(cBuffer, wV1);
					if(	m_pClientList[i]->m_iAdminUserLevel > 0) {
						char cTxt[200],cTmpName[12] ;
						ZeroMemory(cTxt,sizeof(cTxt)) ;
						ZeroMemory(cTmpName,sizeof(cTmpName)) ;

						memcpy(cTmpName,cBuffer+10,10) ;
						wsprintf(cTxt,"PC Chat(%s):\"%s\"\tto GM(%s)",cTmpName,cBuffer+21,m_pClientList[i]->m_cCharName) ;
						bSendMsgToLS(MSGID_GAMEMASTERLOG, i, NULL, cTxt);
					}
					break;
				}
			break;

		// New 16/05/2004 Changed
		case GSM_REQUEST_FINDCHARACTER:
			cp++;

			wp = (WORD *)cp;
			wServerID = *wp;
			cp += 2;

			wp = (WORD *)cp;
			wClientH = *wp;
			cp += 2;

			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			ZeroMemory(cTemp2, sizeof(cTemp2));
			memcpy(cTemp2, cp, 10);
			cp += 10;

			GSM_RequestFindCharacter(wServerID, wClientH, cTemp, cTemp2);
			break;

		case GSM_RESPONSE_FINDCHARACTER:
			sX = -1;
			sY = -1;
			cp++;
			wp = (WORD *)cp;
			wServerID = *wp;
			cp += 2;
			wp = (WORD *)cp;
			wClientH = *wp;
			cp += 2;
			ZeroMemory(cTemp, sizeof(cTemp));
			memcpy(cTemp, cp, 10);
			cp += 10;

			ZeroMemory(cTemp2, sizeof(cTemp2));
			memcpy(cTemp2, cp, 10);
			cp += 10;

			ZeroMemory(cTemp3, sizeof(cTemp3));
			memcpy(cTemp3, cp, 14);

			if ((wServerID == m_wServerID_GSS) && m_pClientList[wClientH] != NULL) {
				if (m_pClientList[wClientH]->m_bIsAdminOrderGoto == TRUE) {
					m_pClientList[wClientH]->m_bIsAdminOrderGoto = FALSE;
					ZeroMemory(cMapName, sizeof(cMapName));
					memcpy(cMapName, cp, 10);
					cp += 10;

					wp = (WORD *)cp;
					sX = *wp;
					cp += 2;

					wp = (WORD *)cp;
					sY = *wp;
					cp += 2;

					if (m_pClientList[wClientH]->m_iAdminUserLevel > 0) {
						if(sX == -1 && sY == -1){
							wsprintf(G_cTxt,"GM Order(%s): GoTo MapName(%s)",m_pClientList[wClientH]->m_cCharName, cMapName);
						}
						else{
							wsprintf(G_cTxt,"GM Order(%s): GoTo MapName(%s)(%d %d)",m_pClientList[wClientH]->m_cCharName,
								cMapName, sX, sY);
						}
						bSendMsgToLS(MSGID_GAMEMASTERLOG, wClientH, FALSE, G_cTxt);
						RequestTeleportHandler(wClientH,"2   ", cMapName, sX, sY);
					}
				}
				else{
					if ((m_pClientList[wClientH]->m_bIsCheckingWhisperPlayer == TRUE) && (strcmp(m_pClientList[wClientH]->m_cWhisperPlayerName, cTemp) == 0)) {
						m_pClientList[wClientH]->m_iWhisperPlayerIndex = 10000;
						SendNotifyMsg(NULL, wClientH, DEF_NOTIFY_WHISPERMODEON, NULL, NULL, NULL, m_pClientList[wClientH]->m_cWhisperPlayerName);
					}
					else{
						if (m_pClientList[wClientH]->m_iAdminUserLevel == 0) {
							ZeroMemory(cTemp3, sizeof(cTemp3));
						}
						if (strcmp(m_pClientList[wClientH]->m_cCharName, cTemp2) == 0) {
							SendNotifyMsg(NULL, wClientH, DEF_NOTIFY_PLAYERONGAME, NULL, NULL, NULL, cTemp,
								NULL, NULL, NULL, NULL, NULL, NULL, cTemp3);
						}
					}
				}
			}
			break;

		default:
			bFlag = TRUE;
			break;
		}
	}
}

void CGame::GSM_RequestFindCharacter(WORD wReqServerID, WORD wReqClientH, char *pName, char * pFinder)
{
 char * cp, cTemp[120];
 WORD * wp;
 int i;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
	if ((m_pClientList[i] != NULL)  && (strcmp(m_pClientList[i]->m_cCharName, pName) == 0)) {
		// 횄짙쩐횘쨈횢.
		ZeroMemory(cTemp, sizeof(cTemp));
		cp = (char *)(cTemp);
		*cp = GSM_RESPONSE_FINDCHARACTER;
		cp++;

		wp = (WORD *)cp;
		*wp = wReqServerID;
		cp += 2;

		wp = (WORD *)cp;
		*wp = wReqClientH;
		cp += 2;
		
		memcpy(cp, pName, 10);
		cp += 10;

		memcpy(cp, pFinder, 10);
		cp += 10;

		memcpy(cp, m_pClientList[i]->m_cMapName, 10);
		cp += 10;

		wp = (WORD *)cp;
		*wp = m_pClientList[i]->m_sX;
		cp += 2;

		wp = (WORD *)cp;
		*wp = m_pClientList[i]->m_sY;
		cp += 2;

		bStockMsgToGateServer(cTemp, 39);
		break;	
	}
}

BOOL CGame::bAddClientShortCut(int iClientH)
{
 int i; 

	for (i = 0; i < DEF_MAXCLIENTS; i++)
	if (m_iClientShortCut[i] == iClientH) return FALSE;

	for (i = 0; i < DEF_MAXCLIENTS; i++)
	if (m_iClientShortCut[i] == 0) {
		m_iClientShortCut[i] = iClientH;
		return TRUE;
	}

	return FALSE;
}

void CGame::RemoveClientShortCut(int iClientH)
{
 int i;

	for (i = 0; i < DEF_MAXCLIENTS+1; i++)
	if (m_iClientShortCut[i] == iClientH) {
		m_iClientShortCut[i] = 0;
		goto RCSC_LOOPBREAK;
	}

RCSC_LOOPBREAK:;

	for (i = 0; i < DEF_MAXCLIENTS; i++)
	if ((m_iClientShortCut[i] == 0) && (m_iClientShortCut[i+1] != 0)) {
		m_iClientShortCut[i] = m_iClientShortCut[i+1];
		m_iClientShortCut[i+1] = 0;
	}
}

void CGame::RequestChangePlayMode(int iClientH)
{

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_iPKCount > 0) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;

	if (memcmp(m_pClientList[iClientH]->m_cMapName,"cityhall",8) != 0) return;

	if (m_pClientList[iClientH]->m_iLevel < 100) {
			if (m_pClientList[iClientH]->m_bIsPlayerCivil == TRUE) {
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "arehunter", 9) == 0) strcpy(m_pClientList[iClientH]->m_cLocation, "aresden");
				else if (memcmp(m_pClientList[iClientH]->m_cLocation, "elvhunter", 9) == 0) strcpy(m_pClientList[iClientH]->m_cLocation, "elvine");
				m_pClientList[iClientH]->m_bIsPlayerCivil = FALSE;
			}
			else {
				if (memcmp(m_pClientList[iClientH]->m_cLocation, "aresden", 7) == 0) strcpy(m_pClientList[iClientH]->m_cLocation, "arehunter");
				else if (memcmp(m_pClientList[iClientH]->m_cLocation, "elvine", 6) == 0) strcpy(m_pClientList[iClientH]->m_cLocation, "elvhunter");
				m_pClientList[iClientH]->m_bIsPlayerCivil = TRUE;
			}
			SendNotifyMsg(NULL,iClientH,DEF_NOTIFY_CHANGEPLAYMODE,NULL,NULL,NULL,m_pClientList[iClientH]->m_cLocation);
			SendEventToNearClient_TypeA(iClientH,DEF_OWNERTYPE_PLAYER,MSGID_EVENT_MOTION,100,NULL,NULL,NULL);
		}
}

void CGame::RequestRango(int iClientH, int iObjectID)
{
	if (m_pClientList[iClientH] == NULL) return;
	if ((iObjectID <= 0) || (iObjectID >= DEF_MAXCLIENTS)) return;

	if (m_pClientList[iObjectID] != NULL) {
		// 쩔채횄쨩 쨔횧��쨘 Object째징 쩐첩쨈횢.

		// centu - que cuente m_iMaxEK
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_REQRANGO, m_pClientList[iObjectID]->m_iMaxEK, m_pClientList[iObjectID]->m_iRating, m_pClientList[iObjectID]->m_iWantedLevel, NULL);
	}
}

// thx to kazin
void CGame::RequestOnlines(int iClientH)
{
	char * cData = G_cData50000; //esta es el "buffer", onda, la memoria que neceisto para enviar

	DWORD * dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_REQUEST_ONLINE;//a la memoria esa le escribo este mensaje
	WORD * wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);			   
	*wp  = 0;//este no se usa, le mando 0

	char * cp = (char *)(cData	+ DEF_INDEX2_MSGTYPE + 2); //eso se usa para decirle "desde aca empiezo a escribir"

	short * pTotal = (short *)cp;
	cp += 2;

	int count = 0;
	for (int i = 0; i <= DEF_MAXCLIENTS; i++) //recorro todosl os clientes
	{
		if (!m_pClientList[i])//si son nulls
			continue;//no darles bola y seguir

		memcpy(cp, m_pClientList[i]->m_cCharName, 10); //copiar el nombre del char (de tama�o 10) a la data
		cp += 10;//decirle a la data que le sume 10 bites

		memcpy(cp, m_pClientList[i]->m_cGuildName, 21); //copiar el nombre del char (de tama�o 10) a la data
		cp += 21;//decirle a la data que le sume 10 bites
		count++;
	}

	*pTotal = count; //esto es medio enroscado, es para decirle cuantos onlines escribio
	m_pClientList[iClientH]->m_pXSock->iSendMsg(G_cData50000, cp - G_cData50000);//mandarle la data a p que es el cliente
	
}

void CGame::GetExp(int iClientH, unsigned long iExp, BOOL bIsAttackerOwn)
{

	double dV1, dV2, dV3;
	int i, iH, iUnitValue;
	DWORD dwTime = timeGetTime();
	int iTotalPartyMembers;

	if (m_pClientList[iClientH] == NULL) return;
	if (iExp <= 0) return;

	if (m_pClientList[iClientH]->m_iLevel <= 80) 
	{
		dV1 = (double)(80 - m_pClientList[iClientH]->m_iLevel);
		dV2 = dV1 * 0.025f;
		dV3 = (double)iExp;
		dV1 = (dV2 + 1.025f)*dV3;
		iExp = (unsigned long)dV1;
	}
		
	//Check for party status, else give exp to player
	if ((m_pClientList[iClientH]->m_iPartyID != NULL) && (m_pClientList[iClientH]->m_iPartyStatus == DEF_PARTYSTATUS_CONFIRM))
	{
		//Only divide exp if > 1 person 
		if(m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers > 0){	
			iTotalPartyMembers = 0;
			for(i = 0; i < m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers; i++){
				iH = m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i];
				if ((m_pClientList[iH] != NULL) && (m_pClientList[iH]->m_iHP > 0)) {
					if ((strlen(m_pMapList[m_pClientList[iH]->m_cMapIndex]->m_cName)) == (strlen(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName))) {
						if(memcmp(m_pMapList[m_pClientList[iH]->m_cMapIndex]->m_cName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, strlen(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName)) == 0){
							iTotalPartyMembers++;
						}
					}
				}
			}

			//Check for party bug
			if(iTotalPartyMembers > 8){
				wsprintf(G_cTxt, "(X) Party Bug !! partyMember %d", iTotalPartyMembers);
				PutLogFileList(G_cTxt);
				iTotalPartyMembers = 8;
			}

			//Figure out how much exp a player gets
			dV1 = (double)iExp;

			switch(iTotalPartyMembers){
			case 1:
				dV2 = dV1;
				break;
			case 2:
				dV2 = (dV1 + (dV1 * 2.0e-2)) / 2.0f;
				break;
			case 3:
				dV2 = (dV1 + (dV1 * 5.0e-2)) / 3.0f;
				break;
			case 4:
				dV2 = (dV1 + (dV1 * 7.000000000000001e-2)) / 4.0f;
				break;
			case 5:
				dV2 = (dV1 + (dV1 * 1.0e-1)) / 5.0f;
				break;
			case 6:
				dV2 = (dV1 + (dV1 * 1.4e-1)) / 6.0f;
				break;
			case 7:
				dV2 = (dV1 + (dV1 * 1.7e-1)) / 7.0f;
				break;
			case 8:
				dV2 = (dV1 + (dV1 * 2.0e-1)) / 8.0f;
				break;
			}

			dV3 = dV2 + 5.0e-1;
			iUnitValue = (int)dV3;

			//Divide exp among party members
			for(i = 0; i < iTotalPartyMembers; i++){
				iH = m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i];
				//Player who kills monster gets more exp
				if(iH == iClientH){
					if((m_pClientList[iH] != NULL) && (m_pClientList[iH]->m_iHP > 0)) { // Is player alive ??
						//Exp gain based on lvl
						if((m_pClientList[iH]->m_iStatus & 0x10000) != 0) iUnitValue *= 3;
						MultiplicadorExp(iH, iUnitValue);
					}
				}
				else{
					//Other players get normal exp :P
					if((m_pClientList[iH] != NULL) && (m_pClientList[iH]->m_iHP > 0))
						if(m_pClientList[iH]->m_bSkillUsingStatus[19] != 1)
							//Only players on same map get exp
							if(m_pClientList[iH]->m_cMapIndex == m_pClientList[iClientH]->m_cMapIndex)
								MultiplicadorExp(iH, iUnitValue);
				}
			}

			if (bIsAttackerOwn == TRUE)
				if (iTotalPartyMembers > 1)
					MultiplicadorExp(iClientH, (iUnitValue/iTotalPartyMembers));
		}
		else
		{
			if ((m_pClientList[iClientH]->m_iStatus & 0x10000) != 0) iExp *= 3;	
			MultiplicadorExp(iClientH, iExp);
		}
	}
	else
	{
		if ((m_pClientList[iClientH]->m_iStatus & 0x10000) != 0) iExp *= 3;
		MultiplicadorExp(iClientH, iExp);
	}
}

void CGame::MultiplicadorExp(int Client, unsigned long Exp)
{
	if (m_pClientList[Client] == NULL) return;

	if (m_iExpSetting == 0) 
	{
		if		(m_pClientList[Client]->m_iLevel < 20)		Exp *= 2.0f;

		else if	(m_pClientList[Client]->m_iLevel >= 20 && 
				 m_pClientList[Client]->m_iLevel < 60)		Exp *= 1.75f;

		else if	(m_pClientList[Client]->m_iLevel >= 60 && 
				 m_pClientList[Client]->m_iLevel < 100)		Exp *= 1.5f;

		else if	(m_pClientList[Client]->m_iLevel >= 100 &&
				 m_pClientList[Client]->m_iLevel < 140)		Exp *= 1.25f;

		else if	(m_pClientList[Client]->m_iLevel >= 140 &&
				 m_pClientList[Client]->m_iLevel < 160)		Exp *= 0.75f;

		else if	(m_pClientList[Client]->m_iLevel >= 160 &&
				 m_pClientList[Client]->m_iLevel < 180)		Exp *= 0.5f;

		else if	(m_pClientList[Client]->m_iLevel >= 180)	Exp *= 0.25f;
	}
	else if (m_iExpSetting == 1) 
	{
		if		(m_pClientList[Client]->m_iLevel < 20)		Exp *= 20;

		else if	(m_pClientList[Client]->m_iLevel >= 20 && 
				 m_pClientList[Client]->m_iLevel < 60)		Exp *= 17.5f;

		else if	(m_pClientList[Client]->m_iLevel >= 60 && 
				 m_pClientList[Client]->m_iLevel < 100)		Exp *= 15;

		else if	(m_pClientList[Client]->m_iLevel >= 100 &&
				 m_pClientList[Client]->m_iLevel < 140)		Exp *= 12.5f;

		else if	(m_pClientList[Client]->m_iLevel >= 140 &&
				 m_pClientList[Client]->m_iLevel < 160)		Exp *= 10;

		else if	(m_pClientList[Client]->m_iLevel >= 160 &&
				 m_pClientList[Client]->m_iLevel < 180)		Exp *= 7.5f;

		else if	(m_pClientList[Client]->m_iLevel >= 180)	Exp *= 5;
	}
	else if (m_iExpSetting == 2) 
	{
		Exp *= 400;
	}
	
	m_pClientList[Client]->m_iExp += Exp;

	if (bCheckLimitedUser(Client) == FALSE)
	{
		SendNotifyMsg(NULL, Client, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);
	}

	bCheckLevelUp(Client);
}

void CGame::AdminOrder_GoTo(int iClientH, char* pData, DWORD dwMsgSize)
{
	char   seps[] = "= \t\n";
	char   * token, cBuff[256], cPlayerName[11],cMapName[32];
	class  CStrTok * pStrTok;
	char *cp;
	WORD *wp;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelGoto) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cPlayerName, sizeof(cPlayerName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();

	token = pStrTok->pGet();
	if (token == NULL) {
		delete pStrTok;
		return;
	}

	if (strlen(token) > 10) {
		memcpy(cPlayerName,token,10);
	}
	else{
		memcpy(cPlayerName,token,strlen(token));
	}

	for(int i = 1; i < DEF_MAXCLIENTS; i++){
		if (m_pClientList[i] != NULL) {
			if (memcmp(cPlayerName,m_pClientList[i]->m_cCharName, 10) == 0) {
				if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) {
					if(m_pClientList[i]->m_sX == -1 && m_pClientList[i]->m_sY == -1){
						wsprintf(cBuff,"GM Order(%s): GoTo MapName(%s)",m_pClientList[iClientH]->m_cCharName,m_pClientList[i]->m_cMapName);
					}
					else{
						wsprintf(cBuff,"GM Order(%s): GoTo MapName(%s)(%d %d)",m_pClientList[iClientH]->m_cCharName,
							     m_pClientList[i]->m_cMapName,m_pClientList[i]->m_sX,m_pClientList[i]->m_sY);
					}
					bSendMsgToLS(MSGID_GAMEMASTERLOG,iClientH,FALSE,cBuff);
					ZeroMemory(cMapName,sizeof(cMapName));
					strcpy(cMapName, m_pClientList[i]->m_cMapName);
					RequestTeleportHandler(iClientH,"2   ", cMapName, m_pClientList[i]->m_sX,m_pClientList[i]->m_sY);
					

				}
				delete pStrTok;
				return;
			}
		}
	}
	m_pClientList[iClientH]->m_bIsAdminOrderGoto = TRUE;

	ZeroMemory(cBuff,sizeof(cBuff));
	
	cp = (char *)cBuff;
	*cp = GSM_REQUEST_FINDCHARACTER;
	cp++;

	wp = (WORD *)cp;
	*wp = m_wServerID_GSS;
	cp += 2;

	wp = (WORD *)cp;
	*wp = iClientH;
	cp += 2;

	memcpy(cp,cPlayerName,10);
	cp += 10;

	memcpy(cp,m_pClientList[iClientH]->m_cCharName,10);
	cp += 10;

	bStockMsgToGateServer(cBuff,25);

	delete pStrTok;
}

void CGame::AdminOrder_MonsterCount(int iClientH, char* pData, DWORD dwMsgSize)
{
	int iMonsterCount;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelMonsterCount) {
		// Admin user level��횑 쨀쨌쩐횈쩌짯 ��횑 짹창쨈횋��쨩 쨩챌쩔챘횉횘 쩌철 쩐첩쨈횢.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}
	iMonsterCount = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_iTotalAliveObject;
	SendNotifyMsg(0,iClientH, DEF_NOTIFY_MONSTERCOUNT, iMonsterCount,NULL,NULL,NULL);
}

// v2.17 2002-7-15 운영자 명령어로 강콜시간을 설정한다.
void CGame::AdminOrder_SetForceRecallTime(int iClientH, char *pData, DWORD dwMsgSize)
{
 class  CStrTok * pStrTok;
 char   seps[] = "= \t\n";
 char   * token, cBuff[256],* cp; 
 WORD * wp ;
 int    iTime;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;


	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelSetRecallTime) {
		// Admin user level이 낮아서 이 기능을 사용할 수 없다.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
   	
	if (token != NULL) {

		if (token == NULL) 
			 iTime = 0;
		else iTime = atoi(token);
	
		if (iTime < 0) iTime = 0;
	 	
		m_sForceRecallTime = iTime ;

		ZeroMemory(cBuff, sizeof(cBuff));
		cp = (char *)cBuff;
		*cp = GSM_REQUEST_SETFORCERECALLTIME;
		cp++;
	
		wp = (WORD *)cp;
		*wp = iTime ;
		cp += 2;

		bStockMsgToGateServer(cBuff, 3);

		wsprintf(G_cTxt,"(!) Game Server Force Recall Time (%d)min",m_sForceRecallTime) ;
		PutLogList(G_cTxt) ;
	}

	delete pStrTok;
}

void CGame::AdminOrder_UnsummonBoss(int iClientH)
{
	if (m_pClientList[iClientH] == NULL) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelUnsummonBoss) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	for(int i = 1; i < DEF_MAXNPCS; i++){
		if (m_pNpcList[i] != NULL && m_pNpcList[i]->m_bIsSummoned == FALSE) {
			switch(m_pNpcList[i]->m_sType) {
			case 31: //Demon
			case 49: //Hellclaw
			case 45: //GHKABS
			case 47: //BG
			case 50: //Tigerworm
			case 52: //Gagoyle
			case 81: //Abaddon
			case 66: //Wyvern
			case 73: //Fire-Wyvern
				m_pNpcList[i]->m_bIsUnsummoned = TRUE;
				NpcKilledHandler(iClientH, DEF_OWNERTYPE_PLAYER, i, 0);
				break;
			}
		}
	}
}

void CGame::AdminOrder_ClearNpc(int iClientH)
{
	if (m_pClientList[iClientH] == NULL) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelClearNpc) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	for(int i = 1; i < DEF_MAXNPCS; i++){
		if (m_pNpcList[i] != NULL && m_pNpcList[i]->m_bIsSummoned == FALSE) {
			switch(m_pNpcList[i]->m_sType) {
			case 15:
			case 19:
			case 20:
			case 24:
			case 25:
			case 26:
			case 67:
			case 68:
			case 69:
			case 90:
			case 91:
				break;

			default:
				m_pNpcList[i]->m_bIsUnsummoned = TRUE;
				NpcKilledHandler(iClientH, DEF_OWNERTYPE_PLAYER, i, 0);
				break;
			}
		}
	}
}

// Testcode, found reference to it in 3.51, InitPlayerData and RequestTeleportHandler
int CGame::iGetPlayerABSStatus(int iClientH)
{
	int iRet;

	if (m_pClientList[iClientH] == NULL) return 0;

	iRet = 0;

		if (m_pClientList[iClientH]->m_iPKCount != 0) {
			iRet = 8;
		}

		if (m_pClientList[iClientH]->m_cSide != 0) {
			iRet = iRet | 4;
		}

		if (m_pClientList[iClientH]->m_cSide == 1) {
			iRet = iRet | 2;
		}

		if (m_pClientList[iClientH]->m_bIsPlayerCivil == TRUE)
			iRet = iRet | 1;

		return iRet;
}

// New 18/05/2004
void CGame::SetPlayingStatus(int iClientH)
{
	char cMapName[11], cLocation[11];

	if (m_pClientList[iClientH] == NULL) return;

	ZeroMemory(cMapName, sizeof(cMapName));
	ZeroMemory(cLocation, sizeof(cLocation));

	strcpy(cLocation, m_pClientList[iClientH]->m_cLocation);
	strcpy(cMapName, m_pMapList[ m_pClientList[iClientH]->m_cMapIndex]->m_cName);

	m_pClientList[iClientH]->m_cSide = 0;
	m_pClientList[iClientH]->m_bIsOwnLocation = FALSE;
	m_pClientList[iClientH]->m_bIsPlayerCivil = FALSE;

	if (memcmp(cLocation, cMapName, 3) == 0) {
		m_pClientList[iClientH]->m_bIsOwnLocation = TRUE;
	}

	if (memcmp(cLocation, "are", 3) == 0)
		m_pClientList[iClientH]->m_cSide = 1;
	else if (memcmp(cLocation, "elv", 3) == 0)
		m_pClientList[iClientH]->m_cSide = 2;
	else{ 
		if (strcmp(cMapName, "elvine") == 0 || strcmp(cMapName, "aresden") == 0) {
			m_pClientList[iClientH]->m_bIsOwnLocation = TRUE;
		}
		m_pClientList[iClientH]->m_bIsNeutral = TRUE;
	}

	if (memcmp(cLocation, "arehunter", 9) == 0 || memcmp(cLocation, "elvhunter", 9) == 0) {
		m_pClientList[iClientH]->m_bIsPlayerCivil = TRUE;
	}

	if (memcmp(m_pClientList[iClientH]->m_cMapName, "bisle", 5) == 0) {
		m_pClientList[iClientH]->m_bIsPlayerCivil = FALSE;
	}

	if (memcmp(m_pClientList[iClientH]->m_cMapName, "bsmith", 6) == 0 ||
		memcmp(m_pClientList[iClientH]->m_cMapName, "gldhall", 7) == 0 ||
		memcmp(m_pClientList[iClientH]->m_cMapName, "gshop", 5) == 0)
		m_pClientList[iClientH]->m_pIsProcessingAllowed = TRUE;
	else
		m_pClientList[iClientH]->m_pIsProcessingAllowed = TRUE;

	if (memcmp(m_pClientList[iClientH]->m_cMapName, "wrhus", 5) == 0 ||
		memcmp(m_pClientList[iClientH]->m_cMapName, "arewrhus", 8) == 0 ||
		memcmp(m_pClientList[iClientH]->m_cMapName, "elvwrhus", 8) == 0)
		m_pClientList[iClientH]->m_bIsInsideWarehouse = TRUE;
	else
		m_pClientList[iClientH]->m_bIsInsideWarehouse = TRUE;

	if (memcmp(m_pClientList[iClientH]->m_cMapName, "wzdtwr", 6) == 0)
		m_pClientList[iClientH]->m_bIsInsideWizardTower = TRUE;
	else
		m_pClientList[iClientH]->m_bIsInsideWizardTower = TRUE;
}

void CGame::ForceChangePlayMode(int iClientH, bool bNotify)
{
	if(m_pClientList[iClientH] == NULL) return;

	if (memcmp(m_pClientList[iClientH]->m_cLocation, "arehunter", 9) == 0)
		strcpy(m_pClientList[iClientH]->m_cLocation, "aresden");
	else if (memcmp(m_pClientList[iClientH]->m_cLocation, "elvhunter", 9) == 0)
		strcpy(m_pClientList[iClientH]->m_cLocation, "elvine");

	if (m_pClientList[iClientH]->m_bIsPlayerCivil == TRUE)
		m_pClientList[iClientH]->m_bIsPlayerCivil = FALSE;

	if (bNotify) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CHANGEPLAYMODE, NULL, NULL, NULL, m_pClientList[iClientH]->m_cLocation);
		SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
	}
}

// v2.15 2002-5-21
void CGame::GSM_RequestShutupPlayer(char * pGMName,WORD wReqServerID, WORD wReqClientH, WORD wTime,char * pPlayer )
{
	char * cp, cTemp[120];
	WORD * wp;
 int i;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (strcmp(m_pClientList[i]->m_cCharName, pPlayer) == 0)) {
			// 횄짙쩐횘쨈횢.
			ZeroMemory(cTemp, sizeof(cTemp));
			cp = (char *)(cTemp);
			*cp = GSM_RESPONSE_SHUTUPPLAYER;
			cp++;

			wp = (WORD *)cp;
			*wp = wReqServerID;
			cp += 2;

			wp = (WORD *)cp;
			*wp = wReqClientH;
			cp += 2;

			memcpy(cp, pGMName, 10);
			cp += 10;

			wp = (WORD *)cp;
			*wp = (WORD) wTime;
			cp += 2;

			memcpy(cp, pPlayer, 10);
			cp += 10;

			// v2.14 쩌횏쩐첨쩍횄째짙��쨩 쨘횖��쨍쨌횓 쩌철횁짚
			m_pClientList[i]->m_iTimeLeft_ShutUp = wTime*20; // 1��횑 3횄횎쨈횢. 20��횑쨍챕 1쨘횖 

			SendNotifyMsg(NULL, i, DEF_NOTIFY_PLAYERSHUTUP, wTime, NULL, NULL, pPlayer);

			bStockMsgToGateServer(cTemp, 27);
			break;	
		}
}

// v2.14 05/22/2004 - Hypnotoad - adds pk log
BOOL CGame::_bPKLog(int iAction,int iAttackerH , int iVictumH, char * pNPC)
{
	char  cTxt[1024], cTemp1[120], cTemp2[120];

	//  쨌횓짹횞 쨀짼짹채쨈횢. 
	ZeroMemory(cTxt, sizeof(cTxt));
	ZeroMemory(cTemp1, sizeof(cTemp1));
	ZeroMemory(cTemp2, sizeof(cTemp2));

	if ( m_pClientList[iVictumH] == NULL) return FALSE ;

	switch (iAction) {

		case DEF_PKLOG_REDUCECRIMINAL: 
			wsprintf(cTxt, "(%s) PC(%s)\tReduce\tCC(%d)\t%s(%d %d)\t", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, m_pClientList[iVictumH]->m_iPKCount,
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY);
			break; 

		case DEF_PKLOG_BYPLAYER:
			if ( m_pClientList[iAttackerH] == NULL) return FALSE ;
			wsprintf(cTxt, "(%s) PC(%s)\tKilled by PC\t \t%s(%d %d)\t(%s) PC(%s)", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, 
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY,m_pClientList[iAttackerH]->m_cIPaddress, m_pClientList[iAttackerH]->m_cCharName);
			break;
		case DEF_PKLOG_BYPK:
			if ( m_pClientList[iAttackerH] == NULL) return FALSE ;
			wsprintf(cTxt, "(%s) PC(%s)\tKilled by PK\tCC(%d)\t%s(%d %d)\t(%s) PC(%s)", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, m_pClientList[iAttackerH]->m_iPKCount,
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY,m_pClientList[iAttackerH]->m_cIPaddress, m_pClientList[iAttackerH]->m_cCharName);
			break; 
		case DEF_PKLOG_BYENERMY:
			if ( m_pClientList[iAttackerH] == NULL) return FALSE ;
			wsprintf(cTxt, "(%s) PC(%s)\tKilled by Enemy\t \t%s(%d %d)\t(%s) PC(%s)", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, 
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY,m_pClientList[iAttackerH]->m_cIPaddress, m_pClientList[iAttackerH]->m_cCharName);
			break; 
		case DEF_PKLOG_BYNPC:
			if(pNPC==NULL) return FALSE ;
			wsprintf(cTxt, "(%s) PC(%s)\tKilled by NPC\t \t%s(%d %d)\tNPC(%s)", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, 
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY,pNPC);
			break; 
		case DEF_PKLOG_BYOTHER:
			wsprintf(cTxt, "(%s) PC(%s)\tKilled by Other\t \t%s(%d %d)\tUnknown", m_pClientList[iVictumH]->m_cIPaddress, m_pClientList[iVictumH]->m_cCharName, 
				m_pClientList[iVictumH]->m_cMapName,m_pClientList[iVictumH]->m_sX,m_pClientList[iVictumH]->m_sY);
			break; 
		default:
			return FALSE;
	}
	PutPvPLogFileList(cTxt);
	return TRUE ;
}

void CGame::RequestResurrectPlayer(int iClientH, bool bResurrect)
{
short sX, sY;
char buff[100];

	if (m_pClientList[iClientH] == NULL) return;

	sX = m_pClientList[iClientH]->m_sX;
	sY = m_pClientList[iClientH]->m_sY;

	if (bResurrect == FALSE) {
		m_pClientList[iClientH]->m_bIsBeingResurrected = FALSE;
		return;
	}

	if (m_pClientList[iClientH]->m_bIsBeingResurrected == FALSE) {
		wsprintf(buff, "(!!!) Player(%s) Tried To Use Resurrection Hack", m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		DeleteClient(iClientH, TRUE, TRUE, TRUE, TRUE);
		return;
	}

	wsprintf(buff, "(*) Resurrect Player! %s", m_pClientList[iClientH]->m_cCharName);
	PutLogList(buff);


	m_pClientList[iClientH]->m_bIsKilled = FALSE;
	// Player's HP becomes half of the Max HP. 
	m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH, FALSE)/2; 
	// Player's MP
	m_pClientList[iClientH]->m_iMP = iGetMaxMP(iClientH);
	// Player's SP
	m_pClientList[iClientH]->m_iSP = iGetMaxSP(iClientH);
	// Player's Hunger
	m_pClientList[iClientH]->m_iHungerStatus = 100;

	m_pClientList[iClientH]->m_bIsBeingResurrected = FALSE;

	// !!! RequestTeleportHandler쨀쨩쩔징쩌짯 m_cMapName��쨩 쩐짼짹창 쨋짠쨔짰쩔징 짹횞쨈챘쨌횓 횈횆쨋처쨔횑횇횒쨌횓 쨀횗째횥횁횜쨍챕 쩔��쨉쩔��횤
	RequestTeleportHandler(iClientH, "2   ", m_pClientList[iClientH]->m_cMapName, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
}

void CGame::bCheckClientAttackFrequency(int iClientH, DWORD dwClientTime)
{
 DWORD dwTimeGap;

	if (m_pClientList[iClientH] == NULL) return ;
	if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) return ;

	if (m_pClientList[iClientH]->m_dwAttackFreqTime == NULL) 
		m_pClientList[iClientH]->m_dwAttackFreqTime = dwClientTime;
	else {
		dwTimeGap = dwClientTime - m_pClientList[iClientH]->m_dwAttackFreqTime;
		m_pClientList[iClientH]->m_dwAttackFreqTime = dwClientTime;

		if (dwTimeGap < 450) {
			wsprintf(G_cTxt, "Swing Hack: (%s) Player: (%s) - attacking with weapon at irregular rates.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			DeleteClient(iClientH, TRUE, TRUE);

		}
	}

}

void CGame::bCheckClientMagicFrequency(int iClientH, DWORD dwClientTime)
{
 DWORD dwTimeGap;
	
	if (m_pClientList[iClientH] == NULL) return ;

	if (m_pClientList[iClientH]->m_dwMagicFreqTime == NULL) 
		m_pClientList[iClientH]->m_dwMagicFreqTime = dwClientTime;
	else {
		dwTimeGap = dwClientTime - m_pClientList[iClientH]->m_dwMagicFreqTime;
		m_pClientList[iClientH]->m_dwMagicFreqTime = dwClientTime;

		if ((dwTimeGap < 1500) && (m_pClientList[iClientH]->m_bMagicConfirm == TRUE)) {
			wsprintf(G_cTxt, "Speed Cast: (%s) Player: (%s) - casting magic at irregular rates. ", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			DeleteClient(iClientH, TRUE, TRUE);
			
		}
		
		m_pClientList[iClientH]->m_iSpellCount--;
		m_pClientList[iClientH]->m_bMagicConfirm = FALSE;
		m_pClientList[iClientH]->m_bMagicPauseTime = FALSE;
	}
}

void CGame::bCheckClientMoveFrequency(int iClientH, DWORD dwClientTime)
{
 DWORD dwTimeGap;
	
	if (m_pClientList[iClientH] == NULL) return ;
	if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) return ;

	if (m_pClientList[iClientH]->m_dwMoveFreqTime == NULL) 
		m_pClientList[iClientH]->m_dwMoveFreqTime = dwClientTime;
	else {
		if (m_pClientList[iClientH]->m_bIsMoveBlocked == TRUE) {
			m_pClientList[iClientH]->m_dwMoveFreqTime = NULL;
			m_pClientList[iClientH]->m_bIsMoveBlocked = FALSE;
			return ;
		}

		if (m_pClientList[iClientH]->m_bIsAttackModeChange == TRUE) {
			m_pClientList[iClientH]->m_dwMoveFreqTime = NULL;
			m_pClientList[iClientH]->m_bIsAttackModeChange = FALSE;
			return ;
		}

		dwTimeGap = dwClientTime - m_pClientList[iClientH]->m_dwMoveFreqTime;
		m_pClientList[iClientH]->m_dwMoveFreqTime = dwClientTime;
		
		if ((dwTimeGap < 200) && (dwTimeGap >= 0)) {
			wsprintf(G_cTxt, "Speed Hack: (%s) Player: (%s) - running too fast.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
			PutHackLogFileList(G_cTxt);
			DeleteClient(iClientH, TRUE, TRUE);
			
		}

	}
}

void CGame::bReadScheduleConfigFile(char *pFn)
{
 FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadModeA, cReadModeB;
 char seps[] = "= \t\n";
 class CStrTok * pStrTok;
 int   iIndex;

	cReadModeA = 0;
	cReadModeB = 0;
	iIndex = 0;

	hFile = CreateFile(pFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(pFn, "rt");
	if (pFile == NULL) {
		// 게임서버의 초기화 파일을 읽을 수 없다.
		PutLogList("(!) Cannot open Schedule file.");
		return;
	}
	else {
		PutLogList("(!) Reading Schedule file...");
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();

		while( token != NULL )   {
			
			if (cReadModeA != 0) {
				switch (cReadModeA) {
				case 1:
					if (strcmp(m_cServerName, token) == 0) {
						PutLogList("(!) Success: This server will schedule Crusade Total War.");
						m_bIsCrusadeWarStarter = TRUE;
					}
					cReadModeA = 0;
					break;

				case 2:
					if (strcmp(m_cServerName, token) == 0) {
						PutLogList("(!) Success: This server will schedule Apocalypse.");
						m_bIsApocalypseStarter = TRUE;
					}
					cReadModeA = 0;
					break;

				case 3:
					switch (cReadModeB) {
					case 1:
						if (iIndex >= DEF_MAXSCHEDULE) {
							PutLogList("(!) WARNING! Too many Crusade War schedule!"); 
							return;
						}
						m_stCrusadeWarSchedule[iIndex].iDay = atoi(token);
						cReadModeB = 2;
						break;
					case 2:
						m_stCrusadeWarSchedule[iIndex].iHour = atoi(token);
						cReadModeB = 3;
						break;
					case 3:
						m_stCrusadeWarSchedule[iIndex].iMinute = atoi(token);
						cReadModeB = 0;
						break;
					}
					iIndex++;
					cReadModeA = 0;
					break;

				case 4:
					switch (cReadModeB) {
					case 1:
						if (iIndex >= DEF_MAXAPOCALYPSE) {
							PutLogList("(!) WARNING! Too many Apocalypse schedule!"); 
							return;
						}
						m_stApocalypseScheduleStart[iIndex].iDay = atoi(token);
						cReadModeB = 2;
						break;
					case 2:
						m_stApocalypseScheduleStart[iIndex].iHour = atoi(token);
						cReadModeB = 3;
						break;
					case 3:
						m_stApocalypseScheduleStart[iIndex].iMinute = atoi(token);
						cReadModeB = 0;
						break;
					}
					iIndex++;
					m_bIsApocalypseScheduleLoaded = TRUE;
					cReadModeA = 0;
					break;

				case 5:
					
					cReadModeA = 0;
					break;

				case 6:
					switch (cReadModeB) {
					case 1:
						if (iIndex >= DEF_MAXHELDENIAN) {
							PutLogList("(!) WARNING! Too many Heldenian schedule!"); 
							return;
						}
						m_stHeldenianSchedule[iIndex].iDay = atoi(token);
						cReadModeB = 2;
						break;
					case 2:
						m_stHeldenianSchedule[iIndex].StartiHour = atoi(token);
						cReadModeB = 3;
						break;
					case 3:
						m_stHeldenianSchedule[iIndex].StartiMinute = atoi(token);
						cReadModeB = 4;
						break;
					}
					iIndex++;
					m_bIsHeldenianScheduleLoaded = TRUE;
					cReadModeA = 0;
					break;

				case 7: // by Centuu.-
					if (strcmp(m_cServerName, token) == 0) {
						PutLogList("(!) Success: This server will schedule Heldenian.");
						m_bIsHeldenianReady = TRUE;
					}
					cReadModeA = 0;
					break;

				case 8:
					cReadModeA = 0;
					break;

				case 9:
					iIndex++;
					cReadModeA = 0;
					break;
				}
			}
			else {
				if (memcmp(token, "crusade-server-name", 19) == 0) {
					cReadModeA = 1;
					cReadModeB = 1;
				}
				if (memcmp(token, "apocalypse-server-name", 22) == 0) {
					cReadModeA = 2;
					cReadModeB = 1;
				}
				if (memcmp(token, "crusade-schedule", 16) == 0) {
					cReadModeA = 3;
					cReadModeB = 1;
				}
				if (memcmp(token, "apocalypse-schedule-start", 25) == 0) {
					cReadModeA = 4;
					cReadModeB = 1;
				}
				if (memcmp(token, "heldenian-schedule", 18) == 0) {
					cReadModeA = 6;
					cReadModeB = 1;
				}
				if (memcmp(token, "heldenian-server-name", 21) == 0) {
					cReadModeA = 7;
					cReadModeB = 1;
				}
			}
			
			token = pStrTok->pGet();
		}
		delete pStrTok;
		delete[] cp;
		fclose(pFile);
	}
}

void CGame::OnStartGameSignal()
{
 int i;
	
	for (i = 0; i < DEF_MAXMAPS; i++)
	if (m_pMapList[i] != NULL) 
		__bReadMapInfo(i);
	
	bReadCrusadeStructureConfigFile("..\\GameConfigs\\Crusade.cfg");
	_LinkStrikePointMapIndex();
	bReadScheduleConfigFile("..\\GameConfigs\\Schedule.cfg");

	bReadCrusadeGUIDFile("..\\GameConfigs\\CrusadeGUID.txt");
	bReadApocalypseGUIDFile("..\\GameConfigs\\ApocalypseGUID.txt");
	bReadHeldenianGUIDFile("..\\GameConfigs\\HeldenianGUID.txt");

	PutLogList("");
	PutLogList("(!) Game Server Activated.");
}

void CGame::CheckForceRecallTime(int iClientH)
{
	SYSTEMTIME SysTime;

	if(m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) return;

	GetLocalTime(&SysTime);
	switch(SysTime.wDayOfWeek) {
			case 1:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeMonday; break;  //월요일  3분 2002-09-10 #1
			case 2:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeTuesday; break;  //화요일  3분 
			case 3:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeWednesday; break;  //수요일  3분 
			case 4:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeThursday; break;  //목요일  3분 
			case 5:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeFriday; break; //금요일 15분
			case 6:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeSaturday; break; //토요일 45분 
			case 0:	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 20*m_sRaidTimeSunday; break; //일요일 60분
	}
		
}

BOOL CGame::bReadAdminSetConfigFile(char * cFn)
{
	FILE * pFile;
	HANDLE hFile;
	DWORD  dwFileSize;
	char * cp, * token, cReadMode, cGSMode[16] = "";
	char seps[] = "= \t\n";
	class CStrTok * pStrTok;

	cReadMode = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile != NULL) {
	
		 PutLogList("(!) Reading Admin Settings file...");
		 cp = new char[dwFileSize+2];
		 ZeroMemory(cp, dwFileSize+2);
		 fread(cp, dwFileSize, 1, pFile);

		 pStrTok = new class CStrTok(cp, seps);
		 token = pStrTok->pGet();
		 while( token != NULL )   {

		 if (cReadMode != 0) {
		   switch (cReadMode) {

		   case 1:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGMKill = atoi(token);
			}
			else{
				m_iAdminLevelGMKill = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		   case 2:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGMRevive = atoi(token);
			}
			else{
				m_iAdminLevelGMRevive = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		   case 3:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGMCloseconn = atoi(token);
			}
			else{
				m_iAdminLevelGMCloseconn = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		   case 4:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGMCheckRep = atoi(token);
			}
			else{
				m_iAdminLevelGMCheckRep = 1;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 5:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelWho = atoi(token);
			}
			else{
				m_iAdminLevelWho = 1;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 6:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelEnergySphere = atoi(token);
			}
			else{
				m_iAdminLevelEnergySphere = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 7:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelShutdown = atoi(token);
			}
			else{
				m_iAdminLevelShutdown = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 8:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelObserver = atoi(token);
			}
			else{
				m_iAdminLevelObserver = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 9:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelShutup = atoi(token);
			}
			else{
				m_iAdminLevelShutup = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 10:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCallGaurd = atoi(token);
			}
			else{
				m_iAdminLevelCallGaurd = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 11:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummonDemon = atoi(token);
			}
			else{
				m_iAdminLevelSummonDemon = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------		   
		  case 12:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummonDeath = atoi(token);
			}
			else{
				m_iAdminLevelSummonDeath = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 13:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelReserveFightzone = atoi(token);
			}
			else{
				m_iAdminLevelReserveFightzone = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 14:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCreateFish = atoi(token);
			}
			else{
				m_iAdminLevelCreateFish = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 15:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelTeleport = atoi(token);
			}
			else{
				m_iAdminLevelTeleport = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 16:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCheckIP = atoi(token);
			}
			else{
				m_iAdminLevelCheckIP = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 17:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelPolymorph = atoi(token);
			}
			else{
				m_iAdminLevelPolymorph = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 18:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetInvis = atoi(token);
			}
			else{
				m_iAdminLevelSetInvis = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 19:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetZerk = atoi(token);
			}
			else{
				m_iAdminLevelSetZerk = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 20:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetIce = atoi(token);
			}
			else{
				m_iAdminLevelSetIce = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 21:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGetNpcStatus = atoi(token);
			}
			else{
				m_iAdminLevelGetNpcStatus = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------				
		  case 22:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetAttackMode = atoi(token);
			}
			else{
				m_iAdminLevelSetAttackMode = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 23:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelUnsummonAll = atoi(token);
			}
			else{
				m_iAdminLevelUnsummonAll = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 24:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelUnsummonDemon = atoi(token);
			}
			else{
				m_iAdminLevelUnsummonDemon = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 25:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummon = atoi(token);
			}
			else{
				m_iAdminLevelSummon = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------			
		  case 26:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummonAll = atoi(token);
			}
			else{
				m_iAdminLevelSummonAll = 4;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 27:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummonPlayer = atoi(token);
			}
			else{
				m_iAdminLevelSummonPlayer = 1;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 28:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelDisconnectAll = atoi(token);
			}
			else{
				m_iAdminLevelDisconnectAll = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 29:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelEnableCreateItem = atoi(token);
			}
			else{
				m_iAdminLevelEnableCreateItem = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------			
		  case 30:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCreateItem = atoi(token);
			}
			else{
				m_iAdminLevelCreateItem = 4;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 31:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelStorm = atoi(token);
			}
			else{
				m_iAdminLevelStorm = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 32:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelWeather = atoi(token);
			}
			else{
				m_iAdminLevelWeather = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 33:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetStatus = atoi(token);
			}
			else{
				m_iAdminLevelSetStatus = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 34:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelGoto = atoi(token);
			}
			else{
				m_iAdminLevelGoto = 1;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 35:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelMonsterCount = atoi(token);
			}
			else{
				m_iAdminLevelMonsterCount = 1;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------			
		  case 36:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSetRecallTime = atoi(token);
			}
			else{
				m_iAdminLevelSetRecallTime = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 37:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelUnsummonBoss = atoi(token);
			}
			else{
				m_iAdminLevelUnsummonBoss = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------	
		  case 38:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelClearNpc = atoi(token);
			}
			else{
				m_iAdminLevelClearNpc = 3;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------				
		  case 39:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelTime = atoi(token);
			}
			else{
				m_iAdminLevelTime = 2;
			}
			cReadMode = 0;
			break;
//----------------------------------------------------------------
		  case 40:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelPushPlayer = atoi(token);
			}
			else{
				m_iAdminLevelPushPlayer = 2;
			}
			cReadMode = 0;
			break;
//-----------------------------------------------------------------
		  case 41:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelSummonGuild = atoi(token);
			}
			else{
				m_iAdminLevelSummonGuild = 3;
			}
			cReadMode = 0;
			break;
//-----------------------------------------------------------------
		  case 42:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCheckStatus = atoi(token);
			}
			else{
				m_iAdminLevelCheckStatus = 1;
			}
			cReadMode = 0;
			break;
//-----------------------------------------------------------------
		  case 43:
			if ((strlen(token) > 0) && (strlen(token) < 9))
			{
				m_iAdminLevelCleanMap = atoi(token);
			}
			else{
				m_iAdminLevelCleanMap = 1;
			}
			cReadMode = 0;
			break;
//-----------------------------------------------------------------
			}
		  }
		  else {
			if (memcmp(token, "Admin-Level-/kill", 17) == 0)						cReadMode = 1;
			if (memcmp(token, "Admin-Level-/revive", 19) == 0)						cReadMode = 2;
			if (memcmp(token, "Admin-Level-/closecon", 21) == 0)					cReadMode = 3;
			if (memcmp(token, "Admin-Level-/checkrep", 21) == 0)					cReadMode = 4;
			if (memcmp(token, "Admin-Level-/who", 16) == 0)							cReadMode = 5;
			if (memcmp(token, "Admin-Level-/energysphere", 25) == 0)				cReadMode = 6;
			if (memcmp(token, "Admin-Level-/shutdownthisserverrightnow", 39) == 0)	cReadMode = 7;
			if (memcmp(token, "Admin-Level-/setobservermode", 28) == 0)				cReadMode = 8;
			if (memcmp(token, "Admin-Level-/shutup", 19) == 0)						cReadMode = 9;
			if (memcmp(token, "Admin-Level-/attack", 19) == 0)						cReadMode = 10;
			if (memcmp(token, "Admin-Level-/summondemon", 24) == 0)					cReadMode = 11;
			if (memcmp(token, "Admin-Level-/summondeath", 24) == 0)					cReadMode = 12;
			if (memcmp(token, "Admin-Level-/reservefightzone", 28) == 0)			cReadMode = 13;
			if (memcmp(token, "Admin-Level-/createfish", 23) == 0)					cReadMode = 14;
			if (memcmp(token, "Admin-Level-/teleport", 21) == 0)					cReadMode = 15;
			if (memcmp(token, "Admin-Level-/checkip", 20) == 0)						cReadMode = 16;
			if (memcmp(token, "Admin-Level-/polymorph", 22) == 0)					cReadMode = 17;
			if (memcmp(token, "Admin-Level-/setinvi", 20) == 0)						cReadMode = 18;
			if (memcmp(token, "Admin-Level-/setzerk", 20) == 0)						cReadMode = 19;
			if (memcmp(token, "Admin-Level-/setfreeze", 22) == 0)					cReadMode = 20;
			if (memcmp(token, "Admin-Level-/gns", 16) == 0)							cReadMode = 21;
			if (memcmp(token, "Admin-Level-/setattackmode", 26) == 0)				cReadMode = 22;
			if (memcmp(token, "Admin-Level-/unsummonall", 24) == 0)					cReadMode = 23;
			if (memcmp(token, "Admin-Level-/unsummondemon", 26) == 0)				cReadMode = 24;
			if (memcmp(token, "Admin-Level-/summonnpc", 22) == 0)					cReadMode = 25;
			if (memcmp(token, "Admin-Level-/summonall", 22) == 0)					cReadMode = 26;
			if (memcmp(token, "Admin-Level-/summonplayer", 25) == 0)				cReadMode = 27;
			if (memcmp(token, "Admin-Level-/disconnectall", 26) == 0)				cReadMode = 28;
			if (memcmp(token, "Admin-Level-/enableadmincreateitem", 34) == 0)		cReadMode = 29;
			if (memcmp(token, "Admin-Level-/createitem", 23) == 0)					cReadMode = 30;
			if (memcmp(token, "Admin-Level-/storm", 18) == 0)						cReadMode = 31;
			if (memcmp(token, "Admin-Level-/weather", 20) == 0)						cReadMode = 32;
			if (memcmp(token, "Admin-Level-/setstatus", 22) == 0)					cReadMode = 33;
			if (memcmp(token, "Admin-Level-/goto", 17) == 0)						cReadMode = 34;
			if (memcmp(token, "Admin-Level-/monstercount", 17) == 0)				cReadMode = 35;
			if (memcmp(token, "Admin-Level-/setforcerecalltime", 23) == 0)			cReadMode = 36;
			if (memcmp(token, "Admin-Level-/unsummonboss", 25) == 0)				cReadMode = 37;
			if (memcmp(token, "Admin-Level-/clearnpc", 21) == 0)					cReadMode = 38;
			if (memcmp(token, "Admin-Level-/time", 17) == 0)						cReadMode = 39;
			if (memcmp(token, "Admin-Level-/send", 17) == 0)						cReadMode = 40;
			if (memcmp(token, "Admin-Level-/summonguild", 24) == 0)					cReadMode = 41;
			if (memcmp(token, "Admin-Level-/checkstatus", 24) == 0)					cReadMode = 42;	
			if (memcmp(token, "Admin-Level-/clearmap", 21) == 0)					cReadMode = 43;	
		  }

		  token = pStrTok->pGet();
		 }
		 delete pStrTok;
		 delete[] cp;

		 fclose(pFile);

		 return TRUE;
		}

		return FALSE;
}

void CGame::AdminOrder_CheckRep(int iClientH, char *pData,DWORD dwMsgSize)
{
 class  CStrTok * pStrTok;
 short m_iRating;
 char   * token, cName[11], cTargetName[11], cRepMessage[256], cTemp[256], seps[] = "= \t\n", cBuff[256];
 int i;

	if (m_pClientList[iClientH] == NULL) return;
	ZeroMemory(cTemp, sizeof(cTemp));
	ZeroMemory(cRepMessage, sizeof(cRepMessage));
	if (m_pClientList[iClientH]->m_iAdminUserLevel < 1) {
		wsprintf(cRepMessage, " You have %d reputation points.", m_pClientList[iClientH]->m_iRating);
		SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, cRepMessage);
	} 
	else {
		if ((dwMsgSize)	<= 0) return;
		ZeroMemory(cTargetName, sizeof(cTargetName));
		ZeroMemory(cBuff, sizeof(cBuff));
		memcpy(cBuff, pData, dwMsgSize);

		pStrTok = new class CStrTok(cBuff, seps);
		token = pStrTok->pGet();

		token = pStrTok->pGet();
		
		if (token != NULL) {
			ZeroMemory(cName, sizeof(cName));
			strcpy(cName, token);
		} 
		else {
			ZeroMemory(cName, sizeof(cName));
			strcpy(cName, "null");
		}

		token = pStrTok->pGet();
		
		if (token != NULL) {
			m_iRating = atoi(token);
		} 
		
		if (token == NULL) { 
			token = "null"; 
		}
		
			if (cName != NULL) {
			token = cName;

				if (strlen(token) > 10) 
  					memcpy(cTargetName, token, 10);
				else memcpy(cTargetName, token, strlen(token));

				for (i = 1; i < DEF_MAXCLIENTS; i++) 
  					if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cTargetName, 10) == 0)) {
						wsprintf(cRepMessage, " %s has %d reputation points.", m_pClientList[i]->m_cCharName, m_pClientList[i]->m_iRating);
						SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, cRepMessage);
					}
			}
	}
}

void CGame::AdminOrder_Pushplayer(int iClientH, char * pData, DWORD dwMsgSize)
{
//Push Player- By:ACiDx  Monday , September 2004
	//Teleports a Defined Player to Defined Destination
	// /push playername mapname sX dX
 char   seps[] = "= \t\n";
 char   * token, cBuff[256], cMapName[256], cName[11], cTargetName[11];
 class  CStrTok * pStrTok;
 int dX, dY;
  int i;
 BOOL   bFlag;
	ZeroMemory(cTargetName, sizeof(cTargetName));
	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cBuff, sizeof(cBuff));

	dX = dY = -1;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelPushPlayer) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	
	
	if (token != NULL) {
		ZeroMemory(cName, sizeof(cName));
		strcpy(cName, token);
	} else {
		ZeroMemory(cName, sizeof(cName));
		strcpy(cName, "null");
	}
	token = pStrTok->pGet();
	if (token != NULL) {
		ZeroMemory(cMapName, sizeof(cMapName));
		strcpy(cMapName, token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		dX = atoi(token);
	}

	token = pStrTok->pGet();
	if (token != NULL) {
		dY = atoi(token);
	}

	if (token == NULL) { token = "null"; }
	if (cName != NULL) {
		token = cName;

	if (strlen(token) > 10) 
			memcpy(cTargetName, token, 10);
		else memcpy(cTargetName, token, strlen(token));

		for (i = 1; i < DEF_MAXCLIENTS; i++) 
			if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cTargetName, 10) == 0)) {
			bFlag = FALSE;
			//Asks For Flag on maps
			if (strcmp("2ndmiddle", cMapName) == 0) bFlag = TRUE;
			if (strcmp("abaddon", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("arebrk11", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arebrk12", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arebrk21", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arebrk22", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arefarm", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arejail", cMapName) == 0) bFlag = TRUE;
			if (strcmp("aremidl", cMapName) == 0) bFlag = TRUE;
			if (strcmp("aremidr", cMapName) == 0) bFlag = TRUE;
			if (strcmp("aresden", cMapName) == 0) bFlag = TRUE;
			if (strcmp("aresdend1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("areuni", cMapName) == 0) bFlag = TRUE;
			if (strcmp("arewrhus", cMapName) == 0) bFlag = TRUE;
			if (strcmp("bisle", cMapName) == 0)   bFlag = TRUE;
			if (strcmp("bsmith_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("bsmith_1f", cMapName) == 0) bFlag = TRUE;
			if (strcmp("bsmith_2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("bsmith_2f", cMapName) == 0) bFlag = TRUE;
			if (strcmp("BtField", cMapName) == 0) bFlag = TRUE;
			if (strcmp("cath_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("cath_2", cMapName) == 0)      bFlag = TRUE;
			if (strcmp("cityhall_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("cityhall_2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("CmdHall_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("CmdHall_2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("default", cMapName) == 0) bFlag = TRUE;
			if (strcmp("dglv2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("dglv3", cMapName) == 0) bFlag = TRUE;
			if (strcmp("dglv4", cMapName) == 0) bFlag = TRUE;
			if (strcmp("druncncity", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("elvbrk11", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvbrk12", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvbrk21", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvbrk22", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvfarm", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvine", cMapName) == 0)  bFlag = TRUE;
			if (strcmp("elvined1", cMapName) == 0)    bFlag = TRUE;
			if (strcmp("elvjail", cMapName) == 0)    bFlag = TRUE;
			if (strcmp("elvmidl", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvmidr", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvuni", cMapName) == 0) bFlag = TRUE;
			if (strcmp("elvwrhus", cMapName) == 0) bFlag = TRUE;
			if (strcmp("fightzone1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("gldhall_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("gldhall_2", cMapName) == 0)   bFlag = TRUE;
			if (strcmp("GodH", cMapName) == 0)   bFlag = TRUE;
			if (strcmp("gshop_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("gshop_1f", cMapName) == 0) bFlag = TRUE;
			if (strcmp("gshop_2", cMapName) == 0)     bFlag = TRUE;
			if (strcmp("gshop_2f", cMapName) == 0)     bFlag = TRUE;
			if (strcmp("HRampart", cMapName) == 0)     bFlag = TRUE;
			if (strcmp("huntzone1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("huntzone2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("huntzone3", cMapName) == 0) bFlag = TRUE;
			if (strcmp("huntzone4", cMapName) == 0) bFlag = TRUE;
			if (strcmp("icebound", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("inferniaA", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("inferniaB", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("maze", cMapName) == 0) bFlag = TRUE; 
			if (strcmp("middled1n", cMapName) == 0) bFlag = TRUE;
			if (strcmp("middled1x", cMapName) == 0) bFlag = TRUE;
			if (strcmp("middleland", cMapName) == 0) bFlag = TRUE;
			if (strcmp("penalty", cMapName) == 0) bFlag = TRUE;
			if (strcmp("procella", cMapName) == 0) bFlag = TRUE;
			if (strcmp("resurr1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("resurr2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("toh1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("toh2", cMapName) == 0) bFlag = TRUE;
			if (strcmp("toh3", cMapName) == 0) bFlag = TRUE;
			if (strcmp("wrhus_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("wrhus_1f", cMapName) == 0) bFlag = TRUE;
			if (strcmp("wrhus_2", cMapName) == 0)     bFlag = TRUE;
			if (strcmp("wrhus_2f", cMapName) == 0)     bFlag = TRUE;
			if (strcmp("wzdtwr_1", cMapName) == 0) bFlag = TRUE;
			if (strcmp("wzdtwr_2", cMapName) == 0) bFlag = TRUE;

			//Defines I as Max clients
				if (bFlag == TRUE)
					//Reqeust the Push/Teleport
					RequestTeleportHandler(i, "2   ", cMapName, dX, dY);
   					wsprintf(G_cTxt,"(%s) GM(%s) sends (%s) Player(%s) to [%s](%d,%d)",m_pClientList[iClientH]->m_cIPaddress, 
						m_pClientList[iClientH]->m_cCharName, m_pClientList[i]->m_cIPaddress, m_pClientList[i]->m_cCharName, cMapName, dX, dY);
					bSendMsgToLS(MSGID_GAMEMASTERLOG, iClientH, FALSE, G_cTxt);
				delete pStrTok;
			}
	}
}


BOOL CGame::bReadAdminListConfigFile(char *pFn)
{
 FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadModeA, cReadModeB;
 char seps[] = "= \t\n";
 class CStrTok * pStrTok;
 int   iIndex;
 char len;

	cReadModeA = 0;
	cReadModeB = 0;
	iIndex = 0;

	hFile = CreateFile(pFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(pFn, "rt");
	if (pFile == NULL) {
		// 게임서버의 초기화 파일을 읽을 수 없다.
		PutLogList("(!) Cannot open AdminList.cfg file.");
		return FALSE;
	}
	else {
		PutLogList("(!) Reading AdminList.cfg...");
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();

		while( token != NULL )   {
			if (cReadModeA != 0) {
				switch (cReadModeA) {
				case 1:
						if (iIndex >= DEF_MAXADMINS) {
							PutLogList("(!) WARNING! Too many GMs on the AdminList.cfg!"); 
							return TRUE;
						}
						len = strlen(token);
						if(len > 10) len = 10;
						ZeroMemory(m_stAdminList[iIndex].m_cGMName, sizeof(m_stAdminList[iIndex].m_cGMName));
						memcpy(m_stAdminList[iIndex].m_cGMName, token, strlen(token));
						iIndex++;
						cReadModeA = 0;
						cReadModeB = 0;
						break;
				}
			}
			else {
				if (memcmp(token, "verified-admin", 14) == 0) {
					cReadModeA = 1;
					cReadModeB = 1;
				}
			}
			
			token = pStrTok->pGet();
		}
		delete pStrTok;
		delete[] cp;

		fclose(pFile);
	}

	return TRUE;
}

BOOL CGame::bReadBannedListConfigFile(char *pFn)
{
 FILE * pFile;
 HANDLE hFile;
 DWORD  dwFileSize;
 char * cp, * token, cReadModeA, cReadModeB;
 char seps[] = "= \t\n";
 class CStrTok * pStrTok;
 int   iIndex;
 char len;

	cReadModeA = 0;
	cReadModeB = 0;
	iIndex = 0;

	hFile = CreateFile(pFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(pFn, "rt");
	if (pFile == NULL) {
		// 게임서버의 초기화 파일을 읽을 수 없다.
		PutLogList("(!) Cannot open BannedList.cfg file.");
		return FALSE;
	}
	else {
		PutLogList("(!) Reading BannedList.cfg...");
		cp = new char[dwFileSize+2];
		ZeroMemory(cp, dwFileSize+2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();

		while( token != NULL )   {
			if (cReadModeA != 0) {
				switch (cReadModeA) {
				case 1:
						if (iIndex >= DEF_MAXBANNED) {
							PutLogList("(!) WARNING! Too many banned on the BannedList.cfg!"); 
							return TRUE;
						}
						len = strlen(token);
						if(len > 20) len = 20;
						ZeroMemory(m_stBannedList[iIndex].m_cBannedIPaddress, sizeof(m_stBannedList[iIndex].m_cBannedIPaddress));
						memcpy(m_stBannedList[iIndex].m_cBannedIPaddress, token, strlen(token));
						iIndex++;
						cReadModeA = 0;
						cReadModeB = 0;
						break;
				}
			}
			else {
				if (memcmp(token, "banned-ip", 9) == 0) {
					cReadModeA = 1;
					cReadModeB = 1;
				}
			}
			
			token = pStrTok->pGet();
		}
		delete pStrTok;
		delete[] cp;

		fclose(pFile);
	}

	return TRUE;
}

void CGame::AdminOrder_CleanMap(int iClientH, char * pData, DWORD dwMsgSize)
{
	char   seps[] = "= \t\n";
	class  CStrTok * pStrTok;
	char   * token, cMapName[11], cBuff[256];
	BOOL bFlag = FALSE;	//Used to check if we are on the map we wanna clear
	int i;
	CItem *pItem;
	short sRemainItemSprite, sRemainItemSpriteFrame, dX, dY;
	char cRemainItemColor, len;


	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelCleanMap) {
		// Admin user level이 낮아서 이 기능을 사용할 수 없다.
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token != NULL) {
		ZeroMemory(cMapName, sizeof(cMapName));
		strcpy(cMapName, token);

		for (i = 0; i < DEF_MAXMAPS; i++)	//Enum all maps
			if (m_pMapList[i] != NULL) {	//Is allocated map
				if (memcmp(m_pMapList[i]->m_cName, cMapName, 10) == 0) {	//is map same name
					bFlag = TRUE; //Set flag
					//Get X and Y coords
					int m_x = m_pMapList[i]->m_sSizeX;
					int m_y = m_pMapList[i]->m_sSizeY;
					for(int j = 1; j < m_x; j++)
						for(int k = 1; k < m_y; k++){
							do {	//Delete all items on current tile
								pItem = m_pMapList[i]->pGetItem(j, k, &sRemainItemSprite, &sRemainItemSpriteFrame, &cRemainItemColor); // v1.4
								if (pItem != NULL) {
									delete pItem;	//Delete item;
								}
							} while(pItem != NULL);
						}
					break;	//Break outo f loop
				}
			}

		if (bFlag) 
		{	//Notify GM that all items have been cleared
			for(int i = 1; i < DEF_MAXCLIENTS; i++){
				if (m_pClientList[i] != NULL) {
				len = strlen(cMapName);
				if(len > 10) len = 10;
				if (memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, cMapName, len) != 0) return;
				dX = m_pClientList[i]->m_sX;
				dY = m_pClientList[i]->m_sY;
				ZeroMemory(cMapName,sizeof(cMapName));
				strcpy(cMapName, m_pClientList[i]->m_cMapName);
				RequestTeleportHandler(i,"2   ", cMapName, dX, dY);
				}
			}
		}
	}

	delete pStrTok;
}

void CGame::ShowClientMsg(int iClientH, char* pMsg)
{
	char * cp, cTemp[256];
	DWORD * dwp, dwMsgSize;
	WORD * wp;
	short * sp;

	ZeroMemory(cTemp, sizeof(cTemp));

	dwp = (DWORD *)cTemp;
	*dwp = MSGID_COMMAND_CHATMSG;

	wp  = (WORD *)(cTemp + DEF_INDEX2_MSGTYPE);
	*wp = NULL;

	cp  = (char *)(cTemp + DEF_INDEX2_MSGTYPE + 2);
	sp  = (short *)cp;
	*sp = NULL;
	cp += 2;

	sp  = (short *)cp;
	*sp = NULL;
	cp += 2;

	memcpy(cp, "[BOT]", 5); // Player name :P
	cp += 10;

	*cp = 10; // chat type
	cp++;

	dwMsgSize = strlen(pMsg);
	if(dwMsgSize > 50) dwMsgSize = 50;
	memcpy(cp, pMsg, dwMsgSize);
	cp += dwMsgSize;

	m_pClientList[iClientH]->m_pXSock->iSendMsg(cTemp, dwMsgSize + 22);
}

void CGame::GlobalUpdateConfigs(char cConfigType)
{
 char * cp, cData[120];

	ZeroMemory(cData, sizeof(cData));
	cp = (char *)cData;
	*cp = GSM_UPDATECONFIGS;
	cp++;

	*cp = (char)cConfigType;
	cp++;			

	LocalUpdateConfigs(cConfigType);

	bStockMsgToGateServer(cData, 5);
}

void CGame::LocalUpdateConfigs(char cConfigType)
{
	if (cConfigType == 1) {
		bReadSettingsConfigFile("..\\GameConfigs\\Settings.cfg");
		PutLogList("(!!!) Settings.cfg updated successfully!");
	}
	else if (cConfigType == 2) {
		bReadAdminListConfigFile("..\\GameConfigs\\AdminList.cfg");
		PutLogList("(!!!) AdminList.cfg updated successfully!");
	}
	else if (cConfigType == 3) {
		bReadBannedListConfigFile("..\\GameConfigs\\BannedList.cfg");
		PutLogList("(!!!) BannedList.cfg updated successfully!");
	}
	else if (cConfigType == 4) {
		bReadAdminSetConfigFile("..\\GameConfigs\\AdminSettings.cfg");
		PutLogList("(!!!) AdminSettings.cfg updated successfully!");
	}
}

void CGame::TimeHitPointsUp(int iClientH)
{
 int iMaxHP, iTemp, iTotal;
 double dV1, dV2, dV3;

	if (m_pClientList[iClientH] == NULL) return;

	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
		
	if (m_pClientList[iClientH]->m_iHungerStatus <= 0) return;

	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;

	if (m_pClientList[iClientH]->m_bSkillUsingStatus[19] == TRUE) return;
	
	iMaxHP = iGetMaxHP(iClientH);

	if (m_pClientList[iClientH]->m_iHP < iMaxHP) {
		
		iTemp = iDice(1, (m_pClientList[iClientH]->m_iVit));

		if (iTemp < (m_pClientList[iClientH]->m_iVit/2)) iTemp = (m_pClientList[iClientH]->m_iVit/2);

		if (m_pClientList[iClientH]->m_iSideEffect_MaxHPdown != 0)

			iTemp -= (iTemp / m_pClientList[iClientH]->m_iSideEffect_MaxHPdown);

		iTotal = iTemp + m_pClientList[iClientH]->m_iHPstock;

		if (m_pClientList[iClientH]->m_iAddHP != 0) {
			dV2 = (double)iTotal;
			dV3 = (double)m_pClientList[iClientH]->m_iAddHP;
			dV1 = (dV3 / 100.0f)*dV2;
			iTotal += (int)dV1;
		}

		m_pClientList[iClientH]->m_iHP += iTotal;

		if (m_pClientList[iClientH]->m_iHP > iMaxHP) m_pClientList[iClientH]->m_iHP = iMaxHP;

		if (m_pClientList[iClientH]->m_iHP <= 0) m_pClientList[iClientH]->m_iHP = 0;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
	}

	m_pClientList[iClientH]->m_iHPstock = 0;
}

int CGame::iCalculateAttackEffect(short sTargetH, char cTargetType, short sAttackerH, char cAttackerType, int tdX, int tdY, int iAttackMode, BOOL bNearAttack, BOOL bIsDash, BOOL bArrowUse, BOOL bMainGaucheAttack)
{
 int    iAP_SM, iAP_L, iAttackerHitRatio, iTargetDefenseRatio, iDestHitRatio, iResult, iAP_Abs_Armor, iAP_Abs_Shield, iAP_Abs_Cape;
 char   cAttackerName[21], cAttackerDir, cAttackerSide, cTargetDir, cProtect, cCropSkill, cFarmingSkill;
 short  sWeaponIndex, sAttackerWeapon, dX, dY, sX, sY, sAtkX, sAtkY, sTgtX, sTgtY;
 DWORD  dwTime;
 WORD   wWeaponType;
 double dTmp1, dTmp2, dTmp3;
 BOOL   bKilled;
 BOOL   bNormalMissileAttack;
 BOOL   bIsAttackerBerserk;
 int    iKilledDice, iDamage, iWepLifeOff, iSideCondition, iMaxSuperAttack, iWeaponSkill, iComboBonus, iTemp;
 int    iAttackerHP, iMoveDamage, iRepDamage;
 char   cAttackerSA;
 int    iAttackerSAvalue, iHitPoint, iFarmingSSN;
 char   cDamageMoveDir;
 int    iPartyID, iConstructionPoint, iWarContribution, tX, tY, iDst1, iDst2;
 short	sItemIndex;
 short	sSkillUsed;
 unsigned long iExp;

	dwTime = timeGetTime();
	bKilled = FALSE;
	iExp = 0;
	iPartyID = 0;
	bNormalMissileAttack = FALSE;
	ZeroMemory(cAttackerName, sizeof(cAttackerName));
	cAttackerSA      = NULL;
	iAttackerSAvalue = NULL;
	wWeaponType      = NULL;

	switch (cAttackerType) {
	case DEF_OWNERTYPE_PLAYER:

		if (m_pClientList[sAttackerH] == NULL) return 0;
		//LifeX Fix Admin Hit NPC
		if ((m_pClientList[sAttackerH]->m_iAdminUserLevel == 2) || (m_pClientList[sAttackerH]->m_iAdminUserLevel == 3))
		{
			SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_IPACCOUNTINFO, NULL, NULL, NULL, "You cannot do any damage as a GM.");
			return 0;
		}
		if ((m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsAttackEnabled == FALSE) && (m_pClientList[sAttackerH]->m_iAdminUserLevel == 0)) return 0;
		
		if (   (m_bIsHeldenianMode == TRUE)				
			&& (m_bHeldenianWarInitiated == FALSE)			// No attack work before war has begun
			&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex] != 0) 
			&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsHeldenianMap == 1)) return 0; 

		if (cAttackerType == DEF_OWNERTYPE_NPC) 
		{	if (   ( m_pClientList[sTargetH]->m_bSkillUsingStatus[22] == TRUE )
				&& (iDice(1,100) <= m_pClientList[sTargetH]->m_cSkillMastery[22]) )
				return 0;// SNOOPY, do not attack while Taming in progress
		}

		if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[sAttackerH]->m_bIsPlayerCivil == TRUE) && (cTargetType == DEF_OWNERTYPE_PLAYER)) return 0;

		if ((m_pClientList[sAttackerH]->m_iStatus & 0x10) != 0) {
			SetInvisibilityFlag(sAttackerH, DEF_OWNERTYPE_PLAYER, FALSE);
			bRemoveFromDelayEventList(sAttackerH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_INVISIBILITY);
			m_pClientList[sAttackerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = NULL;
		}
		
		if ((m_pClientList[sAttackerH]->m_sAppr2 & 0xF000) == 0) return 0;

		iAP_SM = 0;
		iAP_L  = 0;

		wWeaponType = ((m_pClientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);

		sSkillUsed = m_pClientList[sAttackerH]->m_sUsingWeaponSkill;
		if ((bIsDash == TRUE) && (m_pClientList[sAttackerH]->m_cSkillMastery[sSkillUsed] != 100) && (wWeaponType != 25) && (wWeaponType != 27)) {
			wsprintf(G_cTxt, "TSearch Fullswing Hack: (%s) Player: (%s) - dashing with only (%d) weapon skill.", m_pClientList[sAttackerH]->m_cIPaddress, m_pClientList[sAttackerH]->m_cCharName, m_pClientList[sAttackerH]->m_cSkillMastery[sSkillUsed]);
			PutHackLogFileList(G_cTxt);
			DeleteClient(sAttackerH, TRUE, TRUE);
			return 0;
		}

		cAttackerSide = m_pClientList[sAttackerH]->m_cSide;

		// SNOOPY Added a 2nd attack if character has a MainGauche.
		if (bMainGaucheAttack)
		{	sSkillUsed = 20;
			iAttackerHitRatio = m_pClientList[sAttackerH]->m_iHitRatio + m_pClientList[sAttackerH]->m_cSkillMastery[20];			
			if ( iAttackerHitRatio < 1 ) iAttackerHitRatio = 1;
			// Compute damage
			iAP_SM = iDice(1, 6);
			iAP_L  = iDice(1, 8);
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) != NULL) 
			{	int dwSWEType  = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) >> 20;  
				int dwSWEValue = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x000F0000) >> 16;
				// CriticalDamage && Poison Damage will have no effect on armors & MainGauche
				switch (dwSWEType) {
				case 7: // Sharp
					iAP_SM = iDice(1, 7);
					iAP_L  = iDice(1, 9);				
					break;
				case 9: // Ancient
					iAP_SM = iDice(1, 8);
					iAP_L  = iDice(1, 10);
					break;				
			}	}

			dTmp1 = (double)iAP_SM;
			if (m_pClientList[sAttackerH]->m_iStr <= 0)
				 dTmp2 = 1.0f;
			else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iStr + m_pClientList[sAttackerH]->m_iAngelicStr);

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_SM = (int)(dTmp3 +0.5f);

			dTmp1 = (double)iAP_L;
			if (m_pClientList[sAttackerH]->m_iStr <= 0)
				 dTmp2 = 1.0f;
			else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iStr + m_pClientList[sAttackerH]->m_iAngelicStr);

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_L = (int)(dTmp3 +0.5f);
		}else
				
		if (wWeaponType == 0) {
			iAP_SM = iAP_L    = iDice(1, ((m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr) / 12));
			if (iAP_SM <= 0) iAP_SM = 1;
			if (iAP_L  <= 0) iAP_L  = 1;
			iAttackerHitRatio = m_pClientList[sAttackerH]->m_iHitRatio + m_pClientList[sAttackerH]->m_cSkillMastery[5];
			m_pClientList[sAttackerH]->m_sUsingWeaponSkill = 5 ;

		}
		else if ((wWeaponType >= 1) && (wWeaponType < 40)) {
			iAP_SM = iDice(m_pClientList[sAttackerH]->m_cAttackDiceThrow_SM, m_pClientList[sAttackerH]->m_cAttackDiceRange_SM);
			iAP_L  = iDice(m_pClientList[sAttackerH]->m_cAttackDiceThrow_L, m_pClientList[sAttackerH]->m_cAttackDiceRange_L);

			iAP_SM += m_pClientList[sAttackerH]->m_cAttackBonus_SM;
			iAP_L  += m_pClientList[sAttackerH]->m_cAttackBonus_L;

			iAttackerHitRatio = m_pClientList[sAttackerH]->m_iHitRatio;

			dTmp1 = (double)iAP_SM;
			if ((m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr) <= 0)
				dTmp2 = 1.0f;
			else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr);

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_SM = (int)(dTmp3 +0.5f);

			dTmp1 = (double)iAP_L;
			if ((m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr) <= 0)
				dTmp2 = 1.0f;
			else dTmp2 = (double)(m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr);

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_L = (int)(dTmp3 +0.5f);
		}
		else if (wWeaponType >= 40) {
			iAP_SM = iDice(m_pClientList[sAttackerH]->m_cAttackDiceThrow_SM, m_pClientList[sAttackerH]->m_cAttackDiceRange_SM);
			iAP_L  = iDice(m_pClientList[sAttackerH]->m_cAttackDiceThrow_L, m_pClientList[sAttackerH]->m_cAttackDiceRange_L);

			iAP_SM += m_pClientList[sAttackerH]->m_cAttackBonus_SM;
			iAP_L  += m_pClientList[sAttackerH]->m_cAttackBonus_L;

			iAttackerHitRatio = m_pClientList[sAttackerH]->m_iHitRatio;
			bNormalMissileAttack = TRUE;

			iAP_SM += iDice(1, ((m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr) / 20));
			iAP_L  += iDice(1, ((m_pClientList[sAttackerH]->m_iStr+m_pClientList[sAttackerH]->m_iAngelicStr) / 20));
		}
	
		iAttackerHitRatio += 50;
		if (iAP_SM <= 0) iAP_SM = 1;
		if (iAP_L  <= 0) iAP_L  = 1;

		if (m_pClientList[sAttackerH]->m_iCustomItemValue_Attack != 0) {
			if ((m_pClientList[sAttackerH]->m_iMinAP_SM != 0) && (iAP_SM < m_pClientList[sAttackerH]->m_iMinAP_SM)) {
				iAP_SM = m_pClientList[sAttackerH]->m_iMinAP_SM;
			}
			if ((m_pClientList[sAttackerH]->m_iMinAP_L != 0) && (iAP_L < m_pClientList[sAttackerH]->m_iMinAP_L)) {
				iAP_L = m_pClientList[sAttackerH]->m_iMinAP_L;
			}
			if ((m_pClientList[sAttackerH]->m_iMaxAP_SM != 0) && (iAP_SM > m_pClientList[sAttackerH]->m_iMaxAP_SM)) {
				iAP_SM = m_pClientList[sAttackerH]->m_iMaxAP_SM;
			}
			if ((m_pClientList[sAttackerH]->m_iMaxAP_L != 0) && (iAP_L > m_pClientList[sAttackerH]->m_iMaxAP_L)) {
				iAP_L = m_pClientList[sAttackerH]->m_iMaxAP_L;
			}
		}

		if (m_pClientList[sAttackerH]->m_cHeroArmourBonus == 1) {
			iAttackerHitRatio += 100;
			iAP_SM += 5;
			iAP_L += 5;
		}

		sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
		if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 851) || // KlonessEsterk 
				(m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 863) || // KlonessWand(MS.20)
				(m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 864)) { // KlonessWand(MS.10) 
				if (m_pClientList[sAttackerH]->m_iRating > 0) {
					iRepDamage = m_pClientList[sAttackerH]->m_iRating/10;
					iAP_SM += iRepDamage;
					iAP_L += iRepDamage;
				}
				if (cTargetType == DEF_OWNERTYPE_PLAYER) {
					if (m_pClientList[sTargetH] == NULL) return 0;
					if (m_pClientList[sTargetH]->m_iRating <= 0) {
						iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/10);
						iAP_SM += iRepDamage;
						iAP_L += iRepDamage;
					}
				}
			}
			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 861) || // BerserkWand(MS.20)
				(m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 862)) { // BerserkWand(MS.10)
				iAttackerHitRatio *= 1.5f;
				iAP_SM ++;
				iAP_L ++;
			}
		}

		sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
		if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
			
			if (   (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 616) // DemonSlayer	
				&& (cTargetType == DEF_OWNERTYPE_NPC)) 
			{	if ( m_pNpcList[sTargetH]->m_sType == 31) 
				{	iAttackerHitRatio += 100;
					iAP_L += iDice(1,((2*iAP_L)/3));							
			}	}

			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 847) && 
				(m_cDayOrNight == 2)) {
					iAP_SM += 4;
					iAP_L += 4;
			}
			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 848) && 
				(m_cDayOrNight == 1)) {
					iAP_SM += 4;
					iAP_L += 4;
			}
			if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 849) || // KlonessBlade 
				(m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 850)) { // KlonessAxe
				if (m_pClientList[sAttackerH]->m_iRating > 0) {
					iRepDamage = m_pClientList[sAttackerH]->m_iRating/10;
					iAP_SM += iRepDamage;
					iAP_L += iRepDamage;
				}
				if (cTargetType == DEF_OWNERTYPE_PLAYER) {
					if (m_pClientList[sTargetH] == NULL) return 0;
					if (m_pClientList[sTargetH]->m_iRating <= 0) {
						iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/10);
						iAP_SM += iRepDamage;
						iAP_L += iRepDamage;
					}
				}
			}
		}

		sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_NECK];
		if ((sItemIndex != -1) && (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {
			if (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 859) { // NecklaceOfKloness  
				if (cTargetType == DEF_OWNERTYPE_PLAYER) {
					if (m_pClientList[sTargetH] == NULL) return 0;
						iRepDamage = (abs(m_pClientList[sTargetH]->m_iRating)/20);
						iAP_SM += iRepDamage;
						iAP_L += iRepDamage;
				}
			}
		}

		cAttackerDir = m_pClientList[sAttackerH]->m_cDir;
		strcpy(cAttackerName, m_pClientList[sAttackerH]->m_cCharName);

		if (m_pClientList[sAttackerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0)
			bIsAttackerBerserk = TRUE;
		else bIsAttackerBerserk = FALSE;
		
		if ((bArrowUse != TRUE) && (m_pClientList[sAttackerH]->m_iSuperAttackLeft > 0) && (iAttackMode >= 20)) {

			dTmp1 = (double)iAP_SM;
			dTmp2 = (double)(m_pClientList[sAttackerH]->m_iLevel+ m_pClientList[sAttackerH]->m_iMajesticLevel);
			dTmp3 = dTmp2 / 100.0f;
			dTmp2 = dTmp1 * dTmp3;
			iTemp = (int)(dTmp2 +0.5f);
			iAP_SM += iTemp;

			dTmp1 = (double)iAP_L;
			dTmp2 = (double)(m_pClientList[sAttackerH]->m_iLevel+ m_pClientList[sAttackerH]->m_iMajesticLevel);
			dTmp3 = dTmp2 / 100.0f;
			dTmp2 = dTmp1 * dTmp3;
			iTemp = (int)(dTmp2 +0.5f);
			iAP_L += iTemp;

			switch (m_pClientList[sAttackerH]->m_sUsingWeaponSkill) {
				case 6:  iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10); iAttackerHitRatio  += 30 ; break;
				case 7:  iAP_SM *= 1.5f; iAP_L *= 1.5f; break;				
				case 8:  iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10); iAttackerHitRatio += 30 ; break;
				case 10:  iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5) ;                           break;
				case 14:  iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5) ; iAttackerHitRatio += 20 ; break;
				case 21:  iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5); iAttackerHitRatio +=  50 ; break;
				default: break;
			}
			iAttackerHitRatio += 100 + m_pClientList[sAttackerH]->m_iCustomItemValue_Attack;
		}
		if (bIsDash == TRUE) {
			iAttackerHitRatio += 20;
			switch (m_pClientList[sAttackerH]->m_sUsingWeaponSkill) {
				case 8:  iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10); break;
				case 10: iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);break;
				case 14: iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);break;
				default: break;
			}
		}
		iAttackerHP = m_pClientList[sAttackerH]->m_iHP;
		iAttackerHitRatio += m_pClientList[sAttackerH]->m_iAddAR;
		sAtkX = m_pClientList[sAttackerH]->m_sX;
		sAtkY = m_pClientList[sAttackerH]->m_sY;
		iPartyID = m_pClientList[sAttackerH]->m_iPartyID;
		break;

	case DEF_OWNERTYPE_NPC:

		if (m_pNpcList[sAttackerH] == NULL) return 0;
		if (m_pMapList[m_pNpcList[sAttackerH]->m_cMapIndex]->m_bIsAttackEnabled == FALSE) return 0;

		if ((m_pNpcList[sAttackerH]->m_iStatus & 0x10) != 0) {
			SetInvisibilityFlag(sAttackerH, DEF_OWNERTYPE_NPC, FALSE);
			bRemoveFromDelayEventList(sAttackerH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_INVISIBILITY);
			m_pNpcList[sAttackerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = NULL;
		}

		cAttackerSide = m_pNpcList[sAttackerH]->m_cSide;
		iAP_SM = 0;
		iAP_L  = 0;

		if (m_pNpcList[sAttackerH]->m_cAttackDiceThrow != 0) 
			iAP_L = iAP_SM = iDice(m_pNpcList[sAttackerH]->m_cAttackDiceThrow, m_pNpcList[sAttackerH]->m_cAttackDiceRange);

		iAttackerHitRatio = m_pNpcList[sAttackerH]->m_iHitRatio;

		cAttackerDir = m_pNpcList[sAttackerH]->m_cDir;
		memcpy(cAttackerName, m_pNpcList[sAttackerH]->m_cNpcName, 20);

		if (m_pNpcList[sAttackerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_BERSERK] != 0)
			bIsAttackerBerserk = TRUE;
		else bIsAttackerBerserk = FALSE;

		iAttackerHP = m_pNpcList[sAttackerH]->m_iHP;
		cAttackerSA = m_pNpcList[sAttackerH]->m_cSpecialAbility;

		sAtkX = m_pNpcList[sAttackerH]->m_sX;
		sAtkY = m_pNpcList[sAttackerH]->m_sY;

		// Check for arrow attack
		switch (m_pNpcList[sAttackerH]->m_sType) {
		case 54: // Dark-Elf				
			// No more "not arrow attack if close" (was buggy)
			bNormalMissileAttack = TRUE; 	
			break;
		default:		
			break;
		}
		break;
	}

	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:

		if (m_pClientList[sTargetH] == NULL) return 0;
		if (m_pClientList[sTargetH]->m_bIsKilled == TRUE) return 0;
		if ((m_pClientList[sTargetH]->m_iStatus & 0x400000) != 0) return 0;

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == FALSE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsPlayerCivil == TRUE)) return 0;
				
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sTargetH]->m_bIsNeutral == TRUE) && 
			(m_pClientList[sTargetH]->m_iPKCount == 0) && (m_pClientList[sTargetH]->m_bIsOwnLocation == TRUE)) return 0;
		
		if ((m_pClientList[sTargetH]->m_sX != tdX) || (m_pClientList[sTargetH]->m_sY != tdY)) return 0;

		if (m_pClientList[sTargetH]->m_iAdminUserLevel > 0) return 0; 

		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH]->m_bIsNeutral == TRUE) 
			&& (m_pClientList[sTargetH]->m_iPKCount == 0)) return 0;

		if ((m_pClientList[sTargetH]->m_iPartyID != NULL) && (iPartyID == m_pClientList[sTargetH]->m_iPartyID)) return 0;

		cTargetDir = m_pClientList[sTargetH]->m_cDir;
		iTargetDefenseRatio = m_pClientList[sTargetH]->m_iDefenseRatio;
		m_pClientList[sTargetH]->m_dwLogoutHackCheck = dwTime;
		if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH]->m_bIsSafeAttackMode == TRUE)) { 
			iSideCondition = iGetPlayerRelationship(sAttackerH, sTargetH);
			if ((iSideCondition == 7) || (iSideCondition == 2) || (iSideCondition == 6)) {
				iAP_SM = iAP_SM / 2;
				iAP_L  = iAP_L / 2;
			}
			else {
				if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
					if (m_pClientList[sAttackerH]->m_iGuildGUID == m_pClientList[sTargetH]->m_iGuildGUID) return 0;
					else {
						iAP_SM = iAP_SM / 2;
						iAP_L  = iAP_L / 2;
					}
				}
				else return 0;
			}
		}

		iTargetDefenseRatio += m_pClientList[sTargetH]->m_iAddDR;

		sTgtX = m_pClientList[sTargetH]->m_sX;
		sTgtY = m_pClientList[sTargetH]->m_sY;
		break;

	case DEF_OWNERTYPE_NPC:

		if (m_pNpcList[sTargetH] == NULL) return 0;
		if (m_pNpcList[sTargetH]->m_iHP <= 0) return 0;

		if ((m_pNpcList[sTargetH]->m_sX != tdX) || (m_pNpcList[sTargetH]->m_sY != tdY)) return 0;

		cTargetDir = m_pNpcList[sTargetH]->m_cDir;
		iTargetDefenseRatio = m_pNpcList[sTargetH]->m_iDefenseRatio;

		if (cAttackerType == DEF_OWNERTYPE_PLAYER) 
		{	switch (m_pNpcList[sTargetH]->m_sType) {
			case 40: // ESG
			case 41: // GMG
				if ((m_pClientList[sAttackerH]->m_cSide == 0) || (m_pNpcList[sTargetH]->m_cSide == m_pClientList[sAttackerH]->m_cSide)) return 0;
				break;
			case 36: // AGT
			case 37: // CGT
			case 38: // MS
			case 39: // DT		
				// Snoopy added Tile where you can't stay (behind crusade structures) 
				// If you try to stay behind and accept normal punition, damage is worse and at each attack...
				if (   (m_bIsCrusadeMode == TRUE)
					&& (m_pClientList[sAttackerH]->m_iAdminUserLevel == 0)
					&& (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->bGetIsStayAllowedTile(m_pClientList[sAttackerH]->m_sX, m_pClientList[sAttackerH]->m_sY) == FALSE))
				{	char iDir = (char)iDice(1,7);
					if (iDir >= 5) iDir ++;
					int iDamage = m_pClientList[sAttackerH]->m_iHP/8 + iDice(1,20) + iAP_SM;					
					if (iDamage < 40) iDamage = 30 + iDice(1,20);
					if (iDamage > m_pClientList[sAttackerH]->m_iHP) iDamage = m_pClientList[sAttackerH]->m_iHP -1;
					m_pClientList[sAttackerH]->m_iHP -= iDamage;					
					m_pClientList[sAttackerH]->m_iLastDamage = iDamage;
					m_pClientList[sAttackerH]->m_dwRecentAttackTime = dwTime;
					SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_DAMAGEMOVE, iDir, iDamage, 0, NULL);					
					iAP_SM = iAP_SM/2; 
					iAP_L = iAP_L/2;
				}
				break;
			} 

			if (   (wWeaponType == 25) && (m_pNpcList[sTargetH]->m_cActionLimit == 5) 
				&& (m_pNpcList[sTargetH]->m_iBuildCount > 0)) 
			{	if ((m_pClientList[sAttackerH]->m_iCrusadeDuty != 2) && (m_pClientList[sAttackerH]->m_iAdminUserLevel == 0)) break;
				switch (m_pNpcList[sTargetH]->m_sType) {
				case 36: // AGT
				case 37: // CGT
				case 38: // MS
				case 39: // DT
					// administrators instantly build crusade structures
					// SNOOPY: was buugy because those structure woundn't Attack due to a m_iBuildCount = 0 value....
					if (m_pClientList[sAttackerH]->m_iAdminUserLevel > 0) 
					{	m_pNpcList[sTargetH]->m_sAppr2 = 0;
						m_pNpcList[sTargetH]->m_iBuildCount = 1;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
					}				
					switch (m_pNpcList[sTargetH]->m_iBuildCount) {
					case 1:
						m_pNpcList[sTargetH]->m_sAppr2 = 0;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						// SNOOPY: Will not send those message outside crusades...
						if (m_bIsCrusadeMode == TRUE) 
						{	switch (m_pNpcList[sTargetH]->m_sType) {
							case 36: iConstructionPoint = 700; iWarContribution = 700; break;
							case 37: iConstructionPoint = 700; iWarContribution = 700; break;
							case 38: iConstructionPoint = 500; iWarContribution = 500; break;
							case 39: iConstructionPoint = 500; iWarContribution = 500; break;
							}
							// Snoopy: Forbid Tile behind finished crusade structure
							m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->SetStayAllowedFlag(m_pNpcList[sTargetH]->m_sX, m_pNpcList[sTargetH]->m_sY-1, FALSE);
							m_pClientList[sAttackerH]->m_iWarContribution   += iWarContribution;
							

							wsprintf(G_cTxt, "Construction Complete: PC(%s) - WarContribution +%d"
								, m_pClientList[sAttackerH]->m_cCharName
								, iWarContribution);
							PutLogList(G_cTxt);
							PutLogEventFileList(G_cTxt);
							SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[sAttackerH]->m_iConstructionPoint, m_pClientList[sAttackerH]->m_iWarContribution, NULL, NULL);
						}
						break;
					case 5:
						m_pNpcList[sTargetH]->m_sAppr2 = 1;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						break;
					case 10:
						m_pNpcList[sTargetH]->m_sAppr2 = 2;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						break;
					}
					break;
				}
				
				m_pNpcList[sTargetH]->m_iBuildCount--;
				if (m_pNpcList[sTargetH]->m_iBuildCount <= 0) {
					m_pNpcList[sTargetH]->m_iBuildCount = 0;
				}
				return 0;
			}
			if (   (wWeaponType == 27) && (m_pNpcList[sTargetH]->m_cCropType != 0) 
				&& (m_pNpcList[sTargetH]->m_cActionLimit == 5) && (m_pNpcList[sTargetH]->m_iBuildCount > 0)) 
			{	cFarmingSkill = m_pClientList[sAttackerH]->m_cSkillMastery[2];
				cCropSkill = m_pNpcList[sTargetH]->m_cCropSkill;
				if (cFarmingSkill < 20) return 0;
				if (m_pClientList[sAttackerH]->m_iLevel < 20) return 0;
				switch(m_pNpcList[sTargetH]->m_sType) {
				case 64:
					// There skill increase only if needed skill is less than 10% over the minimum skill for such crop
					// Only count once per seedbag if over mimi Skill +10%
					iFarmingSSN = 1;
					if (cFarmingSkill <= (cCropSkill + 10)) 
					{	iFarmingSSN = 1;
					}else 
					{	iFarmingSSN = 0;
					}
					switch(m_pNpcList[sTargetH]->m_iBuildCount) {
					case 1:	
						m_pNpcList[sTargetH]->m_sAppr2 = 3;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						//sub_4B67E0
						CalculateSSN_SkillIndex(sAttackerH, 2, 1); 
						_CheckFarmingAction(sAttackerH, sTargetH, 1);
						DeleteNpc(sTargetH);
						return 0;
					case 8:	
						m_pNpcList[sTargetH]->m_sAppr2 = 3;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						CalculateSSN_SkillIndex(sAttackerH, 2, iFarmingSSN);
						_CheckFarmingAction(sAttackerH, sTargetH, 0);
						m_pNpcList[sTargetH]->m_iBuildCount--;
						break;
					case 18:
						m_pNpcList[sTargetH]->m_sAppr2 = 2;
						SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTNULLACTION, NULL, NULL, NULL);
						CalculateSSN_SkillIndex(sAttackerH, 2, iFarmingSSN);
						_CheckFarmingAction(sAttackerH, sTargetH, 0);
						// 1/20 chance to have 4 crops
						if (iDice(1,20) != 2)  m_pNpcList[sTargetH]->m_iBuildCount--;
						break;
					default:
						// SNOOPY Added a Skill Check to slow down a bit the process.
						// With minima Skill will cost twice the time
						if (   ((iDice(1,100) <= ((50+cFarmingSkill)-(cCropSkill)))// Chance off succes depends on skill
							|| (iDice(1,100)) <6 )) { // 1/20 chace of succes  ever skill you have
							m_pNpcList[sTargetH]->m_iBuildCount--;
						}
						break;
					}
					break;
				}
				// Useless? safety check !			
				if (m_pNpcList[sTargetH]->m_iBuildCount <= 0) 
				{	m_pNpcList[sTargetH]->m_iBuildCount = 0;
				}
				// They forgot to put Hoe deplession here..
				// Weapon's wep life off				
				sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
				if ( sWeaponIndex != -1)
				{	m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan--;
					if (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan < 1)
						m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan = 0;
					// then notify the client...
					if (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan == 0)
					{	SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_cEquipPos, sWeaponIndex, NULL, NULL);
						ReleaseItemHandler(sAttackerH, sWeaponIndex, TRUE);
				}	}
				return 0;
		}	}

		sTgtX = m_pNpcList[sTargetH]->m_sX;
		sTgtY = m_pNpcList[sTargetH]->m_sY;
		break;
	}

	if ( (cAttackerType == DEF_OWNERTYPE_PLAYER) && (cTargetType == DEF_OWNERTYPE_PLAYER) ) {

		sX = m_pClientList[sAttackerH]->m_sX;
		sY = m_pClientList[sAttackerH]->m_sY;

		dX = m_pClientList[sTargetH]->m_sX;
		dY = m_pClientList[sTargetH]->m_sY;

		if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000006) != 0) return 0;
		if (m_pMapList[m_pClientList[sTargetH]->m_cMapIndex]->iGetAttribute(dX, dY, 0x00000006) != 0) return 0;
	}

	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		if ((m_pClientList[sAttackerH]->m_iDex+m_pClientList[sAttackerH]->m_iAngelicDex) > 50) {
			iAttackerHitRatio += ((m_pClientList[sAttackerH]->m_iDex+m_pClientList[sAttackerH]->m_iAngelicDex) - 50); 	
		}
	}

	if (wWeaponType >= 40) {
		switch (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cWhetherStatus) {
		case 0:	break;
		case 1:	iAttackerHitRatio -= (iAttackerHitRatio / 20); break;
		case 2:	iAttackerHitRatio -= (iAttackerHitRatio / 10); break;
		case 3:	iAttackerHitRatio -= (iAttackerHitRatio / 4);  break;
		}
	}

	if (iAttackerHitRatio < 0)   iAttackerHitRatio = 0;    
	switch (cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		cProtect = m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT];
		break;

	case DEF_OWNERTYPE_NPC:
		cProtect = m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT]; 
		break;
	}

	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		if (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1) {
			if (m_pClientList[sAttackerH]->m_pItemList[m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND]] == NULL) {
				m_pClientList[sAttackerH]->m_bIsItemEquipped[m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND]] = FALSE;
				DeleteClient(sAttackerH, TRUE, TRUE);
				return 0;
			}

			if (m_pClientList[sAttackerH]->m_pItemList[m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND]]->m_sItemEffectType == DEF_ITEMEFFECTTYPE_ATTACK_ARROW) {
				if (m_pClientList[sAttackerH]->m_cArrowIndex == -1) {
					return 0;
				}
				else {
					if (m_pClientList[sAttackerH]->m_pItemList[m_pClientList[sAttackerH]->m_cArrowIndex] == NULL) 
						return 0;

					if (bArrowUse != TRUE)
						m_pClientList[sAttackerH]->m_pItemList[m_pClientList[sAttackerH]->m_cArrowIndex]->m_dwCount--;
					if (m_pClientList[sAttackerH]->m_pItemList[ m_pClientList[sAttackerH]->m_cArrowIndex ]->m_dwCount <= 0) {

						ItemDepleteHandler(sAttackerH, m_pClientList[sAttackerH]->m_cArrowIndex, FALSE, TRUE);
						m_pClientList[sAttackerH]->m_cArrowIndex = _iGetArrowItemIndex(sAttackerH);
					}
					else {
						SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_SETITEMCOUNT, m_pClientList[sAttackerH]->m_cArrowIndex, m_pClientList[sAttackerH]->m_pItemList[ m_pClientList[sAttackerH]->m_cArrowIndex ]->m_dwCount, FALSE, NULL);
						iCalcTotalWeight(sAttackerH);
					}
				}
				if (cProtect == 1) return 0;
			}
			else {
				switch (cProtect) {
				case 3: iTargetDefenseRatio += 40;  break;
				case 4: iTargetDefenseRatio += 100; break;
				}
				if (iTargetDefenseRatio < 0) iTargetDefenseRatio = 1;
			}
		}
	}
	else {
		switch (cProtect) {
		case 1: 
			switch (m_pNpcList[sAttackerH]->m_sType) {
				case 54:
					if ((abs(sTgtX - m_pNpcList[sAttackerH]->m_sX) >= 1) || (abs(sTgtY - m_pNpcList[sAttackerH]->m_sY) >= 1)) return 0; 
					break;
			}
			break;
		case 3: iTargetDefenseRatio += 40;  break;
		case 4: iTargetDefenseRatio += 100; break;
		}
		if (iTargetDefenseRatio < 0) iTargetDefenseRatio = 1;
	}

	if (cAttackerDir == cTargetDir) iTargetDefenseRatio = iTargetDefenseRatio / 2;
	if (iTargetDefenseRatio < 1)   iTargetDefenseRatio = 1;

	dTmp1 = (double)(iAttackerHitRatio);
	dTmp2 = (double)(iTargetDefenseRatio);
	dTmp3 = (dTmp1 / dTmp2) * 50.0f;
	iDestHitRatio = (int)(dTmp3); 


	if ((bIsAttackerBerserk == TRUE) && (iAttackMode < 20)) {
		iAP_SM *= 2;
		iAP_L  *= 2;
	}

	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		iAP_SM += m_pClientList[sAttackerH]->m_iAddPhysicalDamage;
		iAP_L  += m_pClientList[sAttackerH]->m_iAddPhysicalDamage;
	}

	if (bNearAttack == TRUE) {
		iAP_SM = iAP_SM / 2;
		iAP_L  = iAP_L / 2;
	}

	if (cTargetType == DEF_OWNERTYPE_PLAYER) {
		iAP_SM -= (iDice(1, m_pClientList[sTargetH]->m_iVit/10) - 1);
		iAP_L  -= (iDice(1, m_pClientList[sTargetH]->m_iVit/10) - 1);
	}

	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		if (iAP_SM <= 1) iAP_SM = 1;
		if (iAP_L  <= 1) iAP_L  = 1;
	}
	else {
		if (iAP_SM <= 0) iAP_SM = 0;
		if (iAP_L  <= 0) iAP_L  = 0;
	}

	// Centuu : Ranged Hit Fix - HB2
	BOOL bRangedWeapon = FALSE;
	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
		if (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)
			 sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
		else sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
		if (sWeaponIndex != -1)	{
			if (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_sRelatedSkill == 6) {
				bRangedWeapon = TRUE;
			}
		}
		switch (cTargetType) {
		case DEF_OWNERTYPE_PLAYER:
			if (m_pClientList[sAttackerH]->m_sX > m_pClientList[sTargetH]->m_sX) {
				if ((m_pClientList[sAttackerH]->m_sX - m_pClientList[sTargetH]->m_sX) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pClientList[sTargetH]->m_sX > m_pClientList[sAttackerH]->m_sX) {
				if ((m_pClientList[sTargetH]->m_sX - m_pClientList[sAttackerH]->m_sX) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pClientList[sAttackerH]->m_sY > m_pClientList[sTargetH]->m_sY) {
				if ((m_pClientList[sAttackerH]->m_sY - m_pClientList[sTargetH]->m_sY) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pClientList[sTargetH]->m_sY > m_pClientList[sAttackerH]->m_sY) {
				if ((m_pClientList[sTargetH]->m_sY - m_pClientList[sAttackerH]->m_sY) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			break;
		case DEF_OWNERTYPE_NPC:
			if (m_pClientList[sAttackerH]->m_sX > m_pNpcList[sTargetH]->m_sX) {
				if ((m_pClientList[sAttackerH]->m_sX - m_pNpcList[sTargetH]->m_sX) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pNpcList[sTargetH]->m_sX > m_pClientList[sAttackerH]->m_sX) {
				if ((m_pNpcList[sTargetH]->m_sX - m_pClientList[sAttackerH]->m_sX) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pClientList[sAttackerH]->m_sY > m_pNpcList[sTargetH]->m_sY) {
				if ((m_pClientList[sAttackerH]->m_sY - m_pNpcList[sTargetH]->m_sY) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			if (m_pNpcList[sTargetH]->m_sY > m_pClientList[sAttackerH]->m_sY) {
				if ((m_pNpcList[sTargetH]->m_sY - m_pClientList[sAttackerH]->m_sY) > 1) {
					if ((bRangedWeapon != TRUE) && (iAttackMode < 20)) return 0;
				}
			}
			break;
		}
	}

	iResult = iDice(1, 100);

	if (iResult <= iDestHitRatio) {
		if (   (m_bHeldenianWarInitiated == TRUE)
			&& (bCheckHeldenianMap(sAttackerH, cAttackerType) == TRUE))
		{	iAP_SM += iAP_SM/3;
			iAP_L  += iAP_L/3;
		}
		if (cAttackerType == DEF_OWNERTYPE_PLAYER) {

			if (((m_pClientList[sAttackerH]->m_iHungerStatus <= 10) || (m_pClientList[sAttackerH]->m_iSP <= 0)) && (iDice(1,10) == 5)) return FALSE;	
			m_pClientList[sAttackerH]->m_iComboAttackCount++;
			if (m_pClientList[sAttackerH]->m_iComboAttackCount < 0) m_pClientList[sAttackerH]->m_iComboAttackCount = 0;
			if (m_pClientList[sAttackerH]->m_iComboAttackCount > 4) m_pClientList[sAttackerH]->m_iComboAttackCount = 1;
			iWeaponSkill = _iGetWeaponSkillType(sAttackerH);
			iComboBonus = iGetComboAttackBonus(iWeaponSkill, m_pClientList[sAttackerH]->m_iComboAttackCount);

			if ((m_pClientList[sAttackerH]->m_iComboAttackCount > 1) && (m_pClientList[sAttackerH]->m_iAddCD != NULL))
				iComboBonus += m_pClientList[sAttackerH]->m_iAddCD;

			iAP_SM += iComboBonus;
			iAP_L  += iComboBonus;

			switch (m_pClientList[sAttackerH]->m_iSpecialWeaponEffectType) {
				case 0: break;
				case 1:
					if ((m_pClientList[sAttackerH]->m_iSuperAttackLeft > 0) && (iAttackMode >= 20)) {
						iAP_SM += m_pClientList[sAttackerH]->m_iSpecialWeaponEffectValue;
						iAP_L  += m_pClientList[sAttackerH]->m_iSpecialWeaponEffectValue;
					}
					break;

				case 2:
					cAttackerSA = 61;
					iAttackerSAvalue = m_pClientList[sAttackerH]->m_iSpecialWeaponEffectValue*5; 
					break;

				case 3:
					cAttackerSA = 62;
					break;
			}

			if (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
				iAP_SM += iAP_SM/3;
				iAP_L  += iAP_L/3;
			}

			if (bCheckHeldenianMap(sAttackerH, DEF_OWNERTYPE_PLAYER) == 1) {
				iAP_SM += iAP_SM/3;
				iAP_L  += iAP_L/3;
			}
			
			if ((cTargetType == DEF_OWNERTYPE_PLAYER) && (m_bIsCrusadeMode == TRUE) && (m_pClientList[sAttackerH]->m_iCrusadeDuty == 1)) {
				if (m_pClientList[sAttackerH]->m_iLevel <= 80) {
					iAP_SM += iAP_SM;
					iAP_L += iAP_L;
				}
				else if (m_pClientList[sAttackerH]->m_iLevel > 80 && m_pClientList[sAttackerH]->m_iLevel <= 100) {
					iAP_SM += (iAP_SM* 7)/10;
					iAP_L += (iAP_L* 7)/10;
				} else if (m_pClientList[sAttackerH]->m_iLevel > 100) {
					iAP_SM += iAP_SM/3;
					iAP_L += iAP_L/3;
				}
			}
		}

		switch (cTargetType) 
		{
		case DEF_OWNERTYPE_PLAYER:
			ClearSkillUsingStatus(sTargetH);
			if ((dwTime - m_pClientList[sTargetH]->m_dwTime) > DEF_RAGPROTECTIONTIME) {
				return 0;
			}
			else {
				switch (cAttackerSA) {
					case 62:
						if (m_pClientList[sTargetH]->m_iRating < 0) {
							iTemp = abs(m_pClientList[sTargetH]->m_iRating)/10;
							if (iTemp > 10) iTemp = 10;
							iAP_SM += iTemp;
						}
						break;
				}

				iAP_Abs_Armor  = 0;
				iAP_Abs_Shield = 0;

				iAP_Abs_Cape   = 0;

				iTemp = iDice(1,10000);
				if ((iTemp >= 1) && (iTemp < 5000))           iHitPoint = 1;
				else if ((iTemp >= 5000) && (iTemp < 7500))   iHitPoint = 2;
				else if ((iTemp >= 7500) && (iTemp < 9000))   iHitPoint = 3;
				else if ((iTemp >= 9000) && (iTemp <= 10000)) iHitPoint = 4;

				// PA: Armures
				if (iHitPoint == 2)
				{	if (cAttackerType == DEF_OWNERTYPE_NPC)
					{	switch (m_pNpcList[sAttackerH]->m_sType) {
						case 10: // Slime 
						case 16: // Ant
						case 22: // Snake
						case 55: // Rabbit
						case 56: // Cat
								iHitPoint = 5; // Only boots depleted
								break;
						case 17: // Scorpions 
						case 80: // Tentocle
								iHitPoint = 4 + iDice(1,2); // 5-boots (50%) or 6-both (50%)
								break;
						default: 
							if (iDice(1,3) == 2) iHitPoint = 6; // 6-both (50%)
								break;					
						}
					}else if (cAttackerType == DEF_OWNERTYPE_PLAYER)
					{	if (iDice(1,3) == 2) iHitPoint = 6;
				}	}

				switch (iHitPoint) {
				case 1: // torse
					iAP_Abs_Armor = (double)m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_BODY];
					break;
				case 2: // jambes
					iAP_Abs_Armor = (double)m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_PANTS];
					break;
				case 3:  // bras
					iAP_Abs_Armor = (double)m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_ARMS];
					break;
				case 4: // t�te
					iAP_Abs_Armor = (double)m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_HEAD];
					break;	
				case 5: // Bottes
					iAP_Abs_Armor = (double)m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_LEGGINGS];
					break;	
				case 6: // Bottes et jambes
					if ((m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_PANTS] +
						m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_LEGGINGS]) > 0) 
					{	if ((m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_PANTS] +
							m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_LEGGINGS]) >= 60)
							 iAP_Abs_Armor = 60.0f;
						else iAP_Abs_Armor = (double)(m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_PANTS] + m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_LEGGINGS]);
					}
					break;
				}

				// PA: Shields
				if (m_pClientList[sTargetH]->m_iDamageAbsorption_Shield > 0) 
				{	if (iDice(1,100) <= (m_pClientList[sTargetH]->m_cSkillMastery[11])) 
					{	CalculateSSN_SkillIndex(sTargetH, 11, 1);
						iAP_Abs_Shield = m_pClientList[sTargetH]->m_iDamageAbsorption_Shield;
						// Usure Shield
						iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
						if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL)) 
						{	if ((m_pClientList[sTargetH]->m_cSide != 0) && (m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan > 0))	
								m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan--;
							if (m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan == 0) 
							{	SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[sTargetH]->m_pItemList[iTemp]->m_cEquipPos, iTemp, NULL, NULL);
								ReleaseItemHandler(sTargetH, iTemp, TRUE);
				}	}	}	}
				// PA: Back (capes)  Added Damage absorbtion for enchanted capes  iAP_Abs_Cape
				if (   (cAttackerDir == cTargetDir) // Of course only when attacked from behind !
					&& (m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_BACK] > 0)) 
				{	iAP_Abs_Cape = m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_BACK];
					// Deplete Cape durability in this case	
					iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_BACK];
					if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL)) 
					{	if ((m_pClientList[sTargetH]->m_cSide != 0) && (m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan > 0))	
							m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan--;
						if (m_pClientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan == 0) 
						{	SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[sTargetH]->m_pItemList[iTemp]->m_cEquipPos, iTemp, NULL, NULL);
							ReleaseItemHandler(sTargetH, iTemp, TRUE);
				}	}	}

				// PA: Hammer reduces PA unless if robed...
				if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) 
					&& (m_pClientList[sAttackerH]->m_sUsingWeaponSkill == 14)) 	// PA counts for 3/4 vs Hammers
				{	iAP_Abs_Armor  = iAP_Abs_Armor  - iAP_Abs_Armor/4;
					iAP_Abs_Shield = iAP_Abs_Shield + iAP_Abs_Shield/4;
					// Robes have an extra PA vs hammers
					iAP_Abs_Cape   = iAP_Abs_Cape + m_pClientList[sTargetH]->m_iDamageAbsorption_Armor[DEF_EQUIPPOS_RELEASEALL];
				}

				// PA total: Calculer les d�g�ts restants.
				iAP_Abs_Armor = iAP_Abs_Armor + iAP_Abs_Shield + iAP_Abs_Cape;
				if (iAP_Abs_Armor >= 80) 
					dTmp1 = 80.0f;
				else dTmp1 = (double)iAP_Abs_Armor;
				dTmp2 = (double)iAP_SM;
				dTmp3 = (dTmp1 / 100.0f) * dTmp2;
				iAP_SM = iAP_SM - (int)dTmp3;
				if (iAP_SM <= 0) iAP_SM = 1;

				if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) && (m_pClientList[sAttackerH]->m_bIsSpecialAbilityEnabled == TRUE)) {
					switch (m_pClientList[sAttackerH]->m_iSpecialAbilityType) {
						case 0: break;
						case 1: // Xelima weapon
							iTemp = (m_pClientList[sTargetH]->m_iHP / 2);
							if (iAP_SM <= 0) iAP_SM = 1;
							if (iTemp > iAP_SM) iAP_SM = iTemp;
							break;
						case 2: // Ice weapon
							if (   (bCheckResistingIceSuccess(0, sTargetH, DEF_OWNERTYPE_PLAYER, 50) == FALSE) 
								&& (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] == 0)) 
							{	m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] = 1;
								SetIceFlag(sTargetH, DEF_OWNERTYPE_PLAYER, TRUE);
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + 30000, 
									sTargetH, DEF_OWNERTYPE_PLAYER, NULL, NULL, NULL, 1, NULL, NULL);
								SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, NULL, NULL);
							}
							break;
						case 3: // Medusa sword
							if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] >= 5) break; 
							// Medusa neck or very high PR gives invulnerability, unless having a Medusa Blade...
							if (   ((m_pClientList[sTargetH]->m_cSkillMastery[23] + m_pClientList[sTargetH]->m_iAddPR + iDice(1,100)) >= 250) 
								&& (m_pClientList[sTargetH]->m_iSpecialAbilityType != 3)) break; 
							m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = 5;
							// Nota: The client was fixed to show "paralysed" for any 2+ value
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + 10000, 
								sTargetH, DEF_OWNERTYPE_PLAYER, NULL, NULL, NULL, 5, NULL, NULL);								
							SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_HOLDOBJECT, 5, NULL, NULL);		
							break;
						case 4: // Instant kill weapon
							iAP_SM = (m_pClientList[sTargetH]->m_iHP);
							break;
						case 5: // Vampiric weapon
							m_pClientList[sAttackerH]->m_iHP += iAP_SM;
							if (iGetMaxHP(sAttackerH) < m_pClientList[sAttackerH]->m_iHP)  // BloodEffect limite le regen
								m_pClientList[sAttackerH]->m_iHP = iGetMaxHP(sAttackerH);
							SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
							break;
					}
				}

				if (m_pClientList[sTargetH]->m_bIsSpecialAbilityEnabled == TRUE)
				{	if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL)) 
					{	switch (m_pClientList[sTargetH]->m_iSpecialAbilityType) {
						case 50: // Merien Plate
							if (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)
								sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
							else sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
							if ((sWeaponIndex != -1) && (iWeaponSkill !=6)) // Don't break bows
								m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan = 0;
							break;
						case 51: // Merien Shield effect on armor piece
							if (iHitPoint == m_pClientList[sTargetH]->m_iSpecialAbilityEquipPos)
								iAP_SM = 0;
							break;
						case 52: // Merien Shield
							iAP_SM = 0;
							break;
						}
					}else if (cAttackerType == DEF_OWNERTYPE_NPC)
					{	switch (m_pClientList[sTargetH]->m_iSpecialAbilityType) {
						case 50: // Merien Plate							
							if (m_pNpcList[sAttackerH]->m_cActionLimit < 2)
							{	m_pNpcList[sAttackerH]->m_sBehaviorTurnCount = 0;
								m_pNpcList[sAttackerH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
								m_pNpcList[sAttackerH]->m_bIsPermAttackMode = FALSE;
								m_pNpcList[sAttackerH]->m_iTargetIndex = NULL;
							}
							break;
						case 51: // Merien Shield effect on armor piece
							if (iHitPoint == m_pClientList[sTargetH]->m_iSpecialAbilityEquipPos)
								iAP_SM = 0;
							break;
						case 52: // Merien Shield
							iAP_SM = iAP_SM/2;
							break;				
				}	}	}

				if ((m_pClientList[sTargetH]->m_bIsLuckyEffect > 0) && (iDice(1,100) <= m_pClientList[sTargetH]->m_bIsLuckyEffect) 
					&& (m_pClientList[sTargetH]->m_iHP <= iAP_SM)) 
				{	iAP_SM = m_pClientList[sTargetH]->m_iHP - 1;
				}

				switch (iHitPoint) 
				{
				case 1:
					iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_BODY];
					if (iTemp == -1) iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RELEASEALL];
					if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL) && (cAttackerType != DEF_OWNERTYPE_NPC) )
					{
						bCalculateEnduranceDecrement(sTargetH, sAttackerH, cTargetType, iTemp);
					}
					break;

				case 2:
					iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_PANTS];
					if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL) && (cAttackerType != DEF_OWNERTYPE_NPC)) {
						bCalculateEnduranceDecrement(sTargetH, sAttackerH, cTargetType, iTemp);
					}
					else {
						iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LEGGINGS];
						if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL) && (cAttackerType != DEF_OWNERTYPE_NPC)) {
							bCalculateEnduranceDecrement(sTargetH, sAttackerH, cTargetType, iTemp);
						}
					}
					break;

				case 3:
					iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_ARMS];
					if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL) && (cAttackerType != DEF_OWNERTYPE_NPC)) {
						bCalculateEnduranceDecrement(sTargetH, sAttackerH, cTargetType, iTemp);
					}
					break;

				case 4:
					iTemp = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_HEAD];
					if ((iTemp != -1) && (m_pClientList[sTargetH]->m_pItemList[iTemp] != NULL) && (cAttackerType != DEF_OWNERTYPE_NPC)) {
						bCalculateEnduranceDecrement(sTargetH, sAttackerH, cTargetType, iTemp);
					}
					break;
				}
	
				if ((cAttackerSA == 2) && (m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] != 0)) {
					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_PROTECT, m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT ], NULL, NULL);
					switch(m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT]) {
					case 1:
						SetProtectionFromArrowFlag(sTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
						break;
					case 2:
					case 5:
						SetMagicProtectionFlag(sTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
						break;
					case 3:
					case 4:
						SetDefenseShieldFlag(sTargetH, DEF_OWNERTYPE_PLAYER, FALSE);
						break;
					}
					m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_PROTECT] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_PROTECT);
				}

				if ( (m_pClientList[sTargetH]->m_bIsPoisoned == FALSE) && 
					((cAttackerSA == 5) || (cAttackerSA == 6) || (cAttackerSA == 61)) ) {
					if (bCheckResistingPoisonSuccess(sTargetH, DEF_OWNERTYPE_PLAYER) == FALSE) {
						m_pClientList[sTargetH]->m_bIsPoisoned = TRUE;
						if (cAttackerSA == 5)		m_pClientList[sTargetH]->m_iPoisonLevel = 15;
						else if (cAttackerSA == 6)  m_pClientList[sTargetH]->m_iPoisonLevel = 40;
						else if (cAttackerSA == 61) m_pClientList[sTargetH]->m_iPoisonLevel = iAttackerSAvalue;

						m_pClientList[sTargetH]->m_dwPoisonTime = dwTime;
						SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_POISON, m_pClientList[sTargetH]->m_iPoisonLevel, NULL, NULL);
						SetPoisonFlag(sTargetH, DEF_OWNERTYPE_PLAYER, TRUE);
					}
				}

				// Magic Weapons - Add Magical Damages
				if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL)) {
					double iInitial_AP_SM, iWeaponDamage, iTotalMagicDamage;
					int iMagDamage;
					short sManaCost;
					DWORD dwType1, dwType2, dwValue1, dwValue2;

					if(m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1){
						sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
					}
					else if(m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1){
						sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
					}
					else sItemIndex = -1;

					if(sItemIndex != -1){
						if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) != NULL) {
							dwType1  = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) >> 20;  
							dwValue1 = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x000F0000) >> 16;
							dwType2  = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x0000F000) >> 12;  
							dwValue2 = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00000F00) >> 8;
						}
						if(dwType1 == 15){
							sManaCost = dwValue2*2;
							if(m_pClientList[sAttackerH]->m_iMP >= sManaCost){
								iWeaponDamage = (double)dwValue2*7;
								iInitial_AP_SM = (double)iAP_SM;
								//m_pClientList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT]
								iMagDamage = (double)(m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag)/20;
								iTotalMagicDamage = ((iInitial_AP_SM/100.0f)*(iWeaponDamage+100))+iMagDamage;
								iAP_SM = (int)iTotalMagicDamage;
								m_pClientList[sAttackerH]->m_iMP -= sManaCost;
								SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_MP, NULL, NULL, NULL, NULL);
							}
						}
					}
				}
				// End of Magic Weapons 
				
				// DS reduce Demon's Damage:  max 34-39 damage by DDs (Never fly by DDs)		
				sItemIndex = m_pClientList[sTargetH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				if ((sItemIndex != -1) && (m_pClientList[sTargetH]->m_pItemList[sItemIndex] != NULL)) 
				{	if (   (m_pClientList[sTargetH]->m_pItemList[sItemIndex]->m_sIDnum == 616) // DemonSlayer	
						&& (cAttackerType == DEF_OWNERTYPE_NPC)) 
					{	if ( m_pNpcList[sAttackerH]->m_sType == 31) 
						{	if (iAP_SM >= 40) iAP_SM = 33 + iDice(1,6);
				}	}	}

				m_pClientList[sTargetH]->m_iHP -= iAP_SM;
				if (m_pClientList[sTargetH]->m_iHP <= 0) {
					if (cAttackerType == DEF_OWNERTYPE_PLAYER)
						bAnalyzeCriminalAction(sAttackerH, m_pClientList[sTargetH]->m_sX, m_pClientList[sTargetH]->m_sY);
					ClientKilledHandler(sTargetH, sAttackerH, cAttackerType, iAP_SM);	
					bKilled     = TRUE;
					iKilledDice = (m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel);
				}
				else {
					if (iAP_SM > 0) {
						if (m_pClientList[sTargetH]->m_iAddTransMana > 0) {
							dTmp1 = (double)m_pClientList[sTargetH]->m_iAddTransMana;
							dTmp2 = (double)iAP_SM;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iTemp = iGetMaxMP(sTargetH);
							m_pClientList[sTargetH]->m_iMP += (int)dTmp3;
							if (m_pClientList[sTargetH]->m_iMP > iTemp) m_pClientList[sTargetH]->m_iMP = iTemp;
						}
						if (m_pClientList[sTargetH]->m_iAddChargeCritical > 0) {
							// Crit increase items (bug < and not <= means CritIncrease 1% have no effect)
							if (iDice(1,100) <= (m_pClientList[sTargetH]->m_iAddChargeCritical)) {
								iMaxSuperAttack = ((m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel) / 10);
								if (m_pClientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[sTargetH]->m_iSuperAttackLeft++;
									SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
							}
						}

					SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);

					if (cAttackerType == DEF_OWNERTYPE_PLAYER) 
						sAttackerWeapon = ((m_pClientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
					else sAttackerWeapon = 1;

					if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE)) 
						iMoveDamage = 60;
					else iMoveDamage = 40;

					if (iAP_SM >= iMoveDamage) {
						if (sTgtX == sAtkX) {
							if (sTgtY == sAtkY)     goto CAE_SKIPDAMAGEMOVE;
								else if (sTgtY > sAtkY) cDamageMoveDir = 5;
								else if (sTgtY < sAtkY) cDamageMoveDir = 1;
							}
							else if (sTgtX > sAtkX) {
								if (sTgtY == sAtkY)     cDamageMoveDir = 3;
									else if (sTgtY > sAtkY) cDamageMoveDir = 4;
									else if (sTgtY < sAtkY) cDamageMoveDir = 2;
								}
								else if (sTgtX < sAtkX) {
									if (sTgtY == sAtkY)     cDamageMoveDir = 7;
										else if (sTgtY > sAtkY) cDamageMoveDir = 6;
										else if (sTgtY < sAtkY) cDamageMoveDir = 8;							
								}
							m_pClientList[sTargetH]->m_iLastDamage = iAP_SM;

							SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_DAMAGEMOVE, cDamageMoveDir, iAP_SM, sAttackerWeapon, NULL);
						}
						else {
CAE_SKIPDAMAGEMOVE:;
							int iProb;
							if (cAttackerType == DEF_OWNERTYPE_PLAYER) {
								switch (m_pClientList[sAttackerH]->m_sUsingWeaponSkill) {
									case 6 : iProb = 3500; break;
									case 8 : iProb = 1000; break;
									case 9 : iProb = 2900; break;
									case 10: iProb = 2500; break;
									case 14: iProb = 2000; break;
									case 21: iProb = 2000; break;
									default: iProb = 1; break;
								}
							}
							else iProb = 1;

							if (iDice(1,10000) >= iProb) 
								SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iAP_SM, sAttackerWeapon, NULL);		
							}

							if (m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] == 1) {
								SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ], NULL, NULL);
								m_pClientList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
								bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
							}

							m_pClientList[sTargetH]->m_iSuperAttackCount++;
							if (m_pClientList[sTargetH]->m_iSuperAttackCount > 14) { 
								m_pClientList[sTargetH]->m_iSuperAttackCount = 0;
								iMaxSuperAttack = ((m_pClientList[sTargetH]->m_iLevel+ m_pClientList[sTargetH]->m_iMajesticLevel) / 10);
								if (m_pClientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) m_pClientList[sTargetH]->m_iSuperAttackLeft++;
									SendNotifyMsg(NULL, sTargetH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
							}
						}
					}
				}
				break;				   

		case DEF_OWNERTYPE_NPC:
			if (m_pNpcList[sTargetH]->m_cBehavior == DEF_BEHAVIOR_DEAD) return 0;
			if (m_pNpcList[sTargetH]->m_bIsKilled == TRUE) return 0;
			if (m_bIsCrusadeMode == TRUE) {
				if (cAttackerSide == m_pNpcList[sTargetH]->m_cSide) {
					switch (m_pNpcList[sTargetH]->m_sType) {
						case 40:
						case 41:
						case 43:
						case 44:
						case 45:
						case 46:
						case 47: 
						case 51:
							return 0;

						default: 
							break;
					}
				}
				else {
					switch (m_pNpcList[sTargetH]->m_sType) {
						case 41:
							if (cAttackerSide != 0) {
								m_pNpcList[sTargetH]->m_iV1 += iAP_L;
								if (m_pNpcList[sTargetH]->m_iV1 > 500) {
									m_pNpcList[sTargetH]->m_iV1 = 0;
									m_pNpcList[sTargetH]->m_iManaStock--;
									if (m_pNpcList[sTargetH]->m_iManaStock <= 0) m_pNpcList[sTargetH]->m_iManaStock = 0;
									
								}
							}
							break;
					}
				}
			}
			switch (m_pNpcList[sTargetH]->m_cActionLimit) { // Invulnerable npcs...
			case 2: // merchants
			case 6: // moving merchants
				return 0;
				
			}
			// SNOOPY: Added possibility to poison npcs
			if (cTargetType == DEF_OWNERTYPE_NPC) {
				if ((cAttackerSA == 5) || (cAttackerSA == 6) || (cAttackerSA == 61))
				{
					if (bCheckResistingPoisonSuccess(sTargetH, DEF_OWNERTYPE_NPC) == FALSE)
					{
						switch (cAttackerSA) {
						case 5:
							if (m_pNpcList[sTargetH]->m_iPoisonLevel < 15) m_pNpcList[sTargetH]->m_iPoisonLevel = 15; //15
							SetPoisonFlag(sTargetH, DEF_OWNERTYPE_NPC, TRUE);
							break;
						case 6:
							if (m_pNpcList[sTargetH]->m_iPoisonLevel < 40) m_pNpcList[sTargetH]->m_iPoisonLevel = 40; //40
							SetPoisonFlag(sTargetH, DEF_OWNERTYPE_NPC, TRUE);
							break;
						case 61:
							if (m_pNpcList[sTargetH]->m_iPoisonLevel < iAttackerSAvalue) m_pNpcList[sTargetH]->m_iPoisonLevel = iAttackerSAvalue;
							SetPoisonFlag(sTargetH, DEF_OWNERTYPE_NPC, TRUE);
							break;
						}
					}
				}
			}

			// Snoopy: Added possibilty of activated weapons effect on npcs
			if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) 
				&& (m_pClientList[sAttackerH] != NULL) 
				&& (m_pClientList[sAttackerH]->m_bIsSpecialAbilityEnabled == TRUE)) 
			{	switch (m_pClientList[sAttackerH]->m_iSpecialAbilityType) {
				case 0: break;
				case 1: // Xelima weapon, deals double damage 1 in 3 times
					if (iDice(1,3)==2) 
					{	iAP_SM *= 2;
						iAP_L *= 2;
					}
					break;
				case 2: // Ice weapon, will ice npcs						
					if (   (bCheckResistingIceSuccess(0, sTargetH, DEF_OWNERTYPE_NPC, 50) == FALSE) 
							&& (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] == 0)) 
					{	m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_ICE ] = 2;
						SetIceFlag(sTargetH, DEF_OWNERTYPE_NPC, TRUE);
						bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + 20000, 
							sTargetH, DEF_OWNERTYPE_NPC, NULL, NULL, NULL, 1, NULL, NULL);
					}
					break;
				case 3: // Medusa sword - hold for 10 sec
					if (m_pNpcList[sTargetH]->m_cMagicLevel >= 6)
					{	// Not on magic npcs,
					}else  // para for 10 sec
					{	if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] == 0) 
						{	m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = 3;
							bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_HOLDOBJECT, dwTime + 10000, 
								sTargetH, DEF_OWNERTYPE_NPC, NULL, NULL, NULL, 3, NULL, NULL);
							// May be canceled due to damage later...					
					}	}
					break;
				case 4: // Instant kill weapon, deals Double damage
					iAP_SM *= 2;
					iAP_L *= 2;
					break;
				case 5: // Vampiric weapon 1/8 of given HP
					if (m_pNpcList[sTargetH]->m_cSize == 0)	
						 m_pClientList[sAttackerH]->m_iHP += iAP_SM/8;					
					else m_pClientList[sAttackerH]->m_iHP += iAP_L/8;
					if (iGetMaxHP(sAttackerH) < m_pClientList[sAttackerH]->m_iHP) // BloodEffect limite le regen
						m_pClientList[sAttackerH]->m_iHP = iGetMaxHP(sAttackerH);
					SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
					break;
			}	}

			if (m_pNpcList[sTargetH]->m_cSize == 0)	
				iDamage = iAP_SM;					
			else iDamage = iAP_L;

			// PA monsters
			if (m_pNpcList[sTargetH]->m_iAbsDamage < 0) // negative value: PA mobs
			{	dTmp1 = (double)iDamage;
				dTmp2 = (double)(abs(m_pNpcList[sTargetH]->m_iAbsDamage))/100.0f;
				dTmp3 = dTmp1 * dTmp2;										
				if (   (cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) 
					&& (m_pNpcList[sTargetH]->m_cSpecialAbility == 3)
					&& (m_pClientList[sAttackerH]->m_sUsingWeaponSkill == 14)) 	// PA counts for 1/2 vs Hammers but not against natural PA
				{	dTmp2 = dTmp1 - (dTmp3/2);	
				}else dTmp2 = dTmp1 - dTmp3;	
				iDamage = (int)dTmp2;
				if (iDamage < 0) iDamage = 1;
			}

			if ((cAttackerSA == 2) && (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_PROTECT ] != 0)) {
					switch(m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT]) {
					case 1:
						SetProtectionFromArrowFlag(sTargetH, DEF_OWNERTYPE_NPC, FALSE);
						break;
					case 2:
					case 5:
						SetMagicProtectionFlag(sTargetH, DEF_OWNERTYPE_NPC, FALSE);
						break;
					case 3:
					case 4:
						SetDefenseShieldFlag(sTargetH, DEF_OWNERTYPE_NPC, FALSE);
						break;
					}
				m_pNpcList[sTargetH]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] = NULL;
				bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_PROTECT);					  
			}

			// Magic Weapons - Add Magical Damages
			if ((cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL)) {
				double iInitial_AP_SM, iWeaponDamage, iTotalMagicDamage;
				int iMagDamage;
				short sManaCost;
				DWORD dwType1, dwType2, dwValue1, dwValue2;

				if(m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND] != -1){
					sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
				}
				else if(m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1){
					sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
				}
				else sItemIndex = -1;

				if(sItemIndex != -1){
					if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) != NULL) {
						dwType1  = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00F00000) >> 20;  
						dwValue1 = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x000F0000) >> 16;
						dwType2  = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x0000F000) >> 12;  
						dwValue2 = (m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_dwAttribute & 0x00000F00) >> 8;
					}
					if(dwType1 == 15){
						sManaCost = dwValue2*2;
						if(m_pClientList[sAttackerH]->m_iMP >= sManaCost){
							iWeaponDamage = (double)dwValue2*7;
							iInitial_AP_SM = (double)iDamage;
							iMagDamage = (double)(m_pClientList[sAttackerH]->m_iMag+m_pClientList[sAttackerH]->m_iAngelicMag)/20;
							iTotalMagicDamage = ((iInitial_AP_SM/100.0f)*(iWeaponDamage+100))+iMagDamage;
							iDamage = (int)iTotalMagicDamage;
							m_pClientList[sAttackerH]->m_iMP -= sManaCost;
							SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_MP, NULL, NULL, NULL, NULL);
						}
					}
				}
			}
			// End of Magic Weapons 

			switch (m_pNpcList[sTargetH]->m_cActionLimit) {
			case 0:
			case 3:
			case 5:
				m_pNpcList[sTargetH]->m_iHP -= iDamage;
				break;
			}

			if (m_pNpcList[sTargetH]->m_iHP <= 0) {
				NpcKilledHandler(sAttackerH, cAttackerType, sTargetH, iDamage);
				bKilled = TRUE;
				iKilledDice = m_pNpcList[sTargetH]->m_iHitDice;
			}
			else {
				if ((m_pNpcList[sTargetH]->m_sType != 21) && (m_pNpcList[sTargetH]->m_sType != 55) && (m_pNpcList[sTargetH]->m_sType != 56)
					&& (m_pNpcList[sTargetH]->m_cSide == cAttackerSide)) goto CAE_SKIPCOUNTERATTACK;

				// Tammed mobs
				if ((m_pNpcList[sTargetH]->m_dwTamingTime != 0) && (m_pNpcList[sTargetH]->m_iSummonControlMode == 1)) goto CAE_SKIPCOUNTERATTACK;

				if (m_pNpcList[sTargetH]->m_cActionLimit != 0) goto CAE_SKIPCOUNTERATTACK;
				if (m_pNpcList[sTargetH]->m_bIsPermAttackMode == TRUE) goto CAE_SKIPCOUNTERATTACK;
				if ((m_pNpcList[sTargetH]->m_bIsSummoned == TRUE) && (m_pNpcList[sTargetH]->m_iSummonControlMode == 1)) goto CAE_SKIPCOUNTERATTACK;
				if (m_pNpcList[sTargetH]->m_sType == 51) goto CAE_SKIPCOUNTERATTACK;

				if (iDice(1,3) == 2) {
					if (m_pNpcList[sTargetH]->m_cBehavior == DEF_BEHAVIOR_ATTACK) {
						tX = tY = 0;
						switch (m_pNpcList[sTargetH]->m_cTargetType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[m_pNpcList[sTargetH]->m_iTargetIndex] != NULL) {
									tX = m_pClientList[m_pNpcList[sTargetH]->m_iTargetIndex]->m_sX;
									tY = m_pClientList[m_pNpcList[sTargetH]->m_iTargetIndex]->m_sY;
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[m_pNpcList[sTargetH]->m_iTargetIndex] != NULL) {
									tX = m_pNpcList[m_pNpcList[sTargetH]->m_iTargetIndex]->m_sX;
									tY = m_pNpcList[m_pNpcList[sTargetH]->m_iTargetIndex]->m_sY;
								}
								break;
							}

						iDst1 = (m_pNpcList[sTargetH]->m_sX - tX)*(m_pNpcList[sTargetH]->m_sX - tX) + (m_pNpcList[sTargetH]->m_sY - tY)*(m_pNpcList[sTargetH]->m_sY - tY);

						tX = tY = 0;
						switch (cAttackerType) {
							case DEF_OWNERTYPE_PLAYER:
								if (m_pClientList[sAttackerH] != NULL) {
									tX = m_pClientList[sAttackerH]->m_sX;
									tY = m_pClientList[sAttackerH]->m_sY;
								}
								break;

							case DEF_OWNERTYPE_NPC:
								if (m_pNpcList[sAttackerH] != NULL) {
									tX = m_pNpcList[sAttackerH]->m_sX;
									tY = m_pNpcList[sAttackerH]->m_sY;
								}
								break;
						}

						iDst2 = (m_pNpcList[sTargetH]->m_sX - tX)*(m_pNpcList[sTargetH]->m_sX - tX) + (m_pNpcList[sTargetH]->m_sY - tY)*(m_pNpcList[sTargetH]->m_sY - tY);

						if (iDst2 <= iDst1) {
							m_pNpcList[sTargetH]->m_cBehavior          = DEF_BEHAVIOR_ATTACK;
							m_pNpcList[sTargetH]->m_sBehaviorTurnCount = 0;		
							m_pNpcList[sTargetH]->m_iTargetIndex = sAttackerH;
							m_pNpcList[sTargetH]->m_cTargetType  = cAttackerType;
						}
					}
					else {
						m_pNpcList[sTargetH]->m_cBehavior          = DEF_BEHAVIOR_ATTACK;
						m_pNpcList[sTargetH]->m_sBehaviorTurnCount = 0;		
						m_pNpcList[sTargetH]->m_iTargetIndex = sAttackerH;
						m_pNpcList[sTargetH]->m_cTargetType  = cAttackerType;
					}
				}

CAE_SKIPCOUNTERATTACK:;

				if ((iDice(1,3) == 2) && (m_pNpcList[sTargetH]->m_cActionLimit == 0))
					m_pNpcList[sTargetH]->m_dwTime = dwTime;

				if (cAttackerType == DEF_OWNERTYPE_PLAYER) 
					sAttackerWeapon = ((m_pClientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
				else sAttackerWeapon = 1;

				if ((wWeaponType < 40) && (m_pNpcList[sTargetH]->m_cActionLimit == 4)) {
 					if (sTgtX == sAtkX) {
						if (sTgtY == sAtkY)     goto CAE_SKIPDAMAGEMOVE2;
						else if (sTgtY > sAtkY) cDamageMoveDir = 5;
						else if (sTgtY < sAtkY) cDamageMoveDir = 1;
					}
					else if (sTgtX > sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 3;
						else if (sTgtY > sAtkY) cDamageMoveDir = 4;
						else if (sTgtY < sAtkY) cDamageMoveDir = 2;
					}
					else if (sTgtX < sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 7;
						else if (sTgtY > sAtkY) cDamageMoveDir = 6;
						else if (sTgtY < sAtkY) cDamageMoveDir = 8;							
					}

					dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
					dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

					if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {
						cDamageMoveDir = iDice(1,8);
						dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
						dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

						if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) goto CAE_SKIPDAMAGEMOVE2;
					}

					m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->ClearOwner(5, sTargetH, DEF_OWNERTYPE_NPC, m_pNpcList[sTargetH]->m_sX, m_pNpcList[sTargetH]->m_sY);
					m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_NPC, dX, dY);
					m_pNpcList[sTargetH]->m_sX   = dX;
					m_pNpcList[sTargetH]->m_sY   = dY;
					m_pNpcList[sTargetH]->m_cDir = cDamageMoveDir;

					SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);

					dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
					dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

					if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {
						cDamageMoveDir = iDice(1,8);
						dX = m_pNpcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
						dY = m_pNpcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];
						if (m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) goto CAE_SKIPDAMAGEMOVE2;
					}

					m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->ClearOwner(5, sTargetH, DEF_OWNERTYPE_NPC, m_pNpcList[sTargetH]->m_sX, m_pNpcList[sTargetH]->m_sY);
					m_pMapList[m_pNpcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, DEF_OWNERTYPE_NPC, dX, dY);
					m_pNpcList[sTargetH]->m_sX   = dX;
					m_pNpcList[sTargetH]->m_sY   = dY;
					m_pNpcList[sTargetH]->m_cDir = cDamageMoveDir;

					SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);

				}
				else {
					SendEventToNearClient_TypeA(sTargetH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, sAttackerWeapon, NULL);
				}

CAE_SKIPDAMAGEMOVE2:;

				if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] == 1) {
					m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
					bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_HOLDOBJECT);
				}
				else if (m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] == 2) {
					if ((m_pNpcList[sTargetH]->m_iHitDice > 50) && (iDice(1, 10) == 5)) {
						m_pNpcList[sTargetH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_HOLDOBJECT ] = NULL;
						bRemoveFromDelayEventList(sTargetH, DEF_OWNERTYPE_NPC, DEF_MAGICTYPE_HOLDOBJECT);
					}
				}

				if ( (m_pNpcList[sTargetH]->m_iNoDieRemainExp > 0) && (m_pNpcList[sTargetH]->m_bIsSummoned != TRUE) && 
					(cAttackerType == DEF_OWNERTYPE_PLAYER) && (m_pClientList[sAttackerH] != NULL) ) {
						if (m_pNpcList[sTargetH]->m_iNoDieRemainExp > iDamage) {
							iExp = iDamage;
							m_pNpcList[sTargetH]->m_iNoDieRemainExp -= iDamage;
						}
						else {
							iExp = m_pNpcList[sTargetH]->m_iNoDieRemainExp;
							m_pNpcList[sTargetH]->m_iNoDieRemainExp = 0;
						}

						if (m_pClientList[sAttackerH]->m_iAddExp != NULL) {
							dTmp1 = (double)m_pClientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (m_bIsCrusadeMode == TRUE) iExp = iExp/3;

						if (m_pClientList[sAttackerH]->m_iLevel > 100 ) {
							switch (m_pNpcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0;
								break;
							default: break;
							}
						}
					}
			}
			break;
		}

		if (cAttackerType == DEF_OWNERTYPE_PLAYER) 
		{	if (m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND] != -1)
				 sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_TWOHAND];
			else sWeaponIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_RHAND];
// SNOOPY: ADDED support for Dual-Wielding on 4th Combo Attack
			// And add MainGauche Attack on succesfull 4th combo Attacks
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
			if ((bMainGaucheAttack == FALSE) // No 2nd MainGauche Attack
				&& (sItemIndex != -1)
				&& (m_pClientList[sAttackerH]->m_iComboAttackCount == 4)
				&& (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {				
				iWeaponSkill = _iGetWeaponSkillType(sAttackerH);
				if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 10) // MainGauche
					&& ((iWeaponSkill==7)||(iWeaponSkill==9)) // Only SS or Fencers					
					&& (iDice(1,120) < m_pClientList[sAttackerH]->m_cSkillMastery[20]) )// Dual-Wielding skill					 
				{	iExp += iCalculateAttackEffect(sTargetH, cTargetType, sAttackerH, DEF_OWNERTYPE_PLAYER, tdX, tdY, 2, FALSE, FALSE, FALSE, TRUE);				
			}	}			
			//SNOOPY: Increase Dual-Wielding Skill if appropriate
			if (bMainGaucheAttack == TRUE) {
				CalculateSSN_SkillIndex(sAttackerH, 20, 1);
				if (bKilled == FALSE)
					CalculateSSN_SkillIndex(sAttackerH, 20, 1);
				else {
					if (m_pClientList[sAttackerH]->m_iHP <= 3)
						 CalculateSSN_SkillIndex(sAttackerH, 20, iDice(1, iKilledDice));
					else CalculateSSN_SkillIndex(sAttackerH, 20, iDice(1, ((int)(iKilledDice/2))));
				}
			}else // Else compute normal weapons skill increase
			// Compute skill increase
			if ((sWeaponIndex != -1) && (bArrowUse != TRUE)) {
				// No skill increase if bArrowUse
				if (   (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex] != NULL) 
					&& (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_sIDnum != 231) )  //  Not for PickAxe
				{	if (bKilled == FALSE)
						CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, 1);
					else 
					{	if (m_pClientList[sAttackerH]->m_iHP <= 3)
							 CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, iDice(1, iKilledDice)*2);
						else CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, iDice(1, iKilledDice));
				}	}
				// Weapon's wep life off
				if (   (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex] != NULL) 
					&& (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wMaxLifeSpan != 0) ) 
				{	iWepLifeOff = 1;
					if ((wWeaponType >= 1) && (wWeaponType < 40)) 
					{	switch (m_pMapList[m_pClientList[sAttackerH]->m_cMapIndex]->m_cWhetherStatus) {
						case 0:	break;
						case 1:	if (iDice(1,3) == 1) iWepLifeOff++; break;
						case 2:	if (iDice(1,2) == 1) iWepLifeOff += iDice(1,2); break;
						case 3:	if (iDice(1,2) == 1) iWepLifeOff += iDice(1,3); break;
						}
					}
					if (m_pClientList[sAttackerH]->m_cSide != 0) {
						if (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan < iWepLifeOff) 
							 m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan = 0;
						else m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan -= iWepLifeOff;
					}
					if (m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan == 0) {
						SendNotifyMsg(NULL, sAttackerH, DEF_NOTIFY_ITEMLIFESPANEND, m_pClientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_cEquipPos, sWeaponIndex, NULL, NULL);
						ReleaseItemHandler(sAttackerH, sWeaponIndex, TRUE);
				}	}
			}else 
			{	if (wWeaponType == 0)  // Open-Hand Skill increase
				{	CalculateSSN_SkillIndex(sAttackerH, 5, 1);
		}	}	}
	}else  // Missing the target !
	{	if (cAttackerType == DEF_OWNERTYPE_PLAYER) {	//bMainGaucheAttack
			m_pClientList[sAttackerH]->m_iComboAttackCount = 0;
			//SNOOPY: Adding MainGauche Attack
			sItemIndex = m_pClientList[sAttackerH]->m_sItemEquipmentStatus[DEF_EQUIPPOS_LHAND];
			if ((bMainGaucheAttack == FALSE) // Not if alreaddy a MainGauche Attack
				&& (sItemIndex != -1)
				&& (m_pClientList[sAttackerH]->m_pItemList[sItemIndex] != NULL)) {				
				iWeaponSkill = _iGetWeaponSkillType(sAttackerH);
				if ((m_pClientList[sAttackerH]->m_pItemList[sItemIndex]->m_sIDnum == 10) // MainGauche
					&& ((iWeaponSkill == 7)||(iWeaponSkill == 9)) // Only SS or Fencers					
					&& (iDice(1,150) < m_pClientList[sAttackerH]->m_cSkillMastery[20]) )// Dual-Wielding skill					 
				{	iExp = iCalculateAttackEffect(sTargetH, cTargetType, sAttackerH, DEF_OWNERTYPE_PLAYER, tdX, tdY, 2, FALSE, FALSE, FALSE, TRUE);
	}	}	}	}
	return iExp;
}

BOOL CGame::_bCheckCharacterData(int iClientH)
{
 int i;
 int iTotalPoints;

	if (((m_pClientList[iClientH]->m_iStr+m_pClientList[iClientH]->m_iAngelicStr) > m_sCharStatLimit) || (m_pClientList[iClientH]->m_iVit > m_sCharStatLimit-11) || ((m_pClientList[iClientH]->m_iDex+m_pClientList[iClientH]->m_iAngelicDex) > m_sCharStatLimit) ||
        ((m_pClientList[iClientH]->m_iMag+m_pClientList[iClientH]->m_iAngelicMag) > m_sCharStatLimit) || ((m_pClientList[iClientH]->m_iInt+m_pClientList[iClientH]->m_iAngelicInt) > m_sCharStatLimit) || (m_pClientList[iClientH]->m_iCharisma > m_sCharStatLimit-11)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) stat points are greater then server accepts.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}
			

	iTotalPoints = 0;
	for (i = 0; i <	DEF_MAXSKILLTYPE; i++) 
		iTotalPoints += m_pClientList[iClientH]->m_cSkillMastery[i];
		if ((iTotalPoints-21 > m_sCharSkillLimit) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) - has more than allowed skill points (%d).", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, iTotalPoints);
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if ((strcmp(m_pClientList[iClientH]->m_cLocation, "elvine") != 0) && 
		(strcmp(m_pClientList[iClientH]->m_cLocation, "elvhunter") != 0) && 
		(strcmp(m_pClientList[iClientH]->m_cLocation, "arehunter") != 0) && 
		(strcmp(m_pClientList[iClientH]->m_cLocation, "aresden") != 0) &&
		(m_pClientList[iClientH]->m_iLevel >= 20) &&
		(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Traveller Hack: (%s) Player: (%s) is a traveller and is greater than level 19.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if ((m_pClientList[iClientH]->m_iLevel > m_iPlayerMaxLevel) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) level above max server level.", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if (m_pClientList[iClientH]->m_iExp < 0) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) experience is below 0 - (Exp:%d).", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iExp);
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if ((m_pClientList[iClientH]->m_iHP > iGetMaxHP(iClientH)) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) HP: current/maximum (%d/%d).", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iHP, iGetMaxHP(iClientH));
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if ((m_pClientList[iClientH]->m_iMP > iGetMaxMP(iClientH)) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) MP: current/maximum (%d/%d).", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iMP, iGetMaxMP(iClientH));
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	if ((m_pClientList[iClientH]->m_iSP > iGetMaxSP(iClientH)) && (m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		wsprintf(G_cTxt, "Packet Editing: (%s) Player: (%s) SP: current/maximum (%d/%d).", m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName, m_pClientList[iClientH]->m_iSP, iGetMaxSP(iClientH));
		PutHackLogFileList(G_cTxt);
		return FALSE;
	}

	for (i = 0; i < DEF_MAXBANNED; i++) {
		if(strlen(m_stBannedList[i].m_cBannedIPaddress) == 0) break; //No more GM's on list
		if ((strlen(m_stBannedList[i].m_cBannedIPaddress)) == (strlen(m_pClientList[iClientH]->m_cIPaddress))) {
			if(memcmp(m_stBannedList[i].m_cBannedIPaddress, m_pClientList[iClientH]->m_cIPaddress, strlen(m_pClientList[iClientH]->m_cIPaddress)) == 0){
				wsprintf(G_cTxt,"Client Rejected: Banned: (%s)", m_pClientList[iClientH]->m_cIPaddress);
				PutLogList(G_cTxt);
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CGame::AdminOrder_GetFightzoneTicket(int iClientH)
{
 int iReserveTime, iFightzoneTN, iFightzoneN;
 char cTemp[21];
 SYSTEMTIME SysTime;

	if (m_pClientList[iClientH] == NULL) return;
	if (memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "fightzone", 9) == 0) {
		
		iReserveTime = m_pClientList[iClientH]->m_iReserveTime;
		GetLocalTime(&SysTime);
		m_pClientList[iClientH]->m_iReserveTime = SysTime.wMonth*10000 + SysTime.wDay*100 + (SysTime.wHour +3);  
		
		ZeroMemory(cTemp, sizeof(cTemp));
		strcpy(cTemp, (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName +9));
		iFightzoneN  = m_pClientList[iClientH]->m_iFightzoneNumber;
		iFightzoneTN = m_pClientList[iClientH]->m_iFightZoneTicketNumber;
		m_pClientList[iClientH]->m_iFightZoneTicketNumber = 10;
		m_pClientList[iClientH]->m_iFightzoneNumber = atoi(cTemp);
		
		GetFightzoneTicketHandler(iClientH);
		GetFightzoneTicketHandler(iClientH);
		GetFightzoneTicketHandler(iClientH);
		
		m_pClientList[iClientH]->m_iFightzoneNumber = iFightzoneN;
		m_pClientList[iClientH]->m_iFightZoneTicketNumber = iFightzoneTN;
		m_pClientList[iClientH]->m_iReserveTime = iReserveTime;
	}
	else {
		iReserveTime = m_pClientList[iClientH]->m_iReserveTime;
		GetLocalTime(&SysTime);
		m_pClientList[iClientH]->m_iReserveTime = SysTime.wMonth*10000 + SysTime.wDay*100 + (SysTime.wHour +2);  
		
		ZeroMemory(cTemp, sizeof(cTemp));
		strcpy(cTemp, (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName +9));
		iFightzoneN  = m_pClientList[iClientH]->m_iFightzoneNumber;
		iFightzoneTN = m_pClientList[iClientH]->m_iFightZoneTicketNumber;
		m_pClientList[iClientH]->m_iFightZoneTicketNumber = 10;
		m_pClientList[iClientH]->m_iFightzoneNumber = 1;
		
		GetFightzoneTicketHandler(iClientH);
		GetFightzoneTicketHandler(iClientH);
		GetFightzoneTicketHandler(iClientH);

		m_pClientList[iClientH]->m_iFightzoneNumber = iFightzoneN;
		m_pClientList[iClientH]->m_iFightZoneTicketNumber = iFightzoneTN;
		m_pClientList[iClientH]->m_iReserveTime = iReserveTime;
	}
}

/*********************************************************************************************************************
**  int iGetPlayerStatus(int iClientH, short sOwnerH)																**
**  DESCRIPTION			:: returns client tile's mistatus															**
**  LAST_UPDATED		:: March 16, 2005; 12:31 PM; Hypnotoad														**
**	RETURN_VALUE		:: int																						**
**  NOTES				::	- not available in 2.03				 													**
**	MODIFICATION		:: N/A																						**
**********************************************************************************************************************/
int CGame::iGetPlayerStatus(int iClientH, short sOwnerH)
{
 int iRet;

	if (m_pClientList[iClientH]->m_cSide != m_pClientList[sOwnerH]->m_cSide) {
		if (iClientH != sOwnerH) {
			iRet = m_pClientList[sOwnerH]->m_iStatus & 0x0F0FFFF7F;
		}
		else iRet = m_pClientList[sOwnerH]->m_iStatus;
	}
	else iRet = m_pClientList[sOwnerH]->m_iStatus;
	return iRet;
}

BOOL CGame::bReadSettingsConfigFile(char * cFn) 
{ 
   FILE * pFile; 
   HANDLE hFile; 
   DWORD  dwFileSize; 
   char * cp, * token, cReadMode, cTxt[120], cGSMode[16] = "", len; 
   char seps[] = "= \t\n"; 
   class CStrTok * pStrTok; 

   cReadMode = 0; 

   hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL); 
   dwFileSize = GetFileSize(hFile, NULL); 
   if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile); 

   pFile = fopen(cFn, "rt"); 
   if (pFile == NULL) { 
      // 째횚��횙쩌짯쨔철��횉 횄횎짹창횊짯 횈횆��횕��쨩 ��횖��쨩 쩌철 쩐첩쨈횢. 
      PutLogList("(!) Cannot open configuration file."); 
      return FALSE; 
   } 
   else { 
      PutLogList("(!) Reading settings file..."); 
      cp = new char[dwFileSize+2]; 
      ZeroMemory(cp, dwFileSize+2); 
      fread(cp, dwFileSize, 1, pFile); 

      pStrTok = new class CStrTok(cp, seps); 
      token = pStrTok->pGet(); 
      while( token != NULL )   { 

         if (cReadMode != 0) { 
            switch (cReadMode) { 

            case 1: 
               if ((strlen(token) != 0) && (strlen(token) <= 10000) && (strlen(token) >= 1)) 
               { 
                  m_iPrimaryDropRate = atoi(token); 
               } 
               else 
               { 
                  wsprintf(cTxt, "(!!!) Primary drop rate(%s) invalid must be between 1 to 10000", token); 
                  PutLogList(cTxt); 
               } 
               wsprintf(cTxt, "(*) Primary drop rate: (%d)", m_iPrimaryDropRate); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 2: 
               if ((strlen(token) != 0) && (strlen(token) <= 10000) && (strlen(token) >= 1)) 
               { 
                  m_iSecondaryDropRate = atoi(token); 
               } 
               else 
               { 
                  wsprintf(cTxt, "(!!!) Secondary drop rate(%s) invalid must be between 1 to 10000", token); 
                  PutLogList(cTxt); 
               } 
               wsprintf(cTxt, "(*) Secondary drop rate: (%d)", m_iSecondaryDropRate); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 3: 
               if ((memcmp(token, "classic", 7) == 0) || (memcmp(token, "CLASSIC", 7) == 0)) 
               { 
                  m_bEnemyKillMode = FALSE; 
                  PutLogList("(*) Enemy Kill Mode: CLASSIC");
               } 
               else if ((memcmp(token, "deathmatch", 10) == 0) || (memcmp(token, "DEATHMATCH", 10) == 0)) 
               { 
                  m_bEnemyKillMode = TRUE; 
                  PutLogList("(*) Enemy Kill Mode: DEATHMATCH");
               } 
               else 
               { 
                  wsprintf(cTxt, "(!!!) ENEMY-KILL-MODE: (%s) must be either DEATHMATCH or CLASSIC", token); 
                  PutLogList(cTxt); 
                  return FALSE; 
               } 
               cReadMode = 0; 
               break; 

            case 4: 
               if ((strlen(token) != 0) && (strlen(token) <= 100) && (strlen(token) >= 1)) 
               { 
                  m_iEnemyKillAdjust = atoi(token); 
               } 
               else 
               { 
                  wsprintf(cTxt, "(!!!) ENEMY-KILL-ADJUST: (%s) invalid must be between 1 to 100", token); 
                  PutLogList(cTxt); 
               } 
               wsprintf(cTxt, "(*) Player gains (%d) EK.", m_iEnemyKillAdjust); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 5: 
               if ((memcmp(token, "on", 2) == 0) || (memcmp(token, "ON", 2) == 0)) 
               { 
                  m_bAdminSecurity = TRUE; 
                  PutLogList("(*) Administator actions limited through security.");
               } 
               if ((memcmp(token, "off", 3) == 0) || (memcmp(token, "OFF", 3) == 0)) 
               { 
                  m_bAdminSecurity = FALSE; 
                  PutLogList("(*) Administator vulnerability ignored.");
               } 

               cReadMode = 0; 
               break; 

            case 6: 
               m_sRaidTimeMonday = atoi(token); 
               if (m_sRaidTimeMonday == 0) m_sRaidTimeMonday = 3; 
               wsprintf(cTxt, "(*) Monday Raid Time : (%d) minutes", m_sRaidTimeMonday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 7: 
               m_sRaidTimeTuesday = atoi(token); 
               if (m_sRaidTimeTuesday == 0) m_sRaidTimeTuesday = 3; 
               wsprintf(cTxt, "(*) Tuesday Raid Time : (%d) minutes", m_sRaidTimeTuesday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 8: 
               m_sRaidTimeWednesday = atoi(token); 
               if (m_sRaidTimeWednesday == 0) m_sRaidTimeWednesday = 3; 
               wsprintf(cTxt, "(*) Wednesday Raid Time : (%d) minutes", m_sRaidTimeWednesday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 9: 
               m_sRaidTimeThursday = atoi(token); 
               if (m_sRaidTimeThursday == 0) m_sRaidTimeThursday = 3; 
               wsprintf(cTxt, "(*) Thursday Raid Time : (%d) minutes", m_sRaidTimeThursday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 10: 
               m_sRaidTimeFriday = atoi(token); 
               if (m_sRaidTimeFriday == 0) m_sRaidTimeFriday = 10; 
               wsprintf(cTxt, "(*) Friday Raid Time : (%d) minutes", m_sRaidTimeFriday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 11: 
               m_sRaidTimeSaturday = atoi(token); 
               if (m_sRaidTimeSaturday == 0) m_sRaidTimeSaturday = 45; 
               wsprintf(cTxt, "(*) Saturday Raid Time : (%d) minutes", m_sRaidTimeSaturday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 

            case 12: 
               m_sRaidTimeSunday = atoi(token); 
               if (m_sRaidTimeSunday == 0) m_sRaidTimeSunday = 60; 
               wsprintf(cTxt, "(*) Sunday Raid Time : (%d) minutes", m_sRaidTimeSunday); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break; 
		
			case 13:
				if ((memcmp(token, "player", 6) == 0) || (memcmp(token, "PLAYER", 6) == 0))
				{
					m_bLogChatOption = 1;
					PutLogList("(*) Logging Player Chat.");
				}
				if ((memcmp(token, "gm", 2) == 0) || (memcmp(token, "GM", 2) == 0))
				{
					m_bLogChatOption = 2;
					PutLogList("(*) Logging GM Chat.");
				}
				if ((memcmp(token, "all", 3) == 0) || (memcmp(token, "ALL", 3) == 0))
				{
					m_bLogChatOption = 3;
					PutLogList("(*) Logging All Chat.");
				}
				if ((memcmp(token, "none", 4) == 0) || (memcmp(token, "NONE", 4) == 0))
				{
					m_bLogChatOption = 4;
					PutLogList("(*) Not Logging Any Chat.");
				}
				cReadMode = 0;
				break;

            case 14: 
               m_iSummonGuildCost = atoi(token); 
               wsprintf(cTxt, "(*) Summoning guild costs (%d) gold", m_iSummonGuildCost); 
               PutLogList(cTxt); 
               cReadMode = 0; 
               break;
 
			case 15: 
               m_sSlateSuccessRate = atoi(token); 
               wsprintf(cTxt, "(*) Slate Success Rate (%d) percent", m_sSlateSuccessRate); 
               PutLogList(cTxt); 
			   if (m_sSlateSuccessRate == 0) m_sSlateSuccessRate = 14; 
               cReadMode = 0; 
               break;

			case 16: 
               m_sCharStatLimit = 11 + atoi(token); 
               if (m_sCharStatLimit == 0) m_sCharStatLimit = 200; 
               cReadMode = 0;
               break;

			case 17: 
               m_sCharSkillLimit = atoi(token); 
               if (m_sCharSkillLimit == 0) m_sCharSkillLimit = 700; 
               cReadMode = 0;
               break;

			case 18: 
               
               cReadMode = 0; 
               break;

			case 19: 
               ZeroMemory(m_cSecurityNumber, sizeof(m_cSecurityNumber));
			   len = strlen(token);
			   if(len > 10) len = 10;
			   memcpy(m_cSecurityNumber, token, len);
               PutLogList("(*) Security number memorized!");
               cReadMode = 0; 
               break;

			case 20: 
               m_iPlayerMaxLevel = atoi(token); 
               cReadMode = 0;
               break;

			case 21: 
					
					cReadMode = 0;
					break;

			case 22: // Coded by Mkintosh
					if ((memcmp(token, "HIGH", 4) == 0) || (memcmp(token, "high", 4) == 0)) 
					{
						m_iGoldRate = 3000; 
						PutLogList("(*) Gold drop rate HIGH");
					}
					else if ((memcmp(token, "MEDIUM", 6) == 0) || (memcmp(token, "medium", 6) == 0)) 
					{
						m_iGoldRate = 6000; 
						PutLogList("(*) Gold drop rate MEDIUM");
					}
					else if ((memcmp(token, "LOW", 3) == 0) || (memcmp(token, "low", 3) == 0)) 
					{
						m_iGoldRate = 9000; 
						PutLogList("(*) Gold drop rate LOW");
					}
					else 
					{ 
						PutLogList("(!!!) Gold drop rate must be either HIGH/MEDIUM/LOW");
						return FALSE; 
					}
					cReadMode = 0;
					break;

			case 23:
				// centu - added exp rate setting
					if ((memcmp(token, "HIGH", 4) == 0) || (memcmp(token, "high", 4) == 0)) 
					{
						m_iExpSetting = 2; 
						PutLogList("(*) Experience HIGH");
					}
					else if ((memcmp(token, "MEDIUM", 6) == 0) || (memcmp(token, "medium", 6) == 0)) 
					{
						m_iExpSetting = 1; 
						PutLogList("(*) Experience MEDIUM");
					}
					else if ((memcmp(token, "LOW", 3) == 0) || (memcmp(token, "low", 3) == 0)) 
					{
						m_iExpSetting = 0; 
						PutLogList("(*) Experience LOW");
					}
					else 
					{ 
						PutLogList("(!!!) Experience must be either HIGH/MEDIUM/LOW");
						return FALSE; 
					}
					cReadMode = 0;
					break;

				case 24: 
					m_iGuildCost = atoi(token); 
					wsprintf(cTxt, "(*) Creating guild costs (%d) gold", m_iGuildCost); 
					PutLogList(cTxt); 
					cReadMode = 0; 
					break;

			case 25: 
				
					if ((strlen(token) < 1) || (strlen(token) > 10000)) 
					{ 
						PutLogList("(!!!) Rare drop rate invalid must be between 1 to 10000");
						return FALSE; 
					} 
					else 
					{ 
						m_iRareDropRate = atoi(token);
					} 
					wsprintf(cTxt, "(*) Rare drop rate: (%d)", m_iRareDropRate); 
					PutLogList(cTxt); 
					cReadMode = 0; 
					break;

			case 26: 
               
				// centu - added clear map time to settings
				if (memcmp(token, "1", 1) == 0)
				{
					m_iClearMapTime = 3600;
					PutLogList("(*) Clear map timed to 1 hour."); 
				}
				else if (memcmp(token, "2", 1) == 0)
				{
					m_iClearMapTime = 7200;
					PutLogList("(*) Clear map timed to 2 hours."); 
				}
				else if (memcmp(token, "30", 2) == 0)
				{
					m_iClearMapTime = 1800;
					PutLogList("(*) Clear map timed to 30 minutes."); 
				}
				else if (memcmp(token, "15", 2) == 0)
				{
					m_iClearMapTime = 900;
					PutLogList("(*) Clear map timed to 15 minutes.");
				}
               
               cReadMode = 0; 
               break;

			case 27:
				if ((strlen(token) != 0) && (strlen(token) <= 100) && (strlen(token) >= 1))
				{
					m_iRatingAdjust = atoi(token);
				}
				else
				{
					wsprintf(cTxt, "(!!!) RATING-ADJUST: (%s) invalid must be between 1 to 100", token);
					PutLogList(cTxt);
				}
				wsprintf(cTxt, "(*) Player gains (%d) REP.", m_iRatingAdjust);
				PutLogList(cTxt);
				cReadMode = 0;
				break;

			case 28:
				m_iDKCost = atoi(token);
				wsprintf(cTxt, "(*) DK Set costs (%d) gold", m_iDKCost);
				PutLogList(cTxt);
				cReadMode = 0;
				break;
				
			
			}
         } 
         else { 
            if (memcmp(token, "primary-drop-rate"      , 17) == 0)   cReadMode = 1; 
            if (memcmp(token, "secondary-drop-rate"      , 19) == 0) cReadMode = 2; 
            if (memcmp(token, "enemy-kill-mode"         , 15) == 0)  cReadMode = 3; 
            if (memcmp(token, "enemy-kill-adjust"      , 17) == 0)   cReadMode = 4; 
            if (memcmp(token, "admin-security"         , 14) == 0)   cReadMode = 5; 
            if (memcmp(token, "monday-raid-time"      , 16) == 0)    cReadMode = 6; 
            if (memcmp(token, "tuesday-raid-time"      , 17) == 0)   cReadMode = 7; 
            if (memcmp(token, "wednesday-raid-time"      , 19) == 0) cReadMode = 8; 
            if (memcmp(token, "thursday-raid-time"      , 18) == 0)  cReadMode = 9; 
            if (memcmp(token, "friday-raid-time"      , 16) == 0)    cReadMode = 10; 
            if (memcmp(token, "saturday-raid-time"      , 18) == 0)  cReadMode = 11; 
            if (memcmp(token, "sunday-raid-time"      , 16) == 0)    cReadMode = 12; 
			if (memcmp(token, "log-chat-settings", 17) == 0)		 cReadMode = 13;
			if (memcmp(token, "summonguild-cost", 16) == 0)			 cReadMode = 14;
			if (memcmp(token, "slate-success-rate", 18) == 0)		 cReadMode = 15;
			if (memcmp(token, "character-stat-limit", 20) == 0)		 cReadMode = 16;
			if (memcmp(token, "character-skill-limit", 21) == 0)	 cReadMode = 17;
			// 18
			if (memcmp(token, "admin-security-code", 19) == 0)		 cReadMode = 19;
			if (memcmp(token, "max-player-level", 16) == 0)			 cReadMode = 20;
			if (memcmp(token, "build-date", 10) == 0)				 cReadMode = 21;
			if (memcmp(token, "gold-drop-rate", 14) == 0)			 cReadMode = 22;
			if (memcmp(token, "exp-rate", 8) == 0)					 cReadMode = 23;
			if (memcmp(token, "guild-cost", 10) == 0)				 cReadMode = 24;
			if (memcmp(token, "rare-drop-rate"      , 14) == 0)		 cReadMode = 25;
			if (memcmp(token, "clear-map-time"      , 14) == 0)		 cReadMode = 26;
			if (memcmp(token, "rating-adjust", 13) == 0)		     cReadMode = 27;
			if (memcmp(token, "dk-set-cost", 11) == 0)				 cReadMode = 28;
		 } 

         token = pStrTok->pGet(); 
      } 

      delete pStrTok; 
      delete[] cp;

	  fclose(pFile);
   } 

   return TRUE; 
} 

void CGame::SendNotifyMsg(int iFromH, int iToH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, char* pString, DWORD sV4, DWORD sV5, DWORD sV6, DWORD sV7, DWORD sV8, DWORD sV9, char* pString2)
{
	char cData[1000];
	DWORD* dwp;
	WORD* wp;
	char* cp;
	short* sp;
	int* ip, iRet, i;

	if (m_pClientList[iToH] == NULL) return;

	ZeroMemory(cData, sizeof(cData));

	dwp = (DWORD*)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_NOTIFY;

	wp = (WORD*)(cData + DEF_INDEX2_MSGTYPE);
	*wp = wMsgType;

	cp = (char*)(cData + DEF_INDEX2_MSGTYPE + 2);

	// !!! sV1, sV2, sV3쨈횂 DWORD횉체��횙��쨩 쨍챠쩍횋횉횕쨋처.
	switch (wMsgType) {
	case DEF_NOTIFY_EVENTFISHMODE:
		wp = (WORD*)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV2;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV3;
		cp += 2;

		memcpy(cp, pString, 21);
		cp += 21;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 33);
		break;

		//LifeX Party Cords
	case DEF_SEND_PARTYCOORDS:
	case DEF_NOTIFY_DGKILL:
	case DEF_NOTIFY_ENERGYSPHEREGOALIN:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV3;
		cp += 4;

		if (pString != NULL) memcpy(cp, pString, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 28);
		break;

	case DEF_SEND_PARTYHP: //New Party Status - ZeroEoyPnk
	case DEF_NOTIFY_HELDENIANCOUNT:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV3;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV4;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV5;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV6;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 30);
		break;

		// New 07/05/2004
		// Party Notify Msg's
	case DEF_NOTIFY_PARTY:
		switch (sV1) {
		case 4:
		case 6:
			wp = (WORD*)cp;
			*wp = (WORD)sV1;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV2;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV3;
			cp += 2;

			memcpy(cp, pString, 10);
			cp += 10;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 22);
			break;

		case 5:
			wp = (WORD*)cp;
			*wp = (WORD)sV1;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV2;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV3;
			cp += 2;

			memcpy(cp, pString, sV3 * 11);
			cp += sV3 * 11;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 12 + (sV3 * 11));
			break;

		default:
			wp = (WORD*)cp;
			*wp = (WORD)sV1;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV2;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV3;
			cp += 2;

			wp = (WORD*)cp;
			*wp = (WORD)sV4;
			cp += 2;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 14);
			break;
		}
		break;

	case DEF_NOTIFY_UPGRADEHEROCAPE:
	case DEF_NOTIFY_GIZONITEMCANGE:
		sp = (short*)cp;
		*sp = (short)sV1;
		cp += 2;

		*cp = (char)sV2;
		cp++;

		sp = (short*)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV5;
		cp += 2;

		*cp = (char)sV6;
		cp++;

		*cp = (char)sV7;
		cp++;

		dwp = (DWORD*)cp;
		*dwp = sV8;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 41);
		break;

	case DEF_NOTIFY_TCLOC:
		wp = (WORD*)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV2;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		wp = (WORD*)cp;
		*wp = (WORD)sV4;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV5;
		cp += 2;

		memcpy(cp, pString2, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 34);
		break;

		//New 11/05/2004
	case DEF_NOTIFY_GRANDMAGICRESULT:
		wp = (WORD*)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV2;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)sV3;
		cp += 2;

		memcpy(cp, pString, 10);
		cp += 10;

		wp = (WORD*)cp;
		*wp = (WORD)sV4;
		cp += 2;

		if (sV9 > 0) {
			memcpy(cp, pString2, (sV9 * 2) + 2);
			cp += (sV9 * 2) + 2;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, (sV9 * 2) + 26);
		}
		else {
			sp = (short*)cp;
			*sp = 0;
			cp += 2;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 26);
		}
		break;

	case DEF_NOTIFY_MAPSTATUSNEXT:
	case DEF_NOTIFY_MAPSTATUSLAST:
		memcpy(cp, pString, sV1);
		cp += sV1;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 6 + sV1);
		break;

	case DEF_NOTIFY_BUILDITEMSUCCESS:
	case DEF_NOTIFY_BUILDITEMFAIL:
		if (sV1 >= 0) {
			sp = (short*)cp;
			*sp = (short)sV1;
			cp += 2;
		}
		else {
			sp = (short*)cp;
			*sp = (short)sV1 + 10000;
			cp += 2;
		}

		sp = (short*)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_QUESTCONTENTS:
		sp = (short*)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV5;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV8;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV9;
		cp += 2;

		if (pString2 != NULL) memcpy(cp, pString2, 20);
		cp += 20;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 44);
		break;

	case DEF_NOTIFY_SETEXCHANGEITEM:
	case DEF_NOTIFY_OPENEXCHANGEWINDOW:
		sp = (short*)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV3;
		cp += 2;

		ip = (int*)cp;
		*ip = (int)sV4;
		cp += 4;

		*cp = (char)sV5;
		cp++;

		sp = (short*)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV8;
		cp += 2;

		memcpy(cp, pString, 20);
		cp += 20;

		memcpy(cp, m_pClientList[iFromH]->m_cCharName, 10);
		cp += 10;

		// v1.42
		dwp = (DWORD*)cp;
		*dwp = (DWORD)sV9;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 57);
		break;

	case DEF_NOTIFY_ITEMPOSLIST:
		for (i = 0; i < DEF_MAXITEMS; i++) {
			sp = (short*)cp;
			*sp = (short)m_pClientList[iToH]->m_ItemPosList[i].x;
			cp += 2;

			sp = (short*)cp;
			*sp = (short)m_pClientList[iToH]->m_ItemPosList[i].y;
			cp += 2;
		}
		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 6 + (DEF_MAXITEMS * 4));
		break;

	case DEF_NOTIFY_ADMINIFO:
		switch (sV1) {
		case 1:
			// NPC��횉 횁짚쨘쨍쨍짝 쩐챵쩐챤쩔횂쨈횢.
			ip = (int*)cp;
			*ip = m_pNpcList[sV2]->m_iHP;
			cp += 4;

			ip = (int*)cp;
			*ip = m_pNpcList[sV2]->m_iDefenseRatio;
			cp += 4;

			ip = (int*)cp;
			*ip = m_pNpcList[sV2]->m_bIsSummoned;
			cp += 4;

			ip = (int*)cp;
			*ip = m_pNpcList[sV2]->m_cActionLimit;
			cp += 4;

			ip = (int*)cp;
			*ip = m_pNpcList[sV2]->m_iHitDice;
			cp += 4;

			dwp = (DWORD*)cp; // v1.4
			*dwp = m_pNpcList[sV2]->m_dwDeadTime;
			cp += 4;

			dwp = (DWORD*)cp;
			*dwp = m_pNpcList[sV2]->m_dwRegenTime;
			cp += 4;

			ip = (int*)cp;
			*ip = (int)m_pNpcList[sV2]->m_bIsKilled;
			cp += 4;

			iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 26 + 12);
			break;
		}
		break;

	case DEF_NOTIFY_NPCTALK:
		sp = (short*)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV2;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV3;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV4;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV5;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV6;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV7;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV8;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)sV9;
		cp += 2;

		if (pString != NULL) memcpy(cp, pString, 20);
		cp += 20;

		if (pString2 != NULL) memcpy(cp, pString2, 20);
		cp += 20;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 64);
		break;

	case DEF_NOTIFY_SUPERATTACKLEFT:
		sp = (short*)cp;
		*sp = m_pClientList[iToH]->m_iSuperAttackLeft;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case DEF_NOTIFY_SAFEATTACKMODE:
		*cp = m_pClientList[iToH]->m_bIsSafeAttackMode;
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case DEF_NOTIFY_QUERY_JOINPARTY:
	case DEF_NOTIFY_IPACCOUNTINFO:
		strcpy(cp, pString);
		cp += strlen(pString);

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 6 + strlen(pString) + 1);
		break;

	case DEF_NOTIFY_REWARDGOLD:
		dwp = (DWORD*)cp;
		*dwp = m_pClientList[iToH]->m_iRewardGold;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_SERVERSHUTDOWN:
	case DEF_NOTIFY_GLOBALATTACKMODE:
	case DEF_NOTIFY_WHETHERCHANGE:
	case DEF_NOTIFY_TIMECHANGE:
	case DEF_NOTIFY_HUNGER:
		*cp = (char)sV1;
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 7);
		break;

	case DEF_NOTIFY_NOTICEMSG:
		memcpy(cp, pString, strlen(pString));
		cp += strlen(pString);

		*cp = NULL;
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, strlen(pString) + 7);
		break;

	case DEF_NOTIFY_RATINGPLAYER:
		*cp = (char)sV1;
		cp++;

		memcpy(cp, pString, 10);
		cp += 10;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iRating;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 21);
		break;

	case DEF_NOTIFY_PLAYERPROFILE:
		if (strlen(pString) > 100) {
			memcpy(cp, pString, 100);
			cp += 100;
		}
		else {
			memcpy(cp, pString, strlen(pString));
			cp += strlen(pString);
		}
		*cp = NULL;
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 7 + strlen(pString));
		break;

		// New 10/05/2004 Changed
	case DEF_NOTIFY_WHISPERMODEON:
	case DEF_NOTIFY_WHISPERMODEOFF:
	case DEF_NOTIFY_PLAYERNOTONGAME:
		memcpy(cp, pString, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

		// New 15/05/2004 Changed
	case DEF_NOTIFY_PLAYERONGAME:
		memcpy(cp, pString, 10);
		cp += 10;

		if (pString[0] != 0) {
			memcpy(cp, pString2, 14);
			cp += 14;
		}

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 30);
		break;

	case DEF_NOTIFY_REPAIRALLPRICES:
		wp = (WORD*)cp;
		*wp = (WORD)m_pClientList[iToH]->totalItemRepair;
		cp += 2;

		for (i = 0; i < m_pClientList[iToH]->totalItemRepair; i++)
		{
			*cp = (char)m_pClientList[iToH]->m_stRepairAll[i].index;
			cp++;

			wp = (WORD*)cp;
			*wp = (WORD)m_pClientList[iToH]->m_stRepairAll[i].price;
			cp += 2;
		}

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 8 + (m_pClientList[iToH]->totalItemRepair * 3));
		break;

	case DEF_NOTIFY_HELP:
	case DEF_NOTIFY_QUESTREWARD:
	case DEF_NOTIFY_REPAIRITEMPRICE:
	case DEF_NOTIFY_SELLITEMPRICE:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)sV1;
		cp += 4;

		dwp = (DWORD*)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		dwp = (DWORD*)cp;
		*dwp = (DWORD)sV3;
		cp += 4;

		dwp = (DWORD*)cp;
		*dwp = (DWORD)sV4;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 42);
		break;

	case DEF_NOTIFY_TOTALUSERS:
		wp = (WORD*)cp;
		*wp = (WORD)m_iTotalGameServerClients;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 8);
		break;

	case DEF_NOTIFY_SERVERCHANGE:
		memcpy(cp, m_pClientList[iToH]->m_cMapName, 10);
		cp += 10;

		// World Server connection across hgservers, behind router problem
		// ArchAngel fix
		if (m_iGameServerMode == 1) // Mode = 1 is LAN or ROUTER (behind router)
		{
			if (memcmp(m_cLogServerAddr, m_cGameServerAddr, 15) == 0)
			{
				memcpy(cp, m_cGameServerAddrExternal, 15);
			}
			else
			{
				memcpy(cp, m_cLogServerAddr, 15);
			}
		}
		else if (m_iGameServerMode == 2)// mode = 2 INTERNET
		{
			memcpy(cp, m_cLogServerAddr, 15);
		}
		cp += 15;

		ip = (int*)cp;
		*ip = m_iLogServerPort;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 16 + 19);
		break;

	case DEF_NOTIFY_ENEMYKILLREWARD:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iExp;
		cp += 4;

		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iEnemyKillCount;
		cp += 4;

		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iMaxEK;
		cp += 4;

		memcpy(cp, m_pClientList[sV1]->m_cCharName, 10);
		cp += 10;

		memcpy(cp, m_pClientList[sV1]->m_cGuildName, 20);
		cp += 20;

		sp = (short*)cp;
		*sp = (short)m_pClientList[sV1]->m_iGuildRank;
		cp += 2;

		sp = (short*)cp;
		*sp = (short)m_pClientList[iToH]->m_iWarContribution;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 48);
		break;

	case DEF_NOTIFY_USERJOIN:
		memcpy(cp, pString, 21);
		cp += 21;
		memcpy(cp, pString2, 22);
		cp += 22;
		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 48);
		break;

	case DEF_NOTIFY_PKCAPTURED:
		// PK쨍짝 ��창쩐횘쨈횢.
		// PK��횉 PKcount
		wp = (WORD*)cp;
		*wp = (WORD)sV1;
		cp += 2;
		wp = (WORD*)cp;
		*wp = (WORD)sV2;
		cp += 2;
		memcpy(cp, pString, 10);
		cp += 10;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iRewardGold;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = m_pClientList[iToH]->m_iExp;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 28);
		break;

	case DEF_NOTIFY_PKPENALTY:
		// PK 횈채쨀횓횈쩌쨍짝 쨍횚쩐첬쨈횢.
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iExp;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iStr;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iVit;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iDex;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iInt;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iMag;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iCharisma;
		cp += 4;
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iPKCount;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 38);
		break;

	case DEF_NOTIFY_TRAVELERLIMITEDLEVEL:
	case DEF_NOTIFY_LIMITEDLEVEL:
	case DEF_NOTIFY_EXP:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iExp;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iRating;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 14);
		break;

	case DEF_NOTIFY_HP:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iHP;
		cp += 4;

		if ((m_pClientList[iToH]->m_iPartyID != NULL) && (m_pClientList[iToH]->m_iPartyStatus == DEF_PARTYSTATUS_CONFIRM))
		{
			RefreshPartyStatus(iToH);
		}

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_MP:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iMP;
		cp += 4;

		if ((m_pClientList[iToH]->m_iPartyID != NULL) && (m_pClientList[iToH]->m_iPartyStatus == DEF_PARTYSTATUS_CONFIRM))
		{
			RefreshPartyStatus(iToH);
		}

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_SP:
		dwp = (DWORD*)cp;
		*dwp = (DWORD)m_pClientList[iToH]->m_iSP;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_RESUR_ON:
	case DEF_NOTIFY_RESUR_OFF:
		int i;

		for (i = 0; i < DEF_MAXMAGICTYPE; i++) {
			*cp = m_pClientList[iToH]->m_cMagicMastery[i];
			cp++;
		}

		for (i = 0; i < DEF_MAXSKILLTYPE; i++) {
			*cp = m_pClientList[iToH]->m_cSkillMastery[i];
			cp++;
		}

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 6 + DEF_MAXMAGICTYPE + DEF_MAXSKILLTYPE);
		break;

	/* Centuu: msgs agrupados */
	case DEF_NOTIFY_HELDENIANSTART:
	case DEF_NOTIFY_ANGEL_RECEIVED:
	case DEF_NOTIFY_DEATHMATCHSTART: // MORLA 2.3 - DEATHMACH ON
	case DEF_NOTIFY_DEATHMATCHEND: // MORLA 2.3 - DEATHMACH OFF
	case DEF_NOTIFY_MORLEARPJ:
	case DEF_NOTIFY_NOMOREAGRICULTURE:
	case DEF_NOTIFY_AGRICULTURESKILLLIMIT:
	case DEF_NOTIFY_AGRICULTURENOAREA:
	case DEF_NOTIFY_APOCFORCERECALLPLAYERS:
	case DEF_NOTIFY_APOCGATESTARTMSG:
	case DEF_NOTIFY_APOCGATEENDMSG:
	case DEF_NOTIFY_NORECALL:
	case DEF_NOTIFY_ABADDONTHUNDER:
	case DEF_NOTIFY_0BE8:
	case DEF_NOTIFY_HELDENIANTELEPORT:
	case DEF_NOTIFY_HELDENIANEND:
	case DEF_NOTIFY_RESURRECTPLAYER:
	case DEF_NOTIFY_SLATE_EXP:
	case DEF_NOTIFY_SLATE_MANA:
	case DEF_NOTIFY_SLATE_INVINCIBLE:
	case DEF_NOTIFY_SLATE_CREATEFAIL:
	case DEF_NOTIFY_NOMORECRUSADESTRUCTURE:
	case DEF_NOTIFY_EXCHANGEITEMCOMPLETE:
	case DEF_NOTIFY_CANCELEXCHANGEITEM:
	case DEF_NOTIFY_NOTFLAGSPOT:
	case DEF_NOTIFY_CRAFTING_SUCCESS:
	case DEF_NOTIFY_POTIONSUCCESS:
	case DEF_NOTIFY_LOWPOTIONSKILL:
	case DEF_NOTIFY_POTIONFAIL:
	case DEF_NOTIFY_NOMATCHINGPOTION:
	case DEF_NOTIFY_ADMINUSERLEVELLOW:
	case DEF_NOTIFY_TOBERECALLED:
	case DEF_NOTIFY_CANNOTITEMTOBANK:
	case DEF_NOTIFY_STATECHANGE_FAILED:
	case DEF_NOTIFY_SETTING_FAILED:
	case DEF_NOTIFY_NOGUILDMASTERLEVEL:
	case DEF_NOTIFY_CANNOTBANGUILDMAN:
	case DEF_NOTIFY_CAPTURETHEFLAGSTART: //50Cent - Capture The Flag
	case DEF_NOTIFY_ARESDENCAPTUREDELVINEFLAG:
	case DEF_NOTIFY_ELVINECAPTUREDARESDENFLAG:
	case DEF_NOTIFY_ELVINEFLAGBACKTOCH:
	case DEF_NOTIFY_ARESDENFLAGBACKTOCH:
	case DEF_NOTIFY_ELVINEWINSROUND:
	case DEF_NOTIFY_ARESDENWINSROUND:
	case DEF_NOTIFY_ELVINEWINCTF:
	case DEF_NOTIFY_ARESDENWINCTF:
	case DEF_NOTIFY_TIECTF:
		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 6);
		break;

	case DEF_MAX_STATS: //LifeX Fix Bytes Accuracy 01/01
	case DEF_NOTIFY_QUESTCOUNTER:
	case DEF_NOTIFY_ITEMUPGRADEFAIL:
	case DEF_NOTIFY_CANNOTCONSTRUCT:
	case DEF_NOTIFY_METEORSTRIKECOMING:
	case DEF_NOTIFY_METEORSTRIKEHIT:
	case DEF_NOTIFY_HELPFAILED:
	case DEF_NOTIFY_SPECIALABILITYENABLED:
	case DEF_NOTIFY_FORCEDISCONN:
	case DEF_NOTIFY_OBSERVERMODE:
	case DEF_NOTIFY_QUESTCOMPLETED:
	case DEF_NOTIFY_QUESTABORTED:
	case DEF_NOTIFY_ENEMYKILLS:
	case DEF_NOTIFY_DOWNSKILLINDEXSET:
	case DEF_NOTIFY_RESPONSE_CREATENEWPARTY:
	case DEF_NOTIFY_CRAFTING_FAIL:	//reversed by Snoopy: 0x0BF1:
	case DEF_NOTIFY_ANGEL_FAILED:
	case DEF_NOTIFY_FIGHTZONERESERVE:
	case DEF_NOTIFY_FORCERECALLTIME:
	case DEF_NOTIFY_HELDENIANVICTORY:
	case DEF_NOTIFY_MONSTERCOUNT:
	case DEF_NOTIFY_SLATE_STATUS:
	case DEF_NOTIFY_FISHCANCELED:
	case DEF_NOTIFY_FISHSUCCESS:
	case DEF_NOTIFY_FISHFAIL:
	case DEF_NOTIFY_DEBUGMSG:
	case DEF_NOTIFY_FISHCHANCE:
	case DEF_NOTIFY_CANNOTRATING:
	case DEF_NOTIFY_SKILLUSINGEND:
	case DEF_NOTIFY_SLATE_CREATESUCCESS:
	case DEF_NOTIFY_MAJESTIC_LEVEL:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_ITEMDEPLETED_ERASEITEM:
	case DEF_NOTIFY_SKILL:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		wp = (WORD *)cp;
		*wp = (WORD)sV2;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_ITEMCOLORCHANGE:
	case DEF_NOTIFY_ITEMRELEASED:
	case DEF_NOTIFY_ITEMLIFESPANEND:
		sp = (short *)cp;
		*sp = (short)sV1;
		cp += 2;

		sp = (short *)cp;
		*sp = (short)sV2;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 10);
		break;

	case DEF_NOTIFY_DROPITEMFIN_COUNTCHANGED:
	case DEF_NOTIFY_DROPITEMFIN_ERASEITEM:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		ip = (int *)cp;
		*ip = (int)sV2;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 12);
		break;

	case DEF_NOTIFY_REQRANGO: // Morla2.2 - Notify Rango
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV3;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 18);
		break;

	case DEF_NOTIFY_GIZONITEMUPGRADELEFT:
	case DEF_SEND_NPCHP: //50Cent - HP Ba
	case DEF_NOTIFY_ENERGYSPHERECREATED:
	case DEF_NOTIFY_ITEMSOLD:
	case DEF_NOTIFY_ITEMREPAIRED:
	case DEF_NOTIFY_SHOWMAP:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 14);
		break;

	case DEF_NOTIFY_SETITEMCOUNT:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		*cp = (char)sV3;
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 13);
		break;

	case DEF_NOTIFY_SPAWNEVENT:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		*cp = (char)sV3;   // Mob's type
		cp++;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 15);
		break;

	case DEF_NOTIFY_QUERY_DISMISSGUILDREQPERMISSION:
	case DEF_NOTIFY_QUERY_JOINGUILDREQPERMISSION:
	case DEF_NOTIFY_CANNOTJOINMOREGUILDSMAN:
	case DEF_NOTIFY_ABADDONKILLED:
		memcpy(cp, m_pClientList[iFromH]->m_cCharName, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case DEF_NOTIFY_CHANGEPLAYMODE: // 2.06 - by KLKS
	case DEF_NOTIFY_KILLED:
		memcpy(cp, pString, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case DEF_NOTIFY_MAGICEFFECTOFF:
	case DEF_NOTIFY_MAGICEFFECTON:
		wp = (WORD *)cp;
		*wp = (WORD)sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV2;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = (DWORD)sV3;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 16);
		break;

	case DEF_NOTIFY_CONSTRUCTIONPOINT:
	case DEF_NOTIFY_SPECIALABILITYSTATUS:
	case DEF_NOTIFY_DAMAGEMOVE:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV3;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 18);
		break;

	case DEF_NOTIFY_PLAYERSHUTUP:
	case DEF_NOTIFY_LOCKEDMAP:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		memcpy(cp, pString, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 20);
		break;

	case DEF_NOTIFY_ITEMATTRIBUTECHANGE:
		sp = (short *)cp;
		*sp = sV1;
		cp += 2;

		dwp = (DWORD *)cp;
		*dwp = sV2;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = sV3;
		cp += 4;

		dwp = (DWORD *)cp;
		*dwp = sV4;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 20);
		break;

	case DEF_NOTIFY_CRUSADE:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV3;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV4;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 22);
		break;

	case DEF_COMMONTYPE_JOINGUILDAPPROVE:
		if (m_pClientList[iFromH] != NULL)
			memcpy(cp, m_pClientList[iFromH]->m_cGuildName, 20);
		else memcpy(cp, "?", 1);
		cp += 20;

		sp = (short*)cp;
		*sp = DEF_GUILDSTARTRANK;
		cp += 2;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 28);
		break;

	case DEF_NOTIFY_APOCGATECLOSE:
	case DEF_NOTIFY_APOCGATEOPEN:
	case DEF_NOTIFY_REQGUILDNAMEANSWER:
	case DEF_NOTIFY_CANNOTREPAIRITEM:
	case DEF_NOTIFY_CANNOTSELLITEM:
	case DEF_NOTIFY_CANNOTGIVEITEM:
	case DEF_NOTIFY_GIVEITEMFIN_COUNTCHANGED:
	case DEF_NOTIFY_GIVEITEMFIN_ERASEITEM:
		ip = (int*)cp;
		*ip = (int)sV1;
		cp += 4;

		ip = (int*)cp;
		*ip = (int)sV2;
		cp += 4;

		memcpy(cp, pString, 20);
		cp += 20;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 34);
		break;

	case DEF_NOTIFY_STATECHANGE_SUCCESS:
	case DEF_NOTIFY_SETTING_SUCCESS:
	case DEF_NOTIFY_LEVELUP:
		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iLevel;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iStr;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iVit;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iDex;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iInt;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iMag;
		cp += 4;

		ip = (int*)cp;
		*ip = m_pClientList[iToH]->m_iCharisma;
		cp += 4;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 34);
		break;

	case DEF_NOTIFY_GUILDDISBANDED:
		memcpy(cp, pString, 20);
		cp += 20;

		memcpy(cp, m_pClientList[iToH]->m_cLocation, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 36);
		break;

	case DEF_COMMONTYPE_JOINGUILDREJECT:
	case DEF_COMMONTYPE_DISMISSGUILDAPPROVE:
	case DEF_COMMONTYPE_DISMISSGUILDREJECT:
		if (m_pClientList[iFromH] != NULL)
			memcpy(cp, m_pClientList[iFromH]->m_cGuildName, 20);
		else memcpy(cp, "?", 1);
		cp += 20;

		sp = (short*)cp;
		*sp = DEF_GUILDSTARTRANK;
		cp += 2;

		memcpy(cp, m_pClientList[iToH]->m_cLocation, 10);
		cp += 10;

		iRet = m_pClientList[iToH]->m_pXSock->iSendMsg(cData, 38);
		break;
	}

	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		break;
	}
}

// centu - Agregado Majestic Level
/*****************************************************************
**---------------------------FUNCTION---------------------------**
**             void Game::CheckLevelUp(int iClientH)            **
**-------------------------DESCRIPTION--------------------------**
** Level-Up                                                     **
**  - Level +1                                                  **
**  - +3 Level Up Points                                        **
**  - Reset Next Level EXP                                      **
**  - Civilian Level Limit                                      **
**      Player mode switches to Combatant                       **
**      when the limit is reached                               **
** Max Level                                                    **
**  - Majestic Points +1                                        **
**  - Majestic Level +1											**
**  - Reset Next Level EXP                                      **
**------------------------CREATION DATE-------------------------**
**                January 30, 2007; 3:06 PM; Dax                **
*****************************************************************/
void CGame::bCheckLevelUp(int iClientH)
{
	if (m_pClientList[iClientH] == NULL) return;
	while (m_pClientList[iClientH]->m_iExp >= m_pClientList[iClientH]->m_iNextLevelExp)
	{ 
		if (m_pClientList[iClientH]->m_iLevel < m_iPlayerMaxLevel)
		{
			m_pClientList[iClientH]->m_iLevel++;
			m_pClientList[iClientH]->m_iLU_Pool += 3;
			if (m_pClientList[iClientH]->m_iLevel > 100) 
			{
				if (m_pClientList[iClientH]->m_bIsPlayerCivil == TRUE) 
				{
					ForceChangePlayMode(iClientH, TRUE);
				}
			}
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_LEVELUP, NULL, NULL, NULL, NULL);
			m_pClientList[iClientH]->m_iNextLevelExp = m_iLevelExpTable[m_pClientList[iClientH]->m_iLevel + 1];
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);
			CalcTotalItemEffect(iClientH, -1, FALSE);
		}
		else 
		{
			m_pClientList[iClientH]->m_iMajesticLevel++;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAJESTIC_LEVEL, m_pClientList[iClientH]->m_iMajesticLevel, NULL, NULL, NULL, NULL);
			m_pClientList[iClientH]->m_iNextLevelExp = m_iLevelExpTable[m_iPlayerMaxLevel + m_pClientList[iClientH]->m_iMajesticLevel + 1];
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_EXP, NULL, NULL, NULL, NULL);
			m_pClientList[iClientH]->m_iGizonItemUpgradeLeft++;		
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GIZONITEMUPGRADELEFT, m_pClientList[iClientH]->m_iGizonItemUpgradeLeft, 1, NULL, NULL, NULL);
		}
	}
}

void CGame::RequestTeleportHandler(int iClientH, char * pData, char * cMapName, int dX, int dY)
{
 char  * pBuffer, cTempMapName[21];
 DWORD * dwp;
 WORD  * wp;
 char  * cp, cDestMapName[11], cDir, cMapIndex, cPoints;
 short * sp, sX, sY, sSummonPoints, sV1;
 int   * ip, i, iRet, iSize, iDestX, iDestY, iExH, iMapSide, iTemp, iTemp2, iMapside, iMapside2, iQuestNumber, iQuestType;
 BOOL    bRet, bIsLockedMapNotify;
 SYSTEMTIME SysTime;

	cPoints = 0;
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE) return;
	if (m_pClientList[iClientH]->m_bIsOnWaitingProcess == TRUE) return;
	if (m_pClientList[iClientH]->m_bIsForceDisconnect == TRUE) return;
	if ((m_pClientList[iClientH]->m_cSide == 2) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "aresden", 7) == 0) &&
		((pData[0] == '1')  || (pData[0] == '3'))) {
		if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) return;
	}	
	if ((m_pClientList[iClientH]->m_cSide == 1) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "elvine", 6) == 0) &&
		((pData[0] == '1')  || (pData[0] == '3'))) {
		if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) return;
	}
	bIsLockedMapNotify = FALSE;
	// Prevent recalls spells/scrolls, and any recall type magic if forbidden on the map
	if ((m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsRecallImpossible == TRUE) 
		&& (m_pClientList[iClientH]->m_iAdminUserLevel == 0) 
		&& (m_pClientList[iClientH]->m_bIsKilled == FALSE) 
		&& (m_pClientList[iClientH]->m_iHP > 0)) 
	{	if (   (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsApocalypseMap == TRUE)
				&& (m_bIsApocalypseMode == FALSE))
		{	// Can recall
		}else // either Apocalypse running on Apoc map or not an apoc map
		{	if ((pData[0] == '3') ||(pData[0] == '1')) 
			// '0' is forced recall
			// '1' is recall spells
			// '2' is fixed, stated destination such as tickets or GM TPing characters
			// '3' is fixed, stated destination but forbidden on NoRecall map
			// '' Means client is on TP tile and asks the server to perform the TP.
			{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_NORECALL, NULL, NULL, NULL, NULL);
				return;
	}	}	}
	if (m_pClientList[iClientH]->m_cExchangeMode != 0) {
		iExH = m_pClientList[iClientH]->m_iExchangeH;
		_ClearExchangeStatus(iExH);
		_ClearExchangeStatus(iClientH);
	}
	m_pClientList[iClientH]->m_dwLastActionTime = m_pClientList[iClientH]->m_dwAFKCheckTime = timeGetTime();
	
	RemoveFromTarget(iClientH, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_TELEPORT);
	
	m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->ClearOwner(13, iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_LOG, DEF_MSGTYPE_REJECT, NULL, NULL, NULL);
	sX = m_pClientList[iClientH]->m_sX;
	sY = m_pClientList[iClientH]->m_sY;
	ZeroMemory(cDestMapName, sizeof(cDestMapName));
	bRet = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->bSearchTeleportDest(sX, sY, cDestMapName, &iDestX, &iDestY, &cDir);
	if ((strcmp(m_pClientList[iClientH]->m_cLockedMapName, "NONE") != 0) && (m_pClientList[iClientH]->m_iLockedMapTime > 0)) {
		iMapSide = iGetMapLocationSide(cDestMapName);
		if (iMapSide > 3) iMapSide -= 2;
		if ((iMapSide != 0) && (m_pClientList[iClientH]->m_cSide != iMapSide)) {
		
			iDestX = -1;
			iDestY = -1;
			bIsLockedMapNotify = TRUE;
			ZeroMemory(cDestMapName, sizeof(cDestMapName));
			strcpy(cDestMapName, m_pClientList[iClientH]->m_cLockedMapName);
		}
	}
	if ((bRet == TRUE) && (cMapName == NULL)) {
		for (i = 0; i < DEF_MAXMAPS; i++) {
			if ((m_pMapList[i] != NULL) && (memcmp(m_pMapList[i]->m_cName, cDestMapName, 10) == 0)) {
				m_pClientList[iClientH]->m_sX   = iDestX;
				m_pClientList[iClientH]->m_sY   = iDestY;
				m_pClientList[iClientH]->m_cDir = cDir;
				m_pClientList[iClientH]->m_cMapIndex = i;
				ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
				memcpy(m_pClientList[iClientH]->m_cMapName, m_pMapList[i]->m_cName, 10);
				goto RTH_NEXTSTEP;
			}
		}
		m_pClientList[iClientH]->m_sX   = iDestX;
		m_pClientList[iClientH]->m_sY   = iDestY;
		m_pClientList[iClientH]->m_cDir = cDir;
		ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
		memcpy(m_pClientList[iClientH]->m_cMapName, cDestMapName, 10);
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_CONFUSE, m_pClientList[iClientH]->m_cMagicEffectStatus[ DEF_MAGICTYPE_CONFUSE ], NULL, NULL);
		SetSlateFlag(iClientH, DEF_NOTIFY_SLATECLEAR, FALSE);
		bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA_REPLY, iClientH, FALSE);
		m_pClientList[iClientH]->m_bIsOnServerChange = TRUE;
		m_pClientList[iClientH]->m_bIsOnWaitingProcess = TRUE;
		return;
	}
	else {
		switch (pData[0]) {
		case '0':
		case '1':
			ZeroMemory(cTempMapName, sizeof(cTempMapName));
			if (m_pClientList[iClientH]->m_cSide == 0) { 
				strcpy(cTempMapName, "default"); 
			}
			else if (m_pClientList[iClientH]->m_iLevel > 80) {
				if (m_pClientList[iClientH]->m_cSide == 1) {
					strcpy(cTempMapName, "aresden");
				}
				else {
					strcpy(cTempMapName, "elvine");
				}
			}
			else if (m_pClientList[iClientH]->m_cSide == 1) {
				strcpy(cTempMapName, "arefarm");
			}
			else {
				strcpy(cTempMapName, "elvfarm");
			}
			if ((strcmp(m_pClientList[iClientH]->m_cLockedMapName, "NONE") != 0) && (m_pClientList[iClientH]->m_iLockedMapTime > 0)) {
				bIsLockedMapNotify = TRUE;
				ZeroMemory(cTempMapName, sizeof(cTempMapName));
				strcpy(cTempMapName, m_pClientList[iClientH]->m_cLockedMapName);
			}
			for (i = 0; i < DEF_MAXMAPS; i++) {
				if ((m_pMapList[i] != NULL) && (memcmp(m_pMapList[i]->m_cName, cTempMapName, 10) == 0)) {
					
					short playerCoordX = m_pClientList[iClientH]->m_sX;
					short playerCoordY = m_pClientList[iClientH]->m_sY;

					GetMapInitialPoint(i, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_cLocation);

					if (playerCoordX == m_pClientList[iClientH]->m_sX && playerCoordY == m_pClientList[iClientH]->m_sY)
					{
						RequestTeleportHandler(iClientH, "1");
						return;
					}

					m_pClientList[iClientH]->m_cMapIndex = i;
					ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
					memcpy(m_pClientList[iClientH]->m_cMapName, m_pMapList[i]->m_cName, 10);
					goto RTH_NEXTSTEP;
				}
			}
			m_pClientList[iClientH]->m_sX   = -1;
			m_pClientList[iClientH]->m_sY   = -1;
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			memcpy(m_pClientList[iClientH]->m_cMapName, cTempMapName, 10);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_CONFUSE, m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE], NULL, NULL);
			SetSlateFlag(iClientH, DEF_NOTIFY_SLATECLEAR, FALSE);	
			bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA_REPLY, iClientH, FALSE, FALSE);
			m_pClientList[iClientH]->m_bIsOnServerChange = TRUE;
			m_pClientList[iClientH]->m_bIsOnWaitingProcess = TRUE;
			return;

		case '2':
			if ((strcmp(m_pClientList[iClientH]->m_cLockedMapName, "NONE") != 0) && 
				(m_pClientList[iClientH]->m_iLockedMapTime > 0) &&
				(memcmp(cMapName, "resurr", 6) != 0)) {
				dX = -1;
				dY = -1;
				bIsLockedMapNotify = TRUE;
				ZeroMemory(cTempMapName, sizeof(cTempMapName));
				strcpy(cTempMapName, m_pClientList[iClientH]->m_cLockedMapName);
			}
			else {
				ZeroMemory(cTempMapName, sizeof(cTempMapName));
				strcpy(cTempMapName, cMapName);
			}
			cMapIndex = iGetMapIndex(cTempMapName);
			if (cMapIndex == -1) {
				m_pClientList[iClientH]->m_sX   = dX;
				m_pClientList[iClientH]->m_sY   = dY;
				ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
				memcpy(m_pClientList[iClientH]->m_cMapName, cTempMapName, 10);
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_CONFUSE, m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE], NULL, NULL);
				SetSlateFlag(iClientH, DEF_NOTIFY_SLATECLEAR, FALSE);
				bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA_REPLY, iClientH, FALSE);
				m_pClientList[iClientH]->m_bIsOnServerChange   = TRUE;
				m_pClientList[iClientH]->m_bIsOnWaitingProcess = TRUE;
				return;
			}
			m_pClientList[iClientH]->m_sX   = dX;
			m_pClientList[iClientH]->m_sY   = dY;
			m_pClientList[iClientH]->m_cMapIndex = cMapIndex;
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			memcpy(m_pClientList[iClientH]->m_cMapName, m_pMapList[cMapIndex]->m_cName, 10);  
			goto RTH_NEXTSTEP;		
		
		case '3':
			if ((strcmp(m_pClientList[iClientH]->m_cLockedMapName, "NONE") != 0) && 
				(m_pClientList[iClientH]->m_iLockedMapTime > 0) &&
				(memcmp(cMapName, "resurr", 6) != 0)) {
				dX = -1;
				dY = -1;
				bIsLockedMapNotify = TRUE;
				ZeroMemory(cTempMapName, sizeof(cTempMapName));
				strcpy(cTempMapName, m_pClientList[iClientH]->m_cLockedMapName);
			}
			else {
				ZeroMemory(cTempMapName, sizeof(cTempMapName));
				strcpy(cTempMapName, cMapName);
			}
			cMapIndex = iGetMapIndex(cTempMapName);
			if (cMapIndex == -1) {
				m_pClientList[iClientH]->m_sX   = dX;
				m_pClientList[iClientH]->m_sY   = dY;
				ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
				memcpy(m_pClientList[iClientH]->m_cMapName, cTempMapName, 10);
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_CONFUSE, m_pClientList[iClientH]->m_cMagicEffectStatus[DEF_MAGICTYPE_CONFUSE], NULL, NULL);
				SetSlateFlag(iClientH, DEF_NOTIFY_SLATECLEAR, FALSE);
				bSendMsgToLS(MSGID_REQUEST_SAVEPLAYERDATA_REPLY, iClientH, FALSE);
				m_pClientList[iClientH]->m_bIsOnServerChange   = TRUE;
				m_pClientList[iClientH]->m_bIsOnWaitingProcess = TRUE;
				return;
			}		
			m_pClientList[iClientH]->m_sX   = dX;
			m_pClientList[iClientH]->m_sY   = dY;
			m_pClientList[iClientH]->m_cMapIndex = cMapIndex;
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			memcpy(m_pClientList[iClientH]->m_cMapName, m_pMapList[cMapIndex]->m_cName, 10);  
			goto RTH_NEXTSTEP;
		}
	}

RTH_NEXTSTEP:;

	SetPlayingStatus(iClientH);
	iTemp = m_pClientList[iClientH]->m_iStatus;
	iTemp = 0x0FFFFFFF & iTemp;
	iTemp2 = iGetPlayerABSStatus(iClientH);
	iTemp = iTemp | (iTemp2 << 28);
	m_pClientList[iClientH]->m_iStatus = iTemp;
	
	if ((m_pClientList[iClientH]->m_pIsProcessingAllowed == TRUE) && 
		(m_sLastHeldenianWinner != m_pClientList[iClientH]->m_cSide) && 
		(m_sLastHeldenianWinner != 0)) {
		cPoints = 100;
	}
	if (bIsLockedMapNotify == TRUE) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_LOCKEDMAP, m_pClientList[iClientH]->m_iLockedMapTime, NULL, NULL, m_pClientList[iClientH]->m_cLockedMapName);
	}
	pBuffer = new char [DEF_MSGBUFFERSIZE+1];
	ZeroMemory(pBuffer, DEF_MSGBUFFERSIZE+1);

	dwp  = (DWORD *)(pBuffer + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_INITDATA;
	wp   = (WORD *)(pBuffer + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_MSGTYPE_CONFIRM;
	cp = (char *)(pBuffer + DEF_INDEX2_MSGTYPE + 2);
	if (m_pClientList[iClientH]->m_bIsObserverMode == FALSE) {
		bGetEmptyPosition(&m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_cMapIndex);
	}
	else {
		GetMapInitialPoint(m_pClientList[iClientH]->m_cMapIndex, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY);
	}

	sp  = (short *)cp;
	*sp = iClientH;
	cp += 2;
//8
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sX - 14 - 5;
	cp += 2;
//10
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sY - 12 - 5;
	cp += 2;
//12
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sType;
	cp += 2;
//14
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr1;
	cp += 2;
//16
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr2;
	cp += 2;
//18
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr3;
	cp += 2;
//20
	sp  = (short *)cp;
	*sp = m_pClientList[iClientH]->m_sAppr4;
	cp += 2;
//22
	ip  = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iApprColor;
	cp += 4;
//26
	ip  = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iStatus;
	cp += 4;
//30
	
	memcpy(cp, m_pClientList[iClientH]->m_cMapName, 10);
	cp += 10;
//44
	memcpy(cp, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, 10);
	cp += 10;
//54
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFixedDayMode == TRUE) {
		*cp = 1;
	}
	else {
		*cp = m_cDayOrNight;
	}
	cp++;
//55
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFixedDayMode == TRUE) {
		*cp = NULL;
	}
	else {
		*cp = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cWhetherStatus;
	}
	cp++;
//56
	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iContribution;
	cp += 4;
//60
	if (m_pClientList[iClientH]->m_bIsObserverMode == FALSE) {
		m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetOwner(iClientH, DEF_OWNERTYPE_PLAYER, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY);
	}

	*cp = (char)m_pClientList[iClientH]->m_bIsObserverMode;
	cp++;
//61
	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iRating;
	cp += 4;
//65
	ip = (int *)cp;
	*ip = m_pClientList[iClientH]->m_iHP;
	cp += 4;
//69
	*cp = cPoints;
	cp++;
//70
	iSize = iComposeInitMapData(m_pClientList[iClientH]->m_sX - 13, m_pClientList[iClientH]->m_sY - 10, iClientH, cp);
	cp += iSize;

	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(pBuffer, 85 + iSize); // SephirotH fix - 66
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		DeleteClient(iClientH, TRUE, TRUE);
		if(pBuffer != NULL) delete[] pBuffer;
		return;
	}
	if(pBuffer != NULL) delete[] pBuffer;
	SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_LOG, DEF_MSGTYPE_CONFIRM, NULL, NULL, NULL);
	m_pClientList[iClientH]->m_bIsWarLocation = FALSE;
	m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 0;
	if ((m_pClientList[iClientH]->m_cSide == 1) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "elvine", 6) == 0) && 
		(m_pClientList[iClientH]->m_iAdminUserLevel < 1)) {
		m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
		m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
		CheckForceRecallTime(iClientH);
	}
	else if ((m_pClientList[iClientH]->m_cSide == 2) && 
		(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "aresden", 7) == 0) && 
		(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
		m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
		m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
		CheckForceRecallTime(iClientH);	
	}
	else if ((m_pClientList[iClientH]->m_cSide == 0) &&
		(m_bIsCrusadeMode == TRUE) &&
		((strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "elvine") == 0) ||
		(strcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, "aresden") == 0))) {
		if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) {
			m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
			m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
			CheckForceRecallTime(iClientH);	
			m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 1;
		}
	}
	// Heldenian: TP to GodH go to appropriate place...
	if ((m_bIsHeldenianMode == TRUE) && (bRet == TRUE) && (cMapName == NULL))
	{	if (memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "HRampart", 8) == 0)
		{	if (m_pClientList[iClientH]->m_iAdminUserLevel == 0)
			{	if (memcmp(cDestMapName, "GodH", 4) == 0)
				{	if (m_pClientList[iClientH]->m_cSide == m_sLastHeldenianWinner)
					{	iDestX = 54;
						iDestY = 67;
						cDir = 4;
					}else
					{	iDestX = 192 + iDice(1,20);
						iDestY = 166 + iDice(1,10);
						cDir = 7;
	}	}	}	}	}
	iMapside = iGetMapLocationSide(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName);
	if (iMapside > 3) iMapside2 = iMapside - 2;
	else iMapside2 = iMapside;
	m_pClientList[iClientH]->m_bIsInsideEnemyBuilding = 0;
	if ((m_pClientList[iClientH]->m_cSide != iMapside2) && (iMapside != 0)) {
		if ((iMapside <= 2) && 
			(m_pClientList[iClientH]->m_iAdminUserLevel == 0) && 
			(m_pClientList[iClientH]->m_cSide != 0)) {
			m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
			m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
			m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 1;
			m_pClientList[iClientH]->m_bIsInsideEnemyBuilding = TRUE;
		}
	}
	else{
		if ((m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFightZone == TRUE) &&
			(m_iFightzoneNoForceRecall == FALSE) && 
			(m_pClientList[iClientH]->m_iAdminUserLevel == 0)) {
			m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
			m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
			GetLocalTime(&SysTime);
			m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 2*60*20 - ((SysTime.wHour%2)*20*60 + SysTime.wMinute*20) - 2*20;
		}
		else{
			if ((memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "arejail", 7) == 0) ||
				(memcmp(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cLocationName, "elvjail", 7) == 0)) {
				if (m_pClientList[iClientH]->m_iAdminUserLevel == 0) {
					m_pClientList[iClientH]->m_bIsWarLocation = TRUE;
					m_pClientList[iClientH]->m_dwWarBeginTime = timeGetTime();
					if (m_pClientList[iClientH]->m_iTimeLeft_ForceRecall == 0) {
						m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 100;
					}
					else if(m_pClientList[iClientH]->m_iTimeLeft_ForceRecall > 100) {
						m_pClientList[iClientH]->m_iTimeLeft_ForceRecall = 100;
					}
				}
			}
		}
	}
	if (m_pClientList[iClientH]->m_iTimeLeft_ForceRecall > 0) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_FORCERECALLTIME, m_pClientList[iClientH]->m_iTimeLeft_ForceRecall, NULL, NULL, NULL);
		wsprintf(G_cTxt,"(!) Game Server Force Recall Time %d (%d)min", m_pClientList[iClientH]->m_iTimeLeft_ForceRecall, m_pClientList[iClientH]->m_iTimeLeft_ForceRecall/20) ;
		PutLogList(G_cTxt) ;
	}
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SAFEATTACKMODE, NULL, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_DOWNSKILLINDEXSET, m_pClientList[iClientH]->m_iDownSkillIndex, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ITEMPOSLIST, NULL, NULL, NULL, NULL);
	_SendQuestContents(iClientH);
	_CheckQuestEnvironment(iClientH);
	if (m_pClientList[iClientH]->m_iSpecialAbilityTime == 0) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SPECIALABILITYENABLED, NULL, NULL, NULL, NULL);
	}
	if (m_bIsCrusadeMode == TRUE) {
		if (m_pClientList[iClientH]->m_dwCrusadeGUID == 0) {
			m_pClientList[iClientH]->m_iCrusadeDuty			= 0;
			m_pClientList[iClientH]->m_iConstructionPoint	= 0;
			m_pClientList[iClientH]->m_dwCrusadeGUID = m_dwCrusadeGUID;
		}
		else if (m_pClientList[iClientH]->m_dwCrusadeGUID != m_dwCrusadeGUID) {
			m_pClientList[iClientH]->m_iCrusadeDuty       = 0;
			m_pClientList[iClientH]->m_iConstructionPoint = 0;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
			m_pClientList[iClientH]->m_dwCrusadeGUID = m_dwCrusadeGUID;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, 0, NULL, -1);		
		}
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, m_pClientList[iClientH]->m_iCrusadeDuty, NULL, NULL);
	}
	// Heldenian mode on
	else if (m_bIsHeldenianMode == TRUE) 
	{	sSummonPoints = 10000 + m_pClientList[iClientH]->m_iCharisma*100;
		if (m_pClientList[iClientH]->m_dwHeldenianGUID == NULL) 
		{	m_pClientList[iClientH]->m_dwHeldenianGUID    = m_dwHeldenianGUID;
			m_pClientList[iClientH]->m_iConstructionPoint = sSummonPoints;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
		}else if (m_pClientList[iClientH]->m_dwHeldenianGUID != m_dwHeldenianGUID) 
		{	m_pClientList[iClientH]->m_dwHeldenianGUID    = m_dwHeldenianGUID;
			m_pClientList[iClientH]->m_iConstructionPoint = sSummonPoints;
			m_pClientList[iClientH]->m_iWarContribution   = 0;
		}
		if (m_cHeldenianWinner == -1) 
		{	if (m_bHeldenianWarInitiated == TRUE) 
			{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANSTART, NULL, NULL, NULL, NULL);
			}else
			{	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANTELEPORT, NULL, NULL, NULL, NULL);
			}
		}
		m_pClientList[iClientH]->m_cWarType = 2;// character have been informed of heldenian starting...
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iClientH]->m_iConstructionPoint, m_pClientList[iClientH]->m_iWarContribution, 1, NULL);
		UpdateHeldenianStatus(iClientH);
	}
	else if ((m_pClientList[iClientH]->m_dwCrusadeGUID != 0) && (m_pClientList[iClientH]->m_cWarType == 1)) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, NULL, NULL, -1);
	}
	// The Heldenian he has participated is over...
	else if ( (m_pClientList[iClientH]->m_cWarType == 2) // Just finished Heldenian
			&& (m_pClientList[iClientH]->m_dwHeldenianGUID == m_dwHeldenianGUID)
			&& (m_pClientList[iClientH]->m_dwHeldenianGUID != NULL)) 
	{	m_pClientList[iClientH]->m_iConstructionPoint = 0;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELDENIANEND, NULL, NULL, NULL, NULL);
		m_pClientList[iClientH]->m_cWarType = 0; // Character is informed of Hedenian end... so he'll get XP later
	}
	else {
		m_pClientList[iClientH]->m_dwCrusadeGUID		= 0;
		m_pClientList[iClientH]->m_iWarContribution		= 0;
		m_pClientList[iClientH]->m_iConstructionPoint	= 0;
	}
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iClientH]->m_iConstructionPoint, m_pClientList[iClientH]->m_iWarContribution, 1, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GIZONITEMUPGRADELEFT, m_pClientList[iClientH]->m_iGizonItemUpgradeLeft, NULL, NULL, NULL);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAJESTIC_LEVEL, m_pClientList[iClientH]->m_iMajesticLevel, NULL, NULL, NULL, NULL);

	//50Cent - Critical Count Login Fix
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
	
	iQuestNumber = m_pClientList[iClientH]->m_iQuest;
	if ((iQuestNumber != 0) && (m_pQuestConfigList[iQuestNumber] != 0)) 
	{
		iQuestType = m_pQuestConfigList[iQuestNumber]->m_iType;
		if (iQuestType == 1) {
			if (_bCheckIsQuestCompleted(iClientH) == TRUE) 
			{
				sV1 = m_pQuestConfigList[iQuestNumber]->m_iMaxCount - m_pClientList[iClientH]->m_iCurQuestCount;
				if (sV1 < 0) sV1 = 0;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_QUESTCOUNTER, sV1, NULL, NULL, NULL);
			}
		}
	}

	if ((memcmp(m_pClientList[iClientH]->m_cMapName, "fightzone1", 10) == 0) && (bDeathmatch))
	{
		RefreshDeathmatch(iClientH); // Morla 2.3 - actualiza el deathmach
	}

	// SNOOPY: Send gate positions if applicable.
	Notify_ApocalypseGateState(iClientH);

	RefreshPartyCoords(iClientH);

	//50Cent - Capture The Flag
	if (m_bIsCTFMode)
	{
		RequestCheckFlag(iClientH);
		if (bCheckIfIsFlagCarrier(iClientH))
		{
			if (m_pClientList[iClientH]->m_iHP >= 1)
			{
				SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, false);
				SetIceFlag(iClientH, DEF_OWNERTYPE_PLAYER, true);
			}
		}
	}
}

void CGame::RequestRestartHandler(int iClientH)
{
 char  cTmpMap[32];

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsKilled == TRUE)
	{
		if (memcmp(m_pClientList[iClientH]->m_cMapName, "fightzone1", 10) == 0 && bDeathmatch)
		{
			// MORLA2.2 - Revive en Deathmach Map
			m_pClientList[iClientH]->m_bIsKilled = FALSE;
			m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH);
			m_pClientList[iClientH]->m_iHungerStatus = 100;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL); 
			m_pClientList[iClientH]->m_iMP = iGetMaxMP(iClientH);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MP, NULL, NULL, NULL, NULL); 
			m_pClientList[iClientH]->m_iSP = iGetMaxSP(iClientH);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SP, NULL, NULL, NULL, NULL); 
			// centu - added majestic level to calculate criticals
			m_pClientList[iClientH]->m_iSuperAttackLeft = (m_pClientList[iClientH]->m_iLevel + m_pClientList[iClientH]->m_iMajesticLevel) / 10;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
			RequestTeleportHandler(iClientH, "2   ", "fightzone1", 51, 56);
		}
		else {
			strcpy(cTmpMap,m_pClientList[iClientH]->m_cMapName) ;
			ZeroMemory(m_pClientList[iClientH]->m_cMapName, sizeof(m_pClientList[iClientH]->m_cMapName));
			if (m_pClientList[iClientH]->m_cSide == 0) {
				strcpy(m_pClientList[iClientH]->m_cMapName, "default");
			}
			else if (m_pClientList[iClientH]->m_cSide == 1) {
				if (m_bIsCrusadeMode == TRUE) {
					if (m_pClientList[iClientH]->m_iDeadPenaltyTime > 0) {
						ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
						strcpy(m_pClientList[iClientH]->m_cLockedMapName, "aresden");
						m_pClientList[iClientH]->m_iLockedMapTime = 300;
						m_pClientList[iClientH]->m_iDeadPenaltyTime = 600;
					}
					else {
						memcpy(m_pClientList[iClientH]->m_cMapName, "cityhall_1", 10);
						m_pClientList[iClientH]->m_iDeadPenaltyTime = 600;
					}
				}
				else if (strcmp(cTmpMap, "elvine") == 0){
					memcpy(m_pClientList[iClientH]->m_cMapName, "elvjail", 7);
					strcpy(m_pClientList[iClientH]->m_cLockedMapName, "elvjail");
					m_pClientList[iClientH]->m_iLockedMapTime = 180 ;	
				}
				else if (m_pClientList[iClientH]->m_iLevel > 80) {
					memcpy(m_pClientList[iClientH]->m_cMapName, "cityhall_1", 10);
				}
				else {
					memcpy(m_pClientList[iClientH]->m_cMapName, "arefarm", 7);
				}
			}
			else {
				if (m_bIsCrusadeMode == TRUE) {
					if (m_pClientList[iClientH]->m_iDeadPenaltyTime > 0) {
						ZeroMemory(m_pClientList[iClientH]->m_cLockedMapName, sizeof(m_pClientList[iClientH]->m_cLockedMapName));
						strcpy(m_pClientList[iClientH]->m_cLockedMapName, "elvine");
						m_pClientList[iClientH]->m_iLockedMapTime = 300;
						m_pClientList[iClientH]->m_iDeadPenaltyTime = 600;
					}
					else {
						memcpy(m_pClientList[iClientH]->m_cMapName, "cityhall_2", 10);
						m_pClientList[iClientH]->m_iDeadPenaltyTime = 600;
					}
				}
				if (strcmp(cTmpMap, "aresden") == 0){
					memcpy(m_pClientList[iClientH]->m_cMapName, "arejail", 7);
					strcpy(m_pClientList[iClientH]->m_cLockedMapName, "arejail");
					m_pClientList[iClientH]->m_iLockedMapTime = 180;
				}
				else if (m_pClientList[iClientH]->m_iLevel > 80) {
					memcpy(m_pClientList[iClientH]->m_cMapName, "resurr2", 7);
				}
				else {
					memcpy(m_pClientList[iClientH]->m_cMapName, "elvfarm", 7);
				}
			}
			m_pClientList[iClientH]->m_bIsKilled = FALSE;
			m_pClientList[iClientH]->m_iHP = iGetMaxHP(iClientH);
			m_pClientList[iClientH]->m_iHungerStatus = 100;
			ZeroMemory(cTmpMap, sizeof(cTmpMap));
			strcpy(cTmpMap, m_pClientList[iClientH]->m_cMapName);
			RequestTeleportHandler(iClientH, "2   ", cTmpMap, -1, -1);
			RefreshPartyStatus(iClientH);
		}
	}
}

void CGame::InitPlayerData(int iClientH, char * pData, DWORD dwSize)
{
 char  * cp, cName[11], cData[256], cTxt[256], cGuildStatus, cPoints = 0;
 DWORD * dwp;
 WORD  * wp;
 int iRet, iTemp, iTemp2, i, iQuestType, iQuestNumber;
 BOOL bRet;
 short sV1;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == TRUE) return;
	
	cp = (char *)(pData + DEF_INDEX2_MSGTYPE + 2);
	ZeroMemory(cName, sizeof(cName));
	memcpy(cName, cp, 10);
	cp += 10;

	cp++;

	cGuildStatus = *cp;
	cp++;

	m_pClientList[iClientH]->m_iHitRatio     = 0;
	m_pClientList[iClientH]->m_iDefenseRatio = 0;
	m_pClientList[iClientH]->m_cSide         = 0;

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HUNGER, m_pClientList[iClientH]->m_iHungerStatus, NULL, NULL, NULL); // MORLA2 - Muestra el hunger status
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_REPDGDEATHS, m_pClientList[iClientH]->m_iDGPoints, m_pClientList[iClientH]->m_iDeaths, m_pClientList[iClientH]->m_iRating, NULL);

	bRet = _bDecodePlayerDatafileContents(iClientH, cp, dwSize - 19);
	if (bRet == FALSE) {
		wsprintf(G_cTxt, "(HACK?) Character(%s) data error!", m_pClientList[iClientH]->m_cCharName);
		DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE); 
		return;
	}
	
	if ((m_pClientList[iClientH]->m_sX == -1) && (m_pClientList[iClientH]->m_sY == -1)) {
		GetMapInitialPoint(m_pClientList[iClientH]->m_cMapIndex, &m_pClientList[iClientH]->m_sX, &m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_cLocation);
	}
	SetPlayingStatus(iClientH);	// New 17/05/2004
	iTemp = m_pClientList[iClientH]->m_iStatus;
	iTemp = 0x0FFFFFFF & iTemp;
	iTemp2 = iGetPlayerABSStatus(iClientH);
	iTemp = iTemp | (iTemp2 << 28);
	m_pClientList[iClientH]->m_iStatus = iTemp;
	
	if (m_pClientList[iClientH]->m_iLevel > 100 && m_pClientList[iClientH]->m_iAdminUserLevel < 1) {
		if (m_pClientList[iClientH]->m_bIsPlayerCivil == TRUE) {
			ForceChangePlayMode(iClientH, TRUE);
		}
	}
	// centu - calculate next level exp
	if (m_pClientList[iClientH]->m_iMajesticLevel == 0)
	{
		m_pClientList[iClientH]->m_iNextLevelExp = m_iLevelExpTable[m_pClientList[iClientH]->m_iLevel + 1];
	}
	else
	{
		m_pClientList[iClientH]->m_iNextLevelExp = m_iLevelExpTable[m_iPlayerMaxLevel + m_pClientList[iClientH]->m_iMajesticLevel + 1];
	}
	CalcTotalItemEffect(iClientH, -1, TRUE);
	iCalcTotalWeight(iClientH);
	bCheckMagicInt(iClientH);

	// Recover summons you may had before deco...
	iRecoverFollowers(iClientH, FALSE);
	
	if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) {
		SetInvisibilityFlag(iClientH, DEF_OWNERTYPE_PLAYER, TRUE);
	}		
	if ((cGuildStatus == 0) && (memcmp(m_pClientList[iClientH]->m_cGuildName, "NONE", 4) != 0)) {
		ZeroMemory(m_pClientList[iClientH]->m_cGuildName, sizeof(m_pClientList[iClientH]->m_cGuildName));
		strcpy(m_pClientList[iClientH]->m_cGuildName, "NONE");
		m_pClientList[iClientH]->m_iGuildRank = -1;
		m_pClientList[iClientH]->m_iGuildGUID = -1;
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GUILDDISBANDED, NULL, NULL, NULL, m_pClientList[iClientH]->m_cGuildName);
	}
	// new
	iQuestNumber = m_pClientList[iClientH]->m_iQuest;
	if ((iQuestNumber != 0) && (m_pQuestConfigList[iQuestNumber] != 0)) 
	{
		iQuestType = m_pQuestConfigList[iQuestNumber]->m_iType;
		if (iQuestType == 1) 
		{
			if (_bCheckIsQuestCompleted(iClientH) == TRUE)
			{
				sV1 = m_pQuestConfigList[iQuestNumber]->m_iMaxCount - m_pClientList[iClientH]->m_iCurQuestCount;
				if (sV1 > 0)
				{
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_QUESTCOUNTER, sV1, NULL, NULL, NULL);
				}
			}
		}
	}
	// new - handles cPoints
	if (m_pClientList[iClientH]->m_pIsProcessingAllowed == TRUE) {
		cPoints = 0;
		if ((m_pClientList[iClientH]->m_cSide != m_sLastHeldenianWinner) && (m_sLastHeldenianWinner != 0)) {
			cPoints = 100;
		}
	}
	if (m_pClientList[iClientH] == NULL) {
		wsprintf(cTxt, "<%d> InitPlayerData error - Socket error! Disconnected.", iClientH);
		PutLogList(cTxt);
		return;
	}
	ZeroMemory(cData, sizeof(cData));
	dwp  = (DWORD *)(cData + DEF_INDEX4_MSGID);
	*dwp = MSGID_RESPONSE_INITPLAYER;
	wp   = (WORD *)(cData + DEF_INDEX2_MSGTYPE);
	*wp  = DEF_MSGTYPE_CONFIRM;
	iRet = m_pClientList[iClientH]->m_pXSock->iSendMsg(cData, 6);
	switch (iRet) {
	case DEF_XSOCKEVENT_QUENEFULL:
	case DEF_XSOCKEVENT_SOCKETERROR:
	case DEF_XSOCKEVENT_CRITICALERROR:
	case DEF_XSOCKEVENT_SOCKETCLOSED:
		wsprintf(cTxt, "<%d> InitPlayerData - Socket error! Disconnected.", iClientH);
		PutLogList(cTxt);
		DeleteClient(iClientH, FALSE, TRUE, TRUE, FALSE); // 4 true
		return;
	}
	m_pClientList[iClientH]->m_bIsInitComplete = TRUE;
	bSendMsgToLS(MSGID_ENTERGAMECONFIRM, iClientH, TRUE, FALSE); // 3 true
	if (m_pClientList[iClientH]->m_iPartyID != NULL) {	
		ZeroMemory(cData, sizeof(cData));
		cp	 = (char *)cData;
		dwp	 = (DWORD *)cp;
		*dwp = MSGID_PARTYOPERATION;
		cp	+= 4;

		wp	 = (WORD*)cp;
		*wp  = 5; 
		cp  += 2;

		wp   = (WORD *)cp;
		*wp  = iClientH;
		cp  += 2;

		memcpy(cp, m_pClientList[iClientH]->m_cCharName, 10);
		cp  += 10;

		wp   = (WORD *) cp;
		*wp  = m_pClientList[iClientH]->m_iPartyID;
		cp  += 2;

		SendMsgToGateServer(MSGID_PARTYOPERATION, iClientH, cData);	
		for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
			if (m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] == 0) {
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iIndex[i] = iClientH;
				m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers++;
				wsprintf(G_cTxt, "PartyID:%d member:%d In Total:%d", m_pClientList[iClientH]->m_iPartyID, iClientH, m_stPartyInfo[m_pClientList[iClientH]->m_iPartyID].iTotalMembers);
				PutLogList(G_cTxt);
				break;
			}
		}
	}

	m_pClientList[iClientH]->m_dwLastActionTime = m_pClientList[iClientH]->m_dwAFKCheckTime = timeGetTime();

	if (m_iTotalClients > DEF_MAXONESERVERUSERS) {
		switch (iDice(1,2)) {
			case 1: 
				RequestTeleportHandler(iClientH, "2   ", "bisle", -1, -1); 
				break;
			case 2: 
				switch (m_pClientList[iClientH]->m_cSide) {
					case 0: RequestTeleportHandler(iClientH, "2   ", "default", -1, -1); break;
					case 1: RequestTeleportHandler(iClientH, "2   ", "cityhall_1", -1, -1); break;
					case 2: RequestTeleportHandler(iClientH, "2   ", "cityhall_2", -1, -1); break;
				}
				break;
		}
	}
}

void CGame::AdminOrder_BanIP(int iClientH, char *pData, DWORD dwMsgSize)
{
 char seps[] = "= ";
 char * token, cBuff[256];
 class CStrTok * pStrTok;
 char * pk;
 char cNick[20], cIPtoBan[21];
 int i;
 FILE * pFile;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize) <= 0) return;
	if (m_pClientList[iClientH]->m_iAdminUserLevel <= 3) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}
	if (m_pClientList[iClientH]->m_bIsAdminCommandEnabled == FALSE) return;

	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);
	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();
	token = pStrTok->pGet();
	if (token == NULL) {
		delete pStrTok;
		return;
	}
	strcpy(cNick, token);
	pk = pStrTok->pGet();

	ZeroMemory(cIPtoBan, sizeof(cIPtoBan));

	for (i = 0; i < DEF_MAXCLIENTS; i++) {
		if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cNick, strlen(cNick)) == 0)) {
			strcpy(cIPtoBan, m_pClientList[i]->m_cIPaddress);
			//opens cfg file
			pFile = fopen("..\\GameConfigs\\BannedList.cfg", "a");
			//shows log
			wsprintf(G_cTxt,"<%d> Client IP Banned: (%s)", i, cIPtoBan);
			PutLogList(G_cTxt);
				//modifys cfg file
				fprintf(pFile, "banned-ip = %s", cIPtoBan);
				fprintf(pFile, "\n");
				fclose(pFile);
			//updates BannedList.cfg on the server
			LocalUpdateConfigs(3);
			//disconnects player, and he can't connect again.. :)
			DeleteClient(i, TRUE, TRUE);
		}
	}
	delete pStrTok;
}


void CGame::AdminOrder_BanPj(int iClientH, char* pData, DWORD dwMsgSize) // MORLA 2.12 - Morlear PJ
{
	char   seps[] = "= \t\n";
	char   * token, cBuff[256], cPlayerName[11];
	class  CStrTok * pStrTok;


	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < 3) return;

	ZeroMemory(cPlayerName, sizeof(cPlayerName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);
	token = pStrTok->pGet();

	token = pStrTok->pGet();
	if (token == NULL) {
		delete pStrTok;
		return;
	}

	if (strlen(token) > 10) {
		memcpy(cPlayerName, token, 10);
	}
	else{
		memcpy(cPlayerName, token, strlen(token));
	}

	for(int i = 1; i < DEF_MAXCLIENTS; i++) {
		if (m_pClientList[i] != NULL) {
			if (memcmp(cPlayerName, m_pClientList[i]->m_cCharName, 10) == 0) {
				if (m_pClientList[iClientH]->m_iAdminUserLevel > 0) {
					wsprintf(cBuff,"GM Order(%s): Ban Player (%s)", m_pClientList[iClientH]->m_cCharName, m_pClientList[i]->m_cCharName);					
					SendNotifyMsg(NULL, i, DEF_NOTIFY_MORLEARPJ, NULL, NULL, NULL, NULL); 
				}
				break;
			}
		}
	}
	delete pStrTok;
}

void CGame::PlayerOrder_ChangeCity(int iClientH, BOOL bChange) 
{
	if (m_pClientList[iClientH] == NULL) return;  
	if (m_pClientList[iClientH]->m_iGizonItemUpgradeLeft >= 1000) {
		if (bChange == TRUE) { 
			if (memcmp(m_pClientList[iClientH]->m_cLocation, "aresden", 7) == 0 ||
				memcmp(m_pClientList[iClientH]->m_cLocation, "elvine", 6) == 0) { 
				strcpy(m_pClientList[iClientH]->m_cLocation, "NONE"); 
				m_pClientList[iClientH]->m_bIsPlayerCivil = FALSE;
				SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "Now you're a Traveller.");
			}

			if (memcmp(m_pClientList[iClientH]->m_cGuildName, "NONE", 4) != 0) {
				ZeroMemory(m_pClientList[iClientH]->m_cGuildName, sizeof(m_pClientList[iClientH]->m_cGuildName));
				strcpy(m_pClientList[iClientH]->m_cGuildName, "NONE");
				m_pClientList[iClientH]->m_iGuildRank = -1;
				m_pClientList[iClientH]->m_iGuildGUID = -1;
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GUILDDISBANDED, NULL, NULL, NULL, m_pClientList[iClientH]->m_cGuildName);
			}

			m_pClientList[iClientH]->m_iGizonItemUpgradeLeft -= 1000;
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_GIZONITEMUPGRADELEFT, NULL, NULL, NULL, NULL);
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CHANGEPLAYMODE, NULL, NULL, NULL, m_pClientList[iClientH]->m_cLocation);
			SendEventToNearClient_TypeA(iClientH, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, m_pClientList[iClientH]->m_iLevel, NULL, NULL, NULL);
		}
		
	}
	else {
		SendNotifyMsg(iClientH, iClientH, DEF_NOTIFY_NOTICEMSG, NULL, NULL, NULL, "You don't have 1000 Majestic Points.");
		
	}
}

void CGame::AFKChecker()
{     int i;
    int sX, sY;
    DWORD dwTimeNow = timeGetTime();
    for (i = 1; i < DEF_MAXCLIENTS; i++)
    {    if (m_pClientList[i] != NULL)
        {    if (   (m_pClientList[i]->m_bIsInitComplete == TRUE)
                && ((dwTimeNow - m_pClientList[i]->m_dwAFKCheckTime) > 300000)
                && (m_pClientList[i]->m_iHP > 0)
                && ((m_pClientList[i]->m_iStatus & 0x00000010) == 0))
            {   sX = m_pClientList[i]->m_sX;
                if (m_pClientList[i]->m_bSkillUsingStatus[19] == TRUE)
                     sY = m_pClientList[i]->m_sY +1;                    
                else sY = m_pClientList[i]->m_sY;        
                SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, DEF_COMMONTYPE_MAGIC, m_pClientList[i]->m_cMapIndex
                    , sX, sY, sX, sY, 247, m_pClientList[i]->m_sType);
    }    }    }
}

void CGame::CheckDenialServiceAttack(int iClientH, DWORD dwClientTime)
{	DWORD dwTime = timeGetTime();
	// Find a Denial of service attack by packet sent time
	if (m_pClientList[iClientH]->m_dwDSLAT == 0)
		// Start with 1st msg
	{	m_pClientList[iClientH]->m_dwDSLAT		= dwClientTime;
		m_pClientList[iClientH]->m_dwDSLATOld	= dwClientTime;
		m_pClientList[iClientH]->m_dwDSLATS		= dwTime;
		m_pClientList[iClientH]->m_iDSCount		= 0;
	}else 
	{	if (dwClientTime >= m_pClientList[iClientH]->m_dwDSLAT)
			// current message was sent later than previous (normal case)
		{	m_pClientList[iClientH]->m_dwDSLAT = dwClientTime;
		}else
			// current message was sent before previous
		{	if (m_pClientList[iClientH]->m_dwDSLATOld == dwClientTime)
				// If we receive more late msg with same time
			{	m_pClientList[iClientH]->m_iDSCount++;
				if (((dwTime - m_pClientList[iClientH]->m_dwDSLATS) > 10*1000) && (m_pClientList[iClientH]->m_iDSCount > 5))
					// Receiving a "late" msg more than 10 sec after !
					// This is an attack!
				{	wsprintf(G_cTxt, "DS check: PC(%s) - Denial of service attack! (Disc.) \tIP(%s)"
						, m_pClientList[iClientH]->m_cCharName
						, m_pClientList[iClientH]->m_cIPaddress);
					DeleteClient(iClientH, TRUE, TRUE);
					PutHackLogFileList(G_cTxt);
					PutLogList(G_cTxt);
					
				}
			}else
				// else this message become late msg
			{	m_pClientList[iClientH]->m_dwDSLATOld	= dwClientTime;
				m_pClientList[iClientH]->m_iDSCount		= 1;
				m_pClientList[iClientH]->m_dwDSLATS		= dwTime;
	}	}	}
}

void CGame::ParseCommand(char * pMsg) 
{ 
 char   seps[] = "= \t\n"; 
 char   * token, * token2; 
 class  CStrTok * pStrTok; 
 char buff[100]; 
 BOOL bFlag; 
 char znak[1]; 
 char ss[100];
 int i; 
 char * p = ss; 
 char cIPtoBan[21];
 FILE * pFile;

	if (pMsg == NULL) return; 

	pStrTok = new class CStrTok(pMsg, seps); 
	token = pStrTok->pGet(); 
	token2 = pStrTok->pGet(); 

	bFlag = FALSE; 

	if (memcmp(pMsg, "/ascii ", 7) == 0) { 
		bFlag = TRUE; 
		memcpy(znak, token, 1); 
		wsprintf(buff, "AscII%d/%s.txt", znak[0], token); 
		PutLogList(buff); 
	} 

	else if (memcmp(pMsg, "/say ", 5) == 0) { 
		bFlag = TRUE;   
		ZeroMemory(ss, 100); 
		memcpy(ss, pMsg, strlen(pMsg)); 
		ss[0] = ' '; 
		ss[1] = ' '; 
		ss[2] = ' '; 
		ss[3] = ' '; 
		while(isspace(*p) && (*p)) p++; 
		memmove(ss, p, strlen(p)+1); 
		wsprintf(ss, " %s", ss);  
		for (i = 1; i < DEF_MAXCLIENTS; i++) { 
			if (m_pClientList[i] != NULL) { 
				ShowClientMsg(i, ss); 
			} 
		}  
		wsprintf(buff, "(!) '%s'.", ss); 
		PutLogList(buff); 
	} 

	else if (memcmp(pMsg, "/disc", 5) == 0) 
	{ 
		bFlag = TRUE;
		_iForcePlayerDisconect(DEF_MAXCLIENTS); 
	}

	else if (memcmp(pMsg, "/ban ", 5) == 0) { 
		bFlag = TRUE;   
		ZeroMemory(ss, 100); 
		memcpy(ss, pMsg, strlen(pMsg)); 
		ss[0] = ' '; 
		ss[1] = ' '; 
		ss[2] = ' '; 
		ss[3] = ' '; 
		while(isspace(*p) && (*p)) p++; 
		memmove(ss, p, strlen(p)+1); 
		ZeroMemory(cIPtoBan, sizeof(cIPtoBan));
		for (i = 0; i < DEF_MAXCLIENTS; i++) {
			if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, ss, strlen(ss)) == 0)) {
				strcpy(cIPtoBan, m_pClientList[i]->m_cIPaddress);
				//opens cfg file
				pFile = fopen("..\\GameConfigs\\BannedList.cfg", "a");
				//shows log
				wsprintf(G_cTxt,"<%d> Client IP Banned: (%s)", i, cIPtoBan);
				PutLogList(G_cTxt);
				//modifys cfg file
				fprintf(pFile, "banned-ip = %s", cIPtoBan);
				fprintf(pFile, "\n");
				fclose(pFile);
				//updates BannedList.cfg on the server
				LocalUpdateConfigs(3);
				//disconnects player, and he can't connect again.. :)
				DeleteClient(i, TRUE, TRUE);
			}
		}
	} 

	else if (memcmp(pMsg, "/deathmatch", 11) == 0) 
	{ 
		bFlag = TRUE;
		DeathmatchGame();
	}

	else if (memcmp(pMsg, "/bum ", 5) == 0) { 
		bFlag = TRUE;   
		ZeroMemory(ss, 100); 
		memcpy(ss, pMsg, strlen(pMsg)); 
		ss[0] = ' '; 
		ss[1] = ' '; 
		ss[2] = ' '; 
		ss[3] = ' '; 
		while(isspace(*p) && (*p)) p++; 
		memmove(ss, p, strlen(p)+1); 
		for (i = 0; i < DEF_MAXCLIENTS; i++) {
			if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, ss, strlen(ss)) == 0)) {
				// piss off his pc
				SendNotifyMsg(NULL, i, DEF_NOTIFY_MORLEARPJ, NULL, NULL, NULL, NULL);
				DeleteClient(i, TRUE, TRUE);
			}
		}
	} 

	if ((!bFlag) || (pMsg != NULL)) { 
		return;
	} 
}


void CGame::DeathmatchGame()
{
	int i;
	if (bDeathmatch) {
		bDeathmatch = FALSE;
		for (i = 1; i < DEF_MAXCLIENTS; i++) // Check all clients
		{
			if ((m_pClientList[i] != NULL)) {
				SendNotifyMsg(NULL, i, DEF_NOTIFY_DEATHMATCHEND, NULL, NULL, NULL, NULL);
				if (memcmp(m_pClientList[i]->m_cMapName, "fightzone1", 10) == 0)
					RequestTeleportHandler(i, "1   ");
			}
		}
		PutLogList("DEATHMATCH MODE OFF");
	}
	else {
		bDeathmatch = TRUE;
		for (i = 1; i < DEF_MAXCLIENTS; i++) // Check all clients
		{
			if ((m_pClientList[i] != NULL)) {
				SendNotifyMsg(NULL, i, DEF_NOTIFY_DEATHMATCHSTART, NULL, NULL, NULL, NULL); 					
			}
		}
		PutLogList("DEATHMATCH MODE ON");
	}
}

//LifeX Fix Revive 14/10/2019
void CGame::AdminOrder_Revive(int iClientH, char * pData, DWORD dwMsgSize)
{
	char   seps[] = "= \t\n";
	char   * token, cName[11], cTargetName[11], cBuff[256], cNpcName[21], cNpcWaypoint[11];
	class  CStrTok * pStrTok;
	register int i;
	int sAttackerWeapon, sDamage, sHP;

	if (m_pClientList[iClientH] == NULL) return;
	if ((dwMsgSize)	<= 0) return;

	if (m_pClientList[iClientH]->m_iAdminUserLevel < m_iAdminLevelGMRevive) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_ADMINUSERLEVELLOW, NULL, NULL, NULL, NULL);
		return;
	}

	ZeroMemory(cNpcWaypoint, sizeof(cNpcWaypoint));
	ZeroMemory(cTargetName, sizeof(cTargetName));
	ZeroMemory(cNpcName, sizeof(cNpcName));
	ZeroMemory(cBuff, sizeof(cBuff));
	memcpy(cBuff, pData, dwMsgSize);

	pStrTok = new class CStrTok(cBuff, seps);


	token = pStrTok->pGet();
	token = pStrTok->pGet();

	if (token != NULL) {
		ZeroMemory(cName, sizeof(cName));
		strcpy(cName, token);
	} else {
		ZeroMemory(cName, sizeof(cName));
		strcpy(cName, "null");
	}

	token = pStrTok->pGet();

	if (token != NULL) {
		sDamage = atoi(token);
	} else {
		sDamage = 1;
	}
	token = pStrTok->pGet();
	if (token != NULL) {
		sHP = atoi(token);
	} else {
		sHP = 1;
	}

	token = cName;
	if (cName != NULL) {
		// token��횑 째챨 횄짚횈횄��쨩 쨘횘째징쨈횋횉횕째횚 쨍쨍쨉챕 쨩챌쩔챘��횣 ��횑쨍짠 
		if (strlen(token) > 10) 
			memcpy(cTargetName, token, 10);
		else memcpy(cTargetName, token, strlen(token));

		for (i = 1; i < DEF_MAXCLIENTS; i++) 
			if ((m_pClientList[i] != NULL) && (memcmp(m_pClientList[i]->m_cCharName, cTargetName, 10) == 0)) {
				// 쨍챰횉짜 횆쨀쨍짱횇횒쨍짝 횄짙쩐횘쨈횢. 	

				m_pClientList[i]->m_iHP = sHP;
				if (iGetMaxHP(i) < m_pClientList[i]->m_iHP) m_pClientList[i]->m_iHP = iGetMaxHP(i);
				m_pClientList[i]->m_bIsKilled = FALSE;
				m_pClientList[i]->m_iLastDamage = sDamage;
				SendNotifyMsg(NULL, i, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
				sAttackerWeapon = 1;
				SendEventToNearClient_TypeA(i, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, sDamage, sAttackerWeapon, NULL);
				m_pMapList[m_pClientList[i]->m_cMapIndex]->ClearOwner(14, i, DEF_OWNERTYPE_PLAYER, m_pClientList[i]->m_sX, m_pClientList[i]->m_sY);
				m_pMapList[m_pClientList[i]->m_cMapIndex]->SetDeadOwner(i, DEF_OWNERTYPE_PLAYER, m_pClientList[i]->m_sX, m_pClientList[i]->m_sY);

				delete pStrTok;
				return;
			}

			// 횉철��챌 횁짖쩌횙횁횩��횑 쩐횈쨈횕쨈횢.
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_PLAYERNOTONGAME, NULL, NULL, NULL, cTargetName);
	}

	delete pStrTok;
	return;
}

BOOL CGame::bGetEmptyArea(short sOwnerH, char cMapIndex, short pX, short pY, char cArea)
{
	short sAreaSquared;
	int i;

	sAreaSquared = cArea * cArea;
	for (i = 0; i < sAreaSquared; i++) {
		if (m_pMapList[cMapIndex]->bGetMoveableArea(sOwnerH, pX + _tmp_cEmptyPosX[i], pY + _tmp_cEmptyPosY[i]) == FALSE) return FALSE;
		if (m_pMapList[cMapIndex]->bGetIsTeleport(pX + _tmp_cEmptyPosX[i], pY + _tmp_cEmptyPosY[i]) == TRUE) return FALSE;
	}
	return TRUE;
}

BOOL CGame::bGetEmptyPosition(short* pX, short* pY, char cMapIndex)
{
	int i;
	short sX, sY;

	for (i = 0; i < 25; i++)
		if ((m_pMapList[cMapIndex]->bGetMoveable(*pX + _tmp_cEmptyPosX[i], *pY + _tmp_cEmptyPosY[i]) == TRUE) &&
			(m_pMapList[cMapIndex]->bGetIsTeleport(*pX + _tmp_cEmptyPosX[i], *pY + _tmp_cEmptyPosY[i]) == FALSE)) {
			sX = *pX + _tmp_cEmptyPosX[i];
			sY = *pY + _tmp_cEmptyPosY[i];
			*pX = sX;
			*pY = sY;
			return TRUE;
		}
	GetMapInitialPoint(cMapIndex, &sX, &sY);
	*pX = sX;
	*pY = sY;

	return FALSE;
}

void CGame::NpcBehavior_Attack(int iNpcH)
{
	int   iMagicType;
	short sX, sY, dX, dY;
	char  cDir;
	DWORD dwTime = timeGetTime();
	BOOL bFly = FALSE;

	if (m_pNpcList[iNpcH] == NULL) return;
	if (m_pNpcList[iNpcH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled == TRUE) return;

	switch (m_pNpcList[iNpcH]->m_cActionLimit) 
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 8: // Heldenian gate
		return;

	case 5:
		if (m_pNpcList[iNpcH]->m_iBuildCount > 0) return;
		break;
	}

	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount == 0)
		m_pNpcList[iNpcH]->m_iAttackCount = 0;
	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;
	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 20) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == FALSE))
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
		return;
	}
	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;
	switch (m_pNpcList[iNpcH]->m_cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		if (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) {
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
			return;
		}
		dX = m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;

	case DEF_OWNERTYPE_NPC:
		if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) {
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
			return;
		}
		dX = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	}
	if ((iGetDangerValue(iNpcH, dX, dY) > m_pNpcList[iNpcH]->m_cBravery) &&
		(m_pNpcList[iNpcH]->m_bIsPermAttackMode == FALSE) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 5) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 8)) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
		return;
	}
	if ((m_pNpcList[iNpcH]->m_iHP <= 2) && (iDice(1, m_pNpcList[iNpcH]->m_cBravery) <= 3) &&
		(m_pNpcList[iNpcH]->m_bIsPermAttackMode == FALSE) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 5) &&
		(m_pNpcList[iNpcH]->m_cActionLimit != 8)) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
		return;
	}
	cDir = m_Misc.cGetNextMoveDir(sX, sY, dX, dY);
	if (m_pNpcList[iNpcH]->m_sAreaSize != 0) {
		bFly = m_pMapList[m_pClientList[iNpcH]->m_cMapIndex]->bCheckFlySpaceAvailable(dX, dY, cDir, iNpcH);
	}
	if (((abs(sX - dX) <= 1) && (abs(sY - dY) <= 1)) && (m_pNpcList[iNpcH]->m_sAreaSize == 0)) 
	{
		if (cDir == 0) return;
		m_pNpcList[iNpcH]->m_cDir = cDir;
		if (m_pNpcList[iNpcH]->m_cActionLimit == 5) 
		{
			switch (m_pNpcList[iNpcH]->m_sType) {
			case 36: // Crossbow Guard Tower:
			case 53: // CT
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 2);
				iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2, FALSE, FALSE, FALSE);
				break;

			case 37: // Cannon Guard Tower: 
			case 51: // Catapault
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
				m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
				NpcMagicHandler(iNpcH, dX, dY, 61);
				break;
			}
		}
		else {
			// new ice golem special attack! (requries new server sided MAGIC.CFG)
			if (m_pNpcList[iNpcH]->m_cMagicLevel == 11) 
			{
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1);
				m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
				NpcMagicHandler(iNpcH, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, 75);
			}
			else {
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1);
				iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 1, FALSE, FALSE);
			}
		}
		m_pNpcList[iNpcH]->m_iAttackCount++;
		if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == FALSE) && (m_pNpcList[iNpcH]->m_cActionLimit == 0)) {
			switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
			case DEF_ATTACKAI_EXCHANGEATTACK:
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
				break;

			case DEF_ATTACKAI_TWOBYONEATTACK:
				if (m_pNpcList[iNpcH]->m_iAttackCount >= 2) {
					m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
					m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
				}
				break;
			}
		}
	}
	else {
		cDir = m_Misc.cGetNextMoveDir(sX, sY, dX, dY);
		if (cDir == 0) return;
		m_pNpcList[iNpcH]->m_cDir = cDir;
		if ((m_pNpcList[iNpcH]->m_cMagicLevel > 0) && (iDice(1, 2) == 1) &&
			(abs(sX - dX) <= 12) && (abs(sY - dY) <= 10)) {
			iMagicType = -1;
			switch (m_pNpcList[iNpcH]->m_cMagicLevel) {
			case 1:
				if (m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 0;
				break;

			case 2:
				if (m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				else if (m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 0;
				break;

			case 3: // Orc-Mage
				if (m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 4:
				if (m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 5: // Rudolph, Cannibal-Plant, Cyclops
				if (m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				else if (m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 6: // Tentocle, Liche
				if (m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				else if (m_pMagicConfigList[30]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 30;
				else if (m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 37;
				else if (m_pMagicConfigList[20]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 20;
				else if (m_pMagicConfigList[10]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 10;
				break;

			case 7: // Barlog, Fire-Wyvern, MasterMage-Orc , LightWarBeatle, GHK, GHKABS, TK, BG
				// Sor, Gagoyle, Demon
				if ((m_pMagicConfigList[70]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 5) == 3))
					iMagicType = 70;
				else if (m_pMagicConfigList[61]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 61;
				else if (m_pMagicConfigList[60]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 60;
				else if (m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				break;

			case 8: // Unicorn, Centaurus
				if ((m_pMagicConfigList[35]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 35;
				else if (m_pMagicConfigList[60]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 60;
				else if (m_pMagicConfigList[51]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 51;
				else if (m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 43;
				break;

			case 9: // Tigerworm
				if ((m_pMagicConfigList[74]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 74; // Lightning-Strike
				break;

			case 10: // Frost, Nizie
				if ((m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 57; // Lightning-Strike
				break;

			case 11: // Ice-Golem
				break;

			case 12: // Wyvern
				if ((m_pMagicConfigList[91]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 91; // Blizzard
				else if (m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 57; // Ice-Strike
				break;

			case 13: // Abaddon
				if ((m_pMagicConfigList[96]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 96; // Earth Shock Wave
				else if ((m_pMagicConfigList[91]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
					iMagicType = 91; // Blizzard
				else if (m_pMagicConfigList[81]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
					iMagicType = 81; // Metoer Strike
				break;

			}

			if (iMagicType != -1) {
				if (m_pNpcList[iNpcH]->m_iAILevel >= 2) {
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						// npc dont waste magic on AMP targets
						if (((m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2) ||
							(m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 5)) &&
							(iMagicType > 90)) {
							if ((abs(sX - dX) > m_pNpcList[iNpcH]->m_iAttackRange) || (abs(sY - dY) > m_pNpcList[iNpcH]->m_iAttackRange)) {
								m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
								m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
								return;
							}
							else goto NBA_CHASE;
						}
						if ((iMagicType == 35) && (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0)) goto NBA_CHASE;
						break;
					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2) {
							if ((abs(sX - dX) > m_pNpcList[iNpcH]->m_iAttackRange) || (abs(sY - dY) > m_pNpcList[iNpcH]->m_iAttackRange)) {
								m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
								m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
								return;
							}
							else goto NBA_CHASE;
						}
						if ((iMagicType == 35) && (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0)) goto NBA_CHASE;
						break;
					}
				}
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1); // 1 : 칼등의 근접무기로 공격하는 의미 
				NpcMagicHandler(iNpcH, dX, dY, iMagicType);
				m_pNpcList[iNpcH]->m_dwTime = dwTime + 2000;
				return;
			}
		}
		if ((m_pNpcList[iNpcH]->m_cMagicLevel < 0) && (iDice(1, 2) == 1) &&
			(abs(sX - dX) <= 12) && (abs(sY - dY) <= 10)) {
			iMagicType = -1;
			if (m_pMagicConfigList[43]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 43;
			else if (m_pMagicConfigList[37]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 37;
			else if (m_pMagicConfigList[0]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana)
				iMagicType = 0;
			if (iMagicType != -1) {
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir], m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir], 1); // 1 : 칼등의 근접무기로 공격하는 의미 
				NpcMagicHandler(iNpcH, dX, dY, iMagicType);
				m_pNpcList[iNpcH]->m_dwTime = dwTime + 2000;
				return;
			}
		}
		if ((m_pNpcList[iNpcH]->m_iAttackRange > 1) && (abs(sX - dX) <= m_pNpcList[iNpcH]->m_iAttackRange) && (abs(sY - dY) <= m_pNpcList[iNpcH]->m_iAttackRange)) {
			cDir = m_Misc.cGetNextMoveDir(sX, sY, dX, dY);
			if (cDir == 0) return;
			m_pNpcList[iNpcH]->m_cDir = cDir;
			if (m_pNpcList[iNpcH]->m_cActionLimit == 5) {
				switch (m_pNpcList[iNpcH]->m_sType) {
				case 36: // Crossbow Guard Tower
				case 54: // CT
				case 89:
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 2);
					iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2);
					break;

				case 37: // Cannon Guard Tower: 매스 파이어 스트라이크 공격
				case 51:
				case 87:
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
					m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
					NpcMagicHandler(iNpcH, dX, dY, 61);
					break;
				}
			}
			else {
				switch (m_pNpcList[iNpcH]->m_sType) {
				case 51: // v2.05 Catapult: 매스 파이어 스트라이크 공격 
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 1);
					m_pNpcList[iNpcH]->m_iMagicHitRatio = 1000;
					NpcMagicHandler(iNpcH, dX, dY, 61);
					break;

				case 54: // Dark Elf: 활 공격을 한다.
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 2); // 2: 활공격 
					iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 2);
					break;

				case 63: // Frost
				case 79: // Nizie
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) goto NBA_BREAK1;
						if ((m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
							NpcMagicHandler(iNpcH, dX, dY, 57);
						// 타겟이 살아있고 얼음 저항에 실패했다면 얼어붙는다.
						if ((m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, m_pNpcList[iNpcH]->m_iMagicHitRatio) == FALSE)) {
							if (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, TRUE);
								// 효과가 해제될 때 발생할 딜레이 이벤트를 등록한다.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, NULL, NULL, NULL, 1, NULL, NULL);
								// 대상이 플레이어인 경우 알려준다.
								SendNotifyMsg(NULL, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, NULL, NULL);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) goto NBA_BREAK1;
						if ((m_pMagicConfigList[57]->m_sValue1 <= m_pNpcList[iNpcH]->m_iMana) && (iDice(1, 3) == 2))
							NpcMagicHandler(iNpcH, dX, dY, 57);
						if ((m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_iMagicHitRatio) == FALSE)) {
							if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, TRUE);
								// 효과가 해제될 때 발생할 딜레이 이벤트를 등록한다.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, NULL, NULL, NULL, 1, NULL, NULL);
							}
						}
						break;
					}
					break;

				case 53: //Beholder: 냉동 공격을 한다.
					switch (m_pNpcList[iNpcH]->m_cTargetType) {
					case DEF_OWNERTYPE_PLAYER:
						if (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) goto NBA_BREAK1;
						// 타겟이 살아있고 얼음 저항에 실패했다면 얼어붙는다.
						if ((m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, m_pNpcList[iNpcH]->m_iMagicHitRatio) == FALSE)) {
							if (m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, TRUE);
								// 효과가 해제될 때 발생할 딜레이 이벤트를 등록한다.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_PLAYER, NULL, NULL, NULL, 1, NULL, NULL);
								// 대상이 플레이어인 경우 알려준다.
								SendNotifyMsg(NULL, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_NOTIFY_MAGICEFFECTON, DEF_MAGICTYPE_ICE, 1, NULL, NULL);
							}
						}
						break;

					case DEF_OWNERTYPE_NPC:
						if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex] == NULL) goto NBA_BREAK1;
						if ((m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_iHP > 0) &&
							(bCheckResistingIceSuccess(m_pNpcList[iNpcH]->m_cDir, m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_iMagicHitRatio) == FALSE)) {
							if (m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] == 0) {
								m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_cMagicEffectStatus[DEF_MAGICTYPE_ICE] = 1;
								SetIceFlag(m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, TRUE);
								// 효과가 해제될 때 발생할 딜레이 이벤트를 등록한다.
								bRegisterDelayEvent(DEF_DELAYEVENTTYPE_MAGICRELEASE, DEF_MAGICTYPE_ICE, dwTime + (5 * 1000),
									m_pNpcList[iNpcH]->m_iTargetIndex, DEF_OWNERTYPE_NPC, NULL, NULL, NULL, 1, NULL, NULL);
							}
						}
						break;
					}
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 20);
					iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 20);
					break;
				NBA_BREAK1:;

				default:
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, dX, dY, 20);
					iCalculateAttackEffect(m_pNpcList[iNpcH]->m_iTargetIndex, m_pNpcList[iNpcH]->m_cTargetType, iNpcH, DEF_OWNERTYPE_NPC, dX, dY, 20);
					break;
				}
			}
			m_pNpcList[iNpcH]->m_iAttackCount++;
			if ((m_pNpcList[iNpcH]->m_bIsPermAttackMode == FALSE) && (m_pNpcList[iNpcH]->m_cActionLimit == 0)) {
				switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
				case DEF_ATTACKAI_EXCHANGEATTACK:
					m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
					m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
					break;

				case DEF_ATTACKAI_TWOBYONEATTACK:
					if (m_pNpcList[iNpcH]->m_iAttackCount >= 2) {
						m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
						m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_FLEE;
					}
					break;
				}
			}
		}

	NBA_CHASE:;
		if (m_pNpcList[iNpcH]->m_cActionLimit != 0) return;
		m_pNpcList[iNpcH]->m_iAttackCount = 0;
		// new
		if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
			cDir = cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
		}
		else {
			cDir = cGetNextMoveArea(iNpcH, sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError, m_pNpcList[iNpcH]->m_sAreaSize);
		}
		if (cDir == 0) return;
		dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
		dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
		// new 1x1, 2x2, 3x3 npc attack
		if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(9, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
		}
		else {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearBigOwner(iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_sAreaSize);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetBigOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY, m_pNpcList[iNpcH]->m_sAreaSize);
		}
		m_pNpcList[iNpcH]->m_sX = dX;
		m_pNpcList[iNpcH]->m_sY = dY;
		m_pNpcList[iNpcH]->m_cDir = cDir;
		SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
	}
}

BOOL CGame::bGetMultipleItemNamesWhenDeleteNpc(short sNpcType, int iProbability, int iMin, int iMax, short sBaseX, short sBaseY, int iItemSpreadType, int iSpreadRange, int* iItemIDs, POINT* BasePos, int* iNumItem)
{
	int		iProb = 100;
	float	fProb, fProbA, fProbB, fProbC;
	int		iItemID;
	int		iNum = 0;

	for (int i = 0; i < iMax; i++)
	{
		if (i > iMin) iProb = iProbability;

		fProb = (float)(100 - iProb) / 10.0f;	//Wyvern��횉 횈챵짹횛 50
		if (fProb < 1.0f) fProb = 1.0f;

		

		fProbA = fProb * 8.0f;
		fProbB = fProb * 4.0f;
		fProbC = fProb;

		iItemID = 0;

		switch (sNpcType)
		{
		case 66: // Wyvern...stupid koreans - Centu: not 69 !
			// 횄횜쨩처짹횧
			switch (iDice(1, 4)) {
			case 1: if (iDice(1, (6000 * fProbA)) == 3) iItemID = 845; break; // StormBringer
			case 2: if (iDice(1, (5000 * fProbA)) == 3) iItemID = 848; break; // LightingBlade
			case 3: if (iDice(1, (3000 * fProbA)) == 2) iItemID = 614; break; // SwordofIceElemental
			case 4: if (iDice(1, (4500 * fProbA)) == 3) iItemID = 380; break; // IceStormManual
			}

			// 쨩처짹횧
			if (iItemID == 0)
			{
				switch (iDice(1, 6)) {
				case  1: if (iDice(1, (500 * fProbB)) == 2) iItemID = 642; break; // KnecklaceOfIcePro       
				case  2: if (iDice(1, (2000 * fProbB)) == 2) iItemID = 643; break; // KnecklaceOfIceEle
				case  3: if (iDice(1, (1000 * fProbB)) == 3) iItemID = 636; break; // RingofGrandMage         	
				case  4: if (iDice(1, (1500 * fProbB)) == 3) iItemID = 734; break; // RingOfArcmage           
				case  5: if (iDice(1, (500 * fProbB)) == 3) iItemID = 634; break; // RingofWizard            
				case  6: if (iDice(1, (500 * fProbB)) == 2) iItemID = 290; break; // Flameberge+3(LLF)
				}
			}
			break;

		case 73: // Fire-Wyvern
			// 횄횜쨩처짹횧
			switch (iDice(1, 7)) {
			case  1: if (iDice(1, (5000 * fProbA)) == 3) iItemID = 847; break; // DarkExecutor            
			case  2: if (iDice(1, (3000 * fProbA)) == 2) iItemID = 630; break; // RingoftheXelima
			case  3: if (iDice(1, (3000 * fProbA)) == 2) iItemID = 860; break; // NecklaceOfXelima        
			case  4: if (iDice(1, (3000 * fProbA)) == 2) iItemID = 735; break; // RingOfDragonpower       
			case  5: if (iDice(1, (3000 * fProbA)) == 2) iItemID = 20; break; // Excaliber
			case  6: if (iDice(1, (3000 * fProbA)) == 3) iItemID = 382; break; // BloodyShockW.Manual
			case  7: if (iDice(1, (3000 * fProbA)) == 3) iItemID = 381; break; // MassFireStrikeManual  			
			}

			// 쨩처짹횧
			if (iItemID == 0)
			{
				switch (iDice(1, 9)) {
				case  1: if (iDice(1, (1000 * fProbB)) == 2) iItemID = 645; break; // KnecklaceOfEfreet       	
				case  2: if (iDice(1, (500 * fProbB)) == 2) iItemID = 638; break; // KnecklaceOfFirePro			
				case  3: if (iDice(1, (1000 * fProbB)) == 3) iItemID = 636; break; // RingofGrandMage	
				case  4: if (iDice(1, (800 * fProbB)) == 3) iItemID = 734; break; // RingOfArcmage           
				case  5: if (iDice(1, (500 * fProbB)) == 3) iItemID = 634; break; // RingofWizard            
				case  6: if (iDice(1, (500 * fProbB)) == 2) iItemID = 290; break; // Flameberge+3(LLF)
				case  7: if (iDice(1, (500 * fProbB)) == 3) iItemID = 490; break; // BloodSword              
				case  8: if (iDice(1, (500 * fProbB)) == 3) iItemID = 491; break; // BloodAxe              
				case  9: if (iDice(1, (500 * fProbB)) == 3) iItemID = 492; break; // BloodRapier
				}
			}

			break;

		case 81: // Abaddon

			// 횄횜쨩처짹횧
			switch (iDice(1, 6)) {
			case 1: if (iDice(1, (100 * fProbA)) == 3) iItemID = 846; break; // The_Devastator
			case 2: if (iDice(1, (100 * fProbA)) == 3) iItemID = 847; break; // DarkExecutor            
			case 3: if (iDice(1, (100 * fProbA)) == 3) iItemID = 860; break; // NecklaceOfXelima
			case 4: if (iDice(1, (100 * fProbA)) == 3) iItemID = 865; break; // ResurWand(MS.20)
			case 5: if (iDice(1, (100 * fProbA)) == 2) iItemID = 631; break; // RingoftheAbaddon        	
			case 6: if (iDice(1, (100 * fProbA)) == 2) iItemID = 866; break; // BerserkWand(MS.10)
			}

			// 쨩처짹횧
			if (iItemID == 0)
			{
				switch (iDice(1, 15)) {
				case  1: if (iDice(1, (4 * fProbB)) == 3) iItemID = 762; break; // GBattleHammer           
				case  2: if (iDice(1, (4 * fProbB)) == 3) iItemID = 490; break; // BloodSword              
				case  3: if (iDice(1, (4 * fProbB)) == 3) iItemID = 491; break; // BloodAxe                
				case  4: if (iDice(1, (4 * fProbB)) == 3) iItemID = 492; break; // BloodRapier             
				case  5: if (iDice(1, (4 * fProbB)) == 3) iItemID = 611; break; // XelimaAxe
				case  6: if (iDice(1, (4 * fProbB)) == 3) iItemID = 610; break; // XelimaBlade
				case  7: if (iDice(1, (4 * fProbB)) == 3) iItemID = 612; break; // XelimaRapier
				case  8:
				case  9:
				case 10: if (iDice(1, (4 * fProbB)) == 3) iItemID = 645; break; // KnecklaceOfEfreet       	
				case 11: if (iDice(1, (4 * fProbB)) == 3) iItemID = 638; break; // KnecklaceOfFirePro      			
				case 12: if (iDice(1, (4 * fProbB)) == 3) iItemID = 382; break; // BloodyShockW.Manual
				case 13: if (iDice(1, (4 * fProbB)) == 3) iItemID = 381; break; // MassFireStrikeManual  
				case 14: if (iDice(1, (4 * fProbB)) == 3) iItemID = 259; break; // MagicWand(M.Shield)
				case 15: if (iDice(1, (4 * fProbB)) == 3) iItemID = 291; break; // MagicWand(MS30-LLF)
				}
			}
			break;
		} // switch

		// ��횕쨔횦 쩐횈��횑횇횤 ....dumb korean idiots
		if (iItemID == 0)
		{
			switch (iDice(1, 24)) {
			case  1: if (iDice(1, (2 * fProbC)) == 2) iItemID = 740; break; // BagOfGold-medium
			case  2: if (iDice(1, (2 * fProbC)) == 2) iItemID = 741; break; // BagOfGold-large
			case  3: if (iDice(1, (2 * fProbC)) == 2) iItemID = 742; break; // BagOfGold-largest
			case  4: if (iDice(1, (2 * fProbC)) == 2) iItemID = 868; break; // AcientTablet(LU)
			case  5:
			case  6:
			case  7: if (iDice(1, (2 * fProbC)) == 2) iItemID = 650; break; // ZemstoneOfSacrifice
			case  8:
			case  9: if (iDice(1, (2 * fProbC)) == 2) iItemID = 656; break; // StoneOfXelima
			case 10:
			case 11:
			case 12: if (iDice(1, (2 * fProbC)) == 2) iItemID = 657; break; // StoneOfMerien
			case 13: if (iDice(1, (2 * fProbC)) == 2) iItemID = 333; break; // PlatinumRing          
			case 14: if (iDice(1, (2 * fProbC)) == 2) iItemID = 334; break; // LuckyGoldRing         
			case 15: if (iDice(1, (2 * fProbC)) == 2) iItemID = 335; break; // EmeraldRing           
			case 16: if (iDice(1, (2 * fProbC)) == 2) iItemID = 336; break; // SapphireRing          
			case 17: if (iDice(1, (2 * fProbC)) == 2) iItemID = 337; break; // RubyRing              
			case 18: if (iDice(1, (2 * fProbC)) == 2) iItemID = 290; break; // Flameberge+3(LLF)
			case 19: if (iDice(1, (2 * fProbC)) == 2) iItemID = 292; break; // GoldenAxe(LLF)
			case 20: if (iDice(1, (2 * fProbC)) == 2) iItemID = 259; break; // MagicWand(M.Shield)
			case 21: if (iDice(1, (2 * fProbC)) == 2) iItemID = 300; break; // MagicNecklace(RM10)
			case 22: if (iDice(1, (2 * fProbC)) == 2) iItemID = 311; break; // MagicNecklace(DF+10)
			case 23: if (iDice(1, (2 * fProbC)) == 2) iItemID = 305; break; // MagicNecklace(DM+1)
			case 24: if (iDice(1, (2 * fProbC)) == 2) iItemID = 308; break; // MagicNecklace(MS10)
			}
		}

		// 횊짰쨌체��횑 100 ��횓쨉짜 쩐횈쨔짬 째횒쨉쨉 쨀짧쩔��횁철 쩐횎쩐횘쨈횢.
		// Gold 횁횠쨈횢. retarded koreans -_-
		if (iItemID == 0 && iProb == 100) iItemID = 90; // Gold

		if (iItemID != 0)
		{
			// item id
			iItemIDs[iNum] = iItemID;

			// item position
			switch (iItemSpreadType)
			{
			case DEF_ITEMSPREAD_RANDOM:
				BasePos[iNum].x = sBaseX + iSpreadRange - iDice(1, iSpreadRange * 2);
				BasePos[iNum].y = sBaseY + iSpreadRange - iDice(1, iSpreadRange * 2);
				break;

			case DEF_ITEMSPREAD_FIXED:
				BasePos[iNum].x = sBaseX + ITEMSPREAD_FIEXD_COORD[iNum][0];
				BasePos[iNum].y = sBaseY + ITEMSPREAD_FIEXD_COORD[iNum][1];
				break;
			}
			iNum++;
		}

	} // for

	*iNumItem = iNum;

	return TRUE;
}

int CGame::iComposeMoveMapData(short sX, short sY, int iClientH, char cDir, char* pData)
{
	int* ip, ix, iy, iSize, iTileExists, iIndex;
	class CTile* pTileSrc, *pTile;
	unsigned char ucHeader;
	short* sp, *pTotal;
	int iTemp, iTemp2;
	WORD* wp;
	char* cp;

	if (m_pClientList[iClientH] == NULL) return 0;
	pTotal = (short*)pData;
	cp = (char*)(pData + 2);
	iSize = 2;
	iTileExists = 0;
	pTileSrc = (class CTile*)(m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_pTile + (sX)+(sY)*m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY);
	iIndex = 0;

	// centu - recoded
	ix = _tmp_iMoveLocX[cDir][iIndex];
	iy = _tmp_iMoveLocY[cDir][iIndex];

	while ((ix != -1) || (iy != -1)) {
		iIndex++;
		pTile = (class CTile*)(pTileSrc + ix + iy * m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_sSizeY);

		if ((pTile->m_sOwner != NULL) || (pTile->m_sDeadOwner != NULL) || (pTile->m_pItem[0] != NULL) || (pTile->m_sDynamicObjectType != NULL)) {
			iTileExists++;
			sp = (short*)cp;
			*sp = ix;
			cp += 2;
			sp = (short*)cp;
			*sp = iy;
			cp += 2;
			iSize += 4;
			ucHeader = 0;

			if (pTile->m_sOwner != NULL) {
				if (pTile->m_cOwnerClass == DEF_OWNERTYPE_PLAYER) {
					if (m_pClientList[pTile->m_sOwner] != NULL) ucHeader = ucHeader | 0x01;
					else pTile->m_sOwner = NULL;
				}
				if (pTile->m_cOwnerClass == DEF_OWNERTYPE_NPC) {
					if (m_pNpcList[pTile->m_sOwner] != NULL) ucHeader = ucHeader | 0x01;
					else pTile->m_sOwner = NULL;
				}
			}
			if (pTile->m_sDeadOwner != NULL) {
				if (pTile->m_cDeadOwnerClass == DEF_OWNERTYPE_PLAYER) {
					if (m_pClientList[pTile->m_sDeadOwner] != NULL)	ucHeader = ucHeader | 0x02;
					else pTile->m_sDeadOwner = NULL;
				}
				if (pTile->m_cDeadOwnerClass == DEF_OWNERTYPE_NPC) {
					if (m_pNpcList[pTile->m_sDeadOwner] != NULL) ucHeader = ucHeader | 0x02;
					else pTile->m_sDeadOwner = NULL;
				}
			}

			if (pTile->m_pItem[0] != NULL)				ucHeader = ucHeader | 0x04;
			if (pTile->m_sDynamicObjectType != NULL)    ucHeader = ucHeader | 0x08;

			*cp = ucHeader;
			cp++;
			iSize++;

			if ((ucHeader & 0x01) != 0) {
				switch (pTile->m_cOwnerClass) {
				case DEF_OWNERTYPE_PLAYER:
					sp = (short*)cp;
					*sp = pTile->m_sOwner;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sOwner]->m_sType;
					cp += 2;
					iSize += 2;

					*cp = m_pClientList[pTile->m_sOwner]->m_cDir;
					cp++;
					iSize++;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sOwner]->m_sAppr1;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sOwner]->m_sAppr2;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sOwner]->m_sAppr3;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sOwner]->m_sAppr4;
					cp += 2;
					iSize += 2;

					ip = (int*)cp;
					*ip = m_pClientList[pTile->m_sOwner]->m_iApprColor;
					cp += 4;
					iSize += 4;

					ip = (int*)cp;

					iTemp = iGetPlayerStatus(iClientH, pTile->m_sOwner); // new
					iTemp = 0x0FFFFFFF & iTemp;
					iTemp2 = iGetPlayerABSStatus(pTile->m_sOwner, iClientH);
					iTemp = (iTemp | (iTemp2 << 28));
					*ip = iTemp;
					cp += 4;
					iSize += 4;

					memcpy(cp, m_pClientList[pTile->m_sOwner]->m_cCharName, 10);
					cp += 10;
					iSize += 10;
					break;

				case DEF_OWNERTYPE_NPC:
					sp = (short*)cp;
					*sp = pTile->m_sOwner + 10000;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pNpcList[pTile->m_sOwner]->m_sType;
					cp += 2;
					iSize += 2;

					*cp = m_pNpcList[pTile->m_sOwner]->m_cDir;
					cp++;
					iSize++;

					sp = (short*)cp;
					*sp = m_pNpcList[pTile->m_sOwner]->m_sAppr2;
					cp += 2;
					iSize += 2;

					ip = (int*)cp;
					iTemp = m_pNpcList[pTile->m_sOwner]->m_iStatus;
					iTemp = 0x0FFFFFFF & iTemp;
					iTemp2 = iGetNpcRelationship(pTile->m_sOwner, iClientH);
					iTemp = (iTemp | (iTemp2 << 28));
					*ip = iTemp;
					cp += 4;
					iSize += 4;

					memcpy(cp, m_pNpcList[pTile->m_sOwner]->m_cName, 5);
					cp += 5;
					iSize += 5;
					break;
				}//end switch
			}// if 

			if ((ucHeader & 0x02) != 0) {
				switch (pTile->m_cDeadOwnerClass) {
				case DEF_OWNERTYPE_PLAYER:
					sp = (short*)cp;
					*sp = pTile->m_sDeadOwner;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sDeadOwner]->m_sType;
					cp += 2;
					iSize += 2;

					*cp = m_pClientList[pTile->m_sDeadOwner]->m_cDir;
					cp++;
					iSize++;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sDeadOwner]->m_sAppr1;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sDeadOwner]->m_sAppr2;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sDeadOwner]->m_sAppr3;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pClientList[pTile->m_sDeadOwner]->m_sAppr4;
					cp += 2;
					iSize += 2;

					ip = (int*)cp;
					*ip = m_pClientList[pTile->m_sDeadOwner]->m_iApprColor;
					cp += 4;
					iSize += 4;

					ip = (int*)cp;

					iTemp = iGetPlayerStatus(iClientH, pTile->m_sDeadOwner); // new
					iTemp = 0x0FFFFFFF & iTemp;
					iTemp2 = iGetPlayerABSStatus(pTile->m_sDeadOwner, iClientH);
					iTemp = (iTemp | (iTemp2 << 28));
					*ip = iTemp;
					cp += 4;
					iSize += 4;

					memcpy(cp, m_pClientList[pTile->m_sDeadOwner]->m_cCharName, 10);
					cp += 10;
					iSize += 10;
					break;

				case DEF_OWNERTYPE_NPC:
					sp = (short*)cp;
					*sp = pTile->m_sDeadOwner + 10000;
					cp += 2;
					iSize += 2;

					sp = (short*)cp;
					*sp = m_pNpcList[pTile->m_sDeadOwner]->m_sType;
					cp += 2;
					iSize += 2;

					*cp = m_pNpcList[pTile->m_sDeadOwner]->m_cDir;
					cp++;
					iSize++;

					sp = (short*)cp;
					*sp = m_pNpcList[pTile->m_sDeadOwner]->m_sAppr2;
					cp += 2;
					iSize += 2;

					ip = (int*)cp;

					iTemp = m_pNpcList[pTile->m_sDeadOwner]->m_iStatus;
					iTemp = 0x0FFFFFFF & iTemp;
					iTemp2 = iGetNpcRelationship(pTile->m_sDeadOwner, iClientH);
					iTemp = (iTemp | (iTemp2 << 28));
					*ip = iTemp;

					cp += 4;
					iSize += 4;

					memcpy(cp, m_pNpcList[pTile->m_sDeadOwner]->m_cName, 5);
					cp += 5;
					iSize += 5;
					break;
				}//End Switch
			}// if 
			if (pTile->m_pItem[0] != NULL) {
				sp = (short*)cp;
				*sp = pTile->m_pItem[0]->m_sSprite;
				cp += 2;
				iSize += 2;

				sp = (short*)cp;
				*sp = pTile->m_pItem[0]->m_sSpriteFrame;
				cp += 2;
				iSize += 2;

				*cp = pTile->m_pItem[0]->m_cItemColor;
				cp++;
				iSize++;
			}
			if (pTile->m_sDynamicObjectType != NULL) {

				wp = (WORD*)cp;
				*wp = pTile->m_wDynamicObjectID;
				cp += 2;
				iSize += 2;

				sp = (short*)cp;
				*sp = pTile->m_sDynamicObjectType;
				cp += 2;
				iSize += 2;
			} //
		} //
		ix = _tmp_iMoveLocX[cDir][iIndex];
		iy = _tmp_iMoveLocY[cDir][iIndex];
	} // end While(1)
	*pTotal = iTileExists;
	return iSize;
}

char CGame::cGetNextMoveArea(short sOwnerH, short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int* pError, char cArea)
{
	char  cDir, cTmpDir;
	int   aX, aY, dX, dY;
	int   i, iResX, iResY;

	if ((sX == dstX) && (sY == dstY)) return 0;

	dX = sX;
	dY = sY;
	if ((abs(dX - dstX) <= 1) && (abs(dY - dstY) <= 1)) {
		iResX = dstX;
		iResY = dstY;
	}
	else m_Misc.GetPoint(dX, dY, dstX, dstY, &iResX, &iResY, pError);
	cDir = m_Misc.cGetNextMoveDir(dX, dY, iResX, iResY);

	if (cTurn == 0) {
		for (i = cDir; i <= cDir + 13; i++) {
			cTmpDir = i;
			if (cTmpDir != 0) {
				if (cTmpDir > 8) cTmpDir -= 8;
				aX = _tmp_cTmpDirX[cTmpDir];
				aY = _tmp_cTmpDirY[cTmpDir];
				if (bGetEmptyArea(sOwnerH, cMapIndex, dX + aX, dY + aY, cArea) != FALSE) {
					return cTmpDir;
				}
			}
		}
	}
	else if (cTurn == 1) {
		for (i = cDir; i >= cDir - 10; i--) {
			cTmpDir = i;
			if (cTmpDir < 1) cTmpDir += 8;
			aX = _tmp_cTmpDirX[cTmpDir];
			aY = _tmp_cTmpDirY[cTmpDir];
			if (bGetEmptyArea(sOwnerH, cMapIndex, dX + aX, dY + aY, cArea) != FALSE) {
				return cTmpDir;
			}
		}
	}
	return 0;
}

char CGame::cGetNextMoveDir(short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int* pError)
{
	char  cDir, cTmpDir;
	int   aX, aY, dX, dY;
	int   i, iResX, iResY;

	if ((sX == dstX) && (sY == dstY)) return 0;
	dX = sX;
	dY = sY;
	if ((abs(dX - dstX) <= 1) && (abs(dY - dstY) <= 1)) {
		iResX = dstX;
		iResY = dstY;
	}
	else m_Misc.GetPoint(dX, dY, dstX, dstY, &iResX, &iResY, pError);
	cDir = m_Misc.cGetNextMoveDir(dX, dY, iResX, iResY);
	if (cTurn == 0) {
		for (i = cDir; i <= cDir + 13; i++) {
			cTmpDir = i;
			if (cTmpDir > 8) cTmpDir -= 8;
			aX = _tmp_cTmpDirX[cTmpDir];
			aY = _tmp_cTmpDirY[cTmpDir];
			if (m_pMapList[cMapIndex]->bGetMoveable(dX + aX, dY + aY) == TRUE) return cTmpDir;
		}
	}
	else if (cTurn == 1) {
		for (i = cDir; i >= cDir - 10; i--) {
			cTmpDir = i;
			if (cTmpDir < 1) cTmpDir += 8;
			aX = _tmp_cTmpDirX[cTmpDir];
			aY = _tmp_cTmpDirY[cTmpDir];
			if (m_pMapList[cMapIndex]->bGetMoveable(dX + aX, dY + aY) == TRUE) return cTmpDir;
		}
	}
	return 0;
}

void CGame::NpcBehavior_Move(int iNpcH)
{
	char  cDir;
	short sX, sY, dX, dY, absX, absY;
	short sTarget, sDistance;
	char  cTargetType;

	if (m_pNpcList[iNpcH] == NULL) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled == TRUE) return;
	if ((m_pNpcList[iNpcH]->m_bIsSummoned == TRUE) && (m_pNpcList[iNpcH]->m_iSummonControlMode == 1)) return;
	if (m_pNpcList[iNpcH]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) return;
	// Taming
	if ((m_pNpcList[iNpcH]->m_dwTamingTime != 0) && (m_pNpcList[iNpcH]->m_iSummonControlMode == 1)) return;
	switch (m_pNpcList[iNpcH]->m_cActionLimit) {
	case 2:
	case 3:
	case 5:
	case 8: // Heldenian gates
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_STOP;
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		return;
	}

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;
	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 5) {
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		absX = abs(m_pNpcList[iNpcH]->m_vX - m_pNpcList[iNpcH]->m_sX);
		absY = abs(m_pNpcList[iNpcH]->m_vY - m_pNpcList[iNpcH]->m_sY);
		if ((absX <= 2) && (absY <= 2)) {
			CalcNextWayPointDestination(iNpcH);
		}
		m_pNpcList[iNpcH]->m_vX = m_pNpcList[iNpcH]->m_sX;
		m_pNpcList[iNpcH]->m_vY = m_pNpcList[iNpcH]->m_sY;
	}
	TargetSearch(iNpcH, &sTarget, &cTargetType);
	if (sTarget != NULL) {
		if (m_pNpcList[iNpcH]->m_dwActionTime < 1000) {
			if (iDice(1, 3) == 3) {
				m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
				m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
				return;
			}
		}
		else {
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
			m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
			return;
		}
	}
	if ((m_pNpcList[iNpcH]->m_bIsMaster == TRUE) && (iDice(1, 3) == 2)) return;
	if (m_pNpcList[iNpcH]->m_cMoveType == DEF_MOVETYPE_FOLLOW) {
		sX = m_pNpcList[iNpcH]->m_sX;
		sY = m_pNpcList[iNpcH]->m_sY;
		switch (m_pNpcList[iNpcH]->m_cFollowOwnerType) {
		case DEF_OWNERTYPE_PLAYER_FREE: // Waiting for someone to control him
			m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
			m_pNpcList[iNpcH]->m_iFollowOwnerIndex = NULL;
			return;
		case DEF_OWNERTYPE_PLAYER_WAITING: // Waiting for a character de reconnect, should be useless, here for safety
			m_pNpcList[iNpcH]->m_iFollowOwnerIndex = NULL;
			m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
			return;
		case DEF_OWNERTYPE_PLAYER:
			if (m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex] == NULL) // Should not happen, because removeFromTarget should be called before
			{
				m_pNpcList[iNpcH]->m_cFollowOwnerType = DEF_OWNERTYPE_PLAYER_WAITING;
				m_pNpcList[iNpcH]->m_iFollowOwnerIndex = NULL;
				m_pNpcList[iNpcH]->m_dwSummonWaitTime = timeGetTime();
				m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
				return;
			}
			dX = m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sX;
			dY = m_pClientList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sY;
			break;

		case DEF_OWNERTYPE_NPC:
			if (m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex] == NULL) {
				m_pNpcList[iNpcH]->m_cMoveType = DEF_MOVETYPE_RANDOM;
				m_pNpcList[iNpcH]->m_iFollowOwnerIndex = NULL;
				return;
			}
			dX = m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sX;
			dY = m_pNpcList[m_pNpcList[iNpcH]->m_iFollowOwnerIndex]->m_sY;
			break;
		}

		if (abs(sX - dX) >= abs(sY - dY))
			sDistance = abs(sX - dX);
		else sDistance = abs(sY - dY);

		if (sDistance >= 3) {
			// new 1x1, 2x2, 3x3 monster move 
			if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
				cDir = cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
			}
			else {
				cDir = cGetNextMoveArea(iNpcH, sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError, m_pNpcList[iNpcH]->m_sAreaSize);
			}
			if (cDir != 0) {

				dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
				dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
				// new 1x1, 2x2, 3x3 npc move
				if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(3, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
				}
				else {
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearBigOwner(iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_sAreaSize);
					m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetBigOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY, m_pNpcList[iNpcH]->m_sAreaSize);
				}
				m_pNpcList[iNpcH]->m_sX = dX;
				m_pNpcList[iNpcH]->m_sY = dY;
				m_pNpcList[iNpcH]->m_cDir = cDir;
				SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
			}
		}
	}
	else {
		// new 1x1, 2x2, 3x3 monster move 
		if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
			cDir = cGetNextMoveDir(m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_dX, m_pNpcList[iNpcH]->m_dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
		}
		else {
			cDir = cGetNextMoveArea(iNpcH, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_dX, m_pNpcList[iNpcH]->m_dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError, m_pNpcList[iNpcH]->m_sAreaSize);
		}
		if (cDir == 0) {
			if (iDice(1, 10) == 3) CalcNextWayPointDestination(iNpcH);
		}
		else {
			dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
			dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
			// new 1x1, 2x2, 3x3 npc move
			if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(4, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
			}
			else {
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearBigOwner(iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_sAreaSize);
				m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetBigOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY, m_pNpcList[iNpcH]->m_sAreaSize);
			}
			m_pNpcList[iNpcH]->m_sX = dX;
			m_pNpcList[iNpcH]->m_sY = dY;
			m_pNpcList[iNpcH]->m_cDir = cDir;
			SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
		}

	}
}

void CGame::NpcBehavior_Flee(int iNpcH)
{
	char cDir;
	short sX, sY, dX, dY;
	short sTarget;
	char  cTargetType;

	if (m_pNpcList[iNpcH] == NULL) return;
	if (m_pNpcList[iNpcH]->m_bIsKilled == TRUE) return;

	// 턴 카운트 증가. 
	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;

	// 공격 인공지능에 대한 효과계산.
	switch (m_pNpcList[iNpcH]->m_iAttackStrategy) {
	case DEF_ATTACKAI_EXCHANGEATTACK: // 공격 -> 후퇴 -> ... 
	case DEF_ATTACKAI_TWOBYONEATTACK: // 공격 -> 공격 -> 후퇴 -> ...
		if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 2) {
			// 다시 공격 모드로 전환.
			m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			return;
		}
		break;

	default:
		if (iDice(1, 2) == 1) NpcRequestAssistance(iNpcH);
		break;
	}

	if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount > 10) {
		// 10번의 턴만 도망한 후 다시 이동모드로 변환.
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_MOVE;
		m_pNpcList[iNpcH]->m_tmp_iError = 0;
		if (m_pNpcList[iNpcH]->m_iHP <= 3) {
			m_pNpcList[iNpcH]->m_iHP += iDice(1, m_pNpcList[iNpcH]->m_iHitDice); // ! 에너지 부족으로 도망쳤을때 성공적으로 도망쳤으므로 에너지 증가.
			if (m_pNpcList[iNpcH]->m_iHP <= 0) m_pNpcList[iNpcH]->m_iHP = 1;
		}
		return;
	}

	// SNOOPY: Buggy here if TargetSearchfunction returns a faultly target
	// server will crash ! (added "else return")
	TargetSearch(iNpcH, &sTarget, &cTargetType);
	if (sTarget != NULL) {
		m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
		m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
	}
	else return;

	// 목표물과 자신의 위치를 구한다. 반대방향으로 도망치기 위함.
	sX = m_pNpcList[iNpcH]->m_sX;
	sY = m_pNpcList[iNpcH]->m_sY;
	switch (m_pNpcList[iNpcH]->m_cTargetType) {
	case DEF_OWNERTYPE_PLAYER:
		dX = m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pClientList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	case DEF_OWNERTYPE_NPC:
		dX = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sX;
		dY = m_pNpcList[m_pNpcList[iNpcH]->m_iTargetIndex]->m_sY;
		break;
	}
	dX = sX - (dX - sX);
	dY = sY - (dY - sY);

	cDir = cGetNextMoveDir(sX, sY, dX, dY, m_pNpcList[iNpcH]->m_cMapIndex, m_pNpcList[iNpcH]->m_cTurn, &m_pNpcList[iNpcH]->m_tmp_iError);
	if (cDir != 0) {
		// 이동할 수 없다. 

		dX = m_pNpcList[iNpcH]->m_sX + _tmp_cTmpDirX[cDir];
		dY = m_pNpcList[iNpcH]->m_sY + _tmp_cTmpDirY[cDir];
		// 예전 위치에서 지운다. 
		// 새 위치에 표시한다. 
		// new 1x1, 2x2, 3x3 npc flee
		if (m_pNpcList[iNpcH]->m_sAreaSize == 0) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearOwner(11, iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY);
		}
		else {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->ClearBigOwner(iNpcH, DEF_OWNERTYPE_NPC, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, m_pNpcList[iNpcH]->m_sAreaSize);
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->SetBigOwner(iNpcH, DEF_OWNERTYPE_NPC, dX, dY, m_pNpcList[iNpcH]->m_sAreaSize);
		}
		m_pNpcList[iNpcH]->m_sX = dX;
		m_pNpcList[iNpcH]->m_sY = dY;
		m_pNpcList[iNpcH]->m_cDir = cDir;
		SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTMOVE, NULL, NULL, NULL);
	}
}

BOOL CGame::bGetNpcMovementArea(short sOwnerH, short pX, short pY, char cMapIndex, char cArea)
{
	short sAreaSquared, sPositionY, sPositionX, sX, sY;
	int i;

	sAreaSquared = cArea * cArea;
	if (m_pNpcList[sOwnerH]->m_sType == 91) return TRUE;
	for (i = 1; i < sAreaSquared; i++) {
		if (_tmp_cEmptyPosX[i] > 0) {
			sPositionX = 2;
		}
		else if (_tmp_cEmptyPosX[i] < 0) {
			sPositionX = -2;
		}
		else {
			sPositionX = 0;
		}

		if (_tmp_cEmptyPosY[i] > 0) {
			sPositionY = 2;
		}
		else if (_tmp_cEmptyPosY[i] < 0) {
			sPositionY = -2;
		}
		else {
			sPositionY = 0;
		}
		if (bGetEmptyArea(sOwnerH, cMapIndex, pX + sPositionX, pY + sPositionY, cArea) != FALSE) {
			sX = pX + sPositionX;
			sY = pY + sPositionY;
			pX = sX;
			pY = sY;
			return TRUE;
		}
	}
	return FALSE;
}