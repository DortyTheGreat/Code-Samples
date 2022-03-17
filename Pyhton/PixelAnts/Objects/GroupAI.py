import random


class AI:
    def __init__(self, destinations,target):
        self.destinations = destinations
        self.target = target
        # {'home' : 123, 'food' : 12}
    def collided(self, obj):
        self.destinations[obj] = 0
        if obj == self.target: # следует ли развернуться
            list_ = list(self.destinations.keys())
            list_.pop(list_.index(obj))
            self.target = random.choice(list_)
            #print('new target', self.target, list_ )
            return True
        return False

    def listen(self, info, distance):
        flag = False
        for obj in info:
            if ( info[obj]+distance < self.destinations[obj] ):
                self.destinations[obj] = info[obj]
                if obj == self.target:
                    flag = True
        return flag

    def move(self,distance):
        for obj in self.destinations:
            self.destinations[obj]+= distance