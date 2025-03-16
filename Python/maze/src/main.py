import pygame
#from cell import Cell
from cell import remove_walls
import globals as gl

while True:
    gl.screen.fill(pygame.Color('darkslategray'))

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_s:
                gl.show_solution = True

    [cell.draw() for cell in gl.grid_cells]
    gl.current_cell.visited = True
    gl.current_cell.draw_current_cell()
    [pygame.draw.rect(gl.screen, gl.colors[i], (cell.x * gl.TILE + 2, cell.y * gl.TILE + 2,
                                            gl.TILE - 4, gl.TILE - 4)) for i, cell in enumerate(gl.stack)]

    next_cell = gl.current_cell.check_neighbors(gl.grid_cells)
    if next_cell:
        next_cell.visited = True
        gl.stack.append(gl.current_cell)
        if gl.found_solution == False:
            gl.solution.append(gl.current_cell)
            if gl.current_cell == gl.finish_cell:
                gl.found_solution = True
        gl.colors.append((min(gl.color, 255), 10, 100))
        gl.color += 1
        remove_walls(gl.current_cell, next_cell)
        gl.current_cell = next_cell
    elif gl.stack:
        gl.current_cell = gl.stack.pop()
        if gl.found_solution == False:
            gl.solution.pop()
    if gl.show_solution and not gl.stack:
        [pygame.draw.rect(gl.screen, "green", (cell.x * gl.TILE + 10, cell.y * gl.TILE + 10,
                                            gl.TILE - 20, gl.TILE - 20)) for i, cell in enumerate(gl.solution)]
    pygame.display.flip()
    gl.clock.tick(32)#30