import pygame as pygame

from settings import *


from GameField import GameField

# Set up the drawing window
screen = pygame.display.set_mode([width, height])

# Run until the user asks to quit
running = True

GF = GameField()

flag = 0

while running:

    # Did the user click the window close button?



    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LSHIFT:
                flag += 0.1

            if event.key == pygame.K_LCTRL:
                flag -= 0.1

        if event.type == pygame.KEYUP:
            if event.key == pygame.K_LSHIFT:
                flag += -0.1

            if event.key == pygame.K_LCTRL:
                flag -= -0.1


    # Fill the background with white
    screen.fill((255, 255, 255))

    GF.update(ms_per_frame)
    GF.allowed_dist -= ms_per_frame * flag
    #print(GF.allowed_dist)
    GF.render(screen)

    #print()

    # Flip the display
    pygame.display.flip()
    pygame.time.wait(ms_per_frame)
# Done! Time to quit.
pygame.quit()