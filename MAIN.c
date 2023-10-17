#include<stdio.h>
#include<stdlib.h>
struct pcb
{
int arrivaltime;
int bursttime;
int priority;
}*p;
int main(int argc , char *argv[])
{
printf("Please enter one of Number for Simulation\n");  //Menu for which algo to be used;
printf("1.First-Come First-Served\n");
printf("2.Shortest Job First\n");
printf("3.Round Robin Scheduling\n");
printf("4.Priority Scheduling\n");
printf("5.Shortest Remaining Time First\n");
printf("6.Longest remaining time first\n");
p=malloc(sizeof(struct pcb)*2);
FILE *fp=fopen("Test.txt","r");
if(fp==NULL)
{
printf("File not opened\n");
}
else
{
printf("File Opened Successfully\n");
}
char s[2];                                        // code to read file and save in char array;
int count=0;
int count1=2;
int count2=0,j,i,t;
char ch;
do {
        ch = fgetc(fp);
        s[count]=ch;
        if(count%6==0)
        {
          p[count2].arrivaltime=ch-'0';
        }
        else if(count%6==2)
        {
          p[count2].bursttime=ch-'0';
        }
        else if(count%6==4)
        {
          p[count2].priority=ch-'0';
          count2++;
          count1++;
          p=realloc(p,count1*sizeof(struct pcb));
        }
        count++;
    } while (ch != EOF);
    int choice=0;
    scanf("%d",&choice);
    for (i=0; i<count2-1; i++){
     for (j=i+1; j<count2; j++){
        if (p[i].arrivaltime > p[j].arrivaltime){
            t = p[i].arrivaltime;
            p[i].arrivaltime = p[j].arrivaltime;
            p[j].arrivaltime = t;
            t = p[i].bursttime;
            p[i].bursttime = p[j].bursttime;
            p[j].bursttime = t;
            t=p[i].priority;
            p[i].priority=p[j].priority;
            p[j].priority=t;
         }
      }
   }
   for(i=0;i<count2;i++)
   {
       printf("%d %d %d\n",p[i].arrivaltime,p[i].bursttime,p[i].priority);
   }
    if(choice==1)
    {
        printf("1.First-Come First-Served\n");
        int  ft[count2],tat[count2],wt[count2];
        int sum=0;
        printf("Gantt Chart\n");
        for(i=0;i<count2;i++)
        {
            
            for(j=0;j<p[i].arrivaltime-sum;j++)
            {
                printf(" e");
            }
            if(p[i].arrivaltime>sum)
            {
                sum+=p[i].arrivaltime;
            }
            sum+=p[i].bursttime;
            ft[i]=sum;
            for(j=0;j<p[i].bursttime;j++)
            {
                printf(" P%d",i+1);
            }
        }
        printf("\n");
        for(i=0;i<count2;i++)
        {
            tat[i]=ft[i]-p[i].arrivaltime;
            wt[i]=tat[i]-p[i].bursttime;
        }
        printf("Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for(int i=0; i<count2; i++)
        {
        printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",p[i].priority,p[i].arrivaltime,p[i].bursttime,ft[i],tat[i],wt[i]);
        }
        float sum1=0;
        float sum2=0;
        for(i=0;i<count2;i++)
        {
            sum1+=tat[i];
            sum2+=wt[i];
        }
        printf("Average Turn Around Time is: %.2f\n",sum1/count2);
        printf("Average Waiting Time is: %.2f\n",sum2/count2);
    }
    else if(choice==2)
    {
        printf("2.Shortest Job First\n");
        int rt[count2];
        for(i=0;i<count2;i++)
        {
            rt[i]=p[i].bursttime;
        }
        int com=0;
        int ti=0;
        int s=0;
        int finisht;
        int check=0;
        int minm=1000;
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while(com!=count2)
        {
            for (j = 0; j < count2; j++) {
            if((p[j].arrivaltime <= ti) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                s = j;
                check = 1;
            }
            }
            if(check==0)
            {
                ti++;
                printf(" e");
                continue;
            }
            rt[s]=0;
            minm=rt[s];
            if (minm == 0)
            minm=1000;
            if (rt[s] == 0)
            {
            for(int k=0;k<p[s].bursttime;k++)
            {
                printf(" P%d",s+1);
            }
            ti+=p[s].bursttime;
            com++;
            check=0;
            ft[s]=ti;
            wt[s] = ft[s]-p[s].arrivaltime-p[s].bursttime;
            if (wt[s] < 0)
                wt[s] = 0;
            }
        }
        for(i=0;i<count2;i++)
        {
            tat[i]=ft[i]-p[i].arrivaltime;
        }
        printf("\n");
        printf("Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for(int i=0; i<count2; i++)
        {
        printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",p[i].priority,p[i].arrivaltime,p[i].bursttime,ft[i],tat[i],wt[i]);
        }
        float sum1=0;
        float sum2=0;
        for(i=0;i<count2;i++)
        {
            sum1+=tat[i];
            sum2+=wt[i];
        }
        printf("Average Turn Around Time is: %.2f\n",sum1/count2);
        printf("Average Waiting Time is: %.2f\n",sum2/count2);
    }
    else if(choice==3)
    {
        printf("3.Round Robin Scheduling\n");
        printf("Please enter time quantum\n");
        int qt=0;
        scanf("%d",&qt);
        int com=0;
        int ct=0;
        int check;
        int ft[count2];
        int wt[count2];
        int tat[count2];
        int rt[count2];
        for(i=0;i<count2;i++)
        {
            rt[i]=p[i].bursttime;
        }
        while(com!=count2)
        {
            check=0;
            for(int i=0;i<count2;i++)
            {
                if(p[i].arrivaltime<=ct && rt[i] > 0)
                {
                if(rt[i]<=qt)
                {
                    com++;
                    ct+=rt[i];
                    ft[i]=ct;
                    tat[i]=ft[i]-p[i].arrivaltime;
                    wt[i] = tat[i]-p[i].bursttime;
                    for(j=0;j<rt[i];j++)
                    {
                        printf(" P%d",i+1);
                    }
                    rt[i]= 0;
                }
                else
                {
                    ct+=qt;
                    for(j=0;j<qt;j++)
                    {
                        printf(" P%d",i+1);
                    }
                    rt[i]-=qt;
                }
                check=1;
        }
        }
        if(check == 0)
        {
            ct++;
            printf(" e");
        }
        }
        for(i=0;i<count2;i++)
        {
            tat[i]=ft[i]-p[i].arrivaltime;
        }
        printf("\n");
        printf("Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for(int i=0; i<count2; i++)
        {
        printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",p[i].priority,p[i].arrivaltime,p[i].bursttime,ft[i],tat[i],wt[i]);
        }
        float sum1=0;
        float sum2=0;
        for(i=0;i<count2;i++)
        {
            sum1+=tat[i];
            sum2+=wt[i];
        }
        printf("Average Turn Around Time is: %.2f\n",sum1/count2);
        printf("Average Waiting Time is: %.2f\n",sum2/count2);
    }
    else if(choice==4)
    {
        printf("4.Priority Scheduling\n");
    }
    else if(choice==5)
    {
        printf("5.Shortest Remaining Time First\n");
        int rt[count2];
        for(i=0;i<count2;i++)
        {
            rt[i]=p[i].bursttime;
        }
        int com=0;
        int ti=0;
        int s=0;
        int finisht;
        int check=0;
        int minm=1000;
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while(com!=count2)
        {
            for (j = 0; j < count2; j++) {
            if((p[j].arrivaltime <= ti) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                s = j;
                check = 1;
            }
            }
            if(check==0)
            {
                ti++;
                printf(" e");
                continue;
            }
            rt[s]--;
            printf(" P%d",s+1);
            minm=rt[s];
            if (minm == 0)
            minm =1000;
            if (rt[s] == 0) {
            com++;
            check=0;
            ft[s]=ti+1;
            wt[s] = ft[s]-p[s].arrivaltime-p[s].bursttime;
            if (wt[s] < 0)
                wt[s] = 0;
            }
        ti++;
        }
        for(i=0;i<count2;i++)
        {
            tat[i]=ft[i]-p[i].arrivaltime;
        }
        printf("\n");
        printf("Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for(int i=0; i<count2; i++)
        {
        printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",p[i].priority,p[i].arrivaltime,p[i].bursttime,ft[i],tat[i],wt[i]);
        }
        float sum1=0;
        float sum2=0;
        for(i=0;i<count2;i++)
        {
            sum1+=tat[i];
            sum2+=wt[i];
        }
        printf("Average Turn Around Time is: %.2f\n",sum1/count2);
        printf("Average Waiting Time is: %.2f\n",sum2/count2);
    }
    else if(choice==6)
    {
     printf("6.Longest remaining time first\n"); 
        int rt[count2];
        for(i=0;i<count2;i++)
        {
            rt[i]=p[i].bursttime;
        }
        int com=0;
        int ti=0;
        int s=0;
        int finisht;
        int check=0;
        int maxm=0;
        int wt[count2];
        int tat[count2];
        int ft[count2];
        while(com!=count2)
        {
            for (j = 0; j < count2; j++) {
            if((p[j].arrivaltime <= ti) &&
            (rt[j] >= maxm) && rt[j] > 0) {
                maxm = rt[j];
                s = j;
                check = 1;
            }
            }
            if(check==0)
            {
                ti++;
                printf(" e");
                continue;
            }
            rt[s]--;
            printf(" P%d",s+1);
            maxm=rt[s];
            if (rt[s] == 0) {
            com++;
            check=0;
            ft[s]=ti+1;
            wt[s] = ft[s]-p[s].arrivaltime-p[s].bursttime;
            if (wt[s] < 0)
                wt[s] = 0;
            }
        ti++;
        }
        for(i=0;i<count2;i++)
        {
            tat[i]=ft[i]-p[i].arrivaltime;
        }
        printf("\n");
        printf("Priority\tArraival Time\tBurst Time\tFinish Time\tTurn Around\tWaiting time\n");
        for(int i=0; i<count2; i++)
        {
        printf("   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\t\t   %d\n",p[i].priority,p[i].arrivaltime,p[i].bursttime,ft[i],tat[i],wt[i]);
        }
        float sum1=0;
        float sum2=0;
        for(i=0;i<count2;i++)
        {
            sum1+=tat[i];
            sum2+=wt[i];
        }
        printf("Average Turn Around Time is: %.2f\n",sum1/count2);
        printf("Average Waiting Time is: %.2f\n",sum2/count2);
    }
    else
    {
        printf("You entered wrong number\n");
    }
return 0;
}
