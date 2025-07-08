# Sorting_Visualizer
This project visualizes and compares the three famous sorting algorithms : Bubble Sort, Quick Sort and Merged Sort.  I have used the library SDL2 for graphics rendering. The visualizer helps in understanding how the algorithms work internally. 

### 🔹 Bubble Sort  
Bubble Sort is a simple comparison based sorting algorithm. It repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. This continues until the list is sorted. On each pass through the list the largest unsorted element bubbles up to its correct spot.  
While Bubble Sort is easy to learn and implement, it is very inefficient when dealing with large datasets because of its O(n²) time complexity.

---

### 🔹 Merge Sort  
Merge Sort is a divide-and-conquer algorithm that finds the midpoint of an array, recursively sorts the two halves, and merges the two sorted halves back together. The overall sorting process is stable, efficient, and takes O(n log n) time for every single case!  
The Merge Sort in this visualizer shows a smooth merge of the sorted subarrays and has great performance even with large data sizes.

---

### 🔹 Quick Sort  
Quick Sort is an efficient in-place divide-and-conquer sorting algorithm. It makes a choice of a pivot element, partitions the array into an array of smaller elements to the left and larger elements to the right of the pivot, and then recursively sorts both partitions, and the empty arrays around them. For the best case, the Time complexity is O(n logn). And for the Worst case, it is O(n²).

###  Requirements  
You need to have **SDL2** installed on your system to run the visualizer. For detecting memory management issues, install valgrind 
To install SDL2 and valgrind on Ubuntu/Linux, run the following command:

```bash
sudo apt update  
sudo apt install libsdl2-dev
sudo apt install valgrind
```

---

###  How to Run

1. **Clone the repository**

```bash
git clone https://github.com/ssk1504/Sorting_Visualizer 
cd Sorting_Visualizer
```

2. **Compile the code**

```bash
g++ compare_sorts.cpp -g -o compare_sorts -pthread `sdl2-config --cflags --libs`
```

3. **Run the visualizer**

```bash
valgrind ./compare_sorts
```
