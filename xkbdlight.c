#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#define BRIGHTNESS	"/sys/class/leds/smc::kbd_backlight/brightness"
#define MAX_BRIGHTNESS	"/sys/class/leds/smc::kbd_backlight/max_brightness"
#define MAX_LENGTH	4

int main(int argc, char **argv)
{
	if (setuid(0)) {
		printf("%s needs to be run with root privileges.\n", argv[0]);
		return -1;
	}

	int c, val;
	opterr = 0;

	char max[MAX_LENGTH] = { '\0' };
	char actual[MAX_LENGTH] = { '\0' };

	FILE *brightness = fopen(BRIGHTNESS, "r");
	fscanf(brightness, "%s", actual);
	fclose(brightness);
	FILE *max_brightness = fopen(MAX_BRIGHTNESS, "r");
	fscanf(max_brightness, "%s", max);
	fclose(max_brightness);

	while ((c = getopt(argc, argv, "hi:d:s:")) != -1)
	switch(c) {
		case 'h':
			printf("\t\tGet actual brightness\n"
				"-h\t\tHelp\n"
				"-i <int>\tIncrement of +int\n"
				"-d <int>\tDecrement of -int\n"
				"-s <int>\tSet to 0 <= int <= %s\n", max);
			return 0;
			break;
		case 'i':
			val = (int) strtol(actual, (char **)NULL, 10);
			val += (int) strtol(optarg, (char **)NULL, 10);
			sprintf(actual, "%d", val);
			brightness = fopen(BRIGHTNESS, "w+");
			if (val >= 0 && val <= (int) strtol(max, (char **)NULL, 10))
				fprintf(brightness, "%s", actual);
			else
				fprintf(brightness, "%s", max);
			fclose(brightness);
			break;
		case 'd':
			val = (int) strtol(actual, (char **)NULL, 10);
			val -= (int) strtol(optarg, (char **)NULL, 10);
			sprintf(actual, "%d", val);
			brightness = fopen(BRIGHTNESS, "w+");
			if (val >= 0 && val <= (int) strtol(max, (char **)NULL, 10))
				fprintf(brightness, "%s", actual);
			else
				fprintf(brightness, "0");
			fclose(brightness);
			break;
		case 's':
			val = (int) strtol(optarg, (char **)NULL, 10);
			strcpy(actual, optarg);
			if (val >= 0 && val <= (int) strtol(max, (char **)NULL, 10)) {
				brightness = fopen(BRIGHTNESS, "w+");
				fprintf(brightness, "%s", actual);
				fclose(brightness);
			} else
				printf("Error: invalid argument for option -s\n");
			break;
		case '?':
			if (optopt == 'g')
				printf("%s\n", actual);
			else
				printf("Error: option %c requires an argument\n", optopt);
			break;
		default:
			printf("\t\tGet actual brightness\n"
				"-h\t\tHelp\n"
				"-i <int>\tIncrement of +int\n"
				"-d <int>\tDecrement of -int\n"
				"-s <int>\tSet to 0 <= int <= %s\n", max);
	}

	return 0;
}
