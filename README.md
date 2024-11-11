![version](https://img.shields.io/badge/version-20%2B-E23089)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-mediainfo)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-mediainfo/total)

4d-plugin-mediainfo
===================

4D implementation of the [MediaInfo](https://github.com/MediaArea/MediaInfo) program. (`22.03`)

```4d
info:=MediaInfo (data;type)
```

Parameter|Type|Description
------------|------------|----
data|BLOB|classic `C_BLOB`, not `4D.Blob` object
type|LONGINT|``MediaInfo Inform XML``, ``MediaInfo Inform CSV``, ``MediaInfo Inform HTML``, `MediaInfo Inform JSON`
info|TEXT|

```4d
info:=MediaInfoFile (path;type)
```

Parameter|Type|Description
------------|------------|----
path|TEXT|
type|LONGINT|``MediaInfo Inform XML``, ``MediaInfo Inform CSV``, ``MediaInfo Inform HTML``, `MediaInfo Inform JSON`
info|TEXT|


## Examples

```4d
$path:=Get 4D folder(Current resources folder)+"sample.mp3"
DOCUMENT TO BLOB($path;$data)

$info:=MediaInfo ($data;MediaInfo Inform XML)
$info:=MediaInfo ($data;MediaInfo Inform CSV)
$info:=MediaInfo ($data;MediaInfo Inform HTML)
$info:=MediaInfo ($data;MediaInfo Inform JSON)
```
