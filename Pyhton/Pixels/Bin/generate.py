import random
from Classes.Rectangle import *
from Classes.Ball import *
from Classes.Scores import *
from Classes.Text import *



LastScores = Scores('Data/LastScores.txt')
HighScores = Scores('Data/HighScores.txt')

TimeText = TextObject(WidthOfScreen/2, 10, "hui morzeviq", (255, 255, 255))
FinishText = TextObject(WidthOfScreen/2, HeightOfScreen/3, '', (255, 255, 255))
RestartText = TextObject(WidthOfScreen/2, HeightOfScreen/3+50, '', (255, 255, 255))
CommentTextOfLasts = TextObject(WidthOfScreen-100, 50, 'Last 5 Scores:', (255, 255, 255))
CommentTextOfHighs = TextObject(100, 50, '5 Highest Scores:', (255, 255, 255))

HighScoresText =  []
LastScoresText = []
Balls = []
for i in range(len(LastScores.DATA)):
    LastScoresText.append(TextObject(WidthOfScreen-100, 80 + i * 20, LastScores.GetStr(i), (255, 255, 255)))
for i in range(len(HighScores.DATA)):
    HighScoresText.append(TextObject(100, 80 + i * 20, HighScores.GetStr(i), (255, 255, 255)))

BigRectangle=Rectangle([100,590])
BigRectangle.pos[1]=HeightOfScreen-BigRectangle.height
def Generator():
    for i in range(AmountOfBalls):
        Balls.append(Ball((random.randint(WidthOfScreen/20, WidthOfScreen-100), random.randint(0, HeightOfScreen/2))))
    print(Balls)

    return Balls
