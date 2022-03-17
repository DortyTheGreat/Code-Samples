class Vec:
    def __init__(self, _x=0, _y=0):
        self.x = _x
        self.y = _y

    def add(self, vec2):
        self.x += vec2.x
        self.y += vec2.y
        return self

    def div(self, n):
        self.x /= n
        self.y /= n
        return self