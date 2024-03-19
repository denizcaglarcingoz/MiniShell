#include <stdio.h>
#include <unistd.h>
int main() {
    char buffer[100];
     ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
    {
    write(1, buffer, bytes_read);
    }
    return 0;
}