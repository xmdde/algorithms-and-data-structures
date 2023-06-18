import random
import math

cmps = 0

class BinomialTree:
    def __init__(self, key):
        self.key = key
        self.children = []
        self.order = 0
 
    def add_at_end(self, t):
        self.children.append(t)
        self.order = self.order + 1
 
class BinomialHeap:
    def __init__(self):
        self.trees = []
 
    def extract_min(self):
        global cmps
        if self.trees == []:
            return None
        smallest_node = self.trees[0]
        for tree in self.trees:
            cmps += 1
            if tree.key < smallest_node.key:
                smallest_node = tree
        self.trees.remove(smallest_node)
        h = BinomialHeap()
        h.trees = smallest_node.children
        self.merge(h)
 
        return smallest_node.key
 
    def get_min(self):
        global cmps
        if self.trees == []:
            return None
        least = self.trees[0].key
        for tree in self.trees:
            cmps += 1
            if tree.key < least:
                least = tree.key
        return least
 
    def combine_roots(self, h):
        self.trees.extend(h.trees)
        self.trees.sort(key=lambda tree: tree.order)
 
    def merge(self, h):
        global cmps
        self.combine_roots(h)
        if self.trees == []:
            return
        i = 0
        while i < len(self.trees) - 1:
            current = self.trees[i]
            after = self.trees[i + 1]
            if current.order == after.order:
                if (i + 1 < len(self.trees) - 1
                    and self.trees[i + 2].order == after.order):
                    after_after = self.trees[i + 2]
                    cmps += 1
                    if after.key < after_after.key:
                        after.add_at_end(after_after)
                        del self.trees[i + 2]
                    else:
                        after_after.add_at_end(after)
                        del self.trees[i + 1]
                else:
                    cmps += 1
                    if current.key < after.key:
                        current.add_at_end(after)
                        del self.trees[i + 1]
                    else:
                        after.add_at_end(current)
                        del self.trees[i]
            i = i + 1
 
    def insert(self, key):
        g = BinomialHeap()
        g.trees.append(BinomialTree(key))
        self.merge(g)

def floor_log(x):
    return math.frexp(x)[1] - 1

def generate_data_hist():
    global cmps
    with open("./data/binomial1.txt", "w") as file:
        file.write("k;n;i;comps\n")
        for n in [500, 1000]:
            for k in range(5):
                i = 0
                cmps = 0
                heap1 = BinomialHeap()
                file.write(f"{k};{n};{i};{cmps}\n")
                cmps = 0
                heap2 = BinomialHeap()
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
    with open("./data/binomial2.txt", "w") as file:
        file.write("n;cmp\n")
        for n in range(100, 10001, 100):
            cmps = 0
            heap1 = BinomialHeap()
            heap2 = BinomialHeap()
            for _ in range(n):
                heap1.insert(random.randint(0, (2*n - 1)))
                heap2.insert(random.randint(0, (2*n - 1)))
            heap1.merge(heap2)
            for _ in range(2*n):
                heap1.extract_min()
            file.write(f"{n};{cmps}\n")

if __name__ == "__main__":
    generate_data_hist()
    #generate_data()