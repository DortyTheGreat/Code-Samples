from BaseObjects.DrawableCircle import DrawCircle

from Player import Player

from settings import pygame



def dist(obj1,obj2):
    return ((obj1.pos[0]-obj2.pos[0])**2 +  (obj1.pos[1]-obj2.pos[1])**2)**0.5


class GameField:
    def __init__(self):
        self.Dr = []
        self.Dr.append(DrawCircle(1000))
        self.time = 0
        self.Pla = Player()
        self.distancing = 0
        self.allowed_dist = 300

        self.nu = 0.3
        self.k = 1
        self.F = [0, 0]
        self.mass = 5

    def update(self,dt):
        #a = []


        K = 0.000001



        self.Pla.update(dt)
        dist_ = dist(self.Pla.circle, self.Dr[0])

        delta_dist = (dist_ - self.allowed_dist)

        g = self.Dr[0].Acceleration[1]
        Ek = (self.Dr[0].Velocity[0] ** 2 + self.Dr[0].Velocity[1] ** 2) / 2
        Ep = (-1) * self.Dr[0].pos[1] * g
        Eprugina= 0


        if delta_dist > 0:

            Eprugina = K * delta_dist**2 / 2

            mult = (delta_dist / dist_ ) * K

            dx = self.Pla.circle.pos[0] - self.Dr[0].pos[0]
            dy = self.Pla.circle.pos[1] - self.Dr[0].pos[1]

            self.distancing = min((dist_ - self.allowed_dist),200)

            self.Dr[0].ExtraForces = dx*mult*dt, dy*mult*dt

        else:
            self.Dr[0].ExtraForces = 0,0

        print(Ek,Ep,Eprugina,Ek+Ep+Eprugina)



        for Dc in self.Dr:
            Dc.update(dt)



    def render(self,screen):
        for Dc in self.Dr:
            Dc.render(screen)
        self.Pla.render(screen)

        pygame.draw.line(screen, (self.distancing,100,0), self.Pla.circle.pos,self.Dr[0].pos, 5 )