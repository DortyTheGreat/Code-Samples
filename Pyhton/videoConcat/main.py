# install by > python3 -m pip install --upgrade moviepy
from moviepy.editor import VideoFileClip
from moviepy.editor import concatenate_videoclips

def concatenate(video_clip_paths, output_path):
    """Concatenates several video files into one video file
    and save it to `output_path`. Note that extension (mp4, etc.) must be added to `output_path`
    `method` can be either 'compose' or 'reduce':
        `reduce`: Reduce the quality of the video to the lowest quality on the list of `video_clip_paths`.
        `compose`: type help(concatenate_videoclips) for the info"""
    # create VideoFileClip object for each video file
    clips = [VideoFileClip(c) for c in video_clip_paths]

    # concatenate the final video with the compose method provided by moviepy
    final_clip = concatenate_videoclips(clips, method="compose")
    # write the output video file
    final_clip.write_videofile(output_path)


from os import listdir
from os.path import isfile, join

mypath = "videos"

onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

onlyfiles_dirs = []

for file in onlyfiles:
    onlyfiles_dirs += [ mypath + '/' + file ]
print(onlyfiles_dirs)
concatenate(onlyfiles_dirs,"new.mp4")