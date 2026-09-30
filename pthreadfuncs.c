#include "pthreadfuncs.h"

// common resources - is a file for logging
int g_fd = -1;
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

// git ID of current thread
pid_t getThreadID(void) {
    return (pid_t) syscall(SYS_gettid);
}

// write a string from thread with mutex
// Поменяли void на int в начале строки:
int write_line(const char *msg) {
    pthread_mutex_lock(&g_lock);
    int len = strlen(msg);
    ssize_t n = write(g_fd, msg, len);
    if (n < 0) {
        // Твой вывод ошибки оставляем на месте
        fprintf(stderr, "write() failed: %s, [file descr = %d]\n", strerror(errno), g_fd);
    }
  pthread_mutex_unlock(&g_lock);

    // Твой nanosleep из 5 задания (если он остался ниже, оставь его перед return)

    // ВОТ ЭТО ВСТАВЛЯЕМ В САМЫЙ КОНЕЦ ФУНКЦИИ (ЗАДАНИЕ 6):
    return (n == len) ? 0 : -1;
}


// function for thread
void *func_thread(void *arg){
//pthread_detach(pthread_self());
struct ThreadArgs *t = (struct ThreadArgs *)arg;
    char buf[128];
    // write something in opened file
        for (int i = 0; i < COUNT_ITERATIONS; ++i) {
        // Здесь твой старый snprintf и write_line(buf);
        snprintf(buf, sizeof(buf),
            "[tag = %s] pid = %d ppid = %d tid = %d iter = %d\n", t->tag, getpid(), getppid(), getThreadID(), i);
        write_line(buf);
        
       // ВОТ ЭТО ВСТАВЛЯЕМ ВМЕСТО USLEEP (ЗАДАНИЕ 5):
        struct timespec ts;
        ts.tv_sec = 1;
        ts.tv_nsec = 0; 
        nanosleep(&ts, NULL);
    }

    return NULL;
}

void about()  {
    printf("Pthread example\n");
}
