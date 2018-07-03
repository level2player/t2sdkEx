#include <stdio.h>
#include <stdlib.h>

#ifndef _T2SDK_INTERFACE_H
# define _T2SDK_INTERFACE_H

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

#ifndef HS_IKNOWN_SDK
#define HS_IKNOWN_SDK
struct IKnown
{
    virtual unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv) = 0;

    virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;

    virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
    
    ~IKnown(){}
};
#endif

#include <string.h>

#ifdef _WIN32
typedef unsigned int		uint32;
#else
#include <sys/types.h>
#if defined(__linux__)
#include <stdint.h>
#endif
typedef uint32_t			uint32;
#endif

///ESB�������ȣ�����Ϊ�ɼ��ַ������ܰ���ʵ���ָ�����ո񡢷ֺ�;
#define IDENTITY_NAME_LENGTH	32
///ʵ��������ռλ����
#define ID_LENGTH               4 
///�ڵ���ȫ��,����ʱʹ��char sName[ID_STR_LEN+1]
#define ID_STR_LEN		       (IDENTITY_NAME_LENGTH + ID_LENGTH + 1)


//	����ӿ�������󳤶�,����ʱʹ��char sName[PLUGINID_LENGTH+1]
#define PLUGINID_LENGTH	256
//	���ʵ��������󳤶�,����ʱʹ��char sName[PLUGIN_NAME_LENGTH+1]
#define PLUGIN_NAME_LENGTH	(PLUGINID_LENGTH+ID_LENGTH+1)
//	��������󳤶�.����ʱʹ��char sName[SVR_NAME_LENGTH+1]
#define SVR_NAME_LENGTH	256
//	����ʵ������󳤶�.����ʱʹ��char sName[PLUGINID_NAME_LENGTH+1]
#define SVRINSTANCE_NAME_LENGTH	(SVR_NAME_LENGTH+ID_LENGTH+1)

//�ļ������б��ֶ�
/** �ļ����£����º�ΪAPI�����ļ����¹��������佻���Ĵ�����е��ֶ� */
#define PACKER_INT_FILE_LIST            "file_list"     /**< �ļ��б� */
#define PACKER_INT_FILE_ID              "file_id"       /**< �ļ�id */
#define PACKER_INT_FILE_SIZE            "file_size"     /**< �ļ���С */
#define PACKER_INT_TIME                 "time"          /**< �ļ�ʱ�� */
#define PACKER_STRING_FILE_NAME         "file_name"     /**< �ļ��� */
#define PACKER_STRING_FILE_PATH         "file_path"     /**< �ļ�·�� */
#define PACKER_STRING_LOCAL_PATH        "local_path"    /**< �����ļ�·�� */
#define PACKER_STRING_MD5_CODE          "md5_code"      /**< �ļ�md5ֵ */
#define PACKER_STRING_FILE_FLAG         "file_flag"     /**< �ļ���ʶ */

//ҵ����Ϣ����
//����
#define REQUEST_PACKET 0 
//Ӧ��
#define ANSWER_PACKET  1 
//20110302 xuxp ����·����Ϣ�Ľṹ�嶨��
typedef struct tagRouteInfo
{
	char ospfName[ID_STR_LEN+1];
	char nbrName[ID_STR_LEN+1];
	char svrName[SVRINSTANCE_NAME_LENGTH+1];
	char pluginID[PLUGIN_NAME_LENGTH+1];
	int connectID;
	int memberNO;

	tagRouteInfo()
	{
		memset(this,0,sizeof(tagRouteInfo));
	}
}Route_Info;


//20101228 xuxp Ϊ�˷��ͺͷ��ض���������Ϣ�����ӵĽṹ��Ķ���
typedef struct tagRequestData
{	
	int sequeceNo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	void* lpFileHead;
	int fileHeadLen;
	int packetType;//20100111 xuxp �¼ӵİ�����
	Route_Info routeInfo;//20110302 xuxp ������������·����Ϣ
	int iSubSystemNo;//20130508 xuxp ������������ϵͳ�Ŵ���
	int iCompanyID;//20140114 xuxp ���ӹ�˾���
}REQ_DATA, *LPREQ_DATA;
typedef struct tagRespondData
{
	int functionID;
	int returnCode;
	int errorNo;
	char* errorInfo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	Route_Info sendInfo;//20110302 xuxp Ӧ���������ӷ�������Ϣ
}RET_DATA, *LPRET_DATA;

//20150209 majc  ���Ӻ궨��
#define T2SDK_MAX_BRANCH_NO_LEN  256 
#define T2SDK_MAX_COMPANY_NO_LEN 256 
#define T2SDK_MAX_OSPF_LEN       256

//20150209 majc ���Ӵ���������ʱ��ָ��·�ɲ����ṹ�嶨��
typedef struct tagSubRouteInfo
{
	int iSystemNo;                       //ϵͳ��
	int iSubSystemNo;                    //��ϵͳ��
	char szBranchNo[T2SDK_MAX_BRANCH_NO_LEN+1];       //��֧��
	char szCompanyNo[T2SDK_MAX_COMPANY_NO_LEN+1];        //��˾���
	char szOspfName[T2SDK_MAX_OSPF_LEN+1];         //OSPF
	tagSubRouteInfo()
	{
		memset(this,0,sizeof(tagSubRouteInfo));
	}
}SUB_ROUTER_INFO;

///������ӿ�
struct IF2ResultSet : public IKnown
{

	///ȡ�ֶ���
    /**@return �����ֶ���.
      */
    virtual int FUNCTION_CALL_MODE GetColCount()=0;

    ///ȡ�ֶ���
    /** @param column:�ֶ����(��0Ϊ����)
      * @return �����ֶ���  �±�Խ�� ����NULL
      */
    virtual const char * FUNCTION_CALL_MODE GetColName(int column)=0;

    //ȡ�ֶ���������
    /** @param column:�ֶ����(��0Ϊ����)
      * @return:�����泣������;�±�Խ�� ����-1
      */
    virtual char FUNCTION_CALL_MODE GetColType(int column)=0;


   ///ȡ�������ֶ�С��λ��
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶ�����С��λ�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColScale(int column)=0;
  
   //ȡ�ֶ����������ݵ������.
   /** @param column:�ֶ����(��0Ϊ����)
     * @return int �����ֶο�� �±�Խ�� ����-1
     */
   virtual int FUNCTION_CALL_MODE GetColWidth(int column) = 0;

   ///ȡ�ֶ�����Ӧ���ֶ����
   /**@param columnName: �ֶ���
     *@return �����ֶ����. �����ڷ���-1
     */
   virtual int  FUNCTION_CALL_MODE FindColIndex(const char * columnName)=0;

    //
    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ(�ַ���)
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ������ֶ�ֵ,�±�Խ�緵��NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStrByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ(�ַ���)
    /**@param columnName: �ֶ���
      *@return �ַ������ֶ�ֵ,�����ڷ���NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStr(const char * columnName)=0;

    //���ֶ����(��0Ϊ����)��ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return �ַ����ֶ�ֵ,�±�Խ�緵��'\0'.
      */
     virtual char  FUNCTION_CALL_MODE  GetCharByIndex(int column)=0;

    //���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName: �ֶ���
     *@return �ַ����ֶ�ֵ,�����ڷ���'\0'
     */
    virtual char   FUNCTION_CALL_MODE GetChar(const char * columnName)=0;

    //���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return double���ֶ�ֵ,�±�Խ�緵��0
      */
    virtual double  FUNCTION_CALL_MODE GetDoubleByIndex( int column)=0;
    
	///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return double���ֶ�ֵ,�����ڷ���0
      */
    virtual double  FUNCTION_CALL_MODE GetDouble(const char * columnName)=0;

    ///���ֶ���ţ�ȡ�ֶ�ֵ
    /**@param column:�ֶ����(��0Ϊ����)
      *@return int���ֶ�ֵ,�±�Խ�緵��0
      */
    virtual int  FUNCTION_CALL_MODE GetIntByIndex(int column)=0;

    ///���ֶ�����ȡ�ֶ�ֵ
    /**@param columnName:�ֶ���
      *@return int���ֶ�ֵ,�����ڷ���0
      */
    virtual int FUNCTION_CALL_MODE GetInt(const char * columnName)=0;

	///���ֶ���Ż���ֶ�ֵ,����������
	/**@param column: �ֶ����(��0Ϊ����)
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRawByIndex(int column,int * lpRawLen) = 0;

	///���ֶ�����ȡ�ֶ�ֵ
	/**@param columnName:�ֶ���
	*@param   lpRawLen: [out]���ݳ���
	*@return : �����׵�ַ
	*/
	virtual void *  FUNCTION_CALL_MODE GetRaw(const char * columnName,int * lpRawLen) = 0;


	///���һ��ȡ���ֶ�ֵ�Ƿ�ΪNULL
   /**@return 0 �ǣ� 1����
   */
    virtual int  FUNCTION_CALL_MODE WasNull()=0;

    ///ȡ��һ����¼
    virtual void  FUNCTION_CALL_MODE Next()=0;

    ///�ж��Ƿ�Ϊ��β
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEOF()=0;
   
	///�ж��Ƿ�Ϊ��
    /**@return 1 �ǣ�0 ����;
      */
    virtual int  FUNCTION_CALL_MODE IsEmpty()=0;
    
    virtual void * FUNCTION_CALL_MODE Destroy() = 0;
};

struct IF2UnPacker;

///����������ӿ�(һ�������ж���칹�����)
/**ִ������:
 *
 * 0��׼��(��ѡ, ����иò���, ����IF2Packer�ڲ������ڴ滺��)�� SetBuffer(),�������������ɵ������ṩ,�������BeginPack()֮ǰ׼��;
 *
 * 1����ʼ:  BeginPack(),�������λ;
 *
 * 2����һ������������
 *
 *(a)����ֶ����б���AddField()
 *
 *(b)���ս������ά��˳�����ֶΣ�������¼���ֶ�����������ݣ�AddStr() {AddInt(), AddDouble(), AddRaw()}
 *
 * 3�����ý�����ķ�����(��ѡ��������, �򷵻���Ϊ0) SetReturnCode()
 *
 * 4������һ�������(��ѡ) NewDataSet()���˴�ͬʱ�����˸ý�����ķ����룻
 * 
 * 5���ο���2��ʵ����һ����������(��ѡ)��
 *
 * 6��������EndPack(),�ظ����ûᵼ�¼���ս����;
 *
 * 7��ȡ������(����������������С�����ݳ���)
 *    ������Ҳ����ֱ�ӽ��UnPack()���ؽ���ӿ�
 *
 *ʹ��ע������:IF2Packer��ʹ�õ��ڴ滺�������ɵ����߸�����գ�
 *             ����������ķ����룬ֻ���ڰ���ʽ�汾0x21������ʱ��Ч��
 */
struct IF2Packer : public IKnown
{
    ///�������ʼ��(ʹ�õ����ߵĻ�����)
	/** ��һ��ʹ�ô����ʱ������ʹ�ñ��������úû�����(���ݳ��ȱ���ΪiDataLen)
	 *@param  char * pBuf  ��������ַ
 	 *@param  int iBufSize  �������ռ�
 	 *@param  int iDataLen  �������ݳ��ȣ��������ݼ�����������֮��ֻ��V1.0��ʽ�İ���Ч�� 	 
 	 */
	virtual void FUNCTION_CALL_MODE SetBuffer(void * pBuf,int iBufSize,int iDataLen=0 )=0;

	///��λ�����¿�ʼ����һ����(�ֶ������¼����Ϊ0��0��)
	/**
	 * ���ܣ���ʼ������Ѱ���������(�ظ�ʹ�����еĻ������ռ�)
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE BeginPack(void)=0;

	///��ʼ��һ�������
	/**�ڴ򵥽�����İ�ʱ�����Բ����ñ�����,��ȡĬ��ֵ
	 *@param const char *szDatasetName 0x20������Ҫָ�����������
	 *@param int iReturnCode           0x20������ҪΪÿ�������ָ������ֵ
	 */
	virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0)=0;

	/**
	 * ���ܣ��������ֶ�
	 *
	 *��ִ�д���Ҫ��:�� NewDataset()��Reset(),SetBuffer()֮��,����ֶΰ�˳�����;
	 *
	 *@param szFieldName���ֶ���
	 *@param cFieldType ���ֶ�����:I������D��������C�ַ���S�ַ�����R�������������
	 *@param iFieldWidth ���ֶο�ȣ���ռ����ֽ�����
	 *@param iFieldScale ���ֶξ���,��cFieldType='D'ʱ��С��λ��(ȱʡΪ4λС��)
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddField(const char *szFieldName,char cFieldType ='S',int iFieldWidth=255,int iFieldScale=4)=0;

	/**
	 * ���ܣ��������ַ�������
     * ��ִ�д���Ҫ��:�����������ֶ�������֮��,����ֶΰ�˳�����;
	 *@param       szValue���ַ�������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddStr(const char *szValue)=0;

	/**
     * ���ܣ���������������
 	 *@param       iValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddInt(int iValue)=0;
	
    /**
	 * ���ܣ������Ӹ�������
	 *@param       fValue����������
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddDouble(double fValue)=0;

	/**
	 * ���ܣ�������һ���ַ�
	 *@param		 cValue���ַ�
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddChar(char cValue)=0;

	/**
	 * ���ܣ�������һ�������
	 *@param	void * lpBuff ������
	 *@param	int iLen  ���ݳ���	 
	 *@return ������ʾʧ�ܣ�����ΪĿǰ���ĳ���
	 */
	virtual int FUNCTION_CALL_MODE AddRaw(void * lpBuff,int iLen)=0;

    ///�������
	virtual void FUNCTION_CALL_MODE EndPack()=0;
 
	/**
     * ���ܣ�ȡ������ָ��
	 *@return ������ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;
	
	/**
     * ���ܣ�ȡ����������
     *@return ����������
	 */
	virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * ���ܣ�ȡ��������������С
     *@return ��������������С
	 */
	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
	
	/**
	 * ���ܣ�ȡ�����ʽ�汾
     *@return �汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;
	
	///���ý�����ķ�����(0x20������Ҫ��)������������Ҫ����
	/**������ȡȱʡֵ0�������ã�������ã��������EndPack()֮ǰ����
     *@return �汾
	 */
	virtual void FUNCTION_CALL_MODE SetReturnCode(unsigned long dwRetCode) = 0;

	/**ֱ�ӷ��ص�ǰ�������Ľ���ӿ�,������EndPack()֮����ܵ���,�ڴ�����ͷ�ʱ��Ӧ�Ľ����ʵ��Ҳ�ͷ�
     *@return ������ӿڣ��˽���ӿڲ��ܵ��� destroy()���ͷ�
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE UnPack(void) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE ClearValue() = 0;
	
	
	//20110302 xuxp ����һ���ӿں������������ݵ�һ�������������
	///��λ�����¿�ʼ����һ����(�ֶ������¼����Ϊ0��0��)
	/**
	 * ���ܣ���ʼ������Ѱ���������(�ظ�ʹ�����еĻ������ռ�)
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE BeginPackEx(char* szName = NULL) = 0;

	//20110324 dongpf ����һ���ӿں�����������λ��ǰ�����
	///��λ��ǰ�����(�ֶ������¼����Ϊ0��0��)����Ӱ�����������
	/**
	 * ���ܣ���λ��ǰ�����
	 *@return ��
	 */
	virtual void FUNCTION_CALL_MODE ClearDataSet() = 0;
};

///������ӿ�
struct IF2UnPacker : public IF2ResultSet
{
	/**ȡ�����ʽ�汾
     *@return �汾
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;

	/**ȡ������ݳ���
     *@return 							0 ��ʾ�ɹ��� ����Ϊʧ��
	 */
	virtual int FUNCTION_CALL_MODE Open(void * lpBuffer,unsigned int iLen) = 0;

    ///ȡ���������(0x20���ϰ汾֧��)
    virtual int FUNCTION_CALL_MODE GetDatasetCount()=0;

    ///���õ�ǰ�����(0x20���ϰ汾֧��)
    /**
	 *@param  int nIndex				��������
	 *@return int						��0 ��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDatasetByIndex(int nIndex)=0;

    ///���õ�ǰ����� (0x20���ϰ汾֧��)
    /**
	 *@param  const char *szDatasetName	���������
	 *@return int						��0 ��ʾ�ɹ�������Ϊʧ��
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDataset(const char *szDatasetName)=0;

	/** ȡ���������ָ��
	 *@return ������ָ��
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;

	/** ȡ������ݳ���
     *@return ������ݳ���
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetPackLen(void) = 0;

	/**ȡ������ݼ�¼����,20051207�Ժ�汾֧��
     *@return ��¼����
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetRowCount(void) = 0;
	
	///������м�¼�α�ӿڣ�ȡ�������������¼
    virtual void FUNCTION_CALL_MODE First() = 0;

    ///������м�¼�α�ӿڣ�ȡ����������һ����¼
    virtual void FUNCTION_CALL_MODE Last() = 0;

    ///������м�¼�α�ӿڣ�ȡ������ĵ�n����¼��ȡֵ��Χ[1, GetRowCount()]
    virtual void FUNCTION_CALL_MODE Go(int nRow) = 0;
	
	///��ȡ��ǰ��������ֵĽӿ�,û�����ַ���""
	virtual const char* FUNCTION_CALL_MODE GetDatasetName() = 0;
	
	virtual int FUNCTION_CALL_MODE OpenAndCopy(void * lpBuffer,unsigned int iLen) = 0;
	
	//20140623 majc ���Ӹ������ֻ�ȡ�ֶ����ͣ��ֶξ��ȣ��ֶ���󳤶�
	//ȡ�ֶ���������
    /** @param columnName:�ֶ���
      * @return:�����泣������;���������� Ĭ�Ϸ���'S'
      */
    virtual char FUNCTION_CALL_MODE GetColTypeByName(const char * columnName)=0;


   ///ȡ�������ֶ�С��λ��
   /** @param columnName:�ֶ���
     * @return int �����ֶ�����С��λ�� ���������� ����0 
     */
   virtual int FUNCTION_CALL_MODE GetColScaleByName(const char * columnName)=0;
  
   //ȡ�ֶ����������ݵ������.
   /** @param columnName:�ֶ���
     * @return int �����ֶο�� ���������� ����1
     */
   virtual int FUNCTION_CALL_MODE GetColWidthByName(const char * columnName) = 0;
};

///���Ӷ��� CConnectionInterface �Ĳ������ö���CConfigInterface
/**
* �������ļ����ء����浽�ļ�����д����
*/
class CConfigInterface: public IKnown
{
public:
	/**
    * ���ļ�����
    * @param szFileName �ļ�������ʽ����ini������ο�������ʾ��
    * @return ����0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

    /**
    * ���浽�ļ�
    * @param szFileName �ļ���
    * @return ����0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

    /**
    * ȡ�ַ���ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param szDefault ȱʡֵ
    * @return �ַ���ֵ��û���ҵ�ʱ����szDefault
    */
    virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

    /**
    * ȡ����ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param iDefault  ȱʡֵ
    * @return ����ֵ��û���ҵ�ʱ����iDefault
    */
    virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

    /**
    * �����ַ���ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param szValue   ֵ
    * @return 0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

    /**
    * ��������ֵ
    * @param szSection ����
    * @param szEntry   ������
    * @param iValue    ֵ
    * @return 0��ʾ�ɹ�������ʧ��
    */
    virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};


typedef struct tagBizRouteInfo
{
	char ospfName[ID_STR_LEN+1];//·��Ŀ��ڵ��м������
	char nbrName[ID_STR_LEN+1];//�м���ڵ���ھ�����
	char svrName[SVRINSTANCE_NAME_LENGTH+1];//�м���Ľ�������
	char pluginID[PLUGIN_NAME_LENGTH+1];//�м�������
	int connectID;//���Ӻ�
	int memberNO;//��Ա���
	
	tagBizRouteInfo()
	{
		memset(this,0,sizeof(tagBizRouteInfo));
	}
}BIZROUTE_INFO;


struct IBizMessage : public IKnown
{
	//���ù��ܺ�
	virtual void FUNCTION_CALL_MODE SetFunction(const int nFUnctionNo) = 0;
	//��ȡ���ܺ�
	virtual int FUNCTION_CALL_MODE GetFunction() = 0;

	//���ð�����
	virtual void FUNCTION_CALL_MODE SetPacketType(const int nPacketType) = 0;
	//��ȡ������
	virtual int FUNCTION_CALL_MODE GetPacketType() = 0;

	//����Ӫҵ����
	virtual void FUNCTION_CALL_MODE SetBranchNo(const int nBranchNo) = 0;
	//��ȡӪҵ����
	virtual int FUNCTION_CALL_MODE GetBranchNo() = 0;

	//����ϵͳ��
	virtual void FUNCTION_CALL_MODE SetSystemNo(const int nSystemNo) = 0;
	//��ȡϵͳ��
	virtual int FUNCTION_CALL_MODE GetSystemNo() = 0;

	//������ϵͳ��
	virtual void FUNCTION_CALL_MODE SetSubSystemNo(const int nSubSystemNo) = 0;
	//��ȡ��ϵͳ��
	virtual int FUNCTION_CALL_MODE GetSubSystemNo() = 0;

	//���÷����߱��
	virtual void FUNCTION_CALL_MODE SetSenderId(const int nSenderId) = 0;
	//��ȡ�����߱��
	virtual int FUNCTION_CALL_MODE GetSenderId() = 0;

	//���ð����
	virtual void FUNCTION_CALL_MODE SetPacketId(const int nPacketId) = 0;
	//��ȡ�����
	virtual int FUNCTION_CALL_MODE GetPacketId() = 0;

	//����Ŀ�ĵ�·��
	virtual void FUNCTION_CALL_MODE SetTargetInfo(const BIZROUTE_INFO targetInfo) = 0;
	//��ȡĿ�ĵ�·��
	virtual void FUNCTION_CALL_MODE GetTargetInfo(BIZROUTE_INFO& targetInfo) = 0;
	
	//���÷�����·��
	virtual void FUNCTION_CALL_MODE SetSendInfo(const BIZROUTE_INFO sendInfo) = 0;
	//��ȡ������·��
	virtual void FUNCTION_CALL_MODE GetSendInfo(BIZROUTE_INFO& sendInfo) = 0;

	//���ô����
	virtual void FUNCTION_CALL_MODE SetErrorNo(const int nErrorNo) = 0;
	//��ȡ�����
	virtual int FUNCTION_CALL_MODE GetErrorNo() = 0;
	
	//���ô�����Ϣ
	virtual void FUNCTION_CALL_MODE SetErrorInfo(const char* strErrorInfo) = 0;
	//��ȡ������Ϣ
	virtual const char* FUNCTION_CALL_MODE GetErrorInfo() = 0;
	
	//���÷�����
	virtual void FUNCTION_CALL_MODE SetReturnCode(const int nReturnCode) = 0;
	//��ȡ������
	virtual int FUNCTION_CALL_MODE GetReturnCode() = 0;

	//����ҵ������
	virtual void FUNCTION_CALL_MODE SetContent(void* lpContent,int iLen) = 0;
	//��ȡҵ������
	virtual const void* FUNCTION_CALL_MODE GetContent(int& iLen) = 0;

	//���½ӿ�������Ϣ����1.0�Ķ���
	//���ö�������
	virtual void FUNCTION_CALL_MODE SetIssueType(const int nIssueType) = 0;
	//��ȡ��������
	virtual int FUNCTION_CALL_MODE GetIssueType() = 0;

	//�������
	virtual void FUNCTION_CALL_MODE SetSequeceNo(const int nSequeceNo) = 0;
	//��ȡ���
	virtual int FUNCTION_CALL_MODE GetSequeceNo() = 0;

	//���ùؼ��ֶ���Ϣ
	virtual void FUNCTION_CALL_MODE SetKeyInfo(void* lpKeyData,int iLen) = 0;
	//��ȡ�ؼ��ֶ���Ϣ
	virtual const void* FUNCTION_CALL_MODE GetKeyInfo(int& iLen) = 0;

	//���ø������ݣ���������ʱԭ������
	virtual void FUNCTION_CALL_MODE SetAppData(const void* lpAppdata,int nAppLen) = 0;
	//��ȡ�������ݣ���������ʱԭ������
	virtual const void* FUNCTION_CALL_MODE GetAppData(int& nAppLen) = 0;

	//����תӦ��
	virtual int	FUNCTION_CALL_MODE ChangeReq2AnsMessage() = 0;

	//��ȡ������
	virtual void* FUNCTION_CALL_MODE GetBuff(int& nBuffLen) = 0;
	//����������
	virtual int	FUNCTION_CALL_MODE SetBuff(const void* lpBuff,int nBuffLen) = 0;

	//�����Ϣ�ڵ��ֶΣ������´θ��á�
	virtual void FUNCTION_CALL_MODE ReSet() = 0;
	
	//���ù�˾���
	virtual void FUNCTION_CALL_MODE SetCompanyID(const int nCompanyID) = 0;
	//��ȡ��˾���
	virtual int FUNCTION_CALL_MODE GetCompanyID() = 0;
	
	//���÷����߹�˾���
	virtual void FUNCTION_CALL_MODE SetSenderCompanyID(const int nSenderCompanyID) = 0;
	//��ȡ�����߹�˾���
	virtual int FUNCTION_CALL_MODE GetSenderCompanyID() = 0;
};

#define IDENTITY_NAME_LENGTH    32  /**< �ͻ������ֳ��� */
#define MAX_MACADDRESS_LEN	    18  /**< MAC ��ַ���� */
#define MAX_RAND_LEN	        4   /**< ��������� */

/** �ͻ���ʶ���� */
#define MAX_BIZNAME_LEN \
	IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

#define INIT_RECVQ_LEN 256          /**< ���ն��г�ʼ���� */
#define STEP_RECVQ_LEN 512          /**< ���ն�����չ���� */
#define SIMPLIFIED_CHINESE      0   /**< ������Ϣ����:�������� */
#define ENGLISH                 1   /**< ������Ϣ����:Ӣ�� */
#define MAX_FILTERFIELD_LEN 63      /**< �����ֶγ��� */

/** ����ɿ��ȼ� */
enum ReliableLevel
{
    LEVEL_DOBEST            = 0,    /**< ������Ϊ */
    LEVEL_DOBEST_BYSEQ      = 1,    /**< �������� */
    LEVEL_MEM               = 2,    /**< �ڴ� */
    LEVEL_FILE              = 3,    /**< �ļ� */
    LEVEL_SYSTEM            = 4     /**< ϵͳ */
};

/** 
 * �������ӿ�
 */
class CFilterInterface:public IKnown
{
public:
   /**
    * �����±��ȡ��������������
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±�������������֣����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterNameByIndex(int index) = 0;

   /**
    * �����±��ȡ����������ֵ
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValueByIndex(int index)= 0;

   /**
    * ���ݹ������������ֻ�ȡ����������ֵ
    * @param fileName ��Ӧ�Ĺ�����������
    * @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValue(char*  fileName)= 0;

   /**
    * ��ȡ���������ĸ���
    * @return ���ض�Ӧ���������ĸ�����û�з���0
    */
    virtual int   FUNCTION_CALL_MODE GetCount() = 0;

   /**
    * ���ù������������ݹ����������ֺ�ֵ
    * @param filterName ��Ӧ�Ĺ�����������
    * @param filterValue ��Ӧ�Ĺ����������ֵ�ֵ
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue) =0;
};

/**
 * ���Ĳ�����ӿ�
 */
class CSubscribeParamInterface:public IKnown
{
public:

   /**
    * ������������
    * @param szName ��Ӧ����������
    */
    virtual void FUNCTION_CALL_MODE  SetTopicName(char* szName) =0;

   /**
    * ���ø�������
    * @param lpData �������ݵ��׵�ַ
    * @param iLen �������ݵĳ���
    */
    virtual void FUNCTION_CALL_MODE  SetAppData(void* lpData,int iLen)=0;
    
   /**
    * ��ӹ�������
    * @param filterName ��������������
    * @param filterValue ����������ֵ
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue)=0;

   /**
    * ��ӷ����ֶ�
    * @param filedName ��Ҫ��ӵķ����ֶ�
    */
    virtual void FUNCTION_CALL_MODE  SetReturnFiled(char* filedName)=0;

   /**
    * �����Ƿ�ȱ��־
    * @param bFromNow true��ʾ��Ҫ֮ǰ�����ݣ�Ҳ���ǲ�ȱ��false��ʾ����Ҫ��ȱ
    */
    virtual void FUNCTION_CALL_MODE  SetFromNow(bool bFromNow)=0;

   /**
    * ���ø��Ƕ��ı�־
    * @param bReplace true��ʾ���Ƕ��ģ�ȡ��֮ǰ�����ж��ģ�ֻ����ǰ�Ķ��ģ�false��ʾ׷�Ӷ���
    */
    virtual void FUNCTION_CALL_MODE  SetReplace(bool bReplace)=0;

   /**
    * ���÷��ͼ��
    * @param nSendInterval ��λ����
    */
    virtual void FUNCTION_CALL_MODE  SetSendInterval(int nSendInterval)=0;

   /**
    * ��ȡ��������
    * @return ��������������Ϣ
    */
    virtual char* FUNCTION_CALL_MODE  GetTopicName() =0;

   /**
    * ��ȡ��������
    * @param iLen ���Σ���ʾ�������ݵĳ���
    * @return ���ظ��������׵�ַ��û�з���NULL
    */
    virtual void* FUNCTION_CALL_MODE  GetAppData(int *iLen) =0;

   /**
    * ��ȡ��Ӧ�Ĺ����ֶε�����
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±�������������֣����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterNameByIndex(int index) = 0;

   /**
    * �����±��ȡ����������ֵ
    * @param index ��Ӧ�Ĺ��������±�
    * @return ���ض�Ӧ���±����������ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValueByIndex(int index)= 0;

   /**
    * ���ݹ������������ֻ�ȡ����������ֵ
    * @param fileName ��Ӧ�Ĺ�����������
    * @return ���ض�Ӧ�Ĺ����������ֵ�����ֵ�����򷵻�NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValue(char*  fileName)= 0;

   /**
    * ��ȡ���������ĸ���
    * @return ���ض�Ӧ���������ĸ�����û�з���0
    */
    virtual int   FUNCTION_CALL_MODE  GetFilterCount() = 0;

   /**
    * ��ȡ�����ֶ�
    * @return ���ض�Ӧ�ķ����ֶ���Ϣ
    */
    virtual char* FUNCTION_CALL_MODE  GetReturnFiled()=0;

   /**
    * ��ȡ�Ƿ�ȱ�ı�־
    * @return ���ض�Ӧ�Ĳ�ȱ��־
    */
    virtual bool  FUNCTION_CALL_MODE  GetFromNow()=0 ;

   /**
    * ��ȡ�Ƿ񸲸Ƕ��ĵı�־
    * @return ���ض�Ӧ�ĸ��Ƕ��ı�־
    */
    virtual bool  FUNCTION_CALL_MODE  GetReplace() =0;

   /**
    * ��ȡ��Ӧ�ķ���Ƶ��
    * @return ���ض�Ӧ�ķ��ͼ��
    */
    virtual int   FUNCTION_CALL_MODE  GetSendInterval()=0;
    
	/**
    * �����Ƿ������Ϣ���
    * @param bUpdate true��ʾ��Ҫ������Ϣ��ţ�false��ʾ������
    */
    virtual void FUNCTION_CALL_MODE  SetUpdateMsgNo(bool bUpdate)=0;

	/**
    * ��ȡ�Ƿ������Ϣ���
    * @return �����Ƿ������Ϣ���
    */
    virtual bool  FUNCTION_CALL_MODE  GetUpdateMsgNo()=0;
};

class CSubscribeInterface;

/**
 * @brief ���Ļص��ӿڷ��ص����ݶ��壬���˶�����Ҫ��ҵ����֮�⣬����Ҫ���ص�����
 */
typedef struct tagSubscribeRecvData
{
	char* lpFilterData;     /**< �����ֶε�����ͷָ�룬�ý������� */
	int iFilterDataLen;     /**< �����ֶε����ݳ��� */
	char* lpAppData;        /**< �������ݵ�����ͷָ�� */
	int iAppDataLen;        /**< �������ݵĳ��� */
	char szTopicName[260];  /**< �������� */
	
   /**
    * tagSubscribeRecvData ���캯��
    */
	tagSubscribeRecvData()
	{
		memset(this,0,sizeof(tagSubscribeRecvData));
	}
}SUBSCRIBE_RECVDATA, *LPSUBSCRIBE_RECVDATA;

/**
 * ���Ļص��ӿڣ��ϲ�Ӧ��ͨ������ӿڣ��������ƹ�������Ϣ
 */
class CSubCallbackInterface: public IKnown
{
public:

   /**
    * �յ�������Ϣ�Ļص�
    * @param lpSub �ص��Ķ���ָ��
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @param lpData ������Ϣ�Ķ�����ָ�룬һ������Ϣ��ҵ����������
    * @param nLength ���������ݵĳ���
	* @param lpRecvData ������Ϣ�������ֶη��أ���Ҫ�����˸������ݣ�������Ϣ���������֣���ϸ�ο�ǰ��ṹ�嶨��
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData) = 0;

   /**
    * �յ��޳����������Ϣ�ص���һ����ӵ�����˲��Ե������»�ص�����ӿ�,����ص����治��Ҫȡ�����ģ��ײ��Ѿ�ȡ��������ģ�ֻ��һ��֪ͨ�ӿ�
    * @param lpSub �ص��Ķ���ָ��
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @param TickMsgInfo ���˵Ĵ�����Ϣ����Ҫ�ǰ��������ظ��Ķ�����λ����Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) = 0;
};


/**
 * ���ĽӿڵĶ���
 */
class CSubscribeInterface: public IKnown
{
public:

   /**
    * ��������
    * @param lpSubscribeParamInter ���涨��Ķ��Ĳ����ṹ
    * @param uiTimeout ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ��������ĳɹ�û�з��أ������������Ҫ�������Release�ͷ�
                          �������ҵ��У��Ĵ�����Ϣ��д�����£�
                          IF2UnPacker* lpBizUnPack =NULL;
                          SubscribeTopic(...,&lpBizUnPack);
                          �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                          ��������Ϣ��ȡ��֮��,�ͷ�
                          lpBizUnPack->Release();
    * @param lpBizPack ҵ��У����Ҫ���ӵ�ҵ���ֶ��Լ�ֵ��û�о͸��ݹ���������Ϊҵ��У���ֶ�
    * @return ����ֵ����0����ʾ��ǰ���ĳɹ��Ķ��ı�ʶ������Ҫ��ס�����ʶ�Ͷ�����֮���ӳ���ϵ�������ʶ��Ҫ����ȡ�����ĺͽ�����Ϣ�Ļص�����.
	*		  ��������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE SubscribeTopic(CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2UnPacker** lppBizUnPack=NULL,IF2Packer* lpBizPack=NULL) = 0;

   /**
    * ȡ����������
    * @param subscribeIndex ��Ϣ��Ӧ�Ķ��ı�ʶ�������ʶ������SubscribeTopic�����ķ���
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int subscribeIndex) = 0;


	/**
    * ȡ����������
    * @param topicName ��������
    * @param lpFilterInterface ��Ӧ�Ĺ�������
    * @return ����0��ʾȡ�����ĳɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface) = 0;



   /**
    * ��ȡ��ǰ���Ľӿ��Ѿ����ĵ����������Լ�����������Ϣ
    * @param lpPack ���洫��Ĵ����
    * @note packer�����ֶ�
        - SubcribeIndex
        - IsBornTopic
        - TopicName
        - TopicNo
        - FilterRaw
        - Appdata
        - SendInterval
        - ReturnFileds
        - isReplace
        - isFromNow
    */
    virtual void FUNCTION_CALL_MODE GetSubcribeTopic(IF2Packer* lpPack)=0;
	
	
	/**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
	 /**
    * ��ȡ����˵�����������Ϣ
    * @param byForce �Ƿ�ǿ�ƴӺ�̨��ȡ
    * @param iTimeOut ��ʱʱ��
    * @return �ɹ��ͷ�������������Ϣ
    * @note �����������Ҫ����release�ӿڽ����ͷ�.
    * @note packer�����ֶ�
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
	* - FilterField7
	* - FilterField8
	* - FilterField9
	* - FilterField10
	* - FilterField11
	* - FilterField12
	* - FilterField13
	* - FilterField14
	* - FilterField15
	* - FilterField16
    * - SubscribeStr 
    * - PublishStr
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;


	/**
	*�������ĵĽӿ�
	*@param lpSubReqUnpack ���������ļ��ϣ�����unpack����ʽ����
	*����Ľ��������������ֶ����£�
	*TopicName SendInterval  ReturnFileds isFromNow AppData
	*FilterField1 FilterValue1 FilterField2 FilterValue2 FilterField3 FilterValue3 FilterField4 FilterValue4
	*FilterField5 FilterValue5 FilterField6 FilterValue6 FilterField7 FilterValue7 FilterField8 FilterValue8
	*FilterField9 FilterValue9 FilterField10 FilterValue10 FilterField11 FilterValue11 FilterField12 FilterValue12
	*FilterField13 FilterValue13 FilterField14 FilterValue14 FilterField15 FilterValue15 FilterField16 FilterValue16
	*BizCheckPack(���ڶ�����Ӧ�����ҵ��У��unpack�������Ƹ�ʽ���)
	*@param lpSubAnsPacker ���Ľ���ķ��أ����ⲿ����һ���յĴ�����������ڲ���ÿ�����Ľ������������
	*�����Ĵ�����������ֶ����£�
	*TopicName SendInterval  ReturnFileds isFromNow AppData
	*FilterField1 FilterValue1 FilterField2 FilterValue2 FilterField3 FilterValue3 FilterField4 FilterValue4
	*FilterField5 FilterValue5 FilterField6 FilterValue6 FilterField7 FilterValue7 FilterField8 FilterValue8
	*FilterField9 FilterValue9 FilterField10 FilterValue10 FilterField11 FilterValue11 FilterField12 FilterValue12
	*FilterField13 FilterValue13 FilterField14 FilterValue14 FilterField15 FilterValue15 FilterField16 FilterValue16
	*BizCheckPack SubscribeIndex NotifyStatus ErrorNo ErrorInfo 
	*@param uiTimeout ���ĵĳ�ʱʱ��,��λ����
	*@return �ɹ��ͷ���0������ֵ��ʾʧ�ܣ�ͨ������Ż�ȡ������Ϣ������ÿ�����ĵ�ʧ��ԭ����Բ鿴lpSubAnsPacker���ݡ�
	//////////////////////////////////////////////////////////////////////////////
	*����ʵ����
	*IF2Packer* lpSubReqPack =NewPacker(2);
	*lpSubReqPack->AddRef();
	*��Ӷ�����Ҫ���ĵĲ��������ղ���˵����ӡ�
	*IF2Packer* lpSubAnsPack =NewPacker(2);
	*lpSubAnsPack->AddRef();
	*lpSubAnsPack->BeginPack();
	*BatchSubscribeTopic(lpSubReqPack->Unpack(),lpSubAnsPack,10000);
	*lpSubAnsPack->EndPack();
	*IF2UnPacker* lpAnsUnPack=lpSubAnsPack->Unpack();
	*���ݷ��ز�����ȡ��Ӧ�Ķ���Ӧ��
	*lpSubReqPack->FreeMem(lpSubReqPack->GetPackBuf());
	*lpSubReqPack->Release();
	*lpSubAnsPack->FreeMem(lpSubAnsPack->GetPackBuf());
	*lpSubAnsPack->Release();
	//////////////////////////////////////////////////////////////////////////////
	*/
	virtual int FUNCTION_CALL_MODE BatchSubscribeTopic(IF2UnPacker* lpSubReqUnpack,IF2Packer* lpSubAnsPacker,unsigned int uiTimeout) = 0;

	/**
    * ��ȡ���ĻỰ״̬
    * @return 0		 ����Ϣ�������ӶϿ� 
			  1		 ��������Ϣ���Ľ������� 
			  2		 ����Ϣ���������ѽ��� 
    */
    virtual int FUNCTION_CALL_MODE GetSessionStatus() = 0;
};

/**
 * �����ӿ�
 */
class CPublishInterface: public IKnown
{
public:

   /**
    * ҵ������ʽ�����ݷ����ӿ�
    * @param topicName �������֣���֪�����־ʹ�NULL
    * @param lpUnPacker ���������
    * @param iTimeOut ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ����������ɹ�û�з��أ������������Ҫ�������Release�ͷ�
                            �������ҵ��У��Ĵ�����Ϣ��д�����£�
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                            ��������Ϣ��ȡ��֮��,�ͷ�
                            lpBizUnPack->Release();
    * @param bAddTimeStamp �Ƿ����ʱ�������ϵ������ܲ���
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName ,IF2UnPacker* lpUnPacker,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;
    
   /**
    * ��ҵ������ʽ�����ݷ����ӿڣ�һ������Ƹ�ʽ���ķ���
    * @param topicName �������֣���֪�����־ʹ�NULL
    * @param lpFilterInterface ������������Ҫ�ϲ��Լ�ָ��������Ĭ��û�й�������
    * @param lpData ���������
    * @param nLength ���ݳ���
    * @param iTimeOut ��ʱʱ��
    * @param lppBizUnPack ҵ��У��ʱ��ʧ�ܷ��ص�ҵ�������Ϣ����������ɹ�û�з��أ������������Ҫ�������Release�ͷ�
                            �������ҵ��У��Ĵ�����Ϣ��д�����£�
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            �����ݷ���ֵ�������ʧ�ܵľ��ж� lpBizUnPack �ǲ���NULL.
                            ��������Ϣ��ȡ��֮��,�ͷ�
                            lpBizUnPack->Release();
    * @param bAddTimeStamp �Ƿ����ʱ�������ϵ������ܲ���
    * @return ����0��ʾ�ɹ�����������ֵ�����ݴ���Ż�ȡ������Ϣ.
    */
    virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, CFilterInterface* lpFilterInterface, const void *lpData, int nLength,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;

   /**
    * ���ص�ǰ����ķ������
    * @param topicName ��������
    * @return ����0��ʾû�ж�Ӧ�����⣬��������ֵ��ʾ�ɹ�
    */
    virtual uint32 FUNCTION_CALL_MODE GetMsgNoByTopicName(char* topicName)=0;

   /**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};
/**
 * �ļ����»ص��ӿ�
 */
class CFileUpdateCallbackInterface: public IKnown
{
public:

   /**
    * �յ������ļ��б�Ļص�
    * @param lpData ���ض�����ָ��
    * @param nLength ���������ݵĳ��ȣ����Ϊ������Ϊ������
	* @param lpErrorInfo �����ΪNULL��Ϊ������Ϣ����������Ӧ����ȥ��������Ϣ�����û����ȥ�ô�������Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnRecvFileList(const void *lpData, int nLength, const char * lpErrorInfo) = 0;

   /**
    * �յ�֪ͨ�ļ����½���
    * @param iOneFileProcessBar ��ǰ�ļ�����
    * @param iTotalProcessBar �ܽ���
	* @param lpErrorInfo �����ΪNULL��Ϊ������Ϣ����������Ӧ����ȥ��������Ϣ�����û����ȥ�ô�������Ϣ
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnShowProcessBar(int iOneFileProcessBar, int iTotalProcessBar, const char * lpErrorInfo) = 0;
	
	/**
    * �յ��ɹ�ȡ���ļ�����
    * @return ��
    */
    virtual void FUNCTION_CALL_MODE OnCancel() = 0;


};
/**
 * �ļ����½ӿ�
 */
class CFileUpdateInterface: public IKnown
{
public:

   /**
    * ����ǰ��ص���ʾ���ļ��б����û�ѡ����·���Ҫ���µ��ļ��б�
    * @param lpPack �����ļ��б�ָ��
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��.
    */
    virtual int FUNCTION_CALL_MODE UpdateFile(IF2Packer* lpPack) = 0;

   /**
    * ����ȡ�����ڸ����еĸ��¶���
    * @return ����0��ʾ�ɹ�������ֵ��ʾʧ��
    */
    virtual int FUNCTION_CALL_MODE CancelUpdateFile() = 0;

   /**
    * ��ȡ�����ļ��б�
    * @return �ļ��б��������������ⲿ������ֻ�ܶ��������ͷ�
	* @note �����������ֶμ����ļ�define�ֶ�,ע�⣺��OnRecvFileList�ص��Ժ�÷�����Ч
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetFileUpdateList() = 0;
};
class CConnectionInterface;

///���Ӷ��� CConnectionInterface ��Ҫ�Ļص�����ӿڶ���
/**
* �������ӳɹ������ӶϿ���������ɡ��յ����ݵ��¼�    
*/
class CCallbackInterface: public IKnown
{
public:
    /**
    * �׽������ӳɹ�
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * ��ɰ�ȫ����
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * ���ע��
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

    /**
    * ���ӱ��Ͽ�
    * @param lpConnection �������¼������Ӷ���
    */
    virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

    /**
    * �������
    * @param lpConnection �������¼������Ӷ���
    * @param hSend        ���;��
    * @param reserved1    �����ֶ�
    * @param reserved2    �����ֶ�
    * @param nQueuingData ���Ͷ�����ʣ�������ʹ���߿����ô���ֵ���Ʒ��͵��ٶȣ���С��ĳֵʱ���з���
    * @see Send()
    */
    virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData) = 0;

    virtual void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d) = 0;

    virtual void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d) = 0;

    virtual int  FUNCTION_CALL_MODE Reserved3() = 0;

    virtual void FUNCTION_CALL_MODE Reserved4() = 0;

    virtual void FUNCTION_CALL_MODE Reserved5() = 0;

    virtual void FUNCTION_CALL_MODE Reserved6() = 0;

    virtual void FUNCTION_CALL_MODE Reserved7() = 0;

    /**
    * �յ�SendBiz�첽���͵������Ӧ��
    * @param lpConnection    �������¼������Ӷ���
    * @param hSend           ���;��
    * @param lpUnPackerOrStr ָ������ָ����ߴ�����Ϣ
    * @param nResult         �հ����
    * ���nResult����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���lpUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�lpUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����2����ʾ�յ���ҵ�������Ϣ��lpUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    * ���nResult����3����ʾҵ������ʧ�ܡ�lpUnPackerOrStrָ��NULL��
    * ���nResult����4����ʾҵ���Ϊ�ա�lpUnpackerOrStrָ��NULL��lpRetData�ⲿ�ֽ���������
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult) = 0;

		/**
    * �յ�SendBiz�첽���͵������Ӧ��
    * @param lpConnection    �������¼������Ӷ���
    * @param hSend           ���;��
    * @param lpRetData ������Ҫ���ص�Ӧ�����ݣ�������Ҫ��ȡ
    * @param lpUnPackerOrStr ָ������ָ����ߴ�����Ϣ
    * @param nResult         �հ����
    * ���nResult����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�lpUnpackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    * ���nResult����2����ʾ�յ���ҵ�������Ϣ��lpUnpackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    * ���nResult����3����ʾҵ������ʧ�ܡ�lpUnpackerOrStrָ��NULL��
    * ���nResult����4����ʾҵ���Ϊ�ա�lpUnpackerOrStrָ��NULL��lpRetData�ⲿ�ֽ���������
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult) = 0;
	//20130624 xuxp �ص�����BizMessage�ӿ�
		/**
		* �յ�����ʱָ����ReplyCallbackѡ��������Ӧ�������û�ж�Ӧ���������
		* @param lpConnection �������¼������Ӷ���
		* @param hSend        ���;��
		* @param lpMsg        ҵ����Ϣָ��
		*/
	virtual void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg) = 0;

	//20150709 majc ���ӻص��������
	~CCallbackInterface(){}

};

///T2_SDK���Ӷ���ӿ�
/**
* ���ӵĶ������̲߳���ȫ��ͬʱһ����������ǹ���һ���߳����ã���Ҫ���߳�ʹ�ã�����
* �������ӡ��Ͽ������͡����յ�
*/
class CConnectionInterface: public IKnown
{
public:
    ///����״̬�������
    enum ConnectionStatus
    {
        Disconnected	= 0x0000, /**< δ���� */
        Connecting		= 0x0001, /**< socket�������� */
        Connected		= 0x0002, /**< socket������ */
        SafeConnecting	= 0x0004, /**< ���ڽ�����ȫ���� */
        SafeConnected	= 0x0008, /**< �ѽ�����ȫ���� */
        Registering		= 0x0010, /**< ��ע�� */
        Registered		= 0x0020, /**< ��ע�� */
        Rejected		= 0x0040  /**< ���ܾ��������ر� */
    };

    ///����ѡ�����ϣ�0��ʾ���ճ�ʱʱ����ɾ����ID���Կ��ٴε���RecvBiz���������Խ��գ�
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< �����ճ�ʱʱ����packet_idɾ�� */
    };

    /**
    * ��ʼ�����Ӷ���
    * @param lpCallback �ص�����
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
    */
    virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;

    /**
    * ��ʼ����/ע��
    * @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���ʹ�ô������ӷ�����ʱ���ò����������ã�
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;

    /**
    * �Ͽ�����
    * @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE Close() = 0;

    virtual int FUNCTION_CALL_MODE Reserved1() = 0;

    virtual int FUNCTION_CALL_MODE Reserved2() = 0;

    virtual int FUNCTION_CALL_MODE Reserved3() = 0;

    virtual int FUNCTION_CALL_MODE Reserved4() = 0;

    virtual int FUNCTION_CALL_MODE Reserved5() = 0;

    virtual int FUNCTION_CALL_MODE Reserved6() = 0;

    /**
    * ȡ��������ַ
    * @param lpPort ����ķ������˿ڣ�����ΪNULL
    * @return ���ط�������ַ
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

    /**
    * ȡ����״̬
    * @return ��������״̬
    */
    virtual int FUNCTION_CALL_MODE GetStatus() = 0;

    /**
    * ȡ���������أ�ʹ���߿���ͬʱ�����������ʵ��ͬʱ���Ӳ�ͬ�ķ�����������������ӵ�ʱ���Լ����ؾ���ʹ���ĸ�������
    * @return ���ط��������أ��Ǹ�������Խ���ʾԽ��æ�������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

    /**
    * ȡ�������Ӧ�Ĵ�����Ϣ��Ŀǰ֧�ּ������ĺ�Ӣ�ģ�֧���������Կ���ͨ�����Ӷ�������errormsg
    * @param nErrorCode ������
    * @return ���ش�����Ϣ
    */
    virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * ȡ���Ӵ���ţ��������޷����������ע��ʱ���ȿ�ͨ��Connect�ķ���ֵ��ȡ����ţ�
    * Ҳ��ͨ�����ñ���������ȡ����ţ�Ȼ���øô���ŵ���GetErrorMsg�ɻ�ȡ�ɶ��Ĵ�����Ϣ
    * @return �������Ӵ����
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
    * @param nAsy        0��ʾͬ���������ʾ�첽
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBiz�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBiz��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * ����ҵ������
    * @param hSend            ���;����SendBiz�ĳɹ�����ֵ��
    * @param lppUnPackerOrStr �������ֵ����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����2����ʾ�յ���ҵ�������Ϣ��*lppUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    *                         �������ֵ����3����ʾҵ������ʧ�ܡ�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
    * @param uiTimeout        ��ʱʱ�䣬��λ���롣
    * @param uiFlag           ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������RecvBiz�����գ�
    *                         JustRemoveHandle��ʾ�����ճ�ʱ�󣬰�hSend�������ɾ��
    * @return С��0��ʾRecvBiz��������ʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ע�⣡�ⲿָ����ָ��Ľ�������ڴ���SDK�ڲ������ⲿ�����ͷţ�
	* ע�⣡lppUnPackerOrStr��Ӧ�Ľ��������ʱ�ģ��ϲ㲻���Ի���ָ�룬�ٴε���������ӵ�RecvBiz��ָ��ָ������ݾͻ�ı�
	* ���Ҫ��������Ҫ���ý������GetPackBuf�����������ƿ�����ȥ�������߳���Ҫ�ٽ��
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
    
   //20101228 xuxp �������ͺͽ��ܵ������ӿں��������ڶ��ĺ�����
	/**
    * ����ҵ������
    * @param iFunID      ���ܺ�
    * @param lpPacker    �����ָ��
	* @param svrName     ָ���м���Ľڵ�
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * @param iSystemNo   ���iSystemNo > 0������ϵͳ��
    * @param nCompressID ��ҵ��������ѹ����ѹ���㷨ID��Ŀǰֻ֧��ID = 1��ѹ���㷨��
    * ID = 0��ʾ��ѹ����ע�⣬ѹ��ֻ����SDK������飬�Ƿ�����ѹ����ȡ���ڰ���ʵ�ʴ�С��
    * ͬ�����͵İ���ͨ������RecvBizEx�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBizEx��
    * @param branchNo  Ӫҵ���š�
    * @param lpRequest  ����������������ݣ����ݽṹ�嶨�帳ֵ��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
    virtual int FUNCTION_CALL_MODE SendBizEx(int iFunID, IF2Packer *lpPacker,char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1,int branchNo=0,LPREQ_DATA lpRequest=NULL) = 0;
    
    /**
    * ����ҵ������
    * @param hSend            ���;����SendBiz�ĳɹ�����ֵ��
    * @param lppUnPackerOrStr �������ֵ����0����ʾҵ�����ݽ��ճɹ�������ҵ������ɹ���*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����1����ʾҵ�����ݽ��ճɹ�����ҵ�����ʧ���ˣ�*lppUnPackerOrStrָ��һ�����������ʱӦ���Ƚ���ָ��ת��ΪIF2UnPacker *��
    *                         �������ֵ����2����ʾ�յ���ҵ�������Ϣ��*lppUnPackerOrStrָ��һ���ɶ����ַ���������Ϣ��
    *                         �������ֵ����3����ʾҵ������ʧ�ܡ�*lppUnPackerOrStrԭ����ָ������ݲ��ᱻ�ı䡣
    * @param lpRetData ������Ҫ���ص�Ӧ�����ݣ�������Ҫ��ȡ
    * @param uiTimeout        ��ʱʱ�䣬��λ���룬0��ʾ���ȴ���
    * @param uiFlag           ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������RecvBiz�����գ�
    *                         JustRemoveHandle��ʾ�����ճ�ʱ�󣬰�hSend�������ɾ��
    * @return С��0��ʾRecvBizEx��������ʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ע�⣡�ⲿָ����ָ��Ľ�������ڴ���SDK�ڲ������ⲿ�����ͷţ�
	* ע�⣡�ⲿָ����ָ���LPRET_DATA���ڴ���SDK�ڲ������ⲿ�����ͷţ�
	* ע�⣡lppUnPackerOrStr��Ӧ�Ľ������LPRET_DATA������ʱ�ģ��ϲ㲻���Ի���ָ�룬�ٴε���������ӵ�RecvBizEx��������ָ��ָ������ݾͻ�ı�
	* ���Ҫ��������Ҫ���ý������GetPackBuf�����������ƿ�����ȥ�������߳���Ҫ�ٽ����
	* LPRET_DATA����������Ҫ���ṹ�帴��
    */
    virtual int FUNCTION_CALL_MODE RecvBizEx(int hSend, void **lppUnpackerOrStr, LPRET_DATA* lpRetData, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;


	//20101228 xuxp ����Create����������֤�ص����µ�OnReceivedBizEx�Ľӿ�
	/**
	* ��ʼ�����Ӷ���
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE CreateEx(CCallbackInterface *lpCallback) = 0;
	
	
	//20120111 dongpf ����GetRealAddress����������ȡ��������Լ���ip��ַ�Ͷ˿�
	/**
	* ��ȡip��ַ�Ͷ˿�
	* @return ��ȡip��ַ�Ͷ˿ڣ���ʽ��ip��ַ+�˿�
	*/
	virtual const char* FUNCTION_CALL_MODE GetRealAddress() = 0;
	
	
	virtual int FUNCTION_CALL_MODE Reserved8() = 0;
	virtual int FUNCTION_CALL_MODE Reserved9() = 0;
	
	//20130527 xuxp ����GetSelfAddress����������ȡ�Լ����ص�IP�Ͷ˿�
	/**
	* ��ȡip��ַ�Ͷ˿�
	* @return ��ȡip��ַ�Ͷ˿ڣ���ʽ��ip��ַ+�˿�
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfAddress() = 0;

	//20130529 xuxp ����GetSelfMac����������ȡ�Լ�����ʹ�õ�����MAC
	/**
	* ��ȡMAC��ַ
	* @return MAC�ĵ�ַ�ַ�����ʽ�����ơ�D067E5556D83��,�м�û�зָ��
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfMac() = 0;
	
	//20130609 xuxp �������ķ����ӿ�
	///////////////////////////////////�������Ӷ��ķ����Ľӿ�///////////////////////////////////////

	/**
    * ����һ��������
    * @param lpCallback �ص��ӿ�
    * @param SubScribeName ���������֣��ඩ���ߵ����ֱ��벻һ������������ͬ.��󳤶�32���ֽ�
    * @param iTimeOut ��ʱʱ��
    * @param iInitRecvQLen ��ʼ�����ն��еĳ���
    * @param iStepRecvQLen ���ܶ��е���չ����
    * @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص�.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
    
   /**
    * ��ȡ������
    * @param PublishName ������ҵ����
    * @param msgCount ���ػ�����Ϣ�ĸ���
	  * @param iTimeOut ��ʼ����ʱ��ĳ�ʱʱ��
    * @param bResetNo �Ƿ�������
    * @return ���ط��ͽӿ�ʵ�������ض�Ӧ��ָ��
    */
    //virtual CPublishInterface* FUNCTION_CALL_MODE GetPublisher(int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    virtual CPublishInterface* FUNCTION_CALL_MODE NewPublisher(char* PublishName,int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    
  


   /**
    * ��ȡ����˵�����������Ϣ
    * @param byForce �Ƿ�ǿ�ƴӺ�̨��ȡ
    * @param iTimeOut ��ʱʱ��
    * @return �ɹ��ͷ�������������Ϣ
    * @note �����������Ҫ����release�ӿڽ����ͷ�.
    * @note packer�����ֶ�
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
	* - FilterField7 
	* - FilterField8 
	* - FilterField9 
	* - FilterField10 
	* - FilterField11 
	* - FilterField12
	* - FilterField13 
	* - FilterField14 
	* - FilterField15 
	* - FilterField16
    * - SubscribeStr 
    * - PublishStr
	
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;
	
	/**
	* ��ȡ���ķ�����������
	*/
	virtual const char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20130624 xuxp ���ӽӿ��������������ӿڣ�������Ϊ����˵Ľӿڣ��ͻ��˿���Ҳ�Ƽ�ʹ��
	///////////////////////////////////�µ�һ�ײ����ӿ�///////////////////////////////////////
	/**
	* ��ʼ�����Ӷ���
	* @param lpCallback �ص�����
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    * ���Ӧ�ò���Ҫ�κλص������������÷�������NULL���������Զ���ص���Ͷ���
	*/
	virtual int FUNCTION_CALL_MODE Create2BizMsg(CCallbackInterface *lpCallback) = 0;

	/**
    * ����ҵ������
    * @param lpMsg       ҵ����Ϣ�ӿ�ָ��
    * @param nAsy        0��ʾͬ���������ʾ�첽��
    * ͬ�����͵İ���ͨ������RecvBizMsg�����գ��첽���͵İ������յ�Ӧ������Զ������ص�����OnReceivedBizMsg��
    * @return ���ط��;�����������������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
    */
	virtual int FUNCTION_CALL_MODE SendBizMsg(IBizMessage* lpMsg,int nAsy = 0) = 0;
	
	/**
	* ��������
	* @param hSend     ���;��
	* @param lpMsg	   �յ�ҵ����Ϣָ��ĵ�ַ
	* @param uiTimeout ��ʱʱ�䣬��λ���룬0��ʾ���ȴ�
	* @param uiFlag    ����ѡ�0��ʾ���ճ�ʱ���Կɼ�������Receive�����գ�
    *                  JustRemoveHandle��ʾ�����ճ�ʱʱ����packet_idɾ�����Ժ����յ���������첽�ķ�ʽ�յ���
	* @return ����0��ʾ�ɹ��������ʾʧ�ܣ�ͨ������GetErrorMsg���Ի�ȡ��ϸ������Ϣ
	* ע�⣡�ⲿָ����ָ���IBizMessage���ڴ���SDK�ڲ������ⲿ�����ͷţ�
	* ע�⣡lpMsg��Ӧ����Ϣָ������ʱ�ģ��ϲ㲻���Ի���ָ�룬�ٴε���������ӵ�RecvBizMsg�����ָ��ָ������ݾͻ�ı�
	* ���Ҫ��������Ҫ����IBizMessage��GetBuff�����������ƿ�����ȥ�������߳���Ҫ�ٵ���SetBuff��
	*/
	virtual int FUNCTION_CALL_MODE RecvBizMsg(int hSend, IBizMessage** lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
	
	//20141117 majc �����ļ�����Ŀ¼�����ֶ�
	/**
    * ��ȡ�ļ�����,һ����������ֻ��һ���ļ����£�������ھͷ���֮ǰ�Ľӿ�
    * @param szTopicName �ļ��������⣬�����ڷ������Ϣ�����ļ��������� 
	* @param lpCallBack �ص��ӿ�
	* @param szScanDir ɨ���ļ���Ŀ¼
    * @param szUpdateDir �ļ����´�Ÿ�Ŀ¼
	* @param iTimeOut ��ʱʱ��
	* @param szDirFilter Ŀ¼��������������ж��Ŀ¼��;�Ÿ�
    * @return �����ļ����½ӿ�ָ��
    */
	virtual CFileUpdateInterface* FUNCTION_CALL_MODE NewFileUpdate(const char* szTopicName,CFileUpdateCallbackInterface* lpCallBack ,const char* szScanDir,const char* szUpdateDir,unsigned int uiTimeOut = 5000, const char * szDirFilter = NULL) = 0;

	/**
	* ��ȡ�ļ����µ�������
	*/
	virtual const char* FUNCTION_CALL_MODE GetFileUpdateLastError() = 0;
	
	//20140618 majc ���ӻ�ȡ���һ��Ӧ��������ϸ��Ϣ�ӿ�
	/**
	* ȡ���ش�����Ϣ����ϸ��Ϣ
	* @param bAsyError 0��ʾͬ��(Ĭ��)�������ʾ�첽��
	* @return ������ϸ������Ϣ
	* @note ������Ϣ��ʽ��packType:xxx;funtionId:xxx;branchNo:zxx;systemNo:xxx;subSystemNO:xxx;packId:xxx;routerInfo:xxx,xxx,xxx,xxx,xxx,xxx;sendPath:xxx,xxx,xxx,xxx,xxx,xxx;returnCode:xxx;errorNo:xxx;errorInfo:xxx
	* packType-������
	* funtionId-���ܺ�
	* branchNo-��֧��
	* systemNo-ϵͳ��
	* subSystemNO-��ϵͳ��
	* packId-�����
	* routerInfo-Ŀ��·��
	* sendPath-������·��
	* returnCode-���ش�����
	* errorNo-�����
	* errorInfo-������Ϣ
	* ����˵����1��ͬ������ʱ������Receive���ص�lppData����ESBMessage��RetuenCode��Ϊ0ʱ���ã�����RecvBiz��RecvBizEx���ڷ���ֵΪ1��2��3��4ʱ���ã�����RecvBizMsg����GetReturnCode()��Ϊ0ʱ����
	*           2���첽����ʱ���ص�OnReceived��lpData����ESBMessage��RetuenCode��Ϊ0ʱ���ã��ص�OnReceivedBiz��OnReceivedBizEx��nResultΪ1��2��3��4ʱ���ã��ص�OnReceivedBizMsg��lpMsg��GetReturnCode()��Ϊ0ʱ����
	*/
	virtual const char * FUNCTION_CALL_MODE GetLastAnsError(bool bAsyError = 0) = 0;

	////////////////////////////////////////////////////////////////////////////////
	//20150209 majc �������Ľӿ�
	/**
    * ����һ��������
    * @param lpCallback �ص��ӿ�
    * @param SubScribeName ���������֣��ඩ���ߵ����ֱ��벻һ������������ͬ.��󳤶�32���ֽ�
	* @param subRoterInfo  ����ʱָ��·��
    * @param iTimeOut ��ʱʱ��
    * @param iInitRecvQLen ��ʼ�����ն��еĳ���
    * @param iStepRecvQLen ���ܶ��е���չ����
    * @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص�.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriberEx(CSubCallbackInterface *lpCallback,char* SubScribeName,SUB_ROUTER_INFO &subRoterInfo,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
	//20150514 majc ��������user_token����
	virtual void FUNCTION_CALL_MODE SetUserToken(const char* szUserToken) = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20150610 xuxp ������Ⱥ�����ߴ����Ľӿ�
	/**
    * ����һ����Ⱥ������
    * @param lpCallback �ص��ӿ�
    * @param SubScribeName ���������֣��ඩ���ߵ����ֱ��벻һ������������ͬ.��󳤶�32���ֽ�
    * @param iTimeOut ��ʱʱ��
    * @param iInitRecvQLen ��ʼ�����ն��еĳ���
    * @param iStepRecvQLen ���ܶ��е���չ����
    * @return ���ض��Ľӿ�ʵ����һ���Ự�ӿڶ�Ӧһ���ص�.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewClusterSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,SUB_ROUTER_INFO &subRoterInfo,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;

    ///20150812 liuzl ���������ӵķ������Ľڵ���,��ar#0,֧��F5
	///20160614 zhouwh �޸Ľӿڶ��壬����FUNCTION_CALL_MODE
    //virtual const char *GetServerNodeName() = 0;
	virtual const char * FUNCTION_CALL_MODE GetServerNodeName() = 0;

	//20160614 zhouwh ��������ͬ��ģʽ�Ķ��л���
	// note: ��������ģʽ�£��ýӿڱ�����ã���������ڴ�й¶
	/**
		@param lpData ͬ��receiveʱ���ص�����ָ��
	*/
	virtual void FUNCTION_CALL_MODE RecycleDataBuf(void *lpData) = 0;

	//20161028 majc  ���ӽӿ�����Ψһ���ǰ׺
	/**
	* @param lpPrefix Ψһ���ǰ׺�����֧��255�ֽ�
	*/
	virtual void FUNCTION_CALL_MODE SetUniquePrefix(const char* lpPrefix) = 0;

	//20161223 huxb  ���������Ͽ����ӽӿ�
	/**
	* @param bSafe �Ƿ�Ϊ��ȫֹͣ��Ĭ��Ϊ�ǰ�ȫֹͣ
	* @param uiTimeout ��ȫֹͣ��ʱʱ�䣬��λΪms
	*/
	virtual int FUNCTION_CALL_MODE ActiveClose(bool bSafe = false, unsigned int uiTimeout = 5000) = 0;

	//20161223 huxb  �����������÷�������ַ�ӿ�
	//ע�����뵥�̵߳���
	/**
	* @param szServers �µķ�������ַ
	*/
	virtual int FUNCTION_CALL_MODE SetServers(const char * szServers) = 0;
};

extern "C"
{
    /**
	* ��ȡT2_SDK�İ汾��
	* @return ��ǰT2_SDK�İ汾��
	* Ʃ�磺�汾Ϊ0x10000002��ʾ1.0.0.2
	*/
    int FUNCTION_CALL_MODE GetVersionInfo();

    /**
	* ��ȡһ��ʵ��CConfigInterface�ӿڵ����ָ��
	* @return ʵ��CConfigInterface�ӿڵ����ָ��
	*/
CConfigInterface* FUNCTION_CALL_MODE NewConfig();

    /**
	* ��ȡһ��ʵ��CConnectionInterface�ӿڵ����ָ��
	* @param CConfigInterface ʵ��CConfigInterface�ӿڵ����ָ��
	* @returnʵ��CConnectionInterface�ӿڵ����ָ��
	*/
CConnectionInterface* FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

/**
* @param int iVersion ҵ�����ʽ�汾(ȡֵ:1 �ִ���,����ֵ 0x20��)
* �Ƽ�ʹ��0x20��
* @return IPacker * ������ӿ�ָ��
*/
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

/**
* @param void * lpBuffer Ҫ��������ݣ�����ARͨ�Ű�ͷ��
* @param unsigned int iLen ���ݳ���
* @return IUnPacker * �汾2����������ӿ�ָ��
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);

/**
* @param void * lpBuffer Ҫ��������ݣ�����ARͨ�Ű�ͷ��
* @param unsigned int iLen ���ݳ���
* @return IUnPacker * �汾1����������ӿ�ָ��
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPackerV1(void * lpBuffer, unsigned int iLen);

/**
* @param void * lpBuffer Ҫ��������ݣ�����ARͨ�Ű�ͷ��
* @return 1��ʾ�汾1�Ľ�������ݣ�0x21~0x2F �汾2�Ľ��������
*/
int FUNCTION_CALL_MODE GetPackVersion(const void *lpBuffer);
/**
* @param char *EncodePass ������ɢ�н�����ַ��������Ȳ�����16������'\0'��
* @param const char* Password ����Ĵ�ɢ�е�����
* @param int nReserve �������������Ĭ��ֵ
* @return char * ������ɢ�н����ַ��ͬEncodePass
*/
char * FUNCTION_CALL_MODE Encode(char *EncodePass, const char* Password, int nReserve = 0 );


/**
*����һ���ṩ�ļ��ܺ�������������м���
* @param const char* pIn ����Ĵ����ܵ��ַ���
* @param const char* pOut ������������Ⱥʹ�����ַ�����Сһ�������ⲿ����
* @return 
*/
int FUNCTION_CALL_MODE EncodeEx(const char *pIn, char *pOut);


/**
* ����һ���������ӿ�ָ��
* @return ����NULL��ʾʧ��.
*/
CFilterInterface* FUNCTION_CALL_MODE NewFilter();
    
/**
* ����һ���������Խӿ�ָ��
* @return ����NULL��ʾʧ��.
*/
CSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam();

//20130625 xuxp ����ҵ����Ϣ
IBizMessage* FUNCTION_CALL_MODE NewBizMessage();

//20160317 zhouwh ����ҵ����Ϣ�����ѹ����־
IBizMessage* FUNCTION_CALL_MODE NewBizMessageEx(int nCompressID = 1);

//20161027 majc �������ٶ˿�
/**
*lpRequest�������ֶΣ�address port
*lpResult�� �����ֶΣ��ɹ���conn_count net_delay net_speed  last_error ʧ�ܣ�error_no error_info
*uiTimeOut����ʱʱ��
* ����ֵ��0 �ɹ�����0ʧ��
*/
int FUNCTION_CALL_MODE GetMultiNetWorkSpeed(IF2UnPacker * lpRequest, IF2Packer * lpResult, unsigned int uiTimeOut);
}

#endif
