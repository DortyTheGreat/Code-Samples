from BaseObjects.DrawableCircle import DrawCircle


from settings import pygame

class Player:
    def __init__(self):
        self.circle = DrawCircle( (200,300), (0,0), (100, 100, 100))


    def update(self,dt, controler):

        AirResistance = 0.3

        delta = AirResistance ** (dt/1000) # замедление в секунду

        self.circle.Velocity = (self.circle.Velocity[0]+controler[0]) * delta, (self.circle.Velocity[1]+controler[1])*delta
        self.circle.update(dt)
        print(self.circle.pos)
        #self.circle.pos = pygame.mouse.get_pos()


    def render(self,screen):
        self.circle.render(screen)
