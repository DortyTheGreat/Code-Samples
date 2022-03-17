from Bin.settings import *
GameIs='Running'
class Ball:
    global GameIs
    def __init__(self, pos):
        global GameIs
        self.image = pygame.image.load("Data/basketball.png")
        self.pos = list(pos)
        self.speed=[randint(50,100)/500 * StartBallSpeedMult * ((randint(0,1))*2-1), randint(50,100)/500 * (-1) * StartBallSpeedMult]
        self.width = self.image.get_rect().width
        self.height = self.image.get_rect().height
        self.rect=pygame.Rect((self.pos[0], self.pos[1], self.width, self.height))
        self.ConstOfBounce=500
        GameIs='Running'
    def collide_screen(self):
        global GameIs
        if self.pos[0] + self.width > WidthOfScreen:
            self.speed[0]*=(-1)
            self.pos[0] -= mult/5
        if self.pos[0] < 0:
            self.pos[0]+= mult/5
            self.speed[0] *= (-1)
        if self.pos[1] + self.height > HeightOfScreen:
            GameIs='Stopped'
        if self.pos[1] < 0:
            self.pos[1] += mult/5
            self.speed[1] *= (-1)
    def collides_with(self, other):
        x1 = self.pos[0]
        y1 = self.pos[1]
        x2 = other.pos[0]
        y2 = other.pos[1]
        dx = x2 - x1
        dy = y2 - y1
        dist = (dx ** 2 + dy ** 2)**0.5
        if dist < self.width:
            return True
        else:
            return False

    def bounce(self, other):
        # Выталкивание шаров друг из друга
        self.pos[0] +=((self.pos[0]-other.pos[0])/self.ConstOfBounce) * mult
        self.pos[1] += ((self.pos[1] - other.pos[1]) / self.ConstOfBounce) * mult
        #
        self.speed, other.speed = other.speed, self.speed
    def collides_with_rec(self, other):
        return pygame.sprite.collide_rect(self, other)
    def update(self):
        self.collide_screen()
        self.pos = [self.pos[0] + self.speed[0]*mult,self.pos[1] + self.speed[1]*mult]
        self.rect.x=self.pos[0]
        self.rect.y=self.pos[1]
    def render(self):
        screen.blit(self.image,self.pos)