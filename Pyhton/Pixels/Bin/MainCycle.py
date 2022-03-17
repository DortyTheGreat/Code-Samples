from Bin.Physics import *
from Bin.Init import *
def MainLoop():



    GameWasStopped_=0
    done=False
    GameIs='Running'
    TimeOfDeath=0
    amount=0
    StartTime=time.time()

    while not done:

       # print(GameIs, GameWasStopped_)

        #

        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                done = True
            if TurnAI == 0 or AmountOfBalls != 1:
                BigRectangle.control(e)

        #
        if not(TurnAI == 0 or AmountOfBalls != 1):
            BigRectangle.autocontrol(Balls[0].pos[0] + Balls[0].width/2, BigRectangle.pos[0] + BigRectangle.width/2)

        # Проверка На НеКонецИгры
        from Classes.Ball import GameIs
        if(GameIs == 'Stopped' and GameWasStopped_==0):
            for i in range(len(Balls)):
                Balls[i].speed[0]=0
                Balls[i].speed[1] = 0

            final_Time=str(round((time.time() - StartTime - 1), 1))
            LastScores.AddScore(final_Time)
            HighScores.AddScore(final_Time)
            HighScores.sort()
            #LastScores.sort()
            FinishText.update_text("Game Has been finished with the score: " + final_Time)
            GameWasStopped_=1
            FullRenderCycle()
            TimeOfDeath= (round((time.time() - StartTime - 1), 1))
        # Проверка На НеКонецИгры
        '''
        if GameWasStopped_== 1 :
            final_Time =  str((round( TimeOfDeath-(time.time() - StartTime - 1) + 5, 1)))
            if float(final_Time) <= 0:

                #Balls = []
                Balls.pop()
                done=True
                StartTime=time.time()

            RestartText.update_text("Game Will Restart in " +  final_Time +" seconds")
            FullRenderCycle()
         '''

        if(amount > fps and GameIs == 'Running'):
            FullRenderCycle()  # Отрисовка
            FullPhysCycle()  # Проверка Физики


        #Fps Writter
        amount+=1
        if ((time.time() - StartTime) / amount) != 0:
            ActualFPS = ((1 / ((time.time() - StartTime) / amount)))
        else:
            ActualFPS=fps
        decre = (1000/(ActualFPS) ) - (1000/fps)
        pygame.time.wait(int(1000/fps - fps*decre))
        if((amount%(fps*2)) == 0): print( 'fps =', round(ActualFPS,2) )
        #Fps Writter


