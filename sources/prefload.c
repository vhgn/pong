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
		printf("Failed to understand preference structure");
		return NULL;
	}

	for(int i = 0; i <= MAX_TOKENS; i++)
	{
		printf("---%d---\n", i);
		printf("%d\n", t[i].type);
		printf("start: %d, end: %d, size: %d\n",t[i].start, t[i].start, t[i].size);
		printf("%.*s\n", t[i + 1].end - t[i + 1].start,
             content + t[i + 1].start);
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
		printf("Error in opening file");
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
