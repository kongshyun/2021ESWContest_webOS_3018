var isPlayed = false;
        
        
$(function(){
    $("#start").click(function(){
        if(isPlayed == false){
            $("#player")[0].contentWindow.postMessage('{"event":"command","func":"' + 'playVideo' + '","args":""}', '*');
            isPlayed = true;
            var element = document.getElementById("start");
            element.innerHTML = '<i class="fas fa-pause"></i>';
        }

        else{
            $("#player")[0].contentWindow.postMessage('{"event":"command","func":"' + 'pauseVideo' + '","args":""}', '*');
            isPlayed = false;
            var element = document.getElementById("start");
            element.innerHTML = '<i class="fas fa-play"></i>';
        }
    });   

    $("#previous").click(function(){
        $("#player")[0].contentWindow.postMessage('{"event":"command","func":"' + 'previousVideo' + '","args":""}', '*');
        isPlayed = true;
        var element = document.getElementById("start");
        element.innerHTML = '<i class="fas fa-pause"></i>';
    });

    $("#next").click(function(){
        $("#player")[0].contentWindow.postMessage('{"event":"command","func":"' + 'nextVideo' + '","args":""}', '*');
        isPlayed = true;
        var element = document.getElementById("start");
        element.innerHTML = '<i class="fas fa-pause"></i>';
    });
})


function change_thumb(obj){
    var image_src = document.getElementById(obj).src;
    document.getElementById("thumbnail").src = image_src;
    
    videoID = image_src.substr(23, 11);
    document.getElementById("player").src = "https://www.youtube.com/embed/" + videoID + document.getElementById("player").src.substr(41);

    isPlayed = true;
    var element = document.getElementById("start");
    element.innerHTML = '<i class="fas fa-pause"></i>';

}

$("#music").on("click", function(){ $("#player")[0].contentWindow.postMessage('{"event":"command","func":"' + 'playVideo' + '","args":""}', '*'); });
