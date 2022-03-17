
from Objects.Queen import Queen
from Objects.Food import Food

def dist(a,b):
    return ((a[0]-b[0])**2 + (a[1] - b[1])**2)**0.5

class GameField:

    def __init__(self):

        self.first_queen = Queen(2000)
        self.ff = Food()

    # Муравей кричит
    def shout(self,Ant,distance):
        for Ant2 in self.first_queen.Ants:

            if dist(Ant2.pos, Ant.pos) < distance:
                if (Ant2.AI.listen(Ant.AI.destinations, 50)):
                    # Надо повернуть к нему
                    #self.shout(Ant2,distance)
                    Ant2.rotate(Ant.pos)



    def update(self,dt):

        home = 0

        food = 0




        self.first_queen.update(dt)


        for Ant in self.first_queen.Ants:

            if (Ant.AI.target == 'food'):
                food += 1
            if Ant.AI.target == 'home':
                home += 1

            collided = False
            if (dist(self.ff.pos,Ant.pos) < self.ff.radius) and self.ff.active:

                take = min(255-Ant.storage,self.ff.storage)

                self.ff.storage -= take
                Ant.storage += take

                if Ant.AI.collided('food'):
                    collided = True
                    Ant.Angle += 3.14

            if dist(self.first_queen.pos,Ant.pos) < self.first_queen.radius:

                if Ant.AI.collided('home'):
                    collided = True
                    Ant.Angle += 3.14
                    self.first_queen.storage += Ant.storage
                    Ant.storage = 0

            if collided:
                self.shout(Ant,30000)

            # Кричим всем, кто в радиусе
        print(home,food)

        self.ff.update(dt)




    def render(self,screen):
        self.first_queen.render(screen)
        self.ff.render(screen)


