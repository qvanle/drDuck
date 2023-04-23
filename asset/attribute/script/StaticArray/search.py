CAPACITY = 12
arr = [] * 12
size = 0


def StaticArraySearch(arr, size, value):

    result = -1  # if value does not exist in arr, return -1

    for i in range(0, size):
        if (arr[i] == value):  # found value
            result = i  # get the first position
            break  # stop finding

    return result
