#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
	while (s) {

	int j = 0;
	int words = mx_count_words(s, c);
	char **string = (char **) malloc((words + 1) * sizeof(char *));

	for (int i = 0; i < words; i++) {
		while (*s == c) {
			s++;
		} 
		j = mx_get_char_index(s, c);

		if (j == -1) {
			*string = mx_strndup(s, j);
			string++;
			*string = NULL;
			string -= words;
			return string;
		}	
		*string = mx_strndup(s, j);
		s += j;
		string++;
	}
	*string = NULL;
	string -= words;	
	return string;
	}
return NULL;
}

