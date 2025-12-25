//Open file
//2.Accept file name from user and open it using open()
//print: success message + returned file descriptor
//Handle errors using perror()

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd, iFlag = 0;
    char filename[256];
    char mode[10];

    printf("Enter Filename: \n");

    if(fgets(filename,sizeof(filename),stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }

    for(int iCnt = 0; filename[iCnt]; iCnt++)
    {
        if(filename[iCnt] =='\n')
        {
           filename[iCnt] ='\0';
           break;
        }
    }
    
    printf("Enter Mode: (R, W, WR,A): \n");

    if(fgets(mode,sizeof(mode),stdin) == NULL)
    {
        perror("fgets");
        return -1;
    }

    for(int i = 0; mode[i];i++)
    {
        if(mode[i] == '\n')
        {
            mode[i] = '\0';
            break;
        }
    }

     
    if(strcmp(mode, "R") == 0)
    {
        iFlag = O_RDONLY;
    }
    else if(strcmp(mode,"W") == 0)
    {
        iFlag = O_WRONLY ;
    }
    else if(strcmp(mode,"RW") == 0)
    {
        iFlag = O_RDWR ;
    }
    else if(strcmp(mode,"A")==0)
    {
        iFlag = O_APPEND;
    }
    else{
        printf("Invalid mode entered!!!\n");
        return 1;
    }
    

    fd = open(filename,mode, 0777);

    if(fd == -1)
    {
        perror("open");
        return 1;
    }
    printf("File opened successfully\n");
    printf("File descriptor of file is: %d\n",fd);

    close(fd);
    return 0;
}