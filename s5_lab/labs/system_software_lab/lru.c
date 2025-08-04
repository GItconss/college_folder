#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[100], frames[100], time[100];
    int n, f, i, j, flag, fault = 0, hit = 0, counter = 0, pos;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (i = 0; i < n; ++i) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; ++i) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; ++i) {
        flag = 0;

        // Check if page is already in frame (Hit)
        for (j = 0; j < f; ++j) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);

        // If not hit, do replacement (Fault)
        if (flag == 0) {
            // If there's still space
            for (j = 0; j < f; ++j) {
                if (frames[j] == -1) {
                    counter++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    fault++;

                    // Print frames
                    for (int k = 0; k < f; ++k) {
                        if (frames[k] != -1)
                            printf("%d ", frames[k]);
                        else
                            printf("- ");
                    }
                    printf("\tPage Fault\n");
                    goto next;
                }
            }

            // Find LRU and replace
            pos = findLRU(time, f);
            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            fault++;

            // Print frames
            for (j = 0; j < f; ++j)
                printf("%d ", frames[j]);
            printf("\tPage Fault\n");

        } else {
            hit++;
            for (j = 0; j < f; ++j)
                printf("%d ", frames[j]);
            printf("\tPage Hit\n");
        }

    next:;
    }

    printf("\nTotal Page Faults: %d\n", fault);
    printf("Total Page Hits: %d\n", hit);

    return 0;
}
