from flask import Flask, render_template
from flask_socketio import SocketIO, emit
from flask import session
from flask import request
from flask import redirect
from flask import url_for
from flask import flash

import os
import shelve


# У Юзера будет доступ к прикреплению к одному лобби. Если лобби нет, то этот lobbyAttached=-1
# Т.к. тут немного особенная реализрацияя получения юзера i.e. Uers['username'] = User(...), то юзернейм я не храню, ибо он - есть ключ
# Звучит не очень, но мне пофиг. Пока

# Хочу отметить, что юзер прикреплён к лобби. Т.е. если он "внутри лобби"
class User:
    def __init__(self, _lobbyAttached, _pwd):
        # self.name = _name
        self.lobbyAttached = _lobbyAttached
        self.pwd = _pwd


class Lobby:
    def __init__(self, _owner, _users, _name):
        # self.name = _name
        self.owner = _owner
        self.name = _name
        self.users = _users  # Список из name'ов. ['Oleg', 'Lesha', 'Dmitrii']
        self.state = 'w'  # w - waiting, люди ожидают. 'r' - running, игра уже идёт

    def add_users(self, new_user):
        return Lobby(self.owner, self.users + [new_user], name)


def db_create():
    for bd in ['variables.shelf', 'users.shelf', 'canvases.shelf', 'lobbies.shelf', 'suggestions.shelf']:
        with shelve.open(bd, 'c') as vars:
            pass  # создаём, если вдруг нет файлика

db_create()

def db_new_create():
    for bd in ['variables.shelf', 'users.shelf', 'canvases.shelf', 'lobbies.shelf', 'suggestions.shelf']:
        with shelve.open(bd, 'n') as vars:
            pass  # создаём, если вдруг нет файлика


def db_fix():
    with shelve.open('variables.shelf', 'w') as vars:
        if not vars.__contains__('total_pictures'):
            vars['total_pictures'] = 0
        if not vars.__contains__('new_lobby_id'):
            vars['new_lobby_id'] = 0


def isValidSugg(strin):
    if len(strin) < 2 or len(strin) > 40: return False  # слишком длинная или слишком короткая
    if any((c1 == c2) and (c1 == ' ') for c1, c2 in zip(strin, strin[1:])): return False  # 2 последовательных пробела
    if strin[-1] == ' ': return False  # нельзя писать пробел в конце

    return all(char in 'йцукенгшщзхъфывапролджэячсмитьбюё ' for char in strin)


# suggestions[dorty] = ['apple', 'banana', 'peach']


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
    return render_template('index.html', name=name, user_logged=user_logged)


@app.route('/about')
def about():
    return render_template('about.html')


@app.route('/blogs')
def blogs():
    return render_template('blogs.html')


@app.route('/blogs/gcd_benchmarks')
def gcd_benchmarks():
    image = os.path.join('static', 'gcd_benchmarks.png')
    return render_template('gcd_benchmarks.html')


@app.route('/admin', methods=['GET', 'POST'])
def admin():
    if request.method == 'GET': return render_template('admin.html', admin=False)
    if request.form['activation_key'] != '4':
        flash('Неверный ключ', 'error')
        return render_template('admin.html', admin=False)

    if request.form.__contains__('deleteBD'):
        db_new_create()
        db_fix()

    user_str = []
    with shelve.open('users.shelf', 'r') as users:
        for (key) in users:
            print(key)
            strin = str(key)
            strin += " "
            strin += str(users[key].lobbyAttached) + " "
            strin += str(users[key].pwd)
            print(strin)
            user_str += [strin]
    print(user_str)
    return render_template('admin.html', admin=True, user_str=user_str)


@app.route('/picture')
def picture():
    with shelve.open('canvases.shelf', 'r') as canvases:

        if request.args.get("id") == None:
            return render_template('index.html', name="Напиши site_name/picture?id=one")

        if not canvases.__contains__(request.args.get("id")):
            return render_template('index.html', name="Нет такой картинки")

        return render_template('picture.html', picture=canvases[request.args.get("id")])


@app.route('/play')
def play():
    with shelve.open('lobbies.shelf', 'r') as lobbies:
        arr = []
        for index in lobbies:
            arr += [lobbies[index].name + " - Владелец: " + lobbies[index].owner + " - Участников: " + str(
                len(lobbies[index].users))]
        return render_template('play.html', Len=len(arr), text=arr)


@app.route('/lobby', methods=['GET', 'POST'])
def lobby():
    if not 'username' in session:
        flash('Вы не залогинены', 'error')
        return play()

    id_ = request.args.get("id")  # Номер лобби, в которое юзер хочет зайти

    if id_ == None:
        flash('Лобби некорректно', 'error')
        return play()

    if not lobbies.__contains__(id_):
        flash('Лобби некорректно', 'error')
        return play()

    # if request.method == 'GET':

    return render_template('lobby.html', )
    '''
    with shelve.open('users.shelf', 'w') as users:
        with shelve.open('lobbies.shelf', 'w') as lobbies:
            if users[ session['username'] ].lobbyAttached == -1:
                users[ session['username'] ] = User( int(id_), users[ session['username'] ].pwd)
                lobbies[ id_] = lobbies[ id_].add_users(session['username'])
                return 1 # ### TO-DO] запихнуть юзера в его лобби html

            if lobbies[ users[ session['username'] ].lobbyAttached ].owner ==

    if session['username']
        # Подгрузи его в это лобби
    '''


@app.route('/createLobby', methods=['GET', 'POST'])
def createLobby():
    if not ('username' in session):
        flash('Вы не залогинены', 'error')
        return redirect(url_for('play'))

    hasLobby = -228
    with shelve.open('users.shelf', 'r') as users:
        hasLobby = users[session['username']].lobbyAttached
        print('detected')
        print(users[session['username']].lobbyAttached)

    if request.method == 'GET': return render_template('createLobby.html', hasLobby=hasLobby)

    if hasLobby != -1:
        flash('Уже есть лобби', 'error')

        if request.form.__contains__('delete'):
            with shelve.open('lobbies.shelf', 'w') as lobbies:
                with shelve.open('users.shelf', 'w') as users:
                    lobbies.pop(str(users[session['username']].lobbyAttached))  # Удалим это лобби
                    users[session['username']] = User(-1, users[session['username']])

        return redirect(url_for('play'))

    with shelve.open('variables.shelf', 'w') as variables:
        with shelve.open('lobbies.shelf', 'w') as lobbies:
            with shelve.open('users.shelf', 'w') as users:
                lobbies[str(variables['new_lobby_id'])] = Lobby(session['username'], [request.form['Name']],
                                                                request.form['Name'])
                users[session['username']] = User(variables['new_lobby_id'], users[session['username']].pwd)
                print('attached')
                print(users[session['username']].lobbyAttached)
                print(variables['new_lobby_id'])
                variables['new_lobby_id'] = variables['new_lobby_id'] + 1

                return redirect(url_for('play'))

    return render_template('createLobby.html', hasLobby=hasLobby)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET': return render_template('login.html')

    with shelve.open('users.shelf', 'r') as users:
        if not users.__contains__(request.form['username']):
            flash('Такого пользователя нет', 'error')
            return render_template('login.html')
        if users[request.form['username']].pwd != request.form['pwd']:
            flash('Пароль неверный', 'error')
            return render_template('login.html')
    session['username'] = request.form['username']
    return redirect(url_for('index'))


@app.route('/suggest', methods=['GET', 'POST'])
def suggest():
    if 'username' not in session:
        flash('Войдите в аккаунт, чтобы предлагать слова', 'error')
        return render_template('suggest.html', logined=False, Len=0)

    if request.method == 'POST':

        print(request.form)

        with shelve.open('suggestions.shelf', 'w') as suggestions:
            if (request.form.__contains__('suggestion')):

                if isValidSugg(request.form['suggestion']):
                    if not suggestions.__contains__(session['username']):
                        suggestions[session['username']] = [request.form['suggestion']]
                    else:
                        suggestions[session['username']] += [(request.form['suggestion'])]
                else:
                    flash('ERROR_DUMB', 'error')

            else:
                index = int(list(request.form)[0])
                if index < 0 or index >= len(suggestions[session['username']]):
                    flash('ERROR_BURGER', 'error')
                else:
                    temp_list = suggestions[session['username']]
                    temp_list.pop(index)
                    suggestions[session['username']] = temp_list

    with shelve.open('suggestions.shelf', 'r') as suggestions:
        if not suggestions.__contains__(session['username']):
            return render_template('suggest.html', sugs=['Вы пока ничего не предложили!'], logined=True, Len=0)
        return render_template('suggest.html', sugs=suggestions[session['username']], logined=True,
                               Len=len(suggestions[session['username']]))


@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        with shelve.open('users.shelf', 'r') as users:
            if users.__contains__(request.form['username']):
                flash('такой пользователь уже существует, придумайте другой ник', 'error')
                return render_template('register.html')
        # устанавливаем сессию для пользователя и записываем пароль
        with shelve.open('users.shelf', 'w') as users:
            users[request.form['username']] = User(-1, request.form['pwd'])
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
    # print(data)
    print('saving')
    with shelve.open('variables.shelf', 'w') as vars:
        vars['total_pictures'] = vars['total_pictures'] + 1
        with shelve.open('canvases.shelf', 'w') as canvases:
            canvases[str(vars['total_pictures'])] = data
            flash('успешно сохранили под' + str(vars['total_pictures']), 'error')
    # emit('server message', data[::-1], broadcast=True)


@socketio.on('load')
def handle_message():
    print('loading')
    with shelve.open('canvases.shelf', 'r') as canvases:
        emit('update_image', canvases['one'], broadcast=False)


if __name__ == '__main__':
    socketio.run(app, debug=True, allow_unsafe_werkzeug=True)

print('finishing stuff')
