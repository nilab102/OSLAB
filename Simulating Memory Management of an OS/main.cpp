#include<stdio.h>

#include<conio.h>

#define max 25

void worstfit(int nholes,int nrequests,int holes[],int requests[]){
    int assignedhole[max],ff[max],i,j,IF[max],highest=0;
    for(i=1;i<=nrequests;i++)

    {

        for(j=1;j<=nholes;j++)

        {

            if(assignedhole[j]!=-1 && highest<(holes[j]-requests[i])) //if bf[j] is not allocated

            {

                        ff[i]=j;

                        highest=(holes[j]-requests[i]);
            }

        }

        IF[i]=highest;

        assignedhole[ff[i]]=-1;

        highest=0;

    }

    printf("\nFile_no  \tFile_size  \tBlock_no  \tBlock_size  \tFragment");

    for(i=1;i<=nrequests;i++)

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,requests[i],ff[i],holes[ff[i]],IF[i]);

}
void bestfit(int nholes,int nrequests,int holes[],int requests[]){

    int assignedhole[max],ff[max],i,j,IF[max],lowest=10000;
    for(i=1;i<=nrequests;i++)

    {

        for(j=1;j<=nholes;j++)

        {

            if(assignedhole[j]!=-1 && (lowest>(holes[j]-requests[i])))

            {

                        ff[i]=j;

                        lowest=(holes[j]-requests[i]);



            }

        }

        IF[i]=lowest;

        assignedhole[ff[i]]=-1;

        lowest=10000;

    }

    printf("\nFile_no  \tFile_size  \tBlock_no  \tBlock_size  \tFragment");

    for(i=1;i<=nrequests && ff[i]!=0;i++)

        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,requests[i],ff[i],holes[ff[i]],IF[i]);

}
void firstfit(int nholes,int nrequests,int holes[],int requests[]){

    int assignedhole[max],ff[max],i,j,temp,IF[max],external_f=0,countassiggnedrequests=0;
    for(i=1;i<=nrequests;i++)

    {

        for(j=1;j<=nholes;j++)

        {

            if(assignedhole[j]!=-1)//hole assign kora naki check kortesi

            {

                temp=holes[j]-requests[i];//holes - request

                if(temp>=0)

                {

                    ff[i]=j;//ff r index= request and value hoitase hole ;mane ek numbep process kon hole e rakhsi

                    break;

                }

            }

        }

        IF[i]=temp;// internal fraggmentation

        assignedhole[ff[i]]=-1; //jei sob hol e value rakkha hoise oigula mark korlam

    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragment");

    for(i=1;i<=nrequests;i++)
    {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,requests[i],ff[i],holes[ff[i]],IF[i]);
        if(assignedhole[ff[i]]!=-1){

            external_f=external_f+holes[ff[i]];
        }

    }
    printf("\nExternal Fragmentation %d\n",external_f);

}


int main()

{
    int holes[max],requests[max],i,j,nholes,nrequests;

    printf("\nEnter the number of holes:");

    scanf("%d",&nholes);

    printf("Enter the number of requests:");

    scanf("%d",&nrequests);

    printf("\nEnter the size of the holes:-\n");

    for(i=1;i<=nholes;i++)

    {

        printf("hole %d:",i);

        scanf("%d",&holes[i]);

    }

    printf("Enter the size of the requests:-\n");

    for(i=1;i<=nrequests;i++)

    {

        printf("request %d:",i);

        scanf("%d",&requests[i]);

    }
    printf("\nBestfit:\n");
    bestfit(nholes,nrequests,holes,requests);
    printf("\nfirststfit:\n");
    firstfit(nholes,nrequests,holes,requests);
    printf("\nWorstfit:\n");
    worstfit(nholes,nrequests,holes,requests);
/*
 * 4 3 5 8 4 10 1 4 7
 */

}