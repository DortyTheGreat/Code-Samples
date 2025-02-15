import requests
from PIL import Image  # install by > python3 -m pip install --upgrade Pillow  # ref. https://pillow.readthedocs.io/en/latest/installation.html#basic-installation
import os
url_base = "https://cdn.rawdex.net/manga_"
manga = "634b42d85d128"

# [f,l]
first = 7
last = 22

pdf_bytes = 0
arr_of_files = []

pdf_number = 1

strin = "<!DOCTYPE html>\n<html>\n<head>\n<style>\nimg { \nwidth: 100%;\n}\n</style>\n</head>\n<body>\n"

for chapter in range(first,last):

    for page in range(1, 99):
        #

        url_actual = url_base + manga + "/" + "{:02d}".format(chapter) + "/" + "{:02d}".format(page) + ".jpg"
        file_name = str('dw/' + "{:02d}".format(chapter) + "-" + "{:02d}".format(page) + ".jpg")



        r = requests.get(url_actual)
        if r.text[0] == '<':
            break

        strin += "<img src=\"" + url_actual + "\">\n"
        print(url_actual)
        open(file_name, 'wb').write(r.content)



        arr_of_files += [file_name]



        print(os.stat(file_name).st_size)

images = [Image.open(f) for f in arr_of_files]
pdf_path = "dw/" + "{:02d}".format(99) + ".pdf"

images[0].save(
    pdf_path, "PDF", resolution=100.0, save_all=True,
    append_images=images[1:]
)

strin += "</body>\n</html>\n"

text_file = open("web.html", "w")
n = text_file.write(strin)
text_file.close()