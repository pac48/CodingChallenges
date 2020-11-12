class Node:
    def __init__(self,val = 0, next=None, prev=None):
        self.next = next
        self.prev = prev
        self.value = val

class LinkedList:
    def __init__(self):
        self.head = Node()
        self.tail = Node()
        self.tail.prev = self.head
        self.head.next = self.tail
        self.size = 0

    def append(self, val):
        self.size += 1
        n = Node(val=val)
        tmp = self.tail.prev # node before tail
        self.tail.prev = n
        n.prev = tmp
        n.next = self.tail
        tmp.next = n

    def __str__(self):
        return self.__repr__()

    def __repr__(self):
        if self.size == 0:
            return  "[]"
        string = "["
        n = self.head.next
        while n != self.tail:
            string += str(n.value)+", "
            n = n.next
        string = string[:-2]
        string += "]"
        return string


def reverseList(L):
    # reverse this list
    n = L.head
    while n != None:
        tmp = n.next
        n.next = n.prev
        n.prev = tmp
        n = n.prev
    tmp = L.head
    L.head = L.tail
    L.tail = tmp

if __name__ == '__main__':
    L = LinkedList()
    print(L)
    L.append(0)
    print(L)
    L.append(1)
    L.append(2)
    L.append(3)
    print(L)
    print(L.size)

    reverseList(L)
    print(L)

    reverseList(L)
    print(L)