#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
// Function to generate a random string of specified length
char* generate_random_string(uint64_t num_chars)
{
    // Initialize a string of the specified length
    char* random_string = (char*) malloc(num_chars + 1);

    // Generate a random string of characters
    for (uint64_t i = 0L; i < num_chars; i++) {
        random_string[i] = 'a' + (rand() % 26);
    }
    random_string[num_chars] = '\0';

    // Return the generated string
    return random_string;
}

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Get the number of characters and filename from the user
    uint64_t num_chars;
    printf("Enter the number of characters to generate: ");
    scanf("%llu", &num_chars);
char filename[256];
    printf("Enter the filename: ");
   scanf("%s", filename);

    // Generate the random string
    char* random_string = generate_random_string(num_chars);

    // Write the random string to the specified file
   FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%s", random_string);
    fclose(f);

    // Free the allocated memory
    free(random_string);

    return 0;
}
