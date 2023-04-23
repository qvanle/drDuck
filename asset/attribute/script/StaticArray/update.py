CAPACITY = 12
arr = [] * 12
size = 0


def StaticArrayUpdate(arr, size, position, value):
    # if out of bound, update the last position
    if (position >= size):
        position = size - 1

    # update value of arr[position]
    arr[position] = value

    return arr, size
