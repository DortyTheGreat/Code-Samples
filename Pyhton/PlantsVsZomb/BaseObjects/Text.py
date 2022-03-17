import pygame as pg
#from settings import screen

class Text:
    def __init__(self, text, x, y, size=24):
        self.text = text
        self.x = x
        self.y = y
        self.size = size

    def render(self, screen):
        font = pg.font.SysFont('jetbrainsmonomediumttf', self.size)
        textsurface = font.render(self.text, True, (0, 0, 0))
        screen.blit(textsurface, (self.x, self.y))