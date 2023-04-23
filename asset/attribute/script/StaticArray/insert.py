CAPACITY = 12
arr = [] * 12
size = 0


def StaticArrayInsert(arr, size, position, value):
    # the array is full and unable to insert
    if (size == CAPACITY):
        return  # stop insert

    # create an non-use square for insert value.
    # loop from higher to lower.
    for i in range(size + 1, position, -1):
        arr[i] = arr[i - 1]  # move data from lower square to higher

    # the init arr[position] have been move to arr[position + 1]
    # put the value into arr[position]
    arr[position] = value

    # arr have been inserted, size increase
    size = size + 1

    return arr, size
