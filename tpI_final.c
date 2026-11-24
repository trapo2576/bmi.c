#include <stdlib.h>         //   https://github.com/trapo2576/bmi.c/new/main
#include <stdio.h>          // este bot recibe un hola y devuelve "hola_NOMBRE_clima_24"
#include <string.h>          // chau ........ "chau_NOMBRE_nos_vemos"
#include <unistd.h>           // parseo con cJSON
#include "cJSON.h"
#include <curl/curl.h>

typedef struct string_buffer_s
{
  char * ptr;
  size_t len;
} string_buffer_t;

static void string_buffer_initialize( string_buffer_t * sb )
{
  sb->len = 0;
  sb->ptr = malloc(sb->len+1);
  sb->ptr[0] = '\0';
}

static void string_buffer_finish( string_buffer_t * sb )
{
  free(sb->ptr);
  sb->len = 0;
  sb->ptr = NULL;
}

static size_t string_buffer_callback( void * buf, size_t size, size_t nmemb, void * data )
{
  string_buffer_t * sb = data;
  size_t new_len = sb->len + size * nmemb;
  sb->ptr = realloc( sb->ptr, new_len + 1 );
  memcpy( sb->ptr + sb->len, buf, size * nmemb );
  sb->ptr[ new_len ] = '\0';
  sb->len = new_len;
  return size * nmemb;
}

static size_t write_callback( void * buf, size_t size, size_t nmemb, void * data )
{
  return string_buffer_callback( buf, size, nmemb, data );
}

int main( int argc, char * argv[] )
{
  if (argc < 2)
  {
    fprintf(stderr, "Uso: %s <URL_API_CLIMA>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *archivo_token = fopen("token.txt", "r");
  if (!archivo_token)
  {
    fprintf(stderr, "Fatal: no se pudo abrir token.txt\n");
    return EXIT_FAILURE;
  }
  char token[200] = {0};
  fscanf(archivo_token, "%199s", token);
  fclose(archivo_token);

  CURL * curl_api1;
  CURL * curl_api2;
  CURLcode res;
  string_buffer_t strbuf;
  string_buffer_t strbuf2;
  char * url_api1 = argv[1];

  curl_api1 = curl_easy_init();
  if(!curl_api1)
  {
    fprintf(stderr, "Fatal: curl_easy_init() error.\n");
    return EXIT_FAILURE;
  }

  curl_api2 = curl_easy_init();
  if(!curl_api2)
  {
    fprintf(stderr, "Fatal: curl_easy_init() error.\n");
    curl_easy_cleanup( curl_api1 );
    return EXIT_FAILURE;
  }

  long ultimo_update = 0;
  printf("Bot iniciado. Esperando mensajes...\n");

  while (1)
  {
    char url_updates[500] = {0};
    snprintf(url_updates, sizeof(url_updates),
             "https://api.telegram.org/bot%s/getUpdates?offset=%ld",
             token, ultimo_update + 1);

    string_buffer_initialize( &strbuf );
    curl_easy_setopt(curl_api1, CURLOPT_URL, url_updates );
    curl_easy_setopt(curl_api1, CURLOPT_FOLLOWLOCATION, 1L );
    curl_easy_setopt(curl_api1, CURLOPT_WRITEFUNCTION, write_callback );
    curl_easy_setopt(curl_api1, CURLOPT_WRITEDATA, &strbuf );

    res = curl_easy_perform(curl_api1);
    if( res == CURLE_OK )
    {
      cJSON *json = cJSON_Parse(strbuf.ptr);
      cJSON *result = json ? cJSON_GetObjectItemCaseSensitive(json, "result") : NULL;
      int cantidad = result ? cJSON_GetArraySize(result) : 0;

      if (cantidad > 0)
      {
        cJSON *item = cJSON_GetArrayItem(result, 0);
        cJSON *update_id = item ? cJSON_GetObjectItemCaseSensitive(item, "update_id") : NULL;
        if (update_id)
          ultimo_update = (long)update_id->valuedouble;

        cJSON *message = item ? cJSON_GetObjectItemCaseSensitive(item, "message") : NULL;
        cJSON *text = message ? cJSON_GetObjectItemCaseSensitive(message, "text") : NULL;
        cJSON *chat = message ? cJSON_GetObjectItemCaseSensitive(message, "chat") : NULL;
        cJSON *chat_id = chat ? cJSON_GetObjectItemCaseSensitive(chat, "id") : NULL;
        cJSON *from = message ? cJSON_GetObjectItemCaseSensitive(message, "from") : NULL;
        cJSON *first_name = from ? cJSON_GetObjectItemCaseSensitive(from, "first_name") : NULL;

        if (text && text->valuestring && chat_id && first_name && first_name->valuestring)
        {
          printf("Mensaje recibido de %s: %s\n", first_name->valuestring, text->valuestring);

          if (strcmp(text->valuestring, "hola") == 0 || strcmp(text->valuestring, "Hola") == 0)
          {
            string_buffer_t strbuf_clima;
            string_buffer_initialize(&strbuf_clima);

            curl_easy_setopt(curl_api1, CURLOPT_URL, url_api1);
            curl_easy_setopt(curl_api1, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl_api1, CURLOPT_WRITEDATA, &strbuf_clima);

            res = curl_easy_perform(curl_api1);
            if (res == CURLE_OK)
            {
              cJSON *json_clima = cJSON_Parse(strbuf_clima.ptr);
              cJSON *current = json_clima ? cJSON_GetObjectItemCaseSensitive(json_clima, "current") : NULL;
              cJSON *temp = current ? cJSON_GetObjectItemCaseSensitive(current, "temperature_2m") : NULL;
              char *temp_cadena = temp ? cJSON_Print(temp) : NULL;

              if (temp_cadena)
              {
                char mensaje_enviar[1000] = {0};
                snprintf(mensaje_enviar, sizeof(mensaje_enviar),
                         "https://api.telegram.org/bot%s/sendMessage?chat_id=%.0f&text=hola_%s_clima_%s",
                         token, chat_id->valuedouble, first_name->valuestring, temp_cadena);

                for (int i = 0; mensaje_enviar[i] != 0; i++)
                  if (mensaje_enviar[i] == ' ')
                    mensaje_enviar[i] = '_';

                string_buffer_initialize(&strbuf2);
                curl_easy_setopt(curl_api2, CURLOPT_URL, mensaje_enviar);
                curl_easy_setopt(curl_api2, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt(curl_api2, CURLOPT_WRITEDATA, &strbuf2);
                printf("Enviando: %s\n", mensaje_enviar);
                curl_easy_perform(curl_api2);
                string_buffer_finish(&strbuf2);

                free(temp_cadena);
              }
              cJSON_Delete(json_clima);
            }
            string_buffer_finish(&strbuf_clima);
          }

          if (strcmp(text->valuestring, "chau") == 0 || strcmp(text->valuestring, "Chau") == 0)
          {
            char mensaje_enviar[1000] = {0};
            snprintf(mensaje_enviar, sizeof(mensaje_enviar),
                     "https://api.telegram.org/bot%s/sendMessage?chat_id=%.0f&text=chau_%s_nos_vemos",
                     token, chat_id->valuedouble, first_name->valuestring);

            for (int i = 0; mensaje_enviar[i] != 0; i++)
              if (mensaje_enviar[i] == ' ')
                mensaje_enviar[i] = '_';

            string_buffer_initialize(&strbuf2);
            curl_easy_setopt(curl_api2, CURLOPT_URL, mensaje_enviar);
            curl_easy_setopt(curl_api2, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl_api2, CURLOPT_WRITEDATA, &strbuf2);
            printf("Enviando: %s\n", mensaje_enviar);
            curl_easy_perform(curl_api2);
            string_buffer_finish(&strbuf2);
          }
        }
      }
      cJSON_Delete(json);
    }
    else
    {
      fprintf(stderr, "Error en getUpdates: %s\n", curl_easy_strerror(res));
    }

    string_buffer_finish( &strbuf );
    sleep(2);
  }

  curl_easy_cleanup( curl_api1 );
  curl_easy_cleanup( curl_api2 );
  return EXIT_SUCCESS;
}
