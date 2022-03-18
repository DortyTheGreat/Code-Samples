import discord

from discord.ext import commands


import requests


client = discord.Client()

cliCom = commands.Bot(command_prefix="!")




@client.event # Событие при вызове сообщения
async def on_message(message):

    # Чтобы не было проблем с ловер аппер кейсами
    message.content.lower()


    if message.author == client.user:
        # бот не отвечает на самого себя
        return
    # Отвечать на примитивные комманды
    if message.content.startswith("hello"):
        await message.channel.send("bruh")
    if str(message.channel) == "основной":
        await message.channel.send("Daisy!")
    if str(message.author) == "Тесла#9030":
        await message.channel.send("My King!" + str(message.author))

@cliCom.command()
async def hello(ctx, *args):
    for arg in args:
        print(arg)
        await ctx.send(arg)

@cliCom.command()
async def help1(ctx, *args):
    help_str = '''
Hello, thanks,
Я гей    
'''
    await ctx.send(help_str)


@cliCom.command()
async def minecraft(ctx, *args):

    #r = requests.get()
    embed = discord.Embed(
        title= "CustomTitleName",
        description= "CustomDescName",
        color= discord.Color.dark_green()
    )
    # Картиночка
    embed.set_thumbnail(url="https://bipbap.ru/wp-content/uploads/2017/04/0_7c779_5df17311_orig.jpg")


    await ctx.send(embed=embed)


cliCom.run('OTI5MDY3MDIwODkxMzI4NTIy.Ydh7Fw.DtB0do4CYVKk9SvXeR86mV1ByZI')

#client.run('OTI5MDY3MDIwODkxMzI4NTIy.Ydh7Fw.DtB0do4CYVKk9SvXeR86mV1ByZI')