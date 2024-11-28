const kindID = "com.playlist.db:1";
const bridge = new WebOSServiceBridge();

console.log("js"); 

window.onload = function() {
    putKind();
    putPermissions();
    putDevice();
}

function putKind() {
    let url = 'luna://com.webos.service.db/putKind';
    bridge.onservicecallback = (msg) => {console.log(msg)};
    let params = {
        "id":kindID,
        "owner":"com.playlist.db",
        "indexes": [
            {
                "name": "user",
                "props": [
                    {"name": "user"}
                ]
            },
            {
                "name": "id",
                "props": [
                    {"name": "id"}
                ]
            },
            {
                "name": "vid",
                "props": [
                    {"name": "vid"}
                ]
            },
            {
                "name": "title",
                "props":[
                    {"name": "title"}
                ]
            }
        ]
    };
    bridge.call(url, JSON.stringify(params));
}

function putPermissions() {
    let url = 'luna://com.webos.service.db/putPermissions';
    bridge.onservicecallback = (msg) => {console.log(msg)};
    let params = {
        "permissions":[ 
            { 
               "operations":{ 
                  "read":"allow",
                  "create":"allow",
                  "update":"allow",
                  "delete":"allow"
               },
               "object":kindID,
               "type":"db.kind",
               "caller":"com.playlist.db"
            }
         ]
    };
    bridge.call(url, JSON.stringify(params));
}

function emptyDB() {
    let url = 'luna://com.webos.service.db/del';
    bridge.onservicecallback = (res)=>{console.log(res);};
    
    let params = {
        "query":{ 
            "from":kindID
        }
    };
    bridge.call(url, JSON.stringify(params));
}

function findDeviceHandler(res) {
    console.log(res);
    let results = JSON.parse(res).results;
    
    let main = `<iframe id="player" width="0" height="0" src="https://www.youtube.com/embed/${results[0].vid}?enablejsapi=1&rel=0autoplay=1&amp&loop=1&playlist=`;
    let elem = '';
    for (let i=0; i<results.length; i++) {
        if(i == 0){
            main += `${results[i].vid}`;
        }
        else{
            main += `,${results[i].vid}`;
        }

        elem += `<div class="music" id="music" onclick="change_thumb('music_image${results[i].id}');">
        <div class="music_thumb">
            <image id="music_image${results[i].id}" class="music_image" src="https://i.ytimg.com/vi/${results[i].vid}/hqdefault.jpg"></image>
        </div>
        <div class="details">
            <h3>${results[i].title}</h3>
            <h4>https://youtu.be/${results[i].vid}</h4>
        </div>
    </div>` 
    }


    let thumb = `<image id="thumbnail" class="thumbnail" src="https://i.ytimg.com/vi/${results[0].vid}/hqdefault.jpg"></image>`;
    thumb = thumb + main + '" allowfullscreen allow="autoplay"></iframe>';

    document.getElementById('thum_img').innerHTML = thumb;
    document.getElementById('playlist').innerHTML = elem;
    // createToast_finish(results[0].vid);
}

function findDevice() {
    let url = 'luna://com.webos.service.db/find';
    bridge.onservicecallback = findDeviceHandler;
    var user_name = document.getElementById("title").innerText;

    let params = {
        "query":{ 
            "from":kindID,
            "where":[ 
            { 
                "prop":"user",
                "op":"=",
                "val":user_name
            }
            ]
        }
    };
    bridge.call(url, JSON.stringify(params));
}

function putDeviceHandler(res) {
    let response = JSON.parse(res);
    console.log(res);


    if(response.returnValue) {
        //createToast_success();
        findDevice();
    }
    else {
        alert("Put device error.");
        console.log("Put device error.");
    }
    
}

var num = 0;

function putDevice() {
    let url = 'luna://com.webos.service.db/put';
    bridge.onservicecallback = putDeviceHandler;
   // createToast();
    
    let params = {
        "objects" : [
            {
                "_kind": kindID,
                "user": "sojeong",
                "id": "00",
                "vid": "htVwyYMk_Xg",
                "title": "전쟁터 (Hey kid, Close your eyes) (with Lee Sun Hee)"
            },
            {
                "_kind": kindID,
                "user": "sojeong",
                "id": "01",
                "vid": "uaejCvCMu5I",
                "title": "낙하 (NAKKA) (with IU)"
            },
            {
                "_kind": kindID,
                "user": "sojeong",
                "id": "02",
                "vid": "-PwcLzYMQZY",
                "title": "BENCH (with Zion.T)"
            },
            {
                "_kind": kindID,
                "user": "sojeong",
                "id": "03",
                "vid": "BakKmcAzHBY",
                "title": "째깍 째깍 째깍 (Tictoc Tictoc Tictoc) (with Beenzino)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "04",
                "vid": "cLQox8e9688",
                "title": "Two Of Us (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "05",
                "vid": "LpdJE7HG8Ls",
                "title": "Dig A Pony (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "06",
                "vid": "90M60PzmxEE",
                "title": "Across The Universe (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "07",
                "vid": "seqaTuXkqFI",
                "title": "I Me Mine (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "08",
                "vid": "QDYfEBY9NM4",
                "title": "Let It Be (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "heeran",
                "id": "09",
                "vid": "fUUOX6kAIxI",
                "title": "Dig It (Remastered 2009)"
            },
            {
                "_kind": kindID,
                "user": "bojeong",
                "id": "10",
                "vid": "ZThVobEtp_o",
                "title": "Celebrity (Celebrity)"
            },
            {
                "_kind": kindID,
                "user": "bojeong",
                "id": "11",
                "vid": "04tYkKUPPv4",
                "title": "LILAC (라일락)"
            },
            {
                "_kind": kindID,
                "user": "bojeong",
                "id": "12",
                "vid": "TqIAndOnd74",
                "title": "My sea (아이와 나의 바다)"
            },
            {
                "_kind": kindID,
                "user": "bojeong",
                "id": "13",
                "vid": "7n9D8ZeOQv0",
                "title": "Ah puh (어푸 (Ah puh))"
            },
            {
                "_kind": kindID,
                "user": "bojeong",
                "id": "13",
                "vid": "hiUPJaHjuUk",
                "title": "Troll (Feat. DEAN) (돌림노래 (Feat. DEAN))"
            }
        ]
    };
    bridge.call(url, JSON.stringify(params));
    
    console.log('putDevice', params);
    
}
