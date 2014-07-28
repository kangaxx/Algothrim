#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define INT_DATA_LEN 10
#define INT_MAX_RANDOM (INT_DATA_LEN*10)
void CompareData(const int *before, const int *after, int ChangePos1, int ChangePos2, int Size = INT_DATA_LEN);
void CompareData2(const int *before, const int *after , int ChangePosBef, int ChangePosAft, int EndIdx);
string IntToSortName(int in)
{
    string Ret = "";
    switch (in)
    {
    case 1:
        Ret = "Insertion sort";
        break;
    case 2:
        Ret = "Selection sort";
        break;
    case 3:
        Ret = "Merge sort";
        break;
    case 4:
        Ret = "Heap sort";
        break;
    case 5:
        Ret = "Quick sort";
        break;
    case 6:
        Ret = "Bubble sort";
        break;
    case 7:
        Ret = "Shell sort";
        break;
    case 8:
        Ret = "Comb sort";
        break;
    case 9:
        Ret = "Counting sort";
        break;
    case 10:
        Ret = "Bucket sort";
        break;
    case 11:
        Ret = "Radix sort";
        break;

    default:
        throw("Sort type out of range , program error!");
        break;
    }
    return Ret;
}

void CreateSourceNum(int *in)
{
    srand((int)time(0));
    for(int i=0;i<INT_DATA_LEN;i++)
        *in++ = rand()%INT_MAX_RANDOM;
}



void CompareData(const int *before, const int *after, int ChangePos1,int ChangePos2, int Size)
{

    cout << "================== BEGIN =====================" << endl;
    for (int i=0;i<Size;i++)
    {
        cout << "Origin Data[" << i << "] is : " << (*before++) << (i==(ChangePos1)?"<=== NUM 1":"") <<(i==(ChangePos2)?"<=== NUM 2":"")<< ((i!=(ChangePos1) && i!=(ChangePos2))?"          ":"");
        cout<<" and new Data[" << i << "] is : " << (*after++) << (i==(ChangePos1)?"<=== NUM 2":"") <<(i==(ChangePos2)?"<=== NUM 1":"")<< ((i!=(ChangePos1) && i!=(ChangePos2))?"          ":"") ;
        cout << endl;
    }
    cout << "==================  END  =====================" << endl;
}

void CompareData2(const int *before, const int *after, int ChangePosBef, int ChangePosAft, int EndIdx)
{
    cout << "================== BEGIN =====================" << endl;
    for (int i=0;i<=EndIdx;i++)
    {
        cout << "Origin Data[" << i << "] is : " << (*before++) << (i==(ChangePosBef)?"<=== From":"         ");
        cout<<" and new Data[" << i << "] is : " << (*after++) << (i==(ChangePosAft)?"<===  To ":"         ") ;
        cout << endl;
    }
    cout << "==================  END  =====================" << endl;
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                        Insert Sort                                                        //
//                                                                                                                           //
//***************************************************************************************************************************//
void DoInsertingSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    int ForCompare[INT_DATA_LEN];
    for (int i=0;i<INT_DATA_LEN;i++)
        Temp[i] = in[i];
    //do sort
    for(int j = 1;j<INT_DATA_LEN;j++)
    {
        int t = j;
        while (t > 0 && Temp[t] < Temp[t-1])
        {
            for(int k = 0;k<INT_DATA_LEN;k++)
                ForCompare[k] = Temp[k];
            int Swap = Temp[t];
            Temp[t] = Temp[t-1];
            Temp[t-1] = Swap;
            t--;
            CompareData(ForCompare,Temp,t,t+1);
        }

    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                      Selection Sort                                                       //
//                                                                                                                           //
//***************************************************************************************************************************//

void DoSelectionSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    int ForCompare[INT_DATA_LEN];
    for (int i=0;i<INT_DATA_LEN;i++)
        Temp[i] = in[i];

    //do sort
    int i,j;
    int iMin;
    for(i=0;i<(INT_DATA_LEN-1);i++)
    {
        iMin = i;
        for(j=i+1;j<INT_DATA_LEN;j++)
        {
            if (Temp[iMin]>Temp[j])
                iMin = j;
        }
        if (Temp[iMin] != Temp[i])
        {
            for(int k = 0;k<INT_DATA_LEN;k++)
                ForCompare[k] = Temp[k];
            swap(Temp[iMin],Temp[i]);
            CompareData(ForCompare,Temp,iMin,i);
        }
    }
}


//***************************************************************************************************************************//
//                                                                                                                           //
//                                                       Merge Sort                                                          //
//                                                                                                                           //
//***************************************************************************************************************************//



void Merge(const int Source[],int Target[],int StartIdx,int EndIdx, int MidIdx)
{
    int i,j;
    int k;
    cout << "s = " << StartIdx << " ; e = " << EndIdx << " ; m = " << MidIdx << endl;
    for (i = StartIdx,j=MidIdx+1;StartIdx<= MidIdx&&j<=EndIdx;i++)
    {

        if (Source[StartIdx]<=Source[j])
        {
            Target[i]= Source[StartIdx++];
            CompareData2(Source,Target,(StartIdx-1),i,EndIdx);
        }
        else
        {
            Target[i]= Source[j++];
            CompareData2(Source,Target,(j-1),i,EndIdx);
        }

    }

    if (StartIdx <= MidIdx)
    {
        for (k = 0; k<= (MidIdx-StartIdx);k++)
        {
            Target[i+k] = Source[StartIdx+k];
            CompareData2(Source,Target,(StartIdx+k),i+k,EndIdx);
        }
    }

    if (j <= EndIdx)
    {
        for (k = 0;k<= (EndIdx-j);k++)
        {
            Target[i+k] = Source[j+k];
            CompareData2(Source,Target,(j+k),i+k,EndIdx);
        }
    }
}

void MergeSort(const int Source[],int Target[],int StartIndex,int EndIndex)
{
    int Temp[EndIndex];
    for (int i = 0; i <=EndIndex ; i++)
        Temp[i] = -1;
    if (StartIndex == EndIndex)
    {
        Target[StartIndex] = Source[StartIndex];
    }
    else
    {
        int MidIndex = (StartIndex+EndIndex)/2;
        MergeSort(Source,Temp,StartIndex,MidIndex);
        MergeSort(Source,Temp,MidIndex+1,EndIndex);
        Merge(Temp,Target,StartIndex,EndIndex,MidIndex);
    }
}

void DoMergeSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    for (int i=0;i<INT_DATA_LEN;i++)
        Temp[i] = in[i];

    MergeSort(in,Temp,0,(INT_DATA_LEN-1));
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Heap Sort                                                         //
//                                                                                                                           //
//***************************************************************************************************************************//

void HeapSort(const int Source[], int Target[])
{

}

void BuildHeap(const int Source[], int Target[] , int Size)
{
    int i = 0;
    int j;
    int ForCompare[INT_DATA_LEN];
    while (i < Size)
    {
        Target[i]=Source[i];
        for (int t = 0;t<=i ;t++)
        {
            ForCompare[t] = Target[t];
            cout << "[" << Target[t] << "]   ";

        }
        cout << endl ;
        j = i;
        while (j > 0 && Target[j] > Target[(j-1)/2])
        {
            for (int t = 0;t<=i ;t++)
                ForCompare[t] = Target[t];
            swap(Target[j],Target[(j-1)/2]);
            CompareData(ForCompare,Target,j,(j-1)/2,(i+1));
            j = (j-1)/2;
        }
        i++;
    }

}

void DoHeapSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    for (int i = 0; i<INT_DATA_LEN; i++)
        Temp[i] = in[i];
    for (int j=INT_DATA_LEN; j > 0; j--)
    {
        BuildHeap(Temp,Temp,j);
        swap(Temp[j-1],Temp[0]);
        cout << "============================ Swap Begin ============================" << endl;
        for (int x = 0 ; x < INT_DATA_LEN; x++)
            cout << "[" << Temp[x] << "]   ";
        cout << endl;
        cout << "============================ Swap  End  ============================" << endl;
    }
}


int main()
{

    while(true)
    {
        cout << "There are 11 types Algorithm can be choice :" << endl;

        cout << "1. Insertion sort" << endl;
        cout << "2. Selection sort" << endl;
        cout << "3. Merge sort" << endl;
        cout << "4. Heap sort" << endl;
        cout << "5. Quick sort" << endl;
        cout << "6. Bubble sort" << endl;
        cout << "7. Shell sort" << endl;
        cout << "8. Comb sort " << endl;
        cout << "9. Counting sort" << endl;
        cout << "a. Bucket sort" << endl;
        cout << "b. Radix sort" << endl;

        char t = 0;
        cout << "please input (1-9,a,b) : " << endl;
        int SortType = 0;
        while (true)
        {




            t = getchar();
            if (t == 10)
                continue;
            if (!((t > 48 && t < 58) || (t>96 && t<99)))
                cout << "Input num must in (1-9,a,b),please retry!" << endl;
            else
            {
                if (t<58)
                    SortType = t-48;
                else
                    SortType = t-87;
                break;
            }
        }
        cout << "Sort type is: " << IntToSortName(SortType) << " !" << endl;

        int temp[INT_DATA_LEN];
        CreateSourceNum(temp);
        for (int j = 0;j<INT_DATA_LEN;j++)
            cout << "Input Num [" << j << "] is : " << temp[j] << endl;
        switch (SortType) {
        case 1:
            DoInsertingSort(temp);
            break;
        case 2:
            DoSelectionSort(temp);
            break;
        case 3:
            DoMergeSort(temp);
            break;
        case 4:
            DoHeapSort(temp);
            break;
        default:
            break;
        }
    }
    return 0;
}

