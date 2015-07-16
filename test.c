/* rous-mola-bot: If someone says `Rous' or `Rosa' (like that or in capital
 *         letters) send a message praising Rosa
 * test.c: Test if the functions work
 * Copyright (C) 2015  _Jaime Mosquera_  Rosa Veiga
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

#include <stdio.h>
#include <string.h>
#include "message.h"

int main(int argc, char** argv)
{
    char* fake_string;
    fake_string = (char*) malloc(1 * sizeof(char));
    fake_string[0] = '\0';

    printf("Searching `Rosa'/`Rous'/`ROSA'/`ROUS'\n");

    printf("... in \"Rosa mola\"          (most basic case): ");
    printf("%c [T]\n", search_mention("Rosa mola") ? 'T': 'F');
    printf("... in \"Creo que Rosa mola\" (inside a sentence): ");
    printf("%c [T]\n", search_mention("Creo que Rosa mola") ? 'T': 'F');
    printf("... in \"Hola, Rosa\"         (in the end of the sentence): ");
    printf("%c [T]\n\n", search_mention("Hola, Rosa")? 'T': 'F');

    printf("... in \"Rous mola\"          (most basic case): ");
    printf("%c [T]\n", search_mention("Rous mola") ? 'T': 'F');
    printf("... in \"Creo que Rous mola\" (inside a sentence): ");
    printf("%c [T]\n", search_mention("Creo que Rous mola") ? 'T': 'F');
    printf("... in \"Hola, Rous\"         (in the end of the sentence): ");
    printf("%c [T]\n\n", search_mention("Hola, Rous") ? 'T': 'F');

    printf("... in \"ROSA MOLA\"          (most basic case): ");
    printf("%c [T]\n", search_mention("ROSA MOLA") ? 'T': 'F');
    printf("... in \"CREO QUE ROSA MOLA\" (inside a sentence): ");
    printf("%c [T]\n", search_mention("CREO QUE ROSA MOLA") ? 'T': 'F');
    printf("... in \"HOLA, ROSA\"         (in the end of the sentence): ");
    printf("%c [T]\n\n", search_mention("HOLA, ROSA") ? 'T': 'F');

    printf("... in \"ROUS MOLA\"          (most basic case): ");
    printf("%c [T]\n", search_mention("ROUS MOLA") ? 'T': 'F');
    printf("... in \"CREO QUE ROUS MOLA\" (inside a sentence): ");
    printf("%c [T]\n", search_mention("CREO QUE ROUS MOLA") ? 'T': 'F');
    printf("... in \"HOLA, ROUS\"         (in the end of the sentence): ");
    printf("%c [T]\n\n", search_mention("HOLA, ROUS") ? 'T': 'F');

    printf("... in \"ROUs MOLA\"          (one wrongly cased letter): ");
    printf("%c [F]\n", search_mention("ROUs MOLA") ? 'T': 'F');
    printf("... in \"Creo que RosA mola\" (one wrongly cased letter): ");
    printf("%c [F]\n", search_mention("CREO QUE RosA MOLA") ? 'T': 'F');
    printf("... in \"Hola, rosa\"         (flower name instead of woman name): ");
    printf("%c [F]\n\n\n", search_mention("Hola, rosa") ? 'T': 'F');


    printf("Parsing JSON values: \n");

    /* free(fake_string); */
    printf("    message in `\"message\":\"Rous mola\"'\n");
    printf("        `%s' [`Rous mola']\n", (json_field("\"message\":\"Rous mola\"", "message", STRING, &fake_string), fake_string));
    /* free(fake_string); */
    printf("    time in `\"time\":1346124'\n");
    printf("        `%s' [`1346124']\n\n", (json_field("\"time\":1346124", "time", INT, &fake_string), fake_string));
    /* free(fake_string); */

    printf("    message in `\"message\":1' (expecting a string)\n");
    printf("        `%s' [`']\n", (json_field("\"message\":1", "message", STRING, &fake_string), fake_string));
    /* free(fake_string); */
    printf("    date in \"date\":\"date\" (expecting an int)\n");
    printf("        `%s' [`']\n\n", (json_field("\"date\":\"date\"", "message", INT, &fake_string), fake_string));
    /* free(fake_string); */

    printf("    message in `\"message\":bad' (badly formatted string)\n");
    printf("        `%s' [`']\n", (json_field("\"message\":bad", "message", STRING, &fake_string), fake_string));
    /* free(fake_string); */
    printf("    date in \"date\":\"102\" (badly formatted int)\n");
    printf("        `%s' [`']\n\n", (json_field("\"date\":\"102\"", "message", INT, &fake_string), fake_string));
    /* free(fake_string); */

    printf("    message in `\"message\":\"This is a \\\"message\\\"\"' (escaped `\"')\n");
    printf("        `%s' [`This is \"message\"']\n", (json_field("\"message\":bad", "message", STRING, &fake_string), fake_string));
    /* free(fake_string); */

    return 0;
}
