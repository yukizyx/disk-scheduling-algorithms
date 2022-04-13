#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUEST_NUM 20

int distance(int a, int b)
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        return b - a;
    }
}

void FCFS(int head, int req[])
{
    int i;
    int current = head;
    int total = 0;
    int visit[REQUEST_NUM];

    // visit order is the order of the request array
    for (i = 0; i < REQUEST_NUM; i++)
    {
        total += distance(head, req[i]);

        // change & record the num of next request
        head = req[i];
        visit[i] = head;
    }

    // print the visit array
    for (i = 0; i < REQUEST_NUM - 1; i++)
    {
        printf("%d, ", visit[i]);
    }
    printf("%d\n", visit[REQUEST_NUM - 1]);
    printf("\n");

    // print the total movements
    printf("FCFS - Total head movements = %d\n", total);
};

int main(int argc, const char *argv[])
{
    // handle 2 command line args
    // check the number of args
    if (argc != 3)
    {
        printf("Invalid number of input.");
        return -1;
    }

    // store 1st arg as int, 2nd arg as string
    int head = atoi(argv[1]);
    const char *str = argv[2];

    // read the file and store the int to an array
    FILE *fptr = fopen("request.bin", "rb");

    int request[REQUEST_NUM];
    size_t num = fread(request, sizeof(int), REQUEST_NUM, fptr);

    fclose(fptr);

    // print basic info
    printf("Total requests = %d\n", REQUEST_NUM);
    printf("Initial Head Position: %d\n", head);
    printf("Direction of Head: %s\n", str);
    printf("\n");

    // FCFS
    printf("FCFS DISK SCHEDULING ALGORITHM\n");
    printf("\n");

    FCFS(head, request);
    printf("\n");

    // SSTF
    printf("SSTF DISK SCHEDULING ALGORITHM\n");

    // SCAN
    printf("SCAN DISK SCHEDULING ALGORITHM\n");

    // C - SCAN
    printf("C-SCAN DISK SCHEDULING ALGORITHM\n");

    // LOOK
    printf("LOOK DISK SCHEDULING ALGORITHM\n");

    // C - LOOK
    printf("C-LOOK DISK SCHEDULING ALGORITHM\n");

    return 0;
}