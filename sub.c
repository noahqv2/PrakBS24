if (in[bytes_read - 1] == '\n') {
    // Remove trailing "\r\n" characters
    if (input_length >= 2 && full_input[input_length - 2] == '\r' &&
        full_input[input_length - 1] == '\n') {
        full_input[input_length - 2] = '\0'; // Replace '\r' with '\0'
        full_input[input_length - 1] = '\0'; // Replace '\n' with '\0'
        input_length -= 2; // Adjust input length
        }