import time

from javascript import require, On
mineflayer = require('mineflayer')
pathfinder = require('mineflayer-pathfinder')

from secret import *

RANGE_GOAL = 1


bot = 0

def re_createbot():
  global bot
  bot = mineflayer.createBot({
    'host': "play.new-places.ru",
    'port' : 25565,
    'username': BOT_USERNAME,
    'version' : "1.19.2"
    #'hideErrors': True
  })
  bot.loadPlugin(pathfinder.pathfinder)
  print("Started mineflayer")

  @On(bot, "end")
  def handle(*args):
    print("Bot ended!")

  @On(bot, 'chat')
  def onChat(this, user, message, *rest):
    print(f'{user} said "{message}"')

  @On(bot, 'login')
  def onLogin(this):
    time.sleep(2)

    bot.chat("/login " + BOT_OFFLINE_PASS)
    bot.setQuickBarSlot(0)
    bot.activateItem()

    for i in range(5):
      time.sleep(1)
      bot.setQuickBarSlot(0)
      bot.activateItem()
      print(f'try {i + 1}')

  @On(bot, 'message')
  def onMSG(this, jsonMsg, position, *args):
    mesg = jsonMsg.toString()
    print(f"msg: {mesg}")

  @On(bot, 'kicked')
  def onKick(this, reason, loggedIn):
    print(f'kicked, {reason}, - {loggedIn}')
    # If the message contains stop, remove the event listener and stop logging.
    # if 'stop' in message:
    #  off(bot, 'chat', onChat)









while(True):
  print('30 секунд буферного ожидания для прикола')
  time.sleep(30)
  try:
    re_createbot()
  except:
    print('some error, idk')
  time.sleep(5 * 60) # 5 минут до попытки перезахода
  try:
    bot.end()
  except:
    print('some error, idk')
  print('bye-bye!')
  time.sleep(1 * 60) # 1 минута для ре-логина
