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

sed -i '' s:DCPSBit=1/0:DCPSBit=" + data["DCPSBit"]+": ./ini/file/" + data["ini_file_name"]+".ini"

### 圖片來源

A:(https://pixabay.com/zh/a-%E4%BF%A1-%E5%AD%97%E6%AF%8D-%E6%8C%89%E5%AD%97%E6%AF%8D%E9%A1%BA%E5%BA%8F-%E7%BE%8E%E5%9B%BD%E5%B9%BF%E6%92%AD%E5%85%AC%E5%8F%B8-1015528/)[https://pixabay.com/zh/a-%E4%BF%A1-%E5%AD%97%E6%AF%8D-%E6%8C%89%E5%AD%97%E6%AF%8D%E9%A1%BA%E5%BA%8F-%E7%BE%8E%E5%9B%BD%E5%B9%BF%E6%92%AD%E5%85%AC%E5%8F%B8-1015528/]

B:(https://pixabay.com/zh/b-%E4%BF%A1-%E5%AD%97%E6%AF%8D-%E6%8C%89%E5%AD%97%E6%AF%8D%E9%A1%BA%E5%BA%8F-%E7%BE%8E%E5%9B%BD%E5%B9%BF%E6%92%AD%E5%85%AC%E5%8F%B8-1015529/)[https://pixabay.com/zh/b-%E4%BF%A1-%E5%AD%97%E6%AF%8D-%E6%8C%89%E5%AD%97%E6%AF%8D%E9%A1%BA%E5%BA%8F-%E7%BE%8E%E5%9B%BD%E5%B9%BF%E6%92%AD%E5%85%AC%E5%8F%B8-1015529/)]