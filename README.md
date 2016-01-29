4d-plugin-mediainfo
===================

4D implementation of the MediaInfo program.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|🆗|🆗|🆗|🆗|

Commands
---

```c
// --- MediaInfo
MediaInfo
```

Examples
---

```
$path:=Get 4D folder(Current resources folder)+"sample.mp3"
DOCUMENT TO BLOB($path;$data)

$info:=MediaInfo ($data;MediaInfo Inform XML)
$info:=MediaInfo ($data;MediaInfo Inform CSV)
$info:=MediaInfo ($data;MediaInfo Inform HTML)
```
