# Простой эхобот телеграм на Си

#### У бота нет практического применения, кроме как повеселиться в написании самого бота на нетипичном ему языке.

- Подключаем токен, через файл config.h
```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H
// Замените "YOUR_BOT_TOKEN" на токен вашего бота
#define BOT_TOKEN "YOUR_BOT_TOKEN"
#endif 
```

- либо раскоментировав строку в коде.
```c
const char* BOT_TOKEN = "YOUR_BOT_TOKEN";
```

- Компилируется с флагом -lcurl
``` bash
gcc -o echo-bot echo-bot_c.c -lcurl
```
- Запустив вводим chat id отправителя, затем текст сообщения.

![img](./img/1.png)
