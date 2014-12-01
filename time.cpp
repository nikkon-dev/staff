#include <ctime>
#include <iostream>

using namespace std;
// $ perl -e 'use POSIX; for (my $i = 0 ; $i < 4 * 86400; $i += 86400) { print strftime("%Y%m%d\n", localtime(972676800 + $i)); }'

long getOffset() {
    time_t secs, local_secs, gmt_secs;
    time(&secs); // current time in gmt
    tm* tptr = localtime(&secs);
    local_secs = mktime(tptr);
    tptr = gmtime(&secs);
    gmt_secs = mktime(tptr);
    return long(local_secs - gmt_secs);
}
static void shift_days_to_str(time_t start, long gmt_offset, int days) {
    tm current = *gmtime(&start);
    current.tm_sec += gmt_offset;
    current.tm_mday += days;
    mktime(&current);
    char buf[9] = {0};
    strftime(buf, sizeof(buf), "%Y%m%d", &current);
    cout << buf << endl;
}

int main()
{
    long offset = getOffset();
    time_t lt = 972676800;
    for (int i = -10; i < 10; ++i) {
        shift_days_to_str(lt, offset, i);
    }
    return 0;
}