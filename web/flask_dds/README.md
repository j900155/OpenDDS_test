# flask_dds

```
FLASK_APP=app.py flask run
```

socketio port 9806

publisher event
	send data and command use "publishSend"
	get return use "publishReturn"

subscriber event
	send data and command use "subscriberSend"
	get return use "subscriberReturn"
	get publisher send data use "subscriberRecevieStart" to start event then use subscriberRecevie to get data

{"send":"your data"}
{"active":"create","cmd":"./publisher -DCPSConfigFile rtps.ini","topic":"A"}

{"active":"create","cmd":"./subscriber -DCPSConfigFile rtps.ini","topic":"A"}

{"active":"status"}
{"active":"exit"}
{"active":"kill"}