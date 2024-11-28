var modal = document.getElementById("myModal");
var ym = document.getElementById("YModal");
var nm = document.getElementById("NModal");

var y = document.getElementById("Yes");
var n = document.getElementById("No");

var mx = document.getElementById("mclose");
var yx = document.getElementById("yclose");
var nx = document.getElementById("nclose");




//예 누르면 스마트홈 제어 시작을 알리는 창을 띄움    
y.addEventListener("click", function() {
  ym.style.display = "block";
  modal.style.display = "none";
  setTimeout(autoclose, 3000);
});
//아니오 누르면 스마트홈 제어 시작하지 않음을 알리는 창을 띄움 
n.addEventListener("click", function() {
  nm.style.display = "block";
  modal.style.display = "none";
  setTimeout(autoclose, 3000);
});


// 팝업의 X 버튼 누르면 닫히게 하기
mx.addEventListener("click", function() {
  modal.style.display = "none";
});

yx.addEventListener("click", function() {
  ym.style.display = "none";
});

nx.addEventListener("click", function() {
  nm.style.display = "none";
});



// 팝업 창 바깥을 클릭해도 팝업이 닫히게 하기
window.onclick = function() {
  if (event.target == modal) {
    modal.style.display = "none";
  }
 if (event.target == ym) {
    ym.style.display = "none";
  }
 if (event.target == nm) {
    nm.style.display = "none";
  }
}

//3초 뒤 팝업 자동으로 닫히게 하기
function autoclose(){
  if(ym.style.display = "block"){
    ym.style.display = "none";
  }
  if (nm.style.display = "block"){
    nm.style.display = "none";
  }
     
}