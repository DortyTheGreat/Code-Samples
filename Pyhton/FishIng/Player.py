from BaseObjects.DrawableCircle import DrawCircle

from settings import pygame

class Player:
    def __init__(self):
        self.circle = DrawCircle(100,(100,100,100))

    def update(self,dt):
        self.circle.pos = (300,300)#pygame.mouse.get_pos()

    def render(self,screen):
        self.circle.render(screen)