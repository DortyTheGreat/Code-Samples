import pygame
from Objects.GameField import *

width = 800
height = 800

fps = 120
ms_per_tick = int(1000/fps)

pygame.init()
display = pygame.display.set_mode((800, 800))
screen = pygame.display.get_surface()

def mainLoop():
    done = False

    GF = GameField()

    while not done:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                done = True
            #if TurnAI == 0 or AmountOfBalls != 1:
            #    BigRectangle.control(e)

        screen.fill((0, 100, 100))

        GF.update(ms_per_tick)

        GF.render(screen)
        pygame.display.flip()

        pygame.time.wait(ms_per_tick)

mainLoop()