#include <stdio.h>

int search(int frames[], int f, int key)
{
    for(int i = 0; i < f; i++)
    {
        if(frames[i] == key)
            return 1;
    }
    return 0;
}

/* ---------------- FIFO ---------------- */

void fifo(int pages[], int n, int f)
{
    int frames[10], index = 0, faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n\n--- FIFO Page Replacement ---\n");

    for(int i = 0; i < n; i++)
    {
        if(!search(frames, f, pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        printf("\nPage %d --> ", pages[i]);

        for(int j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

/* ---------------- LRU ---------------- */

void lru(int pages[], int n, int f)
{
    int frames[10], time[10];
    int faults = 0, count = 0;

    for(int i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\n\n--- LRU Page Replacement ---\n");

    for(int i = 0; i < n; i++)
    {
        int flag = 0;

        for(int j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                count++;
                time[j] = count;
                flag = 1;
                break;
            }
        }

        if(flag == 0)
        {
            int pos = 0;

            for(int j = 1; j < f; j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            count++;
            frames[pos] = pages[i];
            time[pos] = count;
            faults++;
        }

        printf("\nPage %d --> ", pages[i]);

        for(int j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

/* ---------------- Optimal ---------------- */

void optimal(int pages[], int n, int f)
{
    int frames[10];
    int faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n\n--- Optimal Page Replacement ---\n");

    for(int i = 0; i < n; i++)
    {
        if(search(frames, f, pages[i]))
        {
            printf("\nPage %d --> ", pages[i]);

            for(int j = 0; j < f; j++)
            {
                if(frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }

            continue;
        }

        int pos = -1, farthest = i + 1;

        for(int j = 0; j < f; j++)
        {
            int k;

            for(k = i + 1; k < n; k++)
            {
                if(frames[j] == pages[k])
                {
                    if(k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                    break;
                }
            }

            if(k == n)
            {
                pos = j;
                break;
            }
        }

        if(pos == -1)
            pos = 0;

        frames[pos] = pages[i];
        faults++;

        printf("\nPage %d --> ", pages[i]);

        for(int j = 0; j < f; j++)
        {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

/* ---------------- Main Function ---------------- */

int main()
{
    int pages[50], n, f, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\nChoose Page Replacement Technique");
    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\n3. Optimal");
    printf("\n4. All");

    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            fifo(pages, n, f);
            break;

        case 2:
            lru(pages, n, f);
            break;

        case 3:
            optimal(pages, n, f);
            break;

        case 4:
            fifo(pages, n, f);
            lru(pages, n, f);
            optimal(pages, n, f);
            break;

        default:
            printf("Invalid Choice");
    }

    return 0;
}
