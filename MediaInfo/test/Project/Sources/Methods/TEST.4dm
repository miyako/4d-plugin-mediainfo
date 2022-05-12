//%attributes = {}
$data:=Folder:C1567(fk resources folder:K87:11).file("sample.mp3").getContent()

$json:=MediaInfo($data; MediaInfo Inform JSON)

$o:=JSON Parse:C1218($json)