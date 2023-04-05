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

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    ret, thresh1 = cv2.threshold(gray, 0, 255, cv2.THRESH_OTSU | cv2.THRESH_BINARY_INV)


    rect_kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (18, 18))


    dilation = cv2.dilate(thresh1, rect_kernel, iterations=1)


    contours, hierarchy = cv2.findContours(dilation, cv2.RETR_EXTERNAL,
                                           cv2.CHAIN_APPROX_NONE)
    im2 = img.copy()

    for cnt in contours:
        x, y, w, h = cv2.boundingRect(cnt)



        # Drawing a rectangle on copied image
        rect = cv2.rectangle(im2, (x, y), (x + w, y + h), (0, 255, 0), 2)
        # Cropping the text block for giving input to OCR
        cropped = im2[y:y + h, x:x + w]

        # Open the file in append mode
        file = open("recognized.txt", "a")

        # Apply OCR on the cropped image
        text = pytesseract.image_to_string(cropped)

        file.write(text)
        file.write("\n")

        # Appending the text into file
        print(text)








    cv2.imwrite('content\\hero\\18\\out\\' + image, im2)
    #cv2.waitKey(0)