/**************************************************************************************************
*   EmQuantAPI.h    version  2.4.0.0                                                              *                                                                      *
*   Copyright(c)2016-2019,  EastMoney Information  Co,. Ltd. All Rights Reserved.                 *
*   Eastmoney API must not be used without authorzation, unauthorized user shall be held liable.  *                                                                  *
***************************************************************************************************/
#ifndef _EMQUANTAPI_H_
#define _EMQUANTAPI_H_ 

#include <stdint.h>

#define EMQUNANTAPIVER 2400

#ifdef WIN32
#ifdef EMQUANTAPI_EXPORTS
#define EMQUANTAPI  extern "C" __declspec(dllexport)
#else
#define EMQUANTAPI extern "C" __declspec(dllimport)
#endif /*#ifdef EMQUANTAPI_EXPORTS*/
#else
#define EMQUANTAPI extern "C"
#endif /*#ifdef WIN32*/

//����������Ͷ���
typedef int EQErr;

//����ID�����Ͷ���
typedef int EQID;

#ifndef WIN32
typedef void* LPVOID;
#endif //#ifndef WIN32
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//�ɹ�
#define EQERR_SUCCESS                  (0)
//�������                             
#define EQERR_BASE                     (10000000)
//һ���Դ���                           
#define EQERR_BASE_GENERAL             (EQERR_BASE)
//�˻���ش���						 
#define EQERR_BASE_ACCOUT              (EQERR_BASE + 1000)
//������ش���                         
#define EQERR_BASE_NET                 (EQERR_BASE + 2000)
//�������������                       
#define EQERR_BASE_PARAM               (EQERR_BASE + 3000)


#pragma region �˻���ش��� 
//�û�δ��¼
#define EQERR_NO_LOGIN                 (EQERR_BASE_ACCOUT + 1)
//�û������������					   
#define EQERR_USERNAMEORPASSWORD_ERR   (EQERR_BASE_ACCOUT + 2)
//�û���APIȨ��						  
#define EQERR_NO_ACCESS                (EQERR_BASE_ACCOUT + 3)
//�û�APIȨ�޹���						 
#define EQERR_ACCESS_EXPIRE            (EQERR_BASE_ACCOUT + 4)
//��ȡ�û���Ϣʧ��					   
#define EQERR_GETUSERINFO_FAIL         (EQERR_BASE_ACCOUT + 5)
//DLL�汾�Ź���						  
#define EQERR_DLLVESION_EXPIRE         (EQERR_BASE_ACCOUT + 6)
//�û���API_LV2Ȩ��					  
#define EQERR_NO_LV2_ACCESS            (EQERR_BASE_ACCOUT + 7)
//�û�API_LV2Ȩ�޹���					 
#define EQERR_LV2_ACCESS_EXPIRE        (EQERR_BASE_ACCOUT + 8)
//�˺ŵ�¼���ﵽ����					  
#define EQERR_LOGIN_COUNT_LIMIT        (EQERR_BASE_ACCOUT + 9)
//�û���¼ʧ��						 
#define EQERR_LOGIN_FAIL               (EQERR_BASE_ACCOUT + 10)
//�û���¼����						 
#define EQERR_LOGIN_DISCONNECT         (EQERR_BASE_ACCOUT + 11)
//�û�Ȩ�޲���						 
#define EQERR_ACCESS_INSUFFICIENCE     (EQERR_BASE_ACCOUT + 12)
//�û����ڵ�¼						 
#define EQERR_IS_LOGIN                 (EQERR_BASE_ACCOUT + 13)
//��Ҫ��¼����						 
#define EQERR_NEED_ACTIVATE            (EQERR_BASE_ACCOUT + 14)
//��¼�����쳣						 
#define EQERR_LOGIN_SERVICE_ERR        (EQERR_BASE_ACCOUT + 15)
//�����˹�����						 
#define EQERR_IS_MANUAL_ACTIVATE       (EQERR_BASE_ACCOUT + 16)
//�����˹�����						 
#define EQERR_NOTNEED_MANUAL_ACTIVATE  (EQERR_BASE_ACCOUT + 17)
//�˹�����ʧ��						 
#define EQERR_MANUAL_ACTIVATE_FAIL     (EQERR_BASE_ACCOUT + 18)
//�����豸���¼�豸��һ��			   
#define EQERR_DIFFRENT_DEVICE          (EQERR_BASE_ACCOUT + 19)
//userInfo��ʧЧ�����¼���			   
#define EQERR_USERINFO_EXPIRED         (EQERR_BASE_ACCOUT + 20)
//��������¼��֤ʧ��
#define EQERR_QUOTE_LOGIN_FAIL         (EQERR_BASE_ACCOUT + 21)
//�������������֤ʧ��
#define EQERR_QUOTE_FLOW_FAIL          (EQERR_BASE_ACCOUT + 22)
//��Ѷ��ѯ�����¼��֤ʧ��
#define EQERR_INFOQUERY_LOGIN_FAIL     (EQERR_BASE_ACCOUT + 23)
//��Ѷ���ķ����¼��֤ʧ��
#define EQERR_INFOSUB_LOGIN_FAIL       (EQERR_BASE_ACCOUT + 24)
//��Ѷ����������֤ʧ��
#define EQERR_INFO_FLOW_FAIL           (EQERR_BASE_ACCOUT + 25)
#pragma  endregion    

#pragma region һ���Դ���             
//��ȡ������ʧ��                      
#define EQERR_GET_TRADE_FAIL           (EQERR_BASE_GENERAL + 1)
//��ʼ������ʧ��                	    
#define EQERR_INIT_OBTAIN_CLASS_FAIL   (EQERR_BASE_GENERAL + 2)
//�����ڴ�ʧ��                         
#define EQERR_NEW_MEM_FAIL             (EQERR_BASE_GENERAL + 3)
//�������ݴ���                         
#define EQERR_PARSE_DATA_ERR           (EQERR_BASE_GENERAL + 4)
//gzip��ѹʧ��                         
#define EQERR_UNGZIP_DATA_FAIL         (EQERR_BASE_GENERAL + 5)
//δ֪����							   
#define EQERR_UNKNOWN_ERR              (EQERR_BASE_GENERAL + 6)
//�����ڲ�����						 
#define EQERR_FUNCTION_INTERNAL_ERR    (EQERR_BASE_GENERAL + 7)
//����Խ��							   
#define EQERR_OUTOF_BOUNDS             (EQERR_BASE_GENERAL + 8)
//������							    
#define EQERR_NO_DATA                  (EQERR_BASE_GENERAL + 9)
//ϵͳ�������						 
#define EQERR_SYSTEM_ERROR             (EQERR_BASE_GENERAL + 10)
//�������б�����                          
#define EQERR_SERVERLIST_ERROR         (EQERR_BASE_GENERAL + 11)
//����ʧ��							   
#define EQERR_OPERATION_FAILURE        (EQERR_BASE_GENERAL + 12)
//�������							   
#define EQERR_SERVICE_ERROR            (EQERR_BASE_GENERAL + 13)
//��ȡ�������б�ʧ��
#define EQERR_GETSERVERLIST_FAIL       (EQERR_BASE_GENERAL + 14)
//����ʱ
#define EQERR_SERVICE_TIMEOUT          (EQERR_BASE_GENERAL + 15)
//����Ƶ�ι���
#define EQERR_FREQUENCY_OVER           (EQERR_BASE_GENERAL + 16)
//����IP����
#define EQERR_OVERSEAS_IP_RESTRICTED   (EQERR_BASE_GENERAL + 17)
//POP��ϲ�֧�ִ˲���
#define EQERR_POP_GROUP_NOT_SUPPORT    (EQERR_BASE_GENERAL + 18)
#pragma  endregion                    

#pragma region ������ش���           
//�������                            
#define EQERR_SOCKET_ERR               (EQERR_BASE_NET + 1)
//��������ʧ��                         
#define EQERR_CONNECT_FAIL             (EQERR_BASE_NET + 2)
//�������ӳ�ʱ                         
#define EQERR_CONNECT_TIMEOUT          (EQERR_BASE_NET + 3)
//�������ʱ���ӶϿ�					  
#define EQERR_RECVCONNECTION_CLOSED    (EQERR_BASE_NET + 4)
//���緢��ʧ��                         
#define EQERR_SENDSOCK_FAIL            (EQERR_BASE_NET + 5)
//���緢�ͳ�ʱ                         
#define EQERR_SENDSOCK_TIMEOUT         (EQERR_BASE_NET + 6)
//������մ���                         
#define EQERR_RECVSOCK_FAIL            (EQERR_BASE_NET + 7)
//������ճ�ʱ                         
#define EQERR_RECVSOCK_TIMEOUT         (EQERR_BASE_NET + 8)
//�����������������ʧ��
#define EQERR_QUOTE_RECONNECT_FAIL     (EQERR_BASE_NET + 9)
//http����ʧ��
#define EQERR_HTTP_FAIL                (EQERR_BASE_NET + 10)
//�ȴ�������Ӧ��ʱ 
#define EQERR_WAIT_NET_RES_TIMEOUT     (EQERR_BASE_NET + 11)
//�������������
#define EQERR_QUOTE_RECONNECT          (EQERR_BASE_NET + 12)
//��Ѷ����������
#define EQERR_INFO_RECONNECT           (EQERR_BASE_NET + 13)
//��Ѷ��������������ʧ��
#define EQERR_INFO_RECONNECT_FAIL      (EQERR_BASE_NET + 14)
#pragma  endregion

#pragma region �������������
//�������Ϊ��
#define EQERR_INPARAM_EMPTY            (EQERR_BASE_PARAM + 1)
//��������Ϊ��					       
#define EQERR_OUTPARAM_EMPTY           (EQERR_BASE_PARAM + 2)
//��������						       
#define EQERR_PARAM_ERR                (EQERR_BASE_PARAM + 3)
//��ʼ���ڸ�ʽ����ȷ				      
#define EQERR_START_DATE_ERR           (EQERR_BASE_PARAM + 4)
//��ֹ���ڸ�ʽ����ȷ  			       
#define EQERR_END_DATE_ERR             (EQERR_BASE_PARAM + 5)
//��ʼ���ڴ��ڽ�������			       
#define EQERR_START_BIGTHAN_END        (EQERR_BASE_PARAM + 6)
//���ڸ�ʽ����ȷ  				        
#define EQERR_DATE_ERR                 (EQERR_BASE_PARAM + 7)
//��Ч��֤ȯ����				        
#define EQERR_CODE_INVALIED            (EQERR_BASE_PARAM + 8)
//֤ȯ�����ظ�					       
#define EQERR_CODE_REPEAT              (EQERR_BASE_PARAM + 9)
//��Ч��ָ��						      
#define EQERR_INDICATOR_INVALIED       (EQERR_BASE_PARAM + 10)
//�û���Ϊ��						      
#define EQERR_USERNAME_EMPTY           (EQERR_BASE_PARAM + 11)
//����Ϊ��						       
#define EQERR_PASSWORD_EMPTY           (EQERR_BASE_PARAM + 12)
//���������Ʊ�����ﵽ����		       
#define EQERR_TO_UPPER_LIMIT           (EQERR_BASE_PARAM + 13)
//��֧�ֵĻ��ָ��				       
#define EQERR_MIXED_INDICATOR          (EQERR_BASE_PARAM + 14)
//���ζ���ָ��ﵽ����				 
#define EQERR_INDICATOR_TO_UPPER_LIMIT (EQERR_BASE_PARAM + 15)
//��������֧�ַ�Χ					   
#define EQERR_BEYOND_DATE_SUPPORT      (EQERR_BASE_PARAM + 16)
//��Ȩ����С�ڽ�ֹ����			       
#define EQERR_BASE_LESS_THAN_END       (EQERR_BASE_PARAM + 17)
//��֧�ֵĻ��֤ȯƷ��			       
#define EQERR_MIXED_CODES_MARKET       (EQERR_BASE_PARAM + 18)
//��֧�ֵ�֤ȯ����Ʒ��				 
#define EQERR_NO_SUPPORT_CODES_MARKET  (EQERR_BASE_PARAM + 19)
//����������������					   
#define EQERR_ORDER_TO_UPPER_LIMIT     (EQERR_BASE_PARAM + 20)
//��֧�ֵĽ�����Ϣ				       
#define EQERR_NO_SUPPORT_ORDERINFO     (EQERR_BASE_PARAM + 21)
//ָ���ظ�						 
#define EQERR_INDICATOR_REPEAT         (EQERR_BASE_PARAM + 22)
//��Ѷ���������					 
#define EQERR_INFOBKCODE_INVALIED      (EQERR_BASE_PARAM + 23)
//��Ѷ����������
#define EQERR_INFOSIZE_TOOLARGE        (EQERR_BASE_PARAM + 24)
//��Ѷ��ѯ��������
#define EQERR_INFO_SEARCH_NODATA       (EQERR_BASE_PARAM + 25)
//��Ѷ�������ظ�
#define EQERR_INFOBKCODE_REPEAT		   (EQERR_BASE_PARAM + 26)

#pragma  endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//������Ϣ��������ö��
typedef enum
{
    eLang_ch,
    eLang_en,
} EQLang;

//EQVARTYPE��������ö��
typedef enum 
{
    eVT_null,
    eVT_char,
    eVT_byte,
    eVT_bool,
    eVT_short,
    eVT_ushort,
    eVT_int,
    eVT_uInt,
    eVT_int64,
    eVT_uInt64,
    eVT_float,
    eVT_double,
    eVT_byteArray,
    eVT_asciiString,
    eVT_unicodeString
} EQVarType;

// ����Events�ṹ����ö��
typedef enum 
{
    eMT_err,                             // ������Ϣ
    eMT_response,                        // ���ݷ���
    eMT_partialResponse,                 // �������ݷ��أ�����ʱ���ã�
    eMT_others,                          // ������Ϣ
} EQMsgType;

//���������ʽö��
typedef enum 
{
	ePT_NONE,                            // ��ʹ�ô���  
	ePT_HTTP,						     // HTTP����
	ePT_HTTPS,						     // HTTPS����
	ePT_SOCK4,						     // SOCK4����
	ePT_SOCK5                            // SOCK5����
} ProxyType;

//�µ���������ö��
typedef enum 
{
	eOT_default,                         // Ĭ��(Ĭ������ݴ���������������־����eOT_buy����eOT_Sell,�������Ͷ�����������ת��)
	eOT_buy,						     // ����
	eOT_sell,						     // ����
	eOT_purchase,						 // �깺
	eOT_redemption,                      // ���
} OperateType;

//��Ѷ��ѯ����ö��
typedef enum
{
	eCfnMode_StartToEnd = 1,             //starttime��endtime�м��������Ѷ
	eCfnMode_EndCount,                   //��ȡendtime�Ľ�count������
}eCfnMode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(push)
#pragma pack(8)

//char�����װ�ṹ��
typedef struct _tagEQCHAR
{
    char*        pChar;                            //�ַ�ָ������
    unsigned int nSize;                            //�ַ����鳤�ȣ�(�洢�ַ���ʱ����0��β���ȣ�
} EQCHAR;

//char��ά�����װ�ṹ��
typedef struct _tagEQCHARARRAY
{
    EQCHAR*      pChArray;                         //EQCHARָ������
    unsigned int nSize;                            //EQCHAR���鳤��
} EQCHARARRAY;

//EQVARIENT�������ͷ�װ�ṹ�壬�ɴ洢������������
typedef struct _tagEQVARIENT
{
    EQVarType          vtype;                      //ֵ����
    union 
    {
        char           charValue;
        bool           boolValue;
        short          shortValue;
        unsigned short uShortValue;
        int            intValue;
        unsigned int   uIntValue;
        int64_t        int64Value;
        uint64_t       uInt64Value;
        float          floatValue;
        double         doubleValue;
    } unionValues;                                 //������
    EQCHAR eqchar;                                 //�ַ�����
} EQVARIENT;

//EQVARIENT�������װ�ṹ��
typedef struct _tagEQVARIENTARRAY
{
    EQVARIENT*     pEQVarient;                       //EQVARIENTָ������
    unsigned int   nSize;                            //EQVARIENT���鳤��
} EQVARIENTARRAY;

//EQDATA���ݷ��ؽṹ��
typedef struct _tagEQDATA
{
    EQCHARARRAY    codeArray;                        //��Ʊ��������
    EQCHARARRAY    indicatorArray;                   //ָ������
    EQCHARARRAY    dateArray;                        //��������
    EQVARIENTARRAY valueArray;                       //ֵ����

    //operator ()(int,int,int)
    EQVARIENT* operator()( const unsigned int code, const unsigned int indicator,const unsigned int date=0 )
    {
        EQVARIENT* pEQVar = NULL;
        if(valueArray.nSize == 0) 
        {
            return pEQVar;
        }

        if(valueArray.nSize != codeArray.nSize * dateArray.nSize * indicatorArray.nSize)
        {
            return pEQVar;
        }

        if(code < codeArray.nSize && indicator < indicatorArray.nSize && date < dateArray.nSize)
        {
            int nIndex = codeArray.nSize * indicatorArray.nSize * date + indicatorArray.nSize * code + indicator;
            pEQVar = valueArray.pEQVarient;
            pEQVar += nIndex;
        }

        return pEQVar;
    }
    //EQVARIENT*
    EQVARIENT* GetAt(const unsigned int pos)
    {
        if(pos >= valueArray.nSize)
        {
            return NULL;
        }
        return &(valueArray.pEQVarient[pos]);
    }

} EQDATA, *PEQDATA;

//EQMSG���ݽṹ��(�첽���ػص�ʱʹ��)
typedef struct _tagEQMSG
{
    int            version;						     //�汾��
    EQMsgType      msgType;                          //Msg����
    EQErr          err;							     //������
    EQID           requestID;					     //����ID
    EQID           serialID;					     //��ˮ��
    EQDATA*        pEQData;      		             //����������
} EQMSG, *PEQMSG;

//��������ṹ��
typedef struct _tagEQCtrData
{
	int            row;                              //����
	int            column;                           //����
	EQCHARARRAY    indicatorArray;                   //ָ��������
	EQVARIENTARRAY valueArray;                       //ֵ����

	//operator ()(int,int)
	EQVARIENT* operator()( const unsigned int rowIndex, const unsigned int columnIndex)
	{
		EQVARIENT* pEQVar = NULL;
		if(valueArray.nSize == 0) 
		{
			return pEQVar;
		}

		if(valueArray.nSize != row * column)
		{
			return pEQVar;
		}

		if(rowIndex < row && columnIndex < column)
		{
			int nIndex = column * rowIndex + columnIndex;
			pEQVar = valueArray.pEQVarient;
			pEQVar += nIndex;
		}

		return pEQVar;
	}
	//EQVARIENT*
	EQVARIENT* GetAt(const unsigned int pos)
	{
		if(pos >= valueArray.nSize)
		{
			return NULL;
		}
		return &(valueArray.pEQVarient[pos]);
	}

} EQCTRDATA;

// ��¼��Ϣ
#define MAXSTRING 255
typedef struct _tagEQLOGININFO
{
	char userName[MAXSTRING];                        //��¼�û���
	char password[MAXSTRING];                        //��¼����
} EQLOGININFO;

//�µ���Ϣ
typedef struct _tagORDERINFO
{
	char           code[20];                         //֤ȯ����
	double         volume;                           //(OrderMode 0:��������  OrderMode 1:�ֲ�Ŀ������  OrderMode 2:�ֲ�Ŀ��Ȩ��)
	float          price;                            //���׼۸�
	int            date;                             //�������� yyyymmdd  8λ��
	int            time;                             //����ʱ�� hhmmss    6λ��
	OperateType    optype;                           //��������
	float          cost;                             //����
	float          rate;                             //����
	int            reserve;                          //�����ֶ�
} ORDERINFO, *PORDERINFO;

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��־�ص�����(���ӿ��е���־ͨ���˻ص��������)
typedef int (*logcallback)(const char* pLog);

//����ص�����(�첽����ʱʹ��)
typedef int (*datacallback) (const EQMSG* pMsg, LPVOID lpUserParam);

//�������ص�����(һ��Ҫ����һ�����ص����������ڵ���start֮ǰ���ã������ղ����˺ŵ���֪ͨ)
EMQUANTAPI EQErr setcallback(datacallback pfnCallback);

//�û������Զ���"ServerList.json.e"��"userInfo"�ļ��Ĵ��Ŀ¼(��������ô˺�������dir������Ĭ�ϵ�ǰĿ¼)
EMQUANTAPI void setserverlistdir(const char* dir);

//��ȡ�������ı�˵��
EMQUANTAPI const char* geterrstring(EQErr errcode, EQLang lang=eLang_en);

//����������� ע������ʹ�ô�������Ҫ�ڵ������нӿ�֮ǰ����
EMQUANTAPI EQErr setproxy(ProxyType type, const char* proxyip, unsigned short proxyport, bool verify, const char* proxyuser, const char* proxypwd);

/**�˹����� �������޽������л�������Զ��linux�����޷�����LoginActivator��������������ɹ��󽫻�õļ����ļ�"userInfo"�ŵ�"ServerList.json.e"ͬ��Ŀ¼���ٵ���start��¼
*  ����˵����
*  pLoginInfo���˻�������ṹ��ָ�루�ش��   options:�ɴ�����,�˹������Ὣ�����ļ�"userInfo"����������������� ���磺"email=who@what.com"  
*  pfnCallback����־�ص����� */
EMQUANTAPI EQErr manualactivate(EQLOGININFO* pLoginInfo, const char* options, logcallback pfnCallback);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**��¼(��ʼʱ����ߺ����) 
*  ����˵����
*  pLoginInfo����������,���贫(2.0.0.0�汾֮���Ϊ�����Զ���½,�����˲����Լ��ݾɰ汾)  
*  options�����Ӳ���,�ð�Ƕ��Ÿ���   �ֿ��� TestLatency=1������������,Ĭ��Ϊ0�����٣� 
*           ForceLogin=1 ��ǿ�Ƶ�¼��Ĭ��Ϊ0��ͨ��¼�� LogLevel=2(��־���� 1:Debug 2:Info 3:Error)
*  pfnCallback����־�ص�����*/
EMQUANTAPI EQErr start(EQLOGININFO* pLoginInfo, const char* options, logcallback pfnCallback);
//�˳�(�����˳�ʱ���ã�ֻ�����һ��)
EMQUANTAPI EQErr stop();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����˵��:
//    codes: ���ƴ���  ���������ð�Ƕ��Ÿ�����֧�ִ�Сд���� "300059.SZ,000002.SZ,000003.SZ,000004.SZ"
//    indicators: ����ָ�� ���ָ����ð�Ƕ��Ÿ�����֧�ִ�Сд���� "open,close,high"
//    startdate��enddate: ��ʼ���ںͽ�ֹ���ڡ����޷ָ����������Ϊ8λ���֡���ʽ֧��:YYYYMMDD YYYY/MM/DD YYYY/M/D YYYY-MM-DD YYYY-M-D
//    options: ���Ӳ���  ��������԰�Ƕ��Ÿ�����"Period=1,Market=CNSESH,Order=1,Adjustflag=1,Curtype=1,Pricetype=1,Type=1"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ָ��������ݲ�ѯ(ͬ������)
EMQUANTAPI EQErr csd(const char* codes, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
//�������ݲ�ѯ(ͬ������)
EMQUANTAPI EQErr css(const char* codes, const char* indicators, const char* options, EQDATA*& pEQData);
//��ȡ���������ڵĽ�����(ͬ������)
EMQUANTAPI EQErr tradedates(const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
//��ȡϵͳ���ɷ�(ͬ������)
EMQUANTAPI EQErr sector(const char* pukeyCode, const char* tradeDate, const char* options, EQDATA*& pEQData);
//��ȡƫ��N�Ľ�����(ͬ������)
#ifdef WIN32 
EMQUANTAPI EQErr getdate(const char* tradeDate, int offDay, const char* options, EQDATA*& pEQData);
#else
EMQUANTAPI EQErr gettradedate(const char* tradeDate, int offDay, const char* options, EQDATA*& pEQData);
#endif
//��ȡ���������ڵĽ���������(ͬ������)
EMQUANTAPI EQErr tradedatesnum(const char* startDate, const char* endDate, const char* options, int& num);

//����K��(ͬ������) //codeֻ֧�ֵ�����Ʊ/�ڻ�/ָ��
EMQUANTAPI EQErr csc(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
//����K��(ͬ������) //codeֻ֧�ֵ�����Ʊ/�ڻ�/ָ��
EMQUANTAPI EQErr cmc(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);
//����K��(ͬ������) //codeֻ֧�ֵ�����Ʊ/�ڻ�/ָ��
EMQUANTAPI EQErr chmc(const char* code, const char* indicators, const char* startDate, const char* endDate, const char* options, EQDATA*& pEQData);

//�������(ͬ������) ÿ��indicators���Ϊ64��
EMQUANTAPI EQErr csqsnapshot(const char* codes, const char* indicators, const char* options, EQDATA*& pEQData);
//��ȡר�ⱨ��(ͬ������)
EMQUANTAPI EQErr ctr(const char* ctrName, const char* indicators, const char* options, EQCTRDATA*& pEQCtrData);

/*����ѡ��(ͬ������)
* ����˵����
* cpsCodes:      ֤ȯ���뷶Χ,�ش�,֧������ģʽ 1.������ �� B_ ��ͷ���� "B_001004"; 2. ���ƴ��룬���������ð�Ƕ��Ÿ�������"000001.SZ,000002.SZ,600000.SH"
* cpsIndicators: ����ʽ����,����ʽ֮ǰ��Ӣ�ķֺŸ���,�ڲ��������ð�Ƕ��Ÿ��� ��   s1,open,2016/12/13,1;s2,close,2017-02-25,1;s3,listdate
* cpsConditions: ��������ʽ
* cpsOptions:    ������������,������,ȡǰN��ѡ�ɽ����
* pEQData:       ѡ�ɽ��*/
EMQUANTAPI EQErr cps(const char* cpsCodes, const char* cpsIndicators, const char* cpsConditions, const char* cpsOptions, EQDATA*& pEQData);
//����˻���ϵ��ѯ(ͬ������)
EMQUANTAPI EQErr pquery(const char* options, EQDATA*& pEQData);
//�����µ�(ͬ������)  pOrderInfo:�µ���Ϣָ������  orderInfoSize������Ԫ�ظ���  combinCode����ϴ���  remark�����˵��
EMQUANTAPI EQErr porder(ORDERINFO* pOrderInfo, int orderInfoSize, const char* combinCode, const char* remark, const char* options);
//�½����(ͬ������) combinCode:��ϴ���  combinName���������  initialFound����ʼ�ʽ����99999999999��  remark�����˵��
EMQUANTAPI EQErr pcreate(const char* combinCode, const char* combinName, int64_t initialFound, const char* remark, const char* options);
//ɾ�����(ͬ������) combinCode:��ϴ���
EMQUANTAPI EQErr pdelete(const char* combinCode, const char* options);
//��ϱ�����ѯ(ͬ������) combinCode:��ϴ���  indicator:��������
EMQUANTAPI EQErr preport(const char* combinCode, const char* indicator, const char* options, EQDATA*& pEQData);
//����ʽ����(ͬ������) combinCode:��ϴ���  transferdirect:IN �����ʽ� OUT �����ʽ�  date����������  opCash�����ӻ���ٵ��ʽ��� remark������˵��
EMQUANTAPI EQErr pctransfer(const char* combinCode, const char* transferdirect, const char* date, double opCash, const char* remark, const char* options);

//������̬����ͬ���ӿڷ�������ָ���ͷ��ڴ�
EMQUANTAPI EQErr releasedata(void* pEQData);
//���ָ�����(ͬ������)
EMQUANTAPI EQErr edb(const char* edbids, const char* options, EQDATA*& pEQData);
//���ָ��id�����ѯ(ͬ������)
EMQUANTAPI EQErr edbquery(const char* edbids, const char* indicators, const char* options, EQDATA*& pEQData);

//��Ѷ���ݲ�ѯ(ͬ������) codes�����ƴ��������루���ɻ�ϣ� content����ѯ����
EMQUANTAPI EQErr cfn(const char* codes, const char* content, eCfnMode emode, const char* options, EQDATA*& pEQData);
//�������ѯ��ͬ������
EMQUANTAPI EQErr cfnquery(const char* options, EQDATA*& pEQData);


//������������������Ϊͬ����������������������������������������������������������������������������
//������������������Ϊ�첽��������������������������������������������������������������������������
//���أ� EQID  ��ˮ��
//pfnCallback����ͬ�Ľӿڿ����趨��ͬ�Ļص�����NULL��ʹ��Ĭ�ϵ����ص�����
//lpUserParam: �û�����,�ص�ʱԭ������

//ʵʱ����(�첽)  ÿ��indicators���Ϊ64�� options: Pushtype=0 ��������  1ȫ������  2��������2(֤ȯ������ָ��ֵȫ��)
EMQUANTAPI EQID csq(const char* codes, const char* indicators, const char* options, datacallback pfnCallback, LPVOID lpUserParam, EQErr& nErrorID);
//ȡ��ʵʱ���鶩��   serialIDΪ0ʱ ȡ�����ж���
EMQUANTAPI EQErr csqcancel(EQID serialID);
//�������۷���(�첽)  startdatetime��enddatetime��ʽ(YYYYMMDDHHMMSS��HHMMSS��ʾϵͳ���ڵ����ʱ�䣬������ʹ��ͬһ�ָ�ʽ)
EMQUANTAPI EQID cst(const char* codes, const char* indicators, const char* startdatetime, const char* enddatetime, const char* options, datacallback pfnCallback, LPVOID lpUserParam, EQErr& nErrorID);

//��Ѷ���ĺ���(�첽)  codes�����ƴ��������루���ɻ�ϣ� content����������
EMQUANTAPI EQID cnq(const char* codes, const char* content, const char* options, datacallback pfnCallback, LPVOID lpUserParam, EQErr& nErrorID);

////��Ѷȡ������  serialIDΪ0ʱ ȡ�����ж���
EMQUANTAPI EQErr cnqcancel(EQID serialID);

#endif /*#ifndef _EMQUANTAPI_H_*/