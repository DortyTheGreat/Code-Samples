ffmpeg -i video.mp4 -vn -acodec copy output-audio.aac
ffmpeg -i video.mp4 -vsync 0 src/out%d.png
