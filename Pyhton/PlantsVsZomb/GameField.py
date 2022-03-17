import random

from BaseObjects.DrawableCircle import DrawCircle

from Player import Player

from settings import pygame

from settings import width

from BaseObjects.Projectile import Projectile

from BaseObjects.Enemy import Zombie

from BaseObjects.Text import Text


class GameField:
    def __init__(self):
        self.fire_time = 0
        self.spawn_time = 0
        self.elapsed_time = 0


        self.Pla = Player()
        self.distancing = 0
        self.allowed_dist = 300

        self.projectiles = set()

        self.zombies = set()

        self.projectiles.add(Projectile(self.Pla.circle.pos, (0,-0.5), (250, 50, 50), 500 ))

        self.zombies.add(Zombie((200,0), (0, 0.2), (50, 250, 50), 500))

        self.timer = Text("abobus",200,50,40)

    def update(self,dt, controller):
        self.fire_time += dt
        self.elapsed_time += dt
        self.spawn_time += dt

        firerate = 50
        spawn_rate = 500

        self.timer.text = str(self.elapsed_time / 1000)

        if self.fire_time > firerate:
            self.fire_time -= firerate
            self.projectiles.add(Projectile(self.Pla.circle.pos, (0,-0.5), (250, 50, 50), 50 ))

        if self.spawn_time > spawn_rate:
            self.spawn_time -= spawn_rate
            self.zombies.add(Zombie((random.randint(50,width-50), 0), (0, 0.05), (50, 250, 50), 100))


        for zombie in self.zombies:
            for bullet in self.projectiles:
                bullet.collide(zombie)


        self.Pla.update(dt, controller)

        remove_zombies = set()

        for zombie in self.zombies:
            if (zombie.update(dt)):
                remove_zombies.add(zombie)

        for remove_ in remove_zombies:
            self.zombies.remove(remove_)

        remove_proj = set()

        for projec in self.projectiles:
            if (projec.update(dt)):
                remove_proj.add(projec)

        for remove in remove_proj:
            self.projectiles.remove(remove)

        print(len(remove_proj),len(self.projectiles))



    def render(self,screen):
        self.Pla.render(screen)
        self.timer.render(screen)
        for projec in self.projectiles:
            projec.render(screen)

        for zombie in self.zombies:
            zombie.render(screen)
