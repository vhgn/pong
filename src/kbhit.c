/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@casual-effectcs.com
*/
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

int _kbhit() {
	static const int STDIN = 0;
	static char initialized;
	int bytesWaiting;

	initialized = 0;

	if (!initialized) {
		struct termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		term.c_lflag &= ~ECHO;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = 1;
	}

	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}
