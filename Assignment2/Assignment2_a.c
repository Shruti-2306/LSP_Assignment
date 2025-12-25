
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 1024

int main(void)
{
   char filename[256];
   int fd;
   ssize_t bytes_read;
   ssize_t total_bytes = 0;
   char buffer[BUF_SIZE];

    
 printf("Enter file name: \n");
    if(fgets(filename,sizeof(filename),stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }

    filename[strcspn(filename, "\n")] = '\0';

    fd = open(filename,O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    printf("\n...File Contents...\n");

    while((bytes_read = read(fd,buffer,BUF_SIZE)) > 0)
    {
        write(STDOUT_FILENO,buffer,bytes_read);
        total_bytes += bytes_read;
    }

    if(bytes_read == -1)
    {
        perror("read");
    }
    printf("\nTotal bytes read: %ld\n",total_bytes);
    close(fd);

    return 0;
}
