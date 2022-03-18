import mcpi.minecraft as minecraft

# https://tutorials.fadehost.com/convert-domain-ip/
mc = minecraft.Minecraft.create("83.69.241.56",25565)
pos = 0
pos = mc.player.getPos()

print(pos.x)