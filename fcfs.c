#include <stdio.h>
#include <stdbool.h>

int main(){
    int n;
    int at[100],bt[100],ct[100],tat[100],wt[100];
    printf("Enter the number of processor to enter:");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        printf("\nEnter the arrival time for the process[%d] ",i+1);
        scanf("%d",&at[i]);
    }
    for(int i=0;i<n;i++){
        printf("\nEnter the bus time for the process[%d] ",i+1);
        scanf("%d",&bt[i]);
    }
    int sum=at[0];
    for(int i=0;i<n;i++){
        sum+=bt[i];
        ct[i]=sum;
    }

    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
    }


    for(int i=0;i<n;i++){
        wt[i]=tat[i]-bt[i];
    }
    for(int i=0;i<n;i++){
        printf("\n%d",ct[i]);
    }

    float TAT,WT;

    for(int i=0;i<n;i++){
        TAT+=tat[i];
        WT+=wt[i];



    }
    TAT=(float)TAT/n;
    WT=(float)WT/n;

    printf("\nThe avarage Tat=%.3f",TAT);
    printf("\nThe avarage WT=%.3f",WT);








}
