/* --------------------------------------------------------------------------------
 #
 #	4DPlugin-MediaInfo.h
 #	source generated by 4D Plugin Wizard
 #	Project : MediaInfo
 #	author : miyako
 #	2022/05/12
 #  
 # --------------------------------------------------------------------------------*/

#ifndef PLUGIN_MEDIAINFO_H
#define PLUGIN_MEDIAINFO_H

#include "4DPluginAPI.h"

#include "MediaInfo.h"
#include "MediaInfo/MediaInfo_Internal.h"

#include "C_TEXT.h"
#include "C_BLOB.h"
#include "C_LONGINT.h"

#define STREAM_BUFFER_SIZE 4096

#define MediaInfo_Inform_HTML (1)
#define MediaInfo_Inform_CSV (2)
#define MediaInfo_Inform_XML (3)
#define MediaInfo_Inform_JSON (4)

#if VERSIONWIN
#include <time.h>
#endif

#pragma mark -

void MediaInfo(PA_PluginParameters params);

#endif /* PLUGIN_MEDIAINFO_H */
