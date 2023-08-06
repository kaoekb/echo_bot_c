#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "config.h" // Включаем файл с токеном


// Раскоментируйте и замените "YOUR_BOT_TOKEN" на токен вашего бота, по умолчаниюб для безопасности, токен хранится в config.h
// const char* BOT_TOKEN = "YOUR_BOT_TOKEN";

// Обработка входящего сообщения и отправка ответа
void handle_message(const char* chat_id, const char* text) {
    // Создание URL для отправки ответа
    char url[1024];
    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s", BOT_TOKEN, chat_id, text);

    // Инициализация библиотеки libcurl
    CURL* curl = curl_easy_init();
    if (curl) {
        // Настройка запроса
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Выполнение запроса
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Освобождение ресурсов
        curl_easy_cleanup(curl);
    }
}

int main() {
    // Запуск основного цикла
    while (1) {
        char chat_id[64];
        char text[1024];

        // Ввод входящего сообщения (chat_id и text)
        printf("\nEnter chat ID: ");
        scanf("%s", chat_id);
        printf("Enter text: ");
        getchar(); // Чтение лишнего символа новой строки после предыдущего ввода
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // Удаление символа новой строки из текста

        // Вывод полученных данных
        printf("Received update:\n");
        printf("Chat ID: %s\n", chat_id);
        printf("Text: %s\n", text);

        // Отправка ответа с помощью функции handle_message
        handle_message(chat_id, text);
    }

    return 0;
}
