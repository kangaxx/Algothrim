#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
#define INT_DATA_LEN 10
#define INT_MAX_RANDOM (INT_DATA_LEN*10)
#define INT_BUCKET_SIZE 10
const int CountOfBucket = INT_MAX_RANDOM / INT_BUCKET_SIZE;

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
    for (int i=0;i<EndIdx;i++)
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
            swap(Temp[t],Temp[t-1]);
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
            CompareData2(Source,Target,(StartIdx-1),i,EndIdx+1);
        }
        else
        {
            Target[i]= Source[j++];
            CompareData2(Source,Target,(j-1),i,EndIdx+1);
        }

    }

    if (StartIdx <= MidIdx)
    {
        for (k = 0; k<= (MidIdx-StartIdx);k++)
        {
            Target[i+k] = Source[StartIdx+k];
            CompareData2(Source,Target,(StartIdx+k),i+k,EndIdx+1);
        }
    }

    if (j <= EndIdx)
    {
        for (k = 0;k<= (EndIdx-j);k++)
        {
            Target[i+k] = Source[j+k];
            CompareData2(Source,Target,(j+k),i+k,EndIdx+1);
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


//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Quick Sort                                                        //
//                                                                                                                           //
//***************************************************************************************************************************//
int Parition(int Target[],int BeginIdx,int EndIdx)
{
    int i = BeginIdx;
    int r = Target[EndIdx];
    int Compare[INT_DATA_LEN];
    for (int j = BeginIdx;j<EndIdx;j++)
    {
        if (Target[j] < r)
        {

            if (i != j)
            {
                for (int k = 0;k<=j;k++)
                    Compare[k]=Target[k];
                swap(Target[i],Target[j]);
                CompareData(Compare,Target,i,j,j+1);
            }
            else
            {
                cout << "============================ i Equal j ============================" << endl;
                cout << "i is :[" << i << "] and j is :[" << j << "]" << endl;
                for (int l=0;l<=j;l++)
                    cout << "Data[" << l<< "] is : [" << Target[l] << "]" << endl;
                cout << "============================ i Equal j ============================" << endl;
            }
            i++;
            cout << "i is " << i << " and j is " << j << endl;
        }

    }
    for (int k = 0;k<=EndIdx;k++)
        Compare[k]=Target[k];
    swap(Target[i],Target[EndIdx]);
    CompareData(Compare,Target,i,EndIdx,EndIdx+1);
    return i;
}



//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Quick   Sort                                                      //
//                                                                                                                           //
//***************************************************************************************************************************//


void QuickSort(const int *in,int Target[],int BeginIdx, int EndIdx)
{
    cout << "bg is : " << BeginIdx << " and ed is : " << EndIdx << endl;
    if (BeginIdx < EndIdx)
    {

        int t = Parition(Target,BeginIdx,EndIdx);
        cout << "t is :[" << t << "]" << endl;
        QuickSort(in,Target,BeginIdx,t-1);
        QuickSort(in,Target,t+1,EndIdx);
    }
}

void DoQuickSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    for (int i = 0;i < INT_DATA_LEN;i++)
        Temp[i] = in[i];
    QuickSort(in,Temp,0,(INT_DATA_LEN-1));
    cout << "The finial int list is : " << endl;
    for (int j = 0; j < INT_DATA_LEN;j++)
        cout << "Data[" << j << "] : " << Temp[j] << endl;
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Bubble  Sort                                                      //
//                                                                                                                           //
//***************************************************************************************************************************//

void DoBubbleSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    for (int k = 0;k< INT_DATA_LEN;k++)
        Temp[k] = in[k];
    int Compare[INT_DATA_LEN];
    int isContinue = 1;
    for (int i = 0; i<INT_DATA_LEN & isContinue;i++)
    {
        isContinue = 0;

        for (int j = 0; j < (INT_DATA_LEN-i-1);j++)
            if (Temp[j]> Temp[j+1])
            {
                isContinue = 1;
                for(int x = 0; x < INT_DATA_LEN; x++)
                    Compare[x] = Temp[x];
                swap(Temp[j],Temp[j+1]);
                CompareData(Compare,Temp,j,j+1,INT_DATA_LEN);
            }

    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Shell   Sort                                                      //
//                           use 2^k-1 (1,3,7,15....),will got n^(3/2) in the Worst-case time complexity                     //
//***************************************************************************************************************************//


void DoShellSort(const int *in)
{
    int gap;
    int Temp[INT_DATA_LEN];
    int Compare[INT_DATA_LEN];
    for (int i = 0; i< INT_DATA_LEN;i++)
        Temp[i] = in[i];
    for (gap = INT_DATA_LEN; gap > 0; gap--)
    {
        int iT = gap;
        while (iT % 2 == 0)
            iT /= 2;
        if (iT != 1)
            continue;
        for (int j = gap; j < INT_DATA_LEN; j++)//从数组第gap个元素开始
            if (Temp[j] < Temp[j - gap])//每个元素与自己组内的数据进行直接插入排序
            {
                int temp = Temp[j];
                int k = j - gap;
                while (k >= 0 && Temp[k] > temp)
                {
                    for (int t=0;t<INT_DATA_LEN;t++)
                        Compare[t] = Temp[t];
                    Temp[k + gap] = Temp[k];
                    k -= gap;
                }

                Temp[k + gap] = temp;
                cout << k << " " << gap << endl;
                CompareData(Compare,Temp,k+gap,k+2*gap,INT_DATA_LEN);

            }
    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Comb    Sort                                                      //
//                                                                                                                           //
//***************************************************************************************************************************//

void DoCombSort(const int *in)
{
    float Shrink = 1.3f;

    bool swapped = false;
    int Temp[INT_DATA_LEN];
    for (int i = 0;i<INT_DATA_LEN;i++)
        Temp[i] = in[i];
    int Compare[INT_DATA_LEN];
    int gap=INT_DATA_LEN;
    while ((gap>1) || swapped)
    {
        if (gap>1)
            gap =  int((float)gap/Shrink);
        swapped = false;
        for (int i = 0; i+gap<INT_DATA_LEN;i++)
        {
            if (Temp[i]>Temp[i+gap])
            {
                for (int j = 0; j<INT_DATA_LEN;j++)
                    Compare[j] = Temp[j];
                swap(Temp[i],Temp[i+gap]);
                CompareData(Compare,Temp,i,i+gap,INT_DATA_LEN);
                swapped = true;
            }
        }
    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Counting    Sort                                                  //
//                                                                                                                           //
//***************************************************************************************************************************//
void MakeCounter(const int *in,int Counter[])
{
    for (int i = 0; i<INT_DATA_LEN;i++)
        Counter[in[i]]++;
    for (int j = 1;j<INT_MAX_RANDOM;j++)
        Counter[j] += Counter[j-1];
    cout << "==================  Show Counter =======================" << endl;
    for (int k = 0;k<INT_MAX_RANDOM;k++)
    {
        if ((k == 0 && Counter[k] > 0) || (Counter[k]> Counter[k-1]))
            cout << "Counter[" << k << "] : " << Counter[k] << endl;
    }
    cout << "==================  Show Counter =======================" << endl;
}


void DoCountingSort(const int *in)
{
    int Temp[INT_DATA_LEN];
    for (int k = 0 ; k<INT_DATA_LEN;k++)
        Temp[k] = -1;
    int Counter[INT_MAX_RANDOM]={0};
    MakeCounter(in,Counter);
    for (int i = 0; i<INT_DATA_LEN;i++)
    {
        Temp[Counter[in[i]]-1] = in[i];
        CompareData2(in,Temp,i,Counter[in[i]]-1,INT_DATA_LEN);
        Counter[in[i]]--;
    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Bucket     Sort                                                   //
//                                                                                                                           //
//***************************************************************************************************************************//
void InitBuckets(int Buckets[CountOfBucket][INT_BUCKET_SIZE])
{
    for (int i = 0;i<CountOfBucket;i++)
        for (int j = 0;j<INT_BUCKET_SIZE;j++)
            Buckets[i][j] = -1;
}

int GotBucketNum(int Num)
{
    for (int i=0;i<CountOfBucket;i++)
    {
        if (Num >= i*INT_BUCKET_SIZE && Num < (i+1)*INT_BUCKET_SIZE)
            return i;
    }
    return -1;
}

void SortBucket(int Buckets[CountOfBucket][INT_BUCKET_SIZE],int BucketNum,int Num)
{
    int t;
    for (int i = 0 ; i<INT_BUCKET_SIZE;i++)
    {
        if (Buckets[BucketNum][i] == -1)
        {
            Buckets[BucketNum][i] = Num;
            break;
        }
        else if (Buckets[BucketNum][i] > Num)
        {
            t = Buckets[BucketNum][i];
            Buckets[BucketNum][i] = Num;
            Num = t;
        }
    }
    cout << "Insert Num : [" << Num << "]" << "  Bucket{" << BucketNum << "}" << endl;
    cout << "Bucket{" << BucketNum << "} : " ;
    for (int j = 0 ; j<INT_BUCKET_SIZE;j++)
    {
        if (Buckets[BucketNum][j] == -1)
            break;
        cout << "[" << Buckets[BucketNum][j] << "] " ;
    }
    cout << endl;
}

void DoBucketSort(const int *in)
{
    int BucketNum;
    int Buckets[CountOfBucket][INT_BUCKET_SIZE];
    InitBuckets(Buckets);

    for (int i = 0;i< INT_DATA_LEN;i++)
    {
        BucketNum = GotBucketNum(in[i]);
        SortBucket(Buckets,BucketNum,in[i]);
    }

    for (int k = 0;k<CountOfBucket;k++)
    {
        for (int l= 0; l < INT_BUCKET_SIZE; l++)
            cout << "[" << Buckets[k][l] << "]" << "  ";
        cout << endl;
    }
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                         Radix     Sort                                                    //
//                                                                                                                           //
//***************************************************************************************************************************//
void ClearTemp(int Temp[11][INT_DATA_LEN+1])
{
    for (int i = 0; i < 10;i++)
        for (int j = 0;j<=INT_DATA_LEN; j++)
            Temp[i][j] = 0;
}

int GetMaxNum(const int *in)
{
    int Ret = -1;
    for (int i = 0;i< INT_DATA_LEN;i++)
        if (in[i] > Ret)
            Ret = in[i];
    return Ret;
}

void RadixSort_LSD(int Source[],int Temp[11][INT_DATA_LEN+1],int LoopTime,int CurrentLoop)
{
    if (LoopTime < CurrentLoop)
        return;
    int PickNum;
    int Num;
    ClearTemp(Temp);
    for (int i = 0; i<INT_DATA_LEN; i++)
    {
        PickNum = (Source[i] %(int(pow10(CurrentLoop))))/(int)(pow10(CurrentLoop-1));
        Num = ++Temp[PickNum][0];
        Temp[PickNum][Num] = Source[i];
    }
    int SourceIdx = 0;

    cout << "Loop : " << CurrentLoop << "/" << LoopTime << " :" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "Temp{" << i << "} : ";
        for (int j = 1; j<= Temp[i][0];j++)
        {
            cout << "[" << Temp[i][j] << "]   " ;
            Source[SourceIdx++]   = Temp[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << "=========================================================" << endl;
    //resort Source
    RadixSort_LSD(Source,Temp,LoopTime,CurrentLoop+1);

}

void DoRadixSort(const int *in) //lsd method
{
    int Temp[10][INT_DATA_LEN+1];
    int Source[INT_DATA_LEN];
    for (int i = 0;i<INT_DATA_LEN;i++)
        Source[i] = in[i];
    int LoopTime = 1;
    int Max = GetMaxNum(in);
    while (Max > 9)
    {
        Max /= 10;
        LoopTime ++;
    }
    RadixSort_LSD(Source,Temp,LoopTime,1);
    cout << "=========================================================" << endl;
    cout << "Radix LSD method ,Result is : " << endl;
    for (int j = 0 ; j< INT_DATA_LEN ;j++)
        cout << "[" << Source[j] << "]  ";
    cout << endl;
    cout << "=========================================================" << endl;
}

//***************************************************************************************************************************//
//                                                                                                                           //
//                                                            Main                                                           //
//                                                                                                                           //
//***************************************************************************************************************************//

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
        case 5:
            DoQuickSort(temp);
            break;
        case 6:
            DoBubbleSort(temp);
            break;
        case 7:
            DoShellSort(temp);
            break;
        case 8:
            DoCombSort(temp);
            break;
        case 9:
            DoCountingSort(temp);
            break;
        case 10:
            DoBucketSort(temp);
            break;
        case 11:
            DoRadixSort(temp);
            break;
        default:
            break;
        }
    }
    return 0;
}

