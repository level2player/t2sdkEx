#include <Include/t2sdk_interface.h>


//typedef int (*callback)(int,int);
typedef int (*OnGoReceivedBiz)(CConnectionInterface*, int, const void*, int );



class CCallback : public CCallbackInterface
{
public:

    // ��ΪCCallbackInterface�����մ��������IKnown��������Ҫʵ��һ����3������
    unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv);
    unsigned long  FUNCTION_CALL_MODE AddRef();
    unsigned long  FUNCTION_CALL_MODE Release();
    void* onGoReceivedBiz;
    // �����¼�����ʱ�Ļص�������ʵ��ʹ��ʱ���Ը�����Ҫ��ѡ��ʵ�֣����ڲ���Ҫ���¼��ص���������ֱ��return
    // Reserved?Ϊ�������Ϊ�Ժ���չ��׼����ʵ��ʱ��ֱ��return��return 0��
    void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection);
    void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData);
    void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d);
    void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d);
    int  FUNCTION_CALL_MODE Reserved3();
    void FUNCTION_CALL_MODE Reserved4();
    void FUNCTION_CALL_MODE Reserved5();
    void FUNCTION_CALL_MODE Reserved6();
    void FUNCTION_CALL_MODE Reserved7();
    void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult);
	void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult);
    void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg);

};

unsigned long CCallback::QueryInterface(const char *iid, IKnown **ppv)
{
    return 0;
}

unsigned long CCallback::AddRef()
{
    return 0;
}

unsigned long CCallback::Release()
{
    return 0;
}

// ���¸��ص�������ʵ�ֽ���Ϊ��ʾʹ��
void CCallback::OnConnect(CConnectionInterface *lpConnection)
{
    puts("CCallback::OnConnect");
}

void CCallback::OnSafeConnect(CConnectionInterface *lpConnection)
{
    puts("CCallback::OnSafeConnect");
}

void CCallback::OnRegister(CConnectionInterface *lpConnection)
{
    puts("CCallback::OnRegister");
}

void CCallback::OnClose(CConnectionInterface *lpConnection)
{
    puts("CCallback::OnClose");
}

void CCallback::OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData)
{
    puts("CCallback::OnSent");
}

void CCallback::Reserved1(void *a, void *b, void *c, void *d)
{
}

void CCallback::Reserved2(void *a, void *b, void *c, void *d)
{
}

void CCallback::OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult)
{
	puts("CCallback::OnReceivedBizEx");
}

void CCallback::OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult)
{
    puts("CCallback::OnReceivedBiz");

    //printf("OnReceivedBiz,hSend:%d \r\n,",hSend);

    if(NULL!=onGoReceivedBiz)
    {
        ((OnGoReceivedBiz)onGoReceivedBiz)(lpConnection,hSend,lpUnPackerOrStr,nResult);
    }
   //printf("OnReceivedBiz,hSend:%d \r\n,",hSend);
}

int  CCallback::Reserved3()
{
    return 0;
}

void CCallback::Reserved4()
{
}

void CCallback::Reserved5()
{
}

void CCallback::Reserved6()
{
}

void CCallback::Reserved7()
{
}
void CCallback::OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg)
{
	puts("CCallback::OnReceivedBizMsg");
}


//Release接口
extern "C"
{
   long Release(IKnown* Known){
      return Known->Release();
   }
}

//配置接口
extern "C"
{
    CConfigInterface*  GetNewConfig(){
        return NewConfig();
   }
    int LoadT2Config(CConfigInterface* config,const char *szFileName){
      return config->Load(szFileName);
   }
}

//连接接口
extern "C"{
    static CCallback cCallback;

    CConnectionInterface* GetNewConnection(CConfigInterface* config){
       return NewConnection(config);
    }
    
   int RegisteredCallBack(void* onGocallback){
       if(NULL!=onGocallback)
       {
           cCallback.onGoReceivedBiz=onGocallback;
           return 1;
       }
       return 0;
   }
 

   int CreateConnection(CConnectionInterface* conn){
      if(NULL==(cCallback.onGoReceivedBiz)){
        return conn->Create(NULL);
      }else{
            return conn->Create(&cCallback);
      }
     //return conn->Create(NULL);
   }

    int T2Connect(CConnectionInterface* conn, int timeOut){
       int r_code=conn->Connect(timeOut);
       //printf("r_code:%d \r\n",r_code);
       return r_code;
   }

     void GetErrorMsg(CConnectionInterface* conn, int retCode,char *errorMsg){
        const char * tmp_error=conn->GetErrorMsg(retCode);
        strcpy(errorMsg,tmp_error);
    }

    int SyncSendBiz(CConnectionInterface* conn,int functionNo,IF2Packer* packer){
      return conn->SendBiz(functionNo,packer);
    }

    int SyncRecvBiz(CConnectionInterface* conn,int retCode,void** pointer){
      return conn->RecvBiz(retCode,pointer);
    }

    int AsynSendBiz(CConnectionInterface* conn,int functionNo,IF2Packer* packer){
      return conn->SendBiz(functionNo,packer,1);
    }
 
}

//打包器
extern "C"{
      IF2Packer* GetNewPacker(int version){
       return NewPacker(version);
   }

     int AddPackerRef(IF2Packer* packer){
       return packer->AddRef();
   }

     void BeginPack(IF2Packer* packer){
       packer->BeginPack();
   }

    void EndPack(IF2Packer* packer){
        packer->EndPack();
   }

    int AddField(IF2Packer* packer,const char *szFieldName){
      return packer->AddField(szFieldName);
   }

    int AddStr(IF2Packer* packer,const char *szValue ){
        return packer->AddStr(szValue);
   }

    int AddInt(IF2Packer* packer,int szValue ){
        return packer->AddInt(szValue);
   }

     int AddDouble(IF2Packer* packer,double szValue ){
        return packer->AddDouble(szValue);
   }

    int AddChar(IF2Packer* packer,char szValue ){
        return packer->AddChar(szValue);
   }
    void FreeMem(IF2Packer* packer){
        packer->FreeMem(packer->GetPackBuf());
   }
}

//解包器
extern "C"{
  //获取解包器版本
     int GetVersion(void** pointer){
       return ((IF2UnPacker *)pointer)->GetVersion();
    }

     int Open(void** pointer,void * lpBuffer,unsigned int iLen){
        return ((IF2UnPacker *)pointer)->Open(lpBuffer,iLen);
    }

     int GetDatasetCount(void** pointer){
      return ((IF2UnPacker *)pointer)->GetDatasetCount();
    }

     int SetCurrentDatasetByIndex(void** pointer,int nIndex){
      return ((IF2UnPacker *)pointer)->SetCurrentDatasetByIndex(nIndex);
    }

     int GetRowCount(void** pointer){
      return ((IF2UnPacker *)pointer)->GetRowCount();
    }

    int GetColCount(void** pointer){
      return ((IF2UnPacker *)pointer)->GetColCount();
   }

    void GetColName(void** pointer,int column,char *colName){
    const char* tmp_colName=((IF2UnPacker *)pointer)->GetColName(column);
    strcpy(colName,tmp_colName);
   }

    char GetColType(void** pointer,int column){
       return ((IF2UnPacker *)pointer)->GetColType(column);
   }

    int GetIntByIndex(void** pointer,int column){
        return ((IF2UnPacker *)pointer)->GetIntByIndex(column);
   }

    char GetCharByIndex(void** pointer,int column){
       return ((IF2UnPacker *)pointer)->GetCharByIndex(column);
   }
    double GetDoubleByIndex(void** pointer,int column){
       return ((IF2UnPacker *)pointer)->GetDoubleByIndex(column);
   }

    void GetStrByIndex(void** pointer,int column,char *colValue){
       const char* tmp_colValue=((IF2UnPacker *)pointer)->GetStrByIndex(column);
       strcpy(colValue,tmp_colValue);
   }
    void Next(void** pointer){
        ((IF2UnPacker *)pointer)->Next();
   }
    void First(void** pointer){
        ((IF2UnPacker *)pointer)->First();
   }
    void Last(void** pointer){
        ((IF2UnPacker *)pointer)->Last();
   }
    void Go(void** pointer,int rowNo){
            ((IF2UnPacker *)pointer)->Go(rowNo);
   }


//    void some_c_func(void*  p)
//     {
//         //int arg = 2;
//         //printf("C.some_c_func(): calling callback with arg = %d\n", arg);
//         int response = ((callback)p)(2,3);
//         printf("C.some_c_func(): callback responded with %d\n", response);
//     }
}





