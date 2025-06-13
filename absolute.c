#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
    FILE *fp;
    int i, j, staddr1;
    char line[50], name1[10], staddr[10];

    fp = fopen("object.txt", "r");
    fscanf(fp, "%s", line);

    // Extract the name part from the object file
    for (i = 2, j = 0; i < 8 ,j < 6; i++, j++) {
        name1[j] = line[i];
    }
    name1[j] = '\0';
    printf("name from obj. %s\n", name1);

    // Process object file contents
    do {
        fscanf(fp, "%s", line);
        if (line[0] == 'T') {
            // Extract starting address from the T record
            for (i = 2, j = 0; i < 8 , j < 6; i++, j++) {
                staddr[j] = line[i];
            }
            staddr[j] = '\0';
            staddr1 = (int)strtol(staddr,NULL,16);  // Convert to integer address

            i = 12;
            while (line[i] != '\0') { 
                if (line[i] != '^') {
                    printf("%d \t %c%c\n", staddr1, line[i], line[i+1]);
                    staddr1++;
                    i += 2;
                } else {
                    i++;
                }
            }
        } else if (line[0] == 'E') {
            break;  // Exit when 'E' record is found
        }
    } while (!feof(fp));

    fclose(fp);  // Close the file after processing
}
