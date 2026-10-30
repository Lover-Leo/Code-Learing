while True:
    text = input("输入q退出")
    if text == 'q':
        break;
    try:
        minutes = int(text)
        print(f"本次学习了{minutes}分钟")
    except ValueError:
        print("请输入整数")