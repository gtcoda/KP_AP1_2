#include <stdlib.h>
#include <stdint.h>
#include "../include/record.h"

void main(void) {

	char command[40];

	while (1) {
		printf("Command : ");
		mfgets(command, sizeof(command), stdin);
		if (!strcmp(command, "add")) {
			add_record();
		}
		else if (!strcmp(command, "read")) {
			read_file();
		}
		else if (!strcmp(command, "write")) {
			write_file();
		}
		else if (!strcmp(command, "view")) {
			view_record();
		}
		else if (!strcmp(command, "exit")) {
			break;
		}
		else {
			printf("command %s not found! \n", command);
		}
	}

}