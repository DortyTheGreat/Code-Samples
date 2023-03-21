
from PIL import Image
import os
import glob

num_images = len(glob.glob('src/*.png'))

#bar = Bar('Censoring...', max=num_images)

for filename in os.listdir('src'):
    if not(filename.endswith('.png')):
        continue

# Detect single image
    true_f_nane = 'src/' + filename
    true_f_nane2 = 'new_content/' + filename

    im = Image.open(true_f_nane)
    rgb_im = im.convert('RGB')
    width, height = im.size

    compress_r = 64
    compress_g = 32
    compress_b = 10
    for x in range(width):
        for y in range(height):
            r, g, b = rgb_im.getpixel((x, y))

            r = (int(r/compress_r) * compress_r)
            g = (int(g/compress_g) * compress_g)
            b = (int(b/compress_b) * compress_b)

            rgb_im.putpixel((x, y), (r, g, b))
    rgb_im.save(true_f_nane2, 'png')
    print(true_f_nane)
    #rgb_im.save

    print(r, g, b)
    (65, 100, 137)
