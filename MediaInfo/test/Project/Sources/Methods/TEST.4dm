//%attributes = {}
//var $data : Blob
//$data:=Folder(fk resources folder).file("sample.mp3").getContent()
//$json:=MediaInfo($data; MediaInfo Inform JSON)
//$ob:=JSON Parse($json)

var $path : Text
$path:="Macintosh HD:Users:miyako:Desktop:画面収録 2024-11-13 10.27.22.mov"
//$path:=Folder(fk resources folder).file("sample.mp3").platformPath
$json:=MediaInfoFile($path; MediaInfo Inform JSON)
$of:=JSON Parse:C1218($json)