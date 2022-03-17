import pygame as pg

from settings import screen, size


class Platform():
    def __init__(self, x=size[0] / 2, y=size[1] - 15):
        self.posX = x
        self.posY = y
        self.width = 400
        self.height = 10
        self.acceleration = 0

    def control(self, e):
        if e.type == pg.KEYDOWN:
            if e.key == pg.K_LEFT:
                self.acceleration += -10
            if e.key == pg.K_RIGHT:
                self.acceleration += 10
        if e.type == pg.KEYUP:
            if e.key == pg.K_LEFT:
                self.acceleration -= -10
            if e.key == pg.K_RIGHT:
                self.acceleration -= 10

    def update_and_render(self):
        self.posX += self.acceleration

        positiong = (self.posX, self.posY, self.width, self.height)
        pg.draw.rect(screen, (255, 255, 255), positiong)
