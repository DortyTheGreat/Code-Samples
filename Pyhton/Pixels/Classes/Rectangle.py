from Bin.settings import *
class Rectangle:
    def __init__(self, pos):
        self.image = pygame.image.load("Data/rectangle.jpg")
        self.pos = list(pos)
        self.acceleration=0
        self.RACOS=200 # self.ReversedAcceleratedConstantOfSpeed
        self.AbsSpeed=0.3*SpeedMultOfRect
        self.flag=0
        self.speed=0
        self.width = self.image.get_rect().width
        self.height = self.image.get_rect().height

        self.rect=pygame.Rect((self.pos[0], self.pos[1], self.width, self.height))

    def control(self, e):
        if e.type == pygame.KEYDOWN:
            if e.key == pygame.K_LEFT:
                self.flag += (-1)
            if e.key == pygame.K_RIGHT:
                self.flag += 1
        if e.type == pygame.KEYUP:
            if e.key == pygame.K_LEFT:
                self.flag -= (-1)
            if e.key == pygame.K_RIGHT:
                self.flag -= 1
    def autocontrol(self,XOfBall , XOfRect ):
        if(XOfBall > XOfRect):
            self.flag=1
        else:
            self.flag=-1




    def update(self):

        if MovementModeOfRect == 'Constant':
            self.speed=self.flag*self.AbsSpeed
        else:
            if EasierAccelerate:
                self.pos[0]+=self.flag*self.AbsSpeed*mult
            self.acceleration=self.flag*self.AbsSpeed

        self.speed+=self.acceleration*mult/self.RACOS
        self.pos[0]+=self.speed*mult

        if (self.pos[0] < 0):
            if MovementModeOfRect != 'Constant':
                self.speed*= (-1) * Slipperiness
            self.pos[0] = 0
        if(self.pos[0] + self.width > WidthOfScreen):
            if MovementModeOfRect != 'Constant':
                self.speed*= (-1)* Slipperiness
            self.pos[0] = WidthOfScreen - self.width

        self.rect.x=self.pos[0]
        self.rect.y=self.pos[1]

    def render(self): screen.blit(self.image,self.pos)