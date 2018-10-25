const wsUrl = 'ws://127.0.0.1:3000';
const websocket = new WebSocket(wsUrl);

const ul_A = document.getElementById("listA");
const ul_B = document.getElementById("listB");

websocket.onopen = function (evt) {
    console.log('Connected');
    // websocket.send('Hello Server!');
};
websocket.onclose = function (evt) {
    console.log('DisConnected');
};
websocket.onmessage = function (evt) {
    console.log('Got Message');
    console.log(evt.data);
    try {
        let data = JSON.parse(evt.data);
        if (data.from == 'A') {
            //send message from a to b
            var li_A = document.createElement("li");
            li_A.innerHTML = "<div class = 'message-a-to-a-sty' ><div>" + data.msg + "</div></div>";
            ul_A.appendChild(li_A);

            var li_B = document.createElement("li");
            li_B.innerHTML = "<div class = 'message-a-to-b-sty' ><img src='/static/img/A.jpg' alt='A' width='31px' height='31px'><div>" + data.msg + "</div></div>";
            ul_B.appendChild(li_B);

            let listA = document.getElementById("listA");
            listA.scrollTop = listA.scrollHeight;
            let listB = document.getElementById("listB");
            listB.scrollTop = listB.scrollHeight;
        } else if (data.from == 'B') {
            //send message from b to a
            let li_A = document.createElement("li");
            li_A.innerHTML = "<div class = 'message-b-to-a-sty' ><img src='/static/img/B.jpg' alt='B' width='31px' height='31px'><div>" + data.msg + "</div></div>"
            ul_A.appendChild(li_A);
            //send message from b to b
            let li_B = document.createElement("li");
            li_B.innerHTML = "<div class = 'message-b-to-b-sty' ><div>" + data.msg + "</div></div>";
            ul_B.appendChild(li_B);

            let listA = document.getElementById("listA");
            listA.scrollTop = listA.scrollHeight;
            let listB = document.getElementById("listB");
            listB.scrollTop = listB.scrollHeight;
        }
    } catch (error) {
        console.log("json error");
    }
    // var msg = $('<div>').append(evt.data);
    // $('#messages').append(msg);
};
websocket.onerror = function (evt) {
    console.log('Something\'s wrong');
};

$(function () {
    $('#sendA').on('click', function () {
        websocket.send(JSON.stringify({ "from": "A", "msg": $('#msgA').val() }));
        $('#msgA').val('');
    });

    $('#sendB').on('click', function () {
        websocket.send(JSON.stringify({ "from": "B", "msg": $('#msgB').val() }));

        $('#msgB').val('');
    });
});