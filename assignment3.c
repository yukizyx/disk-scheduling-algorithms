#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUEST_NUM 20
#define MAX_POSITION 299

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

void SSTF(int head, int req[])
{
    // init variables
    int current_pos = head;
    int total = 0;
    int index = 0;
    int visited[REQUEST_NUM];
    int min = 9999999;
    int candidate = -1;
    int visit_seq[REQUEST_NUM];

    // populate visited array to 0(false)
    for (size_t i = 0; i < REQUEST_NUM; i++)
    {
        visited[i] = 0;
    }

    // main loop
    for (size_t i = 0; i < REQUEST_NUM; i++)
    {
        min = 9999999;
        // finding the minimum distance to head
        for (size_t j = 0; j < REQUEST_NUM; j++)
        {
            if (!visited[j] && min > distance(head, req[j]))
            {
                candidate = j;
                min = distance(head, req[j]);
            }
        }

        visited[candidate] = 1;
        visit_seq[index] = req[candidate];
        index += 1;
        total += distance(head, req[candidate]);
        head = req[candidate];
    }
    // print out the sequence of visiting
    for (size_t i = 0; i < REQUEST_NUM - 1; i++)
    {
        printf("%d, ", visit_seq[i]);
    }

    printf("%d\n", visit_seq[REQUEST_NUM - 1]);
    printf("\n");

    // print the total movements
    printf("SSTF - Total head movements = %d\n", total);
}

void SCAN(int head, int req[], int left)
{
    int index;
    int i;
    int total = 0;
    int visit[REQUEST_NUM];
    int visit_index = 0;

    // the start direction is left
    if (left == 1)
    {
        // find position (index) of head
        for (i = 0; i < REQUEST_NUM; i++)
        {
            if (head < req[i])
            {
                index = i;
                break;
            }
        }

        // move from head to the most left position
        for (i = index - 1; i >= 0; i--)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }

        // move from the most left position to 0
        total += distance(head, 0);
        head = 0;

        // move from 0 to the most right position
        for (i = index; i < REQUEST_NUM; i++)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }
    }
    // the start direction is right
    else
    {
        // find position (index) of head
        for (i = 0; i < REQUEST_NUM; i++)
        {
            if (head <= req[i])
            {
                index = i;
                break;
            }
        }

        // move from head to the most right position
        for (i = index; i < REQUEST_NUM; i++)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }

        // move from the most right position to max
        total += distance(head, MAX_POSITION);
        head = MAX_POSITION;

        // move from max to the most left position
        for (i = index - 1; i >= 0; i--)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }
    }

    // print the visit array
    for (i = 0; i < REQUEST_NUM - 1; i++)
    {
        printf("%d, ", visit[i]);
    }
    printf("%d\n", visit[REQUEST_NUM - 1]);
    printf("\n");

    // print the total movements
    printf("SCAN - Total head movements = %d\n", total);
}

void CSCAN(int head, int req[], int left)
{
    int index;
    int i;
    int total = 0;
    int visit[REQUEST_NUM];
    int visit_index = 0;

    // the start direction is left
    if (left == 1)
    {
        // find position (index) of head
        for (i = 0; i < REQUEST_NUM; i++)
        {
            if (head < req[i])
            {
                index = i;
                break;
            }
        }

        // move from head to the most left position
        for (i = index - 1; i >= 0; i--)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }

        // move from the most left position to 0
        total += distance(head, 0);
        head = 0;

        // big jump to max
        head = MAX_POSITION;
        total += distance(0, MAX_POSITION);

        // move from max to left
        for (i = REQUEST_NUM - 1; i >= index; i--)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }
    }
    // the start direction is right
    else
    {
        // find position (index) of head
        for (i = 0; i < REQUEST_NUM; i++)
        {
            if (head <= req[i])
            {
                index = i;
                break;
            }
        }

        // move from head to the most right position
        for (i = index; i < REQUEST_NUM; i++)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }

        // move from the most right position to max
        total += distance(head, MAX_POSITION);
        head = MAX_POSITION;

        // big jump to 0
        head = 0;
        total += distance(0, MAX_POSITION);

        // move from 0 to right
        for (i = 0; i < index; i++)
        {
            total += distance(head, req[i]);
            head = req[i];
            visit[visit_index] = head;
            visit_index++;
        }
    }

    // print the visit array
    for (i = 0; i < REQUEST_NUM - 1; i++)
    {
        printf("%d, ", visit[i]);
    }
    printf("%d\n", visit[REQUEST_NUM - 1]);
    printf("\n");

    // print the total movements
    printf("C-SCAN - Total head movements = %d\n", total);
}

void LOOK(int head, int req[], int left)
{
}

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

    // if is LEFT, then set the value to 1, if RIGHT than 0, other value will result a termination of program
    int left = -1;
    if (strcmp(str, "LEFT") == 0)
    {
        left = 1;
    }
    else if (strcmp(str, "RIGHT") == 0)
    {
        left = 0;
    }
    else
    {
        printf("Invalid 2nd arg, either 'LEFT' or 'RIGHT'");
        return -1;
    }

    // read the file and store the int to an array
    FILE *fptr = fopen("request.bin", "rb");

    int request[REQUEST_NUM];
    size_t num = fread(request, sizeof(int), REQUEST_NUM, fptr);

    fclose(fptr);

    // use bubble sort to sort request array
    int sorted_req[REQUEST_NUM];
    int temp;
    // copy array
    for (size_t i = 0; i < REQUEST_NUM; i++)
    {
        sorted_req[i] = request[i];
    }
    // inplace bubble sort
    for (size_t i = 0; i < REQUEST_NUM - 1; i++)
    {
        for (size_t j = 0; j < REQUEST_NUM - i - 1; j++)
        {
            if (sorted_req[j] > sorted_req[j + 1])
            {
                temp = sorted_req[j];
                sorted_req[j] = sorted_req[j + 1];
                sorted_req[j + 1] = temp;
            }
        }
    }

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
    printf("\n");
    SSTF(head, request);
    printf("\n");

    // SCAN
    printf("SCAN DISK SCHEDULING ALGORITHM\n");
    printf("\n");
    SCAN(head, sorted_req, left);
    printf("\n");

    // C - SCAN
    printf("C-SCAN DISK SCHEDULING ALGORITHM\n");
    printf("\n");
    CSCAN(head, sorted_req, left);
    printf("\n");

    // LOOK
    printf("LOOK DISK SCHEDULING ALGORITHM\n");

    // C - LOOK
    printf("C-LOOK DISK SCHEDULING ALGORITHM\n");

    return 0;
}