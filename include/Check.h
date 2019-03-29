#ifndef __CHECK_H__
#define __CHECK_H__

#define CHECK(nameFunction, retValue)				\
do {								\
	if(retValue == -1)					\
	{							\
    perror(nameFunction);\
    return 0;   \
	}							\
	else							\
		printf("%s succeeded\n", nameFunction);		\
} while(0)							\

#endif /* __CHECK_H__ */
