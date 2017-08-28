#include <stdio.h>
#include <getopt.h>
#include <unistd.h>

void parse_args(int argc, char *argv[])
{
    int choice;
    while (1)
    {
        static struct option long_options[] =
        {
            /* Use flags like so:
            {"verbose",	no_argument,	&verbose_flag, 'V'}*/
            /* Argument styles: no_argument, required_argument, optional_argument */
            {"version"    , no_argument , 0 , 'v'} ,
            {"help"       , no_argument , 0 , 'h'} ,
            {"optimaze"   , 1           , 0 , 'o'} ,
            {"Include"    , 2           , 0 , 'I'} ,
            {0            , 0           , 0 , 0}
        };

        int option_index = 0;

        /* Argument parameters:
            no_argument: " "
            required_argument: ":"
            optional_argument: "::" */

        choice = getopt_long( argc, argv, "vho:I::",
                    long_options, &option_index);

        if (choice == -1)
            break;

        switch( choice )
        {
            case 'v':
                printf("version\n");
                break;

            case 'h':
                printf("help\n");
                break;

            case 'o':
                printf("optimize level is %s\n", optarg);
                break;

            case 'I':
                printf("Include files is %s\n", optarg);
                break;

            case '?':
                /* getopt_long will have already printed an error */
                printf("unknow parameter\n");
                break;

            default:
                /* Not sure how to get here... */
                return;
        }
    }

    /* Deal with non-option arguments here */
    if ( optind < argc )
    {
        printf("input file is: \n");
        while ( optind < argc )
        {
            printf("\t%s\n", argv[optind]);
            optind++;
        }
    }
}

int main(int argc, char *argv[])
{
    parse_args(argc, argv);
    return 0;
}

