import requests
url = 'http://chat.gosunov.ru/getmessages?for=USER'

url = 'https://www.youtube.com/watch?v=pVJ9I0gpMIw'

r = requests.get('http://chat.gosunov.ru/getmessages?for=USER', auth=('user', 'pass'))
print(r.status_code)
200
print(r.headers['content-type'])

print(r.encoding)
'utf-8'
print()
print(r.text)
'{"type":"User"...'
print(r)

