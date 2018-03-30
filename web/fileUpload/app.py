from flask import Flask,request,render_template
from werkzeug.utils import secure_filename
app = Flask(__name__)

@app.route("/upload/")
@app.route("/upload",methods=['GET','POST'])
def upload():
    if request.method == 'POST':
        f = request.files['file']
        f.save('/home/titan/Titan/github/python/flask/fileUpload/file/'+ secure_filename(f.filename))
    return render_template('upload.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
