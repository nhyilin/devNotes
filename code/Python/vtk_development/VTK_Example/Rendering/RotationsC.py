#!/usr/bin/env python

"""
Rotations, VTK Textbook figure 3-31c.

Note: Make sure Rotations.py is in the same directory as this program.
"""

import Rotations


def main():
    file_name, figure, book_color = Rotations.get_program_parameters()
    # Set up for six rotations about the z-axis.
    figure = 3
    book_color = True
    Rotations.rotate(file_name, figure, book_color)


if __name__ == '__main__':
    main()
