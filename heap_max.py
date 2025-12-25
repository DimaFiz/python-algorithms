class HeapMax:

    def __init__(self):
        self.heap = []
        self.size = 0

    def insert(self, x):

        self.heap.append(x)

        self.size += 1
        if self.size == 0:
            return
        i = self.size - 1
        while i > 0:
            if x > self.heap[(i - 1) // 2]:
                self.heap[i] = self.heap[(i - 1) // 2]
                i = (i - 1) // 2
            else:
                self.heap[i] = x
                break
        else:
            self.heap[0] = x

    def extract(self):
        if self.size == 0:
            return None
        res = self.heap[0]
        mover = self.heap[-1]
        i = 0
        while 2 * i + 1 < self.size - 1:
            if self.heap[2 * i + 1] > self.heap[2 * i + 2]:
                if mover < self.heap[2 * i + 1]:
                    self.heap[i] = self.heap[2 * i + 1]
                    i = 2 * i + 1
                else:
                    self.heap[i] = mover
                    break
            else:
                if mover < self.heap[2 * i + 2]:
                    self.heap[i] = self.heap[2 * i + 2]
                    i = 2 * i + 2
                else:
                    self.heap[i] = mover
                    break
        else:
            self.heap[i] = mover

        self.heap.pop()
        self.size -= 1
        return res


