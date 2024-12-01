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
    
    def run(self):
        distance_array = []
        right_side = []
        left_side = []
        with open('input.txt', 'r') as file:
            for line in file:
                a, b = line.split()
                if a.isdigit() and b.isdigit():
                    a = int(a)
                    b = int(b)
                    left_side.append(a)
                    right_side.append(b)
                else:
                    print('Invalid input')
        left_side.sort()
        right_side.sort()
        for i in range(len(left_side)):
            distance_array.append(self.getDistance(left_side[i], right_side[i]))
        print(sum(distance_array))

    def getDistance(self, a, b):
        return abs(a - b)

if __name__ == '__main__':
    File('input.txt', 'r').run()
