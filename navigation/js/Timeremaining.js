function alarm(){

    var audio = new Audio('../alarm.mp3');
    audio.loop = false;
    audio.play();
  }
  
  var min="";
  
  //남은 소요시간 보여줌, 딱 10분(600초) 남았을 때 스마트홈 제어창과 알람소리가 들린다.
  var t= setInterval(function(){
    min=parseInt(time/60);
  
    document.getElementById("timeremaining").innerHTML ="소요시간: "+min+"분";
    time--;
  
    if(time==600 && ishouse==true){
      modal.style.display = "block";
      alarm();
    }
  
    if(time<0){
      clearInterval(t);
      document.getElementById("timeremaining").innerHTML= "소요시간: 0분";
    }
  },1000);