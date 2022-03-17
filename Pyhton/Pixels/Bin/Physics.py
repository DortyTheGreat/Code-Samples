from Bin.generate import *


def check_ball_intercollisions():
    for i in range(len(Balls) -1):
        for j in range(i + 1, len(Balls)):
            if Balls[i].collides_with(Balls[j]):
                Balls[i].bounce(Balls[j])

def check_ball_with_Rec_coll():
    for i in range(len(Balls)):
        if(Balls[i].collides_with_rec(BigRectangle)):
            Balls[i].speed[1]*= (-1)

            #Balls[i].pos[1]-=mult/20
            Balls[i].pos[1] -= ((Balls[i].pos[1] + Balls[i].height) - HeightOfScreen + BigRectangle.height)
            Balls[i].speed[1]*=MultiplierOfSpeed
            Balls[i].speed[0]*=MultiplierOfSpeed


def FullPhysCycle():
    check_ball_intercollisions()
    check_ball_with_Rec_coll()

    for Ball in Balls:
        Ball.update()
    BigRectangle.update()