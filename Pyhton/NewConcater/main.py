# install by > python3 -m pip install --upgrade ffmpeg-python
from moviepy.editor import VideoFileClip
from moviepy.editor import concatenate_videoclips
import ffmpeg




'''
Как использовать?
1) Закинуть видосы в videos/
2) Настроить параметры 
3) Запустить
4) Ждать
5) Успех
'''

MIN_DURATION = 5 # Если видео слишком короткое, то оно не добавляетсяв итоговое. Ex: 5 seconds

MAX_ONE_VIDEO_DURAION = 300 # Если итоговое видео слишком длинное, то оно разделится на несколько поменьше,
# длиной примерно в указанное. Ex: 300 seconds = 5 minutes


def concatenate(video_clip_paths):

    clips = []
    number_of_clips = 0
    input_clips = 0
    duration = 0
    compiled_number = 0

    for c in video_clip_paths:

        input_clips += 1
        print('memory stuff', input_clips, 'out of', len(video_clip_paths), 'clips:', number_of_clips, 'total duration:', duration)
        new_clip = VideoFileClip(c)
        if new_clip.duration >= MIN_DURATION:
            clips.append(c) #
            duration += new_clip.duration
            number_of_clips += 1

        if duration >= MAX_ONE_VIDEO_DURAION:
            compiled_number += 1
            duration = 0
            number_of_clips = 0





            output_path = "new" + str(compiled_number) + ".mp4"



            open('concat'+ str(compiled_number)+ '.txt', 'w').writelines([('file %s\n' % input_path) for input_path in clips])
            #ffmpeg.input('concat.txt', format='concat', safe=0).output(output_path, c='copy').run()

            clips = []









from os import listdir
from os.path import isfile, join

mypath = "videos"

onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

onlyfiles_dirs = []

for file in onlyfiles:
    onlyfiles_dirs += [ mypath + '/' + file ]
print(onlyfiles_dirs)
concatenate(onlyfiles_dirs)