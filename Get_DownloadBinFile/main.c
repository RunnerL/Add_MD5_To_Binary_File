
#include "inc/global.h"

static U8 MD5[MD5_SIZE] = {0};         //用于存放md5算法生成的摘要
static U32 file_size = 0;              //用于存放原始bin文件大小
static U8 AddContent[HEAD_SIZE] = {0}; //用于存放新的bin文件头部数据


int main(void)
{
    FILE *f_src, *f_out; 
    size_t r_num, w_num;//读写文件数据
    U32 i, j, buf_num;
    U8 rbuff[BUFF_SIZE];//接收缓冲 1k
    MD5_CTX md5;

    memset(MD5, 0, sizeof(MD5));
    memset(AddContent, 0, sizeof(AddContent));

    f_src = fopen(SRC_BIN_PATH, "rb");
    if(!f_src)
        perror("fopen src file");

    /* 获取bin文件大小 */

    file_size = GetFileSize(SRC_BIN_PATH);
    if((file_size%BUFF_SIZE) != 0)
        buf_num = file_size/BUFF_SIZE + 1;
    else
        buf_num = file_size/BUFF_SIZE;
#if DEBUG
    printf("buf_num : %02x\n",buf_num);
    printf("filesize : %ld %x\n",file_size, file_size);
#endif

    /* 获取bin文件对应的md5摘要*/
    
    MD5Init(&md5);
    fseek(f_src, 0, SEEK_SET);
    for(i=0; i<buf_num; i++)
    {
        r_num = fread(rbuff, 1, sizeof(rbuff), f_src);
        if(r_num <= 0)
            perror("read src_bin");
#if DEBUG
        for(j=0; j<r_num; j++)
        {
            printf("%02x ",rbuff[j]);
        }
        putchar(10);
        putchar(10);
#endif
        MD5Update(&md5, rbuff, r_num);
    }
    MD5Final(&md5, MD5);
#if DEBUG
    printf("MD5:");
    for(j=0; j<MD5_SIZE; j++)
    {
        printf("%02x",MD5[j]);
    }
    putchar(10);
#endif

    /* 组装新bin文件的头*/

    for(j=0; j<4; j++)
    {
        AddContent[j] = file_size >> (3-j)*8; 
    }
    memcpy(AddContent+4, MD5, sizeof(MD5));

#if DEBUG
    for(i=0; i<HEAD_SIZE; i++)
    {
        printf("%02x ",AddContent[i]);
    }
    putchar(10);
#endif

    /* 将旧bin文件内容插入新bin文件尾部 */

    f_out = fopen(OUT_BIN_PATH, "w");
    if(!f_out)
        perror("fopen out bin file");
    w_num = fwrite(AddContent,1,sizeof(AddContent),f_out);
    if(w_num <= 0)
        perror("fwrite head");

    fseek(f_src, 0, SEEK_SET);
    for(i=0; i<buf_num; i++)
    {
        r_num = fread(rbuff, 1, sizeof(rbuff), f_src);
        if(r_num <= 0)
            perror("read src_bin");
#if DEBUG
        for(j=0; j<r_num; j++)
        {
            printf("%x ",rbuff[j]);
        }
        putchar(10);
        putchar(10);
#endif
        w_num = fwrite(rbuff,1,r_num,f_out);
        if(w_num <= 0)
            perror("fwrite head");
    }


    fclose(f_src);
    fclose(f_out);
    return 0;
}




/* 获取文件大小 */
U32 GetFileSize(const char *path)
{
    U64 filesize = -1;
    struct stat statbuff;
    if(stat(path, &statbuff) < 0)
    {
        return filesize;
    }
    else
    {
        filesize = statbuff.st_size;
    }
    return filesize;
}
