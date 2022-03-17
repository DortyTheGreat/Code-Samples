import math

import pygame

from settings import width,height

from BaseObjects.Vector2 import Vec

class DrawCircle:
    def __init__(self, value, color = (0,0,255)):
        self.value = value
        self.Velocity = 0,0
        self.Acceleration = 0,0.003
        self.ExtraForces = 0,0
        self.pos = 300,0
        self.radius = self.value ** 0.5
        self.color = color

        self.AirResistance = 1.0 # No resistance

    def update(self,dt):
        #self.value -= max(self.value * dt * 0.0003 * 0.2, 100 * dt * 0.0003 * 0.2)

        self.Velocity = self.Velocity[0] + (self.Acceleration[0]+self.ExtraForces[0]) * dt * 0.5, self.Velocity[1] + (self.Acceleration[1]+self.ExtraForces[1]) * dt * 0.5

        self.pos = self.pos[0] + self.Velocity[0]*dt, self.pos[1] + self.Velocity[1]*dt

        self.Velocity = self.Velocity[0] + (self.Acceleration[0]+self.ExtraForces[0]) * dt * 0.5, self.Velocity[1] + (self.Acceleration[1]+self.ExtraForces[1]) * dt * 0.5

        delta = self.AirResistance ** (dt/1000) # замедление в секунду

        self.Velocity = self.Velocity[0]*delta, self.Velocity[1]*delta



        if self.value > 0:
            self.radius = self.value ** 0.5
        else:
            self.radius = 0

        # Collision Check
        '''
        if self.pos[0] < self.radius or self.pos[0] > width - self.radius:
            self.Velocity = self.Velocity[0]*(-1),self.Velocity[1]

        if self.pos[1] < self.radius or self.pos[1] > height - self.radius:
            self.Velocity = self.Velocity[0],self.Velocity[1]*(-1)

        if self.pos[0] < self.radius:
            deltaX = self.radius - self.pos[0]
            self.pos = self.pos[0] + 2 * deltaX,self.pos[1]

        if self.pos[0] > width - self.radius:
            #print('piska')
            deltaX = self.pos[0] + self.radius - width
            self.pos = self.pos[0] - 2 * deltaX,self.pos[1]
        '''

    def eat(self,another):
        if self.value * 0.5 > another.value:
            self.value += another.value
            another.value = 0
            return True
        return False


    def render(self,screen):
        pygame.draw.circle(screen, self.color, self.pos, self.radius)