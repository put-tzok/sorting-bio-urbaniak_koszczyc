#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 1000*3, 2000*3, 3000*3, 4000*3, 5000*3, 6000*3, 7000*3, 8000*3, 9000*3, 10000*3 /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, unsigned int n) {
    // TODO: implement
    for(int i = 0; i < n; i++)
    {
      t[i] = i;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    // TODO: implement
    for(int i=0; i<n; i++)
    {
      t[i] = n-1-i;
    }
}

void fill_vshape(int *t, unsigned int n) {
    // TODO: implement
    int l = 0;
    int p = n-1;

    for(
        int i = 0; i < n; i++){
      if(i%2 == 0){
        t[l] = n-1-i;
        l++;
      }
      if(i%2 == 1){
        t[p] = n-1-i;
        p--;
      }
    }
}

void fill_random(int *t, unsigned int n) {
    for(int i = 0; i < n; i++)
    {
        t[i] = rand();
    }
}

int argmin(int *t, int pocz, int kon)
{
  int najmn = t[pocz];
  for(int i=pocz; i<kon; i++)
  {
    if(t[i]<t[najmn])
    {
      najmn=i;
    }
  }
  return najmn;
}

void swap(int *src, int *dest) {
    int temp = *src;
    *src = *dest;
    *dest = temp;
}


int findMin(int *arr, unsigned int startingIndex, unsigned int size) {
    unsigned int i;
    int minIndex = startingIndex;
    int minElement = arr[startingIndex];
    for(i = startingIndex; i < size - 1; i++) {
        if(arr[i + 1] < minElement) {
            minIndex = i + 1;
            minElement = arr[i + 1];
        }
    }
    return minIndex;
}

void selection_sort(int *t, int size) {
    unsigned int i;
    for(i = 0; i < size; i++) {
        // int index = argmin(t, i, size);
        int index = findMin(t, i, size);
        swap(&t[i], &t[index]);
    }
}

void insertion_sort(int *t, unsigned int n) {
    // TODO: implement
    int i;
    for(int j=1; j<n; j++)
    {
      int key=t[j];
      i=j-1;

      while (i>=0 && t[i]>key)
      {
        t[i+1]=t[i];
        i--;
      }
      t[i+1]=key;
    }
}

int podzial(int *t, int pocz, int kon) // ostatni element jest pivotem
{
  int pivot=t[kon];
  int i = (pocz - 1);
  for(int j=pocz; j<kon; j++)
  {
    if(t[j] <= pivot)
    {
      i++;
      swap(&t[i], &t[j]);
    }
  }
    i++;
    swap(&t[i], &t[kon]);
    return i;
}

int random_podzial (int *t, int pocz, int kon) // losowy element jest pivotem
{
  int i=rand()%kon + pocz;
  swap(&t[i], &t[kon]);
  return podzial(t, pocz, kon);
}
void szypkie_sortowanie(int *t, int pocz, int kon)
{
  if(pocz < kon)
  {
  int q = podzial(t, pocz, kon);
    szypkie_sortowanie(t, pocz, q-1);
    szypkie_sortowanie(t, q+1, kon);
  }
}

void quick_sort(int *t, unsigned int n) {
    // TODO: implement
    szypkie_sortowanie(t, 0, n-1);

}

void heap_add(int *heap, int size, int value){
  heap[size] = value;
  heap_up(heap, size);
  size++;
}

void heap_up(int *heap, int index){
  int parent;
  if(index > 0){
    parent = floor((index - 1) / 2);
    if(heap[index] < heap[parent]){
      swap(&heap[index], &heap[parent]);
      heap_up(heap, parent);
    }
  }
}

int heap_poll(int *heap, int size){
  int value = heap[0];
  heap[0] = heap[size];
  heap_down(heap, 0, size);
  return value;
}

void heap_down(int *heap, int index, int size){
  int l = 2*index + 1;
  int r = 2*index + 2;
  if(l>=size) return;
  int arg;
  if(r >= size || heap[l] < heap[r]) arg = l;
  else arg = r;
  if(heap[arg] < heap[index]){
    swap(&heap[arg], &heap[index]);
    heap_down(heap, arg, size);
  }
}

void heap_sort(int *t, unsigned int n){
  int *heap = malloc(n * sizeof(*t));
  int size = 0;
  for(int i = 0; i < n; i++){
    heap_add(heap, size, t[i]);
    size++;
  }
  for(int i = 0; i < n; i++){
    size--;
    t[i] = heap_poll(heap, size);
}
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort};

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort"};

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin, end;
                double cpu_time_used;
                begin = clock();
                sort(t, n);
                end = clock();
                is_sorted(t, n);
                cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, cpu_time_used);
                free(t);
            }
        }
    }
    return 0;
}
