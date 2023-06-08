def delete_after_slash(s: str) -> str:
    # 使用 split() 方法分割字符串
    splited = s.split('/', 1)
    # 取出分割后的第一部分
    if splited:
        result = splited[1]
    else:
        result = ''
    # 使用 join() 方法重新拼接字符串
    return result


# 举例
s = 'example/text'
result = delete_after_slash(s)
print(result)  # 'example'
