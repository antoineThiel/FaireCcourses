#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <libintl.h>

#include <mysql/mysql.h>
#include <gtk/gtk.h>

#include "commons.h"

#include "gtk_fonctions.h"
#include "sql_fonctions.h"
#include "views.h"
#include "pathAstar.h"

#define _(STRING) gettext(STRING)
