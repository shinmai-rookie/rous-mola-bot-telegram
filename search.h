/* rous-mola-bot: If someone says `Rous' or `Rosa' (like that or in capital
 *         letters) send a message praising Rosa
 * Copyright (C) 2015  Jaime Mosquera, Rosa Veiga
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

/* Search `Rous' or `Rosa' in  full_message */
char search_mention(char* full_message);

#define INT 0
#define STRING 1

/* Save the value in the field  field,  which may be an integer or a string, as read from the JSON-formatted message  full_message */
void json_field(char* full_message, const char* field, char type,
                char** value);
