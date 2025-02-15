from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

if __name__ == '__main__':
    socketio.run(app,allow_unsafe_werkzeug=True)

@app.route("/")
def index():
  return render_template("index.html", votes=votes)