from flask import Flask,redirect,url_for,request
from flask import render_template
import os

app = Flask(__name__)

@app.route('/')
def index():
    
    return render_template('restart.html')
    

@app.route('/re',methods=['POST'])
def restart():
    print "restart"
    ip = request.form['IP']
    router = request.form['Router']   
    dns = request.form['DNS']   
    print "IP : " + ip + "\n" + "Router : "+router + "\n" + "DNS : " + dns
    os.system("bash static.sh %s %s %s" % (ip,router,dns))
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5000,debug=True)

