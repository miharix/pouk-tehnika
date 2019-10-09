<?php

$karticaID=$_GET["ID"]; //dobi ID karitce posredovan preko get npr moja_spletna.si/izdelek.php?ID=0007812345

//glede na dobljen ID izvedi ustrezno preusmeritev
function PreusmeriNa($ID_kartice){
	$preusmeritve = array
	(//ID kartice => URL redirekcije
		"0007812345" => "http://m.os-mk.si/izdelki/izdelek1.html",
		"0007812348" => "http://m.os-mk.si/izdelki/izdelek2.html",
		"0007812344" => "http://m.os-mk.si/izdelki/izdelek3.html",
		"0007800114" => "http://m.os-mk.si/TIT6.html#/8",
		);
	
	if($preusmeritve[$ID_kartice]!=NULL){ //če je ID v seznamu izvedi ustrezo preusmeritev če ni preusmeri na določeno stran
		return($preusmeritve[$ID_kartice]);
	}else{
		return "http://m.os-mk.si";
	}
}

function KateraStran($ID_kartice){
	//preveri, da je ID numerična številka in da je dolga 10 števk
	if((ctype_digit($ID_kartice))&&(strlen($ID_kartice)===10)){
		return PreusmeriNa($ID_kartice);
	}else{
		return "http://m.os-mk.si";
	}
	
}

//echo KateraStran($karticaID);

header("Location: ".KateraStran($karticaID),302); //brskalniku v HTML headerju sporoči da je stran začasno preusmerejena -> brskalnik ne bo keširal strani, torej bo vedno točno to kar je nadanje shranjeno

?>
