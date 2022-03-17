import math
from random import choice, randint

from pygame import gfxdraw

from settings import screen, size, white
from vec import Vec


class Ball:
    def __init__(self, x, y):
        self.posX = x
        self.posY = y

        self.mass = 10
        self.radius = 20

        x_speed = choice([randint(-7, -5), randint(5, 7)])
        self.velocity = Vec(x_speed, -8)
        self.acceleration = Vec(0, 0)

        self.allForces = Vec(0, 0)

    def update(self):
        # ВКЛЮЧАЕТ ГРАВИТАЦИЮ
        # self.gravity()

        self.acceleration = self.allForces.div(self.mass)
        self.velocity.add(self.acceleration)

        # ВКЛЮЧАЕТ ЗАМЕДЛЕНИЕ ВО ВРЕМЯ ДВИЖЕНИЯ
        # self.velocity.div(1.015)

        self.posX += self.velocity.x
        self.posY += self.velocity.y
        self.checkForEdgesCollisions()

    def gravity(self):
        G = 0.2
        gravitationalForce = Vec(0, G * self.mass)
        self.allForces.add(gravitationalForce)

    def checkForEdgesCollisions(self):
        if self.posY + self.radius > size[1]:
            self.velocity.y *= -1
            self.posY = size[1] - self.radius
            self.velocity.div(1.1)

        if self.posY - self.radius < 0:
            self.velocity.y *= -1
            self.posY = self.radius
            # self.velocity.div(1.1)

        if self.posX + self.radius > size[0]:
            self.velocity.x *= -1
            self.posX = size[0] - self.radius
            # self.velocity.div(1.1)

        if self.posX - self.radius < 0:
            self.velocity.x *= -1
            self.posX = self.radius
            # self.velocity.div(1.1)

    def checkBallsCollision(self, ball):
        def rotate(x, y, sin, cos, reverse):
            if reverse:
                return Vec(x * cos + y * sin, y * cos - x * sin)
            return Vec(x * cos - y * sin, y * cos + x * sin)

        x1 = self.posX
        y1 = self.posY
        x2 = ball.posX
        y2 = ball.posY
        dx = x2 - x1
        dy = y2 - y1
        dist = math.sqrt(dx ** 2 + dy ** 2)
        if dist < 2 * self.radius:
            angle = math.atan2(dy, dx)
            sin = math.sin(angle)
            cos = math.cos(angle)
            pos0 = Vec(0, 0)
            pos1 = rotate(dx, dy, sin, cos, True)

            vel0 = rotate(self.velocity.x, self.velocity.y, sin, cos, True)
            vel1 = rotate(ball.velocity.x, ball.velocity.y, sin, cos, True)

            vxTotal = vel0.x - vel1.x

            vel0.x = ((self.mass - ball.mass) * vel0.x + 2 *
                      ball.mass * vel1.x) / (self.mass + ball.mass)
            vel1.x = vxTotal + vel0.x

            absV = abs(vel0.x) + abs(vel1.x)
            # self.radius + ball1.radius == 100
            overlap = 2 * self.radius - abs(pos0.x - pos1.x)
            pos0.x += vel0.x / absV * overlap
            pos1.x += vel1.x / absV * overlap

            pos0F = rotate(pos0.x, pos0.y, sin, cos, False)
            pos1F = rotate(pos1.x, pos1.y, sin, cos, False)

            ball0x = self.posX
            ball0y = self.posY

            ball.posX = ball0x + pos1F.x
            ball.posY = ball0y + pos1F.y
            self.posX = ball0x + pos0F.x
            self.posY = ball0y + pos0F.y

            vel0F = rotate(vel0.x, vel0.y, sin, cos, False)
            vel1F = rotate(vel1.x, vel1.y, sin, cos, False)
            self.velocity.x = vel0F.x
            self.velocity.y = vel0F.y
            ball.velocity.x = vel1F.x
            ball.velocity.y = vel1F.y

    def checkPlatformCollision(self, plat):
        def clamp(val, ma, mi):
            return max(min(val, ma), mi)

        left = plat.posX
        top = plat.posY
        right = left + plat.width
        bottom = top + plat.height
        closestX = clamp(self.posX, right, left)
        closestY = clamp(self.posY, bottom, top)
        distanceX = self.posX - closestX
        distanceY = self.posY - closestY
        distanceSquared = (distanceX * distanceX) + (distanceY * distanceY)
        if distanceSquared <= (self.radius ** 2) and self.posY < top:
            self.velocity.y = -abs(self.velocity.y * 1.005)

    def isEndGame(self):
        return self.posY - self.radius > size[1]

    def render(self):
        ''' basketball.png
        texture = pg.image.load("assets/basketball.png")
        ballrect = texture.get_rect()

        ballrect.x = int(self.posX)
        ballrect.y = int(self.posY)

        screen.blit(texture, ballrect)
        '''
        x, y = (int(self.posX), int(self.posY))
        # center = (x, y)
        # pg.draw.circle(screen, white, center, self.radius)
        gfxdraw.aacircle(screen, x, y, self.radius, white)
        gfxdraw.filled_circle(screen, x, y, self.radius, white)
