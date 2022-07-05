import math

import pygame

from settings import width,height

from BaseObjects.Vector2 import Vec

from BaseObjects.DrawableCircle import DrawCircle

class Zombie(DrawCircle):

    def __init__(self, pos, velocity, color=(0, 0, 255), value=100):

        DrawCircle.__init__(self, pos, velocity, color, value)

    def update(self,dt):
        DrawCircle.update(self,dt)
        return  self.value <= 0
        # Collision Check

    def render(self,screen):
        DrawCircle.render(self,screen)