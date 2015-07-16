/* rous-mola-bot: If someone says `Rous' or `Rosa' (like that or in capital
 *         letters) send a message praising Rosa
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
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "message.h"
#include "bot_key.h"

typedef unsigned long int size_type;

typedef enum {
    size_type size;
    char* text;
} json_message;

size_type read_message(void* raw_message, size_type size, size_type nmemb, void* dest)
{
    size_type real_size = size * nmemb;
    json_message* dest_message = (json_message*) dest;

    dest_message->text = realloc(dest_message->text, dest_message->size + real_size);
    if (dest_message->text == NULL)
    {
        fprintf(stderr, "Error: Rosa no mola, o no hay memoria suficiente\n");
        return 0;
    }

    memcpy(&(dest_message->text[dest_message->size]), raw_message, real_size);
    dest_message->size += real_size;
    dest_message->message[dest_message->size] = '\0';

    return real_size;
}

int main(int argc, char** argv)
{
    CURL* easy_handle = curl_easy_init();
    CURLcode result;
    json_message in_message;
    char out_params[72] = "chat_id=";
    char* chat_id;
    char* message_text;
    char* message_id;

    strcat(out_params, chat_id);
    strcat(out_params, "&text=Rous mola");
    printf("%s\n", params);

    curl_global_init(CURL_GLOBAL_ALL);

    curl_setopt(easy_handle, CURLOPT_URL, "https://api.telegram.org/bot" BOT_KEY "/getUpdates?limit=1&offset=0");
    curl_setopt(easy_handle, CURLOPT_WRITEFUNCTION, read_message);
    curl_setopt(easy_handle, CURLOPT_WRITEDATA, in_message);
    curl_easy_perform(easy_handle);

    json_field(in_message, "text", STRING, &message_text);
    json_field(in_message, "update_id", INT, &message_id);
    json_field(in_message, "chat", INT, &chat_id);

    /*
    curl_setopt(easy_handle, CURLOPT_URL, "https://api.telegram.org/bot" BOT_KEY "/sendMessage");
    curl_setopt(easy_handle, CURLOPT_READFUNCTION, read_data);
    */
    result = curl_easy_perform(easy_handle);

    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: Rosa no mola, u ocurrió algún error con cURL\n");
    }
    else
    {
    }

    curl_global_cleanup();

    return 0;
}
