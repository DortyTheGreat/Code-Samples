import sqlite3
from flask import g

DATABASE = 'kurs_bd.db'

from flask import Flask, render_template, request,jsonify,json,g


app = Flask(__name__)

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db


def run_txt_script(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        contents = file.read()
        with app.app_context():
            get_db().executescript(contents)


def super_clear_db():
    with open(DATABASE, 'w', encoding='utf-8') as file:
        file.truncate(0)


super_clear_db()
run_txt_script("create_dbs.txt")


@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()