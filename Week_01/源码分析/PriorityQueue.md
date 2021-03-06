PriorityQueue的实现用的是一个二叉堆。默认是个小顶堆。详见源码分析

关键成员变量：
queue: Object[] 元素都存放在这个数组中
size: int = 0 记录元素的数量
comparator: Comparator<? super E> 这个比较器在向上调整或向下调整堆时，
用于比较两个元素的大小，可以为空。为空时要求元素实现Comparable接口，否则在添加时会抛出异常ClassCastException。

关键成员方法：
offer(E): boolean 向堆中插入一个元素，时间：O(logn)
poll(): E 删除堆顶元素，时间：O(logn)
peek(): E 读取堆顶元素，时间：O(1)
siftUp(int,E): void 拿着E从int开始向上调整堆
siftDown(int,E): void 拿着E从int开始向下调整堆
grow(int): void 扩容数组，这个扩容实现比HashMap要简单，因为元素的位置在扩容前后没有发生改变。

源码分析：
```java

//向堆中插入一个元素
public boolean offer(E e) {
    if (e == null)
        //不能插入null
        throw new NullPointerException();
    modCount++;
    //将元素放入到堆尾
    int i = size;
    if (i >= queue.length)
        //数组满了，扩容
        grow(i + 1);
    size = i + 1;
    if (i == 0)
        //当前只有一个元素，直接放在数组中第一个位置
        queue[0] = e;
    else
        //拿着e从i开始向上调整堆
        siftUp(i, e);
    return true;
}
//两个函数的执行流程一致，只是在比较时用的方法不同。
private void siftUp(int k, E x) {
    if (comparator != null)
        //使用Comparator版本的siftUp
        siftUpUsingComparator(k, x);
    else
        //使用Comparable版本的siftUp
        siftUpComparable(k, x);
}

@SuppressWarnings("unchecked")
private void siftUpComparable(int k, E x) {
    //这里解释了为啥添加未实现Comparable的元素时会抛出ClassCastException。
    Comparable<? super E> key = (Comparable<? super E>) x;
    while (k > 0) {
        //计算出父节点的索引
        int parent = (k - 1) >>> 1;
        Object e = queue[parent];
        //这里解释了为啥PriorityQueue默认是小顶堆
        if (key.compareTo((E) e) >= 0)
            //父节点小或与x相等，k就是x应该存放的位置。
            break;
        //父节点大，将父节点下沉
        queue[k] = e;
        //将x上浮
        k = parent;
    }
    queue[k] = key;
}

//执行逻辑与siftUpComparable一致，不再重复分析。
@SuppressWarnings("unchecked")
private void siftUpUsingComparator(int k, E x) {
    while (k > 0) {
        int parent = (k - 1) >>> 1;
        Object e = queue[parent];
        if (comparator.compare(x, (E) e) >= 0)
            break;
        queue[k] = e;
        k = parent;
    }
    queue[k] = x;
}

//取出堆顶元素
public E poll() {
    if (size == 0)
        return null;
    //将元素的数量减一
    int s = --size;
    modCount++;
    //取出堆顶元素
    E result = (E) queue[0];
    //取出堆尾元素
    E x = (E) queue[s];
    //清空堆尾
    queue[s] = null;
    if (s != 0)
        //堆里还有其他元素，拿着x从0开始向下调整堆
        siftDown(0, x);
    //返回堆顶元素
    return result;
}
//两个函数的执行流程一致，只是在比较时用的方法不同。
private void siftDown(int k, E x) {
    if (comparator != null)
        //使用Comparator版本的siftDown
        siftDownUsingComparator(k, x);
    else
        //使用Comparable版本的siftDown
        siftDownComparable(k, x);
}
@SuppressWarnings("unchecked")
private void siftDownComparable(int k, E x) {
    Comparable<? super E> key = (Comparable<? super E>)x;
    int half = size >>> 1;        // loop while a non-leaf
    while (k < half) {
        //k不是叶子节点时循环
        int child = (k << 1) + 1; // assume left child is least
        Object c = queue[child];
        int right = child + 1;
        if (right < size &&
            //这里不用判空吗? ...草，k不会是叶子节点
            ((Comparable<? super E>) c).compareTo((E) queue[right]) > 0)
            c = queue[child = right];
        if (key.compareTo((E) c) <= 0)
            //x小于等于左右孩子中的最小值，k就是x应该存放的位置。
            break;
        //c比x小，将c上浮
        queue[k] = c;
        //将x下沉
        k = child;
    }
    queue[k] = key;
}

@SuppressWarnings("unchecked")
private void siftDownUsingComparator(int k, E x) {
    int half = size >>> 1;
    while (k < half) {
        int child = (k << 1) + 1;
        Object c = queue[child];
        int right = child + 1;
        if (right < size &&
            comparator.compare((E) c, (E) queue[right]) > 0)
            c = queue[child = right];
        if (comparator.compare(x, (E) c) <= 0)
            break;
        queue[k] = c;
        k = child;
    }
    queue[k] = x;
}

//扩容数组
private void grow(int minCapacity) {
    int oldCapacity = queue.length;
    // Double size if small; else grow by 50%
    // 旧容量小于64，则新容量是旧容量的2倍，否则是旧容量的1.5倍
    int newCapacity = oldCapacity + ((oldCapacity < 64) ?
                                     (oldCapacity + 2) :
                                     (oldCapacity >> 1));
    // overflow-conscious code
    if (newCapacity - MAX_ARRAY_SIZE > 0)
        newCapacity = hugeCapacity(minCapacity);
    //创建一个长度为newCapacity的数组，并将旧数组中的内容拷贝到新数组。
    queue = Arrays.copyOf(queue, newCapacity);
}

```
