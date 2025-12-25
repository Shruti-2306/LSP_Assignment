//Read N bytes from file
//Accept filename and number of bytes N
//Read exactly N bytes using read() and print on console
//if the file contains less than N,print only available bytes





#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
   char filename[256];
   int fd;
   size_t n;
   ssize_t bytes_read;

    printf("Enter file name: \n");
    fgets(filename,sizeof(filename),stdin) ;
    filename[strcspn(filename,"\n") ]= '\0';

    printf("Enter number of bytes to read: \n");
    scanf("%zu",&n);

    fd = open(filename,O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    char buffer[n];
    bytes_read = read(fd,buffer,n);
    if(bytes_read == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';
    printf("File Data: \n%s\n", buffer);

    close(fd);




    return 0;
}