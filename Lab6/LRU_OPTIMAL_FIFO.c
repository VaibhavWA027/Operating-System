#include <stdio.h>

int n, f, i, j, k;
int in[100];
int p[50];
int hit = 0;
int pgfaultcnt = 0;

/* Function prototypes */
void getData(void);
void initialize(void);
int  isHit(int data);
int  getHitIndex(int data);
void dispPages(void);
void dispPgFaultCnt(void);
void fifo(void);
void optimal(void);
void lru(void);

/*------------------------------------------------------------*/
void getData(void)
{
    printf("\nEnter length of page reference sequence: ");
    scanf("%d", &n);

    printf("\nEnter the page reference sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &in[i]);

    printf("\nEnter number of frames: ");
    scanf("%d", &f);
}

/*------------------------------------------------------------*/
void initialize(void)
{
    pgfaultcnt = 0;
    for (i = 0; i < f; i++)
        p[i] = 9999;      /* 9999 indicates an empty frame */
}

/*------------------------------------------------------------*/
int isHit(int data)
{
    for (j = 0; j < f; j++)
    {
        if (p[j] == data)
            return 1;     /* Hit */
    }
    return 0;             /* Miss */
}

/*------------------------------------------------------------*/
int getHitIndex(int data)
{
    for (k = 0; k < f; k++)
    {
        if (p[k] == data)
            return k;
    }
    return -1;            /* Should never reach here if called after isHit */
}

/*------------------------------------------------------------*/
void dispPages(void)
{
    for (k = 0; k < f; k++)
    {
        if (p[k] != 9999)
            printf(" %d", p[k]);
    }
}

/*------------------------------------------------------------*/
void dispPgFaultCnt(void)
{
    printf("\nTotal number of page faults: %d", pgfaultcnt);
}

/*------------------------------------------------------------*/
void fifo(void)
{
    getData();      /* Read fresh input each time FIFO is chosen */
    initialize();

    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        /* If it is not a hit */
        if (!isHit(in[i]))
        {
            for (k = 0; k < f - 1; k++)
                p[k] = p[k + 1];

            p[f - 1] = in[i];
            pgfaultcnt++;
            dispPages();
        }
        else
        {
            printf("No page fault");
        }
    }
    dispPgFaultCnt();
}

/*------------------------------------------------------------*/
void optimal(void)
{
    initialize();
    int near[50];

    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (!isHit(in[i]))
        {
            for (j = 0; j < f; j++)
            {
                int pg = p[j];
                int found = 0;

                for (k = i; k < n; k++)
                {
                    if (pg == in[k])
                    {
                        near[j] = k;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    near[j] = 9999;
            }

            int max = -1;
            int repindex = 0;

            for (j = 0; j < f; j++)
            {
                if (near[j] > max)
                {
                    max = near[j];
                    repindex = j;
                }
            }

            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages();
        }
        else
        {
            printf("No page fault");
        }
    }
    dispPgFaultCnt();
}

/*------------------------------------------------------------*/
void lru(void)
{
    initialize();
    int least[50];

    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (!isHit(in[i]))
        {
            for (j = 0; j < f; j++)
            {
                int pg = p[j];
                int found = 0;

                for (k = i - 1; k >= 0; k--)
                {
                    if (pg == in[k])
                    {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    least[j] = -1;
            }

            int min = 9999;
            int repindex = 0;

            for (j = 0; j < f; j++)
            {
                if (least[j] < min)
                {
                    min = least[j];
                    repindex = j;
                }
            }

            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages();
        }
        else
        {
            printf("No page fault!");
        }
    }
    dispPgFaultCnt();
}

/*------------------------------------------------------------*/
int main(void)
{
    int choice;

    while (1)
    {
        printf("\n\nPage Replacement Algorithms\n");
        printf("1. Enter data\n2. FIFO\n3. Optimal\n4. LRU\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                getData();
                break;

            case 2:
                fifo();
                break;

            case 3:
                optimal();
                break;

            case 4:
                lru();
                break;

            case 5:
            default:
                return 0;
        }
    }
}
