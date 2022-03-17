
import pygame.draw

class Food:
    def __init__(self):
        self.pos = (500,500)
        self.storage = 15000
        self.radius = 50
        self.active = True
    def update(self,dt):
        self.storage += 0.2 * dt

        self.radius = self.storage ** 0.3
        if (self.storage < 0):
            self.active = False
            self.radius = 0

    def render(self,screen):
        if self.active:
            pygame.draw.circle(screen, (0, 255, 0), self.pos, self.radius)
