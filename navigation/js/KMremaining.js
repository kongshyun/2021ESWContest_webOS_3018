var km="";

//남은 거리 보여줌
var d = setInterval(function(time){
  km=parseInt(des/1000);

  document.getElementById("km").innerHTML="앞으로 "+km+"km";
  des--;

  if(des<0){
    clearInterval(d);
    document.getElementById("km").innerHTML="앞으로 0km";
  }
},600);

