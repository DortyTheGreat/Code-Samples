import requests


import time

from urllib3.exceptions import InsecureRequestWarning
from urllib3 import disable_warnings

disable_warnings(InsecureRequestWarning)

url_base = "https://dota.gallery/art/"

#login
'''
Мы можем скачивать контент с dota.gallery. В целом можно скачать ВООБЩЕ ВСЮ галлерею. Получится около 25 тысяч файлов.
Однако мне не нужны были все файлы, а лишь видео. Их скачать сложнее всего, ведь для получения ссылки нужно
авторизоваться, а для этого приходится танцевать с бубном( _csrf). В общем и целом не сложно понять, как модифицировать
код, чтобы скачать, например, всю галлерею, или, например, только NSFW картинки, или только SFW-картинки или весь 
SFW контент. Вообще можно очень просто пропарсить по тэгам, найти изображения только с определённым героем

FAQ(?)

1) Нужно скачать некие стороние библиотки. Понятия не имею почему, но это решает одну из проблем с запросами
2) requests.adapters.HTTPAdapter(max_retries=20). Это тоже должно решать проблему с крашами. Действительно помогает
3) Как последняя заплатка, мне сказали перед каждым запросом добавлять ожидание (time.sleep, сказали, что и 0.01 
секунды хватит, но я решил перестраховаться и поставил 0.1)

4) Есть ещё несколько "случайных" заплаток, которые, надеюсь, фиксят код. Однако всё равно всё крашится, поэтому, я
добавил последнюю заплатку. try-except.


libs:
python3 -m pip install --upgrade requests
python3 -m pip install --upgrade ndg-httpsclient
python3 -m pip install --upgrade pyopenssl
python3 -m pip install --upgrade pyasn1

?
pip install certifi
pip install certifi_win32

'''

# Fill in your details here to be posted to the login form.


def try_get(session, url):
        try:
                return session.get(url)
        except:
                print('retrying get')
                time.sleep(hard_retry_sleep_time)
                return try_get(session,url)


def try_post(session, url, payload):
        try:
                return s.post(url, data=payload)
        except:
                print('retrying post')
                time.sleep(hard_retry_sleep_time)
                return try_post(session,url, payload)


def download_video(link, id):



        r = try_get(requests, link)
        #print(r.text)
        #if r.text[0] == '<':
            #break

        file_name = 'videos/' + str(id) + ".mp4"

        open(file_name, 'wb').write(r.content)


sleep_time = 0.1
hard_retry_sleep_time = 3







# Use 'with' to ensure the session context is closed after use.
with requests.Session() as s:

        adapter = requests.adapters.HTTPAdapter(max_retries=20)
        s.mount('http://', adapter)

        url = "https://dota.gallery/login"
        print(url)

        time.sleep(sleep_time)



        r = try_get(s,url)


        csrf = r.text[r.text.find('csrf-token') + 21:r.text.find('csrf-token') + 21 + 88]
        print(csrf)
        print('salami')
        payload = {
                "_csrf" : csrf,
                'LoginForm[username]': 'Igor',
                'LoginForm[password]': 'strongPassword',
                'LoginForm[rememberMe]': 1,

        }
        time.sleep(sleep_time)
        p = try_post(s, url, payload)


        file_name = 'htmls/login-log.html'

        open(file_name, 'wb').write(p.content)

        # An authorised request.
        #r = s.get('A protected web page url')
        #print (r.text)
        # etc...
        # login ...


        # 26-02 11к остановился
        first = 24668
        last = 27000

        for art in range(first, last):
                url_actual = url_base + str(art)

                # file_name = str('dw/' + "{:02d}".format(chapter) + "-" + "{:02d}".format(page) + ".jpg")

                print(url_actual)

                time.sleep(sleep_time)
                r = try_get(s,url_actual)
                mp4_location = r.text.find('.mp4')
                nsfw_location = r.text.find('NSFW')
                if mp4_location == -1 or nsfw_location == -1:
                        print(art, ' не валидный ', mp4_location, nsfw_location)
                        #time.sleep(0.5)
                        continue
                ic_location = r.text.find('/images/clips/')
                path = r.text[ic_location:mp4_location]

                download_video("https://dota.gallery" + path + ".mp4", art)

                file_name = 'htmls/' + str(art) + ".html"

                open(file_name, 'wb').write(r.content)




