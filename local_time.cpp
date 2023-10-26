#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
	//setenv("TZ", "Asia/Shanghai", 1);
    char timestamp[60];
    time_t raw_time;
    struct tm local_time;

    // Get the raw time
    raw_time = time(NULL);

    // Convert to local time
    localtime_r(&raw_time, &local_time);

    // Format the timestamp string
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S.", &local_time);

    // Add microseconds
    sprintf(timestamp + strlen(timestamp), "%06ld", (int64_t)000);

    // Include the UTC offset
    strftime(timestamp + strlen(timestamp), sizeof(timestamp) - strlen(timestamp), "%z", &local_time);

    printf("%s\n", timestamp);

    return 0;
}
