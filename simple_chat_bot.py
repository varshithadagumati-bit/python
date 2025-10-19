def simple_bot():
    while True:
        user = input("You: ")
        if "hello" in user.lower():
            print("Bot: Hi ra bro 👋")
        elif "bye" in user.lower():
            print("Bot: Bye ra 🔥")
            break
        else:
            print("Bot: Naku ardam kaledu ra 😅")

simple_bot()
