/*
  File autogenerated by gengetopt version 2.22.6
  generated with the following command:
  gengetopt --output-dir autogen -i args.ggo --default-optional --unamed-opts=files

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FIX_UNUSED
#define FIX_UNUSED(X) (void) (X) /* avoid warnings for unused params */
#endif

#include <getopt.h>

#include "cmdline.h"

const char *gengetopt_args_info_purpose = "A parallel toolkit, implemented with Pthreads (or MPI), to calculate the\n community quality metrics with and without ground truth community structure.\n\nPaper: Mingming Chen, Sisi Liu, and Boleslaw Szymanski, \"Parallel Toolkit for\n Measuring the Quality of Network Community Structure\", The First European\n Network Intelligence Conference (ENIC), Wroclaw, Poland, September, 2014, pp.\n22-29.\n";

const char *gengetopt_args_info_usage = "Usage: pcomet [OPTIONS] ground-truth|ipnut-network clustering\n\n  ground-truth  - ground-truth clustering (communities) for the extrinsic\nmetrics evaluation. The clusterins are specified in the NCL format, where each\nline consists of the member node ids of the respective cluster (community).\n  ipnut-network  - input network for the intrinsic metrics evaluation. The\ninput network is specified in the NSL format, where each line describes the\nrespective link: <src_id> <dst_id> [<weight>].\n  clustering  - input file, collection of the clusters (detected communities)\nto be evaluated. in the NCL format, where each line list member node ids of the\nrespective cluster (community).\n\nExamples:\n  $ ./pcomet -n 4 -ef1m ./dataset/football_true_community.groups\n./dataset/football_detected_community.groups\n  $ ./pcomet -n 4 -i ./dataset/football_network.pairs\n./dataset/football_detected_community.groups\n";

const char *gengetopt_args_info_versiontext = "Authors: Mingming Chen <mileschen2008@gmail.com> and Sisi Liu\n<liusisiapply@gmail.com>\nCollaborator: Boleslaw K. Szymanski <szymab@rpi.edu>\nExtended by: Artem Lutov <artem@exascale.info>\nSources:  https://github.com/eXascaleInfolab/ParallelComMetric\n";

const char *gengetopt_args_info_description = "Extrinsic or intrinsic measures are evaluated. For the extrinsic measures, two\ninput clusterings (collections of clusters/communities) are compared to each\nother, whether one of them typically is a ground-truth clustering. For the\nintrinsic measures, the clustering is processed together with the respective\ninput network (graph).\n";

const char *gengetopt_args_info_help[] = {
  "  -h, --help              Print help and exit",
  "  -V, --version           Print version and exit",
  "  -n, --num=SHORT         the number of threads to be used.  (default=`1')",
  "  -f, --cpufreq=SHORT     CPU frequency to measure timing of the metrics, MHz\n                            (can be fetched by `$ lscpu`).  (default=`2100')",
  "\n Group: gr_metrics\n  Quality metrics type to be evaluated",
  "  -e, --extrinsic[=ENUM]  extrinsic quality metrics to be evaluated  (possible\n                            values=\"all\", \"f1m\", \"nvd\" default=`all')",
  "  -i, --intrinsic[=ENUM]  intrinsic quality metrics to be evaluated  (possible\n                            values=\"all\" default=`all')",
  "  -w, --weighted          the input network is weighted  (default=off)",
  "  -d, --directed          the input network is directed  (default=off)",
    0
};

typedef enum {ARG_NO
  , ARG_FLAG
  , ARG_SHORT
  , ARG_ENUM
} cmdline_parser_arg_type;

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error);

static int
cmdline_parser_required2 (struct gengetopt_args_info *args_info, const char *prog_name, const char *additional_error);

const char *cmdline_parser_extrinsic_values[] = {"all", "f1m", "nvd", 0}; /*< Possible values for extrinsic. */
const char *cmdline_parser_intrinsic_values[] = {"all", 0}; /*< Possible values for intrinsic. */

static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->num_given = 0 ;
  args_info->cpufreq_given = 0 ;
  args_info->extrinsic_given = 0 ;
  args_info->intrinsic_given = 0 ;
  args_info->weighted_given = 0 ;
  args_info->directed_given = 0 ;
  args_info->gr_metrics_group_counter = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->num_arg = 1;
  args_info->num_orig = NULL;
  args_info->cpufreq_arg = 2100;
  args_info->cpufreq_orig = NULL;
  args_info->extrinsic_arg = extrinsic_arg_all;
  args_info->extrinsic_orig = NULL;
  args_info->intrinsic_arg = intrinsic_arg_all;
  args_info->intrinsic_orig = NULL;
  args_info->weighted_flag = 0;
  args_info->directed_flag = 0;
  
}

static
void init_args_info(struct gengetopt_args_info *args_info)
{


  args_info->help_help = gengetopt_args_info_help[0] ;
  args_info->version_help = gengetopt_args_info_help[1] ;
  args_info->num_help = gengetopt_args_info_help[2] ;
  args_info->cpufreq_help = gengetopt_args_info_help[3] ;
  args_info->extrinsic_help = gengetopt_args_info_help[5] ;
  args_info->intrinsic_help = gengetopt_args_info_help[6] ;
  args_info->weighted_help = gengetopt_args_info_help[7] ;
  args_info->directed_help = gengetopt_args_info_help[8] ;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n",
     (strlen(CMDLINE_PARSER_PACKAGE_NAME) ? CMDLINE_PARSER_PACKAGE_NAME : CMDLINE_PARSER_PACKAGE),
     CMDLINE_PARSER_VERSION);

  if (strlen(gengetopt_args_info_versiontext) > 0)
    printf("\n%s\n", gengetopt_args_info_versiontext);
}

static void print_help_common(void) {
  cmdline_parser_print_version ();

  if (strlen(gengetopt_args_info_purpose) > 0)
    printf("\n%s\n", gengetopt_args_info_purpose);

  if (strlen(gengetopt_args_info_usage) > 0)
    printf("\n%s\n", gengetopt_args_info_usage);

  printf("\n");

  if (strlen(gengetopt_args_info_description) > 0)
    printf("%s\n\n", gengetopt_args_info_description);
}

void
cmdline_parser_print_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_help[i])
    printf("%s\n", gengetopt_args_info_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);

  args_info->inputs = 0;
  args_info->inputs_num = 0;
}

void
cmdline_parser_params_init(struct cmdline_parser_params *params)
{
  if (params)
    { 
      params->override = 0;
      params->initialize = 1;
      params->check_required = 1;
      params->check_ambiguity = 0;
      params->print_errors = 1;
    }
}

struct cmdline_parser_params *
cmdline_parser_params_create(void)
{
  struct cmdline_parser_params *params = 
    (struct cmdline_parser_params *)malloc(sizeof(struct cmdline_parser_params));
  cmdline_parser_params_init(params);  
  return params;
}

static void
free_string_field (char **s)
{
  if (*s)
    {
      free (*s);
      *s = 0;
    }
}


static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{
  unsigned int i;
  free_string_field (&(args_info->num_orig));
  free_string_field (&(args_info->cpufreq_orig));
  free_string_field (&(args_info->extrinsic_orig));
  free_string_field (&(args_info->intrinsic_orig));
  
  
  for (i = 0; i < args_info->inputs_num; ++i)
    free (args_info->inputs [i]);

  if (args_info->inputs_num)
    free (args_info->inputs);

  clear_given (args_info);
}

/**
 * @param val the value to check
 * @param values the possible values
 * @return the index of the matched value:
 * -1 if no value matched,
 * -2 if more than one value has matched
 */
static int
check_possible_values(const char *val, const char *values[])
{
  int i, found, last;
  size_t len;

  if (!val)   /* otherwise strlen() crashes below */
    return -1; /* -1 means no argument for the option */

  found = last = 0;

  for (i = 0, len = strlen(val); values[i]; ++i)
    {
      if (strncmp(val, values[i], len) == 0)
        {
          ++found;
          last = i;
          if (strlen(values[i]) == len)
            return i; /* exact macth no need to check more */
        }
    }

  if (found == 1) /* one match: OK */
    return last;

  return (found ? -2 : -1); /* return many values or none matched */
}


static void
write_into_file(FILE *outfile, const char *opt, const char *arg, const char *values[])
{
  int found = -1;
  if (arg) {
    if (values) {
      found = check_possible_values(arg, values);      
    }
    if (found >= 0)
      fprintf(outfile, "%s=\"%s\" # %s\n", opt, arg, values[found]);
    else
      fprintf(outfile, "%s=\"%s\"\n", opt, arg);
  } else {
    fprintf(outfile, "%s\n", opt);
  }
}


int
cmdline_parser_dump(FILE *outfile, struct gengetopt_args_info *args_info)
{
  int i = 0;

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot dump options to stream\n", CMDLINE_PARSER_PACKAGE);
      return EXIT_FAILURE;
    }

  if (args_info->help_given)
    write_into_file(outfile, "help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->num_given)
    write_into_file(outfile, "num", args_info->num_orig, 0);
  if (args_info->cpufreq_given)
    write_into_file(outfile, "cpufreq", args_info->cpufreq_orig, 0);
  if (args_info->extrinsic_given)
    write_into_file(outfile, "extrinsic", args_info->extrinsic_orig, cmdline_parser_extrinsic_values);
  if (args_info->intrinsic_given)
    write_into_file(outfile, "intrinsic", args_info->intrinsic_orig, cmdline_parser_intrinsic_values);
  if (args_info->weighted_given)
    write_into_file(outfile, "weighted", 0, 0 );
  if (args_info->directed_given)
    write_into_file(outfile, "directed", 0, 0 );
  

  i = EXIT_SUCCESS;
  return i;
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  i = cmdline_parser_dump(outfile, args_info);
  fclose (outfile);

  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}

/** @brief replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = 0;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

static void
reset_group_gr_metrics(struct gengetopt_args_info *args_info)
{
  if (! args_info->gr_metrics_group_counter)
    return;
  
  args_info->extrinsic_given = 0 ;
  free_string_field (&(args_info->extrinsic_orig));
  args_info->intrinsic_given = 0 ;
  free_string_field (&(args_info->intrinsic_orig));

  args_info->gr_metrics_group_counter = 0;
}

int
cmdline_parser (int argc, char **argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser_ext (int argc, char **argv, struct gengetopt_args_info *args_info,
                   struct cmdline_parser_params *params)
{
  int result;
  result = cmdline_parser_internal (argc, argv, args_info, params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser2 (int argc, char **argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;
  struct cmdline_parser_params params;
  
  params.override = override;
  params.initialize = initialize;
  params.check_required = check_required;
  params.check_ambiguity = 0;
  params.print_errors = 1;

  result = cmdline_parser_internal (argc, argv, args_info, &params, 0);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  int result = EXIT_SUCCESS;

  if (cmdline_parser_required2(args_info, prog_name, 0) > 0)
    result = EXIT_FAILURE;

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required2 (struct gengetopt_args_info *args_info, const char *prog_name, const char *additional_error)
{
  int error_occurred = 0;
  FIX_UNUSED (additional_error);

  /* checks for required options */
  if (args_info->gr_metrics_group_counter == 0)
    {
      fprintf (stderr, "%s: %d options of group gr_metrics were given. One is required%s.\n", prog_name, args_info->gr_metrics_group_counter, (additional_error ? additional_error : ""));
      error_occurred = 1;
    }
  

  /* checks for dependences among options */
  if (args_info->weighted_given && ! args_info->intrinsic_given)
    {
      fprintf (stderr, "%s: '--weighted' ('-w') option depends on option 'intrinsic'%s\n", prog_name, (additional_error ? additional_error : ""));
      error_occurred = 1;
    }
  if (args_info->directed_given && ! args_info->intrinsic_given)
    {
      fprintf (stderr, "%s: '--directed' ('-d') option depends on option 'intrinsic'%s\n", prog_name, (additional_error ? additional_error : ""));
      error_occurred = 1;
    }

  return error_occurred;
}


static char *package_name = 0;

/**
 * @brief updates an option
 * @param field the generic pointer to the field to update
 * @param orig_field the pointer to the orig field
 * @param field_given the pointer to the number of occurrence of this option
 * @param prev_given the pointer to the number of occurrence already seen
 * @param value the argument for this option (if null no arg was specified)
 * @param possible_values the possible values for this option (if specified)
 * @param default_value the default value (in case the option only accepts fixed values)
 * @param arg_type the type of this option
 * @param check_ambiguity @see cmdline_parser_params.check_ambiguity
 * @param override @see cmdline_parser_params.override
 * @param no_free whether to free a possible previous value
 * @param multiple_option whether this is a multiple option
 * @param long_opt the corresponding long option
 * @param short_opt the corresponding short option (or '-' if none)
 * @param additional_error possible further error specification
 */
static
int update_arg(void *field, char **orig_field,
               unsigned int *field_given, unsigned int *prev_given, 
               char *value, const char *possible_values[],
               const char *default_value,
               cmdline_parser_arg_type arg_type,
               int check_ambiguity, int override,
               int no_free, int multiple_option,
               const char *long_opt, char short_opt,
               const char *additional_error)
{
  char *stop_char = 0;
  const char *val = value;
  int found;
  FIX_UNUSED (field);

  stop_char = 0;
  found = 0;

  if (!multiple_option && prev_given && (*prev_given || (check_ambiguity && *field_given)))
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: `--%s' (`-%c') option given more than once%s\n", 
               package_name, long_opt, short_opt,
               (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: `--%s' option given more than once%s\n", 
               package_name, long_opt,
               (additional_error ? additional_error : ""));
      return 1; /* failure */
    }

  if (possible_values && (found = check_possible_values((value ? value : default_value), possible_values)) < 0)
    {
      if (short_opt != '-')
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s' (`-%c')%s\n", 
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt, short_opt,
          (additional_error ? additional_error : ""));
      else
        fprintf (stderr, "%s: %s argument, \"%s\", for option `--%s'%s\n", 
          package_name, (found == -2) ? "ambiguous" : "invalid", value, long_opt,
          (additional_error ? additional_error : ""));
      return 1; /* failure */
    }
    
  if (field_given && *field_given && ! override)
    return 0;
  if (prev_given)
    (*prev_given)++;
  if (field_given)
    (*field_given)++;
  if (possible_values)
    val = possible_values[found];

  switch(arg_type) {
  case ARG_FLAG:
    *((int *)field) = !*((int *)field);
    break;
  case ARG_SHORT:
    if (val) *((short *)field) = (short)strtol (val, &stop_char, 0);
    break;
  case ARG_ENUM:
    if (val) *((int *)field) = found;
    break;
  default:
    break;
  };

  /* check numeric conversion */
  switch(arg_type) {
  case ARG_SHORT:
    if (val && !(stop_char && *stop_char == '\0')) {
      fprintf(stderr, "%s: invalid numeric value: %s\n", package_name, val);
      return 1; /* failure */
    }
    break;
  default:
    ;
  };

  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
  case ARG_FLAG:
    break;
  default:
    if (value && orig_field) {
      if (no_free) {
        *orig_field = value;
      } else {
        if (*orig_field)
          free (*orig_field); /* free previous string */
        *orig_field = gengetopt_strdup (value);
      }
    }
  };

  return 0; /* OK */
}


int
cmdline_parser_internal (
  int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error_occurred = 0;
  struct gengetopt_args_info local_args_info;
  
  int override;
  int initialize;
  int check_required;
  int check_ambiguity;
  
  package_name = argv[0];
  
  override = params->override;
  initialize = params->initialize;
  check_required = params->check_required;
  check_ambiguity = params->check_ambiguity;

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = params->print_errors;
  optopt = '?';

  while (1)
    {
      int option_index = 0;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "num",	1, NULL, 'n' },
        { "cpufreq",	1, NULL, 'f' },
        { "extrinsic",	2, NULL, 'e' },
        { "intrinsic",	2, NULL, 'i' },
        { "weighted",	0, NULL, 'w' },
        { "directed",	0, NULL, 'd' },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "hVn:f:e::i::wd", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          cmdline_parser_print_help ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          cmdline_parser_print_version ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'n':	/* the number of threads to be used..  */
        
        
          if (update_arg( (void *)&(args_info->num_arg), 
               &(args_info->num_orig), &(args_info->num_given),
              &(local_args_info.num_given), optarg, 0, "1", ARG_SHORT,
              check_ambiguity, override, 0, 0,
              "num", 'n',
              additional_error))
            goto failure;
        
          break;
        case 'f':	/* CPU frequency to measure timing of the metrics, MHz (can be fetched by `$ lscpu`)..  */
        
        
          if (update_arg( (void *)&(args_info->cpufreq_arg), 
               &(args_info->cpufreq_orig), &(args_info->cpufreq_given),
              &(local_args_info.cpufreq_given), optarg, 0, "2100", ARG_SHORT,
              check_ambiguity, override, 0, 0,
              "cpufreq", 'f',
              additional_error))
            goto failure;
        
          break;
        case 'e':	/* extrinsic quality metrics to be evaluated.  */
        
          if (args_info->gr_metrics_group_counter && override)
            reset_group_gr_metrics (args_info);
          args_info->gr_metrics_group_counter += 1;
        
          if (update_arg( (void *)&(args_info->extrinsic_arg), 
               &(args_info->extrinsic_orig), &(args_info->extrinsic_given),
              &(local_args_info.extrinsic_given), optarg, cmdline_parser_extrinsic_values, "all", ARG_ENUM,
              check_ambiguity, override, 0, 0,
              "extrinsic", 'e',
              additional_error))
            goto failure;
        
          break;
        case 'i':	/* intrinsic quality metrics to be evaluated.  */
        
          if (args_info->gr_metrics_group_counter && override)
            reset_group_gr_metrics (args_info);
          args_info->gr_metrics_group_counter += 1;
        
          if (update_arg( (void *)&(args_info->intrinsic_arg), 
               &(args_info->intrinsic_orig), &(args_info->intrinsic_given),
              &(local_args_info.intrinsic_given), optarg, cmdline_parser_intrinsic_values, "all", ARG_ENUM,
              check_ambiguity, override, 0, 0,
              "intrinsic", 'i',
              additional_error))
            goto failure;
        
          break;
        case 'w':	/* the input network is weighted.  */
        
        
          if (update_arg((void *)&(args_info->weighted_flag), 0, &(args_info->weighted_given),
              &(local_args_info.weighted_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "weighted", 'w',
              additional_error))
            goto failure;
        
          break;
        case 'd':	/* the input network is directed.  */
        
        
          if (update_arg((void *)&(args_info->directed_flag), 0, &(args_info->directed_given),
              &(local_args_info.directed_given), optarg, 0, 0, ARG_FLAG,
              check_ambiguity, override, 1, 0, "directed", 'd',
              additional_error))
            goto failure;
        
          break;

        case 0:	/* Long option with no short option */
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */

  if (args_info->gr_metrics_group_counter > 1)
    {
      fprintf (stderr, "%s: %d options of group gr_metrics were given. One is required%s.\n", argv[0], args_info->gr_metrics_group_counter, (additional_error ? additional_error : ""));
      error_occurred = 1;
    }
  


  if (check_required)
    {
      error_occurred += cmdline_parser_required2 (args_info, argv[0], additional_error);
    }

  cmdline_parser_release (&local_args_info);

  if ( error_occurred )
    return (EXIT_FAILURE);

  if (optind < argc)
    {
      int i = 0 ;
      int found_prog_name = 0;
      /* whether program name, i.e., argv[0], is in the remaining args
         (this may happen with some implementations of getopt,
          but surely not with the one included by gengetopt) */

      i = optind;
      while (i < argc)
        if (argv[i++] == argv[0]) {
          found_prog_name = 1;
          break;
        }
      i = 0;

      args_info->inputs_num = argc - optind - found_prog_name;
      args_info->inputs =
        (char **)(malloc ((args_info->inputs_num)*sizeof(char *))) ;
      while (optind < argc)
        if (argv[optind++] != argv[0])
          args_info->inputs[ i++ ] = gengetopt_strdup (argv[optind-1]) ;
    }

  return 0;

failure:
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}
