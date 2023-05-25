from distutils.core import setup
import py2exe

from distutils.filelist import findall
import javascript

setup(
    console = ['main.py'],

    options = {
        'py2exe': {
            'packages': ['javascript'],

        }
    }
)