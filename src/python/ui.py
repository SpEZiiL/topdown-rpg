# import stuff
import os, sys, game, util, time
with open(os.devnull, 'w') as f:
	oldstdout = sys.stdout
	sys.stdout = f

	import pygame

	sys.stdout = oldstdout
from loader import *
from uiElements import *

# color setup
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# pygame init
pygame.init()

# window setup
screenSize = pygame.display.list_modes()[0]
screen = pygame.display.set_mode(screenSize)
if not game.debug:
	pygame.display.toggle_fullscreen() # set to fullscreen
pygame.display.set_caption("First Test")
done = False
clock = pygame.time.Clock()

# asset setup
potion_heal_small = AnimationAsset("data/ui/title_screen.background", pygame.USEREVENT, (0, 0)) # create asset
potion_heal_small.loadAnimation("main", resolution=screenSize, defaultState=True, loop=True) # load animation
eventnum, updateTime = potion_heal_small.getAnimationEventData("main") # get animation settings
pygame.time.set_timer(eventnum, updateTime) # setup fps loop

#Audio Playing
#audioplayer=util.audio()
#data=audioplayer.play(r"/home/riedler/Scripts/RMusics/D4.wav")

# mainloop
while not done:
	# event handling
	events = pygame.event.get()
	for event in events:
		# close event
		if event.type == pygame.QUIT or event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
			done = True
		'''
		# mouse handler
		if event.type == pygame.MOUSEBUTTONUP:
			pos = pygame.mouse.get_pos()
			position = potion_heal_small.pos
			rectSize = potion_heal_small.currentFrame.get_rect().size
			rect = pygame.Rect(position[0], position[1], rectSize[0], rectSize[1])
			if rect.collidepoint(pos):
				potion_heal_small.start(eventnum)
		'''
		potion_heal_small.update(event.type)
	# end event handling

	if potion_heal_small.changed:
		# drawing
		screen.fill(WHITE)
		screen.blit(potion_heal_small.currentFrame, (0, 0))
		pygame.display.update()
		potion_heal_small.changed = False

	if game.debug:
		print(clock.get_fps(), end="\r")

	# update
	clock.tick(60)

#audioplayer.close(False)
pygame.quit()
