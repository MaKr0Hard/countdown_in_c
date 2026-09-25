#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>

int number_of_days_before_timestamp (long timestamp) {
	time_t t = time(NULL);
	time_t t_end = (time_t)timestamp;
	double diff = difftime(t_end, t);
	int days_before = round(diff / 86400);
	return days_before;
}

int main () {
	FILE* holidays;
	holidays = fopen("holidays.txt", "r"); //TODO : add argument to add stuff to the file 
	char string_being_read[2048]; //Hear me out, it's either the cpu or the ram (fgetc for every char or fgets but no idea on the length)
	if (holidays == NULL) {
		puts("Have you tried checking if the file is even there ?\n");
		return 1;
	}
	while (fgets(string_being_read, 2047, holidays) != NULL) {
		int timestamp = 0;
		int* timestamp_ptr = &timestamp;//TODO: remove this shit
		char name[2048];
		name[0] = '\0';
		// i think it's bad    name[0] = '\0';
		if (0 != sscanf(string_being_read, "%s :  %d", name, timestamp_ptr)) {
		if (timestamp_ptr != NULL && timestamp != 0) /* should really delete that pointer and use a struct to know whether it's empty */  {
			int days_before_the_thing = number_of_days_before_timestamp(*timestamp_ptr);
			printf("%d days before : %s\n", days_before_the_thing, name);
		}
	}
	}	
	return 0;
}
