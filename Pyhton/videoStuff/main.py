from PIL import Image
import os
import glob

num_images = len(glob.glob('src/*.png'))

def color_dist(color1, color2):
    return abs(color1[0] - color2[0]) + abs(color1[1] - color2[1]) + abs(color1[2] - color2[2])

for i in range(1,1000 * 1000):
    path = 'src/out' + str(i) + '.png'
    if not os.path.isfile(path):
        break
    out_path = 'out/out' + str(i) + '.png'


# Detect single image


    im = Image.open(path)
    rgb_im = im.convert('RGB')
    width, height = im.size

    compress_r = 64
    compress_g = 32
    compress_b = 10

    gartic_colors = [
        (0,0,0),
        (102,102,102),
        (0,80,205),
        (255,255,255),
        (170,170,170),
        (38,201,201),
        (1,116,32),
        (153,0,0),
        (150,65,18),
        #(17,176,60),
        #(255,0,19),
        #(255,120,41),
        #(176,112,28),
        #(153,0,78),
        #(203,90,87),
        #(255,193,38),
        #(255,0,143),
        #(254,175,168),
        #(90,0,137),
        #(123,29,252)

    ]

    for x in range(width):
        for y in range(height):
            r, g, b = rgb_im.getpixel((x, y))

            dist = 1000
            selected_color = (r,g,b)
            for color in gartic_colors:
                d = color_dist( (r,g,b), color )
                if d < dist:
                    dist = d
                    selected_color = color

            #r = (int(r/compress_r) * compress_r)
            #g = (int(g/compress_g) * compress_g)
            #b = (int(b/compress_b) * compress_b)

            rgb_im.putpixel((x, y), selected_color)
    rgb_im.save(out_path, 'png')
    print(out_path)
    #rgb_im.save

