def translate(str, old, new):
    return str.replace(old, new)


strx = ".\Z1_rptD_alert_lsj\20220503-1.csv"
print(translate(strx, "\\", "/"))
