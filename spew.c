#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int Usage(const char *argv0)
{
    printf("Usage: %s [-t SECONDS] TEXT [-t SECONDS] TEXT ... | [-h|--help]\n"
            "\n"
            "  Spew TEXT to stdout then sleep SECONDS in the order\n"
            "that the arguments are given.  So for example:\n"
            "\n"
            "    %s \"hello world\\n\" -t 0.3 \"good day\\n\"\n"
            "\n"
            "will first print hello world and a new line, then it\n"
            "will wait 0.3 seconds, and then it will print good\n"
            "day and a new line and then it will exit.\n",
            argv0, argv0);
    return 1;
}

static int
Sleep(const char *s)
{
    double t;
    char *end = NULL;
    t = strtod(s, &end);
    if(s == end) return 1;
    usleep((useconds_t) (t * 1000000.5));
    return 0;
}

int main(int argc, char **argv)
{
    const char *argv0;
    argv0 = *argv;

    int i;
    for(i=1; i<argc; ++i)
        if(argv[i][0] == '-' && argv[i][1] != 't')
            return Usage(argv0);

    while(*(++argv))
    {
        if(strcmp(*argv, "-t") == 0 && *(argv+1))
        {
            if(Sleep(*(++argv))) return 1;
        }
        else if(strncmp(*argv, "-t", 2) == 0 && (*argv)[2])
        {
            if(Sleep(&(*argv)[2])) return 1;
        }
        else
        {
            char *s;
            s = *argv;
            while(*s)
            {
                if(*s == '\\' && *(s+1))
                {
                    ++s;
                    switch(*s)
                    {
                        case 'n':
                            putchar('\n');
                            break;
                        case 'r':
                            putchar('\r');
                            break;
                        case '\\':
                            putchar('\\');
                            break;
                        default:
                            putchar('\\');
                            putchar(*s);
                    }
                }
                else
                    putchar(*s);
                ++s;
            }
            fflush(stdout);
        }
    }
    return 0;
}

