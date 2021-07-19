//log.h
#ifdef DEBUG
#define PRINT_DBG(...)                                                    \
    {                                                                     \
        fprintf(stderr, "%s %s [%d]:", __FILE__, __FUNCTION__, __LINE__); \
        fprintf(stderr, __VA_ARGS__);                                     \
        fprintf(stderr, "\n");                                            \
    }
#else
    #define PRINT_DBG(...) {};
#endif
