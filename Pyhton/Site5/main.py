from flask import Flask, render_template
from flask_socketio import SocketIO, emit
from flask import session
from flask import request
from flask import redirect
from flask import url_for
from flask import flash



import shelve
db = shelve.open('passwords.shelf')

canvases = shelve.open('canvases.shelf')

suggestions = shelve.open('suggestions.shelf')
# suggestions[dorty] = ['apple', 'banana', 'peach']



db['non-exist'] = 'strong_pwd'
print(db.__contains__('non-exist'))
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route('/')
def index():
    name = 'Не залогинен'
    user_logged = False
    if 'username' in session:
        name = session["username"]
        user_logged = True
    return render_template('index.html', name=name, user_logged = user_logged)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # устанавливаем сессию для пользователя
        if not db.__contains__(request.form['username']):
            flash('Такого пользователя нет', 'error')
            return render_template('login.html')

        if db[request.form['username']] != request.form['pwd']:
            flash('Пароль неверный', 'error')
            return render_template('login.html')
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return render_template('login.html')

@app.route('/suggest', methods=['GET', 'POST'])
def suggest():
    if request.method == 'POST':
        if 'username' not in session:
            flash('Войдите в аккаунт, чтобы предлагать слова', 'error')
            return render_template('suggest.html')


        print(request.form['suggestion'])
        print((session['username']))
        if not suggestions.__contains__(session['username']):
            suggestions[session['username']] = [request.form['suggestion']]
        else:
            suggestions[session['username']] += [( request.form['suggestion'])]

        print(suggestions[session['username']])

        return render_template('suggest.html', sugs = suggestions[session['username']])
    if not suggestions.__contains__(session['username']):
        return render_template('suggest.html', sugs = ['Вы пока ничего не предложили!'])
    return render_template('suggest.html', sugs = suggestions[session['username']])

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        if db.__contains__(request.form['username']): return 'такой пользователь уже существует, придумайте другой ник'
        # устанавливаем сессию для пользователя
        db[request.form['username']] = request.form['pwd']
        session['username'] = request.form['username']
        return redirect(url_for('index'))
    return render_template('register.html')

@app.route('/logout')
def logout():
    # удаляем имя пользователя из сеанса, если оно есть
    session.pop('username', None)
    return redirect(url_for('index'))


@socketio.on('save')
def handle_message(data):

    #print(data)
    print('saving')
    canvases['one'] = data
    #emit('server message', data[::-1], broadcast=True)

@socketio.on('load')
def handle_message():
    print('loading')
    emit('update_image', canvases['one'], broadcast=False)

if __name__ == '__main__':
    socketio.run(app, debug=True,allow_unsafe_werkzeug=True)

print('finishing stuff')