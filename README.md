# Инструкция по сборке

1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/Torcna/computer-club.git
2. Обновите и инициализируйте git submodules:
   ```bash
   git submodule update --init --recursive
3. Создайте две директории: bin и build:
   ```bash
   mkdir bin && mkdir build
4. Перейдите в директорию build и выполните генерацию проекта:
   ```bash
   cd build && cmake ..
5. Соберите проект в режиме Release:
   ```bash
   cmake --build . --config Release

Готово! Теперь у вас есть собранный проект.

# Исполняемые файлы

После сборки проекта в директории `bin` будут находиться два исполняемых файла:

1. **club**  
   Это основной исполняемый файл. Для его работы необходимо передать через пробел один аргумент — название файла с входными данными.  
   Пример запуска:
   ```bash
   ./club data_default.txt
Входные данные должны находиться в директории files_for_main_task/. Вы можете использовать готовые файлы из этой директории или добавить свои.

2. **tests**   
   Это бинарный файл, который запускает тесты, реализованные с использованием Google Test.
   Для его работы не требуется никаких дополнительных аргументов. Просто запустите файл:
   ```bash
   ./tests

Тесты используют входные данные из директории files_for_tests/.

# Структура Проекта

![heheh](https://github.com/user-attachments/assets/87192843-305d-45cc-9bba-78a5639bc7b9)

