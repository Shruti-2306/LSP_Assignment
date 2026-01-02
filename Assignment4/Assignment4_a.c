//Write a code that copies content of one file to another 
//input: source file name and destination file name as command line arguments. 
//output: Destination file is exact copy of source file Handle file not found and permissions error 
//Destination file should be created if not present


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    FILE *src = NULL;
    FILE *dest = NULL;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open source file */
    src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        fprintf(stderr, "Error opening source file '%s': %s\n",
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    /* Open/Create destination file */
    dest = fopen(argv[2], "wb");
    if (dest == NULL)
    {
        fprintf(stderr, "Error opening destination file '%s': %s\n",
                argv[2], strerror(errno));
        fclose(src);
        return EXIT_FAILURE;
    }

    /* Copy content */
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0)
    {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read)
        {
            fprintf(stderr, "Write error: %s\n", strerror(errno));
            fclose(src);
            fclose(dest);
            return EXIT_FAILURE;
        }
    }

    /* Check read error */
    if (ferror(src))
    {
        fprintf(stderr, "Read error: %s\n", strerror(errno));
        fclose(src);
        fclose(dest);
        return EXIT_FAILURE;
    }

    
    fclose(src);
    fclose(dest);

    printf("File copied successfully...\n");
    return EXIT_SUCCESS;
}
