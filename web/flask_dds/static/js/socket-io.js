const socket = io.connect('http://' + eth0IP + ':9806');
// const socket = io.connect('http://10.21.20.52:9806');
// const socket = io.connect('http://127.0.0.1:3000');

const ul_A = document.getElementById("listA");

let msgID = "";

socket.on('publishReturn', function (evt) {
    console.log('publishReturn');
    console.log(evt);
    let data = evt.data;
    if (data == 'create' || data == 'exist' || data == 'kill' || data == 'not create') {
        //send message from b to a
        let li_A = document.createElement("li");
        li_A.innerHTML = "<div class = 'message-b-to-a-sty' ><img src='/static/img/opendds.png' alt='B' class='message-img' width='31px' class='message-img' height='31px'><div>" + new Date().toLocaleString() + ' publish狀態：' + data + "</div></div>"
        ul_A.appendChild(li_A);
        let listA = document.getElementById("listA");
        listA.scrollTop = listA.scrollHeight;
    } else {
        console.log('訊息已送出');
    }
});

socket.on('subscriberReturn', function (evt) {
    console.log('subscriberReturn');
    console.log(evt);
    let data = evt.data;
    try {
        //send message from b to a
        let li_A = document.createElement("li");
        li_A.innerHTML = "<div class = 'message-b-to-a-sty' ><img src='/static/img/opendds.png' alt='B' class='message-img' width='31px' height='31px'><div>" + new Date().toLocaleString() + ' subscriber狀態：' + data + "</div></div>"
        ul_A.appendChild(li_A);
        let listA = document.getElementById("listA");
        listA.scrollTop = listA.scrollHeight;
    } catch (error) {
        console.log("a json error");
    }
});

socket.on('subscriberRecevie', function (evt) {
    console.log('subscriberRecevie');
    console.log(evt);
    let data = evt.data;
    if (data == 'create' || data == 'start subscriber recevie' || data == 'not create' || data == 'exist' || data == 'kill') {
        //send message from b to a
        let li_A = document.createElement("li");
        li_A.innerHTML = "<div class = 'message-b-to-a-sty' ><img src='/static/img/opendds.png' alt='B' class='message-img' width='31px' height='31px'><div>" + new Date().toLocaleString() + ' subscriber狀態：' + data + "</div></div>"
        ul_A.appendChild(li_A);
        let listA = document.getElementById("listA");
        listA.scrollTop = listA.scrollHeight;
    } else if (typeof (data) == 'string') {
        try {
            console.log('1');
            let userMsg = JSON.parse(data).message;
            let userMsgID = JSON.parse(data).from;
            console.log(data, msgID)
            if (userMsgID == msgID) {
                console.log(data);
                console.log('2');
                //send message from a to a
                let li_A = document.createElement("li");
                li_A.innerHTML = "<div class = 'message-a-to-a-sty' ><div>" + new Date().toLocaleString() + userMsg + "</div></div>";
                ul_A.appendChild(li_A);
                let listA = document.getElementById("listA");
                listA.scrollTop = listA.scrollHeight;
                msgID = "";
            } else {
                //send message from b to a
                console.log('3');
                console.log(userMsgID, userMsg)
                let li_A = document.createElement("li");
                li_A.innerHTML = "<div class = 'message-b-to-a-sty' ><img src='/static/img/opendds.png' alt='B' class='message-img' width='31px' height='31px'><div>" + new Date().toLocaleString() + ' subscriber接收到的資料：' + userMsg + "</div></div>"
                ul_A.appendChild(li_A);
                var listA = document.getElementById("listA");
                listA.scrollTop = listA.scrollHeight;
            }
        } catch (e) {
            console.log('json error');
        }
    }
});

$(function () {
    $('#sendA').on('click', function () {
        msgID = parseInt(Math.random() * Math.pow(10, 16)).toString();
        let message = JSON.stringify({ 'from': msgID, 'message': $('#msgA').val() });
        socket.emit('publishSend', {
            'send': message
        });
        $('#msgA').val('');
    });

    $('#publishCreate').on('click', function () {
        // {"active":"create","cmd":"./publisher -DCPSConfigFile rtps.ini","topic":"A"}
        let ini = $('#publishIni').val();
        let topic = $('#publishTopic').val();
        let pubSettingSave = { "type": "pub", "topic": topic, "rtps": ini }
        socket.emit('publishSend', {
            "active": "create",
            "cmd": "./publisher -DCPSConfigFile /home/pi/ini/" + ini,
            "topic": topic
        });
        $.ajax({
            type: "POST",
            url: "pubSetting",
            contentType: "application/json",
            dataType: "json",
            data: JSON.stringify(pubSettingSave),
            success: function (data) {
                console.log('success');
            },
            error: function (data) {
                console.log('error');
            }
        });
        $('#publishTopic').val('');
    });

    $('#publishStatus').on('click', function () {
        socket.emit('publishSend', {
            "active": "status"
        });
    });

    $('#publishExit').on('click', function () {
        socket.emit('publishSend', {
            "active": "exit"
        });
    });

    $('#publishKill').on('click', function () {
        socket.emit('publishSend', {
            "active": "kill"
        });
    });

    $('#subscriberCreate').on('click', function () {
        let ini = $('#subscriberIni').val();
        let topic = $('#subscriberTopic').val();
        let subSettingSave = { "type": "sub", "topic": topic, "rtps": ini }
        console.log(ini, topic);
        socket.emit('subscriberSend', {
            "active": "create",
            "cmd": "./subscriber -DCPSConfigFile /home/pi/ini/" + ini,
            "topic": topic
        });
        $.ajax({
            type: "POST",
            url: "subSetting",
            contentType: "application/json",
            dataType: "json",
            data: JSON.stringify(subSettingSave),
            success: function (data) {
                console.log('success');
            },
            error: function (data) {
                console.log('error');
            }
        });
        $('#subscriberTopic').val('');
    });

    $('#subscriberStart').on('click', function () {
        socket.emit('subscriberRecevieStart', 'start');
    });

    $('#subscriberStatus').on('click', function () {
        socket.emit('subscriberSend', {
            "active": "status"
        });
    });

    $('#subscriberKill').on('click', function () {
        socket.emit('subscriberSend', {
            "active": "kill"
        });
    });
});