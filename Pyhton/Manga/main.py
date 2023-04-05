import cv2

#python3 -m pip install --upgrade pytesseract
import pytesseract

pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'
from pytesseract import Output
import os
res = os.listdir(r'content\hero\18')
for image in res:
    if not (image.endswith('.jpg')) and not (image.endswith('.png')) and not (image.endswith('.jpeg')):
        continue
    image_path = 'content\\hero\\18\\' + image
    img = cv2.imread(image_path)

    d = pytesseract.image_to_data(img, output_type=Output.DICT, lang="eng", config="hocr")
    print(d)
    n_boxes = len(d['level'])
    for i in range(n_boxes):
        (x, y, w, h) = (d['left'][i], d['top'][i], d['width'][i], d['height'][i])
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, d['level'][i] * 50, 0), 2)



    #h, w, c = img.shape

    #boxes = pytesseract.image_to_boxes(img)
    #pytesseract.image_to_boxes(image, lang="eng", output_type=)



    cv2.imwrite('content\\hero\\18\\out\\' + image, img)
    #cv2.waitKey(0)