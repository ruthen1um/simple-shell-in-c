#ifndef _CORE_H_
#define _CORE_H_

void rush_loop();
void rush_prompt();
char *rush_read_line();
char **rush_tokenize(char *line);
int rush_execute(char **tokens);

#endif /* _CORE_H_ */
