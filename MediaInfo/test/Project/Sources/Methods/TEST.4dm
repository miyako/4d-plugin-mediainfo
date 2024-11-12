//%attributes = {}
var $data : Blob
$data:=Folder:C1567(fk resources folder:K87:11).file("sample.mp3").getContent()
$json:=MediaInfo($data; MediaInfo Inform JSON)
$ob:=JSON Parse:C1218($json)

var $path : Text
$path:=Folder:C1567(fk resources folder:K87:11).file("sample.mp3").platformPath
$json:=MediaInfoFile($path; MediaInfo Inform JSON)
$of:=JSON Parse:C1218($json)