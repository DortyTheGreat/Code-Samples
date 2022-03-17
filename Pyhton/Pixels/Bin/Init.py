from Bin.generate import *
import time
from Bin.generate import *
StartTime = time.time()
GameWasStopped = 0
done = False



def FullRenderCycle():
    screen.fill((0, 100, 100))
    for Ball in Balls:
        Ball.render()
    FinishText.render()
    RestartText.render()
    BigRectangle.render()
    TimeText.update_text('The Time Spent is: ' + str(round((time.time() - StartTime - 1), 1)))
    TimeText.render()
    CommentTextOfLasts.render()
    CommentTextOfHighs.render()
    for i in range(min(5,len(LastScores.DATA))): LastScoresText[i].render()
    for i in range(min(5, len(HighScores.DATA))): HighScoresText[i].render()
    pygame.display.flip()
