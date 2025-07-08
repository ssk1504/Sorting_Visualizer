# Sorting_Visualizer
This project visualizes and compares the three famous sorting algorithms : Bubble Sort, Quick Sort and Merged Sort.  I have used the library SDL2 for graphics rendering. The visualizer helps in understanding how the algorithms work internally. 

### 🔹 Bubble Sort  
Bubble Sort is a simple comparison-based sorting algorithm. It repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. This process is repeated until the list is sorted. In each pass, the largest unsorted element "bubbles" up to its correct position.  
Although easy to understand and implement, Bubble Sort is highly inefficient for large datasets due to its O(n²) time complexity.

---

### 🔹 Merge Sort  
Merge Sort is a divide-and-conquer algorithm that divides the array into two halves, recursively sorts each half, and then merges the sorted halves back together. This results in a stable and efficient sorting process with guaranteed O(n log n) time complexity for all cases.  
In this visualizer, Merge Sort shows smooth merging of sorted subarrays and performs well even for large data sizes.

---

### 🔹 Quick Sort  
Quick Sort is a highly efficient in-place divide-and-conquer sorting algorithm. It selects a pivot element, partitions the array around the pivot such that smaller elements go to the left and larger to the right, and then recursively sorts the partitions.  
Although Quick Sort has a worst-case time complexity of O(n²), its average performance is O(n log n), and it typically outperforms other algorithms in practice. The visualizer shows how the array gets progressively divided and sorted around pivot positions.
