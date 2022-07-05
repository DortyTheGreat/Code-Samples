import math

import pygame

from settings import width,height

from BaseObjects.Vector2 import Vec

class DrawCircle:
    def __init__(self, pos, velocity, color = (0,0,255), value=100):
        self.value = value
        self.Velocity = velocity
        self.Acceleration = 0,0.003
        self.pos = pos
        self.radius = self.value ** 0.5
        self.color = color

        self.AirResistance = 0.3

    def update(self,dt):
        #self.value -= max(self.value * dt * 0.0003 * 0.2, 100 * dt * 0.0003 * 0.2)
        self.pos = self.pos[0] + self.Velocity[0]*dt, self.pos[1] + self.Velocity[1]*dt

        if self.value > 0:
            self.radius = self.value ** 0.5
        else:
            self.radius = 0

        # Collision Check


    def isWallCollide(self):
        if self.pos[0] < self.radius or self.pos[0] > width - self.radius:
            return True

        if self.pos[1] < self.radius or self.pos[1] > height - self.radius:
            return True

        if self.pos[0] < self.radius:
            return True

        if self.pos[0] > width - self.radius:
            return True

        return False






    def render(self,screen):
        pygame.draw.circle(screen, self.color, self.pos, self.radius)