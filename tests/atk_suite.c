/*
 * AT-SPI - Assistive Technology Service Provider Interface
 * (Gnome Accessibility Project; https://wiki.gnome.org/Accessibility)
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "atk_suite.h"
#include "atk_test_util.h"

static gchar *tdata_list = NULL;
static gchar *one_test = NULL;

typedef struct _Atk_Test_Case Atk_Test_Case;

struct _Atk_Test_Case {
  const char *test_case;
  void (*build)( void);
};

static const Atk_Test_Case atc[] = {
  { ATK_TEST_PATH_ACCESSIBLE, atk_test_accessible },
  { ATK_TEST_PATH_ACTION, atk_test_action },
  { ATK_TEST_PATH_COMP, atk_test_component },
  { NULL, NULL}
};

static void
_list_tests (void)
{
  const Atk_Test_Case *itr;

  itr = atc;
  g_print ("Available Test Cases:\n");
  for (; itr->test_case; itr++)
    g_print ("\t%s\n", itr->test_case);
}

static void
atk_suite_build (int argc, char **argv )
{
  g_test_init (&argc, &argv, NULL);
  atk_test_accessible ();
  atk_test_action ();
  atk_test_component ();
}

static GOptionEntry optentries[] = {
  {"list", 'l', 0, G_OPTION_ARG_NONE, &tdata_list, "Display all available test cases", NULL},
  {"separate", 0, 0, G_OPTION_ARG_STRING, &one_test, "Run only NAME test", "NAME"},
  {NULL}
};

int
main(int argc, char **argv)
{
  int test_result;
  GOptionContext *opt;
  opt = g_option_context_new (NULL);
  g_option_context_add_main_entries (opt, optentries, NULL);
  g_option_context_set_help_enabled (opt, TRUE);
  g_option_context_set_ignore_unknown_options (opt, TRUE);

  if (!g_option_context_parse (opt, &argc, &argv, NULL))
    return EXIT_FAILURE;

  if (tdata_list) {
    _list_tests();
    return EXIT_SUCCESS;
  }

  clean_exit_on_fail ();

  if (one_test) {
    if (!g_strcmp0 (one_test, "Accessible")) {
      g_test_init (&argc, &argv, NULL);
      atk_test_accessible ();
      test_result = g_test_run ();
      return (test_result == 0 ) ? 0 : 255;
    }
    if (!g_strcmp0 (one_test, "Action")) {
      g_test_init (&argc, &argv, NULL);
      atk_test_action ();
      test_result = g_test_run ();
      return (test_result == 0 ) ? 0 : 255;
    }
    if (!g_strcmp0(one_test, "Component")) {
      g_test_init (&argc, &argv, NULL);
      atk_test_component ();
      test_result = g_test_run ();
      return ( test_result == 0 ) ? 0 : 255;
    }
    g_print ("Unknown test name\n");
    _list_tests ();
    return EXIT_SUCCESS;
  }
  atk_suite_build (argc, argv);
  test_result = g_test_run ();

  return (test_result == 0 ) ? 0 : 255;

}