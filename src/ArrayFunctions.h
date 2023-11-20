int DirectionList[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void DeleteDirection(int arr[4][2],int index,int len)
{
    for (int i=index;i<len-1;i++)
        for (int j=0;j<2;j++)
            arr[i][j]=arr[i+1][j];
    
}

void copyArray(int CopyTO[4][2],int CopyFrom[4][2])
{
    for(int i =0;i<4;i++)
        for (int j = 0; j < 2; j++)
            CopyTO[i][j]=CopyFrom[i][j];
}

