import math
import random

from Objects.Food import Food

from Objects.GroupAI import AI



def getRotation(X,Y):
    PI = 3.14
    if Y == 0:
        if X >= 0:
            return 0
        else:
            return PI

    if(Y < 0 ):
        return PI * 3/2 - math.atan( X / Y )
    else:
        return PI/2 - math.atan( X / Y )







class Ant:
    def __init__(self, pos, Angle):
        self.Velocity = 0.1
        self.Angle = Angle
        self.pos = pos
        self.storage = 0 # max = 255
        self.AI = AI({'home' : 0, 'food' : 10000}, 'food')


    def update(self,dt):

        self.AI.move(self.Velocity * dt)

        self.pos = self.pos[0]+self.Velocity*math.cos(self.Angle)*dt, self.pos[1]+self.Velocity*math.sin(self.Angle)*dt
        #self.Angle += dt * random.uniform(-0.01,0.01)

    def rotate(self, pos):
        #Поворачивает к заданой точке
        rel_pos = pos[0] - self.pos[0],pos[1] - self.pos[1]
        #print('Old Angle', self.Angle, angle_between((0,1),rel_pos))
        self.Angle = getRotation(rel_pos[0],rel_pos[1])

    def render(self, screen):
        #screen.blit(self.pos)
        screen.set_at((int(self.pos[0]),int(self.pos[1])) , (255, self.storage, 0))
