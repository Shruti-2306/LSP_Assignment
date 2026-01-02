// File counter + size report create dir_report.c that recursively calculates: 
//total number of files 
//total number of directories 
//total size of regular files(in bytes) 
//largest file name+size 
//count a directory when you enter it for size: consider only regular files(S_ISREG) 
//ignore symlink target size(treat symlink as link object only) 
//output:(eg) files: 120 
//dirs: 15 
//total size: 9823412 bytes 
//Largest: Marvellous.mp4(2341123 bytes)



#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

/* Global counters */
static long long total_size = 0;
static long total_files = 0;
static long total_dirs = 0;

static off_t largest_size = 0;
static char largest_file[PATH_MAX] = "";

void traverse(const char *dirpath)
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

    /* Count directory when entered */
    total_dirs++;

    while ((de = readdir(dp)) != NULL) {

        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        snprintf(fullpath, sizeof(fullpath),
                 "%s/%s", dirpath, de->d_name);

        if (lstat(fullpath, &st) == -1) {
            perror("lstat");
            continue;
        }

        /* Regular file */
        if (S_ISREG(st.st_mode)) {
            total_files++;
            total_size += st.st_size;

            if (st.st_size > largest_size) {
                largest_size = st.st_size;
                strncpy(largest_file, fullpath, sizeof(largest_file) - 1);
                largest_file[sizeof(largest_file) - 1] = '\0';
            }
        }
        /* Directory (do NOT follow symlinks) */
        else if (S_ISDIR(st.st_mode)) {
            traverse(fullpath);
        }
        /* Symlinks ignored for size */
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    traverse(argv[1]);

    printf("files: %ld\n", total_files);
    printf("dirs: %ld\n", total_dirs);
    printf("total size: %lld bytes\n", total_size);

    if (largest_size > 0)
        printf("Largest: %s (%lld bytes)\n",
               largest_file, (long long)largest_size);
    else
        printf("Largest: none\n");

    return EXIT_SUCCESS;
}
