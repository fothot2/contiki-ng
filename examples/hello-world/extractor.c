//This program is used to extract data from the printed output of the sensor program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *buffer = NULL;
    size_t bytes_read;
    int count = 0;
    size_t buffer_size = 0;
    int id, light, temp, humidity;

    id = 0;

    //Reading continuously from stdin each line
    while (1) {
        count++;

        // Read a line from stdin
        bytes_read = getline(&buffer, &buffer_size, stdin);
        if (bytes_read == -1) {
            break;
        }

        //Depending on the printf statements in the sensor program, you may need to change the if statements

        //if buffer string contains "id" then store the number in id
        //if (strstr(buffer, "id") != NULL) {
        //    sscanf(buffer, "id: %d", &id);
        //}
        if (strstr(buffer, "Light") != NULL) {
            sscanf(buffer, "Light: %d", &light);
        }
        else if (strstr(buffer, "Temperature") != NULL) {
            sscanf(buffer, "Temperature: %d", &temp);
        }
        else if (strstr(buffer, "Humidity") != NULL) {
            sscanf(buffer, "Humidity: %d", &humidity);
        }
        
        //if count is 4 then we have all the data we need to create a database entry
        if (count % 4 == 0) {
            //debug print all the data
            printf("id: %d, light: %d, temp: %d, humidity: %d\n", id, light, temp, humidity);
            
        }

        fflush(stdout);
        /*FILE *output_file = fopen("output.txt", "a");
        if (output_file != NULL) {
            fwrite(modified_buffer, 1, bytes_read, output_file);
            fclose(output_file);
        } else {
            fprintf(stderr, "Error: Could not open output file\n");
        }*/

        //(DEBUG) Print a message to the console every time we read input
        //printf("Read input %d times\n", count);
        fflush(stdout);

        // Wait for 30 seconds before reading the next input
        //sleep(30);
    }

    // Free the input buffer
    free(buffer);

    return 0;
}