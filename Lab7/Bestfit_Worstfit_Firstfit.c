#include <stdio.h>

#define MAX 25

/* Function prototypes */
void firstFit(int blocks[], int nb, int files[], int nf);
void worstFit(int blocks[], int nb, int files[], int nf);
void bestFit(int blocks[], int nb, int files[], int nf);

/*------------------------------------------------------------*/
int main(void)
{
    int blocks[MAX], files[MAX];
    int nb, nf;

    printf("Memory Management Schemes\n\n");

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);

    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (int i = 0; i < nb; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("\nEnter the size of the files:\n");
    for (int i = 0; i < nf; i++)
    {
        printf("File %d: ", i + 1);
        scanf("%d", &files[i]);
    }

    printf("\nMemory Management Scheme - First Fit\n");
    firstFit(blocks, nb, files, nf);

    printf("\n\nMemory Management Scheme - Worst Fit\n");
    worstFit(blocks, nb, files, nf);

    printf("\n\nMemory Management Scheme - Best Fit\n");
    bestFit(blocks, nb, files, nf);

    return 0;
}

/*------------------------------------------------------------*/
void firstFit(int blocks[], int nb, int files[], int nf)
{
    int blockFlag[MAX] = {0};
    int fileBlock[MAX]  = {0};
    int frag[MAX];

    for (int i = 0; i < nf; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            if (!blockFlag[j] && blocks[j] >= files[i])
            {
                fileBlock[i] = j;
                blockFlag[j] = 1;
                frag[i] = blocks[j] - files[i];
                break;
            }
        }
    }

    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (int i = 0; i < nf; i++)
    {
        int bIdx = fileBlock[i];
        printf("\n%d\t\t%d\t\t", i + 1, files[i]);
        if (blockFlag[bIdx])
            printf("%d\t\t%d\t\t%d", bIdx + 1, blocks[bIdx], frag[i]);
        else
            printf("Not Allocated");
    }
}

/*------------------------------------------------------------*/
void worstFit(int blocks[], int nb, int files[], int nf)
{
    int blockFlag[MAX] = {0};
    int fileBlock[MAX]  = {0};
    int frag[MAX];

    for (int i = 0; i < nf; i++)
    {
        int worstIdx = -1;
        int maxFrag  = -1;

        for (int j = 0; j < nb; j++)
        {
            if (!blockFlag[j])
            {
                int temp = blocks[j] - files[i];
                if (temp >= 0 && temp > maxFrag)
                {
                    worstIdx = j;
                    maxFrag  = temp;
                }
            }
        }

        if (worstIdx != -1)
        {
            fileBlock[i]   = worstIdx;
            blockFlag[worstIdx] = 1;
            frag[i]        = maxFrag;
        }
    }

    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (int i = 0; i < nf; i++)
    {
        int bIdx = fileBlock[i];
        printf("\n%d\t\t%d\t\t", i + 1, files[i]);
        if (blockFlag[bIdx])
            printf("%d\t\t%d\t\t%d", bIdx + 1, blocks[bIdx], frag[i]);
        else
            printf("Not Allocated");
    }
}

/*------------------------------------------------------------*/
void bestFit(int blocks[], int nb, int files[], int nf)
{
    int blockFlag[MAX] = {0};
    int fileBlock[MAX]  = {0};
    int frag[MAX];

    for (int i = 0; i < nf; i++)
    {
        int bestIdx  = -1;
        int minFrag  = 100000;

        for (int j = 0; j < nb; j++)
        {
            if (!blockFlag[j])
            {
                int temp = blocks[j] - files[i];
                if (temp >= 0 && temp < minFrag)
                {
                    bestIdx = j;
                    minFrag = temp;
                }
            }
        }

        if (bestIdx != -1)
        {
            fileBlock[i]   = bestIdx;
            blockFlag[bestIdx] = 1;
            frag[i]        = minFrag;
        }
    }

    printf("File_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragment");
    for (int i = 0; i < nf; i++)
    {
        int bIdx = fileBlock[i];
        printf("\n%d\t\t%d\t\t", i + 1, files[i]);
        if (blockFlag[bIdx])
            printf("%d\t\t%d\t\t%d", bIdx + 1, blocks[bIdx], frag[i]);
        else
            printf("Not Allocated");
    }
}
