import math

import pygame

from settings import width,height

from BaseObjects.Vector2 import Vec

from BaseObjects.DrawableCircle import DrawCircle

def dist(obj1,obj2):
    return ((obj1.pos[0]-obj2.pos[0])**2 +  (obj1.pos[1]-obj2.pos[1])**2)**0.5

class Projectile(DrawCircle):
    def __init__(self, pos, velocity, color = (0,0,255), value=100):
        self.pierce = 4 # Может пробить одну цель

        self.targering = "auto"
        self.target = "none" # (x,y) - Vector

        DrawCircle.__init__(self,pos,velocity,color,value)


    def update(self,dt):
        DrawCircle.update(self,dt)
        return (DrawCircle.isWallCollide(self) or (self.pierce==0))
        # Collision Check

    # Коллизия с Зомби
    def collide(self, zombie):



        if self.pierce == 0:
            #Обработка "удаления" пули
            return False

        if dist(self,zombie) > self.radius + zombie.radius:
            return False

        zombie.value -= self.value
        self.pierce -= 1
        return True

    def render(self,screen):
        DrawCircle.render(self,screen)