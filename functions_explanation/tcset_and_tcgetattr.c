// NAME
//     tcgetattr, tcsetattr
// SYNOPSIS
//        #include <termios.h>
//        #include <unistd.h>

// 	   int tcgetattr(int fd, struct termios *termios_p);
//        int tcsetattr(int fd, int optional_actions,
//                      const struct termios *termios_p);

// In the context of the functions tcgetattr() and tcsetattr(),  !!!!!!!
// the "tc" stands for "termios" or "terminal control".

// tcgetattr(): This function is used to get the parameters 
// associated with the terminal referred to by the file descriptor fd. 
// It retrieves the current settings of the terminal attributes
// and stores them in a termios structure.

// tcsetattr(): This function is used to set the parameters
// associated with the terminal referred to by the file descriptor fd.
// It sets the terminal attributes according to the values specified
// in the termios structure.

// man termios because it is important !!!!!!

// DESCRIPTION
//        The termios functions describe a general terminal interface that is provided to control asynchronous communications ports.

//    The termios structure
//        Many of the functions described here have a termios_p argument that is a pointer to a termios structure.  This structure  con‐
//        tains at least the following members:

//            tcflag_t c_iflag;      /* input modes */
//            tcflag_t c_oflag;      /* output modes */
//            tcflag_t c_cflag;      /* control modes */
//            tcflag_t c_lflag;      /* local modes */
//            cc_t     c_cc[NCCS];   /* special characters */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
void printBinary(unsigned int num) {
    if (num > 1)
        printBinary(num >> 1);  // Recursively shift right
    printf("%d", num & 1); 
}

int main() {
    struct termios term;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &term);
	printBinary(ECHO);
	printf("\n");
	printBinary(term.c_lflag);
	printf("\n");
	printBinary(ICANON);
	printf("\n");
	printBinary(term.c_lflag);
    // Set raw mode: disable canonical mode and input echoing
    term.c_lflag &= ~(ICANON | ECHO);
	//1 ICANON &= 0 ICANON
	//00000q
    // Set the new terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // Now read characters one by one
    char c;
	printf("Enter characters ('q' to quit): \n");
    printf("term %u\n", term.c_lflag);
	printf("term %o ---- %o\n", ECHO, ICANON);
	printBinary(term.c_lflag);
	printf("\n");
	printBinary(ECHO);
	printf("\n");

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        printf("Read character: %c\n", c);
    }

    // Restore original terminal attributes
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    return 0;
}



