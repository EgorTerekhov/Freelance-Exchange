FROM ubuntu:22.04

# Устанавливаем зависимости
RUN apt-get update && \
    apt-get install -y build-essential cmake git libssl-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*



# Создаём рабочую директорию
WORKDIR /freelance_exchange

# Копируем исходники в контейнер
COPY . .

# Создаём папку для сборки
RUN mkdir -p build
WORKDIR /freelance_exchange/build

# Собираем проект через CMake
# Параллельная сборка(я крутой)
RUN cmake .. && make -j$(nproc)

# Устанавливаем рабочую директорию для запуска программы
WORKDIR /freelance_exchange

# Команда по умолчанию при запуске контейнера
CMD ["./build/freelance_exchange"]
