import time
from random import randint

import pygame as pg

from ball import Ball
from pgplatform import Platform
from settings import *
from ui import ui


def main():
    pg.init()
    game_over = False

    balls = []
    AMOUNT = 5
    for i in range(AMOUNT):
        ball = Ball(randint(0, size[0] - 40), randint(0, size[1] - 40))
        balls.append(ball)
    platform = Platform()

    fps_tester = 0
    startTime = time.time()
    while not game_over:
        ui(fps=fps_tester, start=startTime)
        fps_tester = time.time()
        for event in pg.event.get():
            if event.type == pg.QUIT:
                game_over = True
            platform.control(event)

        for ball in balls:
            ball.update()

        for i in range(AMOUNT):
            for j in range(i + 1, AMOUNT):
                balls[i].checkBallsCollision(balls[j])
            balls[i].render()
            balls[i].checkPlatformCollision(platform)

        platform.update_and_render()

        pg.display.flip()
        screen.fill(black)
        pg.time.wait(20)
    exit()
