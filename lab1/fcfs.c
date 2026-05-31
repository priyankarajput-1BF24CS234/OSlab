#include <stdio.h>

int main(){

    int n,i;
    int at[20],bt[20],ct[20],tat[20],wt[20],rt[20];
    float avg_wt=0,avg_tat=0,avg_rt=0;

    printf("enter number of processes");
    scanf("%d",&n);

    printf("enter arrival time and burst time\n");

    for(int i=0;i<n;i++){
        printf("P%d AT:",i+1);
        scanf("%d",&at[i]);
        printf("P%d BT:",i+1);
        scanf("%d",&bt[i]);
    }

    ct[0]=bt[0]+at[0];

    for(int i=1;i<n;i++){
        if(ct[i-1]<at[i]){
            ct[i]=at[i]+bt[i];
        }
        else{
            ct[i]=ct[i-1]+bt[i];
        }
    }

    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]=wt[i];

        avg_wt+=wt[i];
        avg_tat+=tat[i];
        avg_rt+=rt[i];
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i=0;i<n;i++){
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d", i+1,at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage waiting time= %.2f",avg_wt/n);
    printf("\nAverage turnaround time= %.2f",avg_tat/n);
    printf("\nAverage response time= %.2f",avg_rt/n);

    return 0;
}
