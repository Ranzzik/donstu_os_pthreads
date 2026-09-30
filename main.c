#include "pthreadfuncs.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "pthreadfuncs.h"

int main(void) {
    pthread_t threads[COUNT_THREADS];
    struct ThreadArgs args[COUNT_THREADS];

    // Открываем файл лога
    g_fd = open("output.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (g_fd < 0) {
        perror("open failed");
        return EXIT_FAILURE;
    }

    // Задание 8: Перевели логирование старта на write_line
    write_line("MAIN_START"); 

    // Задание 7: Динамическая инициализация аргументов в цикле
    for (int i = 0; i < COUNT_THREADS; i++) {
        args[i].id = i + 1;
        snprintf(args[i].tag, sizeof(args[i].tag), "T%d", i);

        int rc = pthread_create(&threads[i], NULL, func_thread, &args[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(rc));
            return EXIT_FAILURE;
        }
    }

    // Задание 9: ЭКСПЕРИМЕНТ. ВРЕМЕННО ЗАКЛИНИВАЕМ ОЖИДАНИЕ ПОТОКОВ

    for (int i = 0; i < COUNT_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }


    if (close(g_fd) < 0) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

