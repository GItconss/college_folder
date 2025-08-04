#include <stdio.h>

int main() {
  int b_count, p_count;
  printf("Enter number of blocks, process: ");
  scanf("%d%d", &b_count, &p_count);

  int blocks[b_count], proc[p_count], in_block[p_count];
  printf("Enter size of each block\n");
  for (int i = 0; i < b_count; i++) scanf("%d", &blocks[i]);
  printf("Enter size of each process\n");
  for (int i = 0; i < p_count; i++) {
    scanf("%d", &proc[i]);    
    in_block[i] = -1;
  }

  for (int i = 0; i < p_count; i++) {
    int max_hole = -9999;
    int max_hole_pos = -1;
    for (int j = 0; j < b_count; j++) {
      if (in_block[i] != -1) break;
      int hole = blocks[j] - proc[i];
      if (hole && hole > max_hole) {
        max_hole = hole;
        max_hole_pos = j;
      }
    }
    if (max_hole_pos != -1) {
      blocks[max_hole_pos] -= proc[i];
      in_block[i] = max_hole_pos;
    }
  }

  printf("ProcessNo processSize blockNo\n");
  for (int i = 0; i < p_count; i++)
    printf("%9d %11d %7d\n", i, proc[i], in_block[i]);
  return 0;
}

/*
Enter number of blocks, process: 3 5
Enter size of each block
300
600
200
Enter size of each process
300
100
50
200
100
ProcessNo processSize blockNo
        0         300       1
        1         100       0
        2          50       1
        3         200       1
        4         100       0
*/