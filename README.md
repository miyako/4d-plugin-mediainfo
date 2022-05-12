![version](https://img.shields.io/badge/version-17%2B-3E8B93)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-mediainfo )](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-mediainfo/total)

4d-plugin-mediainfo
===================

4D implementation of the [MediaInfo](https://mediaarea.net/ja/MediaInfo) program.

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

macOS : `v22.03`

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

```4d
info:=MediaInfo (data;type)
```

Parameter|Type|Description
------------|------------|----
data|BLOB|
type|LONGINT|``MediaInfo Inform XML``, ``MediaInfo Inform CSV``, ``MediaInfo Inform HTML``
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
