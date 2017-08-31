#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

/// \file move_file_on_writting.c
/// \brief  log simulation, do move log out when writting the log
/// \author PangBo, bo.pang@metoak.com
/// \version
/// \date 2017-08-31

//函数名称：复制文件
//调用函数：fopen,fclose,fgetc,fputc,feof
//参数：源文件路径名，目标文件路径名
//返回值：-1=源文件打开失败;-2=目标文件打开失败;0=复制成功
int FileCopy(char* src, char* des)
{
    FILE *input,*output;
    char ch;
    if((input = fopen(src,"r")) == NULL)
    {
        printf("'%s' does not exist!\n", src);
        return -1;
    }
    if((output = fopen(des,"w")) == NULL)
    {
        fclose(input);
        printf("Wrong output file name or Permission denied!\n");
        return -2;
    }
    ch = fgetc(input);
    while(!feof(input)) //判断后一位的状态(C语言问题)
    {
        printf("copying...%c", ch);
        fputc(ch,output);
        ch = fgetc(input);
    }
    fclose(input);
    fclose(output);
    return 0;
}

int FileClear(char *file_name)
{
    FILE* fp;
    if((fp = fopen(file_name, "w")) == NULL)
    {
        printf("file clear fail");
        return -1;
    }
    fclose(fp);
    return 0;
}

int write_file_on_timing(char *file_name)
{
    FILE *fp = fopen(file_name, "a+");
    if(fp == NULL)
    {
        printf("open file in write_file_on_timing files");
        return 0;
    }

    for (int i = 0; i < INT_MAX; ++i) {
        fprintf(fp, "%d\n", i);
        fflush(NULL);
        printf("%d\n", i);
        sleep(1);
    }

    fclose(fp);

    return 1;
}

static int record_log_cnt = 0;
int move_file(char *file_name)
{
    char record_name[1024];
    int ret;

    printf("file_name : %s\n", file_name);
    while(1)
    {
        sleep(10);

        sprintf(record_name, "%d.log", record_log_cnt);
        ret = FileCopy(file_name, record_name);
        printf("ret is %d\n", ret);
        if(ret == 0)
        {
            printf("copy file %s success\n", file_name);
        }
        else
        {
            printf("copy file %s fail\n", file_name);
        }

        ret = FileClear(file_name);
        if(ret == 0)
        {
            printf("clear %s success\n", file_name);
        }
        else
        {
            printf("clear %s fail\n", file_name);
        }

        record_log_cnt++;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    char *file_name = (char*)"test.log";
    /*write_file_on_timing(file_name);*/
    if(fork() == 0)
    {
        write_file_on_timing(file_name);
    }
    else {
        /*sleep(3);*/
        move_file(file_name);
    }
    return 0;
}
