import pygame
from random import randint
#
TurnAI=1  # Works only if there is 1 Ball
StartBallSpeedMult=1  # 1
SpeedMultOfRect=2  # 1
AmountOfBalls=5  # 1
HeightOfScreen=800  # 600
WidthOfScreen=800  # 800
MovementModeOfRect ='Constant' # Constan (Not Constant)
fps=60  # 60
mult=1400/fps
MultiplierOfSpeed=1.05
Slipperiness=0.5  # from 0 to 1, 0.5
EasierAccelerate=False
#

pygame.init()
display = pygame.display.set_mode((WidthOfScreen, HeightOfScreen))
screen = pygame.display.get_surface()
def Change():
    pygame.init()
    display = pygame.display.set_mode((WidthOfScreen, HeightOfScreen))
    screen = pygame.display.get_surface()