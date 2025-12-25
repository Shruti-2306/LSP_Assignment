#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{
   char filename[256];
   int fd;
   char text[1024];
   ssize_t bytes_written;

    printf("Enter file name: \n");
    if(fgets(filename,sizeof(filename),stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }

    //filename[strcspn(filename, "\n")] = '\0';

    printf("Enter text to append: \n");
     if(fgets(text,sizeof(text),stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }

    

    fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
    if(fd ==-1)
    {
        perror("open");
        return 1;
    }

    bytes_written = write(fd,text,strlen(text));
    if(bytes_written == -1)
    {
        perror("write");
        close(fd);
        return 1;
    }
    printf("Bytes written: %ld\n",bytes_written);

    close(fd);

    return 0;
}