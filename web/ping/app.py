from flask import Flask,request,render_template
import subprocess
import json

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html');

@app.route('/ping',methods=['POST'])
def ping():
    ip = request.form.get('ip')
    try:
        response = subprocess.check_output(
            ['ping', '-c', '1', ip],
            stderr=subprocess.STDOUT,  # get all output
            universal_newlines=True  # return string not bytes
            )
    except :
        response = "From "+ ip +" Destination Host Unreachable"
    return response

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
