#include <stdio.h>

int main() {
    int frames, pages[100], temp[100];
    int i, j, k, pageFaults = 0, pageHits = 0, index = 0;
    int n, flag;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter length of reference string: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize all frames to -1 (empty)
    for (i = 0; i < frames; i++) {
        temp[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < n; i++) {
        flag = 0;

        // Check if page is already in a frame (Page Hit)
        for (j = 0; j < frames; j++) {
            if (temp[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        printf("%d\t", pages[i]);

        // Page Fault
        if (flag == 0) {
            temp[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;

            // Print frame contents
            for (k = 0; k < frames; k++) {
                if (temp[k] != -1)
                    printf("%d ", temp[k]);
                else
                    printf("- ");
            }
            printf("\tPage Fault\n");
        } 
        // Page Hit
        else {
            pageHits++;
            for (k = 0; k < frames; k++) {
                if (temp[k] != -1)
                    printf("%d ", temp[k]);
                else
                    printf("- ");
            }
            printf("\tPage Hit\n");
        }
    }

    printf("\nTotal Page Faults: %d", pageFaults);
    printf("\nTotal Page Hits: %d\n", pageHits);

    return 0;
}
