/* rous-mola-bot: If someone says `Rous' or `Rosa' (like that or in capital
 *         letters) send a message praising Rosa
 * message.c: Parse the Telegram API messages
 * Copyright (C) 2015  Jaime Mosquera  _Rosa Veiga_
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

/* Esta función busca «Rosa», «Rous», «ROSA» o «ROUS» en full_message; si se
 * encuentra, devuelve 1; si no, devuelve 0.
 *
 * La forma más fácil de hacerlo sería ir con un for desde 0 hasta size-4 (no
 * incluido), poner una «centinela» cuatro caracteres por delante (guardar el
 * valor que está cuatro caracteres por delante en otra variable y meter un
 * '\0' ahí), y usar strcmp (nota: strcmp devuelve 0 cuando son iguales, y !=0
 * cuando son diferentes). Después devuelves el valor que moviste a su
 * posición original.
 *
 * También puedes usar if, que ahorran el tiempo de hacer una llamada a una
 * función (aunque tampoco es una gran ganancia).
 */

#include <string.h>
#include <stdlib.h>

char search_mention(char* full_message) {

    int i = 0;
    char aux;
    size_t searchable_length = strlen(full_message) - 4;

    if (full_message == NULL)
        return 0;

    while (i < searchable_length && *(full_message + i) != '\0') {
        aux = *(full_message + i + 4);
        *(full_message + i + 4) = '\0';
        if (strcmp(full_message + i, "Rosa") * strcmp(full_message + i, "Rous") * strcmp(full_message + i, "ROSA") * strcmp(full_message + i, "ROUS") == 0) {
            *(full_message + i + 4) = aux;
            return 1;
        }
        *(full_message + i + 4) = aux;
        i++;
    }

    return 0;
}

#define INT 0
#define STRING 1

/* ¡Ahora vas a aprender a leer mensajes en JSON, el formato favorito de Pablo
 * Rivas! (no sé si lo de Telegram es JSON de verdad o una copia, pero algo
 * vas a aprender xD)
 *
 * Lo que esta función hace es buscar el valor de  field  entre dos comillas
 * (siempre entre dos comillas), y leer lo que viene después de eso y dos
 * puntos. (Si  field  es "message", buscas "message":"Lo que sea" y devuelves
 * "Lo que sea".) Si  type  es STRING, lo que aparece a la derecha de los dos
 * puntos está entre comillas (ignora las comillas); si es INTEGER, no hay
 * comillas alrededor del número.
 *
 * En cualquier caso, devuelve una cadena con el valor, sea cadena o entero.
 */
void json_field(char* full_message, const char* field, char type, char** value) {

    int i = 0, j = 0, k = 0;
    size_t len = strlen(field);

    while (*(full_message + i) != '\0') {
        if (*(full_message + i) == '\\')
            i++;
        else {
            if (*(full_message + i) == '"') {
                if (*(full_message + i + len) == '"') {
                    for (j = 0; j < len; j++)
                        if (*(full_message + i + j) != *(field + j))
                            goto CONTINUE;                      
                    if (*(full_message + i + len + 1) == ':') {
                        if (type == INT) {
                            j = 0;
                            if (*(full_message + i + len + 2) == '-')
                                j++;
                            while (1) {
                                if ((*(full_message + i + len + 2 + j) >= '0')&&(*(full_message + i + len + 2 + j) <= '9'))
                                    j++;
                                else
                                    break;
                            }
                            *value = (char*) malloc(j);
                            for (k = 0; k < j; k++)
                                *(*value + k) = *(full_message + i + len + 3 + j);
                        }
                        if (type == STRING) {
                            j = 0;
                            if (*(full_message + i + len + 2) != '"') {
                                *value = NULL;
                            }
                            while (1) {
                                if (*(full_message + i + len + 3 + j) == '\\') {
                                    j += 2;
                                    k++;
                                    continue;
                                }
                                if ((*(full_message + i + len + 3 + j) != '"')){
                                    j++;
                                    k++;
                                }
                                else
                                    break;
                            }
                            *value = (char*) malloc(sizeof(char) * k);
                            for (j = 0; j < k; j++) {
                                if (*(full_message + i + len + 3 + j) == '\\')
                                    continue;
                                *(*value + j) = *(full_message + i + len + 3 + k);
                            }
                        }

                    }

CONTINUE:
                    continue;
                }
            }
        }
        i++;
    }

    return;
}
