import pygame
from cell import Cell

RES = WIDTH, HEIGHT = 602, 402
TILE = 50
cols, rows = WIDTH // TILE, HEIGHT // TILE

pygame.init()
screen = pygame.display.set_mode(RES)
clock = pygame.time.Clock()

grid_cells = [Cell(col, row, screen) for row in range(rows) for col in range(cols)]
current_cell = grid_cells[0]
stack = []
colors, color = [], 40
show_solution = False
solution = []
found_solution = False
finish_cell = grid_cells[-1]