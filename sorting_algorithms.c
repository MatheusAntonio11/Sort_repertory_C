#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define tam 10000

void printArray(char* msg, int arr[], int n) {
    printf("%s: [ ", msg);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a[j] > a[j+1]) swap(&a[j], &a[j+1]);
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        int m = i;
        for (int j = i+1; j < n; j++) if (a[j] < a[m]) m = j;
        swap(&a[m], &a[i]);
    }
}

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int k = a[i], j = i-1;
        while (j >= 0 && a[j] > k) { a[j+1] = a[j]; j--; }
        a[j+1] = k;
    }
}

void quickSort(int a[], int L, int H) {
    if (L < H) {
        int p = a[H], i = L-1;
        for (int j = L; j < H; j++) if (a[j] < p) swap(&a[++i], &a[j]);
        swap(&a[i+1], &a[H]);
        int pi = i + 1;
        quickSort(a, L, pi - 1);
        quickSort(a, pi + 1, H);
    }
}

void mergeSort(int a[], int L, int R) {
    if (L < R) {
        int M = L + (R-L)/2;
        mergeSort(a, L, M); mergeSort(a, M+1, R);
        int n1 = M-L+1, n2 = R-M, Left[n1], Right[n2];
        for(int i=0; i<n1; i++) Left[i] = a[L+i];
        for(int j=0; j<n2; j++) Right[j] = a[M+1+j];
        int i=0, j=0, k=L;
        while(i<n1 && j<n2) a[k++] = (Left[i] <= Right[j]) ? Left[i++] : Right[j++];
        while(i<n1) a[k++] = Left[i++];
        while(j<n2) a[k++] = Right[j++];
    }
}

int main() {
    int n = tam, opcao, original[tam];
    srand(time(NULL));
    for(int i=0; i<n; i++) original[i] = rand() % 100;

    while(1) {
        printf("---------------------------");
        printf("Escolha a opcao de sort");
        printf("---------------------------");
        printf("\n1.Bubble\n2.Selection\n3.Insertion\n4.Quick\n5.Merge\n0.Sair\nEscolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n');
            continue;
        }

        if (opcao == 0) break;
        
        if (opcao < 0 || opcao > 5) {
            printf("\n------escolha invalida------.\n");
            continue;
        }

        int copia[tam]; 
        memcpy(copia, original, sizeof(original)); 
        
        printArray("Antes ", copia, n);
        clock_t t = clock();

        switch (opcao)
        {
            case 1: 
            bubbleSort(copia, n); 
                break;
            case 2:
                selectionSort(copia, n);
                    break;
            case 3: 
                insertionSort(copia, n); 
                    break;
            case 4: 
                quickSort(copia, 0, n-1); 
                    break;
            case 5:
                mergeSort(copia, 0, n-1); 
                    break;
        }
       
        t = clock() - t;
        printArray("Depois", copia, n);
        printf("Tempo: %.8f s\n", (double)t/CLOCKS_PER_SEC);
    }
    return 0;
}