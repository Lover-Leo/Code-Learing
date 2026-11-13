from flask import Flask,render_template

app = Flask(__name__)

@app.route("/show/info")
def index():
    return render_template("index.html")

@app.route("/show/memory")
def memory():
    return render_template("memory.html")

if __name__ == '__main__':
    app.run()