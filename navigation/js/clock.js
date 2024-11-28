//오늘 날짜와 현재 시간을 보여줌
function clock(){
    var today = new Date();
    var m = today.getMonth() + 1;
    var d = today.getDate();
    var day = today.getDay();

    var week = ["월요일","화요일","수요일","목요일","금요일","토요일","일요일"]
    var hour = today.getHours();
    var min = today.getMinutes();
    var sec = today.getSeconds();
    
    document.getElementById("clock").innerHTML=
    m+"월 "+d+"일<br/>"+week[day]+"<br/>"+hour+":"+min+":"+sec;
  }
  setInterval(clock,1000);