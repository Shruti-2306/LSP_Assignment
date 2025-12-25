//Display Complete File Information
//Accept file name and display file metadata using stat():
//Size, inode number, permissions, hard links, owner uid/gid, file type, last access/modify time.



#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int main()
{
    char filename[256];
    struct stat st;

    printf("Enter file name: \n");
    if(fgets(filename,sizeof(filename),stdin) == NULL)
    {
        perror("fgets");
        return 1;
    }

    filename[strcspn(filename, "\n")] = '\0';

    if(stat(filename, &st) == -1)
    {
        perror("stat");
        return 1;
    }
    
    printf("\n......File Metadata......\n");
    printf("File Size: %ld\n",st.st_size);
    printf("Inode number: %ld\n",st.st_ino);
    printf("Hardlinks: %ld\n",st.st_nlink);
    printf("Owner UID: %ld\n",st.st_uid);
    printf("Owner GID: %ld\n",st.st_gid);

    printf("\n....File Permissions....\n");
    printf(st.st_mode & S_IRUSR ? "r" : "-");
    printf(st.st_mode & S_IWUSR ? "w" : "-");
    printf(st.st_mode & S_IXUSR ? "x" : "-");
    printf(st.st_mode & S_IRGRP ? "r" : "-");
    printf(st.st_mode & S_IWGRP ? "w" : "-");
    printf(st.st_mode & S_IXGRP ? "x" : "-");
    printf(st.st_mode & S_IROTH ? "r" : "-");
    printf(st.st_mode & S_IWOTH ? "w" : "-");
    printf(st.st_mode & S_IXOTH ? "x\n" : "-\n");

    printf("\n....File Type....\n");
    if(S_ISREG(st.st_mode))
    {
        printf("Regular File..\n");
    }
    else if(S_ISDIR(st.st_mode))
    {
        printf("Directory File..\n");
    }
    else if(S_ISLNK(st.st_mode))
    {
        printf("Symbolic File..\n");
    }
    else if(S_ISCHR(st.st_mode))
    {
        printf("Character File..\n");
    }
    else if(S_ISBLK(st.st_mode))
    {
        printf("Block Device..\n");
    }
    else if(S_ISFIFO(st.st_mode))
    {
        printf("Pipe File..\n");
    }
    else if(S_ISSOCK(st.st_mode))
    {
        printf("Socket File..\n");
    }
    else
    {
        printf("File Type Unknown..\n");
    }
    printf("Last access: %s",ctime(&st.st_atime));
    printf("Last Modify: %s",ctime(&st.st_mtime));

    return 0;
}