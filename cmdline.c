/*
  File autogenerated by gengetopt version 2.22.5
  generated with the following command:
  gengetopt --file-name=cmdline 

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

const char *gengetopt_args_info_purpose = "";

const char *gengetopt_args_info_usage = "Usage: stegobmp [OPTIONS]...";

const char *gengetopt_args_info_description = "StegoBMP permite ocultar un archivo cualquiera dentro de un archivo .bmp, \nmediante un m�todo de esteganografiado elegido, con o sin password. Tambien \npermite estegoanalizar un archivo y extraer el contenido previamente \nesteganografiado.";

const char *gengetopt_args_info_detailed_help[] = {
  "  -h, --help                    Print help and exit",
  "      --detailed-help           Print help, including all details and hidden \n                                  options, and exit",
  "  -V, --version                 Print version and exit",
  "\n Mode: ENCRYPT\n  Modo de encripcion",
  "      --embed                   Indica que se ocultara informacion",
  "      --in=Input filename       Archivo que se va a ocultar",
  "\n Mode: DECRYPT\n  Modo de desencripcion",
  "      --extract                 Indica que se extraera la informacion oculta en \n                                  un BMP",
  "      --out=Output filename     Archivo BMP de entrada/salida",
  "  Si el modo de operacion es de encripcion, corresponde al archivo de salida en \n  el que se guardara la informacion; si se esta en el modo de operacion de \n  desencripcion corresponde al archivo en el que se dejara el contenido \n  previamente esteganografiado",
  "      --steg=Nombre del algoritmo de esteganografiado\n                                Algoritmo de esteganografiado  (possible \n                                  values=\"LSB1\", \"LSB4\", \"LSBE\")",
  "      --p=BMP filename          Archivo BMP portador",
  "  -a, --a=Nombre del algoritmo de encripcion\n                                Algoritmo de encripcion  (possible \n                                  values=\"aes128\", \"aes192\", \"aes256\", \n                                  \"des\" default=`aes128')",
  "  -m, --m=Modo de encadenamiento para OPENSSL\n                                Modo de encadenamiento  (possible \n                                  values=\"ecb\", \"cfb\", \"ofb\", \"cbc\" \n                                  default=`cbc')",
  "      --pass=Password de encripcion\n                                Password de encripcion",
    0
};

static void
init_help_array(void)
{
  gengetopt_args_info_help[0] = gengetopt_args_info_detailed_help[0];
  gengetopt_args_info_help[1] = gengetopt_args_info_detailed_help[1];
  gengetopt_args_info_help[2] = gengetopt_args_info_detailed_help[2];
  gengetopt_args_info_help[3] = gengetopt_args_info_detailed_help[3];
  gengetopt_args_info_help[4] = gengetopt_args_info_detailed_help[4];
  gengetopt_args_info_help[5] = gengetopt_args_info_detailed_help[5];
  gengetopt_args_info_help[6] = gengetopt_args_info_detailed_help[6];
  gengetopt_args_info_help[7] = gengetopt_args_info_detailed_help[7];
  gengetopt_args_info_help[8] = gengetopt_args_info_detailed_help[8];
  gengetopt_args_info_help[9] = gengetopt_args_info_detailed_help[10];
  gengetopt_args_info_help[10] = gengetopt_args_info_detailed_help[11];
  gengetopt_args_info_help[11] = gengetopt_args_info_detailed_help[12];
  gengetopt_args_info_help[12] = gengetopt_args_info_detailed_help[13];
  gengetopt_args_info_help[13] = gengetopt_args_info_detailed_help[14];
  gengetopt_args_info_help[14] = 0; 
  
}

const char *gengetopt_args_info_help[15];

typedef enum {ARG_NO
  , ARG_STRING
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

const char *cmdline_parser_steg_values[] = {"LSB1", "LSB4", "LSBE", 0}; /*< Possible values for steg. */
const char *cmdline_parser_a_values[] = {"aes128", "aes192", "aes256", "des", 0}; /*< Possible values for a. */
const char *cmdline_parser_m_values[] = {"ecb", "cfb", "ofb", "cbc", 0}; /*< Possible values for m. */

static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->detailed_help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->embed_given = 0 ;
  args_info->in_given = 0 ;
  args_info->extract_given = 0 ;
  args_info->out_given = 0 ;
  args_info->steg_given = 0 ;
  args_info->p_given = 0 ;
  args_info->a_given = 0 ;
  args_info->m_given = 0 ;
  args_info->pass_given = 0 ;
  args_info->DECRYPT_mode_counter = 0 ;
  args_info->ENCRYPT_mode_counter = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  FIX_UNUSED (args_info);
  args_info->in_arg = NULL;
  args_info->in_orig = NULL;
  args_info->out_arg = NULL;
  args_info->out_orig = NULL;
  args_info->steg_arg = NULL;
  args_info->steg_orig = NULL;
  args_info->p_arg = NULL;
  args_info->p_orig = NULL;
  args_info->a_arg = gengetopt_strdup ("aes128");
  args_info->a_orig = NULL;
  args_info->m_arg = gengetopt_strdup ("cbc");
  args_info->m_orig = NULL;
  args_info->pass_arg = NULL;
  args_info->pass_orig = NULL;
  
}

static
void init_args_info(struct gengetopt_args_info *args_info)
{

  init_help_array(); 
  args_info->help_help = gengetopt_args_info_detailed_help[0] ;
  args_info->detailed_help_help = gengetopt_args_info_detailed_help[1] ;
  args_info->version_help = gengetopt_args_info_detailed_help[2] ;
  args_info->embed_help = gengetopt_args_info_detailed_help[4] ;
  args_info->in_help = gengetopt_args_info_detailed_help[5] ;
  args_info->extract_help = gengetopt_args_info_detailed_help[7] ;
  args_info->out_help = gengetopt_args_info_detailed_help[8] ;
  args_info->steg_help = gengetopt_args_info_detailed_help[10] ;
  args_info->p_help = gengetopt_args_info_detailed_help[11] ;
  args_info->a_help = gengetopt_args_info_detailed_help[12] ;
  args_info->m_help = gengetopt_args_info_detailed_help[13] ;
  args_info->pass_help = gengetopt_args_info_detailed_help[14] ;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n",
     (strlen(CMDLINE_PARSER_PACKAGE_NAME) ? CMDLINE_PARSER_PACKAGE_NAME : CMDLINE_PARSER_PACKAGE),
     CMDLINE_PARSER_VERSION);
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
cmdline_parser_print_detailed_help (void)
{
  int i = 0;
  print_help_common();
  while (gengetopt_args_info_detailed_help[i])
    printf("%s\n", gengetopt_args_info_detailed_help[i++]);
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);
  init_args_info (args_info);
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

  free_string_field (&(args_info->in_arg));
  free_string_field (&(args_info->in_orig));
  free_string_field (&(args_info->out_arg));
  free_string_field (&(args_info->out_orig));
  free_string_field (&(args_info->steg_arg));
  free_string_field (&(args_info->steg_orig));
  free_string_field (&(args_info->p_arg));
  free_string_field (&(args_info->p_orig));
  free_string_field (&(args_info->a_arg));
  free_string_field (&(args_info->a_orig));
  free_string_field (&(args_info->m_arg));
  free_string_field (&(args_info->m_orig));
  free_string_field (&(args_info->pass_arg));
  free_string_field (&(args_info->pass_orig));
  
  

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
  if (args_info->detailed_help_given)
    write_into_file(outfile, "detailed-help", 0, 0 );
  if (args_info->version_given)
    write_into_file(outfile, "version", 0, 0 );
  if (args_info->embed_given)
    write_into_file(outfile, "embed", 0, 0 );
  if (args_info->in_given)
    write_into_file(outfile, "in", args_info->in_orig, 0);
  if (args_info->extract_given)
    write_into_file(outfile, "extract", 0, 0 );
  if (args_info->out_given)
    write_into_file(outfile, "out", args_info->out_orig, 0);
  if (args_info->steg_given)
    write_into_file(outfile, "steg", args_info->steg_orig, cmdline_parser_steg_values);
  if (args_info->p_given)
    write_into_file(outfile, "p", args_info->p_orig, 0);
  if (args_info->a_given)
    write_into_file(outfile, "a", args_info->a_orig, cmdline_parser_a_values);
  if (args_info->m_given)
    write_into_file(outfile, "m", args_info->m_orig, cmdline_parser_m_values);
  if (args_info->pass_given)
    write_into_file(outfile, "pass", args_info->pass_orig, 0);
  

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
  int error = 0;
  FIX_UNUSED (additional_error);

  /* checks for required options */
  if (args_info->ENCRYPT_mode_counter && ! args_info->embed_given)
    {
      fprintf (stderr, "%s: '--embed' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (args_info->ENCRYPT_mode_counter && ! args_info->in_given)
    {
      fprintf (stderr, "%s: '--in' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (args_info->DECRYPT_mode_counter && ! args_info->extract_given)
    {
      fprintf (stderr, "%s: '--extract' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->out_given)
    {
      fprintf (stderr, "%s: '--out' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->steg_given)
    {
      fprintf (stderr, "%s: '--steg' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  if (! args_info->p_given)
    {
      fprintf (stderr, "%s: '--p' option required%s\n", prog_name, (additional_error ? additional_error : ""));
      error = 1;
    }
  
  
  /* checks for dependences among options */

  return error;
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
  char **string_field;
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
  case ARG_STRING:
    if (val) {
      string_field = (char **)field;
      if (!no_free && *string_field)
        free (*string_field); /* free previous string */
      *string_field = gengetopt_strdup (val);
    }
    break;
  default:
    break;
  };


  /* store the original value */
  switch(arg_type) {
  case ARG_NO:
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


static int check_modes(
  int given1[], const char *options1[],
                       int given2[], const char *options2[])
{
  int i = 0, j = 0, errors = 0;
  
  while (given1[i] >= 0) {
    if (given1[i]) {
      while (given2[j] >= 0) {
        if (given2[j]) {
          ++errors;
          fprintf(stderr, "%s: option %s conflicts with option %s\n",
                  package_name, options1[i], options2[j]);
        }
        ++j;
      }
    }
    ++i;
  }
  
  return errors;
}

int
cmdline_parser_internal (
  int argc, char **argv, struct gengetopt_args_info *args_info,
                        struct cmdline_parser_params *params, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */

  int error = 0;
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
        { "detailed-help",	0, NULL, 0 },
        { "version",	0, NULL, 'V' },
        { "embed",	0, NULL, 0 },
        { "in",	1, NULL, 0 },
        { "extract",	0, NULL, 0 },
        { "out",	1, NULL, 0 },
        { "steg",	1, NULL, 0 },
        { "p",	1, NULL, 0 },
        { "a",	1, NULL, 'a' },
        { "m",	1, NULL, 'm' },
        { "pass",	1, NULL, 0 },
        { 0,  0, 0, 0 }
      };

      c = getopt_long (argc, argv, "hVa:m:", long_options, &option_index);

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

        case 'a':	/* Algoritmo de encripcion.  */
        
        
          if (update_arg( (void *)&(args_info->a_arg), 
               &(args_info->a_orig), &(args_info->a_given),
              &(local_args_info.a_given), optarg, cmdline_parser_a_values, "aes128", ARG_STRING,
              check_ambiguity, override, 0, 0,
              "a", 'a',
              additional_error))
            goto failure;
        
          break;
        case 'm':	/* Modo de encadenamiento.  */
        
        
          if (update_arg( (void *)&(args_info->m_arg), 
               &(args_info->m_orig), &(args_info->m_given),
              &(local_args_info.m_given), optarg, cmdline_parser_m_values, "cbc", ARG_STRING,
              check_ambiguity, override, 0, 0,
              "m", 'm',
              additional_error))
            goto failure;
        
          break;

        case 0:	/* Long option with no short option */
          if (strcmp (long_options[option_index].name, "detailed-help") == 0) {
            cmdline_parser_print_detailed_help ();
            cmdline_parser_free (&local_args_info);
            exit (EXIT_SUCCESS);
          }

          /* Indica que se ocultara informacion.  */
          if (strcmp (long_options[option_index].name, "embed") == 0)
          {
            args_info->ENCRYPT_mode_counter += 1;
          
          
            if (update_arg( 0 , 
                 0 , &(args_info->embed_given),
                &(local_args_info.embed_given), optarg, 0, 0, ARG_NO,
                check_ambiguity, override, 0, 0,
                "embed", '-',
                additional_error))
              goto failure;
          
          }
          /* Archivo que se va a ocultar.  */
          else if (strcmp (long_options[option_index].name, "in") == 0)
          {
            args_info->ENCRYPT_mode_counter += 1;
          
          
            if (update_arg( (void *)&(args_info->in_arg), 
                 &(args_info->in_orig), &(args_info->in_given),
                &(local_args_info.in_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "in", '-',
                additional_error))
              goto failure;
          
          }
          /* Indica que se extraera la informacion oculta en un BMP.  */
          else if (strcmp (long_options[option_index].name, "extract") == 0)
          {
            args_info->DECRYPT_mode_counter += 1;
          
          
            if (update_arg( 0 , 
                 0 , &(args_info->extract_given),
                &(local_args_info.extract_given), optarg, 0, 0, ARG_NO,
                check_ambiguity, override, 0, 0,
                "extract", '-',
                additional_error))
              goto failure;
          
          }
          /* Archivo BMP de entrada/salida.  */
          else if (strcmp (long_options[option_index].name, "out") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->out_arg), 
                 &(args_info->out_orig), &(args_info->out_given),
                &(local_args_info.out_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "out", '-',
                additional_error))
              goto failure;
          
          }
          /* Algoritmo de esteganografiado.  */
          else if (strcmp (long_options[option_index].name, "steg") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->steg_arg), 
                 &(args_info->steg_orig), &(args_info->steg_given),
                &(local_args_info.steg_given), optarg, cmdline_parser_steg_values, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "steg", '-',
                additional_error))
              goto failure;
          
          }
          /* Archivo BMP portador.  */
          else if (strcmp (long_options[option_index].name, "p") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->p_arg), 
                 &(args_info->p_orig), &(args_info->p_given),
                &(local_args_info.p_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "p", '-',
                additional_error))
              goto failure;
          
          }
          /* Password de encripcion.  */
          else if (strcmp (long_options[option_index].name, "pass") == 0)
          {
          
          
            if (update_arg( (void *)&(args_info->pass_arg), 
                 &(args_info->pass_orig), &(args_info->pass_given),
                &(local_args_info.pass_given), optarg, 0, 0, ARG_STRING,
                check_ambiguity, override, 0, 0,
                "pass", '-',
                additional_error))
              goto failure;
          
          }
          
          break;
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */



  if (args_info->DECRYPT_mode_counter && args_info->ENCRYPT_mode_counter) {
    int DECRYPT_given[] = {args_info->extract_given,  -1};
    const char *DECRYPT_desc[] = {"--extract",  0};
    int ENCRYPT_given[] = {args_info->embed_given, args_info->in_given,  -1};
    const char *ENCRYPT_desc[] = {"--embed", "--in",  0};
    error += check_modes(DECRYPT_given, DECRYPT_desc, ENCRYPT_given, ENCRYPT_desc);
  }
  
  if (check_required)
    {
      error += cmdline_parser_required2 (args_info, argv[0], additional_error);
    }

  cmdline_parser_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  return 0;

failure:
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}
