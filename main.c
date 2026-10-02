#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

int number_of_days_before_timestamp (long timestamp) {
	time_t t = time(NULL);
	time_t t_end = (time_t)timestamp;
	double diff = difftime(t_end, t);
	int days_before = round(diff / 86400);
	return days_before;
}

void quit_early_cannot_be_blank () {
	puts("field cannot be blank"); //or sh*t like that, dunno if it's null if it fails or if it's empty
	exit(2);
}

int main (const int argc, const char** argv) {


	if (argc == 1) {
		FILE* holidays;
		holidays = fopen("holidays.txt", "r"); //TODO : add argument to add stuff to the file
		char string_being_read[2048]; //Hear me out, it's either the cpu or the ram (fgetc for every char or fgets but no idea on the length)
		if (holidays == NULL) {
			puts("Have you tried checking if the file is even there ?\n");
			return 1;
		}

		while (fgets(string_being_read, 2047, holidays) != NULL) {
			int timestamp = 0;

			char name[2048];
			name[0] = '\0';
			// i think it's bad    name[0] = '\0';
			if (0 != sscanf(string_being_read, "%s :  %d", name, &timestamp)) {
				if (timestamp != 0) {
					int days_before_the_thing = number_of_days_before_timestamp(timestamp);
					printf("%d days before : %s\n", days_before_the_thing, name);
				}
			}
		}
	}
	else if (argc == 2) {
		if ((argv[2] = "add-element") || (argv[2] = "ae")) {
			FILE* holidays;
			holidays = fopen("holidays.txt", "a");
			char readbuf_name[1996];
			char readbuf_timestamp[48]; //memorilik
			char string_being_written[2048]; // won't fight malloc this time so this will be for another friday
			if (holidays == NULL) {
				puts("Have you tried checking if the file is even there ?\n");
				return 1;
			}

			puts("Holiday name ?");
			if (fgets(readbuf_name, sizeof(readbuf_name), stdin) != NULL) {

			} else {
				quit_early_cannot_be_blank();
			}

			puts("Timestamp ?"); //TODO : make this into a proper date input
			if (fgets(readbuf_timestamp, sizeof(readbuf_timestamp), stdin) != NULL) {

			} else {
				quit_early_cannot_be_blank();
			}

			/*strcat(string_being_written, readbuf_name);
			strcat(string_being_written, " : ");
			strcat(string_being_written, readbuf_timestamp);
			fputs(holidays, string_being_written); //change to a fprintf to save 2048 bytes*/
			readbuf_name[ strlen(readbuf_name) - 1 ] = '\0'; //this will do the job...
			readbuf_timestamp[ strlen(readbuf_timestamp) - 1 ] = '\0';
			fprintf(holidays, "\n%s : %s", readbuf_name, readbuf_timestamp);//TODO : make it check for non-numbers
		} else {
			puts("Wrong arguments");
		}
	} else {
		puts("Wrong arguments");
	}
	return 0;
}
