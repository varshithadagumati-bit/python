import numpy as np
arr = np.array([[10,20,30],[15,9,18],[30,8,12]])
print("Original array: ")
print(arr)
max_indices = np.argmax(arr, axis=1)
min_indices = np.argmin(arr, axis=1)
print("\n Indices of Maximum values: ", max_indices)
print("Indices of minimum values: ", min_indices)
max_values = arr[np.arange(len(arr)), max_indices]
min_values = arr[np.arange(len(arr)), min_indices]
print("\nMaximum Values: ", max_values)
print("Minimum values: ", min_values)