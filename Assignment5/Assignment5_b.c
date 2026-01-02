//recursive directory traversal 
//write tree_clone.c which prints a directory as a tree, like 
//root/ 
//   a.txt 
//   src/ 
//      Ganesh.c 
//Indentation based on recursion depth 
//print type markers: [d] directory [f] regular file [l] symbolic link 
//use lstat() to detect symbolic links do not follow symlink directories(avoid loops)




#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
}

void traverse(const char *dirpath, int depth)
{
    DIR *dp;
    struct dirent *de;
    struct stat st;
    char fullpath[PATH_MAX];

    dp = opendir(dirpath);
    if (!dp) {
        perror("opendir");
        return;
    }

    while ((de = readdir(dp)) != NULL) {

        /* Skip . and .. */
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        snprintf(fullpath, sizeof(fullpath),
                 "%s/%s", dirpath, de->d_name);

        if (lstat(fullpath, &st) == -1) {
            perror("lstat");
            continue;
        }

        print_indent(depth);

        if (S_ISDIR(st.st_mode)) {
            printf("[d] %s/\n", de->d_name);

            /* DO NOT recurse into symlinked directories */
            traverse(fullpath, depth + 1);
        }
        else if (S_ISREG(st.st_mode)) {
            printf("[f] %s\n", de->d_name);
        }
        else if (S_ISLNK(st.st_mode)) {
            printf("[l] %s\n", de->d_name);
        }
        else {
            printf("[?] %s\n", de->d_name);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("[d] %s/\n", argv[1]);
    traverse(argv[1], 1);

    return EXIT_SUCCESS;
}
