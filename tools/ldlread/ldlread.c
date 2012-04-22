#include "getopt.h"

#include <ldl/ldl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Short command line options for get_opt */
const char * SHORT_OPTIONS = "hvl";
/* Long options for getopt_long */
const struct option LONG_OPTIONS[]=
{
    {"help",no_argument,NULL,'h'}, /*  Print help */
    {"verbose",no_argument,NULL,'v'}, /* Verbose mode */
    {"list",required_argument,NULL,'l'}, /*  List mode */
    {NULL, 0, NULL, 0} /*  End of array need by getopt_long do not delete it */
};

/* Handle command line options */
typedef struct cli_opts_t
{
    uint8_t verbose;
    uint8_t list;
} cli_opts_t;

/* Parse command line options and fill BruteOptions structure */
void parse_cli_opts(int argc, char **argv, cli_opts_t * opts);
/* Print usage on standard output */
void usage();

int main(int argc, char **argv)
{
    cli_opts_t opts;
    parse_cli_opts(argc, argv, &opts);

    int32_t ldlstatus;
    ldl_ctx_t ctx = ldl_ctx_create();
    ldlstatus = ldl_ctx_is_valid(&ctx);
    if (!ldlstatus)
    {
        perror("Impossible to start ldl interpretor");
        exit(1);
    }
    /*
    ldlstatus = ldl_ctx_execute(&ctx, argv[1]);
    if (ldlstatus == -1)
    {
        ldl_ctx_destroy(&ctx);
        exit(1);
    }
    */
    ldlstatus = ldl_ctx_execute_file(&ctx, argv[1]);
    if (ldlstatus == -1)
    {
        ldl_ctx_destroy(&ctx);
        exit(1);
    }
    ldlstatus = ldl_ctx_destroy(&ctx);

    return 0;
}

void parse_cli_opts(int argc, char **argv, cli_opts_t * opts)
{
    char c;
    int optIdx;
    opts->verbose = 0;
    opts->list = 0;
    while ((c = getopt_long(argc, argv, (char *) SHORT_OPTIONS, (struct option *) LONG_OPTIONS, &optIdx)) != -1)
    {
        switch (c)
        {
        case 'h' : /* Print usage and exit */
            usage();
            exit(0);
            break;
        case 'v' : /* Verbose mode */
            opts->verbose = 1;
            break;
        case 'l' :  /* List mode */
            opts->list = 1;
            break;
        case '?' : /* Wat? */
            fprintf(stderr, "Unknown option\n");
            usage();
            exit(1);
        default :
            break;
        }
    }
}

void usage()
{
    printf("ldlread [-hvl] \n");
}
