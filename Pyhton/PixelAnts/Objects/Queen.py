import random

import pygame.draw

from Objects.Ant import Ant

class Queen:
    def __init__(self,amount):
        self.Ants = []
        self.pos = 300,300
        self.size = 30
        self.radius = 30
        self.storage = 3000
        for i in range(amount):
            #print((self.pos[0] + random.uniform(-self.size,self.size), self.pos[1] + random.uniform(-self.size,self.size)))
            self.Ants.append(Ant((self.pos[0] + random.uniform(-self.size,self.size), self.pos[1] + random.uniform(-self.size,self.size)), random.uniform(-3.14,3.14)))

    def update(self,dt):
        self.storage -= dt * 0.1
        self.radius = self.storage ** 0.3
        for Ant in self.Ants:
            Ant.update(dt)

    def render(self,screen):
        pygame.draw.circle(screen, (0, 0, 0), self.pos, self.radius)
        for Ant in self.Ants:
            Ant.render(screen)
