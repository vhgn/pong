#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jsmn/jsmn.h"

#include "prefload.h"

appearance*
get_player_prefs
	(unsigned index)
{
	appearance *look = malloc(7);
	char *content = load_file("prefs.json");
	int r;
	jsmn_parser p;
	jsmntok_t t[MAX_TOKENS];
	
	jsmn_init(&p);
	r = jsmn_parse(&p, content, strlen(content), t, MAX_TOKENS);
	if(r < 0)
	{
		printf("Failed to parse JSON: %d\n", r);
		return NULL;
	}
	if(t[0].type != JSMN_ARRAY)
	{
		printf("%s", "Failed to understand preference structure");
		return NULL;
	}

	unsigned object_index = 0,
		array_start, array_end;
	for(int i = 0; i <= MAX_TOKENS; i++)
	{
		if(t[i].type == JSMN_OBJECT)
		{
			if(object_index == index)
			{
				array_start = t[i].start;
				array_end = t[i].end;
			}
			object_index++;
		}
		if
			(t[i].start > array_start &&
			t[i].end < array_end &&
			t[i].type == JSMN_STRING)
		{
			char * tok = strndup(&content[t[i].start], t[i].end - t[i].start);
			if(strcmp(tok, "top") == 0)
			{
				i++;
				char c = content[t[i].start];
				look->top_char = c;
			}
			else if(strcmp(tok, "middle") == 0)
			{
				i++;
				char c = content[t[i].start];
				look->middle_char = c;
			}
			else if (strcmp(tok, "bottom") == 0)
			{
				i++;
				char c = content[t[i].start];
				look->bottom_char = c;
			}
		}
	}

	return look;
}

char*
load_file
	(char *file_name)
{
	FILE *fp;
	char *content;
	int index = 0;

	fp = fopen(file_name, "r");
	if(fp == NULL)
	{
		printf("%s", "Error in opening file");
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	int file_length = ftell(fp);
	rewind(fp);

	content = malloc(file_length);

	while(1)
	{
		int c = fgetc(fp);
		
		if(c < 0)
		{
			content[index] = '\0';
			break;
		}
		
		content[index++] = c;
	}

	fclose(fp);

	return content;
}
