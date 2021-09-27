"use strict";
const BOUND=6;
//document.write('<xmp>');
for(let i=1;i<=BOUND; i=i+1) {
	document.writeln('<table>');
	document.write('<tr><td colspan="8">第' + i + '張卡片'
				+'<input type="checkbox" name="card" value="i">'
				+'</td></tr>');
	for(let j=0,k=2**(i-1);j<32;j++){
		if(j==0 || j==8 || j==16 || j==24)
			{document.write('<tr>');}
		document.write('<td>' + (j*2-j%k+k) + '</td>');
		if(j==7|| j==15 || j==23 || j==31)
			{document.write('</tr>');}
	}
	document.writeln('</table>');
	
}
var btn=document.getElementById("btnAnswer");
var clear=document.getElementById("btnClear");
btn.onclick=function(){
    var obj=document.getElementsByName("card");
    var selected=[];
	var x=0;
    for (var i=0; i<obj.length; i++) {
        if (obj[i].checked) {
			x=x+2**(i);
			
		}
    }
	alert("你心裡想的數是 : " + x);
};

clear.onclick=function(){
	var obj=document.getElementsByName("card");
	for (var i=0; i<obj.length; i++) {
        if (obj[i].checked) {
			obj[i].checked = false;
		}
    }
};