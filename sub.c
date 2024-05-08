void strip_newline_carriage_return(char *str) {
    if (str == NULL) {
        return;  // Handle null input gracefully
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;  // Handle empty string
    }

    // Find the last newline or carriage return character
    char *end = str + len - 1;
    while (end >= str && (*end == '\n' || *end == '\r')) {
        *end = '\0';  // Replace newline/carriage return with null terminator
        end--;
    }
}