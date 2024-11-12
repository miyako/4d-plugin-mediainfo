//%attributes = {}
//var $data : Blob
//$data:=Folder(fk resources folder).file("sample.mp3").getContent()
//$json:=MediaInfo($data; MediaInfo Inform JSON)
//$ob:=JSON Parse($json)

var $path : Text
$path:="Macintosh HD:Users:miyako:Library:CloudStorage:OneDrive-株式会社フォーディー・ジャパン:動画:ios-setup-4k.mp4"
$json:=MediaInfoFile($path; MediaInfo Inform JSON)
$of:=JSON Parse:C1218($json)