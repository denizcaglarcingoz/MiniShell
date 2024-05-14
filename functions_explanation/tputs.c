#include <stdio.h>
#include <curses.h>
#include <ncurses.h>  // or <ncurses.h> for ncurses library
#include <stdlib.h>
#include <termcap.h>

#include <stdio.h>
#include <stdlib.h>

// -Finding the description of the user's terminal type (tgetent).
// -Interrogating the description for information on
// various topics (tgetnum, tgetflag, tgetstr).
// -Computing and performing padding (tputs).
// -Encoding numeric parameters such as cursor positions into the 
// terminal-specific form required for display commands (tparam, tgoto).


// tgetent();
// An application program that is going to use termcap must first 
// look up the description of the terminal type in use.
// This is done by calling tgetent, whose declaration in
// ANSI Standard C looks like:

// int tgetent (char *buffer, char *termtype);

// This function finds the description and remembers
// it internally so that you can interrogate it about
// specific terminal capabilities 

// Each piece of information recorded in a terminal description
// is called a capability. Each defined terminal capability has a
// two-letter code name and a specific meaning.
// For example, the number of columns is named `co'. 
// See section Definitions of the Terminal Capabilities, 
// for definitions of all the standard capability names.
// https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_4.html#SEC23


// Capability values can be numeric,
// boolean (capability is either present or absent) or strings.
// Any particular capability always has the same value type;
// for example, `co' always has a numeric value, while `am'
// (automatic wrap at margin) is always a flag, and `cm'
// (cursor motion command) always has a string value.
// The documentation of each capability says which type of value
// it has.

// There are three functions to use to get the value of a 
// capability, depending on the type of value the capability has.
// Here are their declarations in ANSI C:

// int tgetnum (char *name);
// int tgetflag (char *name);
// char *tgetstr (char *name, char **area);


#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <unistd.h>
int main() {
    char *clear_screen_cap;
    char *cursor_home_cap;
    char *padding;
    char *term_buffer; // Buffer for terminal capabilities

    // Get the terminal type
    char *term_type = getenv("TERM");
    if (term_type == NULL) {
        fprintf(stderr, "TERM environment variable is not set.\n");
        return 1;
    }

	term_buffer=(char*)malloc(4096);
    // Initialize the terminfo database
    if (tgetent(term_buffer, term_type) != 1) {
        fprintf(stderr, "Failed to initialize terminfo database for terminal type %s.\n", term_type);
        return 1;
    }

    // Retrieve terminal capabilities cr ho cl sf do 
    clear_screen_cap = tgetstr("do", (char **)&term_buffer);
    cursor_home_cap = tgetstr("ll", (char **)&term_buffer);
    padding = tgetstr("pc", (char **)&term_buffer);

    // Check if capabilities are available
    // if (clear_screen_cap == NULL || cursor_home_cap == NULL || padding == NULL) {
    //     fprintf(stderr, "Terminal capabilities not supported.\n");
    //     return 1;
    // }

    // Clear the screen
    tputs(clear_screen_cap, 1, putchar);

    // Move the cursor to the home position
    //tputs(padding, 1, putchar);

    // Print some text with padding
    printf("Padded Text:%sHello, World!%s\n", padding, padding);

    return 0;
}


// you have to use tgetent, tgetstr and tputs. It is the whole point
