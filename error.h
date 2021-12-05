// error.h
#define ERROR(...)                                                             \
  {                                                                            \
    fprintf(stderr, "ERROR IN %s %s [%d]:", __FILE__, __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, "\n");                                                     \
  }
