import os,sys,pygame,json
from util import *

lastEventNum = 1

class Asset(pygame.sprite.Sprite):
	def __init__(self, configPath, *groups):
		super().__init__(groups)
		self.conf = self.loadConfig(configPath)
	def loadConfig(self, path):
		with open(path, "r") as f:
			configData = json.loads(f.read())
		return configData

class ImageAsset(Asset):
	loadedimages = {}
	currentFrame = None
	changed = False
	def __init__(self, configPath, defaultPosition=(0, 0), defaultIcon=None, defaultIconResolution=None, defaultLoad=[], *groups):
		self.pos = defaultPosition
		configPath = join_assets(configPath)
		super().__init__(configPath, groups)
		self.changed = True
		if defaultIcon == None:
			defaultIcon = missingTextureIcon
		elif not isinstance(defaultIcon, pygame.Surface):
			self.loadImage(defaultIcon)
			defaultIcon = pygame.transform.scale(self.loadedimages[defaultIcon], defaultIconResolution)
		self.currentFrame = defaultIcon
		for defaultLoaded in defaultLoad:
			self.loadedimages[join_assets("sprites", defaultLoaded)] = pygame.image.load(defaultLoaded)
	def getImageConf(self, imgname):
		return self.conf.get("icons").get(imgname)
	def loadImage(self, imgname, imgConf=None):
		if imgname in self.loadedimages.keys():
			return None
		if imgConf == None:
			imgConf = self.getImageConf(imgname)
		self.loadedimages[imgname] = pygame.image.load(join_assets(imgConf["path"] + self.conf["id"] + "_" + imgname + ".png"))
		self.changed = True
	def setIcon(self, imageName):
		self.currentFrame = loadedimages[imageName]
		self.changed = True
	def moveBy(self, offset):
		self.position = (position[0] + offset[0], position[1] + offset[1])
		self.changed = True

class AnimationAsset(ImageAsset):
	animations = {}
	loadedAnimations = {}
	animationEventData = {}
	def __init__(self, configPath, userEventNum, defaultIconPosition=(0, 0), defaultIcon=None, defaultIconResolution=None, defaultLoad=[], *groups):
		super().__init__(configPath, defaultIconPosition, defaultIcon, defaultIconResolution, defaultLoad, groups)
		self.userEventNum = userEventNum
	def getAnimationConf(self, animationname):
		return self.conf.get("animations").get(animationname)
	def loadAnimation(self, animationname, resolution=None, defaultState=False, loop=False):
		if not animationname in self.loadedAnimations.keys():
			self.loadImage(animationname, self.getAnimationConf(animationname))
			fullImg = self.loadedimages[animationname]
			if fullImg == None:
				return
			imgSize = fullImg.get_rect().size
			imgConf = self.getAnimationConf(animationname)
			framesize = imgConf["framesize"]
			count = (round(imgSize[0]/framesize[0]), round(imgSize[1]/framesize[1]))
			framecount = imgConf["framecount"]
			updateEventNum, updateTime = self.getAnimationEventData(animationname)
			rects = []
			for y in range(0, count[1]):
				for x in range(0, count[0]):
					rects.append(pygame.Rect(x*framesize[0], y*framesize[1], framesize[0], framesize[1]))
			animation = []
			if resolution == None:
				resolution = (framesize[0], framesize[1])
			for i in range(0, framecount):
				animation.append(pygame.transform.scale(fullImg.subsurface(rects[i]), resolution))
			self.loadedAnimations[animationname] = animation
			self.animations[updateEventNum] = [animation, 0, defaultState, loop, animationname, updateEventNum]
			self.currentFrame = animation[0]
			self.changed = True
	def getAnimationEventData(self, animationname):
		global lastEventNum
		updateTime = round(1000/self.conf["animations"][animationname]["fps"])
		if updateTime in self.animationEventData.keys():
			eventnum = self.animationEventData[updateTime]
		else:
			found = False
			for animation in self.animations.keys():
				if self.animations[animation][4] == animationname:
					eventnum = self.animations[animation][5]
					found = True
			if not found:
				eventnum = self.userEventNum + lastEventNum
				lastEventNum += 1
			self.animationEventData[updateTime] = eventnum
		return eventnum, updateTime
	def update(self, *args):
		updateEventNum = args[0]
		if self.animations.get(updateEventNum) != None and self.animations[updateEventNum][2]:
			if self.animations[updateEventNum][1] > self.getAnimationConf(self.animations[updateEventNum][4])["framecount"] - 1:
				self.animations[updateEventNum][1] = 0
				self.animations[updateEventNum][2] = self.animations[updateEventNum][3]
			self.currentFrame = self.animations[updateEventNum][0][self.animations[updateEventNum][1]]
			self.animations[updateEventNum][1] += 1
			self.changed = True
	def start(self, updateEventNum, loop=False):
		self.animations[updateEventNum][2] = True
		self.animations[updateEventNum][3] = loop
	def stop(self, updateEventNum):
		self.animations[updateEventNum][2] = False
	def reset(self, updateEventNum):
		self.animations[updateEventNum][1] = 0
		self.animations[updateEventNum][2] = False
missingTextureIcon = pygame.transform.scale(pygame.image.load(join_assets("sprites", "icons", "missing_texture.png")), (64, 64))
