## HeapBench
A EN063-EnglishIII homework project.

The project tests the performance of the three heaps, or four implementation:
- Binary Heap
- Binary Heap implemented by STL
- Leftist Heap
- Pairing Heap

The time complexity of these heaps are:

|Operation|Binary Heap|Leftist Heap|Pairing Heap|
|:---:|:---:|:---:|:---:|
|Push|$O(\log n)$|$O(\log n)$|$O(1)$|
|Pop|$O(\log n)$|$O(\log n)$|$O(\log n)$|
|Top|$O(1)$|$O(1)$|$O(1)$|
|Merge|Not supported|$O(\log n)$|$O(1)$|

To present a comprehensive review, we considered three cases, and generated data for each.

Since the Binary Heap does not support the operation `merge`, we added two tests, one not including `merge`, and another doing. 
- Operation `push`, `pop`, and `top`
- Operation `push`, `pop`, `top`, and `merge`

And because the Pairing Heap has relatively lower time complexity (O(1) when push, top, and merge; O(log n) when pop), we generated another data to show its superiority:
- Operation `push`, `pop`, `top`, and `merge` with ratio 13 : 13 : 13 : 1

The folder `result` contains the result of the test, in which the unit of value is millisecond.