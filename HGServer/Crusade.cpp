#include "Crusade.h"

extern void PutLogList(char* cMsg);
extern char G_cTxt[512];
extern char	G_cData50000[50000];
extern void PutLogFileList(char* cStr);
extern void PutAdminLogFileList(char* cStr);
extern void PutItemLogFileList(char* cStr);
extern void PutLogEventFileList(char* cStr);
extern void PutHackLogFileList(char* cStr);
extern void PutPvPLogFileList(char* cStr);
extern FILE* pLogFile;
extern HWND	G_hWnd;

#pragma warning (disable : 4996 6011 6001 4244 4018 6385 6386 26451 6054 4267 6053 6031)

Crusade::Crusade()
{
}

Crusade::~Crusade()
{
}

void CGame::NpcBehavior_Stop(int iNpcH)
{
	char  cTargetType;
	short sTarget = NULL;
	BOOL  bFlag;

	if (m_pNpcList[iNpcH] == NULL) return;

	m_pNpcList[iNpcH]->m_sBehaviorTurnCount++;

	switch (m_pNpcList[iNpcH]->m_cActionLimit) {
	case 5:
		switch (m_pNpcList[iNpcH]->m_sType) {
		case 38:
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				bFlag = _bNpcBehavior_ManaCollector(iNpcH);
				if (bFlag == TRUE) {
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, 1);
				}
			}
			break;

		case 39: // Detector
		case 89: // AGC (Ancient Grand Cannon)	will turn as detectors	
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				bFlag = _bNpcBehavior_Detector(iNpcH);

				if (bFlag == TRUE) {
					// 적을 발견했다. 공격 동작으로 알려야 한다.	
					SendEventToNearClient_TypeA(iNpcH, DEF_OWNERTYPE_NPC, MSGID_EVENT_MOTION, DEF_OBJECTATTACK, m_pNpcList[iNpcH]->m_sX, m_pNpcList[iNpcH]->m_sY, 1);
				}
			}
			break;

		case 40: // Energy Shield Generator
			break;

		case 41: // Grand Magic Generator
			if (m_pNpcList[iNpcH]->m_sBehaviorTurnCount >= 3) {
				m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
				_NpcBehavior_GrandMagicGenerator(iNpcH);
			}
			break;

		case 42: // ManaStone: v2.05 정기적으로 마나스톤의 에너지를 5씩 생성한다.
			m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
			m_pNpcList[iNpcH]->m_iV1 += 5;
			if (m_pNpcList[iNpcH]->m_iV1 >= 5) m_pNpcList[iNpcH]->m_iV1 = 5;
			break;

		default:
			TargetSearch(iNpcH, &sTarget, &cTargetType);
			break;
		}
		break;
	}

	if ((sTarget != NULL)) {

		// 공격목표 발견. 
		m_pNpcList[iNpcH]->m_cBehavior = DEF_BEHAVIOR_ATTACK;
		m_pNpcList[iNpcH]->m_sBehaviorTurnCount = 0;
		m_pNpcList[iNpcH]->m_iTargetIndex = sTarget;
		m_pNpcList[iNpcH]->m_cTargetType = cTargetType;
		// 여기서 표효 동작같은것을 위한 메시지 발송. 

	}
}

void CGame::LocalStartCrusadeMode(DWORD dwCrusadeGUID)
{
	int i, z, tX, tY, iNamingValue, c, m;
	char cName[6], cNpcName[21], cNpcWayPoint[11];

	if (m_bIsCrusadeMode == TRUE) return;
	if (m_bIsHeldenianMode == TRUE) return;
	if (m_bIsApocalypseMode == TRUE) return;
	m_bIsCrusadeMode = TRUE;
	m_iCrusadeWinnerSide = 0;
	if (dwCrusadeGUID != NULL) {
		_CreateCrusadeGUID(dwCrusadeGUID, NULL);
		m_dwCrusadeGUID = dwCrusadeGUID;
	}

	for (c = 1; c < DEF_MAXCLIENTS; c++)
		if ((m_pClientList[c] != NULL) && (m_pClientList[c]->m_bIsInitComplete == TRUE)) {
			m_pClientList[c]->m_iCrusadeDuty = 0;
			m_pClientList[c]->m_iConstructionPoint = 0;
			m_pClientList[c]->m_dwCrusadeGUID = m_dwCrusadeGUID;
			SendNotifyMsg(NULL, c, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, m_pClientList[c]->m_iCrusadeDuty, NULL, NULL);
		}

	for (m = 0; m < DEF_MAXMAPS; m++)
		if (m_pMapList[m] != NULL) m_pMapList[m]->RestoreStrikePoints();

	ZeroMemory(cName, sizeof(cName));
	ZeroMemory(cNpcName, sizeof(cNpcName));
	ZeroMemory(cNpcWayPoint, sizeof(cNpcWayPoint));

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
		if (m_stCrusadeStructures[i].cType != NULL) {
			for (z = 0; z < DEF_MAXMAPS; z++)
				if ((m_pMapList[z] != NULL) && (strcmp(m_pMapList[z]->m_cName, m_stCrusadeStructures[i].cMapName) == 0)) {
					// ��짠횆징째징 ��횕횆징횉횕쨈횂 쨍횎쩔징 째횉횄횪쨔째��쨩 ��짠횆징쩍횄횇짼쨈횢.
					iNamingValue = m_pMapList[z]->iGetEmptyNamingValue();
					if (iNamingValue != -1) {
						// 쨈천��횑쨩처 ��횑 쨍횎쩔징 NPC쨍짝 쨍쨍쨉챕쩌철 쩐첩쨈횢. ��횑쨍짠��쨩 횉횘쨈챌횉횘 쩌철 쩐첩짹창 쨋짠쨔짰.
						// ��횑쨌짹 ��횕��횑?

						// NPC쨍짝 쨩첵쩌쨘횉횗쨈횢.
						wsprintf(cName, "XX%d", iNamingValue);
						cName[0] = '_';
						cName[1] = z + 65;

						switch (m_stCrusadeStructures[i].cType) {
						case 36:
							if (strcmp(m_pMapList[z]->m_cName, "aresden") == 0)
								strcpy(cNpcName, "AGT-Aresden");
							else if (strcmp(m_pMapList[z]->m_cName, "elvine") == 0)
								strcpy(cNpcName, "AGT-Elvine");
							break;

						case 37:
							if (strcmp(m_pMapList[z]->m_cName, "aresden") == 0)
								strcpy(cNpcName, "CGT-Aresden");
							else if (strcmp(m_pMapList[z]->m_cName, "elvine") == 0)
								strcpy(cNpcName, "CGT-Elvine");
							break;

						case 40:
							if (strcmp(m_pMapList[z]->m_cName, "aresden") == 0)
								strcpy(cNpcName, "ESG-Aresden");
							else if (strcmp(m_pMapList[z]->m_cName, "elvine") == 0)
								strcpy(cNpcName, "ESG-Elvine");
							break;

						case 41:
							if (strcmp(m_pMapList[z]->m_cName, "aresden") == 0)
								strcpy(cNpcName, "GMG-Aresden");
							else if (strcmp(m_pMapList[z]->m_cName, "elvine") == 0)
								strcpy(cNpcName, "GMG-Elvine");
							break;

						case 42:
							strcpy(cNpcName, "ManaStone");
							break;

						default:
							strcpy(cNpcName, m_pNpcConfigList[m_stCrusadeStructures[i].cType]->m_cNpcName);
							break;
						}

						tX = (int)m_stCrusadeStructures[i].dX;
						tY = (int)m_stCrusadeStructures[i].dY;
						if (bCreateNewNpc(cNpcName, cName, m_pMapList[z]->m_cName, 0, 0, DEF_MOVETYPE_RANDOM,
							&tX, &tY, cNpcWayPoint, NULL, NULL, -1, FALSE) == FALSE) {
							// 쩍횉횈횖횉횩��쨍쨔횉쨌횓 쩔쨔쩐횪쨉횊 NameValue쨍짝 횉횠횁짝쩍횄횇짼쨈횢.
							m_pMapList[z]->SetNamingValueEmpty(iNamingValue);
						}
						else {
							wsprintf(G_cTxt, "(!) Creating Crusade Structure(%s) at %s(%d, %d)", cNpcName, m_stCrusadeStructures[i].cMapName, tX, tY);
							PutLogList(G_cTxt);
						}
					}
				}
		}

	PutLogList("(!)Crusade Mode ON.");
	_bCrusadeLog(DEF_CRUSADELOG_STARTCRUSADE, NULL, NULL, NULL);
}

void CGame::_CreateCrusadeGUID(DWORD dwCrusadeGUID, int iWinnerSide)
{
	char* cp, cTxt[256], cTemp[1024];
	FILE* pFile;

	

	pFile = fopen("..\\GameConfigs\\CrusadeGUID.Txt", "wt");
	if (pFile == NULL) {
		// 횈횆��횕��쨩 쨍쨍쨉챕 쩌철 쩐첩째횇쨀짧 쨩챌��횑횁챤째징 횁철쨀짧횆징째횚 ��횤��쨘 째챈쩔챙쨈횂 . 
		wsprintf(cTxt, "(!) Cannot create CrusadeGUID(%d) file", dwCrusadeGUID);
		PutLogList(cTxt);
	}
	else {
		ZeroMemory(cTemp, sizeof(cTemp));

		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "CrusadeGUID = %d\n", dwCrusadeGUID);
		strcat(cTemp, cTxt);

		ZeroMemory(cTxt, sizeof(cTxt));
		wsprintf(cTxt, "winner-side = %d\n", iWinnerSide);
		strcat(cTemp, cTxt);

		cp = (char*)cTemp;
		fwrite(cp, strlen(cp), 1, pFile);

		wsprintf(cTxt, "(!) CrusadeGUID(%d) file created", dwCrusadeGUID);
		PutLogList(cTxt);

		fclose(pFile);
	}
}

void CGame::bReadCrusadeGUIDFile(char* cFn)
{
	FILE* pFile;
	HANDLE hFile;
	DWORD  dwFileSize;
	char* cp, * token, cReadMode;
	char seps[] = "= \t\n";
	class CStrTok* pStrTok;

	cReadMode = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile == NULL) {
		// 째횚��횙쩌짯쨔철��횉 횄횎짹창횊짯 횈횆��횕��쨩 ��횖��쨩 쩌철 쩐첩쨈횢.
		PutLogList("(!) Cannot open CrusadeGUID file.");
		return;
	}
	else {
		PutLogList("(!) Reading CrusadeGUID file...");
		cp = new char[dwFileSize + 2];
		ZeroMemory(cp, dwFileSize + 2);
		fread(cp, dwFileSize, 1, pFile);

		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();

		while (token != NULL) {

			if (cReadMode != 0) {
				switch (cReadMode) {
				case 1:
					m_dwCrusadeGUID = atoi(token);
					wsprintf(G_cTxt, "(!) Read CrusadeGUID (%d) file.", m_dwCrusadeGUID);
					PutLogList(G_cTxt);
					cReadMode = 0;
					break;

				case 2:
					// New 13/05/2004 Changed
					m_iLastCrusadeWinner = atoi(token);
					wsprintf(G_cTxt, "(!) Crusade Winner Side: (%d)", m_iLastCrusadeWinner);
					PutLogList(G_cTxt);
					cReadMode = 0;
					break;
				}
			}
			else {
				if (memcmp(token, "CrusadeGUID", 11) == 0) cReadMode = 1;
				if (memcmp(token, "winner-side", 11) == 0) cReadMode = 2;
			}

			token = pStrTok->pGet();
		}

		delete pStrTok;
		delete[] cp;

		fclose(pFile);
	}
}

/*********************************************************************************************************************
**  void CGame::GameProcess()																						**
**  DESCRIPTION			:: reads Crusade.cfg file																	**
**  LAST_UPDATED		:: March 17, 2005; 12:30 PM; Hypnotoad														**
**	RETURN_VALUE		:: void																						**
**  NOTES				::	n/a																						**
**	MODIFICATION		::	n/a																						**
**********************************************************************************************************************/
void CGame::bReadCrusadeStructureConfigFile(char* cFn)
{
	FILE* pFile;
	HANDLE hFile;
	DWORD  dwFileSize;
	char* cp, * token, cReadModeA, cReadModeB;
	char seps[] = "= \t\n";
	int   iIndex;
	class CStrTok* pStrTok;

	cReadModeA = 0;
	cReadModeB = 0;

	hFile = CreateFile(cFn, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	dwFileSize = GetFileSize(hFile, NULL);
	if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

	pFile = fopen(cFn, "rt");
	if (pFile != NULL) {

		PutLogList("(!) Reading Crusade configuration file...");
		cp = new char[dwFileSize + 2];
		ZeroMemory(cp, dwFileSize + 2);
		fread(cp, dwFileSize, 1, pFile);

		iIndex = 0;
		pStrTok = new class CStrTok(cp, seps);
		token = pStrTok->pGet();
		while (token != NULL) {
			if (cReadModeA != 0) {
				switch (cReadModeA) {
				case 1:
					switch (cReadModeB) {
					case 1:
						if (_bGetIsStringIsNumber(token) == FALSE) {
							PutLogList("(!!!) CRITICAL ERROR!  Crusade configuration file error - Wrong Data format(1).");
							delete[] cp;
							delete pStrTok;
							return;
						}
						iIndex = atoi(token);

						if (m_stCrusadeStructures[iIndex].cType != NULL) {
							PutLogList("(!!!) CRITICAL ERROR!  Crusade configuration file error - Duplicate crusade number."); // changed from "duplicate potion number"
							delete[] cp;
							delete pStrTok;
							return;
						}
						cReadModeB = 2;
						break;

					case 2:
						ZeroMemory(m_stCrusadeStructures[iIndex].cMapName, sizeof(m_stCrusadeStructures[iIndex].cMapName));
						memcpy(m_stCrusadeStructures[iIndex].cMapName, token, strlen(token));
						cReadModeB = 3;
						break;

					case 3:
						if (_bGetIsStringIsNumber(token) == FALSE) {
							PutLogList("(!!!) CRITICAL ERROR!  Crusade configuration file error - Wrong Data format.");
							delete[] cp;
							delete pStrTok;
							return;
						}
						m_stCrusadeStructures[iIndex].cType = atoi(token);
						cReadModeB = 4;
						break;

					case 4:
						if (_bGetIsStringIsNumber(token) == FALSE) {
							PutLogList("(!!!) CRITICAL ERROR!  Crusade configuration file error - Wrong Data format.");
							delete[] cp;
							delete pStrTok;
							return;
						}
						m_stCrusadeStructures[iIndex].dX = atoi(token);
						cReadModeB = 5;
						break;

					case 5:
						if (_bGetIsStringIsNumber(token) == FALSE) {
							PutLogList("(!!!) CRITICAL ERROR!  Crusade configuration file error - Wrong Data format.");
							delete[] cp;
							delete pStrTok;
							return;
						}
						m_stCrusadeStructures[iIndex].dY = atoi(token);
						cReadModeA = 0;
						cReadModeB = 0;
						break;
					}
					break;

				default:
					break;
				}
			}
			else {
				if (memcmp(token, "crusade-structure", 17) == 0) {
					cReadModeA = 1;
					cReadModeB = 1;
				}
			}
			token = pStrTok->pGet();
		}
		delete pStrTok;
		delete[] cp;
		if ((cReadModeA != 0) || (cReadModeB != 0)) {
			PutLogList("(!!!) CRITICAL ERROR! Crusade Structure configuration file contents error!");
			return;
		}
		fclose(pFile);
	}
}

void CGame::CheckCrusadeResultCalculation(int iClientH)
{
	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_cWarType != 1) return;

	if ((m_bIsCrusadeMode == FALSE) && (m_pClientList[iClientH]->m_dwCrusadeGUID != 0)) {
		if (m_pClientList[iClientH]->m_dwCrusadeGUID == m_dwCrusadeGUID) {
			if (m_iCrusadeWinnerSide == 0) {
				GetExp(iClientH, (m_pClientList[iClientH]->m_iWarContribution / 6));
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, m_pClientList[iClientH]->m_iWarContribution, NULL);
				_bCrusadeLog(DEF_CRUSADELOG_GETEXP, iClientH, (m_pClientList[iClientH]->m_iWarContribution / 6), NULL);
			}
			else {
				if (m_iCrusadeWinnerSide == m_pClientList[iClientH]->m_cSide) {
					if (m_pClientList[iClientH]->m_iLevel <= 80) {
						m_pClientList[iClientH]->m_iWarContribution += (m_pClientList[iClientH]->m_iLevel) * 100;
					}
					else if (m_pClientList[iClientH]->m_iLevel > 80 && m_pClientList[iClientH]->m_iLevel <= 100) {
						m_pClientList[iClientH]->m_iWarContribution += (m_pClientList[iClientH]->m_iLevel) * 40;
					}
					else if (m_pClientList[iClientH]->m_iLevel > 100)
					{
						m_pClientList[iClientH]->m_iWarContribution += m_pClientList[iClientH]->m_iLevel;
					}
					GetExp(iClientH, m_pClientList[iClientH]->m_iWarContribution);
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, m_pClientList[iClientH]->m_iWarContribution, NULL);
					_bCrusadeLog(DEF_CRUSADELOG_GETEXP, iClientH, m_pClientList[iClientH]->m_iWarContribution, NULL);
				}
				else if (m_iCrusadeWinnerSide != m_pClientList[iClientH]->m_cSide) {
					m_pClientList[iClientH]->m_iWarContribution += m_pClientList[iClientH]->m_iLevel;
					GetExp(iClientH, (m_pClientList[iClientH]->m_iWarContribution / 10));
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, -1 * m_pClientList[iClientH]->m_iWarContribution, NULL);
					_bCrusadeLog(DEF_CRUSADELOG_GETEXP, iClientH, (m_pClientList[iClientH]->m_iWarContribution / 10), NULL);
				}
			}
		}
		else {
			SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, 0, NULL, -1);
		}
		m_pClientList[iClientH]->m_iCrusadeDuty = 0;
		m_pClientList[iClientH]->m_iWarContribution = 0;
		m_pClientList[iClientH]->m_dwCrusadeGUID = 0;
		m_pClientList[iClientH]->m_dwSpeedHackCheckTime = timeGetTime();
		m_pClientList[iClientH]->m_iSpeedHackCheckExp = m_pClientList[iClientH]->m_iExp;
	}
}

// New 11/05/2004 Changed
void CGame::DoMeteorStrikeDamageHandler(int iMapIndex)
{
	int i, iDamage;

	// 횉횠쨈챌 쨍횎��횉 횉횄쨌쨔��횑쩐챤쨉챕��횉 HP쨍짝 ��횕째첵 쨩챔째짢
	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_cSide != 0) && (m_pClientList[i]->m_cMapIndex == iMapIndex)) {

			if (m_pClientList[i]->m_iLevel < 80)
				iDamage = m_pClientList[i]->m_iLevel + iDice(1, 100);
			else iDamage = (m_pClientList[i]->m_iLevel) * 2 + iDice(1, 100);

			if (m_pClientList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 2) { //magic cut in half
				iDamage = (iDamage / 2) - 2;
			}

			if (m_pClientList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_PROTECT] == 5) {
				iDamage = 0;
			}

			if (m_pClientList[i]->m_iAdminUserLevel > 0) { // Admins get no damage
				iDamage = 0;
			}

			m_pClientList[i]->m_iHP -= iDamage;
			if (m_pClientList[i]->m_iHP <= 0) {
				// 횉횄쨌쨔��횑쩐챤째징 쨩챌쨍횁횉횩쨈횢.
				ClientKilledHandler(i, NULL, NULL, iDamage);
				m_stMeteorStrikeResult.iCasualties++;
			}
			else {
				if (iDamage > 0) {
					// 쨔횧��쨘 쨈챘쨔횑횁철쨍짝 횇챘쨘쨍횉횗쨈횢. <- HP쨍짝 짹횞쨈챘쨌횓 쩐횏쨍째쨈횢.
					SendNotifyMsg(NULL, i, DEF_NOTIFY_HP, NULL, NULL, NULL, NULL);
					// 횄챈째횦��쨩 쨔횧쩐횘쨈횢쨍챕 횄챈째횦쨉쩔��횤 ��체쩌횤 
					SendEventToNearClient_TypeA(i, DEF_OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, DEF_OBJECTDAMAGE, iDamage, NULL, NULL);

					if (m_pClientList[i]->m_bSkillUsingStatus[19] != TRUE) {
						m_pMapList[m_pClientList[i]->m_cMapIndex]->ClearOwner(0, i, DEF_OWNERTYPE_PLAYER, m_pClientList[i]->m_sX, m_pClientList[i]->m_sY);
						m_pMapList[m_pClientList[i]->m_cMapIndex]->SetOwner(i, DEF_OWNERTYPE_PLAYER, m_pClientList[i]->m_sX, m_pClientList[i]->m_sY);
					}

					if (m_pClientList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] != 0) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_MAGICEFFECTOFF, DEF_MAGICTYPE_HOLDOBJECT, m_pClientList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT], NULL, NULL);
						m_pClientList[i]->m_cMagicEffectStatus[DEF_MAGICTYPE_HOLDOBJECT] = NULL;
						bRemoveFromDelayEventList(i, DEF_OWNERTYPE_PLAYER, DEF_MAGICTYPE_HOLDOBJECT);
					}
				}
			}
		}
}

void CGame::SyncMiddlelandMapInfo()
{
	int i;
	char* cp;
	short* sp;

	// 미들랜드의 정보를 모든 서버에게 싱크시킨다. 미들랜드를 담당한 서버라면 바로 구조체를 업데이트 하고 나머지 서버들에게 정보 전송.
	if (m_iMiddlelandMapIndex != -1) {
		// 구조체 클리어
		for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
			m_stMiddleCrusadeStructureInfo[i].cType = NULL;
			m_stMiddleCrusadeStructureInfo[i].cSide = NULL;
			m_stMiddleCrusadeStructureInfo[i].sX = NULL;
			m_stMiddleCrusadeStructureInfo[i].sY = NULL;
		}
		// 구조체 복사 및 전송 메시지 작성 
		m_iTotalMiddleCrusadeStructures = m_pMapList[m_iMiddlelandMapIndex]->m_iTotalCrusadeStructures;
		ZeroMemory(G_cData50000, sizeof(G_cData50000));
		cp = (char*)G_cData50000;
		*cp = GSM_MIDDLEMAPSTATUS;
		cp++;

		sp = (short*)cp;
		*sp = (short)m_iTotalMiddleCrusadeStructures;
		cp += 2;

		for (i = 0; i < m_iTotalMiddleCrusadeStructures; i++) {
			m_stMiddleCrusadeStructureInfo[i].cType = m_pMapList[m_iMiddlelandMapIndex]->m_stCrusadeStructureInfo[i].cType;
			m_stMiddleCrusadeStructureInfo[i].cSide = m_pMapList[m_iMiddlelandMapIndex]->m_stCrusadeStructureInfo[i].cSide;
			m_stMiddleCrusadeStructureInfo[i].sX = m_pMapList[m_iMiddlelandMapIndex]->m_stCrusadeStructureInfo[i].sX;
			m_stMiddleCrusadeStructureInfo[i].sY = m_pMapList[m_iMiddlelandMapIndex]->m_stCrusadeStructureInfo[i].sY;

			*cp = m_stMiddleCrusadeStructureInfo[i].cType;
			cp++;
			*cp = m_stMiddleCrusadeStructureInfo[i].cSide;
			cp++;
			sp = (short*)cp;
			*sp = (short)m_stMiddleCrusadeStructureInfo[i].sX;
			cp += 2;
			sp = (short*)cp;
			*sp = (short)m_stMiddleCrusadeStructureInfo[i].sY;
			cp += 2;
		}

	}
}

void CGame::GSM_SetGuildConstructLoc(int iGuildGUID, int dX, int dY, char* pMapName)
{
	int i, iIndex;
	DWORD dwTemp, dwTime;

	// 횇짭쨋처��횑쩐챨횈짰쨌횓쨘횓횇횒��횉 쩔채횄쨩��횑 쩐횈쨈횕쨋처 쨈횢쨍짜 쩌짯쨔철쨌횓쨘횓횇횒��횉 횇횣쨌쨔횈첨횈짰 횁횂횉짜 쩌쨀횁짚 쩔채횄쨩��횙. ����쨈채횉횘 횉횎쩔채 쩐첩��쩍.

	dwTime = timeGetTime();

	// 쨍횛��첬 째째��쨘 GUID쨍짝 째징횁첩 짹챈쨉책 횇횣쨌쨔횈첨횈짰 횁횂횉짜째징 쩌쨀횁짚쨉횉쩐챤 ��횜쨈횂횁철 횄짙쨈횂쨈횢.
	for (i = 0; i < DEF_MAXGUILDS; i++)
		if (m_pGuildTeleportLoc[i].m_iV1 == iGuildGUID) {
			// ��횑쨔횑 짹챈쨉책째징 ��횜쨈횢.
			if ((m_pGuildTeleportLoc[i].m_sDestX2 == dX) && (m_pGuildTeleportLoc[i].m_sDestY2 == dY) && (strcmp(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName) == 0)) {
				// 쨀쨩쩔챘��횑 ��횕횆징횉횗쨈횢. 횇쨍��횙 ��횚쨌횂횊횆 쩍쨘횇쨉.
				m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;
				return;
			}
			else {
				// 쨀쨩쩔챘 째쨩쩍횇
				m_pGuildTeleportLoc[i].m_sDestX2 = dX;
				m_pGuildTeleportLoc[i].m_sDestY2 = dY;
				ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName2));
				strcpy(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName);
				m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;
				return;
			}
		}

	// 쩌쨀횁짚쨉횊 쨀쨩쩔챘��횑 쩐첩쨈횢. 쨩천쨌횓 쩌쨀횁짚횉횗쨈횢.
	dwTemp = 0;
	iIndex = -1;
	for (i = 0; i < DEF_MAXGUILDS; i++) {
		if (m_pGuildTeleportLoc[i].m_iV1 == NULL) {

			m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
			m_pGuildTeleportLoc[i].m_sDestX2 = dX;
			m_pGuildTeleportLoc[i].m_sDestY2 = dY;
			ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
			strcpy(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName);
			m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;
			return;
		}
		else {
			// 째징��책 쩔��쨌짠쨉쩔쩐횊 횂체횁쨋쨉횉횁철 쩐횎��쨘 쨍짰쩍쨘횈짰��횉 ��횓쨉짝쩍쨘쨍짝 횄짙쨈횂쨈횢.
			if (dwTemp < (dwTime - m_pGuildTeleportLoc[i].m_dwTime2)) {
				dwTemp = (dwTime - m_pGuildTeleportLoc[i].m_dwTime2);
				iIndex = i;
			}
		}
	}

	m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
	m_pGuildTeleportLoc[i].m_sDestX2 = dX;
	m_pGuildTeleportLoc[i].m_sDestY2 = dY;
	ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName2));
	strcpy(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName);
	m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;
}

void CGame::CheckCommanderConstructionPoint(int iClientH)
{
	char* cp, cData[120];
	int* ip, i;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_bIsCrusadeMode == FALSE) return;
	if (m_pClientList[iClientH]->m_iConstructionPoint <= 0) return;

	switch (m_pClientList[iClientH]->m_iCrusadeDuty) {
	case 1: // 횈횆��횑횇횒
	case 2: // 째횉쩌쨀��횣: 쨍챨쩐횈 쨀천��쨘 횈첨��횓횈짰쨍짝 짹챈쨉책쨍쨋쩍쨘횇횒 횁철횊횜째체쩔징째횚 ��체쨈횧횉횗쨈횢.
		for (i = 0; i < DEF_MAXCLIENTS; i++)
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_iCrusadeDuty == 3) &&
				(m_pClientList[i]->m_iGuildGUID == m_pClientList[iClientH]->m_iGuildGUID)) {
				// 횉철��챌 쩌짯쨔철 쨀쨩쩔징 짹챈쨉책쨍쨋쩍쨘횇횒 횁철횊횜째체��횑 ��횜쨈횢. 횁철횊횜째체��횉 횈첨��횓횈짰쨍짝 쨀척��횓 횊횆 
				m_pClientList[i]->m_iConstructionPoint += m_pClientList[iClientH]->m_iConstructionPoint;
				m_pClientList[i]->m_iWarContribution += (m_pClientList[iClientH]->m_iConstructionPoint / 10);



				SendNotifyMsg(NULL, i, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[i]->m_iConstructionPoint, m_pClientList[i]->m_iWarContribution, NULL, NULL);
				m_pClientList[iClientH]->m_iConstructionPoint = 0; // 째짧 횄횎짹창횊짯 
				return;
			}

		// 쨈횢쨍짜 쩌짯쨔철��횉 횁철횊횜째체쩔징째횚 쩐횏쨌횁쩐횩 횉횗쨈횢.
		ZeroMemory(cData, sizeof(cData));
		cp = (char*)cData;
		*cp = GSM_CONSTRUCTIONPOINT;
		cp++;
		ip = (int*)cp;
		*ip = m_pClientList[iClientH]->m_iGuildGUID;
		cp += 4;
		ip = (int*)cp;
		*ip = m_pClientList[iClientH]->m_iConstructionPoint;
		cp += 4;
		bStockMsgToGateServer(cData, 9);

		m_pClientList[iClientH]->m_iConstructionPoint = 0; // 째짧 횄횎짹창횊짯 
		break;

	case 3: // 횁철횊횜째체: 쨘쨍쨀쩐 횉횎쩔채 쩐첩��쩍 

		break;
	}
}

void CGame::GSM_ConstructionPoint(int iGuildGUID, int iPoint)
{
	int i;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_iCrusadeDuty == 3) &&
			(m_pClientList[i]->m_iGuildGUID == iGuildGUID)) {
			// 횉횠쨈챌 짹챈쨉책쨍쨋쩍쨘횇횒 횁철횊횜째체��쨩 횄짙쩐횘쨈횢.
			m_pClientList[i]->m_iConstructionPoint += iPoint;
			m_pClientList[i]->m_iWarContribution += iPoint / 10;

			SendNotifyMsg(NULL, i, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[i]->m_iConstructionPoint, m_pClientList[i]->m_iWarContribution, NULL, NULL);

			break;
		}
}

void CGame::ManualEndCrusadeMode(int iWinnerSide)
{
	char* cp, cData[256];
	WORD* wp;

	// 쨍횇쨈쨘쩐처쨌횓 횇짤쨌챌쩌쩌��횑쨉책 쨍챨쨉책쨍짝 횁쩐쨌찼쩍횄횇짼쨈횢. 쨘챰짹채 쨩처횇횂쨌횓 횁쩐쨌찼쩍횄횇짼쨈횢.
	if (m_bIsCrusadeMode == FALSE) return;

	LocalEndCrusadeMode(iWinnerSide);

	// 쨈횢쨍짜 쩌짯쨔철쩔징 횇짤쨌챌쩌쩌��횑쨉책 횁쩐쨌찼쨍짝 쩐횏쨍짼.
	ZeroMemory(cData, sizeof(cData));
	cp = (char*)(cData);
	*cp = GSM_ENDCRUSADE;
	cp++;

	*cp = (char)iWinnerSide;
	cp++;

	wp = (WORD*)cp;
	*wp = NULL;
	cp += 2;

	wp = (WORD*)cp;
	*wp = NULL;
	cp += 2;

	wp = (WORD*)cp;
	*wp = NULL;
	cp += 2;

	cp += 10;

	bStockMsgToGateServer(cData, 18);
}

// New 13/05/2004
BOOL CGame::_bCrusadeLog(int iAction, int iClientH, int iData, char* cName)
{
	char  cTxt[200];

	//  쨌횓짹횞 쨀짼짹채쨈횢. 
	ZeroMemory(cTxt, sizeof(cTxt));

	switch (iAction) {

	case DEF_CRUSADELOG_ENDCRUSADE:
		if (cName == NULL) return FALSE;
		wsprintf(cTxt, "\tEnd Crusade\t%s", cName);
		break;

	case DEF_CRUSADELOG_SELECTDUTY:
		if (cName == NULL) return FALSE;
		if (m_pClientList[iClientH] == NULL) return FALSE;
		wsprintf(cTxt, "PC(%s)\tSelect Duty\t(%s)\t \t(%s)", m_pClientList[iClientH]->m_cCharName, cName, m_pClientList[iClientH]->m_cGuildName);
		break;

	case DEF_CRUSADELOG_GETEXP:
		if (m_pClientList[iClientH] == NULL) return FALSE;
		wsprintf(cTxt, "PC(%s)\tGet Exp\t(%d)\t \t(%s)", m_pClientList[iClientH]->m_cCharName, iData, m_pClientList[iClientH]->m_cGuildName);
		break;

	case DEF_CRUSADELOG_STARTCRUSADE:
		wsprintf(cTxt, "\tStart Crusade");
		break;

	default:
		return FALSE;
	}

	bSendMsgToLS(MSGID_GAMECRUSADELOG, iClientH, NULL, cTxt);
	return TRUE;
}

void CGame::CrusadeWarStarter()
{
	SYSTEMTIME SysTime;
	int i;

	if (m_bIsCrusadeMode == TRUE) return;
	if (m_bIsApocalypseMode == TRUE) return;
	if (m_bIsHeldenianMode) return;
	if (m_bIsCrusadeWarStarter == FALSE) return;

	// 게임 서버 1번에서만 
	GetLocalTime(&SysTime);

	for (i = 0; i < DEF_MAXSCHEDULE; i++)
		if ((m_stCrusadeWarSchedule[i].iDay == SysTime.wDayOfWeek) &&
			(m_stCrusadeWarSchedule[i].iHour == SysTime.wHour) &&
			(m_stCrusadeWarSchedule[i].iMinute == SysTime.wMinute)) {
			PutLogList("(!) Automated Crusade is being initiated!");
			GlobalStartCrusadeMode();
			break;
		}
}

void CGame::GlobalStartCrusadeMode()
{
	char* cp, cData[120];
	DWORD* dwp, dwCrusadeGUID;
	SYSTEMTIME SysTime;

	// 오류로 인해 하루에 두번 전면전이 발생하는 것을 막는 코드 
	GetLocalTime(&SysTime);
	if (m_iLatestCrusadeDayOfWeek != -1) {
		if (m_iLatestCrusadeDayOfWeek == SysTime.wDayOfWeek) return;
	}
	else m_iLatestCrusadeDayOfWeek = SysTime.wDayOfWeek;

	dwCrusadeGUID = timeGetTime();

	ZeroMemory(cData, sizeof(cData));
	cp = (char*)cData;
	*cp = GSM_BEGINCRUSADE;
	cp++;
	dwp = (DWORD*)cp;
	*dwp = dwCrusadeGUID;
	cp += 4;

	bStockMsgToGateServer(cData, 5);

	LocalStartCrusadeMode(dwCrusadeGUID);
}

void CGame::RequestGuildTeleportHandler(int iClientH)
{
	int i;
	char cMapName[11];

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_iLockedMapTime != NULL) {
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_LOCKEDMAP, m_pClientList[iClientH]->m_iLockedMapTime, NULL, NULL, m_pClientList[iClientH]->m_cLockedMapName);
		return;
	}

	// if a guild teleport is set when its not a crusade, log the hacker
	if (!m_bIsCrusadeMode) {
		wsprintf(G_cTxt, "Accessing crusade teleport: (%s) Player: (%s) - setting teleport location when crusade is disabled.",
			m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		DeleteClient(iClientH, TRUE, TRUE);
		return;
	}

	// if a player is using guild teleport and he is not in a guild, log the hacker
	if (m_pClientList[iClientH]->m_iCrusadeDuty == 0) {
		wsprintf(G_cTxt, "Accessing crusade teleport: (%s) Player: (%s) - teleporting when not in a guild",
			m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		DeleteClient(iClientH, TRUE, TRUE);
		return;
	}

	if ((m_pClientList[iClientH]->m_cMapIndex == m_iMiddlelandMapIndex) &&
		m_iMiddlelandMapIndex != -1)
		return;

	for (i = 0; i < DEF_MAXGUILDS; i++)
		if (m_pGuildTeleportLoc[i].m_iV1 == m_pClientList[iClientH]->m_iGuildGUID) {
			// 길드를 찾았다.
			ZeroMemory(cMapName, sizeof(cMapName));
			strcpy(cMapName, m_pGuildTeleportLoc[i].m_cDestMapName);



			// !!! RequestTeleportHandler내에서 m_cMapName을 쓰기 때문에 그대로 파라미터로 넘겨주면 오동작
			RequestTeleportHandler(iClientH, "2   ", cMapName, m_pGuildTeleportLoc[i].m_sDestX, m_pGuildTeleportLoc[i].m_sDestY);
			break;
		}

}


void CGame::GSM_SetGuildTeleportLoc(int iGuildGUID, int dX, int dY, char* pMapName)
{
	int i, iIndex;
	DWORD dwTemp, dwTime;

	// 클라이언트로부터의 요청이 아니라 다른 서버로부터의 텔레포트 좌표 설정 요청임. 응답할 필요 없음.

	dwTime = timeGetTime();

	// 먼저 같은 GUID를 가진 길드 텔레포트 좌표가 설정되어 있는지 찾는다.
	for (i = 0; i < DEF_MAXGUILDS; i++)
		if (m_pGuildTeleportLoc[i].m_iV1 == iGuildGUID) {
			// 이미 길드가 있다.
			if ((m_pGuildTeleportLoc[i].m_sDestX == dX) && (m_pGuildTeleportLoc[i].m_sDestY == dY) && (strcmp(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName) == 0)) {
				// 내용이 일치한다. 타임 입력후 스킵.
				m_pGuildTeleportLoc[i].m_dwTime = dwTime;
				return;
			}
			else {
				// 내용 갱신
				m_pGuildTeleportLoc[i].m_sDestX = dX;
				m_pGuildTeleportLoc[i].m_sDestY = dY;
				ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
				strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
				m_pGuildTeleportLoc[i].m_dwTime = dwTime;
				return;
			}
		}

	// 설정된 내용이 없다. 새로 설정한다.
	dwTemp = 0;
	iIndex = -1;
	for (i = 0; i < DEF_MAXGUILDS; i++) {
		if (m_pGuildTeleportLoc[i].m_iV1 == NULL) {

			m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
			m_pGuildTeleportLoc[i].m_sDestX = dX;
			m_pGuildTeleportLoc[i].m_sDestY = dY;
			ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
			strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
			m_pGuildTeleportLoc[i].m_dwTime = dwTime;
			return;
		}
		else {
			// 가장 오랫동안 참조되지 않은 리스트의 인덱스를 찾는다.
			if (dwTemp < (dwTime - m_pGuildTeleportLoc[i].m_dwTime)) {
				dwTemp = (dwTime - m_pGuildTeleportLoc[i].m_dwTime);
				iIndex = i;
			}
		}
	}

	m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
	m_pGuildTeleportLoc[i].m_sDestX = dX;
	m_pGuildTeleportLoc[i].m_sDestY = dY;
	ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
	strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
	m_pGuildTeleportLoc[i].m_dwTime = dwTime;
}


void CGame::RequestSetGuildTeleportLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char* pMapName)
{
	char* cp, cData[120];
	int i;
	int* ip, iIndex;
	DWORD dwTemp, dwTime;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsOnServerChange == TRUE) return;

	// if a player is teleporting and its not a crusade, log the hacker
	if (!m_bIsCrusadeMode) {
		wsprintf(G_cTxt, "Accessing Crusade Set Teleport:(%s) Player: (%s) - setting point when not a crusade.",
			m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		DeleteClient(iClientH, TRUE, TRUE);
		return;
	}

	// if a player is teleporting and its not a crusade, log the hacker
	if (m_pClientList[iClientH]->m_iCrusadeDuty != 3) {
		wsprintf(G_cTxt, "Accessing Crusade Set Teleport: (%s) Player: (%s) - setting point when not a guildmaster.",
			m_pClientList[iClientH]->m_cIPaddress, m_pClientList[iClientH]->m_cCharName);
		PutHackLogFileList(G_cTxt);
		DeleteClient(iClientH, TRUE, TRUE);
		return;
	}

	// v2.04 좌표 보정 
	if (dY < 100) dY = 100;
	if (dY > 600) dY = 600;

	// 게이트 서버 메시지 작성 
	ZeroMemory(cData, sizeof(cData));
	cp = (char*)cData;
	*cp = GSM_SETGUILDTELEPORTLOC;
	cp++;

	ip = (int*)cp;
	*ip = iGuildGUID;
	cp += 4;

	ip = (int*)cp;
	*ip = dX;
	cp += 4;

	ip = (int*)cp;
	*ip = dY;
	cp += 4;

	memcpy(cp, pMapName, 10);
	cp += 10;
	//

	dwTime = timeGetTime();

	// 먼저 같은 GUID를 가진 길드 텔레포트 좌표가 설정되어 있는지 찾는다.
	for (i = 0; i < DEF_MAXGUILDS; i++)
		if (m_pGuildTeleportLoc[i].m_iV1 == iGuildGUID) {
			// 이미 길드가 있다.
			if ((m_pGuildTeleportLoc[i].m_sDestX == dX) && (m_pGuildTeleportLoc[i].m_sDestY == dY) && (strcmp(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName) == 0)) {
				// 내용이 일치한다. 타임 입력후 스킵.
				m_pGuildTeleportLoc[i].m_dwTime = dwTime;
				return;
			}
			else {
				// 내용 갱신후 
				m_pGuildTeleportLoc[i].m_sDestX = dX;
				m_pGuildTeleportLoc[i].m_sDestY = dY;
				ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
				strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
				m_pGuildTeleportLoc[i].m_dwTime = dwTime;

				//게이트 서버를 통해 다른 서버로 정보 전송
				bStockMsgToGateServer(cData, 23);
				return;
			}
		}

	// 설정된 내용이 없다. 새로 설정한다.
	dwTemp = 0;
	iIndex = -1;
	for (i = 0; i < DEF_MAXGUILDS; i++) {
		if (m_pGuildTeleportLoc[i].m_iV1 == NULL) {

			m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
			m_pGuildTeleportLoc[i].m_sDestX = dX;
			m_pGuildTeleportLoc[i].m_sDestY = dY;
			ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
			strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
			m_pGuildTeleportLoc[i].m_dwTime = dwTime;

			//게이트 서버를 통해 다른 서버로 정보 전송  
			bStockMsgToGateServer(cData, 23);
			return;
		}
		else {
			// 가장 오랫동안 참조되지 않은 리스트의 인덱스를 찾는다.
			if (dwTemp < (dwTime - m_pGuildTeleportLoc[i].m_dwTime)) {
				dwTemp = (dwTime - m_pGuildTeleportLoc[i].m_dwTime);
				iIndex = i;
			}
		}
	}

	m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
	m_pGuildTeleportLoc[i].m_sDestX = dX;
	m_pGuildTeleportLoc[i].m_sDestY = dY;
	ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName));
	strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
	m_pGuildTeleportLoc[i].m_dwTime = dwTime;

	//게이트 서버를 통해 다른 서버로 정보 전송
	bStockMsgToGateServer(cData, 23);
}

// New 12/05/2004 Changed
void CGame::MeteorStrikeHandler(int iMapIndex)
{
	int i, ix, iy, dX, dY, iIndex, iTargetIndex, iTotalESG, iEffect;
	int iTargetArray[DEF_MAXSTRIKEPOINTS];
	short sOwnerH;
	char  cOwnerType;
	DWORD dwTime = timeGetTime();

	PutLogList("(!) Beginning Meteor Strike Procedure...");

	if (iMapIndex == -1) {
		PutLogList("(X) MeteorStrikeHandler Error! MapIndex -1!");
		return;
	}

	if (m_pMapList[iMapIndex] == NULL) {
		PutLogList("(X) MeteorStrikeHandler Error! NULL Map!");
		return;
	}

	if (m_pMapList[iMapIndex]->m_iTotalStrikePoints == 0) {
		PutLogList("(X) MeteorStrikeHandler Error! No Strike Points!");
		return;
	}

	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) iTargetArray[i] = -1;

	iIndex = 0;
	for (i = 1; i <= m_pMapList[iMapIndex]->m_iTotalStrikePoints; i++) {
		if (m_pMapList[iMapIndex]->m_stStrikePoint[i].iHP > 0) {
			iTargetArray[iIndex] = i; // 쩍쨘횈짰쨋처��횑횇짤 횈첨��횓횈짰��횉 ��횓쨉짝쩍쨘쨍짝 쨀횜쨈횂쨈횢.
			iIndex++;
		}
	}

	//testcode
	wsprintf(G_cTxt, "(!) Map(%s) has %d available strike points", m_pMapList[iMapIndex]->m_cName, iIndex);
	PutLogList(G_cTxt);

	// 째찼째첬 쨘쨍째챠쩔챘 쩍쨘횈짰쨌째횄챌 횇짭쨍짰쩐챤
	m_stMeteorStrikeResult.iCasualties = 0;
	m_stMeteorStrikeResult.iCrashedStructureNum = 0;
	m_stMeteorStrikeResult.iStructureDamageAmount = 0;

	if (iIndex == 0) {
		// 횈첩째횦횉횘 째횉쨔째��횑 쩐첩쨈횢. 쨍챨쨉횓 횈횆짹짬쨉횉쩐첬쨈횢.
		PutLogList("(!) No strike points!");
		bRegisterDelayEvent(DEF_DELAYEVENTTYPE_CALCMETEORSTRIKEEFFECT, NULL, dwTime + 6000, NULL, NULL, iMapIndex, NULL, NULL, NULL, NULL, NULL);
	}
	else {

		// 횉횠쨈챌 쨍횎��횉 횇짭쨋처��횑쩐챨횈짰쨉챕쩔징째횚 쨍횧횇횞쩔�� 째첩째횦 횊쩔째첬쨍짝 쨘쨍쩔짤횁횜쨋처쨈횂 쨍횧쩍횄횁철 ��체쩌횤
		for (i = 1; i < DEF_MAXCLIENTS; i++)
			if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE) && (m_pClientList[i]->m_cMapIndex == iMapIndex)) {
				SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKEHIT, NULL, NULL, NULL, NULL);
			}

		for (i = 0; i < iIndex; i++) {
			// 쨍챨쨉챌 횈첩째횦 쨍챰횉짜쩔징 쨈챘횉횠 쨉쩔��횕횉횗 째첩째횦��쨩 째징횉횗쨈횢.
			iTargetIndex = iTargetArray[i];

			if (iTargetIndex == -1) {
				PutLogList("(X) Strike Point MapIndex: -1!");
				goto MSH_SKIP_STRIKE;
			}

			dX = m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].dX;
			dY = m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].dY;

			// dX, dY ��짠횆징 횁횜��짠쩔징 횄횜쩌횘 2째쨀 ��횑쨩처��횉 Energy Shield Generator째징 횁쨍��챌횉횕쨍챕 쩍쨘횈짰쨋처��횑횇짤 횈첨��횓횈짰쨈횂 쨔짬쨩챌횉횕쨈횢. 짹횞쨌짱쨀짧 1째쨀 ��횑횉횕��횑쨍챕 째첩째횦쨔횧쩐횘��쨩쨋짠 HP째징 횁횢쩐챤쨉챌쨈횢.
			// NPC 횁횜쨘짱쩔징 ��횜쨈횂 ��청 횆쨀쨍짱횇횒쨍짝 횇쩍횁철횉횠 째챈쨘쨍쨍짝 쩔챦쨍째쨈횢.
			iTotalESG = 0;
			for (ix = dX - 10; ix <= dX + 10; ix++)
				for (iy = dY - 10; iy <= dY + 10; iy++) {
					m_pMapList[iMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
					if ((cOwnerType == DEF_OWNERTYPE_NPC) && (m_pNpcList[sOwnerH] != NULL) && (m_pNpcList[sOwnerH]->m_sType == 40)) {
						iTotalESG++;
					}
				}

			// testcode
			wsprintf(G_cTxt, "(!) Meteor Strike Target(%d, %d) ESG(%d)", dX, dY, iTotalESG);
			PutLogList(G_cTxt);

			if (iTotalESG < 2) {

				m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iHP -= (2 - iTotalESG);
				if (m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iHP <= 0) {
					// 째횉쨔째��횑 횈횆짹짬쨉횉쩐첬쨈횢.
					m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iHP = 0;
					// 째횉쨔째 짹창쨈횋 쨩처쩍횉
					m_pMapList[m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iMapIndex]->m_bIsDisabled = TRUE;
					m_stMeteorStrikeResult.iCrashedStructureNum++;
				}
				else {
					// 째횉쨔째��횑 쨈챘쨔횑횁철쨍짝 쩐챵쩐첬쨈횢.
					m_stMeteorStrikeResult.iStructureDamageAmount += (2 - iTotalESG);
					// 째횉쨔째 쨈챘쨔횑횁철 ��횚��쨘 횊횆 쨘횘횇쨍쨈횂 ��횑쨔횑횁철 쨩챨��횚 
					iEffect = iDice(1, 5) - 1;
					iAddDynamicObjectList(NULL, DEF_OWNERTYPE_PLAYER_INDIRECT, DEF_DYNAMICOBJECT_FIRE2, iMapIndex,
						m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iEffectX[iEffect] + (iDice(1, 3) - 2),
						m_pMapList[iMapIndex]->m_stStrikePoint[iTargetIndex].iEffectY[iEffect] + (iDice(1, 3) - 2), 60 * 1000 * 50);
				}
			}
		MSH_SKIP_STRIKE:;
		}

		// 1횄횎 횊횆 쨍횧횇횞쩔�� 쩍쨘횈짰쨋처��횑횇짤 째첩째횦 쨈챘쨔횑횁철 횊쩔째첬
		bRegisterDelayEvent(DEF_DELAYEVENTTYPE_DOMETEORSTRIKEDAMAGE, NULL, dwTime + 1000, NULL, NULL, iMapIndex, NULL, NULL, NULL, NULL, NULL);
		// 4횄횎 횊횆 쨍횧횇횞쩔�� 쩍쨘횈짰쨋처��횑횇짤 째첩째횦 쨈챘쨔횑횁철 횊쩔째첬
		bRegisterDelayEvent(DEF_DELAYEVENTTYPE_DOMETEORSTRIKEDAMAGE, NULL, dwTime + 4000, NULL, NULL, iMapIndex, NULL, NULL, NULL, NULL, NULL);
		// 6횄횎 횊횆 째첩째횦 째찼째첬 횈횉쨈횥.
		bRegisterDelayEvent(DEF_DELAYEVENTTYPE_CALCMETEORSTRIKEEFFECT, NULL, dwTime + 6000, NULL, NULL, iMapIndex, NULL, NULL, NULL, NULL, NULL);
	}
}

void CGame::CalcMeteorStrikeEffectHandler(int iMapIndex)
{
	int i, iActiveStructure, iStructureHP[DEF_MAXSTRIKEPOINTS];
	char* cp, * cp2, cData[120], cWinnerSide, cTempData[120];
	WORD* wp;

	if (m_bIsCrusadeMode == FALSE) return;
	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) iStructureHP[i] = 0;
	iActiveStructure = 0;
	for (i = 1; i <= m_pMapList[iMapIndex]->m_iTotalStrikePoints; i++) {
		if (m_pMapList[iMapIndex]->m_stStrikePoint[i].iHP > 0) {
			iActiveStructure++;
			iStructureHP[i] = m_pMapList[iMapIndex]->m_stStrikePoint[i].iHP;
		}
	}
	wsprintf(G_cTxt, "ActiveStructure:%d  MapIndex:%d AresdenMap:%d ElvineMap:%d", iActiveStructure, iMapIndex, m_iAresdenMapIndex, m_iElvineMapIndex);
	PutLogList(G_cTxt);
	if (iActiveStructure == 0) {
		if (iMapIndex == m_iAresdenMapIndex) {
			cWinnerSide = 2;
			LocalEndCrusadeMode(2);
		}
		else if (iMapIndex == m_iElvineMapIndex) {
			cWinnerSide = 1;
			LocalEndCrusadeMode(1);
		}
		else {
			cWinnerSide = 0;
			LocalEndCrusadeMode(0);
		}

		ZeroMemory(cData, sizeof(cData));
		cp = (char*)(cData);
		*cp = GSM_ENDCRUSADE;
		cp++;

		*cp = cWinnerSide;
		cp++;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iCrashedStructureNum;
		cp += 2;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iStructureDamageAmount;
		cp += 2;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iCasualties;
		cp += 2;

		memcpy(cp, m_pMapList[iMapIndex]->m_cName, 10);
		cp += 10;

		bStockMsgToGateServer(cData, 18);
	}
	else {
		ZeroMemory(cData, sizeof(cData));
		cp = (char*)(cData);
		*cp = GSM_GRANDMAGICRESULT;
		cp++;

		memcpy(cp, m_pMapList[iMapIndex]->m_cName, 10);
		cp += 10;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iCrashedStructureNum;
		cp += 2;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iStructureDamageAmount;
		cp += 2;

		wp = (WORD*)cp;
		*wp = m_stMeteorStrikeResult.iCasualties;
		cp += 2;

		wp = (WORD*)cp;
		*wp = (WORD)iActiveStructure;
		cp += 2;

		ZeroMemory(cTempData, sizeof(cTempData));
		cp2 = (char*)(cTempData);

		wp = (WORD*)cp2;
		*wp = (WORD)m_pMapList[iMapIndex]->m_iTotalStrikePoints;
		cp2 += 2;

		for (i = 1; i <= m_pMapList[iMapIndex]->m_iTotalStrikePoints;i++) {
			wp = (WORD*)cp2;
			*wp = (WORD)iStructureHP[i];
			cp2 += 2;
		}
		memcpy(cp, cTempData, (m_pMapList[iMapIndex]->m_iTotalStrikePoints * 2) + 2);
		bStockMsgToGateServer(cData, (m_pMapList[iMapIndex]->m_iTotalStrikePoints * 2) + 20);
		GrandMagicResultHandler(m_pMapList[iMapIndex]->m_cName, m_stMeteorStrikeResult.iCrashedStructureNum, m_stMeteorStrikeResult.iStructureDamageAmount, m_stMeteorStrikeResult.iCasualties, iActiveStructure, m_pMapList[iMapIndex]->m_iTotalStrikePoints, cTempData);
	}
	m_stMeteorStrikeResult.iCasualties = 0;
	m_stMeteorStrikeResult.iCrashedStructureNum = 0;
	m_stMeteorStrikeResult.iStructureDamageAmount = 0;
}

void CGame::LocalEndCrusadeMode(int iWinnerSide)
{
	int i, n;

	if (m_bIsCrusadeMode == FALSE) return;

	m_bIsCrusadeMode = FALSE;
	PutLogList("(!)Crusade Mode OFF.");

	for (n = 0; n < DEF_MAXNPCS; n++) {
		if (m_pNpcList[n] != NULL) {
			switch (m_pNpcList[n]->m_sType) {
			case 36:
			case 37:
			case 38:
			case 39:
			case 40:
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
			case 51:
				NpcKilledHandler(NULL, NULL, n, 0);//RemoveEventNpc(n);
				break;
			}
		}
	}

	_CreateCrusadeGUID(m_dwCrusadeGUID, iWinnerSide);
	m_iCrusadeWinnerSide = iWinnerSide;
	m_iLastCrusadeWinner = iWinnerSide;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
			m_pClientList[i]->m_iCrusadeDuty = 0;
			m_pClientList[i]->m_iConstructionPoint = 0;
			m_pClientList[i]->m_iTimeLeft_ForceRecall = 0;
			SendNotifyMsg(NULL, i, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, NULL, NULL, NULL, m_iCrusadeWinnerSide);
		}

	if (iWinnerSide == 2) {
		_bCrusadeLog(DEF_CRUSADELOG_ENDCRUSADE, FALSE, FALSE, "Elvine Win!");
	}
	else if (iWinnerSide == 1) {
		_bCrusadeLog(DEF_CRUSADELOG_ENDCRUSADE, FALSE, FALSE, "Aresden Win!");
	}
	else {
		_bCrusadeLog(DEF_CRUSADELOG_ENDCRUSADE, FALSE, FALSE, "Draw!");
	}
}

void CGame::SendCollectedMana()
{
	char* cp, cData[120];
	WORD* wp;

	// 모인 마나가 없다면 메시지 전송하지 않는다. 마나 스톤이 없는 맵에서 메시지를 전송하면 안된다.
	if ((m_iCollectedMana[1] == 0) && (m_iCollectedMana[2] == 0)) return;

	ZeroMemory(cData, sizeof(cData));
	cp = (char*)(cData);
	*cp = GSM_COLLECTEDMANA;
	cp++;

	wp = (WORD*)cp;
	*wp = (WORD)m_iCollectedMana[1];
	cp += 2;

	wp = (WORD*)cp;
	*wp = (WORD)m_iCollectedMana[2];
	cp += 2;

	CollectedManaHandler(m_iCollectedMana[1], m_iCollectedMana[2]);

	bStockMsgToGateServer(cData, 5);

	// 그동안 모은 마나량 보내고 클리어.
	m_iCollectedMana[0] = 0;
	m_iCollectedMana[1] = 0;
	m_iCollectedMana[2] = 0;
}

void CGame::CollectedManaHandler(WORD wAresdenMana, WORD wElvineMana)
{
	if (m_iAresdenMapIndex != -1) {
		m_iAresdenMana += wAresdenMana;

	}

	if (m_iElvineMapIndex != -1) {
		m_iElvineMana += wElvineMana;

	}
}

void CGame::_LinkStrikePointMapIndex()
{
	int i, z, x;

	// 마을과 건물 내부를 다른 서버에 띄우면 링크가 불가능하므로 다운된다!
	for (i = 0; i < DEF_MAXMAPS; i++)
		if ((m_pMapList[i] != NULL) && (m_pMapList[i]->m_iTotalStrikePoints != 0)) {
			// 스트라이크 포인트가 정의된 맵이다. 각각의 스트라이크 포인트와 연계된 맵의 인덱스를 구해 저장한다.
			for (z = 0; z < DEF_MAXSTRIKEPOINTS; z++)
				if (strlen(m_pMapList[i]->m_stStrikePoint[z].cRelatedMapName) != 0) {
					for (x = 0; x < DEF_MAXMAPS; x++)
						if ((m_pMapList[x] != NULL) && (strcmp(m_pMapList[x]->m_cName, m_pMapList[i]->m_stStrikePoint[z].cRelatedMapName) == 0)) {
							// 인덱스를 구했다. 저장한다.
							m_pMapList[i]->m_stStrikePoint[z].iMapIndex = x;
							//testcode
							wsprintf(G_cTxt, "(!) Map(%s) Strike Point(%d) Related Map(%s) Index(%d)", m_pMapList[i]->m_cName, z, m_pMapList[i]->m_stStrikePoint[z].cRelatedMapName, x);
							PutLogList(G_cTxt);

							break;
						}
				}
		}
}

//New Changed 11/05/2004
void CGame::GrandMagicResultHandler(char* cMapName, int iCrashedStructureNum, int iStructureDamageAmount, int iCasualities, int iActiveStructure, int iTotalStrikePoints, char* cData)
{
	int i;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if (m_pClientList[i] != NULL) {
			SendNotifyMsg(NULL, i, DEF_NOTIFY_GRANDMAGICRESULT, iCrashedStructureNum, iStructureDamageAmount, iCasualities, cMapName, iActiveStructure, NULL, NULL, NULL, NULL, iTotalStrikePoints, cData);
		}
}

// October 19, 2004 - 3.51 translated
void CGame::_GrandMagicLaunchMsgSend(int iType, char cAttackerSide)
{
	char* cp, cBuff[120];
	WORD* wp;

	ZeroMemory(cBuff, sizeof(cBuff));
	cp = (char*)cBuff;
	*cp = GSM_GRANDMAGICLAUNCH;
	cp++;

	wp = (WORD*)cp;
	*wp = (WORD)iType;
	cp += 2;

	wp = (WORD*)cp;
	*wp = (WORD)cAttackerSide;
	cp += 2;

	bStockMsgToGateServer(cBuff, 5);
}

// October 19, 2004 - 3.51 translated
BOOL CGame::_bNpcBehavior_ManaCollector(int iNpcH)
{
	int dX, dY, iMaxMP, iTotal;
	short sOwnerH;
	char  cOwnerType;
	double dV1, dV2, dV3;
	BOOL bRet;

	if (m_pNpcList[iNpcH] == NULL) return FALSE;
	if (m_pNpcList[iNpcH]->m_sAppr2 != 0) return FALSE;

	bRet = FALSE;
	for (dX = m_pNpcList[iNpcH]->m_sX - 5; dX <= m_pNpcList[iNpcH]->m_sX + 5; dX++)
		for (dY = m_pNpcList[iNpcH]->m_sY - 5; dY <= m_pNpcList[iNpcH]->m_sY + 5; dY++) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);
			if (sOwnerH != NULL) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pNpcList[iNpcH]->m_cSide == m_pClientList[sOwnerH]->m_cSide) {
						iMaxMP = (2 * (m_pClientList[sOwnerH]->m_iMag + m_pClientList[sOwnerH]->m_iAngelicMag)) + (2 * (m_pClientList[sOwnerH]->m_iLevel)) + ((m_pClientList[sOwnerH]->m_iInt + m_pClientList[sOwnerH]->m_iAngelicInt) / 2);
						if (m_pClientList[sOwnerH]->m_iMP < iMaxMP) {
							iTotal = iDice(1, (m_pClientList[sOwnerH]->m_iMag + m_pClientList[sOwnerH]->m_iAngelicMag));
							if (m_pClientList[sOwnerH]->m_iAddMP != 0) {
								dV2 = (double)iTotal;
								dV3 = (double)m_pClientList[sOwnerH]->m_iAddMP;
								dV1 = (dV3 / 100.0f) * dV2;
								iTotal += (int)dV1;
							}

							m_pClientList[sOwnerH]->m_iMP += iTotal;

							if (m_pClientList[sOwnerH]->m_iMP > iMaxMP)
								m_pClientList[sOwnerH]->m_iMP = iMaxMP;

							SendNotifyMsg(NULL, sOwnerH, DEF_NOTIFY_MP, NULL, NULL, NULL, NULL);
						}
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if ((m_pNpcList[sOwnerH]->m_sType == 42) && (m_pNpcList[sOwnerH]->m_iV1 > 0)) {
						if (m_pNpcList[sOwnerH]->m_iV1 >= 3) {
							m_iCollectedMana[m_pNpcList[iNpcH]->m_cSide] += 3;
							m_pNpcList[sOwnerH]->m_iV1 -= 3;
							bRet = TRUE;
						}
						else {
							m_iCollectedMana[m_pNpcList[iNpcH]->m_cSide] += m_pNpcList[sOwnerH]->m_iV1;
							m_pNpcList[sOwnerH]->m_iV1 = 0;
							bRet = TRUE;
						}
					}
					break;
				}
			}
		}
	return bRet;
}

// October 19, 2004 - 3.51 translated
void CGame::MeteorStrikeMsgHandler(char cAttackerSide)
{
	int i;
	DWORD dwTime = timeGetTime();

	switch (cAttackerSide) {
	case 1:
		if (m_iElvineMapIndex != -1) {
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
					if (strcmp(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_cLocationName, "elvine") == 0) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 1, NULL, NULL, NULL);
					}
					else {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 2, NULL, NULL, NULL);
					}
				}
			bRegisterDelayEvent(DEF_DELAYEVENTTYPE_METEORSTRIKE, NULL, dwTime + 5000, NULL, NULL, m_iElvineMapIndex, NULL, NULL, NULL, NULL, NULL);
		}
		else {
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if (m_pClientList[i] != NULL) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 2, NULL, NULL, NULL);
				}
		}
		break;

	case 2:
		if (m_iAresdenMapIndex != -1) {
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_bIsInitComplete == TRUE)) {
					if (strcmp(m_pMapList[m_pClientList[i]->m_cMapIndex]->m_cLocationName, "aresden") == 0) {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 3, NULL, NULL, NULL);
					}
					else {
						SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 4, NULL, NULL, NULL);
					}
				}
			bRegisterDelayEvent(DEF_DELAYEVENTTYPE_METEORSTRIKE, NULL, dwTime + 1000 * 5, NULL, NULL, m_iAresdenMapIndex, NULL, NULL, NULL, NULL, NULL);
		}
		else {
			for (i = 1; i < DEF_MAXCLIENTS; i++)
				if (m_pClientList[i] != NULL) {
					SendNotifyMsg(NULL, i, DEF_NOTIFY_METEORSTRIKECOMING, 4, NULL, NULL, NULL);
				}
		}
		break;
	}
}

// October 19, 2004 - 3.51 translated
void CGame::_NpcBehavior_GrandMagicGenerator(int iNpcH)
{
	switch (m_pNpcList[iNpcH]->m_cSide) {
	case 1:
		if (m_iAresdenMana > DEF_GMGMANACONSUMEUNIT) {
			m_iAresdenMana = 0;
			m_pNpcList[iNpcH]->m_iManaStock++;
			if (m_pNpcList[iNpcH]->m_iManaStock > m_pNpcList[iNpcH]->m_iMaxMana) {
				_GrandMagicLaunchMsgSend(1, 1);
				MeteorStrikeMsgHandler(1);
				m_pNpcList[iNpcH]->m_iManaStock = 0;
				m_iAresdenMana = 0;
			}
		}
		break;

	case 2:
		if (m_iElvineMana > DEF_GMGMANACONSUMEUNIT) {
			m_iElvineMana = 0;
			m_pNpcList[iNpcH]->m_iManaStock++;
			if (m_pNpcList[iNpcH]->m_iManaStock > m_pNpcList[iNpcH]->m_iMaxMana) {
				_GrandMagicLaunchMsgSend(1, 2);
				MeteorStrikeMsgHandler(2);
				m_pNpcList[iNpcH]->m_iManaStock = 0;
				m_iElvineMana = 0;
			}
		}
		break;
	}
}

// October 19, 2004 - 3.51 translated
BOOL CGame::_bNpcBehavior_Detector(int iNpcH)
{
	int dX, dY;
	short sOwnerH;
	char  cOwnerType, cSide;
	BOOL  bFlag = FALSE;

	if (m_pNpcList[iNpcH] == NULL) return FALSE;
	if (m_pNpcList[iNpcH]->m_sAppr2 != 0) return FALSE;

	for (dX = m_pNpcList[iNpcH]->m_sX - 10; dX <= m_pNpcList[iNpcH]->m_sX + 10; dX++)
		for (dY = m_pNpcList[iNpcH]->m_sY - 10; dY <= m_pNpcList[iNpcH]->m_sY + 10; dY++) {
			m_pMapList[m_pNpcList[iNpcH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, dX, dY);

			cSide = 0;
			if (sOwnerH != NULL) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					cSide = m_pClientList[sOwnerH]->m_cSide;
					break;

				case DEF_OWNERTYPE_NPC:
					cSide = m_pNpcList[sOwnerH]->m_cSide;
					break;
				}
			}

			if ((cSide != 0) && (cSide != m_pNpcList[iNpcH]->m_cSide)) {
				switch (cOwnerType) {
				case DEF_OWNERTYPE_PLAYER:
					if (m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != NULL) {
						m_pClientList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = NULL;
						SetInvisibilityFlag(sOwnerH, cOwnerType, FALSE);
					}
					break;

				case DEF_OWNERTYPE_NPC:
					if (m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] != NULL) {
						m_pNpcList[sOwnerH]->m_cMagicEffectStatus[DEF_MAGICTYPE_INVISIBILITY] = NULL;
						SetInvisibilityFlag(sOwnerH, cOwnerType, FALSE);
					}
					break;
				}

				bFlag = TRUE;
			}
		}

	return bFlag;
}

BOOL CGame::__bSetConstructionKit(int iMapIndex, int dX, int dY, int iType, int iTimeCost, int iClientH)
{
	int iNamingValue, ix, iy, tX, tY;
	char cNpcName[21], cName[21], cNpcWaypoint[11], cOwnerType;
	short sOwnerH;

	// 횇짤쨌챌쩌쩌��횑쨉책 쨍챨쨉책째징 쩐횈쨈횕째횇쨀짧 째횉쩌쨀횉횗 쨩챌쨋첨��횑 째첩쨘쨈��횑 쩐횈쨈횕쨍챕 쨔짬쩍횄.
	if ((m_bIsCrusadeMode == FALSE) || (m_pClientList[iClientH]->m_iCrusadeDuty != 2)) return FALSE;
	if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_iTotalCrusadeStructures >= DEF_MAXCRUSADESTRUCTURES) {
		// 횉횠쨈챌 쨍횎쩔징 횇짤쨌챌쩌쩌��횑쨉책 째횉쨔째 째쨀쩌철 횁짝횉횗쩔징 째횋쨍짰횁철 쩐횎쨈횂쨈횢쨍챕
		SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_NOMORECRUSADESTRUCTURE, NULL, NULL, NULL, NULL);
		return FALSE;
	}

	// 횉횠쨈챌 ��짠횆징쩔징 째횉횄횪쨔째 NPC쨍짝 쨩첵쩌쨘.
	iNamingValue = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();
	if (iNamingValue != -1) {
		// 쨈천��횑쨩처 ��횑 쨍횎쩔징 NPC쨍짝 쨍쨍쨉챕쩌철 쩐첩쨈횢. ��횑쨍짠��쨩 횉횘쨈챌횉횘 쩌철 쩐첩짹창 쨋짠쨔짰.


		// 쨍횛��첬 쩌쨀횆징횉횕째챠��횣 횉횕쨈횂 짹횢횄쨀쩔징 짹쨍횁쨋쨔째��횑 쩐첩쨀짧 횊짰��횓횉횗쨈횢.
		for (ix = dX - 3; ix <= dX + 5; ix++)
			for (iy = dY - 3; iy <= dX + 5; iy++) {
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
				if ((sOwnerH != NULL) && (cOwnerType == DEF_OWNERTYPE_NPC) && (m_pNpcList[sOwnerH]->m_cActionLimit == 5)) return FALSE;
			}

		// NPC쨍짝 쨩첵쩌쨘횉횗쨈횢.
		ZeroMemory(cNpcName, sizeof(cNpcName));
		if (m_pClientList[iClientH]->m_cSide == 1) {
			switch (iType) {
			case 1: strcpy(cNpcName, "AGT-Aresden"); break;
			case 2: strcpy(cNpcName, "CGT-Aresen"); break;
			case 3: strcpy(cNpcName, "MS-Aresden"); break;
			case 4: strcpy(cNpcName, "DT-Aresden"); break;
			}
		}
		else if (m_pClientList[iClientH]->m_cSide == 2) {
			switch (iType) {
			case 1: strcpy(cNpcName, "AGT-Elvine"); break;
			case 2: strcpy(cNpcName, "CGT-Elvine"); break;
			case 3: strcpy(cNpcName, "MS-Elvine"); break;
			case 4: strcpy(cNpcName, "DT-Elvine"); break;
			}
		}


		ZeroMemory(cName, sizeof(cName));
		wsprintf(cName, "XX%d", iNamingValue);
		cName[0] = '_';
		cName[1] = m_pClientList[iClientH]->m_cMapIndex + 65;

		ZeroMemory(cNpcWaypoint, sizeof(cNpcWaypoint));

		tX = (int)dX;
		tY = (int)dY;
		if (bCreateNewNpc(cNpcName, cName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 0, (rand() % 9),
			DEF_MOVETYPE_RANDOM, &tX, &tY, cNpcWaypoint, NULL, NULL, -1, FALSE, FALSE) == FALSE) {
			// 쩍횉횈횖횉횩��쨍쨔횉쨌횓 쩔쨔쩐횪쨉횊 NameValue쨍짝 횉횠횁짝쩍횄횇짼쨈횢.
			m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
		}
		else {
			// 쩌쨘째첩
			wsprintf(G_cTxt, "Structure(%s) construction begin(%d,%d)!", cNpcName, tX, tY);
			PutLogList(G_cTxt);
			return TRUE;
		}
	}

	return FALSE;
}

void CGame::RequestSetGuildConstructLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char* pMapName)
{
	char* cp, cData[120];
	int i;
	int* ip, iIndex;
	DWORD dwTemp, dwTime;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsOnServerChange == TRUE) return;

	// 째횚��횑횈짰 쩌짯쨔철 쨍횧쩍횄횁철 ��횤쩌쨘 
	ZeroMemory(cData, sizeof(cData));
	cp = (char*)cData;
	*cp = GSM_SETGUILDCONSTRUCTLOC;
	cp++;

	ip = (int*)cp;
	*ip = iGuildGUID;
	cp += 4;

	ip = (int*)cp;
	*ip = dX;
	cp += 4;

	ip = (int*)cp;
	*ip = dY;
	cp += 4;

	memcpy(cp, pMapName, 10);
	cp += 10;
	//

	dwTime = timeGetTime();



	// 쨍횛��첬 째째��쨘 GUID쨍짝 째징횁첩 짹챈쨉책 횆횁쩍쨘횈짰쨌째횈짰 횁횂횉짜째징 쩌쨀횁짚쨉횉쩐챤 ��횜쨈횂횁철 횄짙쨈횂쨈횢. 
	// 횇횣쨌쨔횈첨횈짰 ��짠횆징��횉 2쨔첩 쨘짱쩌철쨉챕��쨩 쨩챌쩔챘횉횗쨈횢.
	for (i = 0; i < DEF_MAXGUILDS; i++)
		if (m_pGuildTeleportLoc[i].m_iV1 == iGuildGUID) {
			// ��횑쨔횑 짹챈쨉책째징 ��횜쨈횢.
			if ((m_pGuildTeleportLoc[i].m_sDestX2 == dX) && (m_pGuildTeleportLoc[i].m_sDestY2 == dY) && (strcmp(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName) == 0)) {
				// 쨀쨩쩔챘��횑 ��횕횆징횉횗쨈횢. 횇쨍��횙 ��횚쨌횂횊횆 쩍쨘횇쨉.
				m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;
				return;
			}
			else {
				// 쨀쨩쩔챘 째쨩쩍횇횊횆 
				m_pGuildTeleportLoc[i].m_sDestX2 = dX;
				m_pGuildTeleportLoc[i].m_sDestY2 = dY;
				ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName2));
				strcpy(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName);
				m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;

				//째횚��횑횈짰 쩌짯쨔철쨍짝 횇챘횉횠 쨈횢쨍짜 쩌짯쨔철쨌횓 횁짚쨘쨍 ��체쩌횤
				bStockMsgToGateServer(cData, 23);
				return;
			}
		}

	// 쩌쨀횁짚쨉횊 쨀쨩쩔챘��횑 쩐첩쨈횢. 쨩천쨌횓 쩌쨀횁짚횉횗쨈횢.
	dwTemp = 0;
	iIndex = -1;
	for (i = 0; i < DEF_MAXGUILDS; i++) {
		if (m_pGuildTeleportLoc[i].m_iV1 == NULL) {

			m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
			m_pGuildTeleportLoc[i].m_sDestX2 = dX;
			m_pGuildTeleportLoc[i].m_sDestY2 = dY;
			ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName2));
			strcpy(m_pGuildTeleportLoc[i].m_cDestMapName2, pMapName);
			m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;

			//째횚��횑횈짰 쩌짯쨔철쨍짝 횇챘횉횠 쨈횢쨍짜 쩌짯쨔철쨌횓 횁짚쨘쨍 ��체쩌횤  
			bStockMsgToGateServer(cData, 23);
			return;
		}
		else {
			// 째징��책 쩔��쨌짠쨉쩔쩐횊 횂체횁쨋쨉횉횁철 쩐횎��쨘 쨍짰쩍쨘횈짰��횉 ��횓쨉짝쩍쨘쨍짝 횄짙쨈횂쨈횢.
			if (dwTemp < (dwTime - m_pGuildTeleportLoc[i].m_dwTime2)) {
				dwTemp = (dwTime - m_pGuildTeleportLoc[i].m_dwTime2);
				iIndex = i;
			}
		}
	}

	m_pGuildTeleportLoc[i].m_iV1 = iGuildGUID;
	m_pGuildTeleportLoc[i].m_sDestX2 = dX;
	m_pGuildTeleportLoc[i].m_sDestY2 = dY;
	ZeroMemory(m_pGuildTeleportLoc[i].m_cDestMapName2, sizeof(m_pGuildTeleportLoc[i].m_cDestMapName2));
	strcpy(m_pGuildTeleportLoc[i].m_cDestMapName, pMapName);
	m_pGuildTeleportLoc[i].m_dwTime2 = dwTime;

	//째횚��횑횈짰 쩌짯쨔철쨍짝 횇챘횉횠 쨈횢쨍짜 쩌짯쨔철쨌횓 횁짚쨘쨍 ��체쩌횤
	bStockMsgToGateServer(cData, 23);
}

// New 14/05/2004 Changed
void CGame::RequestSummonWarUnitHandler(int iClientH, int dX, int dY, char cType, char cNum, char cMode)
{
	char cName[6], cNpcName[21], cMapName[11], cNpcWayPoint[11], cOwnerType;
	int i, x;
	int iNamingValue, tX, tY, ix, iy;
	BOOL bRet;
	short sOwnerH;
	DWORD dwTime = timeGetTime();

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_bIsInitComplete == FALSE) return;

	ZeroMemory(cNpcWayPoint, sizeof(cNpcWayPoint));
	ZeroMemory(cNpcName, sizeof(cNpcName));
	ZeroMemory(cMapName, sizeof(cMapName));

	// 쩔징쨌짱 횄쩌횇짤쩔챘 
	if (cType < 0) return;
	if (cType >= DEF_MAXNPCTYPES) return;
	if (cNum > 10) return;

	// 째횉쩌쨀횉횕짹창쩔징 횈첨��횓횈짰째징 쨍챨��횣쨋천쨈횢.
	if (m_pClientList[iClientH]->m_iConstructionPoint < m_iNpcConstructionPoint[cType]) return;
	// 째횉쨔째 쨀쨩쨘횓쨍챕 ��체��챦 ��짱쨈횕횈짰 쩌횘횊짱 쨘횘째징.
	if ((m_pMapList[m_pClientList[iClientH]->m_cMapIndex] != NULL) && (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_bIsFixedDayMode == TRUE)) return;

	// ��횕쨈횥 쩔징쨌짱쨔챈횁철쩔챘
	cNum = 1;

	// ConstructionPoint 횁짝횉횗��쨩 째챔쨩챗횉횕째챠 ��짱쨈횕횈짰 째쨀쩌철쨍쨍횇짯 횁횢��횓쨈횢.
	for (x = 1; x <= cNum; x++) {
		// 째쨀쩌철쨍쨍횇짯  ��체��챦 ��짱쨈횕횈짰 쨩첵쩌쨘 
		iNamingValue = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->iGetEmptyNamingValue();
		if (iNamingValue != -1) {
			// 쨈천��횑쨩처 ��횑 쨍횎쩔징 NPC쨍짝 쨍쨍쨉챕쩌철 쩐첩쨈횢. ��횑쨍짠��쨩 횉횘쨈챌횉횘 쩌철 쩐첩짹창 쨋짠쨔짰.
			// ��횑쨌짹 ��횕��횑?

			// NPC쨍짝 쨩첵쩌쨘횉횗쨈횢.
			ZeroMemory(cName, sizeof(cName));
			wsprintf(cName, "XX%d", iNamingValue);
			cName[0] = '_';
			cName[1] = m_pClientList[iClientH]->m_cMapIndex + 65;

			// 쨉쩔��횕횉횗 횇쨍��횚��쨩 째짰횁철쨍쨍 쨈횢쨍짜 쨩챌��횑쨉책쨍짝 째짰쨈횂 째챈쩔챙 

			switch (cType) {
			case 43: // Light War Beetle
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "LWB-Aresden"); break;
				case 2: strcpy(cNpcName, "LWB-Elvine"); break;
				}
				break;

			case 36: // Arrow Guard Tower
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "AGT-Aresden"); break;
				case 2: strcpy(cNpcName, "AGT-Elvine"); break;
				}
				break;

			case 37: // Cannon Guard Tower
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "CGT-Aresden"); break;
				case 2: strcpy(cNpcName, "CGT-Elvine"); break;
				}
				break;

			case 38: // Mana Collector
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "MS-Aresden"); break;
				case 2: strcpy(cNpcName, "MS-Elvine"); break;
				}
				break;

			case 39: // Detector
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "DT-Aresden"); break;
				case 2: strcpy(cNpcName, "DT-Elvine"); break;
				}
				break;

			case 51: // Catapult
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "CP-Aresden"); break;
				case 2: strcpy(cNpcName, "CP-Elvine"); break;
				}
				break;

			case 44:
				strcpy(cNpcName, "GHK");
				break;

			case 45:
				strcpy(cNpcName, "GHKABS");
				break;

			case 46:
				strcpy(cNpcName, "TK");
				break;

			case 47:
				strcpy(cNpcName, "BG");
				break;

			case 82:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "Sor-Aresden"); break;
				case 2: strcpy(cNpcName, "Sor-Elvine"); break;
				}
				break;

			case 83:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "ATK-Aresden"); break;
				case 2: strcpy(cNpcName, "ATK-Elvine"); break;
				}
				break;

			case 84:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "Elf-Aresden"); break;
				case 2: strcpy(cNpcName, "Elf-Elvine"); break;
				}
				break;

			case 85:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "DSK-Aresden"); break;
				case 2: strcpy(cNpcName, "DSK-Elvine"); break;
				}
				break;

			case 86:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "HBT-Aresden"); break;
				case 2: strcpy(cNpcName, "HBT-Elvine"); break;
				}
				break;

			case 87:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "CT-Aresden"); break;
				case 2: strcpy(cNpcName, "CT-Elvine"); break;
				}
				break;

			case 88:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "Bar-Aresden"); break;
				case 2: strcpy(cNpcName, "Bar-Elvine"); break;
				}
				break;

			case 89:
				switch (m_pClientList[iClientH]->m_cSide) {
				case 1: strcpy(cNpcName, "AGC-Aresden"); break;
				case 2: strcpy(cNpcName, "AGC-Elvine"); break;
				}
				break;
			}

			//testcode
			wsprintf(G_cTxt, "(!) Request Summon War Unit (%d) (%s)", cType, cNpcName);
			PutLogList(G_cTxt);

			tX = (int)dX;
			tY = (int)dY;

			// 쨍쨍쩐횪 ��체��챦 째횉횄횪쨔째��횑쨋처쨍챕 째횉횄횪 ��짠횆징쨌횓쨘횓횇횒 ��횓횁짖횉횠쩐횩 횉횗쨈횢.
			bRet = FALSE;
			switch (cType) {
			case 36:
			case 37:
			case 38:
			case 39:
				// 째횉쩌쨀 ��짠횆징쨍짝 쨘챰짹쨀
				if (strcmp(m_pClientList[iClientH]->m_cConstructMapName, m_pClientList[iClientH]->m_cMapName) != 0) bRet = TRUE;
				if (abs(m_pClientList[iClientH]->m_sX - m_pClientList[iClientH]->m_iConstructLocX) > 10) bRet = TRUE;
				if (abs(m_pClientList[iClientH]->m_sY - m_pClientList[iClientH]->m_iConstructLocY) > 10) bRet = TRUE;

				if (bRet == TRUE) {
					// 째횉쩌쨀 ��짠횆징쩔횒 쨀횎쨔짬 쨍횜쨍짰 쨔첸쩐챤쨀짧 ��횜��쨍쨍챕 째횉횄횪 쨘횘째징.
					m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
					SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTCONSTRUCT, 2, NULL, NULL, NULL);
					return;
				}

				// 짹챈쨉책쩔징쩌짯 째횉쩌쨀횉횗 째횉횄횪쨔째��횉 째쨔쩌철쨍짝 횆짬쩔챤횈짰횉횗쨈횢. ��횕횁짚 째쨔쩌철 ��횑쨩처��쨘 횁철��쨩 쩌철 쩐첩쨈횢.
				/////
				for (i = 0; i < DEF_MAXGUILDS; i++)
					if (m_pGuildTeleportLoc[i].m_iV1 == m_pClientList[iClientH]->m_iGuildGUID) {
						m_pGuildTeleportLoc[i].m_dwTime = dwTime;
						if (m_pGuildTeleportLoc[i].m_iV2 >= DEF_MAXCONSTRUCTNUM) {
							// 짹챈쨉책 째횉쩌쨀 째쨀쩌철 횄횎째첬. 횁철��쨩쩌철 쩐첩쨈횢.
							m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
							SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTCONSTRUCT, 3, NULL, NULL, NULL);
							return;
						}
						else {
							// 째횉쩌쨀쨉횊 째횉쨔째 째쨔쩌철 횁천째징.
							m_pGuildTeleportLoc[i].m_iV2++;
							goto RSWU_LOOPBREAK;
						}
					}

				// 짹챈쨉책 쩌쨀횁짚쨉횉쩐챤 ��횜횁철 쩐횎��쩍. 횁철��쨩쩌철 쩐첩쨈횢.
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTCONSTRUCT, 3, NULL, NULL, NULL);
				break;


			case 43:
			case 44:
			case 45:
			case 46:
			case 47:
			case 51:
			case 40:
			case 41:
			case 42:
			case 48:
			case 49:
			case 50:
				break;
			}

		RSWU_LOOPBREAK:;

			// 쨍쨍쩐횪 ��체��챦 째횉횄횪쨔째횁횩 째징쨉책횇쨍쩔철째째��횑 째첩째횦횉체��횑쨋처쨍챕 쨀횎쨔짬 ��횓횁짖횉횠쩌짯 째횉쩌쨀횉횘 쩌철 쩐첩쨈횢.
			bRet = FALSE;
			switch (cType) {
			case 36:
			case 37:
				for (ix = tX - 2; ix <= tX + 2; ix++)
					for (iy = tY - 2; iy <= tY + 2; iy++) {
						m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->GetOwner(&sOwnerH, &cOwnerType, ix, iy);
						if ((sOwnerH != NULL) && (cOwnerType == DEF_OWNERTYPE_NPC)) {
							switch (m_pNpcList[sOwnerH]->m_sType) {
							case 36:
							case 37:
								bRet = TRUE;
								break;
							}
						}
					}

				// 횁철��쨩 쩌철 쩐첩쨈횂 쨩처��짠횁횂횉짜
				if ((dY <= 32) || (dY >= 783)) bRet = TRUE;
				break;
			}

			if (bRet == TRUE) {
				// 짹횢횄쨀쩔징 째징쨉책횇쨍쩔철쨉챕��횑 ��횜쩐챤쩌짯 째횉횄횪쨘횘째징.
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CANNOTCONSTRUCT, 1, NULL, NULL, NULL);
				return;
			}

			// 째징쨉책 쨍챨쨉책��횓째징 횄횩횁쩐 쨍챨쨉책��횓째징 쩌짹횇횄 
			if (cMode == NULL) {
				bRet = bCreateNewNpc(cNpcName, cName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 0, 0, DEF_MOVETYPE_FOLLOW, &tX, &tY, cNpcWayPoint, NULL, NULL, -1, FALSE, FALSE, FALSE, FALSE, m_pClientList[iClientH]->m_iGuildGUID);
				bSetNpcFollowMode(cName, m_pClientList[iClientH]->m_cCharName, DEF_OWNERTYPE_PLAYER);
			}
			else bRet = bCreateNewNpc(cNpcName, cName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 0, 0, DEF_MOVETYPE_GUARD, &tX, &tY, cNpcWayPoint, NULL, NULL, -1, FALSE, FALSE, FALSE, FALSE, m_pClientList[iClientH]->m_iGuildGUID);

			if (bRet == FALSE) {
				// 쩍횉횈횖횉횩��쨍쨔횉쨌횓 쩔쨔쩐횪쨉횊 NameValue쨍짝 횉횠횁짝쩍횄횇짼쨈횢.
				m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->SetNamingValueEmpty(iNamingValue);
			}
			else {
				// 째횉쩌쨀쩔징 쩌쨘째첩횉횩��쨍쨔횉쨌횓 째횉쩌쨀 횈첨��횓횈짰 째짢쩌횘 쩍횄횇짼쨈횢.
				m_pClientList[iClientH]->m_iConstructionPoint -= m_iNpcConstructionPoint[cType];
				if (m_pClientList[iClientH]->m_iConstructionPoint < 0) m_pClientList[iClientH]->m_iConstructionPoint = 0;
				// 횁철횊횜째체쩔징째횚 쨔횢쨌횓 횇챘쨘쨍.
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CONSTRUCTIONPOINT, m_pClientList[iClientH]->m_iConstructionPoint, m_pClientList[iClientH]->m_iWarContribution, NULL, NULL);
			}
		}
	}
}

void CGame::SelectCrusadeDutyHandler(int iClientH, int iDuty)
{

	if (m_pClientList[iClientH] == NULL) return;
	if ((m_pClientList[iClientH]->m_iGuildRank != 0) && (iDuty == 3)) return;

	if (m_iLastCrusadeWinner == m_pClientList[iClientH]->m_cSide &&
		m_pClientList[iClientH]->m_dwCrusadeGUID == 0 && iDuty == 3) {
		m_pClientList[iClientH]->m_iConstructionPoint = 3000;
	}
	m_pClientList[iClientH]->m_iCrusadeDuty = iDuty;

	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_CRUSADE, (DWORD)m_bIsCrusadeMode, m_pClientList[iClientH]->m_iCrusadeDuty, NULL, NULL);
	if (iDuty == 1)
		_bCrusadeLog(DEF_CRUSADELOG_SELECTDUTY, iClientH, NULL, "Fighter");
	else if (iDuty == 2)
		_bCrusadeLog(DEF_CRUSADELOG_SELECTDUTY, iClientH, NULL, "Constructor");
	else
		_bCrusadeLog(DEF_CRUSADELOG_SELECTDUTY, iClientH, NULL, "Commander");
}

void CGame::MapStatusHandler(int iClientH, int iMode, char* pMapName)
{
	int i;

	if (m_pClientList[iClientH] == NULL) return;

	switch (iMode) {
	case 1:
		if (m_pClientList[iClientH]->m_iCrusadeDuty == NULL) return;

		for (i = 0; i < DEF_MAXGUILDS; i++)
			if ((m_pGuildTeleportLoc[i].m_iV1 != NULL) && (m_pGuildTeleportLoc[i].m_iV1 == m_pClientList[iClientH]->m_iGuildGUID)) {
				SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_TCLOC, m_pGuildTeleportLoc[i].m_sDestX, m_pGuildTeleportLoc[i].m_sDestY,
					NULL, m_pGuildTeleportLoc[i].m_cDestMapName, m_pGuildTeleportLoc[i].m_sDestX2, m_pGuildTeleportLoc[i].m_sDestY2,
					NULL, NULL, NULL, NULL, m_pGuildTeleportLoc[i].m_cDestMapName2);
				// 건설 위치를 저장해 놓는다.
				ZeroMemory(m_pClientList[iClientH]->m_cConstructMapName, sizeof(m_pClientList[iClientH]->m_cConstructMapName));
				memcpy(m_pClientList[iClientH]->m_cConstructMapName, m_pGuildTeleportLoc[i].m_cDestMapName2, 10);
				m_pClientList[iClientH]->m_iConstructLocX = m_pGuildTeleportLoc[i].m_sDestX2;
				m_pClientList[iClientH]->m_iConstructLocY = m_pGuildTeleportLoc[i].m_sDestY2;
				break;
			}

		// 길드 소속이 아닌 군인의 요청이다.
		break;

	case 3:
		// 데이터 캐시 구조체 초기화 
		for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
			m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cType = NULL;
			m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cSide = NULL;
			m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sX = NULL;
			m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sY = NULL;
		}
		m_pClientList[iClientH]->m_iCSIsendPoint = NULL;
		ZeroMemory(m_pClientList[iClientH]->m_cSendingMapName, sizeof(m_pClientList[iClientH]->m_cSendingMapName));

		if (strcmp(pMapName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName) == 0) {
			// 현재 사용자가 위치한 맵의 정보를 요구했다.
			// 맵 데이터를 요청할 당시의 내용을 그대로 카피한다.
			for (i = 0; i < m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_iTotalCrusadeStructures; i++) {
				// v2.15 사용자가 Commander 가 아니어도 건물의 위치를 보여준다.
				if (m_pClientList[iClientH]->m_iCrusadeDuty == 3)
				{
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cType = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].cType;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cSide = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].cSide;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sX = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].sX;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sY = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].sY;
				}
				else if (m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].cType == 42)
				{
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cType = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].cType;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cSide = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].cSide;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sX = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].sX;
					m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sY = m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_stCrusadeStructureInfo[i].sY;
				}
			}
			memcpy(m_pClientList[iClientH]->m_cSendingMapName, m_pMapList[m_pClientList[iClientH]->m_cMapIndex]->m_cName, 10);
		}
		else {
			// 다른 맵의 상황을 요청했다. 미들랜드의 경우는 가능 
			if (strcmp(pMapName, "middleland") == 0) {
				for (i = 0; i < m_iTotalMiddleCrusadeStructures; i++) {
					// v2.15 사용자가 Commander 가 아니어도 건물의 위치를 보여준다.
					if (m_pClientList[iClientH]->m_iCrusadeDuty == 3)
					{
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cType = m_stMiddleCrusadeStructureInfo[i].cType;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cSide = m_stMiddleCrusadeStructureInfo[i].cSide;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sX = m_stMiddleCrusadeStructureInfo[i].sX;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sY = m_stMiddleCrusadeStructureInfo[i].sY;
					}
					else if (m_stMiddleCrusadeStructureInfo[i].cType == 42)
					{
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cType = m_stMiddleCrusadeStructureInfo[i].cType;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].cSide = m_stMiddleCrusadeStructureInfo[i].cSide;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sX = m_stMiddleCrusadeStructureInfo[i].sX;
						m_pClientList[iClientH]->m_stCrusadeStructureInfo[i].sY = m_stMiddleCrusadeStructureInfo[i].sY;
					}
				}
				strcpy(m_pClientList[iClientH]->m_cSendingMapName, "middleland");
			}
		}

		_SendMapStatus(iClientH);
		break;
	}
}

void CGame::_SendMapStatus(int iClientH)
{
	int i, iDataSize;
	char* cp, cData[DEF_MAXCRUSADESTRUCTURES * 6];
	short* sp;

	ZeroMemory(cData, sizeof(cData));
	cp = (char*)(cData);

	memcpy(cp, m_pClientList[iClientH]->m_cSendingMapName, 10);
	cp += 10;

	sp = (short*)cp;
	*sp = (short)m_pClientList[iClientH]->m_iCSIsendPoint;
	cp += 2;

	// 횄횗 쨍챤째쨀��횉 쨉짜��횑횇횒째징 ��횜쨈횂횁철 쩐횏쨍짰쨈횂 째첨 쨋챌쩔챵.
	cp++;

	if (m_pClientList[iClientH]->m_iCSIsendPoint == NULL)
		m_pClientList[iClientH]->m_bIsSendingMapStatus = TRUE;

	// 100째쨀쩐쩔 횁짚쨘쨍쨍짝 쨘쨍쨀쩍쨈횢.
	iDataSize = 0;
	for (i = 0; i < 100; i++) {
		if (m_pClientList[iClientH]->m_iCSIsendPoint >= DEF_MAXCRUSADESTRUCTURES) goto SMS_ENDOFDATA;
		if (m_pClientList[iClientH]->m_stCrusadeStructureInfo[m_pClientList[iClientH]->m_iCSIsendPoint].cType == NULL) goto SMS_ENDOFDATA;

		*cp = m_pClientList[iClientH]->m_stCrusadeStructureInfo[m_pClientList[iClientH]->m_iCSIsendPoint].cType;
		cp++;
		sp = (short*)cp;
		*sp = m_pClientList[iClientH]->m_stCrusadeStructureInfo[m_pClientList[iClientH]->m_iCSIsendPoint].sX;
		cp += 2;
		sp = (short*)cp;
		*sp = m_pClientList[iClientH]->m_stCrusadeStructureInfo[m_pClientList[iClientH]->m_iCSIsendPoint].sY;
		cp += 2;
		*cp = m_pClientList[iClientH]->m_stCrusadeStructureInfo[m_pClientList[iClientH]->m_iCSIsendPoint].cSide;
		cp++;

		iDataSize += 6;
		m_pClientList[iClientH]->m_iCSIsendPoint++;
	}

	// 쩔짤짹창짹챤횁철 쩔횚쨈횢쨍챕 쨈천 쨘쨍쨀쩐 쨍횧쩍횄횁철째징 ��횜쨈횢쨈횂 ��횉쨔횑.
	cp = (char*)(cData + 12);
	*cp = (iDataSize / 6);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAPSTATUSNEXT, iDataSize + 13, NULL, NULL, cData);


SMS_ENDOFDATA:;

	// 쨉짜��횑횇횒째징 쨈횢 ��체쩌횤 쨉횉쩐첬��쩍��쨩 ��횉쨔횑.
	cp = (char*)(cData + 12);
	*cp = (iDataSize / 6);
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_MAPSTATUSLAST, iDataSize + 13, NULL, NULL, cData);
	m_pClientList[iClientH]->m_bIsSendingMapStatus = FALSE;
}

void CGame::RequestHelpHandler(int iClientH)
{
	// 횉챦횉횁 쩔채횄쨩��횑쨈횢. 짹챈쨉책 쨍쨋쩍쨘횇횒쩔징째횚 횁횂횉짜쨍짝 ��체쨈횧횉횠 횁횠쨈횢.
	int i;

	if (m_pClientList[iClientH] == NULL) return;
	if (m_pClientList[iClientH]->m_iGuildRank == -1) return;
	if (m_pClientList[iClientH]->m_iCrusadeDuty != 1) return;

	for (i = 1; i < DEF_MAXCLIENTS; i++)
		if ((m_pClientList[i] != NULL) && (m_pClientList[i]->m_iGuildRank == 0) &&
			(m_pClientList[i]->m_iCrusadeDuty == 3) && (m_pClientList[i]->m_iGuildGUID == m_pClientList[iClientH]->m_iGuildGUID)) {
			// 째째��쨘 짹챈쨉책 쨍쨋쩍쨘횇횒��횑째챠 횁철횊횜째체 쩔짧횊째��쨩 쨍횄��쨘 쨩처횇횂��횑쨈횢.
			SendNotifyMsg(NULL, i, DEF_NOTIFY_HELP, m_pClientList[iClientH]->m_sX, m_pClientList[iClientH]->m_sY, m_pClientList[iClientH]->m_iHP, m_pClientList[iClientH]->m_cCharName);
			return;
		}

	// 횉철��챌 쨍횎쩔징 횁철횊횜째체��횑 쩐첩��쩍��쨩 횇챘쨘쨍횉횠 횁횠쨈횢.
	SendNotifyMsg(NULL, iClientH, DEF_NOTIFY_HELPFAILED, NULL, NULL, NULL, NULL);
}