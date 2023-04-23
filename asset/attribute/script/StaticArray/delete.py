CAPACITY = 12
arr = [] * 12
size = 0


def StaticArrayDelete(arr, size, position):
    # the array is empty and unable to delete
    if (size == 0):
        return  # stop delete

    delta = 0  # number of elements that have been deleted
    for i in range(0, size):
        if (i == position):  # ony delete 1 elements at position
            delta = 1
        else:
            arr[i] = arr[i + delta]  # shift left the data
    return arr, size
