#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "config.h" // Включите файл с токеном

// Раскоментируйте и замените "YOUR_BOT_TOKEN" на токен вашего бота, по умолчаниюб для безопасности, токен хранится в config.h
// const char* BOT_TOKEN = "YOUR_BOT_TOKEN";

// Функция для кодирования текста в URL-совместимую строку
char* urlencode(const char* input) {
    CURL* curl = curl_easy_init();
    if (curl) {
        char* output = curl_easy_escape(curl, input, 0);
        curl_easy_cleanup(curl);
        return output;
    }
    return NULL;
}

// Обработка входящего сообщения и отправка ответа
void handle_message(const char* chat_id, const char* text) {
    // Кодируем текст перед вставкой в URL
    char* encoded_text = urlencode(text);

    if (encoded_text) {
        // Создаем URL для отправки сообщения с закодированным текстом
        char url[1024];
        snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s", BOT_TOKEN, chat_id, encoded_text);

        // Инициализируем библиотеку libcurl
        CURL* curl = curl_easy_init();
        if (curl) {
            // Устанавливаем URL для запроса
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Разрешаем следовать перенаправлениям

            // Выполняем запрос
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "Ошибка curl_easy_perform(): %s\n", curl_easy_strerror(res));
            }

            // Завершаем сеанс libcurl
            curl_easy_cleanup(curl);
        }

        // Освобождаем память, выделенную для закодированного текста
        curl_free(encoded_text);
    }
}

int main() {
    // Запуск основного цикла
    while (1) {
        char chat_id[64];
        char text[1024];

        // Ввод входящего сообщения (chat_id и text)
        printf("\nВведите ID чата: ");
        scanf("%s", chat_id);
        
        printf("Введите текст: ");
        getchar(); // Пропустить символ новой строки, оставшийся в буфере ввода
        
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0';

        // Вывод полученных данных
        printf("Получено обновление:\n");
        printf("ID чата: %s\n", chat_id);
        printf("Текст: %s\n", text);

        // Отправка ответа с помощью функции handle_message
        handle_message(chat_id, text);
    }

    return 0;
}
