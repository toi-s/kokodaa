
#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_MAX 25
#define NAME_LEN 12
#define GROUP_LEN 3
#define GROUP_NUM 3


typedef struct idol{
    char name[NAME_LEN];
    char group[GROUP_LEN];
    int score;
} IDOL;

int main(void) {
    FILE *fp;
    char data[LINE_MAX];
    int data_num=0;
    int bad_data_num=0;
    char group[GROUP_NUM][GROUP_LEN+1]={"AKB","SKE","HKT"};
    IDOL *idols;
    int  index=0;
    int bad_data[LINE_MAX];
    int good_data[GROUP_NUM][2];
    int i,j=0;
    int sum =0, number = 0 , max = 0;
    
    if((fp=fopen("data.txt","r"))==NULL){
        exit(EXIT_FAILURE);
    }
    
    while(fgets(data,LINE_MAX,fp)!=NULL){
        data_num++;
    }
    
    idols = malloc(sizeof(IDOL)*data_num);
    
    rewind(fp);
    
    while(fgets(data,LINE_MAX,fp)!=NULL){
        sscanf(data, "%s %s %d¥n", idols[index].name,idols[index].group,&idols[index].score);
        index++;
    }
    
   
    for(i=0;i<data_num;i++){
        if(strcmp(idols[i].group,group[0])!=0 && strcmp(idols[i].group,group[1])!=0 && strcmp(idols[i].group,group[2])!=0){
            bad_data[j++] = i;
            bad_data_num++;
        }
    }
    
    
    for(i=0;i<GROUP_NUM;i++){
        max = sum = 0;
        for(j=0;j<index;j++){
            if(strcmp(idols[j].group,group[i])==0){
                if(max < idols[j].score){
                    max = idols[j].score;
                    number = j;
                }
                sum += idols[j].score;
            }
        }
        good_data[i][0]=number;
        good_data[i][1]=sum;
    }
    
    
    
    fclose(fp);
    
   
    if((fp=fopen("data2.txt","w+"))==NULL){
        exit(EXIT_FAILURE);
    }    
    for(i=0;i<GROUP_NUM;i++){
        fprintf(fp,"%-3s %-6d  %-12s\n",group[i],good_data[i][1],idols[good_data[i][0]].name);
    }
    
    fclose(fp);
    
   
    if((fp=fopen("data3.txt","w+"))==NULL){
        exit(EXIT_FAILURE);
    }
    
    for(i=0;i<bad_data_num;i++){
        fprintf(fp,"%-6s %-3d  %-12s\n",idols[bad_data[i]].name,idols[bad_data[i]].score,idols[bad_data[i]].group);
    }
    
    fclose(fp);
}



