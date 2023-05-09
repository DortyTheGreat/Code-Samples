from javascript import require, On
mineflayer = require('mineflayer')
pathfinder = require('mineflayer-pathfinder')

RANGE_GOAL = 1
BOT_USERNAME = 'python'

bot = mineflayer.createBot({
  'host': "127.0.0.1",
  'port' : 60454,
  'username': BOT_USERNAME,
  'version' : "1.19.3"
  #'hideErrors': True
})

bot.loadPlugin(pathfinder.pathfinder)
print("Started mineflayer")




@On(bot, "end")
def handle(*args):
  print("Bot ended!", args)

@On(bot, 'chat')
def onChat(this, user, message, *rest):
  print(f'{user} said "{message}"')

  # If the message contains stop, remove the event listener and stop logging.
  #if 'stop' in message:
  #  off(bot, 'chat', onChat)