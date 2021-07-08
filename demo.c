/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "http_parser.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* rand */
#include <string.h>
#include <stdarg.h>

int my_on_message_begin_callback(http_parser* parser)
{
  printf("on_message_begin, parser=%p\n", parser);
  return 0;
}

int my_on_url_callback(http_parser* parser, const char *buf, size_t length)
{
  char val[length + 1];
  memcpy(&val, buf, length);
  val[length] = '\0';
  printf("on_url, parser=%p, url=%s\n", parser, val);
  return 0;
}

int my_on_status_callback(http_parser* parser, const char *buf, size_t length)
{
  char val[length + 1];
  memcpy(&val, buf, length);
  val[length] = '\0';
  printf("on_status, parser=%p, status=%s\n", parser, val);
  return 0;
}

int my_on_header_field_callback(http_parser* parser, const char *buf, size_t length)
{
  char val[length + 1];
  memcpy(&val, buf, length);
  val[length] = '\0';
  printf("on_header_field, parser=%p, header_field=%s\n", parser, val);
  return 0;
}

int my_on_header_value_callback(http_parser* parser, const char *buf, size_t length)
{
  char val[length + 1];
  memcpy(&val, buf, length);
  val[length] = '\0';
  printf("on_header_value, parser=%p, header_value=%s\n", parser, val);
  return 0;
}

int my_on_headers_complete_callback(http_parser* parser)
{
  printf("on_headers_complete, parser=%p\n", parser);
  return 0;
}

int my_on_body_callback(http_parser* parser, const char *buf, size_t length)
{
  char val[length + 1];
  memcpy(&val, buf, length);
  val[length] = '\0';
  printf("on_body, parser=%p, body=%s\n", parser, val);
  return 0;
}

int my_on_message_complete_callback(http_parser* parser)
{
  printf("on_message_complete, parser=%p\n", parser);
  return 0;
}

int my_on_chunk_header_callback(http_parser* parser)
{
  printf("on_chunk_header, parser=%p\n", parser);
  return 0;
}

int my_on_chunk_complete_callback(http_parser* parser)
{
  printf("on_chunk_complete, parser=%p\n", parser);
  return 0;
}


int main (void)
{
  printf("hello\n");

  http_parser parser;
  http_parser_init(&parser, HTTP_REQUEST);

  http_parser_settings settings;
  settings.on_message_begin = my_on_message_begin_callback;
  settings.on_url = my_on_url_callback;
  settings.on_status = my_on_status_callback;
  settings.on_header_field = my_on_header_field_callback;
  settings.on_header_value = my_on_header_value_callback;
  settings.on_headers_complete = my_on_headers_complete_callback;
  settings.on_body = my_on_body_callback;
  settings.on_message_complete = my_on_message_complete_callback;
  settings.on_chunk_header = my_on_chunk_header_callback;
  settings.on_chunk_complete = my_on_chunk_complete_callback;

  const char* buf = 
      "GET / HTTP/1.1\r\n"
      "Host: www.baidu.com\r\n"
      "User-Agent: Mozilla/5.0\r\n"
      "Accept: text/html\r\n"
      "\r\n";
  http_parser_execute(&parser, &settings, buf, strlen(buf));

  printf("return 0;\n");
  return 0;
}

