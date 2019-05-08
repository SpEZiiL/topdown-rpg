import pygame

class TextEntry(pygame.sprite.Sprite):
	def __init__(self, position, dimensions, fontName=None, fontSize=32, *groups):
		super().__init__(groups)
		font = pygame.font.Font(fontName, fontSize)
		border = pygame.Rect(position, dimensions)
