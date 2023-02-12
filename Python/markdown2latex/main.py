import re


def wrap_chinese(text):
    pattern = re.compile(r'[\u4e00-\u9fff\u3000-\u303f\ufb00-\ufffd]+')
    return pattern.sub(r'<a>\g<0><b>', text)


def mian():
    text = 'aa试本。BB中文aaa哈28y试0q'
    print("原始文本： " + text+"\n")

    result = wrap_chinese(text)
    print("处理后的文本：" + result)


if __name__ == '__main__':
    mian()
