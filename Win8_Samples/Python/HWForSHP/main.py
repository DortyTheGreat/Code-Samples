#Made By Dorty(aka Tesla) at 06.05.2021 for Hero's Quest
#Version 11 (07.05.2021 html port (4th))

import math

def Clamp(value, min, max):

    if(value > max): return int(max)
    if(value < min): return int(min)
    return int(value)

def GetScalledValue(
value, # Base value
targetLevel, # Mob level
perLevel, # Stat per level
isBoss
):
    level1 = 1500
    level2 = 2000
    level3 = 30000
    level4 = 50000
    level5 = 120000

    x1 = Clamp(targetLevel, 0, level1)

    x2 = Clamp(targetLevel - x1, 0, level2)

    x3 = Clamp(targetLevel - x1 - x2, 0, level3)

    x4 = Clamp(targetLevel - x1 - x2 - x3, 0, level4)

    x5 = Clamp(targetLevel - x1 - x2 - x3 - x4, 0, level5)

    x6 = Clamp(targetLevel - x1 - x2 - x3 - x4 - x5, 0, targetLevel)


    multi = 0.75

    multi += x1 * 0.00195
    multi += x2 * 0.0024025

    multi += x3 * 0.00275

    multi += x4 * 0.00315

    multi += x5 * 0.0037

    multi += x6 * 0.0042


    levelBase = int(targetLevel ** 1.05)
    extraMulti = 1 + (max(0, (targetLevel / 10000) - 2) * 0.125)
    bonus = int(perLevel)
    if isBoss:
        bonus = int(perLevel*1.45)


    totalValue = int(value + levelBase * bonus) * multi * extraMulti

    return (totalValue)

class Hero:
    def __init__(self):
        self.HP = 100
        self.Damage = 50
        self.Defence = 50
        self.AttackSpeed = 1

    def Read_Data(self):
        self.HP = int(input("Input Your Health: \n>>>"))
        self.Damage = int(input("\nInput Your Attack Damage: \n>>>"))

        TopDefense = int(input("\nInput Your TOP Defense: \n>>>"))
        BasicDefense = int(input("\nInput Your BASIC Defense: \n>>>"))

        self.Defence = (TopDefense - BasicDefense) * 3 + BasicDefense

        self.HP = self.HP + TopDefense / 2  # Includes the shield

        self.AttackSpeed = float(input("\nInput Your AttackSpeed(1.1 for example): \n>>>"))



class Mob:

    def Get_Enemy_Health(self):
        return int(GetScalledValue(300, self.level, 60, self.isBoss) * 2)

    def Get_Enemy_DMG(self):
        return int(GetScalledValue(160, self.level, 12, self.isBoss))

    def Get_Enemy_DEF(self):
        return int(GetScalledValue(50, self.level, 8, self.isBoss))

    def __init__(self, lvl, isBoss_ = False):
        self.level = lvl
        self.isBoss = isBoss_
        self.Damage = self.Get_Enemy_DMG()
        self.HP = self.Get_Enemy_Health()
        self.Defence = self.Get_Enemy_DEF()
    def GetDMG(self,damage):    


def Get_Boss_Health(level,isBoss):
    return int(GetScalledValue(1000,level,60,isBoss) * 2)

def Get_Boss_DMG(level,isBoss):
    return int(GetScalledValue(300,level,12,isBoss))

def Get_Boss_DEF(level,isBoss):
    return int(GetScalledValue(200,level,8,isBoss))




#def Get_Enemy_DMG(level):
 #   return level*15

def dmg_mult_to_hero(defense, damage):
    return damage/(damage + defense*2.5)

def dmg_mult_to_enemy(defense, damage):
    return damage/(damage + defense*1.75)

def dmg_to_hero_per_hit(defense, damage):
    return  (damage* dmg_mult_to_hero(defense,damage))

def dmg_to_enemy_per_hit(defense, damage):
    return  (damage* dmg_mult_to_enemy(defense,damage))

def calculateHitsTillDeath(health, defense, damage):
    return  health/(dmg_to_hero_per_hit(defense,damage))

def RECEIVED_DMG(Opponentlevel, OurDefense,isBoss):
    return int(dmg_to_hero_per_hit(OurDefense,int(Get_Enemy_DMG(Opponentlevel,isBoss))))

def DEALT_DMG(Opponentlevel, OurAttack,isBoss):
    return int(dmg_to_enemy_per_hit(int(Get_Enemy_DEF(Opponentlevel,isBoss)),OurAttack))


def GetActualDamage(damage, defense):
    return ( damage*damage/(damage + defense*2.5) )


print(RECEIVED_DMG(54,3450,False))

print(GetActualDamage(Get_Enemy_DMG(55,False),250)) # waiting for 80

print(Get_Enemy_Health(58,False))

print(DEALT_DMG(58,2050,False))

f = open("demofile.txt", "w")

def RePrint(data):
    print(data)
    f.write(data + "\n")

def CanIKillThisGuy(enemy_lvl, isBoss):

    Hits = math.ceil(calculateHitsTillDeath(NewHP, NewDefense, Get_Enemy_DMG(enemy_lvl,isBoss)))
    Opponent_Health = Get_Enemy_Health(enemy_lvl,isBoss)
    damagePerMyHit = int(dmg_to_enemy_per_hit(Get_Enemy_DEF(enemy_lvl,isBoss), NewDamage))
    DamageDealt = Hits * damagePerMyHit * AttackSpeed

    #print(enemy_lvl, "- This Level")
    print("dmg_to_hero_per_hit=", dmg_to_hero_per_hit(NewDefense, Get_Enemy_DMG(enemy_lvl,isBoss)))
    #print("Hits = ", Hits)
    print("Opponent_Health=", Opponent_Health)
    print("DMGmy=", damagePerMyHit)



    if ((DamageDealt < Opponent_Health)):
        print("[" + str(enemy_lvl) + "]NO")
        return False
    else:
        print("[" + str(enemy_lvl) + "]YES")
        return True

def CanIKillThisBoss(enemy_lvl, isBoss):

    Hits = math.ceil(calculateHitsTillDeath(NewHP, NewDefense, Get_Boss_DMG(enemy_lvl,isBoss)))
    Opponent_Health = Get_Boss_Health(enemy_lvl,isBoss)
    damagePerMyHit = int(dmg_to_enemy_per_hit(Get_Boss_DEF(enemy_lvl,isBoss), NewDamage))
    DamageDealt = Hits * damagePerMyHit * AttackSpeed

    #print(enemy_lvl, "- This Level")

    print("Boss DMG = ", Get_Boss_DMG(enemy_lvl,isBoss))
    print("Boss DEF = ", Get_Boss_DEF(enemy_lvl, isBoss))

    print("dmg_to_hero_per_hit=", dmg_to_hero_per_hit(NewDefense, Get_Boss_DMG(enemy_lvl,isBoss)))
    #print("Hits = ", Hits)
    print("Opponent_Health=", Opponent_Health)
    print("DMGmy=", damagePerMyHit)



    if ((DamageDealt < Opponent_Health)):
        print("[" + str(enemy_lvl) + "]NO")
        return False
    else:
        print("[" + str(enemy_lvl) + "]YES")
        return True


#for i in range(3,100000):
    #RePrint("["+str(i)+"]HPBOSS="+str(Get_Boss_Health(i,True)))

print("Made By Dorty. This calculator DOES take into account attack speed and shield... ")


for enemy_lvl in range(2,100000):


    if ( not(CanIKillThisGuy(enemy_lvl,False)) ):
        print("[" + str(enemy_lvl-1) + "] You can easily kill " + str(enemy_lvl-1) + " lvl minion")
        break

print("--- ---")

for BossId in range(1, 6):
    BossName=""
    BossLvL = 0
    if(BossId == 1):
        BossName="Forest Golem"
        BossLvL=105
    elif(BossId == 2):
        BossName= "Avian"
        BossLvL= 75
    elif(BossId == 3):
        BossName = "Bee Queen"
        BossLvL = 70
    elif (BossId == 4):
        BossName = "Void Queen"
        BossLvL = 410
    elif (BossId == 5):
        BossName = "Soul Stealer"
        BossLvL = 365


    if( CanIKillThisBoss(BossLvL,True) ):
        print("Yes, you can kill " + BossName)
    else:
        print("No, you cannot kill " + BossName)
    print()