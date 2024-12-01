#!/bin/python3

class File:
    def __init__(self, file_name, mode):
        self.file_name = file_name
        self.mode = mode

    def __enter__(self):
        self.file = open(self.file_name, self.mode)
        return self.file

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.close()

    def get_side(self, file):
        right_side = []
        left_side = []
        for line in file:
            a, b = line.split()
            if a.isdigit() and b.isdigit():
                a = int(a)
                b = int(b)
                left_side.append(a)
                right_side.append(b)
            else:
                print('Invalid input')
        return left_side, right_side

    def part_two(self):
        score = 0
        number_of_times = 0
        right_side = []
        left_side = []

        with open(self.file_name, self.mode) as file:
            left_side, right_side = self.get_side(file)
        for i in range(len(left_side)):
            for j in range(len(right_side)):
                if left_side[i] == right_side[j]:
                    number_of_times += 1
            score += left_side[i] * number_of_times
            number_of_times = 0
        print(score)

    def part_one(self):
        distance_array = []
        right_side = []
        left_side = []
        with open(self.file_name, self.mode) as file:
            left_side, right_side = self.get_side(file)
        left_side.sort()
        right_side.sort()
        for i in range(len(left_side)):
            distance_array.append(self.getDistance(left_side[i], right_side[i]))
        print(sum(distance_array))

    def getDistance(self, a, b):
        return abs(a - b)

if __name__ == '__main__':
    File('input.txt', 'r').part_one()
    File('input.txt', 'r').part_two()
