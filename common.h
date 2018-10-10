#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

#define COLOR_NONE  "\e[0m"
#define COLOR_RED   "\e[1;31m"
#define COLOR_BLUE  "\e[1;34m"

#define log_info(fmt, ...)  \
	fprintf(stdout, "log_info:%s:%s:%d:>> "fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#ifdef D

#define log_debug(fmt, ...) \
	fprintf(stdout, COLOR_BLUE"log_debug:%s:%s:%d:>> "fmt"\n"COLOR_NONE, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#else

#define log_debug(fmat, ...)

#endif

#define log_warning(fmt, ...) \
	fprintf(stdout, "log_warning:%s:%s:%d:>> "fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)


#define log_error(fmt, ...) \
	fprintf(stderr, COLOR_RED"log_error:%s:%s:%d:>> "fmt"\n"COLOR_NONE, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif /* #ifndef COMMON_H */
