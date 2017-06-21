#!/usr/bin/env python3


def max_number_width_in_row(row):
    ''' Returns the width of the largest value in a matrix row '''
    return max(len(str(value)) for value in row)


def max_number_width_in_matrix(matrix):
    ''' Given a matrix, returns with (in characters) of the
    'widest' value. '''
    return max(max_number_width_in_row(row) for row in matrix)


def create_matrix(rows, cols):
    ''' Build a list of 'rows' lists containing 'cols' elements each '''
    return [[0] * cols for _ in range(rows)]


def format_matrix(matrix, column_divider=' '):
    ''' Returns a string representing a matrix where elements are
    evenly spaced and right justified. '''
    num_fmt = '{{:>{}}}'.format(max_number_width_in_matrix(matrix))

    formatted_rows = []
    for row in matrix:
        fmt_row = column_divider.join([num_fmt.format(element)
                                       for element in row])
        formatted_rows.append(fmt_row)

    return '\n'.join(formatted_rows)


def turn_right(dx, dy):
    ''' Returns updated x and y coordintes (in that order)
    executing a 90 degree right turn. '''
    return -dy, dx


def spiral(num):
    ''' Returns a string representing `num` by `num` matrix forming
    a spiral patterning beginning at the upper left-hand (0, 0) of
    the matrix. '''
    m = create_matrix(num, num)
    # coordinates and velocities
    x = 0
    y = 0
    dx = 1
    dy = 0
    # limits of spiral
    top = 1 
    right = num - 1
    bottom = num - 1
    left = 0

    # used when changing direction
    change_direction = False
    for n in range(1, (num * num) + 1):
        m[y][x] = n
        x += dx
        y += dy

        if dy < 0 and y == top:
            change_direction = True
            top += 1
        elif dx > 0 and x == right:
            change_direction = True
            right -= 1
        elif dy > 0 and y == bottom:
            change_direction = True
            bottom -= 1
        elif dx < 0 and x == left:
            change_direction = True
            left += 1

        if change_direction:
            dx, dy = turn_right(dx, dy)
            change_direction = False

    return format_matrix(m)


if __name__ == '__main__':
    print(spiral(6))
