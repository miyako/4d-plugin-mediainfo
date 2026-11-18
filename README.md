![version](https://img.shields.io/badge/version-20%2B-E23089)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-mediainfo)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-mediainfo/total)

4d-plugin-mediainfo
===================

4D implementation of the [MediaInfo](https://github.com/MediaArea/MediaInfo) program.

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


## Command reference

**Platforms:** macOS 11.5 or later (universal: Intel and Apple silicon), Windows 64-bit.

---

## Requirements & platform notes

- Both commands take **two mandatory parameters** — there is no optional form. Both are read unconditionally, so omitting either produces undefined behavior rather than a clean 4D error.
- `type` must be one of the `MediaInfo Inform …` constants shipped in `constants.xlf` (values 1–9, listed below). Any other value falls back to MediaInfo's default inform output (inferred — the plugin passes an empty inform template to the library in that case).
- **Failure is silent.** Neither command ever raises a 4D error. An empty BLOB, an unreadable path, or media the library cannot parse all return an empty `TEXT` value. Always check the result for `""` before parsing it.
- `MediaInfo` expects a **classic 4D BLOB** (the `BLOB` type produced by e.g. `DOCUMENT TO BLOB`), not a `4D.Blob` object.
- The whole file is analyzed (`Complete` mode), so large files take proportionally longer. Both commands yield to 4D periodically while scanning, so the interface stays responsive, but a very large or deeply nested file can still take seconds.

---

## MediaInfo

### Syntax

```4d
MediaInfo ( data ; type ) → text
```

### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | Blob | Media data to analyze, as a classic 4D BLOB. The entire BLOB is scanned. |
| `type` | Longint | Output format — one of the `MediaInfo Inform …` constants. |
| `Result` | Text | MediaInfo "Inform" output in the requested format (XML, JSON, CSV, HTML, EBUCore, PBCore, …), or `""` on failure. |

`type` constants (theme **MediaInfo Inform Type**):

| Constant | Value | Output |
|----------|-------|--------|
| `MediaInfo Inform HTML` | 1 | HTML table |
| `MediaInfo Inform CSV` | 2 | CSV |
| `MediaInfo Inform XML` | 3 | XML |
| `MediaInfo Inform JSON` | 4 | JSON |
| `MediaInfo Inform OLDXML` | 5 | legacy XML |
| `MediaInfo Inform EBUCore` | 6 | EBUCore XML |
| `MediaInfo Inform PBCore` | 7 | PBCore XML |
| `MediaInfo Inform PBCore2` | 8 | PBCore 2 XML |
| `MediaInfo Inform EBUCore_JSON` | 9 | EBUCore JSON |

### Description

Reads the media bytes directly from the BLOB — no file is written to disk — and returns MediaInfo's analysis as text. The BLOB is fed to the library in 4 KB chunks, so memory use stays flat regardless of file size (the BLOB itself is already in memory, of course).

### Example

From the plugin's own test method (`test/Project/Sources/Methods/TEST.4dm`):

```4d
var $data : Blob
$data:=Folder:C1567(fk resources folder:K87:11).file("sample.mp3").getContent()
$json:=MediaInfo($data; MediaInfo Inform JSON)
$ob:=JSON Parse:C1218($json)
```

```4d
$path:=Get 4D folder(Current resources folder)+"sample.mp3"
DOCUMENT TO BLOB($path;$data)

$info:=MediaInfo ($data;MediaInfo Inform XML)
$info:=MediaInfo ($data;MediaInfo Inform CSV)
$info:=MediaInfo ($data;MediaInfo Inform HTML)
$info:=MediaInfo ($data;MediaInfo Inform JSON)
```

---

## MediaInfoFile

### Syntax

```4d
MediaInfoFile ( path ; type ) → text
```

### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `path` | Text | Platform path of the media file to analyze. |
| `type` | Longint | Output format — one of the `MediaInfo Inform …` constants (same table as `MediaInfo`). |
| `Result` | Text | MediaInfo "Inform" output in the requested format, or `""` on failure. |

### Description

Opens `path` and streams it through the same MediaInfo analysis as `MediaInfo`, in 4 KB chunks. Use this when the media already lives on disk — it avoids loading the whole file into a BLOB first.

The path is interpreted as a platform path: UTF-8 on macOS, UTF-16 on Windows. If the file cannot be opened (missing file, insufficient permissions), the command returns `""`.

### Example

From the plugin's own test method (`test/Project/Sources/Methods/TEST.4dm`):

```4d
var $path : Text
$path:=Folder:C1567(fk resources folder:K87:11).file("sample.mp3").platformPath
$json:=MediaInfoFile($path; MediaInfo Inform JSON)
$of:=JSON Parse:C1218($json)
```

```4d
$info:=MediaInfoFile ("/Users/me/Music/song.mp3"; MediaInfo Inform XML)
```

---

## Choosing a format and reading the result

The `type` parameter selects MediaInfo's "Inform" template. `MediaInfo Inform JSON` (value 4) returns a JSON document you can parse with 4D's `JSON Parse`; `MediaInfo Inform XML` (value 3) returns the classic MediaInfo XML; `MediaInfo Inform CSV` (value 2) returns one row per field, convenient for `TEXT TO ARRAY`-style splitting.

The JSON and XML outputs contain a `media` root with `tracks` (general, video, audio, text, …). Which fields appear depends on what MediaInfo can detect in the file — a truncated or unusual file yields fewer tracks and fields.

---

## Error handling & troubleshooting

- **Empty result, no error** — every failure path (empty BLOB, missing file, unopenable file, unparseable media, unknown `type` fallback) returns `""` instead of raising a 4D error. Check `If($info="")` before parsing.
- **Both parameters are mandatory** — the plugin reads parameter 1 and 2 unconditionally. Calling with fewer than two arguments is undefined behavior, not a clean error.
- **`4D.Blob` object won't work** — `MediaInfo` reads a classic `BLOB`. Convert first, e.g. `DOCUMENT TO BLOB` or `.getContent()` on a `File` object (as the test method does).
- **Path must be a platform path** — `MediaInfoFile` does not resolve 4D-specific paths or aliases; pass an absolute filesystem path (`.platformPath` in the test method).
- **Slow on large files** — analysis runs in `Complete` mode over the entire input. Expect seconds, not milliseconds, on multi-GB video; the commands yield periodically so 4D stays responsive meanwhile.
- **Output encoding** — the result is 4D `Text` (UTF-16). Non-ASCII metadata (artist names, titles) survives the conversion; the underlying library output is UTF-8 internally.

---

## Quick reference

```4d
// Analyze a file on disk
$json:=MediaInfoFile("/path/to/media.mp3"; MediaInfo Inform JSON)
$ob:=JSON Parse($json)

// Analyze bytes already in memory
DOCUMENT TO BLOB("/path/to/media.mp3";$data)
$xml:=MediaInfo($data; MediaInfo Inform XML)

// CSV for simple field extraction
$csv:=MediaInfoFile($path; MediaInfo Inform CSV)
```

## Examples

```4d
$path:=Get 4D folder(Current resources folder)+"sample.mp3"
DOCUMENT TO BLOB($path;$data)

$info:=MediaInfo ($data;MediaInfo Inform XML)
$info:=MediaInfo ($data;MediaInfo Inform CSV)
$info:=MediaInfo ($data;MediaInfo Inform HTML)
$info:=MediaInfo ($data;MediaInfo Inform JSON)
```

**Note**: `2.2.0` added More formats. see [constants.xlf](https://raw.githubusercontent.com/miyako/4d-plugin-mediainfo/refs/heads/master/constants.xlf)

## Releases

Prebuilt plugins for macOS (universal) and Windows 64-bit are attached to each [GitHub release](../../releases).

## License

[MIT](LICENSE)
