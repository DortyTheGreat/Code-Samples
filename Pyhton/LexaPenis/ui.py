import time

import pygame as pg
from settings import screen, white, size


def render_text(text, x, y, font_size=24, center=True):
    font = pg.font.SysFont('jetbrainsmonomediumttf', font_size)
    text = font.render(text, True, white)
    if center:
        text_rect = text.get_rect(center=(x, y))
        screen.blit(text, text_rect)
    else:
        screen.blit(text, (x, y))

def ui(**args):
    fps_text = str(int(1 / (time.time() - args['fps'])))
    render_text(fps_text, 0, 0, 16, False)

    score_text = str(int(time.time() - args['start']))
    render_text(score_text, size[0] / 2, size[1] / 2)
