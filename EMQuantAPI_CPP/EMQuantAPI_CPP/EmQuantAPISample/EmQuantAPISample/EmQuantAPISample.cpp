// EmQuantAPISample.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>
#include "EmQuantAPI.h"

#include <sstream>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <conio.h>
#ifdef WIN32
#include <ctime>
#else
#include <time.h>
#include <sys/time.h>
#endif

using namespace std;

// ʹ�þ�̬���ӷ�ʽ
// #ifdef _WIN64  
// #pragma comment(lib,"EmQuantAPI_x64.lib")  
// #else  
// #pragma comment(lib,"EmQuantAPI.lib")  
// #endif  

//���庯��ָ�� ��̬����dll//////////////////////////////////////////////////////////////////////////////
typedef void  (*psetserverlistdir)(const char* dir);
typedef EQErr (*psetcallback)(datacallback pfnCallback);
typedef EQErr (*pmanualactivate)(EQLOGININFO* pLoginInfo, const char* options, logcallback pfnCallback);
typedef EQErr (*psetproxy)(ProxyType type, const char* proxyip, unsigned short proxyport, bool verify, const char* proxyuser, const char* proxypwd);
typedef EQErr (*pstart)(EQLOGININFO* pLoginInfo, const char* options, logcallback pfnCallback);
typedef EQErr (*pstop)();
typedef const char* (*pgeterrstring)(EQErr errcode, EQLang lang);
typedef EQErr (*pcsd)(const char* codes, const char* indicators, const char* startdate, const char* enddate, const char* options, EQDATA*& eqdata);
typedef EQErr (*pcss)(const char* codes, const char* indicators, const char* options, EQDATA*& pEQData);
typedef EQErr (*ptradedates)(const char* startdate, const char* enddate, const char* options, EQDATA*& pEQData);
typedef EQErr (*psector)(const char* pukeyCode, const char* tradeDate, const char* options, EQDATA*& pEQData);
typedef EQErr (*pgetdate)(const char* tradeDate, int offDay, const char* options, EQDATA*& pEQData);
typedef EQID  (*pcsq)(const char* codes, const char* indicators, const char* options, datacallback pfnCallback, LPVOID lpUserParam, EQErr& nErrorID);
typedef EQErr (*pcsqcancel)(EQID serialID);
typedef EQErr (*preleasedata)(void* pEqData);
typedef EQErr (*pcsc)(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
typedef EQErr (*pcmc)(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
typedef EQErr (*pchmc)(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
typedef EQID  (*pcst)(const char* codes, const char* indicators, const char* startdatetime, const char* enddatetime, const char* options, datacallback pfnCallback, LPVOID lpUserParam, EQErr& nErrorID);
typedef EQErr (*pctr)(const char* ctrName, const char* indicators, const char* options, EQCTRDATA*& pEQCtrData);
typedef EQErr (*pcsqsnapshot)(const char* codes, const char* indicators, const char* options, EQDATA*& pEQData);
typedef EQErr (*pcps)(const char* cpsCodes, const char* cpsIndicators, const char* cpsConditions, const char* cpsOptions, EQDATA*& pEQData);
typedef EQErr (*ppquery)(const char* options, EQDATA*& pEQData);
typedef EQErr (*pporder)(ORDERINFO* pOrderInfo, int orderInfoSize, const char* combinCode, const char* remark, const char* options);
typedef EQErr (*pedb)(const char* edbids, const char* options, EQDATA*& pEQData);
typedef EQErr (*pedbquery)(const char* edbids, const char* indicators, const char* options, EQDATA*& pEQData);
typedef EQErr (*ppcreate)(const char* combinCode, const char* combinName, int64_t initialFound, const char* remark, const char* options);
typedef EQErr (*ppdelete)(const char* combinCode, const char* options);
typedef EQErr (*ppreport)(const char* combinCode, const char* indicator, const char* options, EQDATA*& pEQData);
typedef EQErr (*ptradedatesnum)(const char* startDate, const char* endDate, const char* options, int& num);
typedef EQErr (*pcfn)(const char* codes, const char* content,const eCfnMode emode, const char* options, EQDATA*& pEQData);
typedef EQErr (*pcfnquery)(const char* options, EQDATA*& pEQData);

typedef EQID  (*pcnq)(const char* codes, const char* content, const char* options, datacallback pfnCallback, LPVOID lpUserParam,EQErr& nErrorID);
typedef EQErr (*pcnqcancel)(EQID serialID);

typedef EQErr (*ppctransfer)(const char* combinCode, const char* transferdirect, const char* date, double opCash, const char* remark, const char* options);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
psetserverlistdir emsetserverlistdir = NULL;
psetcallback      emsetcallback = NULL;
pmanualactivate   emmanualactivate = NULL;
psetproxy         emsetproxy = NULL;
pstart        emstart = NULL;
pstop         emstop = NULL;
pgeterrstring emgeterrstring = NULL;
pcsd          emcsd = NULL;
pcss          emcss = NULL;
ptradedates   emtradedates = NULL;
psector       emsector = NULL;
pgetdate      emgetdate = NULL;
pcsq          emcsq = NULL;
pcsqcancel    emcsqcancel = NULL;
preleasedata  emreleasedata = NULL;
pcsc          emcsc = NULL;
pcmc          emcmc = NULL;
pchmc         emchmc = NULL;
pcst          emcst = NULL;
pctr          emctr = NULL;
pcsqsnapshot  emcsqsnapshot = NULL;
pcps          emcps = NULL;
ppquery       empquery = NULL;
pporder       emporder = NULL;
pedb          emedb = NULL;
pedbquery     emedbquery = NULL;
ppcreate      empcreate = NULL;
ppdelete      empdelete = NULL;
ppreport      empreport = NULL;
ptradedatesnum emtradedatesnum = NULL;
pcfn          emcfn = NULL;
pcfnquery     emcfnquery = NULL;
pcnq		  emcnq = NULL;
pcnqcancel    empcnqcancel = NULL;
ppctransfer   empctransfer = NULL;
//תstring����ʾ��
template<typename T>
std::string to_str(const T &v)
{
	stringstream s;
	s << v;
	return s.str();
}

//��־�ص�����ʾ��
int write2Log(const char* log)
{
	printf("%s", log);
	return 0;
}

//ȡEQVARIENTֵʾ��
std::string eqvalue2string(const EQVARIENT* pEQVarient)
{
	if(!pEQVarient)
	{
		return "";
	}

	char z[1024] = {0};
	std::string s = "";
	switch(pEQVarient->vtype)
	{
		//����Ϊ��������ڹ۲죬�����ַ�����޶�����ʵ�ʿɲο�������
	case eVT_null:
		sprintf_s(z,"%s", "        --");
		s = z;
		break;
	case eVT_char:
		sprintf_s(z,"%c", pEQVarient->unionValues.charValue);
		s = z;
		break; 
	case eVT_bool:
		sprintf_s(z,"%c", pEQVarient->unionValues.boolValue ? "true" : "false");
		s = z;
		break;
	case eVT_int:
		sprintf_s(z,"%10d", pEQVarient->unionValues.intValue);
		s = z;
		break;
	case eVT_uInt:
		sprintf_s(z,"%10u", pEQVarient->unionValues.uIntValue);
		s = z;
		break;
	case eVT_int64: 
		sprintf_s(z,"%10I64d", pEQVarient->unionValues.int64Value);
		s = z;
		break;
	case eVT_uInt64: 
		sprintf_s(z,"%10I64u", pEQVarient->unionValues.uInt64Value);
		s = z;
		break;
	case eVT_float:  
		sprintf_s(z,"%10.3f", pEQVarient->unionValues.floatValue);
		s = z;
		break;
	case eVT_double: 
		sprintf_s(z,"%14.3lf", pEQVarient->unionValues.doubleValue);
		s = z;
		break;
	case eVT_asciiString:
		sprintf_s(z,"%s", pEQVarient->eqchar.pChar);
		s = z;
		break;
	case eVT_unicodeString: 
		sprintf_s(z,"%s", pEQVarient->eqchar.pChar);
		s = z;
		break;
	case eVT_short:     
		sprintf_s(z,"%10d", pEQVarient->unionValues.shortValue);
		s = z;
		break;
	case eVT_ushort:     
		sprintf_s(z,"%10u", pEQVarient->unionValues.uShortValue);
		s = z;
		break;

	default:
		break;
	}

	return s;
}
//���ص�����ʾ��
int obtainCallback(const EQMSG* pMsg, LPVOID lpUserParam)
{
	printf("\r\n********obtainCallback*******\r\n");
	//��pMsg->serialID�Ƿ����0���޶��Ƿ������´���
	if(pMsg && pMsg->msgType == eMT_err && pMsg->serialID == 0)
	{
		//�����ص����⵽��½���߻��ߵ�¼���ߴ����߼�
		if(pMsg->err == EQERR_LOGIN_DISCONNECT || pMsg->err == EQERR_LOGIN_COUNT_LIMIT)
		{
			//��¼����  ����  ��½���ﵽ���ߣ�����¼�������ߣ� ��ʱ���еķ��񶼻�ֹͣ
			printf("\r\nYour account is disconnect. err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
			//�������ڴ�֪ͨ���߳��˺ŵ����ˣ������߳����µ�½�ͺ����������ˣ������ڴ˴����µ�½Ҳ�ɡ��Ƽ���һ�֡�
			//...do something
		}
		else if(pMsg->err == EQERR_QUOTE_LOGIN_FAIL || pMsg->err == EQERR_QUOTE_FLOW_FAIL)
		{
			printf("\r\nYour all csq subscribe have stopped. err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
			//�����¼��֤ʧ�ܣ�ÿ���������������ʱ��Ҫ��¼��֤����������������֤ʧ��ʱ����̬���ڲ���ȡ�����ж��ģ��û�����ݾ����������
		}
		else if(pMsg->err == EQERR_QUOTE_RECONNECT_FAIL)
		{
			//��������������Զ���������6��ʧ�ܣ�1�������ң������������Ի����������ֱ���ɹ�Ϊֹ���������������Ҫȷ�����ߵ�����״��
			printf("\r\n err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		}
		else if(pMsg->err == EQERR_QUOTE_RECONNECT)
		{
			//���鶩������һЩ����(��Щ����ᵼ������������ԭ��ͨ����־�����ͳһת����EQERR_QUOTE_RECONNECT������֪ͨ)�����Զ����������¶���,�����������
			printf("\r\n err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		}
		else if(pMsg->err == EQERR_INFO_RECONNECT_FAIL)
		{
			//��Ѷ�����������Զ���������6��ʧ�ܣ�1�������ң������������Ի����������ֱ���ɹ�Ϊֹ���������������Ҫȷ�����ߵ�����״��
			printf("\r\n err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		}
		else if(pMsg->err == EQERR_INFO_RECONNECT)
		{
			//��Ѷ��������һЩ����(��Щ����ᵼ������������ԭ��ͨ����־�����ͳһת����EQERR_QUOTE_RECONNECT������֪ͨ)�����Զ����������¶���,�����������
			printf("\r\n err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		}
		else if(pMsg->err == EQERR_INFOSUB_LOGIN_FAIL || pMsg->err == EQERR_INFO_FLOW_FAIL)
		{
			printf("\r\nYour all cnq subscribe have stopped. err [%d] %s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
			//��Ѷ���ĵ�¼��֤ʧ�ܣ�ÿ��������Ѷ������ʱ��Ҫ��¼��֤��������Ѷ������֤ʧ��ʱ����̬���ڲ���ȡ�����ж��ģ��û�����ݾ����������
		}
	}

	return 0;
}

//ʵʱ����ص�����ʾ��
volatile unsigned long g_recvtimes = 0;
int csqCallback(const EQMSG* pMsg, LPVOID lpUserParam)
{
	//�ر�ע�⣺
	//�벻Ҫ�ڱ��ص����������ȽϺ�ʱ�Ĳ�����csqĿǰ�Ƕ�����Ĺ���һ���߳������ݣ�����̣߳�ÿ������һ���������ͻص���������ڱ�����������ʱ������
	//���ܻᵼ�´�������л�Ѹ�����ӣ����������ӳ٣������ڴ����������
	//ͬʱҪע����߳�ͬ��

	SYSTEMTIME st;
	GetLocalTime(&st);
	if(!pMsg)
	{
		printf("****************************************\r\n");
		return 0;
	}

	printf("version: %d\n", pMsg->version);
	printf("[%02d:%02d:%02d.%03d]Received [%d] callback: msgType=%d requestID=%d, serialID=%d.\r\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, InterlockedIncrement(&g_recvtimes), pMsg->msgType, pMsg->requestID, pMsg->serialID);
	
	if(pMsg->msgType == eMT_err && pMsg->err != EQERR_SUCCESS)
	{
		printf("errid code[%d]:%s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		//��������csq���ܵĴ������ͣ������û���������
		switch(pMsg->err)
		{
			//���ܴ��ڵĴ��󣨲�һ��ֻ����Щ��������Ĵ����Ǳ������ͳ��ֵĴ��󣬻�����ȫ�����������Ĵ���ת������EQERR_QUOTE_RECONNECT �����ص���֪ͨ��
		case EQERR_NEW_MEM_FAIL:
			printf("csq�����ڽ��ջ��߽���ʱ�����ڴ�ʧ�ܡ�");
			break;
		case EQERR_PARSE_DATA_ERR:
			printf("csq�����������󣬱�������ᶪʧ��");
			break;
		case EQERR_FUNCTION_INTERNAL_ERR:
			printf("csq���������з������Դ���һ�㲻�ᷢ�����뷴�����ӿڿͷ���");
			break;
		default:
			break;
		}
		return 0;
	}

	if(!pMsg->pEQData)
	{
		printf("****************************************\r\n");
		return 0;
	}

	//����Ϊ�򵥵����ʾ��
	EQDATA *pEQData = pMsg->pEQData;
	string slinehead(""), sline("");
	if(pEQData->dateArray.nSize == 1)
	{
		slinehead = pEQData->dateArray.pChArray[0].pChar;
		slinehead += " ";
		for(int i=0;i<pEQData->codeArray.nSize;i++)
		{
			sline += string(pEQData->codeArray.pChArray[i].pChar);
			sline += " ";

			for(int j=0;j<pEQData->indicatorArray.nSize;j++)
			{
				if(i == 0)
				{
					slinehead += string(pEQData->indicatorArray.pChArray[j].pChar);
					slinehead += " ";

					if(j == pEQData->indicatorArray.nSize-1)
					{
						printf("%s\r\n",slinehead.c_str());
					}
				}

				EQVARIENT* pEQVarient = (*pEQData)(i,j,0);
				if(pEQVarient)
				{
					sline += eqvalue2string(pEQVarient);
					sline += " ";
				}
			}
			sline += "\n";
		}
		printf("%s",sline.c_str());
	}
	printf("****************************************\r\n");
	return 0;
}

int cnqCallback(const EQMSG* pMsg, LPVOID lpUserParam)
{
	//�ر�ע�⣺
	//�벻Ҫ�ڱ��ص����������ȽϺ�ʱ�Ĳ�����cnqĿǰ�Ƕ�����Ĺ���һ���߳������ݣ�����һ���߳̽����ͻص���������ڱ�����������ʱ������
	//���ܻᵼ�´�������л�Ѹ�����ӣ����������ӳ٣������ڴ����������
	//ͬʱҪע����߳�ͬ��

	SYSTEMTIME st;
	GetLocalTime(&st);
	if(!pMsg)
	{
		printf("****************************************\r\n");
		return 0;
	}

	printf("version: %d\n", pMsg->version);
	printf("[%02d:%02d:%02d.%03d] callback: msgType=%d requestID=%d, serialID=%d.\r\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, pMsg->msgType, pMsg->requestID, pMsg->serialID);

	if(pMsg->msgType == eMT_err && pMsg->err != EQERR_SUCCESS)
	{
		printf("errid code[%d]:%s\r\n", pMsg->err, emgeterrstring(pMsg->err, eLang_en));
		//��������cnq���ܵĴ������ͣ������û���������
		switch(pMsg->err)
		{
			//���ܴ��ڵĴ��󣨲�һ��ֻ����Щ��������Ĵ����Ǳ������ͳ��ֵĴ��󣬻�����ȫ�����������Ĵ���ת������EQERR_INFO_RECONNECT �����ص���֪ͨ��
		case EQERR_NEW_MEM_FAIL:
			printf("cnq�����ڽ��ջ��߽���ʱ�����ڴ�ʧ�ܡ�");
			break;
		case EQERR_PARSE_DATA_ERR:
			printf("cnq�����������󣬱�������ᶪʧ��");
			break;
		case EQERR_FUNCTION_INTERNAL_ERR:
			printf("cnq���������з������Դ���һ�㲻�ᷢ�����뷴�����ӿڿͷ���");
			break;
		default:
			break;
		}
		return 0;
	}

	if(!pMsg->pEQData)
	{
		printf("****************************************\r\n");
		return 0;
	}

	//����Ϊ�򵥵����ʾ��
	EQDATA *pEQData = pMsg->pEQData;
	string slinehead(""), sline("");
	if(pEQData->dateArray.nSize == 1)
	{
		slinehead = pEQData->dateArray.pChArray[0].pChar;
		slinehead += " ";
		for(int i=0;i<pEQData->codeArray.nSize;i++)
		{
			sline += string(pEQData->codeArray.pChArray[i].pChar);
			sline += " ";

			for(int j=0;j<pEQData->indicatorArray.nSize;j++)
			{
				if(i == 0)
				{
					slinehead += string(pEQData->indicatorArray.pChArray[j].pChar);
					slinehead += " ";

					if(j == pEQData->indicatorArray.nSize-1)
					{
						printf("%s\r\n",slinehead.c_str());
					}
				}

				EQVARIENT* pEQVarient = (*pEQData)(i,j,0);
				if(pEQVarient)
				{
					sline += eqvalue2string(pEQVarient);
					sline += " ";
				}
			}
			sline += "\n";
		}
		printf("%s",sline.c_str());
	}
	printf("****************************************\r\n");
	return 0;
}

//�������۷���ص�����ʾ������ʾ���ǽ�������ص��ļ������ڹ۲�
int cstCallback(const EQMSG* pMsg, LPVOID lpUserParam)
{
	LPVOID pUser = lpUserParam;

	static char buf[1024] = {0};
	memset(buf, 0, 1024);

	if(!pMsg->pEQData)
	{
		return 0;
	}


	DWORD dw1 = GetTickCount();

	EQDATA *pEQData = pMsg->pEQData;

	if(pEQData->codeArray.nSize != 1)
	{
		return 0;
	}

	memset(buf, 0, 1024);
	sprintf_s(buf,"..\\bin\\%s.txt", pEQData->codeArray.pChArray[0].pChar);
	FILE* fp = fopen(buf, "w+");
	if(!fp)
	{
		return 0;
	}

	memset(buf, 0, 1024);
	int pos = 0;
	for(int j=0;j<pEQData->indicatorArray.nSize;j++)
	{
		sprintf(buf+pos,"%s ", pEQData->indicatorArray.pChArray[j].pChar);
		pos = pos + pEQData->indicatorArray.pChArray[j].nSize;
	}
	sprintf(buf+pos, "%s", "\n");
	fwrite(buf, 1, strlen(buf), fp);

	string slinehead(""), sline("");
	for(int k=0;k<pEQData->dateArray.nSize;k++)
	{
		memset(buf, 0, 1024);
		sline = "";
		for(int j=0;j<pEQData->indicatorArray.nSize;j++)
		{
			EQVARIENT* pEQVarient = (*pEQData)(0,j,k);
			if(pEQVarient)
			{
				sline += eqvalue2string(pEQVarient);
				sline += " ";
			}
		}
		sprintf(buf,"%s\n",sline.c_str());
		fwrite(buf, 1, strlen(buf), fp);
	}

	DWORD dw2 = GetTickCount() - dw1;

	memset(buf, 0, 1024);
	sprintf(buf, "\nthis callback use %d ms\n", dw2);
	fwrite(buf, 1, strlen(buf), fp);
	fclose(fp);

	return 0;
}

EQErr csdTest()
{
	printf("*************csdTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emcsd("000002.SZ,300059.SZ", "OPEN,CLOSE,HIGH", "2016/01/10", "2016/04/13", "Period=1,Adjustflag=1,Curtype=1,Pricetype=1,Type=2", pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				for(int k=0;k<pData->dateArray.nSize;k++)
				{
					printf("%s %s %s : ",pData->indicatorArray.pChArray[j].pChar, pData->dateArray.pChArray[k].pChar, pData->codeArray.pChArray[i].pChar);

					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("%s\n",s.c_str());
					}
				}
			}
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr cssTest()
{
	printf("*************cssTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emcss("000002.SZ,300059.SZ", "OPEN,CLOSE,HIGH", "Period=1,AdjustFlag=1,CurType=1,PriceType=1,ReportDate=20140930,TradeDate=20160217,StartDate=2015/02/10,EndDate=2015/03/10,ItemsCode=9,type=1,Cycle=1", pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				for(int k=0;k<pData->dateArray.nSize;k++)
				{
					printf("%s %s: ",pData->indicatorArray.pChArray[j].pChar, pData->codeArray.pChArray[i].pChar);

					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("%s\n",s.c_str());
					}
				}
			}
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr tradedatesTest()
{
	printf("*************tradedatesTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emtradedates("2016-3-14", "2016-6-1", "Period=1,Order=1,Market=CNSESH", pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				for(int k=0;k<pData->dateArray.nSize;k++)
				{
					printf("%s %s %s : ",pData->indicatorArray.pChArray[j].pChar, pData->dateArray.pChArray[k].pChar, pData->codeArray.pChArray[i].pChar);

					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("%s\n",s.c_str());
					}
				}
			}
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr sectorTest()
{
	printf("*************sectorTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid =  emsector("2000034138", "2016-04-26", NULL, pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				for(int k=0;k<pData->dateArray.nSize;k++)
				{
					//printf("%s %s %s : ",pData->indicatorArray.pChArray[j].pChar, pData->dateArray.pChArray[k].pChar, pData->codeArray.pChArray[i].pChar);
					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("%s   ",s.c_str());
					}
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr getdateTest()
{
	printf("*************getdateTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emgetdate("20160426", -3, "Market=CNSESH", pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				for(int k=0;k<pData->dateArray.nSize;k++)
				{
					printf("%s %s %s : ",pData->indicatorArray.pChArray[j].pChar, pData->dateArray.pChArray[k].pChar, pData->codeArray.pChArray[i].pChar);

					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("%s\n",s.c_str());
					}
				}
			}
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

bool IsLeapYear(unsigned int iYear)
{
	return (iYear % 4 == 0 && iYear % 100 != 0) || (iYear % 400 == 0);
}

unsigned int MonthLastDays(unsigned int iYear, unsigned int iMonth)
{
	switch(iMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;
	case 2:
		//���������
		if(IsLeapYear(iYear))
			return 29;
		else
			return 28;
		break;
	}
	return 0;
}

unsigned int NextDay( unsigned int today )
{
	int year = today / 10000;
	int month = today % 10000 / 100;
	int day = today % 100;

	int lastday = MonthLastDays(year,month);
	if(day < lastday)
	{
		day++;
	}
	else
	{
		day = 1;
		if(month < 12)
		{
			month++;
		}
		else
		{
			year++;
			month = 1;
		}
	}
	return year*10000 + month*100 + day;
}

unsigned int PreDay( unsigned int today )
{
	int year = today / 10000;
	int month = today % 10000 / 100;
	int day = today % 100;

	if(day > 1)
	{
		day--;
	}
	else
	{
		if(month > 1)
		{
			month--;
		}
		else
		{
			month = 12;
			if (year > 1900)
			{
				year--;
			}
			else
			{
				year = 1900;
			}
		}
		day = MonthLastDays(year,month);
	}
	return year*10000 + month*100 + day;
}

unsigned int OffDay(unsigned int today, int offday)
{
	int ret = today;
	if(offday > 0)
	{
		while(offday)
		{
			ret = NextDay(ret);
			offday--;
		}
		return ret;
	}

	if(offday < 0)
	{
		while(offday)
		{
			ret = PreDay(ret);
			offday++;
		}
		return ret;
	}
	return ret;
}

int GetCurrentDateInt()
{
#ifdef WIN32
	SYSTEMTIME t;
	::GetLocalTime(&t);
	return  t.wYear*10000 + t.wMonth*100 + t.wDay;
#else
	time_t cur=time(0);
	tm t = {0};
	localtime_r(&cur, &t);
	return (t.tm_year + 1900)*10000 + (t.tm_mon+1)*100 + t.tm_mday;
#endif
}

EQErr cmcTest()
{
	printf("*************cmcTest*************\n");
	int today = GetCurrentDateInt();
	int startdate = OffDay(today, -29);
	
	EQDATA* pData = NULL;
	EQErr errid = emcmc("300059.SZ", "DATE,TIME,HIGH,OPEN,LOW,CLOSE,VOLUME,AMOUNT,HQOI,CHANGEOI,CLEAR,CHANGE,PCTCHANGE", to_str(startdate).c_str(), to_str(today).c_str(), NULL, pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int k=0;k<pData->dateArray.nSize;k++)
		{
			for(int j=0;j<pData->indicatorArray.nSize;j++)
			{
				EQVARIENT* pEQVarient = (*pData)(0,j,k);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("%s ",s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
	}
	return errid;
}

EQErr csqsnapshotTest()
{
	printf("*************csqsnapshotTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emcsqsnapshot("000005.SZ,600602.SH,600652.SH,600653.SH,600654.SH,600601.SH,600651.SH,000004.SZ,000002.SZ,000001.SZ,000009.SZ", "PRECLOSE,OPEN,HIGH,LOW,NOW,AMOUNT", "", pData);
	if(errid == EQERR_SUCCESS)
	{
		string slinehead(""), sline("");
		if(pData->dateArray.nSize == 1)
		{
			slinehead = pData->dateArray.pChArray[0].pChar;
			slinehead += " ";
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				sline += string(pData->codeArray.pChArray[i].pChar);
				sline += " ";

				for(int j=0;j<pData->indicatorArray.nSize;j++)
				{
					if(i == 0)
					{
						slinehead += string(pData->indicatorArray.pChArray[j].pChar);
						slinehead += " ";

						if(j == pData->indicatorArray.nSize-1)
						{
							printf("%s\r\n",slinehead.c_str());
						}
					}

					EQVARIENT* pEQVarient = (*pData)(i,j,0);
					if(pEQVarient)
					{
						sline += eqvalue2string(pEQVarient);
						sline += " ";
					}
				}
				sline += "\n";
			}
			printf("%s",sline.c_str());
		}
		emreleasedata(pData);
	}
	return errid;
}

EQErr ctrTest()
{
	printf("*************ctrTest*************\n");
	EQCTRDATA* pCtrData = NULL;
	EQErr errid = emctr("StockInfo",NULL, "StartDate=2014-9-26,EndDate=2014-10-26", pCtrData); 
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pCtrData->column;j++)
		{
			printf("%s ", pCtrData->indicatorArray.pChArray[j].pChar);
		}
		printf("\n");

		for(int i=0;i<pCtrData->row;i++)
		{
			for(int j=0;j<pCtrData->column;j++)
			{
				EQVARIENT* pEQVarient = (*pCtrData)(i,j);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("%s ", s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pCtrData);
	}
	return errid;
}

EQErr cpsTest()
{
	printf("*************cpsTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emcps("B_001004", "ǰ���̼�,OPEN,2017/2/27,1;֤ȯ���,NAME", "[ǰ���̼�]>0", "pickindicate=all,orderby=rd([ǰ���̼�]),top=max([ǰ���̼�],100)", pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			printf("%s  ",pData->indicatorArray.pChArray[j].pChar);
		}
		printf("\n");

		for(int i=0;i<pData->codeArray.nSize;i++)
		{
			for(int j=0;j<pData->indicatorArray.nSize;j++)
			{
				EQVARIENT* pEQVarient = (*pData)(i,j,0);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("%s  ",s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
	}
	return errid;
}

EQErr pqueryTest()
{
	printf("*************pqueryTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = empquery(NULL, pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				printf("%s %s : ",pData->indicatorArray.pChArray[j].pChar, pData->codeArray.pChArray[i].pChar);

				EQVARIENT* pEQVarient = (*pData)(i,j,0);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("%s\n",s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr pcreateTest()
{
	printf("*************pcreateTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = empcreate("quant001.PF", "���ţ��", 1000000, "����һ��ţ�ɵ����", NULL);
	if(errid == EQERR_SUCCESS)
	{
		printf("pcreate quant001:���ţ�� success.\n");
	}
	else
	{
		printf("pcreate quant001:���ţ�� fail.\n");
	}
	return errid;
}

EQErr pctransferTest()
{
	printf("*************pctransferTest*************\n");
	EQErr errid = empctransfer("quant001.PF", "IN", "2019-08-09", 100000.0, "׷���ʽ�", "TRANSFERTYPE=1");
	//EQErr errid = empctransfer("quant001", "IN", "2019-08-09", 1000.0, "׷���ʽ�", "TRANSFERTYPE=2,COMBINCODE2=quant002");
	if(errid == EQERR_SUCCESS)
	{
		printf("pctransfer quant001 success.\n");
	}
	else
	{
		printf("pctransfer quant001 fail.\n");
	}
	return errid;
}

EQErr pdeleteTest()
{
	printf("*************pdeleteTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = empdelete("quant001.PF", NULL);
	if(errid == EQERR_SUCCESS)
	{
		printf("pdelete quant001:���ţ�� success.\n");
	}
	else
	{
		printf("pdelete quant001:���ţ�� fail.\n");
	}
	return errid;
}

EQErr preportTest(int mode)
{
	printf("*************preportTest*************\n");
	EQErr errid = EQERR_SUCCESS;
	EQDATA* pData = NULL;
	if(mode == 1)
	{
		errid = empreport("quant001.PF", "hold", NULL, pData);
	}
	else
	{
		errid = empreport("quant001.PF", "record", "startdate=2017/07/12,enddate=2018/01/15", pData);
	}
	if(errid == EQERR_SUCCESS)
	{
		for(int j=0;j<pData->indicatorArray.nSize;j++)
		{
			printf("%s  ",pData->indicatorArray.pChArray[j].pChar);
		}
		printf("\n");
		for(int i=0;i<pData->codeArray.nSize;i++)
		{
			for(int j=0;j<pData->indicatorArray.nSize;j++)
			{
				EQVARIENT* pEQVarient = (*pData)(i,j,0);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("%s  ",s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr porderTest()
{
	printf("*************porderTest*************\n");
	EQErr errid = EQERR_SUCCESS;
	EQDATA* pData = NULL;
	ORDERINFO* pOrderInfo = new ORDERINFO[2];
	if(pOrderInfo)
	{
		memset(pOrderInfo, 0, sizeof(ORDERINFO)*2);

		strcpy_s(pOrderInfo[0].code, "300059.SZ"); 
		pOrderInfo[0].volume = 100.0;
		pOrderInfo[0].price = 10.88;
		pOrderInfo[0].optype = eOT_default;
		pOrderInfo[0].date = 20170725;
		pOrderInfo[0].time = 131313;

		strcpy_s(pOrderInfo[1].code, "600000.SH"); 
		pOrderInfo[1].volume = 100.0;
		pOrderInfo[1].price = 13.81;
		pOrderInfo[1].optype = eOT_buy;
		pOrderInfo[1].date = 20170725;
		pOrderInfo[1].time = 131815;

		errid = emporder(pOrderInfo, 2, "quant001.PF", "��quant001�в����µ�", "");
		if(errid == EQERR_SUCCESS)
		{
			printf("porder 300059.SZ,600000.SH in quant001�����ţ�� success.\n");
		}
		else
		{
			printf("porder 300059.SZ,600000.SH in quant001�����ţ�� fail.\n");
		}

		delete[] pOrderInfo;
		pOrderInfo = NULL;
	}
	return errid;
}

EQErr edbTest()
{
	printf("*************edbTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emedb("EMM00087117,EMG00147350","IsPublishDate=1",pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int i=0;i<pData->codeArray.nSize;i++)
		{
			for(int k=0;k<pData->dateArray.nSize;k++)
			{
				printf("%s   %s",pData->codeArray.pChArray[i].pChar, pData->dateArray.pChArray[k].pChar);
				for(int j=0;j<pData->indicatorArray.nSize;j++)
				{
					EQVARIENT* pEQVarient = (*pData)(i,j,k);
					if(pEQVarient)
					{
						string s = eqvalue2string(pEQVarient);
						printf("  %s", s.c_str());
					}
				}
				printf("\n");
			}
			printf("\n");
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQErr edbqueryTest()
{
	printf("*************edbqueryTest*************\n");
	EQDATA* pData = NULL;
	EQErr errid = emedbquery("EMM00058124,EMM00087117,EMG00147350", NULL, NULL, pData);
	if(errid == EQERR_SUCCESS)
	{
		for(int i=0;i<pData->codeArray.nSize;i++)
		{
			printf("%s",pData->codeArray.pChArray[i].pChar);
			for(int j=0;j<pData->indicatorArray.nSize;j++)
			{
				EQVARIENT* pEQVarient = (*pData)(i,j,0);
				if(pEQVarient)
				{
					string s = eqvalue2string(pEQVarient);
					printf("  %s", s.c_str());
				}
			}
			printf("\n");
		}
		emreleasedata(pData);
		pData = NULL;
	}
	return errid;
}

EQID cstTest()
{
	printf("*************cstTest*************�������ص������ı�.\n");
	const char* cstindicator = "TIME,OPEN,HIGH,LOW,NOW,AMOUNT,VOLUME,PRECLOSE,HIGHLIMIT,LOWLIMIT,BUYPRICE1,BUYVOLUME1,SELLPRICE1,SELLVOLUME1,BUYPRICE2,BUYVOLUME2,SELLPRICE2,SELLVOLUME2,BUYPRICE3,BUYVOLUME3,SELLPRICE3,SELLVOLUME3,BUYPRICE4,BUYVOLUME4,SELLPRICE4,SELLVOLUME4,BUYPRICE5,BUYVOLUME5,SELLPRICE5,SELLVOLUME5";
	//ʱ�����ֻ��ʱ���������ã���ֻ��ȡ�������������
	EQErr errid = EQERR_SUCCESS;
	EQID nCstSerialId = emcst("000002.SZ,300059.SZ", cstindicator, "20161027083000", "20161027153000", NULL, cstCallback, NULL, errid);
	printf("cst request serialID %d, errid:%d\n", nCstSerialId, errid);
	return nCstSerialId;
}

void csqTest()
{
	printf("*************csqTest*************\n");
	int nSerialID = 0, nSerialID1 = 0;
	const char* codesCSQ1="300216.SZ,002716.SZ,600834.SH,600616.SH";
	const char* codesCSQ2="601669.SH,601198.SH,000712.SZ,600000.SH";

	const char* indicatorCSQ = "TIME,PRECLOSE,OPEN,HIGH,LOW,NOW,AMOUNT";
	//"Pushtype=1"ȫ������   "Pushtype=0"��������  "Pushtype=2"��������2(֤ȯ������ָ��ֵȫ��)
	EQErr errid = EQERR_SUCCESS;
	nSerialID = emcsq(codesCSQ1, indicatorCSQ, "Pushtype=1,TIMESTAMP=1,wransize=500", csqCallback, NULL, errid);
	printf("csq request serialID %d, errid:%d\n", nSerialID, errid);
	nSerialID1 = emcsq(codesCSQ2, indicatorCSQ, "Pushtype=2,WARNSIZE=500", csqCallback, NULL, errid);
	printf("csq request serialID %d, errid:%d\n", nSerialID1, errid);
}

EQErr tradedatesnumTest()
{
	printf("*************tradedatesnumTest*************\n");
	int ntradedatesnum = 0;
	EQErr errid = emtradedatesnum("2018-01-01","2018-09-05","",ntradedatesnum);
	if(errid == EQERR_SUCCESS)
	{
		printf("2018-01-01~2018-09-05 has %d trade day\n", ntradedatesnum);
	}
	return errid;
}

EQErr csqcancelTest()
{
	return emcsqcancel(0);
}

void cfntest()
{
	printf("*************cfntest*************\n");
	EQDATA* pData = NULL;
	EQErr errid=emcfn("300059.SZ,600519.SH,300024.SZ", "companynews,industrynews", eCfnMode_EndCount,"starttime=20190501010000,endtime=20190725,count=10",pData);
	printf("*************cfntest*****EQErr:%d*****\n",errid);
	if(errid == EQERR_SUCCESS)
	{
		string slinehead(""), sline("");
		if(pData->dateArray.nSize == 1)
		{
			slinehead = pData->dateArray.pChArray[0].pChar;
			slinehead += " ";
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				sline += string(pData->codeArray.pChArray[i].pChar);
				sline += " ";

				for(int j=0;j<pData->indicatorArray.nSize;j++)
				{
					if(i == 0)
					{
						slinehead += string(pData->indicatorArray.pChArray[j].pChar);
						slinehead += " ";

						if(j == pData->indicatorArray.nSize-1)
						{
							printf("%s\r\n",slinehead.c_str());
						}
					}

					EQVARIENT* pEQVarient = (*pData)(i,j,0);
					if(pEQVarient)
					{
						sline += eqvalue2string(pEQVarient);
						sline += " ";
					}
				}
				sline += "\n";
			}
			printf("%s",sline.c_str());
		}
		emreleasedata(pData);
		pData = NULL;
	}
}

void cfntest2()
{
	printf("*************cfntest2*************\n");
	EQDATA* pData = NULL;
	EQErr errid=emcfn("S888005002API", "sectornews", eCfnMode_EndCount,"starttime=20190501010000,endtime=20190725200000,count=10",pData);
	printf("*************cfntest2*****EQErr:%d*****\n",errid);
	if(errid == EQERR_SUCCESS)
	{
		string slinehead(""), sline("");
		if(pData->dateArray.nSize == 1)
		{
			slinehead = pData->dateArray.pChArray[0].pChar;
			slinehead += " ";
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				sline += string(pData->codeArray.pChArray[i].pChar);
				sline += " ";

				for(int j=0;j<pData->indicatorArray.nSize;j++)
				{
					if(i == 0)
					{
						slinehead += string(pData->indicatorArray.pChArray[j].pChar);
						slinehead += " ";

						if(j == pData->indicatorArray.nSize-1)
						{
							printf("%s\r\n",slinehead.c_str());
						}
					}

					EQVARIENT* pEQVarient = (*pData)(i,j,0);
					if(pEQVarient)
					{
						sline += eqvalue2string(pEQVarient);
						sline += " ";
					}
				}
				sline += "\n";
			}
			printf("%s",sline.c_str());
		}
		emreleasedata(pData);
		pData = NULL;
	}
}

void cfnquerytest()
{
	printf("*************cfnquerytest*************\n");
	EQDATA* pData = NULL;
	EQErr errid=emcfnquery("",pData);
	printf("*************cfnquerytest*****EQErr:%d*****\n",errid);
	if(errid == EQERR_SUCCESS)
	{
		string slinehead(""), sline("");
		if(pData->dateArray.nSize == 1)
		{
			slinehead = pData->dateArray.pChArray[0].pChar;
			slinehead += " ";
			for(int i=0;i<pData->codeArray.nSize;i++)
			{
				sline += string(pData->codeArray.pChArray[i].pChar);
				sline += " ";

				for(int j=0;j<pData->indicatorArray.nSize;j++)
				{
					if(i == 0)
					{
						slinehead += string(pData->indicatorArray.pChArray[j].pChar);
						slinehead += " ";

						if(j == pData->indicatorArray.nSize-1)
						{
							printf("%s\r\n",slinehead.c_str());
						}
					}

					EQVARIENT* pEQVarient = (*pData)(i,j,0);
					if(pEQVarient)
					{
						sline += eqvalue2string(pEQVarient);
						sline += " ";
					}
				}
				sline += "\n";
			}
			printf("%s",sline.c_str());
		}
		emreleasedata(pData);
		pData = NULL;
	}
	
}
int  cnqtest()
{
	printf("*************cnqtest*************\n");
	EQErr errid= 0;
	int nserialid = emcnq("S888005002API", "sectornews", "",cnqCallback,NULL,errid);
	printf("*************cnqtest******serialid:%d** errid:%d\n",nserialid,errid);
	return nserialid;
}
int  cnqtest2()
{
	printf("*************cnqtest2*************\n");
	EQErr errid= 0;
	int nserialid = emcnq("300059.SZ,300024.SZ", "companynews,industrynews", "",cnqCallback,NULL,errid);
	printf("*************cnqtest2******serialid:%d** errid:%d \n",nserialid,errid);
	return nserialid;
}
int  cnqtest3()
{
	printf("*************cnqtest3*************\n");
	EQErr errid= 0;
	int nserialid = emcnq("300058.SZ,300024.SZ,300057.SZ", "companynews,industrynews", "",cnqCallback,NULL,errid);
	printf("*************cnqtest3******serialid:%d** errid:%d \n",nserialid,errid);
	return nserialid;
}
int _tmain(int argc, _TCHAR* argv[])
{
	char DllPath[MAX_PATH] = {0};

#ifdef _WIN64  
	strcpy_s(DllPath, "../lib/EmQuantAPI_x64.dll");
#else  
	strcpy_s(DllPath, "../lib/EmQuantAPI.dll");
#endif  

	//����dll��ַ
	HMODULE hDll = LoadLibraryA(DllPath);
	if(hDll == NULL)
	{
		return 0;
	}
	emsetserverlistdir = (psetserverlistdir)GetProcAddress(hDll, "setserverlistdir");
	emsetcallback = (psetcallback)GetProcAddress(hDll, "setcallback");
	emmanualactivate = (pmanualactivate)GetProcAddress(hDll, "manualactivate");
	emsetproxy = (psetproxy)GetProcAddress(hDll, "setproxy");
	emstart = (pstart)GetProcAddress(hDll, "start");
	emstop = (pstop)GetProcAddress(hDll, "stop");
	emgeterrstring = (pgeterrstring)GetProcAddress(hDll, "geterrstring");
	emcsd = (pcsd)GetProcAddress(hDll, "csd");
	emcss = (pcss)GetProcAddress(hDll, "css");
	emtradedates = (ptradedates)GetProcAddress(hDll, "tradedates");
	emsector = (psector)GetProcAddress(hDll, "sector");
	emgetdate = (pgetdate)GetProcAddress(hDll, "getdate");
	emcsq = (pcsq)GetProcAddress(hDll, "csq");
	emcsqcancel = (pcsqcancel)GetProcAddress(hDll, "csqcancel");
	emreleasedata = (preleasedata)GetProcAddress(hDll, "releasedata");
	emcsc = (pcsc)GetProcAddress(hDll, "csc");
	emcmc = (pcmc)GetProcAddress(hDll, "cmc");
	emchmc = (pchmc)GetProcAddress(hDll, "chmc");
	emcst = (pcst)GetProcAddress(hDll, "cst");
	emctr = (pctr)GetProcAddress(hDll, "ctr");
	emcsqsnapshot = (pcsqsnapshot)GetProcAddress(hDll, "csqsnapshot");
	emcps = (pcps)GetProcAddress(hDll, "cps");
	empquery = (ppquery)GetProcAddress(hDll, "pquery");
	emporder = (pporder)GetProcAddress(hDll, "porder");
	emedb = (pedb)GetProcAddress(hDll, "edb");
	emedbquery = (pedbquery)GetProcAddress(hDll, "edbquery");
	empcreate = (ppcreate)GetProcAddress(hDll, "pcreate");
	empdelete = (ppdelete)GetProcAddress(hDll, "pdelete");
	empreport = (ppreport)GetProcAddress(hDll, "preport");
	emtradedatesnum = (ptradedatesnum)GetProcAddress(hDll, "tradedatesnum");

	emcfn     = (pcfn)GetProcAddress(hDll, "cfn");
	emcfnquery = (pcfnquery)GetProcAddress(hDll,"cfnquery");
	emcnq     = (pcnq)GetProcAddress(hDll,"cnq");
	empcnqcancel = (pcnqcancel)GetProcAddress(hDll,"cnqcancel");
	empctransfer = (ppctransfer)GetProcAddress(hDll,"pctransfer");
	if( !emsetserverlistdir || !emsetcallback || !emmanualactivate || !emsetproxy || !emstart || !emstop || !emgeterrstring || !emcsd || !emcss || !emtradedates || !emsector 
		|| !emgetdate || !emcsq || !emcsqcancel || !emreleasedata|| !emcsc || !emcmc || !emchmc  || !emcst|| !emctr || !emcsqsnapshot || !emcps || !empquery || !emporder
		|| !emedb || !emedbquery || !empcreate || !empdelete || !empreport || !emtradedatesnum|| !emcfn || !emcfnquery || !emcnq || !empcnqcancel || !empctransfer)
	{
		FreeLibrary(hDll);
		printf("GetProcAddress fail. Press enter...\n");
		getchar();
		return 0;
	}

	//�������ص����� ע��һ��Ҫ����һ�����ص������������ղ����˺ŵ���֪ͨ
	emsetcallback(obtainCallback);
	//���������ļ�Ŀ¼
	emsetserverlistdir("../lib");
	//��ʼ����������־�ص��Լ���½  option����"TestLatency=0"������������  "TestLatency=1"����������ѡ������(���и����������ٵĹ���)
	//����̬���е���־��ͨ���ص��ӿ�������û���Ŀǰwrite2Log��ֻ�ǽ���־�������Ļ���û����Ը���Ϊд���ļ�
	EQErr errid = emstart(NULL, "TestLatency=0,ForceLogin=1", write2Log);
	if(errid != EQERR_SUCCESS)
	{
		printf("Login fail [%d] %s. Press enter to continue\n", errid, emgeterrstring(errid, eLang_en));
		getchar();
		return 0;
	}

	//ע�⣺2.4.0.0�Ķ���
	//�첽����ĩβ�����˴����뷵�ز������ڵ���ʱ���Ը��ݴ��������ж��Ƿ�����ɹ�
	//�첽����֧������ÿ������ֱ����ò�ͬ�Ļص��������Ͳ���Ҫ������ˮ������Զ��Ľ���ˣ�ͬʱ�ᵼ�������Ĵ��󲻻ᵥ����ĳ��������ص��ˣ�ֱ��ת���ɷ����������Ĵ��������ص�֪ͨ
	//ÿ��������ˮ�ŷֱ����ɣ�ԭ����ȫ�����ɵģ�������ʹ����Ҫ����requestid + serialidһ�������֡�

	printf("��¼�ɹ�\n");
	Sleep(2000);cfntest();
	Sleep(2000);cfnquerytest();
	Sleep(2000);cfntest2();
	Sleep(2000);
	int nId =cnqtest();
	Sleep(2000);
	int nId2 = cnqtest2();
	Sleep(1000);
	printf("cnqcancel subscribe %d \n",nId2);
	cnqtest3();
	Sleep(2000);
	empcnqcancel(nId2);
	int ncount = 0;
	while(1)
	{
		Sleep(1000);
		if(++ncount == 60)
		break;
	}
	printf("cnqcancel subscribe \n");
	empcnqcancel(0);
	
	Sleep(2000); tradedatesnumTest();
	Sleep(2000); cmcTest();
	Sleep(2000); csdTest(); 
	Sleep(2000); cssTest();
	Sleep(2000); tradedatesTest();
	Sleep(2000); sectorTest();
	Sleep(2000); getdateTest();
	Sleep(2000); csqsnapshotTest();
	Sleep(2000); ctrTest();
	Sleep(2000); cpsTest();
	Sleep(2000); 
	errid = pcreateTest();
	if(errid == EQERR_SUCCESS)
	{
		Sleep(2000); pctransferTest();
		Sleep(2000); porderTest();
		Sleep(2000); preportTest(1);
		Sleep(2000); preportTest(2);
		Sleep(2000); pqueryTest();
		Sleep(2000); pdeleteTest();
	}
	Sleep(2000); edbTest();
	Sleep(2000); edbqueryTest();
	Sleep(2000); cstTest();
	Sleep(2000); csqTest();
	//csq����20���Ӻ�ȡ������
	int count = 0;
	while(1)
	{
		Sleep(10);
		if(++count == 2000)
			break;
	}
	csqcancelTest();
	
	printf("��������˳�\n");
	getch();
	//�˳�
	emstop();
	FreeLibrary(hDll);
	return 0;
}