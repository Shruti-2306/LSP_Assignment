//Open file
//1.Accept file name from user and open it using open()
//print: success message + returned file descriptor
//Handle errors using perror()

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd;
    char filename[256];

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

    

    fd = open(filename,O_RDONLY);

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