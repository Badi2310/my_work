import pygame
from random import choice

RES = WIDTH, HEIGHT = 602, 402
TILE = 50
cols, rows = WIDTH // TILE, HEIGHT // TILE

class Cell:
    """Класс представляюет собой - класс клеток"""
    def __init__(self, x, y, screen):
        """инициализация клетки"""
        self.x, self.y = x, y
        self.screen = screen
        self.walls = {'top': True, 'right': True, 'bottom': True, 'left': True}
        self.visited = False

    def draw_current_cell(self):
        """отображение текущей клетки"""
        x, y = self.x * TILE, self.y * TILE
        screen = self.screen
        pygame.draw.rect(screen, pygame.Color('saddlebrown'), (x + 2, y + 2, TILE - 2, TILE - 2))

    def draw(self):
        """отображение клетки"""
        x, y = self.x * TILE, self.y * TILE
        screen = self.screen

        if self.visited:
            pygame.draw.rect(screen, pygame.Color('black'), (x, y, TILE, TILE))

        if self.walls['top']:
            pygame.draw.line(screen, pygame.Color('darkorange'), (x, y), (x + TILE, y), 3)
        if self.walls['right']:
            pygame.draw.line(screen, pygame.Color('darkorange'), (x + TILE, y), (x + TILE, y + TILE), 3)
        if self.walls['bottom']:
            pygame.draw.line(screen, pygame.Color('darkorange'), (x + TILE, y + TILE), (x , y + TILE), 3)
        if self.walls['left']:
            pygame.draw.line(screen, pygame.Color('darkorange'), (x, y + TILE), (x, y), 3)

    def check_cell(self, x, y, grid_cells):
        """проверка на корректность координат клетки"""
        find_index = lambda x, y: x + y * cols
        if x < 0 or x > cols - 1 or y < 0 or y > rows - 1:
            return False
        return grid_cells[find_index(x, y)]

    def check_neighbors(self, grid_cells):
        """Эта функция возвращает случайную соседную клетку если таковая есть,
           иначе возвращает False
        """
        neighbors = []
        top = self.check_cell(self.x, self.y - 1, grid_cells)
        right = self.check_cell(self.x + 1, self.y, grid_cells)
        bottom = self.check_cell(self.x, self.y + 1, grid_cells)
        left = self.check_cell(self.x - 1, self.y, grid_cells)
        if top and not top.visited:
            neighbors.append(top)
        if right and not right.visited:
            neighbors.append(right)
        if bottom and not bottom.visited:
            neighbors.append(bottom)
        if left and not left.visited:
            neighbors.append(left)
        return choice(neighbors) if neighbors else False

    def draw_option(self, color):
        """отображение клетки выбранным цветом"""
        x, y = self.x * TILE, self.y * TILE
        screen = self.screen
        if self.visited:
            pygame.draw.rect(screen, color, (x, y, TILE, TILE))

def remove_walls(current, next):
    """удаляет границы между клетками"""
    dx = current.x - next.x
    if dx == 1:
        current.walls['left'] = False
        next.walls['right'] = False
    elif dx == -1:
        current.walls['right'] = False
        next.walls['left'] = False
    dy = current.y - next.y
    if dy == 1:
        current.walls['top'] = False
        next.walls['bottom'] = False
    elif dy == -1:
        current.walls['bottom'] = False
        next.walls['top'] = False