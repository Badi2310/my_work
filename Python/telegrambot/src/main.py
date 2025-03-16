import telebot
from telebot import types
from settings import token
import os
import requests
import json

my_API = "e054c4ccf3b3e01a3e97c256453da65d"
bot = telebot.TeleBot(token)
    
@bot.message_handler(commands = ['start'])
async def start(message):
    bot.send_message(message.chat.id, "Привет, введи имя города")
    
    
@bot.message_handler(content_types = ["text"])
def get_weather(message):
    city = message.text.strip().lower()
    request = requests.get(f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid={my_API}&units=metric")

    if request.status_code == 200:
        data = json.loads(request.text)
        celcium = "U+2103"
        bot.reply_to(message, f"Температура: {round(data["main"]["temp"])}'C\n"
                            f"Чувствуется как: {round(data["main"]["feels_like"])}\n"
                            f"Влажность: {data["main"]["humidity"]}\n"
                            f"Этот город в {data["sys"]["country"]}")
        
        image = ""        
        if data["main"]["temp"] > 15:
            image = "assets/hot.png"
        elif 15 >= data["main"]["temp"] > 5:
            image = "assets/warm.png"
        else:
            image = "assets/cold.jpeg"
        
        with open(image, 'rb') as file:
            bot.send_photo(message.chat.id, file)
    else:
        bot.send_message(message.chat.id, "неправильное имя города!")
    
bot.polling(none_stop = True)