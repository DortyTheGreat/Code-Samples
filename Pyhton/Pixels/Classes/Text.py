from Bin.settings import *
class DrawableObject():
    def __init__(self):
        self.rect = pygame.rect.Rect(0, 0, 0, 0)

    def move(self, x, y):
        self.rect.x = x
        self.rect.y = y

    def move_center(self, x, y):
        self.rect.centerx = x
        self.rect.centery = y

class TextObject(DrawableObject):

    def __init__(self, x, y, text, color):
        super().__init__()
        self.color = color
        self.y = y
        self.x = x

        self.font = pygame.font.SysFont('Comic Sans MS', 20, True)
        self.update_text(text)

    def update_text(self, text):
        self.text = text
        self.surface = self.font.render(self.text, True, self.color)
        self.rect = self.surface.get_rect()
        self.move_center(self.x, self.y)

    def render(self):
        screen.blit(self.surface, [self.rect.x,self.rect.y])