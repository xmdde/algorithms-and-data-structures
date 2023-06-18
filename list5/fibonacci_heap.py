import math
import random

cmps = 0

class FibonacciTree:
    def __init__(self, value):
        self.value = value
        self.child = []
        self.order = 0

    def add_at_end(self, t):
        self.child.append(t)
        self.order = self.order + 1

class FibonacciHeap:
    def __init__(self):
        self.trees = []
        self.least = None
        self.count = 0

    def insert(self, value):
        global cmps
        new_tree = FibonacciTree(value)
        self.trees.append(new_tree)
        cmps += 1
        if self.least is None or value < self.least.value:
            self.least = new_tree
        self.count += 1

    def get_min(self):
        if self.least is None:
            return None
        return self.least.value

    def extract_min(self):
        smallest = self.least
        if smallest is not None:
            for child in smallest.child:
                self.trees.append(child)
            self.trees.remove(smallest)
            if self.trees == []:
                self.least = None
            else:
                self.least = self.trees[0]
                self.consolidate()
            self.count -= 1
            return smallest.value

    def consolidate(self):
        global cmps
        aux = (floor_log(self.count) + 1) * [None]

        while self.trees != []:
            x = self.trees[0]
            order = x.order
            self.trees.remove(x)
            while aux[order] is not None:
                y = aux[order]
                cmps += 1
                if x.value > y.value:
                    x, y = y, x
                x.add_at_end(y)
                aux[order] = None
                order += 1
            aux[order] = x

        self.least = None
        for k in aux:
            if k is not None:
                self.trees.append(k)
                cmps += 1
                if self.least is None or k.value < self.least.value:
                    self.least = k
    
    def merge(self, other_heap):
        global cmps
        self.trees.extend(other_heap.trees)
        cmps += 1
        if self.least is None or (other_heap.least is not None and other_heap.least.value < self.least.value):
            self.least = other_heap.least
        self.count += other_heap.count

def floor_log(x):
    return math.frexp(x)[1] - 1

def generate_data_hist():
    global cmps
    with open("./data/fib1.txt", "w") as file:
        file.write("k;n;i;comps\n")
        for n in [500, 1000]:
            for k in range(5):
                i = 0
                cmps = 0
                heap1 = FibonacciHeap()
                file.write(f"{k};{n};{i};{cmps}\n")
                cmps = 0
                heap2 = FibonacciHeap()
                i += 1
                file.write(f"{k};{n};{i};{cmps}\n")
                for _ in range(n):
                    cmps = 0
                    heap1.insert(random.randint(0, (2*n - 1)))
                    i += 1
                    file.write(f"{k};{n};{i};{cmps}\n")
                for _ in range(n):
                    cmps = 0
                    heap2.insert(random.randint(0, (2*n - 1)))
                    i += 1
                    file.write(f"{k};{n};{i};{cmps}\n")
                cmps = 0
                heap1.merge(heap2)
                i += 1
                file.write(f"{k};{n};{i};{cmps}\n")
                for _ in range(2*n):
                    cmps = 0
                    heap1.extract_min()
                    i += 1
                    file.write(f"{k};{n};{i};{cmps}\n")

def generate_data():
    global cmps
    with open("./data/fib2.txt", "w") as file:
        file.write("n;cmp\n")
        for n in range(100, 10001, 100):
            cmps = 0
            heap1 = FibonacciHeap()
            heap2 = FibonacciHeap()
            for _ in range(n):
                heap1.insert(random.randint(0, (2*n - 1)))
                heap2.insert(random.randint(0, (2*n - 1)))
            heap1.merge(heap2)
            for _ in range(2*n):
                heap1.extract_min()
            file.write(f"{n};{cmps}\n")

if __name__ == "__main__":
    generate_data_hist()
    generate_data()