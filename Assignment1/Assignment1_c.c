//Check file Access Permission
//Accept filename and mode(read/write/execute)
//Use access() to check permission for current process
//Print Accessible/Not accessible with reason 




#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main()
{

    char filename[256];
    int iAcess_mode = 0;
    char mode[20];

    printf("Enter filename: \n");
    scanf("%255s",filename);

    printf("Enter mode of file(read,write,execute,readwrite): \n");
    scanf("%19s",mode);

    if(strcmp(mode,"read")== 0)
    {
        iAcess_mode = R_OK;
    }
    else if(strcmp(mode,"write")== 0)
    {
        iAcess_mode = W_OK;
    }
    else if(strcmp(mode,"execute") == 0)
    {
        iAcess_mode = X_OK;
    }
    else if(strcmp(mode,"readwrite")== 0)
    {
        iAcess_mode = R_OK | W_OK;
    }
    else{
        printf("Invalid input..\n");
        return 1;
    }


    if(access(filename,iAcess_mode) == 0)
    {
        printf("File accessible with permission :%s\n",mode);
    }
    else
    {
        printf("File not accessible...\n");
    }

    if(errno == ENOENT)
    {
        printf("File does not exist..\n");
    }
    else if(errno == EACCES)
    {
        printf("permission denied...\n");
    }
    else
    {
        perror("error");
    }
    return 0;
}