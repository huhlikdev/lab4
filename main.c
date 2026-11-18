#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

// Ввод массива в формате [1, 2, 3]
int input_array(int arr[], int max_size) {
    char str[1000];
    printf("Vvedite massiv v formate [1, 2, 3]:\n");
    scanf(" %[^\n]", str);
    int count = 0;
    int i = 1; // Пропускаем первую скобку
    if (str[0] != '[') {
        printf("Oshibka: massiv dolzhen nachinatsya s '['\n");
        return -1;
    }
    while (str[i] != '\0' && str[i] != ']') {
        // Пропускаем пробелы и запятые
        while (str[i] == ' ' || str[i] == ',') {
            i++;
        }
        if (str[i] == ']' || str[i] == '\0') break;
        int num = 0;
        int sign = 1;
        if (str[i] == '-') {
            sign = -1;
            i++;
        }
        // Собираем число
        while (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
            i++;
        }
        if (count >= max_size) {
            printf("Oshibka: slishkom mnogo elementov!\n");
            return -1;
        }
        arr[count] = num * sign;
        count++;
    }
    if (str[i] != ']') {
        printf("Oshibka: massiv dolzhen zakonchivatsya ']'\n");
        return -1;
    }
    return count;
}

// Вывод массива с динамической шириной поля
void print_array(int arr[], int size, char flag) {
    if (flag == 'f') return; // Если флаг 'f', ничего не выводим
    if (size == 0) return;
    // Ищем максимальную длину числа
    int max_len = 0;
    for (int i = 0; i < size; i++) {
        char buf[50];
        sprintf(buf, "%d", arr[i]);
        int len = strlen(buf);
        if (len > max_len) {
            max_len = len;
        }
    }
    int width = max_len + 1; // Ширина поля по формуле
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%*d", width, arr[i]); // "%*d" - динамическая ширина
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

void quick_sort(int arr[], int low, int high, int size, char flag) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        if (flag == 't') {
            printf("Razdelenie (pivot=%d): ", pivot);
            print_array(arr, size, flag);
        }
        quick_sort(arr, low, pi - 1, size, flag);
        quick_sort(arr, pi + 1, high, size, flag);
    }
}


int main() {
    int choice;
    while (1) {
        printf("\n--- LABORATORNAYA RABOTA N4 ---\n");
        printf("1. Funkciya Akkermana\n");
        printf("2. Sortirovka puzyr'kom\n");
        printf("3. Sortirovka vstavkami\n");
        printf("4. Bystraya sortirovka\n");
        printf("0. Vyhod\n");
        printf("Vyberite punkt: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Oshibka vvoda! Vvedite chislo.\n");
            while (getchar() != '\n'); // Очистка буфера
            continue;
        }
        switch (choice) {
            case 1: {
                int m, n;
                printf("Vvedite m: ");
                if (scanf("%d", &m) != 1 || m < 0) {
                    printf("Oshibka vvoda m!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("Vvedite n: ");
                if (scanf("%d", &n) != 1 || n < 0) {
                    printf("Oshibka vvoda n!\n");
                    while (getchar() != '\n');
                    break;
                }
                printf("A(%d, %d) = %d\n", m, n, ackermann(m, n));
                break;
            }

            case 2: {
                int arr[100];
                int n = input_array(arr, 100); 
                if (n == -1) break;             
                printf("Ishodnyy massiv:\n");
                print_array(arr, n, 't'); 
                
                char flag;
                printf("Vyvesti promezhutochnye shagi? (t/f): ");
                scanf(" %c", &flag); 
                
                // Пузырек
                for (int i = 0; i < n - 1; i++) {
                    int swapped = 0;
                    for (int j = 0; j < n - 1 - i; j++) {
                        if (arr[j] > arr[j + 1]) {
                            int temp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = temp;
                            swapped = 1;
                        }
                    }
                    if (flag == 't') {
                        printf("Prohod %d: ", i + 1);
                        print_array(arr, n, flag);
                    }
                    if (!swapped) break;
                }
                printf("Otsortirovannyy massiv:\n");
                print_array(arr, n, 't');
                break;
            }

            case 3: {
                int arr[100];
                int n = input_array(arr, 100); 
                if (n == -1) break;
                printf("Ishodnyy massiv:\n");
                print_array(arr, n, 't'); 
                
                char flag;
                printf("Vyvesti promezhutochnye shagi? (t/f): ");
                scanf(" %c", &flag); 
                
                // Вставки
                for (int i = 1; i < n; i++) {
                    int key = arr[i];
                    int j = i - 1;
                    while (j >= 0 && arr[j] > key) {
                        arr[j + 1] = arr[j];
                        j = j - 1;
                    }
                    arr[j + 1] = key;
                    
                    if (flag == 't') {
                        printf("Vstavka %d: ", i);
                        print_array(arr, n, flag);
                    }
                }
                
                printf("Otsortirovannyy massiv:\n");
                print_array(arr, n, 't');
                break;
            }
            
            case 4: {
                int arr[100];
                int n = input_array(arr, 100); 
                if (n == -1) break;
                
                printf("Ishodnyy massiv:\n");
                print_array(arr, n, 't'); 
                
                char flag;
                printf("Vyvesti promezhutochnye shagi? (t/f): ");
                scanf(" %c", &flag); 
                
                quick_sort(arr, 0, n - 1, n, flag);
                
                printf("Otsortirovannyy massiv:\n");
                print_array(arr, n, 't');
                break;
            }
            
            case 0: {
                printf("Vyhod...\n");
                return 0;
            }
            default: {
                printf("Nevernyy punkt menu!\n");
            }
        }
    }
    return 0;
}