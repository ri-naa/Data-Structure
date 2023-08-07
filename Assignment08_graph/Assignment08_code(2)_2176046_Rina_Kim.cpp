#include <stdio.h>
#define MAX_VERTICES 8
#define INF 1000L
#define TRUE 1
#define FALSE 0

typedef struct {
    int key;
    int num;
    int selected;
} vertex;

typedef struct {
    vertex heap[100];
    int heap_size;
} HeapType;

int weight[MAX_VERTICES][MAX_VERTICES] = { 
    {0, 3, INF, INF, INF, INF, INF, 14}, 
    {3, 0, 8, INF, INF, INF, INF, 10}, 
    {INF, 8, 0, 15, 2, INF, INF, INF},
    {INF, INF, 15, 0, INF, INF, INF, INF},
    {INF, INF, 2, INF, 0, 9, 4, 5},
    {INF, INF, INF, INF, 9, 0, INF, INF},
    {INF, INF, INF, INF, 4, INF, 0, 6},
    {14, 10, INF, INF, 5, INF, 6, 0} 
};

int dist[MAX_VERTICES];
int parent[MAX_VERTICES];

void swap(vertex* a, vertex* b) {
    vertex temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void build_min_heap(HeapType* h) {
    vertex temp;
    int parent, child;

    int half = h->heap_size / 2;
    for (int i = half; i > 0; i--) {
        temp = h->heap[i];
        parent = i;
        child = 2 * i;

        while (child <= h->heap_size) {
            if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
                child++;
            if (temp.key <= h->heap[child].key)
                break;

            h->heap[parent] = h->heap[child];
            parent = child;
            child *= 2;
        }

        h->heap[parent] = temp;
    }
}

// Delete the root at heap h, (# of elements: heap_size)
vertex delete_min_heap(HeapType* h) {
    vertex item = h->heap[1];
    vertex temp = h->heap[(h->heap_size)--];
    int parent = 1;
    int child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key <= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

// decrease the element i's value to 'key'
void Decrease_key_min_heap(HeapType* h, int i, int key) {
    if (key >= h->heap[i].key)
        printf("New key is smaller than current key\n");

    while (i > 1 && h->heap[i].key < h->heap[parent[i]].key) {
        swap(&h->heap[i], &h->heap[parent[i]]);
        i = parent[i];
    }
    h->heap[i].key = key;
}

void prim(HeapType* h, int n) {
    int u;
    vertex min;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        h->heap[i].key = dist[i];
        h->heap[i].num = i;
        h->heap[i].selected = 0;
        parent[i] = -1;
    }
    dist[1] = 0;

    h->heap_size = n;
    build_min_heap(h);
    for (int i = 0; i < n; i++) {
        min = delete_min_heap(h);
        h->heap[min.num-1].selected = 1;
        for (int j = min.num + 1; j <= n; j++) {
            if (weight[min.num - 1][j - 1] != INF) {
                if (h->heap[j].selected != 1 && weight[min.num - 1][j - 1] < dist[j]) {
                    dist[j] = weight[min.num - 1][j - 1];
                    parent[j] = min.num;
                    Decrease_key_min_heap(h, j, dist[j]);
                }
            }
        }
        build_min_heap(h);
    }
}

void print_prim(HeapType* h, int n) {
    for (int i = 0; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (parent[j] == i)
                printf("Vertex %d -> %d     edge: %d\n", i - 1, j - 1, dist[j]);
}

void main() {
    HeapType h;
    prim(&h, MAX_VERTICES);
    print_prim(&h, MAX_VERTICES);
}