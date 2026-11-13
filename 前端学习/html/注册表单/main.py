from flask import Flask,render_template,request

app = Flask(__name__)

@app.route("/register",methods=["GET","POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        psw = request.form.get("password")
        sex = request.form.get("sex")
        city = request.form.get("city")
        print(username,psw,sex,city)
        return "注册成功"

@app.route("/login",methods=["GET","POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    else:
        username = request.form.get("username")
        psw = request.form.get("password")
        print(username,psw)
        return "登陆成功" 

@app.route("/main")
def main():
    return render_template("main.html")

if __name__ == "__main__":
    app.run()
