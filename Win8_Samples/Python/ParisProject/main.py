#https://www.google.com/search?q=%D0%9F%D0%B0%D1%80%D0%B8%D0%B6


import requests
# import html
import html
searchObj = 'Париж'
url = 'https://www.google.com/search?q=' + searchObj
url = 'https://ru.wikipedia.org/wiki/' + searchObj


r = requests.get(url, auth=('user', 'pass'))
print(r.status_code)
200
print(r.headers['content-type'])

print(r.encoding)
'utf-8'
print()
#print(r.text)
print(html.unescape(r.text))
'{"type":"User"...'
print(r)

