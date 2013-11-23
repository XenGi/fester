#ifndef _MAIN2_H_
#define _MAIN2_H_

//int dosomething(char* message);

typedef void (*cheesefunc)(char *name, void *user_data);
int do_setup();
void do_start_receiving(cheesefunc user_func, void *user_data);
void do_stop_receiving();

void do_teardown(void);
void do_send_message(char* origin, char* message);


#endif
