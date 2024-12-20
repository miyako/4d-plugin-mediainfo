/* --------------------------------------------------------------------------------
 #
 #  4DPlugin-MediaInfo.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : MediaInfo
 #	author : miyako
 #	2022/05/12
 #  
 # --------------------------------------------------------------------------------*/

#include "4DPlugin-MediaInfo.h"

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params) {
    
	try
	{
        switch(selector)
        {
			// --- MediaInfo
            
			case 1 :
				MediaInfo(params);
				break;
            case 2 :
                MediaInfoFile(params);
                break;

        }

	}
	catch(...)
	{

	}
}

#pragma mark -

static void MediaInfo(PA_PluginParameters params) {

    PackagePtr pParams = (PackagePtr)params->fParameters;
    sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
    
    C_BLOB Param1;
    C_LONGINT Param2;
    C_TEXT returnValue;
    
    Param1.fromParamAtIndex(pParams, 1);
    Param2.fromParamAtIndex(pParams, 2);

    PA_ulong64 dataSize = (PA_ulong64)Param1.getBytesLength();
    
    if(dataSize != 0){

        MediaInfoLib::MediaInfo MI;
        MediaInfoLib::Config.Complete_Set(true);
        
        MI.Open_Buffer_Init(dataSize, 0);
                
        const uint8_t *ptr = Param1.getBytesPtr();
        size_t seek = 0L;
        size_t pos = 0L;
        size_t size = STREAM_BUFFER_SIZE;
        time_t startTime = time(0);
        size_t status = 0L;
        
        do
        {
            time_t now = time(0);
            time_t elapsedTime = abs(startTime - now);
            
            if (elapsedTime > 0)
            {
                startTime = now;
                PA_YieldAbsolute();
            }
            
            pos += size;
            status = MI.Open_Buffer_Continue(ptr, size);
            
            if ((status & 0x01) == 0x01) //Accepted
            {
                        printf("Accepted\r");
            }
            
            if ((status & 0x02) == 0x02) //Filled
            {
                        printf("Filled\r");
            }
            
            if ((status & 0x04) == 0x04) //Updated
            {
                        printf("Updated\r");
            }
            
            if ((status & 0x08) == 0x08) //Finalized
            {
                        printf("Finalized\r");
                size = 0;
                break;
            }
            
            seek = MI.Open_Buffer_Continue_GoTo_Get();
            
            printf("seek:%d\r", seek);

            if (seek != (MediaInfo_int64u)-1)
            {
                MI.Open_Buffer_Init(size, seek);
                size_t _size = seek - pos;
                ptr = Param1.getBytesPtrForSize((uint32_t *)&_size);
            }else{
                ptr = Param1.getBytesPtrForSize((uint32_t *)&size);
            }
            
            if (ptr == NULL)
            {
                size = 0;
                break;
            }
            
        }
        while (size > 0);
    
        MI.Open_Buffer_Finalize();

        switch (Param2.getIntValue()) {
            case MediaInfo_Inform_XML:
                MediaInfoLib::Config.Inform_Set(__T("XML"));
                break;
            case MediaInfo_Inform_OLDXML:
                MediaInfoLib::Config.Inform_Set(__T("OLDXML"));
                break;
            case MediaInfo_Inform_EBUCore:
                MediaInfoLib::Config.Inform_Set(__T("EBUCore"));
                break;
            case MediaInfo_Inform_PBCore:
                MediaInfoLib::Config.Inform_Set(__T("PBCore"));
                break;
            case MediaInfo_Inform_PBCore2:
                MediaInfoLib::Config.Inform_Set(__T("PBCore2"));
                break;
            case MediaInfo_Inform_HTML:
                MediaInfoLib::Config.Inform_Set(__T("HTML"));
                break;
            case MediaInfo_Inform_CSV:
                MediaInfoLib::Config.Inform_Set(__T("CSV"));
                break;
            case MediaInfo_Inform_JSON:
                MediaInfoLib::Config.Inform_Set(__T("JSON"));
                break;
            case MediaInfo_Inform_EBUCore_JSON:
                MediaInfoLib::Config.Inform_Set(__T("EBUCore_JSON"));
                break;
            default:
                MediaInfoLib::Config.Inform_Set(__T(""));
                break;
        }
        
        std::wstring inform = std::wstring((const wchar_t *)MI.Inform().c_str());
        
        MI.Close();
        
        uint32_t len;

#if VERSIONMAC
        PA_4DCharSet eVTC_WCHAR_T = eVTC_UTF_32;
#else
        PA_4DCharSet eVTC_WCHAR_T = eVTC_UTF_16;
#endif

        len = (uint32_t)(inform.size() * sizeof(wchar_t)) + sizeof(wchar_t);
        std::vector<char> buf(len);
        
        uint32_t ulen = PA_ConvertCharsetToCharset(
                            (char *)inform.c_str(),
                            inform.size() * sizeof(wchar_t),
                            eVTC_WCHAR_T,
                            (char *)&buf[0],
                            len,
                            eVTC_UTF_16
                            );

        returnValue.setUTF16String((const PA_Unichar *)&buf[0], ulen);
    }

    returnValue.setReturn(pResult);
}

static void MediaInfoFile(PA_PluginParameters params) {

    PackagePtr pParams = (PackagePtr)params->fParameters;
    sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
    
    C_TEXT Param1;
    C_LONGINT Param2;
    C_TEXT returnValue;
    
    Param1.fromParamAtIndex(pParams, 1);
    Param2.fromParamAtIndex(pParams, 2);
    
    if(Param1.getUTF16Length() != 0){
        
        FILE *f;
        unsigned char *buf[STREAM_BUFFER_SIZE];
        
#if VERSIONMAC
        CUTF8String u8;
        Param1.copyPath(&u8);
        const  char   *path = (const  char   *)u8.c_str();
#else
        const wchar_t *path = (const wchar_t *)Param1.getUTF16StringPtr();
#endif
        
        MediaInfoLib::MediaInfo MI;
        MediaInfoLib::Config.Complete_Set(true);

        f = CPathOpen (path, CPathRead);
        
        if (f)
        {
            CPathSeek(f, 0L, SEEK_END);
            PA_ulong64 size = (PA_ulong64)CPathTell(f);
            
            MI.Open_Buffer_Init(size, 0);
            
            ZenLib::int64u seek = 0L;
            size_t len = 0L;
            size_t pos = 0L;
            time_t startTime = time(0);
            size_t status = 0L;
            
            do
            {
                time_t now = time(0);
                time_t elapsedTime = abs(startTime - now);
                
                if (elapsedTime > 0)
                {
                    startTime = now;
                    PA_YieldAbsolute();
                }
                
                if(!CPathSeek(f, pos, SEEK_SET)){
                    len = fread(buf, 1, STREAM_BUFFER_SIZE, f);
                }else{
                    len = 0;
                }
                
                if(len > 0)
                {
                    status = MI.Open_Buffer_Continue((const ZenLib::int8u*)buf, len);

                    if ((status & 0x01) == 0x01) //Accepted
                    {
//                        printf("Accepted\r");
                    }
                    
                    if ((status & 0x02) == 0x02) //Filled
                    {
//                        printf("Filled\r");
                    }
                    
                    if ((status & 0x04) == 0x04) //Updated
                    {
//                        printf("Updated\r");
                    }
                    
                    if ((status & 0x08) == 0x08) //Finalized
                    {
//                        printf("Finalized\r");
                        len = 0;
                        break;
                    }
                    
                    seek = MI.Open_Buffer_Continue_GoTo_Get();
                    
                    if (seek != (MediaInfo_int64u)-1)
                    {
                        pos = seek;
                        MI.Open_Buffer_Init(size, seek);
                        continue;
                    }
                    
                    pos += len;
                }
                
            }
            while (len > 0);
            
            fclose(f);
        }
        
        MI.Open_Buffer_Finalize();
        
        switch (Param2.getIntValue()) {
            case MediaInfo_Inform_XML:
                MediaInfoLib::Config.Inform_Set(__T("XML"));
                break;
            case MediaInfo_Inform_OLDXML:
                MediaInfoLib::Config.Inform_Set(__T("OLDXML"));
                break;
            case MediaInfo_Inform_EBUCore:
                MediaInfoLib::Config.Inform_Set(__T("EBUCore"));
                break;
            case MediaInfo_Inform_PBCore:
                MediaInfoLib::Config.Inform_Set(__T("PBCore"));
                break;
            case MediaInfo_Inform_PBCore2:
                MediaInfoLib::Config.Inform_Set(__T("PBCore2"));
                break;
            case MediaInfo_Inform_HTML:
                MediaInfoLib::Config.Inform_Set(__T("HTML"));
                break;
            case MediaInfo_Inform_CSV:
                MediaInfoLib::Config.Inform_Set(__T("CSV"));
                break;
            case MediaInfo_Inform_JSON:
                MediaInfoLib::Config.Inform_Set(__T("JSON"));
                break;
            case MediaInfo_Inform_EBUCore_JSON:
                MediaInfoLib::Config.Inform_Set(__T("EBUCore_JSON"));
                break;
            default:
                MediaInfoLib::Config.Inform_Set(__T(""));
                break;
        }

        std::wstring inform = std::wstring((const wchar_t *)MI.Inform().c_str());
        
        MI.Close();
        
        uint32_t len;
#if VERSIONMAC
        PA_4DCharSet eVTC_WCHAR_T = eVTC_UTF_32;
#else
        PA_4DCharSet eVTC_WCHAR_T = eVTC_UTF_16;
#endif
        
        len = (uint32_t)(inform.size() * sizeof(wchar_t)) + sizeof(wchar_t);
        vector<char> ubuf(len);
        
        uint32_t ulen = PA_ConvertCharsetToCharset(
                                                   (char *)inform.c_str(),
                                                   inform.size() * sizeof(wchar_t),
                                                   eVTC_WCHAR_T,
                                                   (char *)&ubuf[0],
                                                   len,
                                                   eVTC_UTF_16
                                                   );
        
        returnValue.setUTF16String((const PA_Unichar *)&ubuf[0], ulen);
    }
    
    returnValue.setReturn(pResult);
}
